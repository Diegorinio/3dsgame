#include <3ds.h>
#include <stdio.h>
#include <citro2d.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "player.h"
#include "enemy.h"
#include "gui.h"
#include "sprites.h"
#include "bullet.h"
#include "functions.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240


int main(int argc, char **argv)
{
	//colors
	u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
	u32 clrClear = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);
	u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	u32 clrBlack  = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
	
	//initialize Player
	struct Player MainPlayer;
	SetPlayer(&MainPlayer);
	
	//initialize Enemy
	struct Enemy Enemy;
	SetEnemy(&Enemy);

	int MainScore;

	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	
	// consoleInit(GFX_BOTTOM, NULL);
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	//sprites
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if(!spriteSheet) svcBreak(USERBREAK_PANIC);

	initSprites(&MainPlayer, &Enemy);


	initMenu();

	// Main loop
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//render
		// ShowMeInfo(MainScore);
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START) break; // break in order to return to hbmenu
		touchPosition touch;

		hidTouchRead(&touch);
		if(kDown & KEY_A)
		{
			// PlayerSetSprite(&MainPlayer, &sprites[1].spr);
			if(MainPlayer.sprite == &sprites[1].spr)
			{
				MainPlayer.sprite = &sprites[0].spr;
			}
			else if(MainPlayer.sprite == &sprites[0].spr)
			{
				MainPlayer.sprite = &sprites[1].spr;
			}
		}

		if(kDown & KEY_B)
		{

		}

		if(kHeld & KEY_UP)
		{
			// if(MainPlayer.PlayerCollidersY[0] > -100)
			// {
			// 	MovePlayerY(&MainPlayer, -5);
			// }
		}

		if(kHeld & KEY_DOWN)
		{
			// if(MainPlayer.PlayerCollidersY[0] < 100)
			// {
			// 	MovePlayerY(&MainPlayer, 5);
			// }
			// else
			// {
			// 	MovePlayerY(&MainPlayer, 0);
			// }
		}
		if(kHeld & KEY_RIGHT)
		{
			if(MainPlayer.posX < SCREEN_WIDTH - MainPlayer.width)
			{
				MovePlayerX(&MainPlayer, 2.5f);
			}
		}
		if(kHeld & KEY_LEFT)
		{
			if(MainPlayer.posX > MainPlayer.width)
			{
				MovePlayerX(&MainPlayer, -2.5f);
			}
		}

		//Draw on top
		C2D_SceneBegin(top);

		C2D_TargetClear(top, clrClear);
		
		
		//player
		DrawPlayer(&MainPlayer);
		PlayerCheckPosition(&MainPlayer);

		//enemy
		DrawEnemy(&Enemy);
		Enemy.moveY += 1;
		EnemyCheckCollisions(&Enemy);

		if(Enemy.EnemyColliderY >= 150)
		{
			RespawnEnemy(&Enemy, &sprites[GenerateRandomInt(0,1)].spr);
		}
		
		if(EnemyCheckCollisionsWithPlayer(&Enemy, &MainPlayer))
		{
			MainScore+=1;
			RespawnEnemy(&Enemy, &sprites[GenerateRandomInt(0,1)].spr);
		}

		
		//draw on bottom
		C2D_SceneBegin(bottom);
		C2D_TargetClear(bottom, clrRed);
		DrawGameGUI(MainScore);
		// C2D_DrawRectangle(SCREEN_WIDTH - 50, 0, 0, 50, 50, clrRed, clrRed, clrRed, clrRed);
		// consoleInit(GFX_BOTTOM, NULL);
		// printf("Score:%d ", MainScore);
		
		// gfxFlushBuffers();
		// gfxSwapBuffers();
		C3D_FrameEnd(0);
	}
	
	
	
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	return 0;
}