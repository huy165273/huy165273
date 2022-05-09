#include "Common_Function.h"

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL; // bề mặt của cửa sổ

TTF_Font *gFontText = NULL;
SDL_Surface *fontText = NULL;
Mix_Chunk *gSoundClick[3];
Mix_Chunk *gSoundBomb = NULL;
Mix_Chunk *gSoundWin = NULL;
Mix_Chunk *gSoundLose = NULL;

bool SDLCommonFunction::init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO < 0))
    {
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("Do Min", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
            if (gScreenSurface == NULL)
            {
                success = false;
            }
        }
    }
    if (TTF_Init() == -1)
    {
        success = false;
    }
    gFontText = TTF_OpenFont("US101.TTF", 35);
    if (gFontText == NULL)
    {
        success = false;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        success = false;
    }

    // read file wav audio
    gSoundClick[0] = Mix_LoadWAV("sound/mouse-click.wav");
    gSoundClick[1] = Mix_LoadWAV("sound/mixkit-arcade.wav");
    gSoundClick[2] = Mix_LoadWAV("sound/mixkit-retro.wav");
    gSoundBomb = Mix_LoadWAV("sound/Bomb.wav");
    gSoundWin = Mix_LoadWAV("sound/sound-win.wav");
    gSoundLose= Mix_LoadWAV("sound/sound-lose.wav");
    if ( gSoundBomb == NULL || gSoundWin == NULL || gSoundLose==NULL)
    {
        success = false;
    }
    return success;
}
void SDLCommonFunction::close()
{
    Mix_FreeChunk(gSoundBomb);
    gSoundBomb = NULL;
    for (int i = 0; i < 3; i++)
    {
        Mix_FreeChunk(gSoundClick[i]);
        gSoundClick[i] = NULL;
    }
    SDL_FreeSurface(gScreenSurface);
    gScreenSurface = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    Mix_CloseAudio();
    SDL_Quit();
}

SDL_Surface *SDLCommonFunction::loadImage(string path)
{
    SDL_Surface *optimizeSurface = NULL;
    SDL_Surface *loadSurface = SDL_LoadBMP(path.c_str());
    if (loadSurface != NULL)
    {
        optimizeSurface = SDL_ConvertSurface(loadSurface, gScreenSurface->format, 0);
        SDL_FreeSurface(loadSurface);
    }
    else
    {
        cout << "Failed to load surface." << endl;
    }
    return optimizeSurface;
}
void SDLCommonFunction::showImage(SDL_Surface *image, const int &x, const int &y, const int &h, const int &w)
{
    SDL_Rect stretch;
    stretch.x = x;
    stretch.y = y;
    stretch.h = h;
    stretch.w = w;
    SDL_BlitScaled(image, NULL, gScreenSurface, &stretch);
}
void SDLCommonFunction::showText(int timeGame, const int &x, const int &y)
{
    SDL_Rect stretch;
    stretch.x = x;
    stretch.y = y;
    string strTime = to_string(timeGame);
    fontText = TTF_RenderText_Solid(gFontText, strTime.c_str(), {255, 0, 0});
    SDL_BlitSurface(fontText, NULL, gScreenSurface, &stretch);
}
void SDLCommonFunction::showSound(Mix_Chunk *gSoundl, const bool &checkSound){
    if (checkSound)
    {
        Mix_PlayChannel(-1, gSoundl, 0);
    }
}