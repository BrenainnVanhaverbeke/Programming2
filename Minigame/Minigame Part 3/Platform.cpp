#include "pch.h"
#include "Platform.h"
#include "Texture.h"

Platform::Platform(const Point2f& bottomLeft)
	: m_pTexture{ new Texture("./Resources/Images/Platform.png") }
{
	if (m_pTexture->IsCreationOk())
		m_Shape = Rectf{ bottomLeft.x, bottomLeft.y, m_pTexture->GetWidth(), m_pTexture->GetHeight() };
}

Platform::~Platform()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Platform::Draw() const
{
	utils::FillPolygon(GetVertices());
	m_pTexture->Draw(m_Shape);
}

void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo{};
	if (DoRaycast(actorShape, hitInfo) && actorVelocity.y < 0)
	{
		actorVelocity.y = 0;
		actorShape.bottom = hitInfo.intersectPoint.y;
	}
}

bool Platform::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo{};
	return DoRaycast(actorShape, hitInfo) && actorVelocity.y <= 0;
}

bool Platform::DoRaycast(const Rectf& actorShape, utils::HitInfo& hitInfo) const
{
	Point2f rectCentreTop{ utils::GetRectCentreTop(actorShape) };
	Point2f rectCentreBottom{ rectCentreTop.x, rectCentreTop.y - actorShape.height - 1 };
	return utils::Raycast(GetVertices(), rectCentreTop, rectCentreBottom, hitInfo);
}

std::vector<Point2f> Platform::GetVertices() const
{
	std::vector<Point2f> vertices
	{
		Point2f{ m_Shape.left, m_Shape.bottom },
		Point2f{ m_Shape.left + m_Shape.width, m_Shape.bottom },
		Point2f{ m_Shape.left + m_Shape.width, m_Shape.bottom + m_Shape.height },
		Point2f{ m_Shape.left, m_Shape.bottom + m_Shape.height },
	};
	return vertices;
}
