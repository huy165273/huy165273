#include "Image.h"

Image(imageNumber[11][2]);
Image domin;
Image house;
Image win;
Image lose;
Image huongDan;
Image gameDifficulry;
Image trong;
Image soundOff;
Image batdauchoi;
Image huongdanx;
Image de;
Image trungbinh;
Image kho;
Image ratkho;


Image::Image()
{
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
    gImage=NULL;
}
Image::~Image(){
    if(gImage!=NULL){
        SDL_FreeSurface(gImage);
        gImage=NULL;
    }
}
void Image::SetRect(const int &x, const int &y, const int &width, const int &height) {
        rect.x=x;
        rect.y=y;
        rect.w=width;
        rect.h=height;
    }
bool Image::loadImage(string str){
    gImage=SDLCommonFunction::loadImage(str);
    if(gImage==NULL){
       return false;
    }
    return true;
}
void Image::Show(){
    if(gImage!=NULL){
        SDLCommonFunction::showImage(gImage, rect.x, rect.y, rect.h, rect.w);
    }
}
