#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 240

struct Enemy
{
	float v1x,v1y,v2x,v2y,v3x,v3y;
	float RandomEnemyXPosition;
	float moveX, moveY;
	float EnemyCollidersX[2]; 
	float EnemyCollidersY;
	u32 Color;
};

void SetEnemy(struct Enemy *enemy)
{
	int randomEnemyX = GenerateRandomInt(80, SCREEN_WIDTH-80);
	enemy->RandomEnemyXPosition = randomEnemyX;
	enemy->v1x = enemy->RandomEnemyXPosition;
	enemy->v1y =0;
	enemy->v2x = enemy->RandomEnemyXPosition-15;
	enemy->v2y = -15;
	enemy->v3x = enemy->RandomEnemyXPosition+15;
	enemy->v3y = -15;
	enemy->Color = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	enemy->moveX = 0;
	enemy->moveY = 0;
	enemy->EnemyCollidersX[0] = enemy->v2x;
	enemy->EnemyCollidersX[1] = enemy->v3x;
	enemy->EnemyCollidersY = enemy->v1y;
}

void DrawEnemy(struct Enemy *enemy)
{

	//draw player
	C2D_DrawTriangle(enemy->v1x,enemy->v1y,enemy->Color,
	enemy->v2x,enemy->v2y+enemy->moveY,enemy->Color,
	enemy->v3x, enemy->v3y+enemy->moveY,enemy->Color,1);
}

void EnemyCheckCollisions(struct Enemy *enemy)
{
		//update enemy position
	enemy->v1y = enemy->moveY;
	enemy->EnemyCollidersY = enemy->v1y;

	if(enemy->EnemyCollidersY >= SCREEN_HEIGHT+10)
	{
		enemy->moveY = -15;
		SetEnemy(enemy);
	}
}

bool EnemyCheckCollisionsWithPlayer(struct Enemy *enemy, struct Player *player)
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