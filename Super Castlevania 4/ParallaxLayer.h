#pragma once

class Sprite;

class ParallaxLayer
{
public:
	ParallaxLayer(Sprite* sprite, float staticBackgroundWidth, float offsetY);
	~ParallaxLayer();

	void Draw();
	void Update(float elapsedSec, const Point2f& cameraBottomLeft);
	void SetWindowSize(Rectf& windowSize);

private:
	const float m_StaticWidth;

	//Rectf& m_WindowSize;

	float m_OffsetX;
	float m_OffsetY;
	float startPos;
	float length;
	float parallaxFactor;
	Sprite* m_pSprite;

};