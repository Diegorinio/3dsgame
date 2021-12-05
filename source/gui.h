#include "colors.h"

static C2D_TextBuf staticTextBuf;
static C2D_Text Txt;
static C2D_Text ScoreText;

static void initMenu()
{
    staticTextBuf = C2D_TextBufNew(128);
    C2D_TextParse(&Txt, staticTextBuf, "Test");
    C2D_TextOptimize(&Txt);
}

// static void DrawMenu(int score)
// {
//     char scr[] = "SCore";
//     sprintf(scr, "%d", score);
//     staticTextBuf = C2D_TextBufNew(128);
//     C2D_TextParse(&Txt, staticTextBuf, scr);
//     C2D_TextOptimize(&Txt);
//     C2D_DrawText(&Txt, 1, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 1.0f, 1.0f, 1.0f);
// }

static void DrawGameGUI(int score)
{
    char drawScore[] = "";
    sprintf(drawScore, "%d", score);
    staticTextBuf = C2D_TextBufNew(128);
    C2D_TextParse(&ScoreText, staticTextBuf, drawScore);
    C2D_TextOptimize(&ScoreText);
    C2D_DrawText(&ScoreText, 1, SCREEN_WIDTH/2-50, SCREEN_HEIGHT/2, 1, 1,1);
}

// static void DrawTextOnScreen(char* text[], float posX, float posY)
// {
//     C2D_Text *ScreenText;
//     char Text[] = "";
//     strcpy(Text, text);
//     C2D_TextParse(&ScreenText, staticTextBuf, Text);
//     C2D_TextOptimize(&ScreenText);
//     C2D_DrawText(&ScreenText, 1, posX, posY, 1,1,1);
// }