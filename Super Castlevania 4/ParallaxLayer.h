#pragma once
#include "GameObject.h"

class Sprite;

class ParallaxLayer final : public GameObject
{
public:
	explicit ParallaxLayer(Sprite* sprite, float staticBackgroundWidth, float offsetY, int zIndex);
	virtual ~ParallaxLayer();

	void Update(float elapsedSec, const Point2f& cameraBottomLeft);
	void SetWindowSize(Rectf& windowSize);

	virtual void Draw(int zIndex) const override;
	virtual void DrawDebug(int zIndex) const override;

private:
	const float m_StaticWidth;

	//Rectf& m_WindowSize;

	float m_OffsetX;
	float m_OffsetY;
	float startPos;
	float length;
	float parallaxFactor;
	Sprite* m_pSprite;


	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;


};