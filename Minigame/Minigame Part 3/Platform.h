#pragma once
#include "Vector2f.h"
#include <vector>
#include "utils.h"

class Texture;

class Platform
{
public:
	Platform(const Point2f& bottomLeft);
	~Platform();
	void Draw() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

private:
	Rectf m_Shape;
	Texture* m_pTexture;

	bool DoRaycast(const Rectf& actorShape, utils::HitInfo& hitInfo) const;
	std::vector<Point2f> GetVertices() const;
};