#include "Common_Function.h"

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL; // bề mặt của cửa sổ
SDL_Surface *(imageNumber[11][2]);
SDL_Surface *domin = NULL;
SDL_Surface *house = NULL;
SDL_Surface *win = NULL;
SDL_Surface *lose = NULL;
SDL_Surface *huongDan = NULL;
SDL_Surface *gameDifficulry = NULL;
SDL_Surface *trong = NULL;
SDL_Surface *soundOff = NULL;
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
    SDL_FreeSurface(house);
    house = NULL;
    SDL_FreeSurface(domin);
    domin = NULL;
    SDL_FreeSurface(huongDan);
    huongDan = NULL;
    SDL_FreeSurface(gameDifficulry);
    gameDifficulry = NULL;
    SDL_FreeSurface(win);
    win = NULL;
    SDL_FreeSurface(lose);
    lose = NULL;
    SDL_FreeSurface(trong);
    trong = NULL;
    SDL_FreeSurface(soundOff);
    soundOff = NULL;
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            SDL_FreeSurface(imageNumber[i][j]);
            imageNumber[i][j] = NULL;
        }
    }
    Mix_FreeChunk(gSoundBomb);
    gSoundBomb = NULL;
    for (int i = 0; i < 3; i++)
    {
        Mix_FreeChunk(gSoundClick[i]);
        gSoundClick[i] = NULL;
    }
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    Mix_CloseAudio();
    SDL_Quit();
}
bool SDLCommonFunction::loadMedia()
{
    bool success = true;
    string path;
    ifstream file;
    file.open("file_image.txt");
    if (!file)
    {
        cout << "Failed to open file." << endl;
    }
    else
    {
        for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                file >> path;
                imageNumber[i][j] = SDLCommonFunction::loadImage(path);
                if (imageNumber[i][j] == NULL)
                {
                    success = false;
                    cout << "Failed to load image: " << path << endl;
                }
            }
        }
        file >> path;
        win = SDLCommonFunction::loadImage(path);
        file >> path;
        lose = SDLCommonFunction::loadImage(path);
        file >> path;
        domin = SDLCommonFunction::loadImage(path);
        file >> path;
        house = SDLCommonFunction::loadImage(path);
        file >> path;
        huongDan = SDLCommonFunction::loadImage(path);
        file >> path;
        gameDifficulry = SDLCommonFunction::loadImage(path);
        file >> path;
        trong = SDLCommonFunction::loadImage(path);
        file >> path;
        soundOff = SDLCommonFunction::loadImage(path);
        // if(domin!=NULL) cout<<"huy ";
    }
    return success;
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