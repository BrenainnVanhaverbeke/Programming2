#include "pch.h"
#include "Game.h"
#include "Ball.h"
#include "Texture.h"

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
	m_pBalls[0] = new Ball(Point2f{ 0.0f, 0.0f }, Vector2f{ 100.0f, 200.0f }, Color4f{ 1.0f, 0.9f, 0.8f, 1.0f }, 10.0f);
	m_pBalls[1] = new Ball(Point2f{ 40.0f, 160.0f }, Vector2f{ 500.0f, -200.0f }, Color4f{ 0.8f, 0.9f, 0.8f, 1.0f }, 10.0f);
	//m_pTextures[0] = new Texture()
}

void Game::Cleanup()
{
	delete m_pBalls[0];
	m_pBalls[0] = nullptr;
	delete m_pBalls[1];
	m_pBalls[1] = nullptr;
	delete m_pTextures[0];
	m_pTextures[0] = nullptr;
	delete m_pTextures[1];
	m_pTextures[1] = nullptr;
}

void Game::Update(float elapsedSec)
{
	Rectf activeArea{ 0.0f, 0.0f, m_Window.width, m_Window.height };
	m_pBalls[0]->Update(elapsedSec, activeArea);
	m_pBalls[1]->Update(elapsedSec, activeArea);
}

void Game::Draw() const
{
	ClearBackground();
	m_pBalls[0]->Draw();
	m_pBalls[1]->Draw();
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
