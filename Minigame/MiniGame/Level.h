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
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	bool IsOnGround(const Rectf& actorShape);

private:
	std::vector<Point2f> m_Vertices;
	const Texture* m_pBackgroundTexture;
	const Texture* m_pForegroundTexture;
	Point2f m_FenceBottomLeft;

	void InitialiseVertices();
	bool DoRaycast(const Rectf& actorShape, utils::HitInfo& hitInfo);
};