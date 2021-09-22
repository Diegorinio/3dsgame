#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

typedef struct Bullet
{
    C2D_Sprite *sprite;
    float posX, posY;
    float moveX, moveY;
    float CollidersX[2];
    float ColliderY;
};

void SetBullet(struct Bullet *bullet, struct Player *player)
{
    bullet->posX = player->PlayerCollidersX[0]+player->width;
    bullet->posY = player->posY;
    bullet->moveX = player->posX;
    bullet->moveY = player->moveY;
    bullet->CollidersX[0] = bullet->posX -2;
    bullet->CollidersX[1] = bullet->posX +2;
    bullet->ColliderY = bullet->posX+2;
}

void BulletCheckPosition(struct Bullet *bullet)
{
    bullet->ColliderY = bullet->posX + 2 + bullet->moveY;
}

void DrawBullet(struct Bullet *bullet)
{
    C2D_SpriteSetPos(bullet->sprite, bullet->posX, bullet->posY + bullet->moveY);
    C2D_DrawSprite(bullet->sprite);
}

void moveBullet(struct Bullet *bullet, float bulletMoveDirSpeed)
{
    bullet->moveY += bulletMoveDirSpeed;
}