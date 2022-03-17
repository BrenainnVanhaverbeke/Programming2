#include "pch.h"
#include "Game.h"
#include "Diamond.h"
#include "utils.h"

Game::Game(const Window& window)
	: m_Window{ window }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	InitialiseDiamonds();
}

void Game::InitialiseDiamonds()
{
	const int nrOfDiamonds{ 10 };
	Point2f location{};
	for (int i{ 0 }; i < nrOfDiamonds; ++i)
	{
		location.x = (float)utils::GetRandomNumber(0, (int)m_Window.width);
		location.y = (float)utils::GetRandomNumber(0, (int)m_Window.height);
		m_pDiamonds.push_back(new Diamond(location));
	}
}

void Game::Cleanup()
{
	for (Diamond* diamond : m_pDiamonds)
		delete diamond;
	m_pDiamonds.clear();
}

void Game::Update(float elapsedSec)
{
	for (Diamond* diamond : m_pDiamonds)
		diamond->Update(elapsedSec);
}

void Game::Draw() const
{
	ClearBackground();
	DrawDiamond();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_r)
	{
		for (Diamond* diamond : m_pDiamonds)
			diamond->Reset();
	}
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
	Point2f mousePosition{ (float)e.x, (float)e.y };
	for (Diamond* diamond : m_pDiamonds)
		diamond->IsClickInPolygon(mousePosition);
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::DrawDiamond() const
{
	for (Diamond* diamond : m_pDiamonds)
		diamond->Draw();
}
