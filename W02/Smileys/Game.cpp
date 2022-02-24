// Brenainn Vanhaverbeke - 1 DAE GD 10

#include "pch.h"
#include "Game.h"
#include "Smiley.h"
#include "utils.h"

Game::Game(const Window& window)
	:m_Window{ window }
{
	Initialize();
	float border{ 20.0f };
	m_SafeArea = Rectf{ border, border, m_Window.width - (border * 2), m_Window.height - (border * 2) };

}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	CreateSmileys();
}

void Game::Cleanup()
{
	DeleteSmileys();
}

void Game::Update(float elapsedSec)
{
	UpdateSmileys(elapsedSec);
}

void Game::Draw() const
{
	ClearBackground();
	DrawSmileys();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		IncreaseSmileysSpeed();
		break;
	case SDLK_DOWN:
		DecreaseSmileysSpeed();
		break;
	case SDLK_DELETE:
		DeleteSleepers();
		break;
	default:
		break;
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
	for (int smileyIndex{ 0 }; smileyIndex < m_MaxAmountOfSmileys; ++smileyIndex)
	{
		if (m_pSmileys[smileyIndex])
			m_pSmileys[smileyIndex]->HitTest(mousePosition);
	}
}

void Game::CreateSmileys()
{
	const float arbitraryOffset{ 50 };
	const float leftOrigin{ (m_Window.width - (arbitraryOffset * m_MaxAmountOfSmileys)) / 2 };
	for (int i{ 0 }; i < m_MaxAmountOfSmileys; ++i)
	{
		m_pSmileys[i] = new Smiley(Point2f{ leftOrigin + (arbitraryOffset * i), m_Window.height / 2 });
		std::cout << i << std::endl;
	}
}

void Game::DeleteSmileys()
{
	for (int i{ 0 }; i < Game::m_MaxAmountOfSmileys; ++i)
	{
		delete m_pSmileys[i];
		m_pSmileys[i] = nullptr;
	}
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::UpdateSmileys(float elapsedSec)
{
	const float border{ 30.0f };
	Rectf boundingRect{ 0, 0, m_Window.width, m_Window.height };
	int highestSmileyIndex{ 0 };
	float highestPoint{ 0.0f };
	for (int i{ 0 }; i < m_MaxAmountOfSmileys; ++i)
	{
		Smiley* currentSmiley{ m_pSmileys[i] };
		if (currentSmiley)
		{
			currentSmiley->SetHighest(false);
			if (!currentSmiley->IsSleeping())
			{
				currentSmiley->Update(elapsedSec, boundingRect, m_SafeArea);
				if (highestPoint < m_pSmileys[i]->GetPosition().y)
				{
					highestPoint = m_pSmileys[i]->GetPosition().y;
					highestSmileyIndex = i;
				}
			}
		}
	}
	m_pSmileys[highestSmileyIndex]->SetHighest(true);
}

void Game::IncreaseSmileysSpeed()
{
	for (int smileyIndex{ 0 }; smileyIndex < m_MaxAmountOfSmileys; ++smileyIndex)
	{
		if (m_pSmileys[smileyIndex])
			m_pSmileys[smileyIndex]->IncreaseSpeed();
	}
}

void Game::DecreaseSmileysSpeed()
{
	for (int smileyIndex{ 0 }; smileyIndex < m_MaxAmountOfSmileys; ++smileyIndex)
	{
		if (m_pSmileys[smileyIndex])
			m_pSmileys[smileyIndex]->DecreaseSpeed();
	}
}

void Game::DeleteSleepers()
{
	for (int smileyIndex{ 0 }; smileyIndex < m_MaxAmountOfSmileys; ++smileyIndex)
	{
		if (m_pSmileys[smileyIndex] && m_pSmileys[smileyIndex]->IsSleeping())
		{
			delete m_pSmileys[smileyIndex];
			m_pSmileys[smileyIndex] = nullptr;
		}
	}
}

void Game::DrawSmileys() const
{
	for (int i{ 0 }; i < m_MaxAmountOfSmileys; ++i)
	{
		if (m_pSmileys[i])
			m_pSmileys[i]->Draw();
	}
}
