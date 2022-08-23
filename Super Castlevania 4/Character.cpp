#include "pch.h"
#include "Character.h"
#include "Sprite.h"
#include "MovementBehaviour.h"
#include "utils.h"
#include <iostream>
#include "LevelManager.h"

Character::Character(Transform transform, Sprite* sprite, MovementBehaviour* movement, CharacterTypes type, LevelManager* pLevelManager, float width, float height, int zIndex, int health, int id)
	: Character(transform, sprite, movement, type, ProjectileTag::none, pLevelManager, width, height, zIndex, health, id)
{
}

Character::Character(Transform transform, Sprite* sprite, MovementBehaviour* movement, CharacterTypes type, ProjectileTag projectileTag, LevelManager* pLevelManager, float width, float height, int zIndex, int health, int id)
	: GameObject(transform, zIndex)
	, m_pSprite{ sprite }
	, m_Width{ width }
	, m_CharacterType{ type }
	, m_ProjectileTag{ projectileTag }
	, m_Height{ height }
	, m_pMovementBehaviour{ movement }
	, m_Health{ health }
	, m_Id{ id }
	, m_ShouldDie{ false }
	, m_ShouldFire{ false }
	, m_ImmunityList{}
	, m_IsFlipped{ false }
	, m_pLevelManager{ pLevelManager }
{
}

Character::~Character()
{
	delete m_pSprite;
	delete m_pMovementBehaviour;
	m_pSprite = nullptr;
	m_pMovementBehaviour = nullptr;
}

Rectf Character::GetShape() const
{
	return Rectf{
		m_Transform.positionX,
		m_Transform.positionY,
		m_Width,
		m_Height
	};
}

Vector2f& Character::GetVelocity() const
{
	return m_pMovementBehaviour->GetVelocity();
}

void Character::TakeDamage(int damage)
{
	m_Health -= damage;
	if (m_Health <= 0)
		m_ShouldDie = true;
}

int Character::GetHealth() const
{
	return m_Health;
}

int Character::GetId() const
{
	return m_Id;
}

bool Character::ShouldDie() const
{
	return m_ShouldDie;
}

bool Character::IsFlipped() const
{
	return m_IsFlipped;
}

bool Character::ShouldFire()
{
	return m_ShouldFire;
}

Point2f Character::GetProjectileSpawn() const
{
	return m_ProjectileSpawn;
}

void Character::SetIsFlipped(bool isFlipped)
{
	m_IsFlipped = isFlipped;
}

void Character::AddImmuneId(int id)
{
	m_ImmunityList.push_back(id);
}

CharacterTypes Character::GetCharacterType() const
{
	return m_CharacterType;
}

ProjectileTag Character::GetProjectileTag() const
{
	return m_ProjectileTag;
}

std::vector<int> Character::GetImmunityList() const
{
	return m_ImmunityList;
}

bool Character::IsOverlapping(const Rectf& overlappingShape)
{
	return utils::IsOverlapping(GetShape(), overlappingShape);
}

bool Character::IsOverlapping(const std::vector<Point2f>& overlappingShape)
{
	return utils::IsOverlapping(overlappingShape, GetShape().ConvertToVector());
}

void Character::DrawDebug(int zIndex) const
{
	if (zIndex == m_ZIndex)
		utils::DrawRect(GetShape());
}