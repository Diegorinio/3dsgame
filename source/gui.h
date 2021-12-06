#include "colors.h"

static C2D_TextBuf staticTextBuf;
static C2D_Text Txt;
static C2D_Text ScoreText;
static C2D_Text Message;
// static void DrawMenu(int score)
// {
//     char scr[] = "SCore";
//     sprintf(scr, "%d", score);
//     staticTextBuf = C2D_TextBufNew(128);
//     C2D_TextParse(&Txt, staticTextBuf, scr);
//     C2D_TextOptimize(&Txt);
//     C2D_DrawText(&Txt, 1, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1.0f, 1.0f, 1.0f);
// }

static void DrawGameScoreAndHelth(int score,struct Player *player)
{
    //draw score element
    char drawScore[] = "";
    sprintf(drawScore, "%d", score);
    staticTextBuf = C2D_TextBufNew(128);
    C2D_TextParse(&ScoreText, staticTextBuf, drawScore);
    C2D_TextOptimize(&ScoreText);
    C2D_DrawText(&ScoreText, 1, SCREEN_WIDTH/2-50, SCREEN_HEIGHT/2, 1, 1,1);

    //health system
    int x= 1;
    for(x;x<=player->PlayerHP;x++)
    {
        C2D_DrawRectangle(50+x*10,5,1,5,5,RED,RED,RED,RED);
    }
    // C2D_DrawRectangle(50,5,1,50,50,RED,RED,RED,RED);
}

// static void DrawMainMenu()
// {
//     C2D_SceneBegin(top);
// 	C2D_TargetClear(top, WHITE);
//     DrawTextOnScreen("Colors Mania\n 1.0", 100,50);

//     C2D_SceneBegin(bottom);
// 	C2D_TargetClear(bottom, WHITE);
//     DrawTextOnScreen("Press START", 100, 80);
// }

static void DrawGameOverScreen()
{
    char GameOver[] = "Game Over";
    staticTextBuf = C2D_TextBufNew(128);
    C2D_TextParse(&Message, staticTextBuf, GameOver);
    C2D_TextOptimize(&Message);
    C2D_DrawText(&Message, 1, 50, 50, 1,1,1);
}

static void DrawMenu()
{
    char title[] = "Crazy Colors";
    staticTextBuf = C2D_TextBufNew(128);
    C2D_TextParse(&Message, staticTextBuf, title);
    C2D_TextOptimize(&Message);
    C2D_DrawText(&Message, 1, 50, SCREEN_HEIGHT/2,1,2,2);
}
static void DrawTextOnScreen(char text[], float posX, float posY, float scale)
{
    char Text[] = "";
    strcpy(Text, text);
    staticTextBuf = C2D_TextBufNew(128);
    C2D_TextParse(&Message, staticTextBuf, Text);
    C2D_TextOptimize(&Message);
    C2D_DrawText(&Message, 1, posX, posY, 1,scale,scale);
}