#pragma once
class MovementBehaviour
{
	MovementBehaviour();
	virtual ~MovementBehaviour() = default;
	
	virtual void Update(float elapsedSec) = 0;
	virtual void UpdateState() = 0;
	virtual void Move(float elapsedSec) = 0;
};

