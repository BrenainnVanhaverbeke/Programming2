#pragma once
#include "Vector2f.h"
#include "utils.h"
#include <vector>

class Texture;

class Level
{
public:
	Level();
	~Level();
	void DrawBackground() const;
	void DrawForeground() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape) const;
	Rectf GetBoundaries() const;

private:
	const Texture* m_pBackgroundTexture;
	const Texture* m_pForegroundTexture;
	const Rectf m_Boundaries;
	
	std::vector<Point2f> m_Vertices;
	Point2f m_FenceBottomLeft;

	bool DoRaycast(const Rectf& actorShape, utils::HitInfo& hitInfo) const;
};