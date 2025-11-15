
#include <iostream>

#include "GameManager.h"
#include "GameScene.h"

#define NOMINMAX
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindowSFML(1920, 1080, "Shoot Em Up");

	pInstance->LaunchScene<GameScene>();

	return 0;
}
#pragma endregion