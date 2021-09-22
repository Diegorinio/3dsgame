#include <3ds.h>
#include <stdio.h>
#include <citro2d.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "player.h"
#include "enemytriangle.h"
#include "gui.h"
#include "sprites.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240


int GenerateRandomInt(int min, int max);


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
	struct TriEnemy Enemy;
	TriSetEnemy(&Enemy);
	
	
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

	initSprites(&MainPlayer);

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
		// printf("\x1b[2;0H%03d; %03d", touch.px, touch.py);
		if(kDown & KEY_A)
		{

		}
		if(kDown & KEY_B)
		{

		}
		if(kHeld & KEY_UP)
		{
			if(MainPlayer.PlayerCollidersY[0] > -100)
			{
				MovePlayerY(&MainPlayer, -10);
			}
		}

		if(kHeld & KEY_DOWN)
		{
			if(MainPlayer.PlayerCollidersY[0] < 100)
			{
				MovePlayerY(&MainPlayer, 10);
			}
			else
			{
				MovePlayerY(&MainPlayer, 0);
			}
		}
		if(kHeld & KEY_RIGHT)
		{
			if(MainPlayer.PlayerCollidersX[1] < SCREEN_WIDTH)
			{
				MovePlayerX(&MainPlayer, 10);
			}
		}
		if(kHeld & KEY_LEFT)
		{
			if(MainPlayer.PlayerCollidersX[0] >0)
			{
				MovePlayerX(&MainPlayer, -10);
			}
		}
		if(kHeld & KEY_DOWN)
		{
			// ShowMeSomething("Down");
		}

		//Draw on top
		C2D_SceneBegin(top);

		C2D_TargetClear(top, clrClear);
		
		//player
		DrawPlayer(&MainPlayer);
		PlayerCheckPosition(&MainPlayer);

		//enemy
		TriDrawEnemy(&Enemy);
		Enemy.moveY +=3;
		TriEnemyCheckCollisions(&Enemy);
		
		if(TriEnemyCheckCollisionsWithPlayer(&Enemy, &MainPlayer))
		{
			MainScore -=1;
		}
		C2D_DrawRectangle(SCREEN_WIDTH - 100, 0, 0, 50, 50, clrRed, clrRed, clrRed, clrRed);

		
		//draw on bottom
		C2D_TargetClear(bottom, clrClear);
		C2D_SceneBegin(bottom);
		// consoleInit(GFX_BOTTOM, NULL);
		// printf("%d, %f", MainPlayer.PlayerCollidersY[0] < 100,MainPlayer.PlayerCollidersY[1]);
		// gfxFlushBuffers();
		// gfxSwapBuffers();
		// DrawMenu(MainScore);
		C3D_FrameEnd(0);
	}
	
	
	
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
	return 0;
}

int GenerateRandomInt(int min, int max)
{
	srand(time(0));
	return (rand() % (max-min+1))+min;
}
