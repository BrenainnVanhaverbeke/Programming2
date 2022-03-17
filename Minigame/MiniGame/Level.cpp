#include "pch.h"
#include "Level.h"
#include "Texture.h"

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
	m_pBackgroundTexture->Draw(Rectf{ 0, 0, m_pBackgroundTexture->GetWidth(), m_pBackgroundTexture->GetHeight() });
	utils::DrawPolygon(m_Vertices, true, 3.0f);
	utils::SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 0.25f });
	utils::FillPolygon(m_Vertices);
}

void Level::DrawForeground() const
{
	m_pForegroundTexture->Draw(Rectf{ 200, 190, m_pForegroundTexture->GetWidth(), m_pForegroundTexture->GetHeight() });
}

void Level::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	utils::HitInfo hitInfo{};
	if (DoRaycast(actorShape, hitInfo))
	{
		actorVelocity.y = 0;
		actorShape.bottom = hitInfo.intersectPoint.y;
	}
}

bool Level::IsOnGround(const Rectf& actorShape)
{
	utils::HitInfo hitInfo{};
	return DoRaycast(actorShape, hitInfo);
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
	m_Vertices.push_back(Point2f{ 0, 0 });
}

bool Level::DoRaycast(const Rectf& actorShape, utils::HitInfo& hitInfo)
{
	Point2f rectCentreTop{ utils::GetRectCentreTop(actorShape) };
	Point2f rectCentreBottom{ rectCentreTop.x, rectCentreTop.y - actorShape.height - 1 };
	return utils::Raycast(m_Vertices, rectCentreTop, rectCentreBottom, hitInfo);
}
