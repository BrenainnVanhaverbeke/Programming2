#pragma once
#include "GameObject.h"
#include "Vector2f.h"
#include "IOverlappingObject.h"

class Sprite;
class MovementBehaviour;

class Character : public GameObject, public IOverlappingObject
{
public:
	explicit Character(Transform transform, Sprite* sprite, MovementBehaviour* movement, float width, float height, int zIndex, int health, int id);
	Character& operator=(const Character& rhs) = delete;
	Character& operator=(Character&& rhs) = delete;
	Character(const Character& other) = delete;
	Character(Character&& other) = delete;
	virtual ~Character();

	virtual Rectf GetShape() const;
	virtual Vector2f& GetVelocity() const final;
	virtual void TakeDamage(int damage);

	virtual int GetHealth() const final;
	virtual int GetId() const final;

	// Inherited via IOverlappingObject
	virtual bool IsOverlapping(const Rectf& overlappingShape) override;
	virtual bool IsOverlapping(const std::vector<Point2f>& overlappingShape) override;

	// Inherited via GameObject
	virtual void DrawDebug(int zIndex) const override;

protected:
	const int m_Id;

	Sprite* m_pSprite;
	MovementBehaviour* m_pMovementBehaviour;

	float m_Width;
	float m_Height;
	int m_Health;

	virtual Sprite* GetSprite() const = 0;



};