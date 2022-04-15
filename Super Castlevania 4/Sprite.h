#pragma once
#include "GameObject.h"

class Texture;

class Sprite
{
public:
	Sprite(std::string path);
	Sprite(std::string path, const Rectf& sourceRect, bool hasSourceRect = true);
	~Sprite();

	void Update(float elapsedSec);
	void Draw(const Point2f& origin) const;
	void Draw(const Point2f& origin, int rowOffset);

	void SetSourceRect(const Rectf& sourceRect);

private:
	const bool m_HasSourceRect;
	const std::string m_Path;
	
	Rectf m_SourceRect;

	//const int m_Frames;
	//const int m_Rows;
	//const int m_Columns;
	//const float m_MaxFrameTime;
	//
	//int m_CurrentFrame;
	//float m_AccumulatedTime;
};