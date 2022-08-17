#pragma once
class Camera final
{
public:
	explicit Camera(float width, float height);
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	Point2f Track(const Rectf& target);
	void Transform() const;

private:
	const float m_Width;
	const float m_Height;
	const float m_Bottom;
	const float m_ScaleFactor;

	Point2f m_BottomLeftPosition;
	Rectf m_LevelBoundaries;

	void Clamp(Point2f& bottomLeftPos) const;
};