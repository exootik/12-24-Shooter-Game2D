#pragma once
#include "Entity.h"

class Button : public Entity
{
public:
	Button(float width, float height, int layer, const Color& color, bool hasCollision, Scene* pScene);
	Button(float width, float height, int layer, Scene* pScene);

	void OnUpdate() override;
	void DrawText(const char* text, const char* textButton, float x, float y);

	void SetTypeOfButton(int type) { m_typeOfButton = type; }
	int GetTypeOfButton() { return m_typeOfButton; }

private:
	int m_typeOfButton;
};

