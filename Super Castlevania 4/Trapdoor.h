#pragma once
#include "TerrainObject.h"

class TrapDoor final : public TerrainObject
{
	enum class TrapDoorState
	{
		idle,
		activated,
		rotating
	};

public:
	explicit TrapDoor(const std::vector<Point2f>& vertices, bool isBackground);
	TrapDoor& operator= (const TrapDoor& rhs) = delete;
	TrapDoor& operator= (TrapDoor&& rhs) = delete;
	TrapDoor(const TrapDoor& other) = delete;
	TrapDoor(TrapDoor&& other) = delete;
	virtual ~TrapDoor();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	virtual bool HandleCollisions(Character& character);
	virtual bool IsOnGround(const Character& character) override;

private:
	const float m_ActivationDelay;
	const float m_RotationSpeed;
	const float m_MaxAngle;
	const std::vector<Point2f> m_BaseVertices;

	TrapDoorState m_State;
	float m_AccumulatedTime;

	Point2f GetPivot(const std::vector<Point2f>& vertices);
	void RotateVertices(float elapsedSec);
};