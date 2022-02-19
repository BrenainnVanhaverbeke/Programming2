#include "pch.h"
#include "Card.h"
#include "Texture.h"

Card::Card(Suit suit, int rank)
	: m_Suit{ suit }, m_Rank{ rank }
{
	m_pTexture = new Texture(GetImagePath(suit, rank));
	m_Width = m_pTexture->GetWidth();
	m_Height = m_pTexture->GetHeight();
}

Card::~Card()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

float Card::GetWidth() const
{
	return m_Width;
}

float Card::GetHeight() const
{
	return m_Height;
}

std::string Card::GetImagePath(Suit suit, int rank) const
{
	std::string prefix{ "Resources/Cards/" };
	int index = ((int)suit * 100) + rank;
	std::string suffix{ ".png" };
	return prefix + std::to_string(index) + suffix;
}

void Card::Draw(const Rectf& destRect) const
{
	m_pTexture->Draw(destRect);
}