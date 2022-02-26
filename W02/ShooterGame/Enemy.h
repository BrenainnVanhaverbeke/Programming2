#pragma once
class Enemy
{
public:
	Enemy();
	Enemy(const Point2f& center, float width, float height);
	void Draw() const;
	bool DoHitTest(const Rectf& other) const;
	void SetCenter(const Point2f& center);
	void SetDimensions(float width, float height);
	bool IsDead() const;

private:
	Point2f m_Center;
	float m_Width;
	float m_Height;
	bool m_IsDead;

	Rectf GetEnemyRect() const;
};