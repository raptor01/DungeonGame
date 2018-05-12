#include "GameCore.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Hero.h"
#include "RoomRenderer.h"

namespace DungeonGame
{
	std::vector<Sprite*> g_spriteList;
	Vector2d g_cameraPosition;
	//Hero* g_pHero = nullptr;


	void PlayerState::Initialize()
	{
		//TODO: Initialize PlayerState stuff here

		Reset();
	}

	void PlayerState::Reset()
	{
		m_CurrentPosition = Vector2d(12.0f * 72.0f, 15.0f * 72.0f);

		m_bHasFinishedGame = false;
	}

	bool PlayerState::EnemyCollideWithPlayer(EnemyData* pEnemy)
	{
		Vector2d enemyToPlayer = pEnemy->m_CurrentPosition - m_CurrentPosition;
		float distance = enemyToPlayer.GetLength();
		
		return distance < 48.0f;

	}

	bool PlayerState::SightCollideWithPlayer(EnemyData* pEnemy)
	{
		Vector2d enemyToPlayer = pEnemy->m_CurrentPosition - m_CurrentPosition;
		float distance = enemyToPlayer.GetLength();

		return distance < 216.0f;

	}

	

	void WorldState::Initialize()
	{
		m_TilesPerRow = 24;
		m_Tiles = 
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
			0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
			0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0,
			0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 0,
			0, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 0,
			0, 2, 2, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 0,
			0, 2, 1, 2, 2, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0,
			0, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 0,
			0, 2, 2, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 0,
			0, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0,
			0, 2, 1, 1, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 0,
			0, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 0,
			0, 2, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 0,
			0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
			0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		};

		{
			EnemyData enemy1 = {};
			enemy1.enemytype = ENEMY_Empty;
			enemy1.m_CurrentPosition = Vector2d(4.0f * 72.0f, 4.0f * 72.0f);
			m_Enemy.push_back(enemy1);
		}

		{
			EnemyData enemy2 = {};
			enemy2.enemytype = ENEMY_Empty;
			enemy2.m_CurrentPosition = Vector2d(21.0f * 72.0f, 6.0f * 72.0f);
			m_Enemy.push_back(enemy2);
		}

		{
			EnemyData enemy3 = {};
			enemy3.enemytype = ENEMY_Empty;
			enemy3.m_CurrentPosition = Vector2d(12.0f * 72.0f, 7.0f * 72.0f);
			m_Enemy.push_back(enemy3);
		}

		{
			EnemyData enemy4 = {};
			enemy4.enemytype = ENEMY_Empty;
			enemy4.m_CurrentPosition = Vector2d(6.0f * 72.0f, 9.0f * 72.0f);
			m_Enemy.push_back(enemy4);
		}

		{
			EnemyData enemy5 = {};
			enemy5.enemytype = ENEMY_Full;
			enemy5.m_CurrentPosition = Vector2d(17.0f * 72.0f, 11.0f * 72.0f);
			m_Enemy.push_back(enemy5);
		}

		{
			EnemyData enemy6 = {};
			enemy6.enemytype = ENEMY_Empty;
			enemy6.m_CurrentPosition = Vector2d(20.0f * 72.0f, 14.0f * 72.0f);
			m_Enemy.push_back(enemy6);
		}

		{
			EnemyData enemy7 = {};
			enemy7.enemytype = ENEMY_Empty;
			enemy7.m_CurrentPosition = Vector2d(4.0f * 72.0f, 18.0f * 72.0f);
			m_Enemy.push_back(enemy7);
		}

		{
			EnemyData enemy8 = {};
			enemy8.enemytype = ENEMY_Empty;
			enemy8.m_CurrentPosition = Vector2d(16.0f * 72.0f, 18.0f * 72.0f);
			m_Enemy.push_back(enemy8);
		}

		{
			EnemyData enemy9 = {};
			enemy9.enemytype = ENEMY_Empty;
			enemy9.m_CurrentPosition = Vector2d(8.0f * 72.0f, 19.0f * 72.0f);
			m_Enemy.push_back(enemy9);
		}

		{
			EnemyData enemy10 = {};
			enemy10.enemytype = ENEMY_Empty;
			enemy10.m_CurrentPosition = Vector2d(19.0f * 72.0f, 23.0f * 72.0f);
			m_Enemy.push_back(enemy10);
		}

		{
			EnemyData enemy11 = {};
			enemy11.enemytype = ENEMY_Empty;
			enemy11.m_CurrentPosition = Vector2d(10.0f * 72.0f, 24.0f * 72.0f);
			m_Enemy.push_back(enemy11);
		}

		{
			EnemyData enemy12 = {};
			enemy12.enemytype = ENEMY_Empty;
			enemy12.m_CurrentPosition = Vector2d(3.0f * 72.0f, 25.0f * 72.0f);
			m_Enemy.push_back(enemy12);
		}

		{
			EnemyData enemy13 = {};
			enemy13.enemytype = ENEMY_Empty;
			enemy13.m_CurrentPosition = Vector2d(16.0f * 72.0f, 26.0f * 72.0f);
			m_Enemy.push_back(enemy13);
		}

