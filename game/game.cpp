/*
OneLoneCoder.com - Code-It-Yourself! Simple Tile Based Platform Game
"Its-a meee-a Jario!" - @Javidx9
License
~~~~~~~
Copyright (C) 2018  Javidx9
This program comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it
under certain conditions; See license for details.
Original works located at:
https://www.github.com/onelonecoder
https://www.onelonecoder.com
https://www.youtube.com/javidx9
GNU GPLv3
https://github.com/OneLoneCoder/videos/blob/master/LICENSE
From Javidx9 :)
~~~~~~~~~~~~~~~
Hello! Ultimately I don't care what you use this for. It's intended to be
educational, and perhaps to the oddly minded - a little bit of fun.
Please hack this, change it and use it in any way you see fit. You acknowledge
that I am not responsible for anything bad that happens as a result of
your actions. However this code is protected by GNU GPLv3, see the license in the
github repo. This means you must attribute me if you use it. You can view this
license here: https://github.com/OneLoneCoder/videos/blob/master/LICENSE
Cheers!
Background
~~~~~~~~~~
Tile maps are fundamental to most 2D games. This program explores emulating a classic 2D platformer
using floating point truncation to implement robust collision between a moving tile and a tilemap
representing the level.
Controls
~~~~~~~~
Left and Right arrow keys move Jario, Space bar jumps.
(Up and Down also move jario)
Author
~~~~~~
Twitter: @javidx9
Blog: www.onelonecoder.com
YouTube: www.youtube.com/javidx9
Discord: https://discord.gg/WhwHUMV
Video:
~~~~~~
https://youtu.be/oJvJZNyW_rw
Last Updated: 04/02/2018
*/

#include <iostream>
#include <string>
using namespace std;

#include "olcConsoleGameEngine.h"

class OneLoneCoder_Platformer : public olcConsoleGameEngine
{
public:
	OneLoneCoder_Platformer()
	{
		m_sAppName = L"Tile Based Platform Game";
	}

private:
	// Level storage
	wstring sLevel;
	int nLevelWidth;
	int nLevelHeight;

	// Player Properties
	float fPlayerPosX = 1.0f;
	float fPlayerPosY = 1.0f;
	float fPlayerVelX = 0.0f;
	float fPlayerVelY = 0.0f;

	// Enemy roperties
	float fenemyPosX = 15.0f;
	float fenemyPosY = 1.0f;
	float fenemyVelX = 0.0f;
	float fenemyVelY = 0.0f;

	float fenemySpeed = 1.0f;

	// Camera properties
	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;

	// Sprite Resources
	olcSprite* spriteTiles = nullptr;
	olcSprite* spriteMan = nullptr;
	olcSprite* spriteBoar = nullptr;
	olcSprite* spriteTrees = nullptr;



	// Sprite selection flags
	int nDirModX = 0;
	int nDirModY = 0;

