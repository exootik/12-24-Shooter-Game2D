#include "pch.h"
#include "Entity.h"

#include "MyWindow.h"
#include "GameManager.h"
#include "Utils.h"
#include "Sprite.h"
#include "Color.h"
#include "AssetManager.h"
#include "AnimationManager.h"

Entity::Entity(float width, float height, int layer, bool hasCollision, const Color& color, Scene* pScene, COLLIDER_SHAPES shape)
	: m_width(width), m_height(height), m_pCurrentAnimation(nullptr), m_scale(Vect2(1.f,1.f)), 
	m_layer(layer), m_hasCollision(hasCollision), m_isColliderDisplay(false), m_origin(Vect2(0.5f,0.5f)), m_pScene(pScene),
	m_tagWithoutCollision(std::list<int>()), m_colliderhasSameSize(true),m_pSprite(nullptr)
{
	m_direction = Vect2(0.0f, 0.0f);
	m_speed = 0.0f;
	m_toDestroy = false;
	m_tag = -1;
	m_name = "A";

	m_pShape = m_pScene->GetWindow()->CreateRectShape(color);
	m_pShape->SetScale(m_scale.m_x, m_scale.m_y);
	m_pShape->SetWidth(width);
	m_pShape->SetHeight(height);

	Color colliderColor = color; 
	colliderColor.SetAlpha(100);
	
	switch (shape)
	{
	case Entity::CIRCLE:
		m_pColliderShape = SetColliderCircle(colliderColor,width);
		break;
	case Entity::RECT:
		m_pColliderShape = SetColliderRect(colliderColor,width,height);
		break;
	default:
		break;
	}

	m_pColliderShape->SetScale(1.f,1.f);

	m_currentFrameIndex = 0;
	m_currentFrameTime = 0.f;
	m_pos = Vect2(0.f, 0.f);

	m_target.isSet = false;
}


void Entity::SetPosition(float x, float y)
{
	x -= GetWidth() * m_origin.m_x;
	y -= GetHeight() * m_origin.m_y;

	m_pos.SetVector(x, y);
	
	m_pColliderShape->SetPosition(GetPosition() + m_colliderPos);
	m_pShape->SetPosition(m_pos);
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{

	x -= GetWidth() * ratioX;
	y -= GetHeight() * ratioY;

	m_pos.SetVector(x, y);

	m_pColliderShape->SetPosition(GetPosition() + m_colliderPos);
	m_pShape->SetPosition(m_pos);
}


void Entity::SetPosition(Vect2 pos)
{
	SetPosition(pos.m_x, pos.m_y);
}

Vect2 Entity::GetPosition()
{
	Vect2 position = m_pos;

	position.m_x += GetWidth() * m_origin.m_x;
	position.m_y += GetHeight() * m_origin.m_y;

	return position;
}

Vect2 Entity::GetPositionWithCustomOrigin(float ratioX, float ratioY)
{
	Vect2 position = m_pos; // Top Left pos

	position.m_x += GetWidth() * ratioX;
	position.m_y += GetHeight() * ratioY;

	return position;
}

bool Entity::GoToDirection(float x, float y, float speed)
{
	if (speed > 0)
		m_speed = speed;

	Vect2 position = GetPosition();
	Vect2 direction = Vect2(x - position.m_x, y - position.m_y);

	bool success = Utils::Normalize(direction);
	if (success == false)
		return false;

	m_direction = direction;

	return true;
}

bool Entity::GoToPosition(float x, float y, float speed)
{
	if (GoToDirection(x, y, speed) == false)
		return false;

	Vect2 position = GetPosition();

	m_target.position = { x, y };
	m_target.distance = Utils::GetDistance(position.m_x, position.m_y, x, y);
	m_target.isSet = true;

	return true;
}

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		m_speed = speed;

	m_direction = Vect2(x, y);
}


Scene* Entity::GetScene() const
{
	return m_pScene;
}

float Entity::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}

void Entity::SetLayer(int layer)
{
	GetScene()->ChangeEntityLayer(this, layer);
	m_layer = layer;
}


void Entity::SetSprite(Sprite* pSprite)
{
	m_pSprite = pSprite;
	SetWidth(m_pSprite->GetSpriteWidth());
	SetHeight(m_pSprite->GetSpriteHeight());
}

void Entity::DrawCollider(MyWindow* pWindow)
{
	switch (m_colliderShape)
	{
	case Entity::CIRCLE:
		pWindow->Draw(dynamic_cast<CircleShape*>(m_pColliderShape));
		break;
	case Entity::RECT:
		pWindow->Draw(dynamic_cast<RectShape*>(m_pColliderShape));
		break;
	default:
		break;
	}
}

void Entity::SetScale(Vect2 scale)
{
	m_scale = scale;
	m_pShape->SetScale(scale.m_x,scale.m_y);
	m_pColliderShape->SetScale(scale.m_x, scale.m_y);

	if (m_pSprite != nullptr)
		m_pSprite->SetScale(scale);
}

void Entity::SetScale(float scaleX, float scaleY)
{
	SetScale(Vect2(scaleX, scaleY));
}

void Entity::SetWidth(float width)
{
	m_width = width;
	m_pShape->SetWidth(width);
}

void Entity::SetHeight(float height)
{
	m_height = height;
	m_pShape->SetHeight(height);
}

void Entity::SetSize(float width, float height)
{
	SetWidth(width);
	SetHeight(height);
}

bool Entity::IsColliding(Entity* other)
{
	switch (m_colliderShape)
	{
	case Entity::CIRCLE:
		return IsCollidingCircle(other);
		break;
	case Entity::RECT:
		return IsCollidingRect(other);
		break;
	default:
		std::cout << "ColliderShape Unknow" << std::endl;
		return false;
		break;
	}
}

