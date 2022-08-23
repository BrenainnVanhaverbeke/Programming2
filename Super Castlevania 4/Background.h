#pragma once
#include "GameObject.h"
#include <vector>

class Character;
class Sprite;
class ParallaxLayer;

class Background final : GameObject {

public:
	explicit Background(Sprite* staticBackground, std::vector<ParallaxLayer*> parallaxLayers, int zIndex);
	virtual ~Background();

	void SetParallaxLayers(std::vector<ParallaxLayer*>& parallaxLayers);
	void Track(Character* character, const Rectf& boundaries);
	void Update(float elapsedSec, const Point2f& cameraBottomLeft);
	void SetWindowSize(Rectf& windowSize);
	
	// Inherited via GameObject
	virtual void Draw(int zIndex) const override;
	virtual void DrawDebug(int zIndex) const override;

private:
	Sprite* m_pStaticBackground;
	std::vector<ParallaxLayer*> m_pParallaxLayers;
	Point2f m_pBottomLeft;

	void DeleteParallaxLayers();

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;

};