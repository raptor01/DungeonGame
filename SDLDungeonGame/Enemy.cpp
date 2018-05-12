#include "Enemy.h"
//#include <iostream>
//#include <stdlib.h>
using namespace std;
using namespace DungeonGame;

void Enemy::InitMe(SDL_Renderer* pRenderer, EnemyData* pEnemyData)
{
	m_pEnemyData = pEnemyData;
	if (m_pEnemyData->enemytype == ENEMY_Full)
	{
		m_pFrame0 = Sprite::LoadTexture(pRenderer, "Assets/foe00.bmp");
		m_pFrame1 = Sprite::LoadTexture(pRenderer, "Assets/foe01.bmp");

		m_Seconds = 0.0f;
		Initialize(m_pFrame0);
		
	}
	else if (m_pEnemyData->enemytype == ENEMY_Empty)
	{
		m_pFrame0 = Sprite::LoadTexture(pRenderer, "Assets/foe00.bmp");
		Initialize(m_pFrame0);
		
	}

	

	//m_pExtraSprite = Sprite::LoadTexture(pRenderer, "Assets/hero00.bmp");
}

void Enemy::Render(SDL_Renderer *pRenderer, const WorldState& worldState, const PlayerState& playerState, const Vector2d& baseTransformation)
{
	m_EnemyState = EnemyState_Nothing;
	Sprite::Render(pRenderer, worldState, playerState, baseTransformation);
	
	if (m_pTexture && m_bVisible)
	{
		SDL_Rect destRect = { (int)(m_Position.X + baseTransformation.X), (int)(m_Position.Y + baseTransformation.Y), (int)m_Size.X, (int)m_Size.Y};
		SDL_RenderCopy(pRenderer, m_pTexture, nullptr, &destRect);
	}
	SetEnemyState(EnemyState_Idle);
}
void Enemy::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
{
	{
		m_Seconds -= deltaSeconds;

		if (m_Seconds <= 0)
		{
			if (m_pEnemyData->enemytype == ENEMY_Full)
			{
				if (m_pTexture == m_pFrame0)
				{
					m_pTexture = m_pFrame1;
				}
				else
				{
					m_pTexture = m_pFrame0;
				}
				m_Seconds = 2.5f;
			}
		}
	}

	if (playerState.SightCollideWithPlayer(m_pEnemyData))
	{
		SetEnemyState(EnemyState_Seen);
	}
	if (playerState.WantsToWin)
	{
		SetEnemyState(EnemyState_Winning);
	}

	switch (m_EnemyState)
	{
	case EnemyState_Idle:
	{

	}
		break;
	case EnemyState_Seen:
	{
		if (worldState.GetTileTypeAtPosition(m_Position) != 0)
		{
			Vector2d vectorToPlayer = playerState.m_CurrentPosition - m_pEnemyData->m_CurrentPosition;
			vectorToPlayer.Normalize();
			m_pEnemyData->m_CurrentPosition -= vectorToPlayer * deltaSeconds * 120.0f;
		}
			
		
	}
		break;
	case EnemyState_Returning:
	{
	
	}
		break;

	case EnemyState_Winning:
	{
		Vector2d vectorToPlayer = playerState.m_CurrentPosition - m_pEnemyData->m_CurrentPosition;
		vectorToPlayer.Normalize();
		m_pEnemyData->m_CurrentPosition += vectorToPlayer * deltaSeconds * 120.0f;
		//system(cout<<"YouWin");
		//cout << "YouWin!"<<endl;
		//Sleep(5000000000);
	}
	break;
	}

	/*if (playerState.SightCollideWithPlayer(m_pEnemyData))
	{
		const float ENEMY_MOVEMENT_SPEED = 200.0f *deltaSeconds;

		Vector2d newPosition = m_pEnemyData->m_CurrentPosition + m_pEnemyData->m_DesiredDirection * ENEMY_MOVEMENT_SPEED;
		if (worldState.GetTileTypeAtPosition(newPosition) == 1)
		{
			m_pEnemyData->m_CurrentPosition = newPosition;
		}
	}*/
	

	m_Position = m_pEnemyData->m_CurrentPosition; 

	if (playerState.EnemyCollideWithPlayer(m_pEnemyData))
	{
		if (m_pEnemyData->enemytype == ENEMY_Full)
		{
			playerState.WantsToWin = true;
		}
		else
		{
			playerState.m_bHasFinishedGame = true;
		}
	}
}

void Enemy::SetEnemyState(EnemyState newEnemyState)
{
	if (m_EnemyState != newEnemyState)
	{
		m_EnemyState = newEnemyState;

		switch (m_EnemyState)
		{
		default:
			break;
		}
		m_EnemyState = newEnemyState;
		switch (m_EnemyState)
		{
		default:
			break;
		}
	}
}