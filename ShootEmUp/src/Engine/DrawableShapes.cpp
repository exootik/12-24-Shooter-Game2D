#include "pch.h"
#include "DrawableShapes.h"
#include "Render.h"
#include "AssetManager.h"

#pragma region SFML

//Circle

SFMLCircle::SFMLCircle(const Color& color) : m_sfCircle(sf::CircleShape())
{
	m_color = color;
	m_sfCircle.setRadius(1.f);
	m_sfCircle.setPosition(0.f,0.f);
	m_sfCircle.setFillColor(m_color.ToSFMLColor());
}

SFMLCircle::~SFMLCircle()
{}

void SFMLCircle::SetRadius(float radius)
{
	m_radius = radius;
	m_width = m_radius * 2;
	m_height = m_radius * 2;
	m_sfCircle.setRadius(m_radius);
}

void SFMLCircle::SetPosition(float x, float y)
{
	m_pos.m_x = x - GetRadius();
	m_pos.m_y = y - GetRadius();
	m_sfCircle.setPosition(m_pos.ToSfmlVecf());
}

void SFMLCircle::SetPosition(Vect2 pos)
{
	SetPosition(pos.m_x, pos.m_y);
}

void SFMLCircle::SetScale(float x, float y)
{
	m_scale.SetVector(x, y);
	m_sfCircle.setScale(m_scale.ToSfmlVecf());
}

//Rect

SFMLRectShape::SFMLRectShape(const Color& color) : m_sfRect(sf::RectangleShape())
{
	m_color = color;
	m_sfRect.setFillColor(m_color.ToSFMLColor());
}

SFMLRectShape::~SFMLRectShape()
{}

void SFMLRectShape::SetSize(float width, float height)
{
	m_width = width; 
	m_height = height; 
	m_sfRect.setSize(sf::Vector2(width, height));
}

void SFMLRectShape::SetWidth(float width)
{
	SetSize(width, m_height);
}

void SFMLRectShape::SetHeight(float height)
{
	SetSize(m_width, height);
}

void SFMLRectShape::SetPosition(float x, float y)
{
	m_pos.m_x = x;
	m_pos.m_y = y;
	m_sfRect.setPosition(m_pos.ToSfmlVecf());
}

void SFMLRectShape::SetPosition(Vect2 pos)
{
	m_pos = pos;
	m_sfRect.setPosition(m_pos.ToSfmlVecf());
}

void SFMLRectShape::SetScale(float x, float y)
{
	m_scale.SetVector(x, y);
	m_sfRect.setScale(m_scale.ToSfmlVecf());
}

//Text

SFMLText::SFMLText(const Color& color,const char* text,const char* font) : m_sfText(sf::Text())
{
	m_color = color;
	m_sfText.setString(text);
	m_sfText.setFillColor(m_color.ToSFMLColor());
	m_sfText.setFont(AssetManager::Get()->GetFont(font).resource->m_sfFont);
}

SFMLText::~SFMLText()
{}

void SFMLText::SetText(const char* text)
{
	m_sfText.setString(text);
}


void SFMLText::SetPosition(float x, float y)
{
	m_pos.m_x = x;
	m_pos.m_y = y;
	m_sfText.setPosition(m_pos.ToSfmlVecf());
}

void SFMLText::SetPosition(Vect2 pos)
{
	m_pos = pos;
	m_sfText.setPosition(m_pos.ToSfmlVecf());
}

void SFMLText::SetScale(float x, float y)
{
	m_scale.SetVector(x, y);
	m_sfText.setScale(m_scale.ToSfmlVecf());
}

void SFMLText::SetSize(int size)
{
	m_sfText.setCharacterSize(size);
}

#pragma endregion

#pragma region GC

//Circle

GCCircle::GCCircle(GCGraphics* pGraphics, const Color& color) : 
	m_pGeometry(nullptr), m_pMaterial(nullptr), m_pMesh(nullptr), textureCircle("../Engine/Textures/circle"), m_worldMatrix(DirectX::XMMATRIX())
{
}

GCCircle::~GCCircle()
{}

void GCCircle::SetRadius(float radius)
{
	m_radius = radius;
	m_width = radius * 2; 
	m_height = radius * 2;
	ComputeWorldMatrix();
}


void GCCircle::SetPosition(float x, float y)
{
	m_pos.m_x = x - m_radius;
	m_pos.m_y = y - m_radius;
	ComputeWorldMatrix();
}

void GCCircle::SetPosition(Vect2 pos)
{
	SetPosition(pos.m_x, pos.m_y);
}

void GCCircle::SetScale(float x, float y)
{
	m_scale.SetVector(x, y);
	ComputeWorldMatrix();
}

