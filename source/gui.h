#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

static C2D_TextBuf staticTextBuf;
static C2D_Text Txt;

static void initMenu()
{
    staticTextBuf = C2D_TextBufNew(128);
    C2D_TextParse(&Txt, staticTextBuf, "Test");
    C2D_TextOptimize(&Txt);
}

static void DrawMenu(int score)
{
    char scr[] = "";
    sprintf(scr, "%d", score);
    staticTextBuf = C2D_TextBufNew(128);
    C2D_TextParse(&Txt, staticTextBuf, scr);
    C2D_TextOptimize(&Txt);
    C2D_DrawText(&Txt, 15, 15.0f, 8.0f, 1.0f, 1.0f, 1.0f);
}

static void ShowMeInfo(int score)
{
	consoleInit(GFX_BOTTOM, NULL);
	printf("\x1b[15;14HScore: %d",score);
	printf("\x1b[12;10HSuper Vertices Shooter");
	gfxFlushBuffers();
	gfxSwapBuffers();
}