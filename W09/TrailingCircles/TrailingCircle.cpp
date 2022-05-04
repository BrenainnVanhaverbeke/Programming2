#include "pch.h"
#include <cmath>
#include "TrailingCircle.h"
#include "utils.h"


TrailingCircle::TrailingCircle(float radius, const Point2f& center)
	: m_Radius{ radius }
	, m_Center{ center }
	, m_Color{ GetRandomColor() }
	, m_Velocity(GetRandomVelocity())
	, m_TrailDelay{ 0.08f }
	, m_AccumulatedTime{ 0 }
	, m_MaxTrailPoints{ 10 }
{
}

void TrailingCircle::Update(float elapsedSec, const Rectf& boundingRect)
{
	UpdateSelf(elapsedSec, boundingRect);
	UpdateTrail(elapsedSec, boundingRect);
}

void TrailingCircle::Draw() const
{
	utils::SetColor(m_Color);
	utils::FillEllipse(m_Center, m_Radius, m_Radius);
	Color4f fadingColour{ m_Color };
	fadingColour.a = 0;
	float radiusModifier{ 0 };
	for (Point2f trailPoint : m_TrailPoints)
	{
		fadingColour.a += 0.1f;
		radiusModifier += 0.1f;
		utils::SetColor(fadingColour);
		utils::FillEllipse(trailPoint, m_Radius * radiusModifier, m_Radius * radiusModifier);
	}
}

void TrailingCircle::UpdateSelf(float elapsedSec, const Rectf& boundingRect)
{
	// Calculate new position
	Vector2f centerVector{ m_Center };
	centerVector += m_Velocity * elapsedSec;
	m_Center = centerVector.ToPoint2f();

	// Handle reflection against bounding rectangle
	if (m_Velocity.x > 0 && m_Center.x + m_Radius > boundingRect.left + boundingRect.width)
	{
		m_Velocity.x = -m_Velocity.x;
	}
	else if (m_Velocity.x < 0 && m_Center.x - m_Radius < boundingRect.left)
	{
		m_Velocity.x = -m_Velocity.x;
	}
	if (m_Velocity.y > 0 && m_Center.y + m_Radius > boundingRect.bottom + boundingRect.height)
	{
		m_Velocity.y = -m_Velocity.y;
	}
	else if (m_Velocity.y < 0 && m_Center.y - m_Radius < boundingRect.bottom)
	{
		m_Velocity.y = -m_Velocity.y;
	}
}

void TrailingCircle::UpdateTrail(float elapsedSec, const Rectf& boundingRect)
{
	m_AccumulatedTime += elapsedSec;
	if (m_TrailDelay < m_AccumulatedTime)
	{
		m_AccumulatedTime = 0;
		m_TrailPoints.push_back(m_Center);
	}
	if (m_MaxTrailPoints <= m_TrailPoints.size())
		m_TrailPoints.pop_front();
}

Vector2f TrailingCircle::GetRandomVelocity()
{
	const int speedMin{ 50 };
	const int speedMax{ 100 };
	int speed{ rand() % (speedMax - speedMin + 1) + speedMin };
	float angle{ rand() % 360 * float(utils::g_Pi / 360) };
	return Vector2f{ speed * cos(angle) , speed * sin(angle) };
}

Color4f TrailingCircle::GetRandomColor()
{
	return Color4f{ rand() % 256 / 256.0f, rand() % 256 / 256.0f, rand() % 256 / 256.0f, 1.0f };
}
