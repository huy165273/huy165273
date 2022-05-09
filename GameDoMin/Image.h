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

extern Image(imageNumber[11][2]);
extern Image domin;
extern Image house;
extern Image win;
extern Image lose;
extern Image huongDan;
extern Image gameDifficulry;
extern Image trong;
extern Image soundOff;
extern Image batdauchoi;
extern Image huongdanx;
extern Image de;
extern Image trungbinh;
extern Image kho;
extern Image ratkho;
#endif