#pragma once
#include "GameObject.h"
#include <vector>

class Character;
class Sprite;
class ParallaxLayer;

class Background{

public:
	Background(Sprite* staticBackground, std::vector<ParallaxLayer*> parallaxLayers);
	~Background();

	void SetParallaxLayers(std::vector<ParallaxLayer*>& parallaxLayers);
	void Track(Character* character, const Rectf& boundaries);
	void Draw() const;
	void Update(float elapsedSec, const Point2f& cameraBottomLeft);
	void SetWindowSize(Rectf& windowSize);

private:
	Sprite* m_pStaticBackground;
	std::vector<ParallaxLayer*> m_pParallaxLayers;
	Point2f m_pBottomLeft;

	void DeleteParallaxLayers();
};