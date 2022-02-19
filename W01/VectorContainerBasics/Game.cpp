#include "pch.h"
#include "Game.h"
#include "utils.h"
#include "Card.h"

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
	InitialiseCards();
}

void Game::Cleanup()
{
	for (Card* card : m_CardVector)
	{
		delete card;
		card = nullptr;
	}
}

void Game::Update(float elapsedSec)
{
}

void Game::Draw() const
{
	ClearBackground();
	const float scale{ 0.45f };
	const float width{ m_CardVector[0]->GetWidth() * scale };
	const float height{ m_CardVector[0]->GetHeight() * scale };
	Rectf destination{ 0, 0, width, height };
	for (size_t card = 0; card < m_CardVector.size(); card++)
	{
		Index2i indeces{ utils::Get2DIndexFromLinear((int)card, Card::m_MaxRank) };
		destination.left = width * indeces.column;
		destination.bottom = height * indeces.row;
		m_CardVector[card]->Draw(destination);
	}
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_EQUALS:
		m_NumbersVector.push_back(utils::GetRandomNumber(0, 30));
		PrintVector(m_NumbersVector);
		break;
	case SDLK_MINUS:
		if (0 < m_NumbersVector.size())
		{
			m_NumbersVector.pop_back();
			PrintVector(m_NumbersVector);
		}
		else
			std::cout << "Vector is empty." << std::endl;
		break;
	case SDLK_UP:
		ModifyVector(m_NumbersVector, 1);
		PrintVector(m_NumbersVector);
		break;
	case SDLK_DOWN:
		ModifyVector(m_NumbersVector, -1);
		PrintVector(m_NumbersVector);
		break;
	case SDLK_s:
		ShuffleCards();
		break;
	default:
		break;
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

void Game::InitialiseCards()
{
	for (int suit{ 0 }; suit < (int)Card::Suit::spades; suit++)
	{
		for (int card{ 0 }; card < Card::m_MaxRank; card++)
		{
			m_CardVector.push_back(new Card(Card::Suit(suit + 1), card + 1));
		}
	}
}

void Game::PrintVector(std::vector<int>& vector)
{
	//PrintVectorIndexed(vector);
	PrintVectorRanged(vector);
}

void Game::PrintVectorIndexed(std::vector<int>& vector)
{
	for (size_t i{ 0 }; i < vector.size(); i++)
	{
		std::cout << vector[i] << " ";
	}
	std::cout << std::endl;
}

void Game::PrintVectorRanged(std::vector<int>& vector)
{
	for (int i : vector)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

void Game::ModifyVector(std::vector<int>& vector, int amount)
{
	for (size_t i{ 0 }; i < vector.size(); i++)
	{
		vector[i] += amount;
	}
}

void Game::ShuffleCards()
{
	for (size_t i = 0; i < m_CardVector.size(); i++)
	{
		int swapIndex{ -1 };
		do
		{
			swapIndex = utils::GetRandomNumber(0, (int)m_CardVector.size(), false);
		} while (swapIndex == (int)i);
		Card* temp = m_CardVector[i];
		m_CardVector[i] = m_CardVector[swapIndex];
		m_CardVector[swapIndex] = temp;
	}
}