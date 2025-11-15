#include "pch.h"
#include "SpriteRender.h"
#include "AssetManager.h"
#include "DirectXMath.h"

#include "Entity.h"

SpriteRender::SpriteRender(GCGraphics* pGraphics) : m_pGraphics(pGraphics)
{
	m_pGeometry = m_pGraphics->CreateGeometryPrimitive(Plane, DirectX::XMFLOAT4(255, 255, 255, 255)).resource;

	m_pGraphics->InitializeGraphicsResourcesStart();
	m_pMesh = m_pGraphics->CreateMeshTexture(m_pGeometry).resource;
	m_pGraphics->InitializeGraphicsResourcesEnd();

}

bool SpriteRender::SetTexture(const char* textureName)
{
	SetTextureName(textureName);
	m_pMaterial = m_pGraphics->CreateMaterial(m_pGraphics->CreateShaderTexture().resource).resource;
	if (AssetManager::Get()->GetTexture(textureName).success)
	{
		GCTexture* ptext = AssetManager::Get()->GetTexture(textureName).resource->m_pGCTexture;
		m_pMaterial->SetTexture(ptext);
		m_textWidth = ptext->GetWidth();
		m_textHeight = ptext->GetHeight();
		m_spriteWidth = m_textWidth; m_spriteHeight = m_textHeight;
		m_worldMatrix = DirectX::XMMatrixScaling(m_spriteWidth, m_spriteHeight, 1.0f) * DirectX::XMMatrixTranslation(0.f, 0.f, 0.0f);
		return true;
	}
	std::cout << "Texture Not Loaded";
	return false;
}

void SpriteRender::Draw(MyWindow* pWindow)
{
	m_pGraphics->UpdateWorldConstantBuffer(m_pMaterial, m_worldMatrix);
	m_pGraphics->GetRender()->DrawObject(m_pMesh, m_pMaterial, true);
}

void SpriteRender::Update(Entity* pEntity)
{
	m_worldMatrix = DirectX::XMMatrixScaling(m_spriteWidth * pEntity->GetScale().m_x, m_spriteHeight * pEntity->GetScale().m_y, 1.0f) * DirectX::XMMatrixTranslation(pEntity->GetPosition().m_x, pEntity->GetPosition().m_y, 0.0f);
}

void SpriteRender::ResizeTexture(Frames* pFrame)
{
	m_pGeometry->uv.resize(4);
	for (int i = 0; i < 4; i++) {
		m_pGeometry->uv[i] = pFrame->uvsPos[i].ToXMFLOAT2();
	}
	m_spriteWidth = pFrame->m_width;
	m_spriteHeight = pFrame->m_height;
}
