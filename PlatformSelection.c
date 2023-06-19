#include<allegro5/allegro5.h>
#include<allegro5/allegro_image.h>





int RightImageInPlatform_x(int x){
     x = x + 50;

    return x;
}

int LeftImageInPlatform_x(int x){
     x = x - 50;

    return x;
}

int UPImageInPlatform_y(int y){
    y =  y +50;
    return y;
}

int DownImageInPlatform_y(int y){
    y =  y - 50;
    return y;
}


