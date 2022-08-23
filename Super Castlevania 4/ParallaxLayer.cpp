#include "pch.h"
#include "ParallaxLayer.h"
#include "Sprite.h"
#include <iostream>

ParallaxLayer::ParallaxLayer(Sprite* sprite, float staticBackgroundWidth, float offsetY, int zIndex)
	: GameObject(zIndex)
	, m_pSprite{ sprite }
	, m_StaticWidth{ staticBackgroundWidth }
	, m_OffsetX{ 0 }
	, m_OffsetY{ offsetY }
	, startPos{ 0 }
	, length{ sprite->GetSourceRect().width }
	, parallaxFactor{ 0 }
{
}

ParallaxLayer::~ParallaxLayer()
{
	delete m_pSprite;
	m_pSprite = nullptr;
}

void ParallaxLayer::Draw(int zIndex) const
{
	if (zIndex == m_ZIndex)
		m_pSprite->Draw(Transform{ m_OffsetX, m_OffsetY });
}

void ParallaxLayer::DrawDebug(int zIndex) const
{
}

void ParallaxLayer::Update(float elapsedSec, const Point2f& cameraBottomLeft)
{
	float distance{ cameraBottomLeft.x * parallaxFactor };
	m_OffsetX = startPos + distance;
}

void ParallaxLayer::SetWindowSize(Rectf& windowSize)
{
	float layerWidth{ m_pSprite->GetSourceRect().width };
	float foregroundDistance{ (m_StaticWidth - (windowSize.width / G_SCALEFACTOR)) };
	float backgroundDistance{ m_StaticWidth - layerWidth };
	parallaxFactor = (m_StaticWidth - layerWidth) / foregroundDistance;
}

void ParallaxLayer::Update(float elapsedSec)
{
}
