#pragma once
class GameObject
{
public:
	explicit GameObject();
	explicit GameObject(Transformation transform);
	~GameObject();

	virtual void Update(float elapsedSec) = 0;
	virtual void Draw() const = 0;

protected:
	Transformation m_Transform;

};