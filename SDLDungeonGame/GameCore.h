#pragma once
#include "SDL.h"
#include <vector>

namespace DungeonGame
{
	const float WINDOW_WIDTH = 1280.0f;
	const float WINDOW_HEIGHT = 720.0f;

	const float TILE_SIZE_WIDTH = 72.0f;
	const float TILE_SIZE_HEIGHT = 72.0f;

	struct Vector2d
	{
		float X;
		float Y;

		Vector2d() :
			X(0.0f),
			Y(0.0f)
		{
		}

		Vector2d(float inX, float inY) :
			X(inX),
			Y(inY)
		{
		}

		bool operator==(const Vector2d& otherPosition) const
		{
			return X == otherPosition.X && Y == otherPosition.Y;
		}

		bool operator!=(const Vector2d& otherPosition) const
		{
			return !(*this == otherPosition);
		}

		Vector2d& operator+=(const Vector2d &rhs)
		{
			this->X += rhs.X;
			this->Y += rhs.Y;
			return *this;
		}

		const Vector2d operator+(const Vector2d &other) const
		{
			return Vector2d(*this) += other;
		}

		Vector2d& operator-=(const Vector2d &rhs)
		{
			this->X -= rhs.X;
			this->Y -= rhs.Y;
			return *this;
		}

		const Vector2d operator-(const Vector2d &other) const
		{
			return Vector2d(*this) -= other;
		}

		Vector2d& operator*=(float scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
			return *this;
		}

		const Vector2d operator*(float scalar) const
		{
			return Vector2d(*this) *= scalar;
		}

		float GetLength()
		{
			return sqrtf(X * X + Y * Y);
		}

		void Normalize()
		{
			float length = GetLength();
			if (length > 0.0f)
			{
				X = X / length;
				Y = Y / length;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
			}
		}
	};

	enum EnemyType
	{
		ENEMY_Empty,
		ENEMY_Full
	};

	struct EnemyData
	{
		EnemyType enemytype;
		Vector2d m_CurrentPosition;
		Vector2d m_DesiredDirection;
	};
	struct HeroData
	{
		EnemyType herotype;
		Vector2d m_CurrentPosition;
		Vector2d m_DesiredDirection;
	};
	
	
	class PlayerState
	{
	public:
		void Initialize();
		void Reset();

		bool EnemyCollideWithPlayer(EnemyData* pEnemy);
		bool SightCollideWithPlayer(EnemyData* pEnemy);
		bool WantsToWin;

		Vector2d m_CurrentPosition;
		Vector2d m_DesiredDirection;

		bool m_bHasFinishedGame;


	};

	class WorldState
	{
	public:
		void Initialize();
		void Reset();

		unsigned int GetTileTypeAtPosition(const Vector2d& inPosition);
		

		unsigned int m_TilesPerRow;
		std::vector<unsigned int> m_Tiles;
		std::vector<EnemyData> m_Enemy;
		

	};

	void InitializeGame(SDL_Renderer* pRenderer, WorldState& worldState, PlayerState& playerState);
	void GetInput(const WorldState& worldState, PlayerState& playerState);
	void UpdateGame(float deltaSeconds, WorldState& worldState, PlayerState& playerState);
	void RenderGame(SDL_Renderer* pRenderer, const WorldState& worldState, const PlayerState& playerState);
	void CleanupGame();
}