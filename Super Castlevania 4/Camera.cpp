#include "pch.h"
#include "Camera.h"
#include "utils.h"

Camera::Camera(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_Bottom{}
{
}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

Point2f Camera::Track(const Rectf& target)
{
	m_BottomLeftPosition = utils::GetRectCentre(target);
	m_BottomLeftPosition.x -= (m_Width / 2) / G_SCALEFACTOR;
	Clamp(m_BottomLeftPosition);
	return m_BottomLeftPosition;
}

void Camera::Transform() const
{
	glScalef(G_SCALEFACTOR, G_SCALEFACTOR, 1.0f);
	glTranslatef(-m_BottomLeftPosition.x, -m_BottomLeftPosition.y, 0);
}


void Camera::Clamp(Point2f& bottomLeftPos) const
{
	if (bottomLeftPos.x < m_LevelBoundaries.left)
		bottomLeftPos.x = m_LevelBoundaries.left;
	if (m_LevelBoundaries.left + m_LevelBoundaries.width < bottomLeftPos.x + (m_Width / G_SCALEFACTOR))
		bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - (m_Width / G_SCALEFACTOR);
	bottomLeftPos.y = m_LevelBoundaries.bottom;
}