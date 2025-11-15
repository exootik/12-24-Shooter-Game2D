#include "pch.h"
#include "WindowRender.h"
#include "AssetManager.h"

#include "SpriteRender.h"
#include "Entity.h"

#include "Debug.h"

WindowRender::WindowRender(HINSTANCE hInstance, unsigned int width, unsigned int height, std::wstring title) : 
	MyWindow(width, height), m_pWindow(new Window(hInstance)), m_pGraphics(new GCGraphics())
{

	m_pWindow->Initialize(title);

	m_pGraphics->Initialize(m_pWindow, width, height);
	m_pGraphics->GetRender()->Set2DMode();
	AssetManager::Get()->SetGCGraphics(m_pGraphics);

	m_pGraphics->CreateViewProjConstantBuffer(m_camera.cameraPosition, m_camera.cameraTarget, m_camera.cameraUp, 0.f, 0.f, m_camera.nearZ, m_camera.farZ,m_camera.viewWidth, m_camera.viewHeight, ORTHOGRAPHIC, m_camera.storedProjectionMatrix, m_camera.storedViewMatrix);
}

void WindowRender::Draw(std::vector<std::list<Entity*>> entities)
{
	m_pGraphics->StartFrame();
	m_pGraphics->UpdateViewProjConstantBuffer(m_camera.storedProjectionMatrix, m_camera.storedViewMatrix);
	for (int i = 0; i < entities.size() ; i++ )
		for (Entity* pEntity : entities[i])
		{
			if (pEntity->GetSprite() != nullptr)
				pEntity->GetSprite()->Draw(this);
			else if (pEntity->GetRect() != nullptr)
				Draw(pEntity->GetRect());
			else
				std::cout << "Entity " << pEntity->GetName() << " Don't Have Sprite or Shape" << std::endl;

			if (pEntity->m_isColliderDisplay)
				pEntity->DrawCollider(this);
			pEntity->OnDraw(this);
		}
	Debug::Get()->Draw(this);

	m_pGraphics->EndFrame();
}

void WindowRender::Update()
{
	m_isOpen = m_pWindow->Run();
}

Sprite* WindowRender::CreateSprite(const char* texturename)
{
	Sprite* newSprite = new SpriteRender(m_pGraphics);
	newSprite->SetTexture(texturename);
	return newSprite;
}

Sprite* WindowRender::CreateSpriteWithAtlas(const char* atlasName, const char* assetName)
{
	Sprite* sprite = new SpriteRender(m_pGraphics);
	sprite->SetTexture(atlasName);
	sprite->ResizeTexture(AssetManager::GetAtlasAsset(atlasName, assetName).resource);
	return sprite;
}

void WindowRender::Draw(RectShape* rect)
{
	GCRect gcRect = *dynamic_cast<GCRect*>(rect);
	m_pGraphics->UpdateWorldConstantBuffer(gcRect.m_pMaterial, gcRect.m_worldMatrix);
	m_pGraphics->GetRender()->DrawObject(gcRect.m_pMesh, gcRect.m_pMaterial, true);
}

