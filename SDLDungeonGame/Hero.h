#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Hero : public Sprite
	{
	public:
		void InitMe(SDL_Renderer* pRenderer);
		virtual void Render(SDL_Renderer *pRenderer, const WorldState& worldState, const PlayerState& playerState, const Vector2d& baseTransformation = Vector2d());
		virtual void Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState);

	private:

		bool FacingRight;

		

		


	};
}