#include "pch.h"
#include "GameManager.h"

#include "Entity.h"
#include "Debug.h"

#include "MyWindow.h"
#include "WindowSFML.h"
#include "WindowRender.h"

#include "InputManager.h"

#include "AssetManager.h"
#include <string>

#define FIXED_DT 0.01667f

GameManager::GameManager()
{
	m_pInputSystem = new GCInputSystem();
	m_pWindow = nullptr;
	mDeltaTime = 0.0f;
	m_pActiveScene = nullptr;
	m_changeActiveScene = false;
	m_pNewActiveScene = nullptr;
}

GameManager* GameManager::Get()
{
	static GameManager mInstance;

	return &mInstance;
}

GameManager::~GameManager()
{
	delete m_pWindow;

	for (Scene* scene : m_sceneList)
	{
		delete scene;
	}
	m_sceneList.clear();

	delete m_pInputSystem;
}

void GameManager::CreateWindowSFML(unsigned int width, unsigned int height, const char* title, int fpsLimit)
{
	m_pWindow = new WindowSFML(width, height, title);
	m_pWindow->SetFramerateLimit(fpsLimit);
	AssetManager::Get()->SetType(AssetManager::AssetType::SFML);

	AssetManager::Get()->LoadFont("Hack-Regular.ttf");
}

void GameManager::CreateWindowRender(HINSTANCE hInstance, unsigned int width, unsigned int height, std::wstring title, int fpsLimit)
{
	m_pWindow = new WindowRender(hInstance, width, height, title);
	m_pWindow->SetFramerateLimit(fpsLimit);
	AssetManager::SetType(AssetManager::AssetType::GCRENDER);

	//_ASSERT(m_pWindow == nullptr);
	AssetManager::Get()->LoadFont("TimesFont");
}

void GameManager::SetActiveScene(Scene* pScene)
{
	m_changeActiveScene = true;
	m_pNewActiveScene = pScene;
}


void GameManager::Run()
{
	if (m_pWindow == nullptr)
	{
		std::cout << "Window not created, creating SFML default window" << std::endl;
		CreateWindowSFML(1280, 720, "Default window");
	}

	_ASSERT(m_pActiveScene != nullptr);

	sf::Clock clock;
	while (m_pWindow->IsOpen())
	{
		SetDeltaTime(clock.restart().asSeconds());
		
		if (m_onPause)
		{
			GameManager::Get()->mDeltaTime = 0.f;
			m_accumulatedTime = 0.f;
		}

		m_accumulatedTime += GameManager::Get()->GetDeltaTime();

		HandleInput();

		Update();

		FixedUpdate();
		
		Draw();
	}

	m_pWindow->Close();

}

void GameManager::HandleInput()
{
	m_pInputSystem->Update(m_pWindow);
	
	m_pActiveScene->OnEvent(m_pInputSystem);

	if (m_pInputSystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::Z) && m_pInputSystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::Q) && m_pInputSystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::S) && m_pInputSystem->m_pKeyboard->GetKeyStay(GCKEYBOARD::D))
		m_pActiveScene->m_getCaowed = true;

}

void GameManager::Update()
{
	if (m_changeActiveScene)
	{
		m_pActiveScene = m_pNewActiveScene;
		m_pNewActiveScene = nullptr;
		m_changeActiveScene = false;
	}

	m_pWindow->Update();

	m_pActiveScene->Update();
}

void GameManager::FixedUpdate()
{
	while (m_accumulatedTime > FIXED_DT)
	{
		m_pActiveScene->FixedUpdate();
		m_accumulatedTime -= FIXED_DT;
	}
}

void GameManager::Draw()
{
	m_pActiveScene->Draw(m_pWindow);
}
