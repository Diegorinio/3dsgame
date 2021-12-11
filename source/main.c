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
#include "functions.h"
#include "colors.h"


int main(int argc, char **argv)
{
	// initialize gameplay
	static bool IsPlayable = true;
	static bool IsMenu = true;
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

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		//render
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		// if (kDown & KEY_START) break; // break 
		if(IsPlayable)
		{
					//Scan all the inputs. This should be done oncein order to return to hbmenu
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
		
		if(kHeld & KEY_RIGHT)
		{
			if(MainPlayer.posX <  SCREEN_WIDTH - MainPlayer.width)
			{
				MovePlayerX(&MainPlayer, 3);
			}
		}
		if(kHeld & KEY_LEFT)
		{
			if(MainPlayer.posX > MainPlayer.width)
			{
				MovePlayerX(&MainPlayer, -3);
			}
		}

		//Draw on top
		C2D_SceneBegin(top);

		C2D_TargetClear(top, CLEAR);

		//enemy
		DrawEnemy(&Enemy);
		Enemy.moveY += 1;
		EnemyCheckCollisions(&Enemy);

				//player
		DrawPlayer(&MainPlayer);
		PlayerCheckPosition(&MainPlayer);

		if(Enemy.EnemyColliderY >= 150)
		{
			RespawnEnemy(&Enemy, &sprites[GenerateRandomInt(0,1)].spr);
			PlayerLoseHealth(&MainPlayer);
		}
		
		if(EnemyCheckCollisionsWithPlayer(&Enemy, &MainPlayer))
		{
			MainScore+=1;
			RespawnEnemy(&Enemy, &sprites[GenerateRandomInt(0,1)].spr);
		}

		if(MainPlayer.PlayerHP <= 0)
		{
			IsPlayable = false;
			// free(&MainPlayer);
		}

		
		//draw on bottom
		C2D_SceneBegin(bottom);
		C2D_TargetClear(bottom, CLEAR);
		DrawGameScoreAndHelth(MainScore, &MainPlayer);
		}
		if(!IsPlayable)
		{
			C2D_SceneBegin(top);
			C2D_TargetClear(top, CLEAR);
			DrawGameOverScreen();
			C2D_DrawRectangle(100, 100,1,50,50,BLACK,BLACK,BLACK,BLACK);


			C2D_SceneBegin(bottom);
			C2D_TargetClear(bottom, WHITE);
			DrawTextOnScreen("A) Again\n START) EXIT", 100, 100,1);
			if(kDown && KEY_A)
			{
				IsPlayable = true;
				MainScore = 0;
			}

		}
		// if(IsMenu)
		// {
		// 	C2D_SceneBegin(top);
		// 	C2D_TargetClear(top, WHITE);
    	// 	DrawMenu();

    	// 	C2D_SceneBegin(bottom);
		// 	C2D_TargetClear(bottom, WHITE);
    	// 	DrawTextOnScreen("Press START", 70, SCREEN_HEIGHT/2,1);

		// 	if(kDown && KEY_START)
		// 	{
		// 		IsPlayable = true;
		// 		IsMenu = false;
		// 	}
		// }
		C3D_FrameEnd(0);	
	}
	
	
	
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	return 0;
}