#include "pch.h"
#include "Background.h"
#include "Sprite.h"
#include "Character.h"
#include "ParallaxLayer.h"

Background::Background(Sprite* staticBackground, std::vector<ParallaxLayer*> parallaxLayers, int zIndex)
	: GameObject(zIndex)
	, m_pStaticBackground{ staticBackground }
	, m_pParallaxLayers{ parallaxLayers }
{
}

Background::~Background()
{
	delete m_pStaticBackground;
	m_pStaticBackground = nullptr;
	DeleteParallaxLayers();
}

void Background::SetParallaxLayers(std::vector<ParallaxLayer*>& parallaxLayers)
{
	DeleteParallaxLayers();
	m_pParallaxLayers = parallaxLayers;
}

void Background::Track(Character* character, const Rectf& boundaries)
{
}

void Background::Draw(int zIndex) const
{
	size_t nrOfLayers{ m_pParallaxLayers.size() };
	for (size_t i{ 0 }; i < nrOfLayers; ++i)
		m_pParallaxLayers.at(i)->Draw(zIndex);
	if (zIndex == m_ZIndex)
		m_pStaticBackground->Draw(Transform{});
}

void Background::DrawDebug(int zIndex) const
{
}

void Background::Update(float elapsedSec, const Point2f& cameraBottomLeft)
{
	size_t parallaxLayers{ m_pParallaxLayers.size() };
	for (size_t i{ 0 }; i < parallaxLayers; ++i)
	{
		m_pParallaxLayers.at(i)->Update(elapsedSec, cameraBottomLeft);
	}
}

void Background::SetWindowSize(Rectf& windowSize)
{
	size_t nrOfLayer{ m_pParallaxLayers.size() };
	for (size_t i{ 0 }; i < nrOfLayer; ++i)
	{
		m_pParallaxLayers.at(i)->SetWindowSize(windowSize);
	}
}

void Background::DeleteParallaxLayers()
{
	size_t nrOfLayers{ m_pParallaxLayers.size() };
	if (0 < nrOfLayers)
	{
		for (size_t i{ 0 }; i < nrOfLayers; ++i)
			delete m_pParallaxLayers.at(i);
		m_pParallaxLayers.clear();
	}
}

void Background::Update(float elapsedSec)
{
}
