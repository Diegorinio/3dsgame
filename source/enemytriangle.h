#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

struct TriEnemy
{
	float v1x,v1y,v2x,v2y,v3x,v3y;
	float RandomEnemyXPosition;
	float moveX, moveY;
	float EnemyCollidersX[2]; 
	float EnemyCollidersY;
	u32 Color;
};

void TriSetEnemy(struct TriEnemy *enemy)
{
	int randomEnemyX = GenerateRandomInt(80, SCREEN_WIDTH);
	enemy->RandomEnemyXPosition = randomEnemyX;
	enemy->v1x = enemy->RandomEnemyXPosition;
	enemy->v1y =0;
	enemy->v2x = enemy->RandomEnemyXPosition-10;
	enemy->v2y = -15;
	enemy->v3x = enemy->RandomEnemyXPosition+10;
	enemy->v3y = -15;
	enemy->Color = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	enemy->moveX = 0;
	enemy->moveY = 0;
	enemy->EnemyCollidersX[0] = enemy->v2x;
	enemy->EnemyCollidersX[1] = enemy->v3x;
	enemy->EnemyCollidersY = enemy->v1y;
}

void TriDrawEnemy(struct TriEnemy *enemy)
{
	//draw player
	C2D_DrawTriangle(enemy->v1x,enemy->v1y,enemy->Color,
	enemy->v2x,enemy->v2y+enemy->moveY,enemy->Color,
	enemy->v3x, enemy->v3y+enemy->moveY,enemy->Color,0);
}

void TriEnemyCheckCollisions(struct TriEnemy *enemy)
{
		//update enemy position
	enemy->v1y = enemy->moveY;
	enemy->EnemyCollidersY = enemy->v1y;

	if(enemy->EnemyCollidersY >= SCREEN_HEIGHT+10)
	{
		enemy->moveY = -15;
		TriSetEnemy(enemy);
	}
}

bool TriEnemyCheckCollisionsWithPlayer(struct TriEnemy *enemy, struct Player *player)
{
	if(player->PlayerCollidersX[0] >= enemy->EnemyCollidersX[0] && player->PlayerCollidersX[1] <= enemy->EnemyCollidersX[1])
	{
		if(player->PlayerCollidersY <= enemy->EnemyCollidersY)
		{
			return true;
		}
		return false;
	}
	return false;
}