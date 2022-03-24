#include "pch.h"
#include "Game.h"
#include "Container.h"
#include "GeneralUtils.h"
//#include "Texture.h"
#include <iostream>

//Texture Game::m_StatDaeTexture{ "./Resources/DAE.png" };

Game::Game(const Window& window)
	: m_Window{ window }
	, m_DaeTexture{ "./Resources/DAE.png" }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	TestContainer();
	//m_StatDaeTexture = m_StatDaeTexture;
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
}

void Game::Draw() const
{
	ClearBackground();
	//m_StatDaeTexture.Draw(Point2f{ 0.0f, 50.0f });
	//DrawTexture(m_DaeTexture, Point2f{ 0.0f, 50.0f }, 4, m_DaeTexture.GetWidth(), m_DaeTexture.GetHeight());
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
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

void Game::TestContainer()
{
	Container c1{};
	AddValues(c1, 3, 1, 10);
	Container c2{ c1 };
	c1[0] = 20;
	Container c3{ 3 };
	AddValues(c3, 3, 10, 20);
	c3 = c1;
	//c3 = 4;
	Container c4 = c1;
	c4 = c2;
	c4 = CreateMultiplied(c1, 2);
	AddValues(c4, 3, 20, 30);
}

void Game::AddValues(Container& c, int nr, int min, int max)
{
	for (int i{ 0 }; i < nr; ++i)
		c.PushBack(GeneralUtils::GetRandomNumber(min, max));
}

Container Game::CreateMultiplied(Container c, int factor)
{
	for (int idx{ 0 }; idx < c.Size(); ++idx)
	{
		c[idx] *= factor;
	}
	return c;
}

void Game::DrawTexture(Texture texture, const Point2f& pos, int nr, int dx, int dy) const
{
	for (int i{ 0 }; i < nr; ++i)
		texture.Draw(Point2f{ pos.x + i * dx, pos.y + i * dy });
}