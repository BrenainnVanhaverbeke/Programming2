#include "pch.h"
#include "Level.h"
#include "Texture.h"
#include "utils.h"

Level::Level()
	: m_pBackgroundTexture{ new Texture("Resources/Images/background.png") }, 
	  m_pForegroundTexture{ new Texture("Resources/Images/fence.png") }
{
	InitialiseVertices();
}

Level::~Level()
{
	delete m_pBackgroundTexture;
	delete m_pForegroundTexture;
	m_pBackgroundTexture = nullptr;
	m_pForegroundTexture = nullptr;
}

void Level::DrawBackground() const
{
	//m_pBackgroundTexture->Draw(Rectf{ 0, 0, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight() });
	utils::SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
	utils::FillPolygon(m_Vertices);
	utils::SetColor(Color4f{ 1.0f, 0.0f, 0.0f, 1.0f });
	utils::DrawPolygon(m_Vertices, true, 3.0f);
}

void Level::DrawForeground() const
{
	m_pForegroundTexture->Draw(Rectf{ 200, 190, m_pForegroundTexture->GetWidth(), m_pForegroundTexture->GetHeight() });
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
}

bool Level::IsOnGround(const Rectf& actorShape)
{
	return false;
}

void Level::InitialiseVertices()
{
	m_Vertices.push_back(Point2f{ 0, 0 });
	m_Vertices.push_back(Point2f{ 0, 190 });
	m_Vertices.push_back(Point2f{ 340, 190 });
	m_Vertices.push_back(Point2f{ 408, 124 });
	m_Vertices.push_back(Point2f{ 560, 124 });
	m_Vertices.push_back(Point2f{ 660, 224 });
	m_Vertices.push_back(Point2f{ 846, 224 });
	m_Vertices.push_back(Point2f{ 846, 0 });
	//m_Vertices.push_back(Point2f{ 0, 0 });
}
