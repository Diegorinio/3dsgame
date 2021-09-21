#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

struct Player 
{
	C2D_Sprite *sprite;
	float width, height;
	float posX, posY;
	float moveX, moveY;
	float PlayerCollidersX[2];
	float PlayerCollidersY[2];
	u32 Color;
};

void SetPlayer(struct Player *player)
{
	player->width = 25;
	player->height = 25;
	player->posX = SCREEN_WIDTH/2;
	player->posY = SCREEN_HEIGHT - player->height;
	player->Color = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
	player->moveX = 0;
	player->moveY = 0;
	player->PlayerCollidersX[0] = SCREEN_WIDTH/2 - player->width;
	player->PlayerCollidersX[1] = SCREEN_WIDTH/2 + player->width;
	player->PlayerCollidersY[] = SCREEN_HEIGHT - player->height;
	C2D_SpriteSetPos(player->sprite, SCREEN_WIDTH/2, SCREEN_HEIGHT - player->height);
};

void PlayerCheckPosition(struct Player *player)
{
	player->PlayerCollidersX[0] = player->posX - player->width + player->moveX;
	player->PlayerCollidersX[1] = player->posX + player->width + player->moveX;
	// player->PlayerCollidersX[0] = player->v1x + player->moveX;
	// player->PlayerCollidersX[1] = player->v1x + player->width +player->moveX;
}

void DrawPlayer(struct Player *player)
{
	C2D_SpriteSetPos(player->sprite, player->posX + player->moveX, player->posY);
	C2D_DrawSprite(player->sprite);
	// C2D_DrawRectangle(player->v1x + player->moveX, player->v1y, player->depth, player->width, player->height, player->Color, player->Color, player->Color, player->Color);
	// C2D_DrawTriangle(player->v1x+player->moveX, player->v1y, player->Color, 
	// 		player->v2x+player->moveX,  player->v2y, player->Color,
	// 		player->v3x+player->moveX, player->v3y, player->Color, 1);		
};

void MovePlayer(struct Player *player, float moveDir)
{
        player->moveX += moveDir;
}