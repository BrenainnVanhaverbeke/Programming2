#include "pch.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "utils.h"
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
	, m_Origin{ sourceRect.GetTopLeft() }
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

void Sprite::Draw(const Transform& transform, bool isFlipped) const
{
	TextureManager& textureManager{ TextureManager::GetInstance() };
	glPushMatrix();
	{
		glTranslatef(transform.positionX, transform.positionY, 0);
		if (isFlipped)
		{
			glScalef(-1, 1, 1);
			glTranslatef(-m_SourceRect.width, 0, 0);
		}
		textureManager.DrawTexture(m_Path, m_SourceRect);
	}
	glPopMatrix();
}

void Sprite::DrawRotatedCenter(const Transform& origin, float width, float height, bool isFlipped)
{
	TextureManager& textureManager{ TextureManager::GetInstance() };
	Point2f pivot{ origin.positionX + (width / 2), origin.positionY + (height / 2)};
	glPushMatrix();
	{
		glTranslatef(pivot.x, pivot.y, 0);
		glRotatef(origin.angle, 0, 0, 1);
		glTranslatef(-width / 2, -height / 2, 0);
		textureManager.DrawTexture(m_Path, m_SourceRect);
	}
	glPopMatrix();
}

void Sprite::Reset()
{
	m_CurrentFrame = 0;
	m_AccumulatedTime = 0;
}

void Sprite::SetSourceRect(const Rectf& sourceRect)
{
	m_SourceRect = sourceRect;
}

Rectf Sprite::GetSourceRect()
{
	return m_SourceRect;
}

void Sprite::UpdateSourceRect(int rowOffset)
{
	TextureManager& textureManager{ TextureManager::GetInstance() };
	float textureHeight{};
	float textureWidth{};
	textureManager.GetTextureDimensions(m_Path, textureWidth, textureHeight);
	m_SourceRect.left = m_Origin.x + (m_SourceRect.width * m_CurrentFrame);
	m_SourceRect.bottom = m_Origin.y + (m_SourceRect.height * (rowOffset));
}