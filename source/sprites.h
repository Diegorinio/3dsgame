#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define MAX_SPRITES 10;

typedef struct
{
	C2D_Sprite spr;
	float dx, dy; // velocity
} Sprite;

C2D_SpriteSheet spriteSheet;
Sprite sprites[3];
void initSprites(struct Player *player, struct Enemy *enemy)
{
	size_t numImages = C2D_SpriteSheetCount(spriteSheet);

	for(size_t i = 0; i< numImages; i++)
	{
		Sprite* sprite = &sprites[i];
		C2D_SpriteFromSheet(&sprite->spr, spriteSheet, i);
		C2D_SpriteSetCenter(&sprite->spr, 0.5f, 0.5f);
		C2D_SpriteSetPos(&sprite->spr, SCREEN_WIDTH/2, SCREEN_HEIGHT-25);
	}
	player->sprite = &sprites[0].spr;
	enemy->sprite = &sprites[2].spr;
}

void DrawSprite(int id)
{
    C2D_DrawSprite(&sprites[id].spr);
}

void MoveSprite(int spriteID)
{
	C2D_SpriteSetPos(&sprites[spriteID].spr, 100, 100);
}