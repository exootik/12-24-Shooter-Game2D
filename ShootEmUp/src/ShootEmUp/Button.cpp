#include "Button.h"
#include "GameScene.h"
#include "Debug.h"

Button::Button(float width, float height, int layer, const Color& color, bool hasCollision, Scene* pScene) : Entity(width, height, layer, hasCollision, color, pScene) {}

Button::Button(float width, float height, int layer, Scene* pScene) : Entity(width, height, layer, true, Color::Red , pScene) {}

void Button::OnUpdate()
{
	if (GetTypeOfButton() == 1)
	{
		DrawText("   Shoot Em Up  ", "    Commencer   ", GetPosition().m_x, GetPosition().m_y);
	}
	if (GetTypeOfButton() == 2)
	{
		DrawText("      Pause     ", "    Continuer   ", GetPosition().m_x, GetPosition().m_y);
	}
	if (GetTypeOfButton() == 3)
	{
		DrawText(" Vous avez perdu", "   Recommencer  ", GetPosition().m_x, GetPosition().m_y);
	}
	if (GetTypeOfButton() == 4)
	{
		DrawText("Vous avez gagné", "     Rejouer    ", GetPosition().m_x, GetPosition().m_y);
	}
}
void Button::DrawText(const char* text, const char* textButton, float x, float y)
{
	Debug::Debug::CreateText(x - 150, y - 160 , text, Color::Purple);
	Debug::Debug::CreateText(x - 150, y - 20, textButton, Color::Purple);
}