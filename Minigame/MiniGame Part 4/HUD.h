#pragma once

class Texture;

class HUD
{
public:
	HUD(const Point2f& topLeft, int totalPowerUps);
	~HUD();
	void Draw() const;
	void PowerUpHit();

private:
	const int m_TotalPowerUps;
	const Texture* m_pLeftTexture;
	const Texture* m_pRightTexture;
	const Texture* m_pPowerUpTexture;

	int m_HitPowerUps;
	Point2f m_BottomLeft;

	void DrawLeft(Point2f& elementOrigin) const;
	void DrawCenter(Point2f& elementOrigin) const;
	void DrawRight(Point2f& elementOrigin) const;
};