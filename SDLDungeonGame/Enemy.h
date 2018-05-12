#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	enum EnemyState
	{
		EnemyState_Nothing,
		EnemyState_Idle, 
		EnemyState_Seen,
		EnemyState_Returning,
		EnemyState_Winning

	};
	class Enemy : public Sprite
	{
	public:
		void InitMe(SDL_Renderer* pRenderer, EnemyData* pEnemyData);
		virtual void Render(SDL_Renderer *pRenderer, const WorldState& worldState, const PlayerState& playerState, const Vector2d& baseTransformation = Vector2d());
		virtual void Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState);


	private:
		void SetEnemyState(EnemyState);
		

		EnemyData* m_pEnemyData;

		EnemyState m_EnemyState; 

		float m_Seconds;
		SDL_Texture* m_pFrame0;
		SDL_Texture* m_pFrame1;

		

		

	//private:
		//SDL_Texture* m_pExtraSprite;
	};

}