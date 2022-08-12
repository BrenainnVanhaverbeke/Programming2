#pragma once
#include "GameObject.h"
#include <vector>

class Character;
class Sprite;

class Background{

public:
	Background(Sprite* staticBackground, std::vector<Sprite*> parallaxLayers);
	~Background();

	void SetParallaxLayers(std::vector<Sprite*>& parallaxLayers);
	void Track(Character* character, const Rectf& boundaries);
	void Draw() const;

private:
	Sprite* m_pStaticBackground;
	std::vector<Sprite*> m_pParallaxLayers;
	Point2f m_pBottomLeft;

	void DeleteParallaxLayers();
};