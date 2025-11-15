#pragma once

#include <list>
#include <vector>
#include <string>

#include "DirectXMath.h"


struct HINSTANCE__;
typedef struct HINSTANCE__* HINSTANCE;

class GCInputSystem;
class MyWindow;
class Entity;
class Scene;
class Debug;



class GameManager
{

	MyWindow* m_pWindow;

	Scene* m_pActiveScene;

	std::list<Scene*> m_sceneList;

	float mDeltaTime;

	GCInputSystem* m_pInputSystem;

	bool m_changeActiveScene;
	Scene* m_pNewActiveScene;

	float m_accumulatedTime;

	bool m_onPause = false;


private:
	GameManager();

	void Run();
	
	void HandleInput();
	void Update();
	void FixedUpdate();
	void Draw();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }


public:
	~GameManager();
	static GameManager* Get();

	void CreateWindowSFML(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60);
	void CreateWindowRender(HINSTANCE hInstance, unsigned int width, unsigned int height, std::wstring title, int fpsLimit = 60);
	MyWindow* GetWindow() const { return m_pWindow; }

	template<typename T>
	void LaunchScene();

	float GetDeltaTime() const { return mDeltaTime; }
	Scene* GetActiveScene() const { return m_pActiveScene; }
	GCInputSystem* GetInputSystem() { return m_pInputSystem; };

	void PauseGame(bool state) { m_onPause = state; }

	template<typename T>
	T* CreateScene();

	void SetActiveScene(Scene* pScene);

	friend Debug;
	friend Scene;
};

#include "GameManager.inl"