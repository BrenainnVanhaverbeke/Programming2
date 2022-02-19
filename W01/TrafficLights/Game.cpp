#include "pch.h"
#include "Game.h"
#include "TrafficLight.h"
//#include "structs.h"
#include "utils.h"

Game::Game(const Window& window)
	:m_Window{ window }
{
	Initialize();
	InitialiseTrafficLights();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{

}

void Game::Cleanup()
{
	for (TrafficLight* trafficLight : m_TrafficLights)
	{
		delete trafficLight;
		trafficLight = nullptr;
	}
}

void Game::Update(float elapsedSec)
{
	for (TrafficLight* trafficLight : m_TrafficLights)
		trafficLight->Update(elapsedSec);
}

void Game::Draw() const
{
	ClearBackground();
	for (TrafficLight* trafficLight : m_TrafficLights)
		trafficLight->Draw();
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
	Point2f mousePosition{ (float)e.x, (float)e.y };
	for (TrafficLight* trafficLight : m_TrafficLights)
		trafficLight->DoHitTest(mousePosition);
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::InitialiseTrafficLights()
{
	const int amountOfLights{ 12 };
	const int amountOfRows{ 2 };
	const int amountOfColumns{ amountOfLights / amountOfRows };
	const float border{ 10.0f };
	float height = (m_Window.height - (border * (amountOfRows + 1))) / amountOfRows;
	float width = (m_Window.width - (border * ((amountOfLights / amountOfRows) + 1))) / amountOfColumns;
	for (int i = 0; i < amountOfLights; i++)
	{
		int column{ i % amountOfColumns };
		int row{ i / amountOfColumns };
		float x{ border + (width * column) + (border * column)};
		float y{ border + (height * row) + (border * row)};
		m_TrafficLights.push_back(new TrafficLight(Point2f{ x, y }, width, height));
	}
}
