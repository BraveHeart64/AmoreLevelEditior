#include<allegro5/allegro_image.h>
#include<allegro5/allegro.h>

struct Platforms {
    ALLEGRO_BITMAP *platforms;
    ALLEGRO_BITMAP * orgin_bmp;
    int pos_x; //movese images right or left based on + or -
    int pos_y;  // moves images up or down based on + or -
    int width;
    int height;
    int screen_x;
    int screen_y;
    int rowcounter;
    int endofrows;
    int landobject;
    int land_object_created;



};
 struct Platforms platform;
//int gamelevel[50][50];
