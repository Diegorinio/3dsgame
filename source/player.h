#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 240

struct Player 
{
	float v1x,v1y,v2x,v2y,v3x,v3y;
	float moveX, moveY;
	float PlayerCollidersX[2];
	float PlayerCollidersY;
	u32 Color;
};

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
	player->PlayerCollidersX[0] = player->v2x;
	player->PlayerCollidersX[1] = player->v3x;
	player->PlayerCollidersY = player->v1y;
};

void PlayerCheckPosition(struct Player *player)
{
	player->PlayerCollidersX[0] = player->v2x+player->moveX;
	player->PlayerCollidersX[1] = player->v3x+player->moveX;
}

void DrawPlayer(struct Player *player)
{
	C2D_DrawTriangle(player->v1x+player->moveX, player->v1y, player->Color, 
			player->v2x+player->moveX,  player->v2y, player->Color,
			player->v3x+player->moveX, player->v3y, player->Color, 1);		
};