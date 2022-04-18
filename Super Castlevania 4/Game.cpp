#include "pch.h"
#include "Game.h"
#include "LevelManager.h"
#include "TextureManager.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "Camera.h"
#include <iostream>

Game::Game(const Window& window)
	: m_Window{ window }
	, m_pLevelManager{ new LevelManager() }
	, m_pPlayer{ new Player(m_pLevelManager) }
	, m_pCamera{ new Camera(window.width, window.height) }
	, m_pProjectileManager{ new ProjectileManager() }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
	TextureManager& instance{ TextureManager::GetInstance() };
	instance.DeleteTextureManager();
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
	delete m_pProjectileManager;
	m_pPlayer = nullptr;
	m_pCamera = nullptr;
	m_pLevelManager = nullptr;
	m_pProjectileManager = nullptr;
}

void Game::Update(float elapsedSec)
{
	m_pPlayer->Update(elapsedSec);
	m_pLevelManager->Update(elapsedSec);
	m_pLevelManager->CheckOverlap(m_pPlayer->GetShape());
	m_pProjectileManager->Update(elapsedSec);
	if (m_pLevelManager->IsInTransitionArea(m_pPlayer->GetShape()))
	{
		m_pLevelManager->NextSegment();
		m_pPlayer->Relocate(m_pLevelManager->GetSpawn());
		m_pCamera->SetLevelBoundaries(m_pLevelManager->GetBoundaries());
	}
}

void Game::Draw() const
{
	bool isOnBackground{ m_pLevelManager->IsOnBackground() };
	ClearBackground();
	glPushMatrix();
	{
		m_pCamera->Transform(m_pPlayer->GetShape());
		if (!isOnBackground)
			m_pLevelManager->Draw();
		m_pPlayer->Draw();
		if (isOnBackground)
			m_pLevelManager->Draw();
		m_pProjectileManager->Draw();
	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_SPACE && e.repeat == 0)
		m_pPlayer->Jump();
	if ((e.keysym.sym == SDLK_w || e.keysym.sym == SDLK_UP) && e.repeat == 0)
		m_pPlayer->AttemptInteraction();
	if ((e.keysym.sym == SDLK_q) && e.repeat == 0)
		m_pPlayer->Attack();
	if ((e.keysym.sym == SDLK_e) && e.repeat == 0)
		m_pProjectileManager->AddProjectile(m_pPlayer->Shoot(), m_pPlayer->GetShape().GetCenter(), true, m_pPlayer->IsFlipped());
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_o)
	{
		m_pLevelManager->ToggleDebugDraw();
		m_pPlayer->ToggleDrawDebug();
		m_pProjectileManager->ToggleDrawDebug();
	}
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