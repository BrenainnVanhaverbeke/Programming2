#include "pch.h"
#include "Sprite.h"
#include "TextureManager.h"

Sprite::Sprite(std::string path)
	: Sprite(path, Rectf{}, false)
{
}

Sprite::Sprite(std::string fileName, const Rectf& sourceRect, bool hasSourceRect)
	: m_Path{ fileName }
	, m_SourceRect{ sourceRect }
	, m_HasSourceRect{ hasSourceRect }
{
	m_SourceRect.Log();
}

Sprite::~Sprite()
{
}

void Sprite::Update(float elapsedSec)
{
}

void Sprite::Draw(const Point2f& origin) const
{
	TextureManager* textureManager{ TextureManager::GetInstance() };
	textureManager->DrawSprite(m_Path, origin, m_SourceRect);
}

void Sprite::SetSourceRect(const Rectf& sourceRect)
{
	m_SourceRect = sourceRect;
}
