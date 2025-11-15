#pragma once

#include "GameManager.h"
#include "Scene.h"

template<typename T>
void GameManager::LaunchScene()
{
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	_ASSERT(m_pActiveScene == nullptr);

	T* newScene = new T();
	if (m_pActiveScene == nullptr)
		m_pActiveScene = newScene;

	newScene->SetGameManager(this);
	newScene->LoadAssets();
	newScene->OnInitialize();
	m_sceneList.push_back(newScene);

	Run();
}

template<typename T>
T* GameManager::CreateScene()
{
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	_ASSERT(m_pActiveScene == nullptr);

	T* newScene = new T();

	newScene->SetGameManager(this);
	newScene->LoadAssets();
	newScene->OnInitialize();
	m_sceneList.push_back(newScene);

	return newScene;
}