		Reset();
	}

	void WorldState::Reset()
	{
		//TODO: Reseet WorldState stuff to default values

		
	}

	unsigned int WorldState::GetTileTypeAtPosition(const Vector2d& inPosition)
	{

		int col = (int)(inPosition.X / 72.0f);
		int row = (int)(inPosition.Y / 72.0f);


		int index = row * m_TilesPerRow + col;

		if (index >= 0 && index < m_Tiles.size())
		{
			/*if (index + 1 == 0)
			{
				return m_Tiles[index + 1];
			}
			else if (index - 1 == 0)
			{
				return m_Tiles[index - 1];
			}
			else*/
			
				return m_Tiles[index];
			
		}

	}

	
	void InitializeGame(SDL_Renderer* pRenderer, WorldState& worldState, PlayerState& playerState)
	{
		worldState.Initialize();
		playerState.Initialize();

		g_cameraPosition = Vector2d();

		Sprite* pBackgoundSprite = new Sprite;
		pBackgoundSprite->Initialize(Sprite::LoadTexture(pRenderer, "Assets/background.bmp"));
		pBackgoundSprite->m_Size = Vector2d(WINDOW_WIDTH, WINDOW_HEIGHT);
		g_spriteList.push_back(pBackgoundSprite);

		RoomRenderer* pRoom = new RoomRenderer;
		pRoom->InitMe(pRenderer);
		g_spriteList.push_back(pRoom);

		Hero* pHeroSprite = new Hero;
		pHeroSprite->InitMe(pRenderer);
		g_spriteList.push_back(pHeroSprite);

		

		for (unsigned int i = 0; i < worldState.m_Enemy.size(); i++)
		{
			Enemy* pEnemy = new Enemy;
			pEnemy->InitMe(pRenderer, &worldState.m_Enemy[i]);
			g_spriteList.push_back(pEnemy);
		}

		

		//g_pHero = pHeroSprite;



		
		//charSprite.Initialize(Sprite::LoadTexture(pRenderer, "Assets/hero00.bmp"));
		//charSprite.m_Position = Vector2d(35.0f, 35.0f);

		
		
		
		//enemy.Initialize(Sprite::LoadTexture(pRenderer, "Assets/foe00.bmp"));
		//enemy.m_Position = Vector2d(500.0f, 500.0f);

		//std::string imagePath = "Assets/hero00.bmp";
		//SDL_Surface *pCharBmp = SDL_LoadBMP("hero00.bmp");
		//SDL_Texture *pCharTexture = SDL_CreateTextureFromSurface(pRenderer, pCharBmp);
		//SDL_FreeSurface(pCharBmp);

		
	}

	void GetInput(const WorldState& worldState, PlayerState& playerState)
	{
		
		SDL_Event e = {};
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				playerState.m_bHasFinishedGame = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_ESCAPE:
					playerState.m_bHasFinishedGame = true;
					break;
				case SDLK_UP:
					playerState.m_DesiredDirection.Y = -1.0f;
					break;
				case SDLK_DOWN:
					playerState.m_DesiredDirection.Y = 1.0f;
					break;
				case SDLK_RIGHT:
					playerState.m_DesiredDirection.X = 1.0f;
					break;
				case SDLK_LEFT:
					playerState.m_DesiredDirection.X = -1.0f;
					break;
					
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_UP:	
				case SDLK_DOWN:	
					playerState.m_DesiredDirection.Y = 0.0f;
					break;
				case SDLK_RIGHT:

				case SDLK_LEFT:
					playerState.m_DesiredDirection.X = 0.0f;
					break;
				}
			}
		}
	}

	void UpdateGame(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
	{
		//testSprite.Update(deltaSeconds, worldState, playerState);
		


		for (int i = 0; i < g_spriteList.size(); i++)
		{	
			g_spriteList[i]->Update(deltaSeconds, worldState, playerState);	
		}

		g_cameraPosition = Vector2d(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f) - playerState.m_CurrentPosition;

		//const float CHAR_MOVEMENT_SPEED = 300.0f *deltaSeconds;
		//playerState.m_CurrentPosition = playerState.m_CurrentPosition + playerState.m_DesiredDirection * CHAR_MOVEMENT_SPEED;
		//g_pHero->m_Position = playerState.m_CurrentPosition;
	}

	void RenderGame(SDL_Renderer* pRenderer, const WorldState& worldState, const PlayerState& playerState)
	{
		SDL_RenderClear(pRenderer);

		
		for (int i = 0; i < g_spriteList.size(); i++)
		{
			g_spriteList[i]->Render(pRenderer, worldState, playerState, g_cameraPosition);
		}
		

		SDL_RenderPresent(pRenderer);
	}

	void CleanupGame()
	{
		for (int i = 0; i < g_spriteList.size(); i++)
		{
			g_spriteList[i]->Cleanup();
			delete g_spriteList[i];
		}
		
		Sprite::ClearTextures();
	}
}