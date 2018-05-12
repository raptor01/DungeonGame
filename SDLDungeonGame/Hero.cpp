#include "Hero.h"

using namespace DungeonGame;

void Hero::InitMe(SDL_Renderer* pRenderer)
{
	
	Sprite::Initialize(Sprite::LoadTexture(pRenderer, "Assets/hero00.bmp"));
	
	
}

void Hero::Render(SDL_Renderer *pRenderer, const WorldState& worldState, const PlayerState& playerState, const Vector2d& baseTransformation)
{
	if (m_pTexture && m_bVisible)
	{
		SDL_Rect destRect = { (int)(m_Position.X + baseTransformation.X), (int)(m_Position.Y + baseTransformation.Y), (int)m_Size.X, (int)m_Size.Y };
		SDL_RenderCopyEx(pRenderer, m_pTexture, nullptr, &destRect, 0.0, nullptr, SDL_FLIP_HORIZONTAL);
	}
}

void Hero::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
{
	const float CHAR_MOVEMENT_SPEED = 200.0f *deltaSeconds;

	

	Vector2d newPosition = (playerState.m_CurrentPosition + playerState.m_DesiredDirection * CHAR_MOVEMENT_SPEED);
	if (worldState.GetTileTypeAtPosition(newPosition) == 1)
	{
		playerState.m_CurrentPosition = newPosition;
	}
	


	m_Position = playerState.m_CurrentPosition;
}