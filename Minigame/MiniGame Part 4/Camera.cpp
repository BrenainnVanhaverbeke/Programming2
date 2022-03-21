#include "pch.h"
#include "Camera.h"
#include "utils.h"

Camera::Camera(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
{
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Transform(const Rectf& target)
{
	Point2f bottomLeftPos{ Track(target) };
	Clamp(bottomLeftPos);
	//utils::DrawRect(bottomLeftPos, m_Width, m_Height);
	glTranslatef(-bottomLeftPos.x, -bottomLeftPos.y, 0);
}

Point2f Camera::Track(const Rectf& target)
{
	Point2f bottomLeftPos{ utils::GetRectCentre(target) };
	bottomLeftPos.x -= m_Width / 2;
	bottomLeftPos.y -= m_Height / 2;
	return bottomLeftPos;
}

void Camera::Clamp(Point2f& bottomLeftPos)
{
	if (bottomLeftPos.x < m_LevelBoundaries.left)
		bottomLeftPos.x = m_LevelBoundaries.left;
	if (m_LevelBoundaries.left + m_LevelBoundaries.width < bottomLeftPos.x + m_Width)
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width;
	if (bottomLeftPos.y < m_LevelBoundaries.bottom)
		bottomLeftPos.y = m_LevelBoundaries.bottom;
	if (m_LevelBoundaries.bottom + m_LevelBoundaries.height < bottomLeftPos.y + m_Height)
		bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height;
}