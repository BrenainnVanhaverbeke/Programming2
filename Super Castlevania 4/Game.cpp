#include "pch.h"
#include "Game.h"
#include "LevelManager.h"
#include "TextureManager.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Camera.h"
#include "UI.h"
#include "utils.h"
#include <iostream>

Game::Game(const Window& window)
	: m_Window{ window }
	, m_pLevelManager{ new LevelManager(window.width, window.height) }
	, m_pPlayer{ new Player(m_pLevelManager) }
	, m_pCamera{ new Camera(window.width, window.height) }
	, m_pProjectileManager{ new ProjectileManager() }
	, m_pEnemyManager{ new EnemyManager() }
	, m_IsDrawDebugEnabled{ false }
	, m_pUI{ new UI(m_pPlayer, window) }
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
	m_pProjectileManager->SetBoundaries(Rectf{ 0, 0, m_Window.width / G_SCALEFACTOR, m_Window.height / G_SCALEFACTOR });
}

void Game::Cleanup()
{
	delete m_pPlayer;
	delete m_pCamera;
	delete m_pLevelManager;
	delete m_pProjectileManager;
	delete m_pEnemyManager;
	delete m_pUI;
	m_pPlayer = nullptr;
	m_pCamera = nullptr;
	m_pLevelManager = nullptr;
	m_pProjectileManager = nullptr;
	m_pEnemyManager = nullptr;
	m_pUI = nullptr;
}

void Game::Update(float elapsedSec)
{
	const Point2f& cameraBottomLeft{ m_pCamera->Track(m_pPlayer->GetShape()) };
	m_pPlayer->Update(elapsedSec);
	m_pLevelManager->Update(elapsedSec, cameraBottomLeft);
	m_pEnemyManager->Update(elapsedSec, m_pPlayer);
	m_pProjectileManager->Update(elapsedSec, cameraBottomLeft);
	m_pLevelManager->CheckOverlap(m_pPlayer->GetShape(), m_pPlayer->GetZIndex());
	m_pProjectileManager->CheckOverlap(m_pEnemyManager->GetEnemies(), m_pPlayer);
	if (m_pPlayer->IsAttacking())
		m_pEnemyManager->HandleAttack(m_pPlayer->GetWeaponShape(), m_pPlayer->GetWeaponDamage(), m_pPlayer->GetZIndex());
	if (m_pLevelManager->IsInTransitionArea(m_pPlayer->GetShape()))
	{
		m_pLevelManager->NextSegment();
		m_pPlayer->Relocate(m_pLevelManager->GetSpawn());
		m_pCamera->SetLevelBoundaries(m_pLevelManager->GetBoundaries());
	}
	m_pUI->Update();
}

void Game::Draw() const
{
	ClearBackground();
	glPushMatrix();
	{
		m_pCamera->Transform();
		for (int i{ -5 }; i < 5; ++i)
		{
			m_pLevelManager->Draw(i);
			m_pPlayer->Draw(i);
			m_pProjectileManager->Draw(i);
			m_pEnemyManager->Draw(i);
			if (m_IsDrawDebugEnabled)
			{
				m_pLevelManager->DrawDebug(i);
				m_pPlayer->DrawDebug(i);
				m_pProjectileManager->DrawDebug(i);
				m_pEnemyManager->DrawDebug(i);
			}
		}
	}
	glPopMatrix();
	m_pUI->Draw();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_SPACE && e.repeat == 0)
		m_pPlayer->Jump();
	if ((e.keysym.sym == SDLK_w || e.keysym.sym == SDLK_UP) && e.repeat == 0)
		m_pPlayer->AttemptInteraction();
	if ((e.keysym.sym == SDLK_j) && e.repeat == 0)
		m_pPlayer->Attack();
	if ((e.keysym.sym == SDLK_k) && e.repeat == 0)
		m_pProjectileManager->AddProjectile(m_pPlayer->Shoot(), m_pPlayer->GetShape().GetCenter(), true, m_pPlayer->IsFlipped(), m_pPlayer->GetZIndex());
	if ((e.keysym.sym == SDLK_i) && e.repeat == 0)
		m_pPlayer->CycleProjectileType();
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_o)
		m_IsDrawDebugEnabled = !m_IsDrawDebugEnabled;
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
	std::cout << "J to whip attack.\n";
	std::cout << "K to use a thrown weapon.\n";
	std::cout << "I to cycle thrown weapons.\n";
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
