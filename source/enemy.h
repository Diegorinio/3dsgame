#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

struct Enemy
{
	C2D_Sprite *sprite;
	char *color;
	float posX, posY;
	float width, height;
	float RandomEnemyXPosition;
	float moveX, moveY;
	float EnemyCollidersX[2]; 
	float EnemyColliderY;
};

void SetEnemy(struct Enemy *enemy)
{
	int randomEnemyX = GenerateRandomInt(80, SCREEN_WIDTH);
	enemy->RandomEnemyXPosition = randomEnemyX;
	enemy->posX = enemy->RandomEnemyXPosition;
	enemy->posY = 0;
	enemy->width = 1;
	enemy->height = 7;
	enemy->moveX = 0;
	enemy->moveY = 0;
	enemy->EnemyCollidersX[0] = enemy->posX;
	enemy->EnemyCollidersX[1] = enemy->posX + enemy->width;
	enemy->EnemyColliderY = enemy->posY + enemy->height;
}

void RespawnEnemy(struct Enemy *enemy, C2D_Sprite *sprite)
{
	int randomEnemyX = GenerateRandomInt(80, SCREEN_WIDTH);
	enemy->RandomEnemyXPosition = randomEnemyX;
	enemy->posX = enemy->RandomEnemyXPosition;
	enemy->posY = 0;
	enemy->moveY = 0;
	enemy->sprite = sprite;
	enemy->EnemyCollidersX[0] = enemy->posX;
	enemy->EnemyCollidersX[1] = enemy->posX + enemy->width;
	enemy->EnemyColliderY = enemy->posY + enemy->height;

}

void DrawEnemy(struct Enemy *enemy)
{
	//draw player
	// C2D_DrawTriangle(enemy->v1x,enemy->v1y,enemy->Color,
	// enemy->v2x,enemy->v2y+enemy->moveY,enemy->Color,
	// enemy->v3x, enemy->v3y+enemy->moveY,enemy->Color,0);
	C2D_SpriteSetPos(enemy->sprite, enemy->posX, enemy->posY + enemy->moveY);
	C2D_DrawSprite(enemy->sprite);
}

void EnemyCheckCollisions(struct Enemy *enemy)
{
		//update enemy position
	enemy->posY = enemy->moveY;
	enemy->EnemyColliderY = enemy->posY;
}

bool EnemyCheckCollisionsWithPlayer(struct Enemy *enemy, struct Player *player)
{
	if(player->PlayerCollidersX[0] < enemy->EnemyCollidersX[0] && player->PlayerCollidersX[1] > enemy->EnemyCollidersX[1])
	{
		if(enemy->EnemyColliderY >= 100)
		{
			return true;
		}
		return false;
	}
	return false;
}