#pragma once
#include "Sprite.h"
#include <DirectXMath.h>
class Entity;
class GCGeometry;
class GCMesh;
class GCMaterial;
class GCGraphics;
class WindowRender;

class SpriteRender : public Sprite
{
public:
	SpriteRender(GCGraphics* pGraphics);
	~SpriteRender() {};
	bool SetTexture(const char* textureName);
	void Draw(MyWindow* pWindow);
	void Update(Entity* pEntity);
	void SetScale(Vect2 scale) {}

	Sprite* Duplicate() override { return this; }
	void ResizeTexture(Frames* pFrame) override;

private:

	GCGeometry* m_pGeometry;
	GCMesh* m_pMesh;
	GCMaterial* m_pMaterial;

	GCGraphics* m_pGraphics;

	DirectX::XMMATRIX m_worldMatrix;

	friend WindowRender;
};

