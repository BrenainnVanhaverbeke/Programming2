#pragma once
#include "Vector2f.h"
#include <deque>

class TrailingCircle
{
public:
	TrailingCircle( float radius, const Point2f& center);
	void Update( float elapsedSec, const Rectf& boundingRect );
	void Draw( ) const;

private:
	const float m_Radius;
	const float m_TrailDelay;
	const size_t m_MaxTrailPoints;
	const Color4f m_Color;

	float m_AccumulatedTime;
	Point2f m_Center;
	Vector2f m_Velocity;
	std::deque<Point2f> m_TrailPoints;

	void UpdateSelf(float elapsedSec, const Rectf& boundingRect);
	void UpdateTrail(float elapsedSec, const Rectf& boundingRect);
	Vector2f GetRandomVelocity( );
	Color4f GetRandomColor( );
};
