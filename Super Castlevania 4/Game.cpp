#include "pch.h"
#include "Game.h"
#include "LevelManager.h"
#include "TextureManager.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "Camera.h"
#include "Pendulum.h"
#include <iostream>

Game::Game(const Window& window)
	: m_Window{ window }
	, m_pLevelManager{ new LevelManager() }
	, m_pPlayer{ new Player(m_pLevelManager) }
	, m_pCamera{ new Camera(window.width, window.height) }
	, m_pProjectileManager{ new ProjectileManager() }
	, m_pPendulum{ new Pendulum(window.width / 2, window.height / 2) }
{
	Initialize();
	DisplayInstructions();
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
	delete m_pPendulum;
	m_pPlayer = nullptr;
	m_pCamera = nullptr;
	m_pLevelManager = nullptr;
	m_pProjectileManager = nullptr;
	m_pPendulum = nullptr;
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
	m_pPendulum->Update(elapsedSec);
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
	m_pPendulum->Draw();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_SPACE && e.repeat == 0)
	{
		m_pPlayer->Jump();
		m_pPendulum->ReleasePendulum();
	}
	if ((e.keysym.sym == SDLK_w || e.keysym.sym == SDLK_UP) && e.repeat == 0)
		m_pPlayer->AttemptInteraction();
	if ((e.keysym.sym == SDLK_q) && e.repeat == 0)
		m_pPlayer->Attack();
	if ((e.keysym.sym == SDLK_e) && e.repeat == 0)
		m_pProjectileManager->AddProjectile(m_pPlayer->Shoot(), m_pPlayer->GetShape().GetCenter(), true, m_pPlayer->IsFlipped());
	if ((e.keysym.sym == SDLK_r) && e.repeat == 0)
		m_pPendulum->ResetPendulum();
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

void Game::DisplayInstructions()
{
	std::cout << "Arrow left/right or A/D keys to move.\n";
	std::cout << "Arrow down or S key to crouch.\n";
	std::cout << "Arrow up or W key to interact with stairs or doors.\n";
	std::cout << "Space bar to jump.\n";
	std::cout << "Q to whip attack (Sprite not implemented).\n";
	std::cout << "E to throw an axe.\n";
	std::cout << "O to enable debug overlay.\n\n";
	std::cout << "Overlay explanation:\n";
	std::cout << "\tPlayer:\n";
	std::cout << "\t\tMagenta rectangle: hitbox\n";
	std::cout << "\t\tRed dots: Horizontal collision anchors.\n";
	std::cout << "\t\tGreen dots and central red dot: Vertical collision anchors.\n";
	std::cout << "\t\tYellow dot: Stair climb anchor.\n";
	std::cout << "\t\tWhite dot: Translation anchor.\n";
	std::cout << "\tTerrain:\n";
	std::cout << "\t\tWhite lines: Terrain object outline.\n";
	std::cout << "\t\tRed dot: Translation anchor.\n";
	std::cout << "\tStairs:\n";
	std::cout << "\t\tCyan rectangle: stairs surface and interaction range.\n";
	std::cout << "\t\tRed dot: Mount point without automount.\n";
	std::cout << "\t\tGreen dot: Mount point with automount.\n";
	std::cout << "\tDoors:\n";
	std::cout << "\t\tGreen rectangle: interaction hitbox.\n";
}
