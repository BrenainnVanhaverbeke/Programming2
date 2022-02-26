// Brenainn Vanhaverbeke - 1 DAE GD 10

#include "pch.h"
#include "Game.h"
#include "Enemy.h"
#include "Avatar.h"

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
	InitialiseAvatar();
}

void Game::InitialiseEnemies()
{
	const int nrOfRows{ 4 };
	const int nrOfColumns{ m_NrOfEnemies / nrOfRows };
	const float border{ m_Window.width / m_NrOfEnemies };
	const float defaultSize{ ((m_Window.width - (border * nrOfColumns)) - border) / nrOfColumns };
	const float enemyOffset{ defaultSize + (border) };
	Point2f center{ border + (defaultSize / 2), m_Window.height - border - (defaultSize / 2) };
	for (int enemyIndex{ 0 }; enemyIndex < m_NrOfEnemies; ++enemyIndex)
	{
		if (enemyIndex != 0 && enemyIndex % (m_NrOfEnemies / nrOfRows) == 0)
		{
			center.x = border + (defaultSize / 2);
			center.y -= enemyOffset;
		}
		m_pEnemies[enemyIndex] = new Enemy(center, defaultSize, defaultSize);
		center.x += enemyOffset;
	}
	m_ActiveEnemies = m_NrOfEnemies;
}

void Game::InitialiseAvatar()
{
	const float avatarWidth{ (m_Window.width / m_NrOfEnemies) * 2 };
	const float avatarHeight{ avatarWidth * 1.5f };
	const Point2f avatarOrigin{ m_Window.width / 2, avatarHeight };
	const Rectf avatarBoundaries{ 0.0f, 0.0f, m_Window.width, m_Window.height };
	m_pAvatar = new Avatar(avatarOrigin, avatarWidth, avatarHeight);
	m_pAvatar->SetBoundaries(avatarBoundaries);
}

void Game::Cleanup()
{
	for (int enemyIndex{ 0 }; enemyIndex < m_ActiveEnemies; ++enemyIndex)
	{
		delete m_pEnemies[enemyIndex];
		m_pEnemies[enemyIndex] = nullptr;
	}
	delete m_pAvatar;
	m_pAvatar = nullptr;
}

void Game::Update(float elapsedSec)
{
	m_pAvatar->Update(elapsedSec, m_pEnemies, m_ActiveEnemies);
}

void Game::Draw() const
{
	ClearBackground();
	DrawEnemies();
	m_pAvatar->Draw();
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
	for (int enemyIndex{ 0 }; enemyIndex < m_ActiveEnemies; ++enemyIndex)
		m_pEnemies[enemyIndex]->Draw();
}
