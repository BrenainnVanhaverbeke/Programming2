#pragma once

class Enemy;
class Avatar
{
public:
	Avatar();
	Avatar(const Point2f& center, float width, float height);
	void Update(float elapsedSec, Enemy** pEnemies, int numEnemies);
	void Draw();
	void SetCenter(const Point2f& center);
	void SetDimensions(float width, float height);
	void SetBoundaries(const Rectf& boundaries);

private:
	Point2f m_Center;
	float m_Width;
	float m_Height;
	float m_Speed;
	Rectf m_Boundaries;

	void HandleMoveKeysState(float elapsedSec);
	void Clamp();
};

