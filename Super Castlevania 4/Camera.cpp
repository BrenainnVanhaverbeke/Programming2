#include "pch.h"
#include "Camera.h"
#include "utils.h"

Camera::Camera(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_Bottom{}
	, m_ScaleFactor{ 2.0f }
{
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

Point2f Camera::Transform(const Rectf& target) const
{
	Point2f bottomLeftPos{ Track(target) };
	Clamp(bottomLeftPos);
	glScalef(m_ScaleFactor, m_ScaleFactor, 1.0f);
	glTranslatef(-bottomLeftPos.x, -bottomLeftPos.y, 0);
	return bottomLeftPos;
}

Point2f Camera::Track(const Rectf& target) const
{
	Point2f bottomLeftPos{ utils::GetRectCentre(target) };
	bottomLeftPos.x -= (m_Width / 2) / m_ScaleFactor;
	return bottomLeftPos;
}

void Camera::Clamp(Point2f& bottomLeftPos) const
{
	if (bottomLeftPos.x < m_LevelBoundaries.left)
		bottomLeftPos.x = m_LevelBoundaries.left;
	if (m_LevelBoundaries.left + m_LevelBoundaries.width < bottomLeftPos.x + (m_Width / m_ScaleFactor))
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - (m_Width / m_ScaleFactor);
	bottomLeftPos.y = m_LevelBoundaries.bottom;
}