	float playerSpeed = 40.0f;

protected:
	virtual bool OnUserCreate()
	{
		nLevelWidth = 64;
		nLevelHeight = 16;
		sLevel += L"................................................................";
		sLevel += L"...TM................M..........................................";
		sLevel += L".......ooooo....................................................";
		sLevel += L"........ooo......T..............................................";
		sLevel += L".....#........T........########.................................";
		sLevel += L"....###########.......###..............#.#......................";
		sLevel += L".....#..............###................#.#......................";
		sLevel += L".....#.............####.........................................";
		sLevel += L".....#.....#.........................##############.....########";
		sLevel += L".....#....#...B.B.................BB.................###........";
		sLevel += L".....#..##..............############.#............###...........";
		sLevel += L"..........##B....B......#............#.........###..............";
		sLevel += L"............................................###.................";
		sLevel += L"........................#................###....................";
		sLevel += L"........................#################.......................";
		sLevel += L"................................................................";

		spriteTiles = new olcSprite(L"leveljario.spr");
		spriteMan = new olcSprite(L"minijario.spr");
		spriteBoar = new olcSprite(L"boar.spr");
		spriteTrees = new olcSprite(L"trees.spr");

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		// Utility Lambdas
		auto GetTile = [&](int x, int y)
		{
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
				return sLevel[y * nLevelWidth + x];
			else
				return L' ';
		};

		auto SetTile = [&](int x, int y, wchar_t c)
		{
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
				sLevel[y * nLevelWidth + x] = c;
		};

		//fPlayerVelX = 0.0f;
		//fPlayerVelY = 0.0f;

		// Handle Input
		if (IsFocused())
		{
			if (GetKey(VK_UP).bHeld)
			{
				fPlayerVelY = -playerSpeed * fElapsedTime;

			}

			if (GetKey(VK_DOWN).bHeld)
			{
				fPlayerVelY = playerSpeed * fElapsedTime;

			}

			if (GetKey(VK_LEFT).bHeld)
			{
				fPlayerVelX = -playerSpeed * fElapsedTime;

				nDirModY = 1;
			}

			if (GetKey(VK_RIGHT).bHeld)
			{
				fPlayerVelX = playerSpeed * fElapsedTime;
				//fPlayerPosX += playerSpeed * fElapsedTime;
				nDirModY = 0;
			}


			/*if (GetKey(VK_SPACE).bPressed)
			{
				if (fPlayerVelY == 0)
				{
					fPlayerVelY = -12.0f;
					nDirModX = 1;
				}
			}*/
		}



		// Calculate potential new position
		float fNewPlayerPosX = fPlayerPosX + fPlayerVelX * fElapsedTime;
		float fNewPlayerPosY = fPlayerPosY + fPlayerVelY * fElapsedTime;

		// Check for pickups!
		if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 0.0f) == L'o')
			SetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 0.0f, L'.');

		if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f) == L'o')
			SetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f, L'.');

		if (GetTile(fNewPlayerPosX + 1.0f, fNewPlayerPosY + 0.0f) == L'o')
			SetTile(fNewPlayerPosX + 1.0f, fNewPlayerPosY + 0.0f, L'.');

		if (GetTile(fNewPlayerPosX + 1.0f, fNewPlayerPosY + 1.0f) == L'o')
			SetTile(fNewPlayerPosX + 1.0f, fNewPlayerPosY + 1.0f, L'.');

		// Check for Collision
		if (fPlayerVelX <= 0) // Moving Left
		{
			if (GetTile(fNewPlayerPosX + 0.0f, fPlayerPosY + 0.0f) != L'.' || GetTile(fNewPlayerPosX + 0.0f, fPlayerPosY + 0.9f) != L'.')
			{
				fNewPlayerPosX = (int)fNewPlayerPosX + 1;

			}
			fPlayerVelX = 0;
		}
		else // Moving Right
		{
			if (GetTile(fNewPlayerPosX + 1.0f, fPlayerPosY + 0.0f) != L'.' || GetTile(fNewPlayerPosX + 1.0f, fPlayerPosY + 0.9f) != L'.')
			{
				fNewPlayerPosX = (int)fNewPlayerPosX;


			}
			fPlayerVelX = 0;
		}

		if (fPlayerVelY <= 0) // Moving Up
		{
			if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY) != L'.' || GetTile(fNewPlayerPosX + 0.9f, fNewPlayerPosY) != L'.')
			{
				fNewPlayerPosY = (int)fNewPlayerPosY + 1;

			}
			fPlayerVelY = 0;
		}
		else
		{
			if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f) != L'.' || GetTile(fNewPlayerPosX + 0.9f, fNewPlayerPosY + 1.0f) != L'.')
			{
				fNewPlayerPosY = (int)fNewPlayerPosY;

				nDirModX = 0;
			}
			fPlayerVelY = 0;
		}

		// Apply new position
		fPlayerPosX = fNewPlayerPosX;
		fPlayerPosY = fNewPlayerPosY;

		// Link camera to player position
		fCameraPosX = fPlayerPosX;
		fCameraPosY = fPlayerPosY;

		// Draw Level
		int nTileWidth = 16;
		int nTileHeight = 16;
		int nVisibleTilesX = ScreenWidth() / nTileWidth;
		int nVisibleTilesY = ScreenHeight() / nTileHeight;

		// Calculate Top-Leftmost visible tile
		float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
		float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;

		// Clamp camera to game boundaries
		if (fOffsetX < 0) fOffsetX = 0;
		if (fOffsetY < 0) fOffsetY = 0;
		if (fOffsetX > nLevelWidth - nVisibleTilesX) fOffsetX = nLevelWidth - nVisibleTilesX;
		if (fOffsetY > nLevelHeight - nVisibleTilesY) fOffsetY = nLevelHeight - nVisibleTilesY;

		// Get offsets for smooth movement
		float fTileOffsetX = (fOffsetX - (int)fOffsetX) * nTileWidth;
		float fTileOffsetY = (fOffsetY - (int)fOffsetY) * nTileHeight;

		// Draw visible tile map
		for (int x = -1; x < nVisibleTilesX + 1; x++)
		{
			for (int y = -1; y < nVisibleTilesY + 1; y++)
			{
				wchar_t sTileID = GetTile(x + fOffsetX, y + fOffsetY);
				switch (sTileID)
				{
				case L'.': // Sky
					Fill(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, PIXEL_SOLID, FG_CYAN);
					break;
				case L'#': // Solid Block
					//Fill(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, PIXEL_SOLID, FG_RED);
					DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTiles, 2 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
					break;
				case L'G': // Ground Block
					DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTiles, 0 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
					break;
				case L'B': // Brick Block
					DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTiles, 0 * nTileWidth, 1 * nTileHeight, nTileWidth, nTileHeight);
					break;
				case L'?': // Question Block
					DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTiles, 1 * nTileWidth, 1 * nTileHeight, nTileWidth, nTileHeight);
					break;
				case L'o': // Coin
					Fill(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, PIXEL_SOLID, FG_CYAN);
					DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTiles, 3 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
					break;
				case L'T': // TREES
					Fill(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, PIXEL_SOLID, FG_CYAN);
					DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTrees, 0, 0 * nTileHeight, nTileWidth, nTileHeight);
					break;
				case L'M': // Mashroom
					Fill(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, PIXEL_SOLID, FG_CYAN);
					DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTrees, 3* nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
					break;
				default:
					Fill(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, PIXEL_SOLID, FG_BLACK);
					break;
				}
			}
		}

		if (fenemyPosX > fPlayerPosX)
		{
			fenemyPosX -= fenemySpeed * fElapsedTime;
		}
		if (fenemyPosX < fPlayerPosX)
		{
			fenemyPosX += fenemySpeed * fElapsedTime;
		}
		if (fenemyPosY > fPlayerPosY)
		{
			fenemyPosY -= fenemySpeed * fElapsedTime;
		}
		if (fenemyPosY < fPlayerPosY)
		{
			fenemyPosY += fenemySpeed * fElapsedTime;
		}
		// Draw Player
		//Fill((fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileWidth, (fPlayerPosX - fOffsetX + 1.0f) * nTileWidth, (fPlayerPosY - fOffsetY + 1.0f) * nTileHeight, PIXEL_SOLID, FG_GREEN);
		DrawPartialSprite((fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileWidth, spriteMan, nDirModX * nTileWidth, nDirModY * nTileHeight, nTileWidth, nTileHeight);


		//Draw Enemy
		DrawPartialSprite((fenemyPosX - fOffsetX) * nTileWidth, (fenemyPosY - fOffsetY) * nTileWidth, spriteBoar, 0, 0, nTileWidth, nTileHeight);
		return true;


	}
};


int main()
{
	OneLoneCoder_Platformer game;
	if (game.ConstructConsole(256, 240, 4, 4))
		game.Start();
	return 0;
}