bool Entity::IsInside(float x, float y)
{
	switch (m_colliderShape)
	{
	case Entity::CIRCLE:
		return IsInsideCircle(x,y);
		break;
	case Entity::RECT:
		return IsInsideRect(x,y);
		break;
	default:
		std::cout << "ColliderShape Unknow" << std::endl;
		return false;
		break;
	}
}

bool Entity::IsCollidingRect(Entity* other) //AABB
{
	RectShape* otherCollide = other->GetColliderShape<RectShape*>();
	RectShape* collide = GetColliderShape<RectShape*>();

	bool FromRight = collide->GetPos().m_x < otherCollide->GetPos().m_x +otherCollide->GetWidth();
	bool FromLeft = collide->GetPos().m_x + collide->GetWidth() > otherCollide->GetPos().m_x;
	bool FromTop = collide->GetPos().m_y + collide->GetHeight() > otherCollide->GetPos().m_y;
	bool FromBottom = collide->GetPos().m_y < otherCollide->GetPos().m_y + otherCollide->GetHeight();


	return (FromRight && FromLeft && FromTop && FromBottom);
}

bool Entity::IsCollidingCircle(Entity* other) //Circle
{
	CircleShape* collide = GetColliderShape<CircleShape*>();
	CircleShape* otherCollide = other->GetColliderShape<CircleShape*>();

	float posX = collide->GetPos(0.5f, 0.5f).m_x;
	float posY = collide->GetPos(0.5f, 0.5f).m_y;
	float otherX = otherCollide->GetPos(0.5f, 0.5f).m_x;
	float otherY = otherCollide->GetPos(0.5f, 0.5f).m_y;

	float dx = posX - otherX;
	float dy = posY - otherY;


	return pow((dx * dx + dy * dy) ,0.5) < (collide->GetRadius() + otherCollide->GetRadius()) ;
}


bool Entity::IsInsideRect(float x, float y) //AABB
{
	RectShape* collide = GetColliderShape<RectShape*>();

	bool FromRight = collide->GetPos().m_x < x;
	bool FromLeft = collide->GetPos().m_x + collide->GetWidth() > x;
	bool FromTop = collide->GetPos().m_y + collide->GetHeight() > y;
	bool FromBottom = collide->GetPos().m_y < y;

	return (FromRight && FromLeft && FromTop && FromBottom);
}

bool Entity::IsInsideCircle(float x, float y) //Circle
{
	CircleShape* collide = GetColliderShape<CircleShape*>();

	float dx = x - collide->GetPos(0.5,0.5).m_x;
	float dy = y - collide->GetPos(0.5,0.5).m_y;

	return (dx * dx + dy * dy) < (collide->GetRadius() * collide->GetRadius());

}

bool Entity::AllowedCollision(Entity* pEntity)
{
	for (int notAllowedTag : m_tagWithoutCollision) {
		if (notAllowedTag == pEntity->m_tag)
			return false;
	}
	return true;
}

void Entity::SetCollisionSize(float width, float height)
{
	switch (m_colliderShape)
	{
	case Entity::CIRCLE:
		dynamic_cast<CircleShape*>(m_pColliderShape)->SetRadius(width);
		break;
	case Entity::RECT:
		dynamic_cast<RectShape*>(m_pColliderShape)->SetSize(width, height);
		break;
	default:
		break;
	}
}

// Reset COllider size & pos same as Entity
void Entity::SetColliderOnEntity()
{
	m_colliderPos.SetVector(0.f, 0.f);
	m_pColliderShape->SetPosition(m_pos);
}


DrawableShape* Entity::SetColliderCircle(Color& colliderColor, float radius)
{
	CircleShape* circle = m_pScene->GetWindow()->CreateCircleShape(colliderColor);
	circle->SetRadius(radius);
	return circle;
}

DrawableShape* Entity::SetColliderRect(Color& colliderColor, float width, float height)
{
	RectShape* rect = m_pScene->GetWindow()->CreateRectShape(colliderColor);
	rect->SetSize(width,height);
	return rect;
}

void Entity::Update()
{

	if (m_pCurrentAnimation != nullptr)
	{
		if (m_pCurrentAnimation->Update(&m_currentFrameIndex, &m_currentFrameTime, m_pSprite) == false)
			StopAnimation();
	}

	OnUpdate();

	if (m_pSprite != nullptr)
		m_pSprite->Update(this);

}

void Entity::FixedUpdate()
{
	float dt = GetDeltaTime();
	float distance = dt * m_speed;
	Vect2 translation = m_direction * distance;
	SetPosition((translation + GetPosition()));

	if (m_target.isSet)
	{
		m_target.distance -= distance;

		if (m_target.distance <= 0.f)
		{
			SetPosition(m_target.position.m_x, m_target.position.m_y);
			m_direction = Vect2(0.f, 0.f);
			m_target.isSet = false;
		}
	}
	OnFixedUpdate();
}


bool Entity::PlayAnimation(const char* animationName)
{
	RessourcesResult<Animation> anim = AnimationManager::Get()->GetAnimation(animationName);
	if (anim.success)
	{
		m_pSprite = anim.resource->GetSprite();
		m_pCurrentAnimation = anim.resource;
		m_currentFrameIndex = 0;
		m_currentFrameTime = 0.f;
		m_pCurrentAnimation->PlayAnimation(m_pSprite);
		SetWidth(m_pSprite->GetSpriteWidth());
		SetHeight(m_pSprite->GetSpriteHeight());
	}
	return anim.success;
}

void Entity::StopAnimation()
{
	m_pCurrentAnimation = nullptr;
}