void GCCircle::ComputeWorldMatrix()
{
	m_worldMatrix = DirectX::XMMatrixScaling(m_radius, m_radius, 1.0f) * DirectX::XMMatrixTranslation(m_pos.m_x, m_pos.m_y, 0.0f);
}

//Rect

GCRect::GCRect(GCGraphics* pGraphics, const Color& color) : 
	m_pGeometry(nullptr), m_pMaterial(nullptr), m_pMesh(nullptr), m_worldMatrix(DirectX::XMMATRIX())
{
	m_color = color;
	pGraphics->InitializeGraphicsResourcesStart();
	m_pGeometry = pGraphics->CreateGeometryPrimitive(Plane, m_color.ToDirectXColor()).resource;
	m_pMesh = pGraphics->CreateMeshColor(m_pGeometry).resource;
	GCShader* pShader = pGraphics->CreateShaderColor().resource;
	pGraphics->InitializeGraphicsResourcesEnd();

	m_pMaterial = pGraphics->CreateMaterial(pShader).resource;
}

GCRect::~GCRect()
{
	delete m_pGeometry;
	delete m_pMesh;
	delete m_pMaterial;
}

void GCRect::SetSize(float width, float height)
{
	SetWidth(width);
	SetHeight(height);
}

void GCRect::SetWidth(float width)
{
	m_width = width;
	ComputeWorldMatrix();
}

void GCRect::SetHeight(float height)
{
	m_height = height;
	ComputeWorldMatrix();
}


void GCRect::SetPosition(float x, float y)
{
	m_pos.m_x = x;
	m_pos.m_y = y;
	ComputeWorldMatrix();
}

void GCRect::SetPosition(Vect2 pos)
{
	m_pos = pos;
	ComputeWorldMatrix();
}

void GCRect::SetScale(float x, float y)
{
	m_scale.SetVector(x, y);
	ComputeWorldMatrix();
}

void GCRect::ComputeWorldMatrix()
{
	m_worldMatrix = DirectX::XMMatrixScaling(m_width, m_height, 1.0f) * DirectX::XMMatrixTranslation(m_pos.m_x, m_pos.m_y, 0.0f);
}

//Text

GCText::GCText(GCGraphics* pGraphics,const Color& color, const char* text) :
	m_pGeometry(nullptr), m_pMesh(nullptr), m_pMaterial(nullptr), m_worldMatrix(DirectX::XMMATRIX())
{

	int flags = 0;
	GC_SET_FLAG(flags, GC_VERTEX_POSITION);
	GC_SET_FLAG(flags, GC_VERTEX_COLOR);
	GC_SET_FLAG(flags, GC_VERTEX_UV);

	m_color = color;
	m_text = text;
	m_pGeometry = pGraphics->GetFontGeometryLoader()->CreateText(m_text, m_color.ToDirectXColor());

	std::string shaderpath = "../../res/Render/Shaders/textTexture.hlsl";
	std::string csoshaderpath = "../../res/Render/CsoCompiled/textTexture";
	GCShader* pShader = pGraphics->CreateShaderCustom(shaderpath, csoshaderpath,flags).resource;

	m_pMesh = pGraphics->CreateMeshCustom(m_pGeometry, flags).resource;
	m_pMaterial = pGraphics->CreateMaterial(pShader).resource;
	m_pMaterial->SetTexture(AssetManager::Get()->GetFont("TimesFont").resource->m_GCfontTexture);
}

GCText::~GCText()
{
	delete m_pGeometry; 
	delete m_pMesh; 
	delete m_pMaterial;
}

void GCText::SetText(const char* text)
{}


void GCText::SetPosition(float x, float y)
{
	m_pos.m_x = x;
	m_pos.m_y = y;

	ComputeWorldMatrix();
}

void GCText::SetPosition(Vect2 pos)
{
	m_pos = pos;
	ComputeWorldMatrix();
}

void GCText::SetScale(float x, float y)
{
	m_scale.SetVector(x, y);
	ComputeWorldMatrix();
}

void GCText::SetSize(int size)
{
	m_size = size;
}

void GCText::ComputeWorldMatrix()
{
	m_worldMatrix = DirectX::XMMatrixScaling(m_width, m_height, 1.0f) * DirectX::XMMatrixTranslation(m_pos.m_x, m_pos.m_y, 0.0f);
}

#pragma endregion

Vect2& DrawableShape::GetPos(float ratioX, float ratioY)
{
	Vect2 pos = m_pos;

	pos.m_x += (m_width * m_scale.m_x) * ratioX;
	pos.m_y += (m_height * m_scale.m_y) * ratioY;

	return pos;
}
