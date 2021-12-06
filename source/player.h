#include "colors.h"

struct Player 
{
	int PlayerHP;
	C2D_Sprite *sprite;
	float width, height;
	float posX, posY;
	float moveX, moveY;
	float PlayerCollidersX[2];
	float PlayerColliderY;
	float PlayerSpeed;
};

void SetPlayer(struct Player *player)
{
	player->PlayerHP = 3;
	player->PlayerSpeed = 3;
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
}

void DrawPlayer(struct Player *player)
{
	C2D_SpriteSetPos(player->sprite, player->posX, player->posY);
	C2D_DrawSprite(player->sprite);	
}

void PlayerLoseHealth(struct Player *player)
{
	player->PlayerHP-=1;
}

void PlayerSetHealth(struct Player *player, int hp)
{
	player->PlayerHP = hp;
}

void MovePlayerX(struct Player *player, float speed)
{
    player->moveX += speed;
}

void MovePlayerY(struct Player *player)
{
	player->moveY += player->PlayerSpeed;
}