#include "pch.h"
#include "Game.h"
#include "Player.h"
#include "Camera.h"
#include "LevelManager.h"
#include "TextureManager.h"

Game::Game(const Window& window)
	: m_Window{ window }
	, m_pLevelManager{ new LevelManager() }
	, m_pPlayer{ new Player(m_pLevelManager) }
	, m_pCamera{ new Camera(window.width, window.height) }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
	TextureManager* test{ TextureManager::GetInstance() };
	test->Delete();
}

void Game::Initialize()
{
	m_pCamera->SetLevelBoundaries(m_pLevelManager->GetBoundaries());
}

void Game::Cleanup()
{
	delete m_pPlayer;
	delete m_pCamera;
	delete m_pLevelManager;
	m_pPlayer = nullptr;
	m_pCamera = nullptr;
	m_pLevelManager = nullptr;
}

void Game::Update(float elapsedSec)
{
	m_pPlayer->Update(elapsedSec);
	m_pLevelManager->Update(elapsedSec, m_pPlayer->GetShape());
	m_pLevelManager->CheckOverlap(m_pPlayer->GetShape());
	if (m_pLevelManager->IsInTransitionArea(m_pPlayer->GetShape()))
	{
		m_pLevelManager->NextSegment();
		m_pPlayer->Relocate(m_pLevelManager->GetSpawn());
		m_pCamera->SetLevelBoundaries(m_pLevelManager->GetBoundaries());
	}
}

void Game::Draw() const
{
	ClearBackground();
	glPushMatrix();
	{
		m_pCamera->Transform(m_pPlayer->GetShape());
		m_pLevelManager->Draw();
		m_pPlayer->Draw();
	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_SPACE)
		m_pPlayer->Jump();
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_w || e.keysym.sym == SDLK_UP)
		m_pPlayer->AttemptInteraction();
	if (e.keysym.sym == SDLK_o)
		m_pLevelManager->ToggleDebugDraw();
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
