#pragma once
class Camera
{
public:
	explicit Camera(float width, float height);
	void SetLevelBoundaries(const Rectf& levelBoundaries);
	Point2f Transform(const Rectf& target) const;

private:
	const float m_Width;
	const float m_Height;
	const float m_Bottom;
	const float m_ScaleFactor;

	Rectf m_LevelBoundaries;

	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& bottomLeftPos) const;
};