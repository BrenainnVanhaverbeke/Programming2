#include "pch.h"
#include "PowerUpManager.h"

PowerUpManager::PowerUpManager()
{
}

PowerUpManager::~PowerUpManager()
{
	for (PowerUp* powerUp : m_pItems)
	{
		delete powerUp;
		powerUp = nullptr;
	}
}

PowerUp* PowerUpManager::AddItem(const Point2f& center, PowerUp::Type type)
{
	PowerUp* newPowerUp{ new PowerUp(center, type) };
	m_pItems.push_back(newPowerUp);
	return newPowerUp;
}

void PowerUpManager::Update(float elapsedSec)
{
	for (PowerUp* powerUp : m_pItems)
		powerUp->Update(elapsedSec);
}

void PowerUpManager::Draw() const
{
	for (PowerUp* powerUp : m_pItems)
		powerUp->Draw();
}

size_t PowerUpManager::Size() const
{
	return m_pItems.size();
}

bool PowerUpManager::HitItem(const Rectf& rect)
{
	for (size_t powerUpIndex{ 0 }; powerUpIndex < Size(); ++powerUpIndex)
	{
		if (m_pItems[powerUpIndex]->IsOverlapping(rect))
		{
			PowerUp* temp{ m_pItems[Size() - 1] };
			m_pItems[Size() - 1] = m_pItems[powerUpIndex];
			m_pItems[powerUpIndex] = temp;
			m_pItems.pop_back();
			return true;
		}
	}
	return false;
}