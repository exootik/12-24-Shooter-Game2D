#pragma once

#include "MyWindow.h"
#include <list>
#include "Render.h"
#include <string>

class Debug;
struct LineShape;


struct HINSTANCE__;
typedef struct HINSTANCE__* HINSTANCE;

struct Plane
{
	GCGeometry* m_pGeometry;
	GCMesh* m_pMesh; 
	GCMaterial* m_pMaterial;
};


struct Camera {

	DirectX::XMFLOAT3 cameraPosition = DirectX::XMFLOAT3(0.f, 0.f, -10.f);
	DirectX::XMFLOAT3 cameraTarget = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	DirectX::XMFLOAT3 cameraUp = DirectX::XMFLOAT3(0.f, 1.f, 0.f);

	float viewWidth = 1920.f;
	float viewHeight = 1080.f;
	float nearZ = 1.f;
	float farZ = 1000.f;

	DirectX::XMMATRIX storedProjectionMatrix, storedViewMatrix;
};

class WindowRender : public MyWindow
{
public: 
	WindowRender(HINSTANCE hInstance, unsigned int width, unsigned int height, std::wstring title);
	~WindowRender() {};

	void Draw(std::vector<std::list<Entity*>> entities) override;
	void SetFramerateLimit(int fps) {};

	void Update();
	void Close() {}

	Sprite* CreateSprite(const char* texturename);
	Sprite* CreateSpriteWithAtlas(const char* atlasName, const char* assetName);

	RectShape* CreateRectShape(const Color& color) { return new GCRect(m_pGraphics, color); }
	CircleShape* CreateCircleShape(const Color& color) { return new GCCircle(m_pGraphics, color); }
	TextShape* CreateText(const Color& color, const char* text) { return new GCText(m_pGraphics, color, text); }

protected:
	void Draw(TextShape* pText) {};
	void Draw(CircleShape* pCircle) {};
	void Draw(RectShape* pRect);

	friend class Debug;
protected: 
	Window* m_pWindow;
	GCGraphics* m_pGraphics;

	Camera m_camera;
};

