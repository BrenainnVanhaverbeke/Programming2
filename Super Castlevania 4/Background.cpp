#include "pch.h"
#include "Background.h"
#include "Sprite.h"
#include "Character.h"

Background::Background(Sprite* staticBackground, std::vector<Sprite*> parallaxLayers)
    : m_pStaticBackground{ staticBackground }
    , m_pParallaxLayers{ parallaxLayers }
{
}

Background::~Background()
{
    delete m_pStaticBackground;
    m_pStaticBackground = nullptr;
    DeleteParallaxLayers();
}

void Background::SetParallaxLayers(std::vector<Sprite*>& parallaxLayers)
{
    DeleteParallaxLayers();
    m_pParallaxLayers = parallaxLayers;
}

void Background::Track(Character* character, const Rectf& boundaries)
{
}

void Background::Draw() const
{
    size_t nrOfLayers{ m_pParallaxLayers.size() };
    for (size_t i{ 0 }; i < nrOfLayers; ++i)
    {
        m_pParallaxLayers.at(i)->Draw(Transform{ m_pBottomLeft });
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
