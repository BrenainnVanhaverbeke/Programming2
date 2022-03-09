#include "pch.h"
#include <iostream>
#include "Game.h"
#include "Weapon.h"
#include "Enemy.h"
#include "PickUp.h"
#include "GameObject.h"

Game::Game()
{

}
Game::~Game()
{
	for (GameObject* gameObject : m_pGameObjects)
	{
		delete gameObject;
	}
	m_pGameObjects.clear();
}

void Game::AddEnemy()
{
	m_pGameObjects.push_back(new Enemy());
}

void Game::AddPickUp()
{
	m_pGameObjects.push_back(new PickUp());
}

void Game::AddWeapon()
{
	m_pGameObjects.push_back(new Weapon());
}

void Game::ReportAll() const
{
	int seqNr{ 0 };

	std::cout << "--> All Game objects\n";
	for (GameObject* ptr : m_pGameObjects)
	{
		++seqNr;
		std::cout << seqNr << ": " << ptr->ToString() << "\n";
	}
}

void Game::ReportEnemies() const
{
	ReportEnemiesDynamicCast();
	ReportEnemiesTypeid();
}

void Game::ReportEnemiesDynamicCast() const
{
	std::cout << "--> Enemies (dynamic cast)\n";
	for (GameObject* gameObject : m_pGameObjects)
	{
		Enemy* enemy{ dynamic_cast<Enemy*>(gameObject) };
		if (enemy)
		{
			std::cout << enemy->ToString() << std::endl;
		}
	}
}

void Game::ReportEnemiesTypeid() const
{
	std::cout << "--> Enemies (typeid)\n";
	for (GameObject* gameObject : m_pGameObjects)
	{
		if (typeid(*gameObject) == typeid(Enemy))
		{
			Enemy* enemy{ static_cast<Enemy*>(gameObject) };
			std::cout << enemy->ToString() << std::endl;
		}
	}
}
