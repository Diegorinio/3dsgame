/*
	Hello World example made by Aurelio Mannara for libctru
	This code was modified for the last time on: 12/12/2014 21:00 UTC+1
*/

#include <3ds.h>
#include <stdio.h>
#include <citro2d.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 240


struct Player 
{
	float v1x,v1y,v2x,v2y,v3x,v3y;
	float moveX, moveY;
	u32 Color;
};
void SetPlayer(struct Player *player);
void DrawPlayer(struct Player *player);

struct Enemy
{
	float v1x,v1y,v2x,v2y,v3x,v3y;
	float moveX, moveY;
	float enemyCollider[2];
	u32 Color;
};

void SetEnemy(struct Enemy *enemy);
void DrawEnemy(struct Enemy *enemy);

int GenerateRandomInt(int min, int max);


int main(int argc, char **argv)
{
	
		
	//colors
	u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
	u32 clrClear = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);
	u32 clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	u32 clrBlack  = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
	
	float xMove;
	
	//initialize Player
	struct Player MainPlayer;
	SetPlayer(&MainPlayer);
	
	//initialize Enemy
	struct Enemy Enemy;
	SetEnemy(&Enemy);
	
	
	int MainScore;
		void ShowMeSomething(const char *text)
	{
		consoleInit(GFX_BOTTOM, NULL);
		printf("\x1b[16;22H%d %s",MainScore, text);
		printf("\x1b[9;5HSuper Vertices Shooter");
		gfxFlushBuffers();
		gfxSwapBuffers();
	}
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	
	consoleInit(GFX_BOTTOM, NULL);
	
	
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	
	
	int enemyMove;
	int enemyVerticleY;
	int RandomEnemyXPosition = GenerateRandomInt(50, SCREEN_WIDTH-100);
	int PlayerVerticle = SCREEN_HEIGHT - 25;

	//PlayerBullet
	int PlayerBulletXPos;
	int PlayerBulletYPos;
	bool BulletExist= false;
	// Main loop
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START) break; // break in order to return to hbmenu

		if(kDown & KEY_A)
		{
			ShowMeSomething("A");
		}
		if(kDown & KEY_B)
		{
			ShowMeSomething("B");
		}
		if(kHeld & KEY_RIGHT)
		{
			MainPlayer.moveX+=5;
		}
		if(kHeld & KEY_LEFT)
		{
			MainPlayer.moveX -=5;
		}
		if(kHeld & KEY_DOWN)
		{
			// ShowMeSomething("Down");
		}
		ShowMeSomething("Score");
		printf("%f", Enemy.moveY);
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);
		
		//player
		DrawPlayer(&MainPlayer);

		//enemy
		// C2D_DrawTriangle(RandomEnemyXPosition,enemyMove, clrRed,
		// RandomEnemyXPosition-15, enemyMove-15, clrRed,
		// RandomEnemyXPosition+15, enemyMove-15, clrRed, 1);
		DrawEnemy(&Enemy);
		Enemy.moveY +=3;
		
		C2D_DrawRectangle(SCREEN_WIDTH - 50, 0, 0, 50, 50, clrRed, clrRed, clrRed, clrRed);
		

		if(!BulletExist)
		{
			PlayerBulletYPos=PlayerVerticle-2;
			PlayerBulletXPos = xMove;
		}
		else
		{
			PlayerBulletYPos-=20;

			//Bullet Behaviour
					if(SCREEN_WIDTH/2-10+PlayerBulletXPos >= RandomEnemyXPosition-15 && SCREEN_WIDTH/2-10+PlayerBulletXPos <= RandomEnemyXPosition+15)
		{
			if(PlayerBulletYPos <= enemyMove)
			{
				BulletExist = false;
				MainScore+=1;
				enemyMove = 0;
				RandomEnemyXPosition = GenerateRandomInt(50, SCREEN_WIDTH-100);
			}
		}
		}
		if(PlayerBulletYPos <= 0)
		{
			BulletExist= false;
		}

		//Bullet behaviour

		//bullet
		C2D_DrawTriangle(SCREEN_WIDTH/2-12.5+PlayerBulletXPos, PlayerBulletYPos+5, clrBlack, 
			SCREEN_WIDTH/2-20+PlayerBulletXPos,  PlayerBulletYPos+15, clrBlack,
			SCREEN_WIDTH/2+PlayerBulletXPos-5, PlayerBulletYPos+15, clrBlack, 0);

		
		if(enemyMove >= SCREEN_HEIGHT)
		{
			enemyMove= 0;
			RandomEnemyXPosition = GenerateRandomInt(50, SCREEN_WIDTH-100);
			MainScore-=1;
		}
					if(kDown & KEY_A)
					{
						//BULLET
						BulletExist = true;
						// MainScore+=1;
						// enemyMove = 0;
						// RandomEnemyXPosition = GenerateRandomInt(50, SCREEN_WIDTH-100);
					}
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

void SetPlayer(struct Player *player)
{
	player->v1x = SCREEN_WIDTH/2-12.5+player->moveX;
	player->v1y = SCREEN_HEIGHT - 25;
	player->v2x = SCREEN_WIDTH/2-25+player->moveX;
	player->v2y = SCREEN_HEIGHT;
	player->v3x = SCREEN_WIDTH/2+player->moveX;
	player->v3y = SCREEN_HEIGHT;
	player->Color = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
	player->moveX = 0;
	player->moveY = 0;
};

void DrawPlayer(struct Player *player)
{
	C2D_DrawTriangle(player->v1x+player->moveX, player->v1y, player->Color, 
			player->v2x+player->moveX,  player->v2y, player->Color,
			player->v3x+player->moveX, player->v3y, player->Color, 1);		
};

void SetEnemy(struct Enemy *enemy)
{
	int randomEnemyX = GenerateRandomInt(15, SCREEN_WIDTH-15);
	enemy->v1x = randomEnemyX;
	enemy->v1y =0;
	enemy->v2x = randomEnemyX-15;
	enemy->v2y = -15;
	enemy->v3x = randomEnemyX+15;
	enemy->v3y = -15;
	enemy->Color = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	enemy->moveX = 0;
	enemy->moveY = 0;
}

void DrawEnemy(struct Enemy *enemy)
{
	C2D_DrawTriangle(enemy->v1x,enemy->v1y+enemy->moveY,enemy->Color,
	enemy->v2x,enemy->v2y+enemy->moveY,enemy->Color,
	enemy->v3x, enemy->v3y+enemy->moveY,enemy->Color,1);
}