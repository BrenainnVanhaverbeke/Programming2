#include "pch.h"
#include "Sprite.h"
#include "TextureManager.h"
#include <iostream>

Sprite::Sprite(std::string fileName)
	: Sprite(fileName, Rectf{}, false)
{
}

Sprite::Sprite(std::string fileName, const Rectf& sourceRect, int frames, int rows, int framePerSeconds)
	: m_Path{ fileName }
	, m_SourceRect{ sourceRect }
	, m_Frames{ frames }
	, m_Rows{ rows }
	, m_MaxFrameTime{ 1.0f / framePerSeconds }
	, m_CurrentFrame{ 0 }
	, m_AccumulatedTime{ 0 }
{
}

Sprite::~Sprite()
{
}

void Sprite::Update(float elapsedSec, int rowOffset, bool freezeFrame)
{
	m_AccumulatedTime += elapsedSec;
	if (freezeFrame)
		m_CurrentFrame = 0;
	else if (m_MaxFrameTime < m_AccumulatedTime)
	{
		m_AccumulatedTime = 0;
		m_CurrentFrame = (m_CurrentFrame + 1) % m_Frames;
	}
	UpdateSourceRect(rowOffset);
}

void Sprite::Draw(const Transform& origin, bool isFlipped) const
{
	TextureManager& textureManager{ TextureManager::GetInstance() };
	glPushMatrix();
	{
		glTranslatef(origin.positionX, origin.positionY, 0);
		if (isFlipped)
		{
			glScalef(-1, 1, 1);
			glTranslatef(-m_SourceRect.width, 0, 0);
		}
		textureManager.DrawSprite(m_Path, origin, m_SourceRect, isFlipped);
	}
	glPopMatrix();
}

void Sprite::SetSourceRect(const Rectf& sourceRect)
{
	m_SourceRect = sourceRect;
}

void Sprite::UpdateSourceRect(int rowOffset)
{
	TextureManager& textureManager{ TextureManager::GetInstance() };
	float textureHeight{};
	float textureWidth{};
	textureManager.GetTextureDimensions(m_Path, textureWidth, textureHeight);
	m_SourceRect.bottom = (textureHeight / m_Rows) * (rowOffset + 1);
	m_SourceRect.left = (textureWidth / m_Frames) * m_CurrentFrame;
}