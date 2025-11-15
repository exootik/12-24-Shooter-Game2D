#include "Player.h"
#include "GameScene.h"
#include "GameManager.h"
#include "AssetManager.h"
#include "InputManager.h"

#include "Projectile.h"

#include <iostream>

Player::Player(float width, float height, int layer, const Color& color, bool hasCollision, Scene* pScene) : Entity(width,height,layer, hasCollision,color, pScene)
{
	SetCollisionSize(GetColliderShape<CircleShape*>()->GetRadius() * 0.5);
}

Player::Player(float width, float height, int layer, Scene* pScene) : Entity(width, height, layer, true, Color::Red, pScene)
{
	SetCollisionSize(GetColliderShape<CircleShape*>()->GetRadius());
}

void Player::OnUpdate()
{
	GameScene* currentScene = GetScene<GameScene>();
	int ratio = GetScene<GameScene>()->ratio;

	int upBorder = currentScene->GetWindowHeight() * 0.25;
	int downBorder = currentScene->GetWindowHeight() * 0.75;
	int leftBorder = currentScene->GetWindowWidth() * 0.05;
	int rightBorder = currentScene->GetWindowWidth() * 0.6;

	if (GetPosition().m_y < upBorder)
	{
		m_canMoveUp = false;
	}
	if (GetPosition().m_y > downBorder)
	{
		m_canMoveDown = false;
	}
	if (GetPosition().m_x < leftBorder)
	{
		m_canMoveLeft = false;
	}
	if (GetPosition().m_x > rightBorder)
	{
		m_canMoveRight = false;
	}
	if (GetPosition().m_y > upBorder)
	{
		m_canMoveUp = true;
	}
	if (GetPosition().m_y < downBorder)
	{
		m_canMoveDown = true;
	}
	if (GetPosition().m_x > leftBorder)
	{
		m_canMoveLeft = true;
	}
	if (GetPosition().m_x < rightBorder)
	{
		m_canMoveRight = true;
	}
	if (m_boostSpeed)
	{
		m_tempTimeForBoostSpeed += GetScene<GameScene>()->GetDeltaTime();

		if (m_durationOfSpeedBoost < m_tempTimeForBoostSpeed)
		{
			m_boostSpeed = false;
			m_tempTimeForBoostSpeed = 0.0f;
		}
	}
	if (m_doUltimate)
	{
		m_tempTimeForUltimate += GetScene<GameScene>()->GetDeltaTime();

		if (m_durationOfUltimate - 5 < m_tempTimeForUltimate && m_canDoFireOfUltimate == true)
		{
			m_canDoFireOfUltimate = false;
			pProjectileUltimate = CreateEntity<Projectile>(800 *  ratio, 400 * ratio, 6, Color::Red);
			pProjectileUltimate->SetTag(GameScene::ULTIMATE);
			pProjectileUltimate->SetPosition(GetPosition().m_x + (GetWidth()), GetPosition().m_y);
			pProjectileUltimate->SetCollisionScale(0.4);
			pProjectileUltimate->projUltimate = true;
		}
		if (m_durationOfSpeedBoost < m_tempTimeForUltimate)
		{
			m_doUltimate = false;
			m_canDoFireOfUltimate = true;
			m_tempTimeForUltimate = 0.0f;
		}
	}
}

void Player::OnCollision(Entity* collidedWith)
{
	if (collidedWith->IsTag(GameScene::Tag::OBSTACLE))
	{
		m_lifePoint -= 1;
		collidedWith->SetTag(GameScene::Tag::OBSTACLEINNACTIF);
	}
    if (collidedWith->IsTag(GameScene::Tag::PROJECTILEENEMY))
    {
        m_lifePoint -= 1;
        collidedWith->SetTag(GameScene::Tag::PROJECTILEINNACTIF);
    }
	if (collidedWith->IsTag(GameScene::Tag::BONUS))
	{
		collidedWith->Destroy();
		if (m_bulletOfProjectile2 < 6)
		{
			m_bulletOfProjectile2 += 2;
		}
	}
}

void Player::UpdateSprite() 
{
	float healthPercentage = m_lifePoint / m_maxLifePoint;

	if (healthPercentage <= 0.3f)
	{
		SetSprite(m_sprite66);
	}
	else if (healthPercentage <= 0.6f)
	{
		SetSprite(m_sprite33);
	}
}

void Player::Movement(const GCInputSystem* inputsystem)
{
    float xDirection = 0.0f;
    float yDirection = 0.0f;

    if (inputsystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::UP_ARROW) && m_canMoveUp)
    {
        yDirection -= 1.0f;
        SetSpeed(500.0f);
		if (m_boostSpeed)
		{
			SetSpeed(750.0f);
		}
    }
    if (inputsystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::DOWN_ARROW) && m_canMoveDown)
    {
        yDirection += 1.0f;
        SetSpeed(500.0f);
		if (m_boostSpeed)
		{
			SetSpeed(750.0f);
		}
    }
    if (inputsystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::LEFT_ARROW) && m_canMoveLeft)
    {
        xDirection -= 1.0f;
        SetSpeed(500.0f);
		if (m_boostSpeed)
		{
			SetSpeed(750.0f);
		}
    }
    if (inputsystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::RIGHT_ARROW) && m_canMoveRight)
    {
        xDirection += 1.0f;
        SetSpeed(250.0f);
		if (m_boostSpeed)
		{
			SetSpeed(500.0f);
		}
    }

    if (xDirection != 0.0f || yDirection != 0.0f)
    {
        float length = std::sqrt(xDirection * xDirection + yDirection * yDirection);
        xDirection /= length;
        yDirection /= length;
    }
    SetDirection(xDirection, yDirection, GetSpeed());
}
void Player::DoBoostSpeed()
{
	m_boostSpeed = true;
}

void Player::DoUltimate()
{
	m_doUltimate = true;
}