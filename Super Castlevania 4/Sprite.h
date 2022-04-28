#pragma once
#include "GameObject.h"

class Sprite final
{
public:
	explicit Sprite(std::string fileName);
	explicit Sprite(std::string fileName, const Rectf& sourceRect, int frames = 1, int rows = 1, int framePerSeconds = 1);
	Sprite& operator= (const Sprite& rhs) = delete;
	Sprite& operator= (Sprite&& rhs) = delete;
	Sprite(const Sprite& other) = delete;
	Sprite(Sprite&& other) = delete;
	~Sprite() = default;

	void Update(float elapsedSec, int rowOffset = 0, bool freezeFrame = false);
	void Draw(const Transform& origin, bool isFlipped = false) const;
	void DrawRotatedCenter(const Transform& origin, float width, float height, bool isFlipped = false);

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