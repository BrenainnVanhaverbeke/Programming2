// Brenainn Vanhaverbeke - 1 DAE GD 10

#include "pch.h"
#include "Game.h"
#include "Enemy.h"

Game::Game(const Window& window)
	:m_Window{ window }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	InitialiseEnemies();
}

void Game::InitialiseEnemies()
{
	const int nrOfEnemies{ 40 };
	const int nrOfRows{ 4 };
	const int nrOfColumns{ nrOfEnemies / nrOfRows };
	const float border{ m_Window.width / nrOfEnemies };
	const float defaultSize{ ((m_Window.width - (border * nrOfColumns)) - border) / nrOfColumns };
	const float enemyOffset{ defaultSize + (border) };
	Point2f center{ border + (defaultSize / 2), m_Window.height - border - (defaultSize / 2) };
	for (int enemy{ 0 }; enemy < nrOfEnemies; ++enemy)
	{
		if (enemy != 0 && enemy % (nrOfEnemies / nrOfRows) == 0)
		{
			center.x = border + (defaultSize / 2);
			center.y -= enemyOffset;
		}
		m_Enemies.push_back(new Enemy(center, defaultSize, defaultSize));
		center.x += enemyOffset;
	}
}

void Game::Cleanup()
{
	for (Enemy* enemy : m_Enemies)
	{
		delete enemy;
		enemy = nullptr;
	}
}

void Game::Update(float elapsedSec)
{
	//for (Enemy* enemy : m_Enemies)
	//	enemy->Update(elapsedSec);
}

void Game::Draw() const
{
	ClearBackground();
	DrawEnemies();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::DrawEnemies() const
{
	for (Enemy* enemy : m_Enemies)
		enemy->Draw();
}
