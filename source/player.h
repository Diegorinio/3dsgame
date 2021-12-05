#include "colors.h"

struct Player 
{
	C2D_Sprite *sprite;
	float width, height;
	float posX, posY;
	float moveX, moveY;
	float PlayerCollidersX[2];
	float PlayerColliderY;
};

void SetPlayer(struct Player *player)
{
	player->width = 15;
	player->height = 15;
	player->posX = SCREEN_WIDTH/2;
	player->posY = SCREEN_HEIGHT-player->height;
	player->moveX = 0;
	player->moveY = 0;
	player->PlayerCollidersX[0] = player->moveX - player->width;
	player->PlayerCollidersX[1] = player->moveX + player->width;
	player->PlayerColliderY = player->posY + 5;
};

void PlayerCheckPosition(struct Player *player)
{
	player->posX = SCREEN_WIDTH/2 + player->moveX;
	player->PlayerCollidersX[0] = player->posX - player->width;
	player->PlayerCollidersX[1] = player->posX + player->width;
	// player->PlayerCollidersX[0] = player->v1x + player->moveX;
	// player->PlayerCollidersX[1] = player->v1x + player->width +player->moveX;
}

void DrawPlayer(struct Player *player)
{
	C2D_SpriteSetPos(player->sprite, player->posX, player->posY);
	C2D_DrawSprite(player->sprite);
	// C2D_DrawRectangle(player->v1x + player->moveX, player->v1y, player->depth, player->width, player->height, player->Color, player->Color, player->Color, player->Color);
	// C2D_DrawTriangle(player->v1x+player->moveX, player->v1y, player->Color, 
	// 		player->v2x+player->moveX,  player->v2y, player->Color,
	// 		player->v3x+player->moveX, player->v3y, player->Color, 1);		
};

void MovePlayerX(struct Player *player, float moveSpeed)
{
    player->moveX += moveSpeed;
}

void MovePlayerY(struct Player *player, float moveSpeed)
{
	player->moveY += moveSpeed;
}