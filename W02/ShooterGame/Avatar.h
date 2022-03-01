#pragma once

class Enemy;
class Bullet;

class Avatar
{
public:
	Avatar();
	Avatar(const Point2f& center, float width, float height);
	~Avatar();
	void Update(float elapsedSec, Enemy** pEnemies, int numEnemies);
	void Draw() const;
	void DrawAvatar() const;
	void SetCenter(const Point2f& center);
	void SetDimensions(float width, float height);
	void SetBoundaries(const Rectf& boundaries);
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);

private:
	Point2f m_Center;
	float m_Width;
	float m_Height;
	float m_Speed;
	Rectf m_Boundaries;
	Bullet* m_Bullet;

	void HandleMoveKeysState(float elapsedSec);
	void Clamp();
};

