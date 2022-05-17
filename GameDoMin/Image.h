#ifndef IMAGE_H_INCLUDE
#define IMAGE_H_INCLUDE

#include "Common_Function.h"

class Image
{
public:
    Image();
    ~Image();
    void Show();
    bool loadImage(string str);
    void SetRect(const int &x, const int &y, const int &width, const int &height);
    SDL_Rect GetRect() { return rect; }
    SDL_Surface *GetImage() { return gImage; }

private:
    SDL_Surface *gImage;
    SDL_Rect rect;
};

#endif