#pragma once
#include "GameObject.h"

class Sprite
{
public:
	Sprite(std::string fileName);
	Sprite(std::string fileName, const Rectf& sourceRect, int frames = 1, int rows = 1, int framePerSeconds = 1);
	~Sprite();

	void Update(float elapsedSec, int rowOffset = 0, bool freezeFrame = false);
	void Draw(const Transform& origin, bool isFlipped = false) const;

	void SetSourceRect(const Rectf& sourceRect);

private:
	const std::string m_Path;
	const int m_Frames;
	const int m_Rows;
	const float m_MaxFrameTime;
	
	Rectf m_SourceRect;

	
	int m_CurrentFrame;
	float m_AccumulatedTime;

	void UpdateSourceRect(int rowOffset);
};