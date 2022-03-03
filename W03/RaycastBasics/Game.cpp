#include "pch.h"
#include "Game.h"
#include <iostream>

Game::Game(const Window& window)
	:m_Window{ window }, m_Center{ Point2f{m_Window.width / 2, m_Window.height / 2} }
{
	Initialize();
	InitialisePoints();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	InitialisePoints();
}

void Game::InitialisePoints()
{
	InitialisePolygon();
	m_MousePoint = Point2f{ 10.0f, 10.0f };
}

void Game::InitialisePolygon()
{
	const float verticalBorder{ 50.0f };
	const float horizontalBorder{ 120.0f };
	m_Points.push_back(Point2f{ m_Window.width / 2, verticalBorder });
	m_Points.push_back(Point2f{ m_Window.width - horizontalBorder, verticalBorder * 2 });
	m_Points.push_back(Point2f{ m_Window.width - horizontalBorder, m_Window.height - verticalBorder * 4 });
	m_Points.push_back(Point2f{ m_Window.width / 2, m_Window.height - verticalBorder });
	m_Points.push_back(Point2f{ horizontalBorder, (m_Window.height - verticalBorder * 4) });
	m_Points.push_back(Point2f{ horizontalBorder, verticalBorder * 2 });
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
	CheckRaycast();
}

void Game::Draw() const
{
	ClearBackground();
	DrawPolygon();
	DrawRay();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	m_MousePoint = Point2f{ (float)e.x, (float)e.y };
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

void Game::DrawPolygon() const
{
	const Color4f polygonFill{ 0.0f, 0.0f, 0.0f, 1.0f };
	const Color4f polygonBorder{ 1.0f, 0.3f, 0.0f, 1.0f };
	utils::SetColor(polygonFill);
	utils::FillPolygon(m_Points);
	utils::SetColor(polygonBorder);
	utils::DrawPolygon(m_Points);
}

void Game::DrawRay() const
{
	const Color4f rayColour{ 1.0f, 1.0f, 0.0f, 1.0f };
	utils::SetColor(rayColour);
	utils::DrawLine(m_Center, m_MousePoint);
	if (m_RayIsIntersecting)
	{
		DrawIntersection();
		DrawNormal();
		DrawReflection();
	}
}

void Game::DrawIntersection() const
{
	const float intersectRadius{ 5.0f };
	const Color4f intersectColour{ 1.0f, 1.0f, 1.0f, 1.0f };
	utils::SetColor(intersectColour);
	utils::FillEllipse(m_RayHitInfo.intersectPoint, intersectRadius, intersectRadius);
}

void Game::DrawNormal() const
{
	const float normalLength{ 30.0f };
	const Color4f normalColour{ 0.0f, 1.0f, 0.0f, 1.0f };
	const Point2f normalPoint{ m_RayHitInfo.intersectPoint + (m_RayHitInfo.normal * normalLength) };
	utils::SetColor(normalColour);
	utils::DrawLine(m_RayHitInfo.intersectPoint, normalPoint);
}

void Game::DrawReflection() const
{
	const Color4f reflectionColour{ 1.0f, 1.0f, 1.0f, 1.0f };
	const Vector2f ray{ m_Center, m_MousePoint };
	const Vector2f reflection{ Vector2f{m_Center, m_RayHitInfo.intersectPoint}.Reflect(m_RayHitInfo.normal).Normalized() };
	const float lengthAfterIntersect{ ray.Length() * (1 - m_RayHitInfo.lambda)};
	utils::SetColor(reflectionColour);
	utils::DrawLine(m_RayHitInfo.intersectPoint, m_RayHitInfo.intersectPoint + (reflection * lengthAfterIntersect));
}

void Game::CheckRaycast()
{
	m_RayIsIntersecting = utils::Raycast(m_Points, m_Center, m_MousePoint, m_RayHitInfo);
}