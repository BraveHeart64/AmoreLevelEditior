#include<allegro5/allegro.h>
#include<stdio.h>
#include<allegro5/allegro_color.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include "path.h"
#include "Editor.h"
#include "Appmenu.h"
#include "Platforms.h"
#include"mouse.h"

void InitAllAllegroValue();
void MenuTabeState();
void MenuInterActions(int menustate);
void MousePaint();
char* SetPathGraphics();
void DestroyBitmaps();


struct AppMenu appmenu;
struct Mouse mymouse;


struct window{

    ALLEGRO_DISPLAY* window;

    ALLEGRO_EVENT_QUEUE* que;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER* gc;
    double time_pt; //= 1.0;
    double fps;// = 60.0;

}  surface;





int main(){

    InitAllAllegroValue();


    surface.window = al_create_display(1200,800);
    al_set_window_title(surface.window,"RyanAmoreSoftware MapEditior");
    al_set_display_icon(surface.window,icon);
    al_set_mouse_cursor(surface.window,ed_mouse);




    al_register_event_source(surface.que,al_get_keyboard_event_source());
    al_register_event_source(surface.que,al_get_mouse_event_source());
    al_register_event_source(surface.que,al_get_display_event_source(surface.window));
    al_register_event_source(surface.que,al_get_timer_event_source(surface.gc));



    al_start_timer(surface.gc);

    while(run == 1){

        al_wait_for_event(surface.que,&surface.event);
        switch(surface.event.type){
            case ALLEGRO_EVENT_TIMER:
                // The game logice is here

               if(t_was_pressed[ALLEGRO_KEY_T] && platform.orgin_bmp != 0){
                    t_was_pressed[ALLEGRO_KEY_T] = 0;
                    printf("T");
                    platform.pos_x = RightImageInPlatform_x(platform.pos_x);
                    appmenu.menutabestate = 5;
                    MenuTabeState();



               }
                else if(escape_was_pressed[ALLEGRO_KEY_ESCAPE]){
                    escape_was_pressed[ALLEGRO_KEY_ESCAPE] = 1;
                    printf("esc");
                    run  = 0;
               }

                redraw = 1;
            break;


            case ALLEGRO_EVENT_MOUSE_AXES:
                mymouse.mouse_x = surface.event.mouse.x;
                mymouse.mouse_y = surface.event.mouse.y;

            break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                    mymouse.mouse_button = surface.event.mouse.button;

                   if( mymouse.mouse_x <=29 &&  mymouse.mouse_y <=30){
                            MenuTabeState();

                          // al_show_native_file_dialog(0,file_chooser);
                        //    thepath  = al_get_native_file_dialog_path(file_chooser, 0);
                        //    char* item = thepath;
                   }
                   else if( mymouse.mouse_x <= 150 &&  mymouse.mouse_y <=100 && appmenu.activemenu == 1){
                    appmenu.menutabestate = 3; // new was pressed looad image to paint screen
                    MenuTabeState();
                    //appmenu.menutabestate = 1;

                   }
                   else if( mymouse.mouse_x <= 150 &&  mymouse.mouse_y <=150 && appmenu.activemenu == 1){
                    appmenu.menutabestate = 2; // new was pressed looad image to paint screen
                    MenuTabeState();
                    //appmenu.menutabestate = 1;

                   }
                   else if( mymouse.mouse_x <= 150 &&  mymouse.mouse_y <=250 && appmenu.activemenu == 1){
                    //appmenu.menutabestate = 2; // new was pressed looad image to paint screen
                   // MenuTabeState();
                    //appmenu.menutabestate = 1;

                   }
                   else if(  mymouse.mouse_x >=174 ||  mymouse.mouse_y >= 300){ // mouse_y >=300 resets state menu no longer selected
                    appmenu.menutabestate = 0;
                    appmenu.activemenu = 0;

                   }
                    else if(  mymouse.mouse_x <= 150 &&  mymouse.mouse_y >= 250 &&  mymouse.mouse_y <= 300 && appmenu.activemenu == 1){
                        run = 0;
                   }


            break;


            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                 mymouse.mouse_button = surface.event.mouse.button;
                // once a file is loaded, this method will allow the mouse to add plateforms based on a click


            break;



            case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:

            break;

            case ALLEGRO_EVENT_KEY_DOWN:
                switch(surface.event.keyboard.keycode){
                    case ALLEGRO_KEY_T:
                        t_was_pressed[ALLEGRO_KEY_T] = 1;

                    break;
                    case ALLEGRO_KEY_ESCAPE:
                        escape_was_pressed[ALLEGRO_KEY_ESCAPE] = 2;

                    break;

                }




                case ALLEGRO_KEY_ESCAPE:
                  //  run = 0; // ends on escape

                break;



            break;

            case ALLEGRO_EVENT_KEY_UP:
                switch(surface.event.keyboard.keycode){
                    case ALLEGRO_KEY_T:
                        t_was_pressed[ALLEGRO_KEY_T] = 0;


                    break;
                    case ALLEGRO_KEY_ESCAPE:
                        escape_was_pressed[ALLEGRO_KEY_ESCAPE] = 0;

                    break;

                }




            break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                run = 0;
            break;

        }

        if(redraw == 1 && al_is_event_queue_empty(surface.que)){

             al_clear_to_color(al_map_rgb(135,206,235));
             al_draw_rectangle(700, 50, 600, 150, al_map_rgb(0,0,0),4);
             al_draw_bitmap(menu[appmenu.menutabestate],0,0,0);


             if(platform.platforms !=0){ // keeps program from crashing if a plaform bitmaps has not been loaded
                al_draw_bitmap(platform.platforms,620,90,0);//620
            }

            //al_show_native_file_dialog(0,file_chooser);
          //  thepath  = al_get_native_file_dialog_path(file_chooser, 0);
            //printf("c%", thepath);
            redraw = 0;
            al_flip_display();


        }


    }


    DestroyBitmaps();
    return 0;
}



char* SetPathGraphics(){

    path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_replace_path_component(path,-2,"LevelAssets");
    al_remove_path_component(path, -1);
    thepath = al_path_cstr(path,ALLEGRO_NATIVE_PATH_SEP);

    return thepath;

}

void MenuTabeState(){

    if(appmenu.activemenu == 0){

        appmenu.activemenu = 1;
    }
    else if(appmenu.activemenu == 1 && appmenu.menutabestate == 1){
        appmenu.activemenu = 0;
        appmenu.menutabestate = 0;
        // occur if you click the file menu twice reset
        //menu state

    }

    switch(appmenu.menutabestate){

        case 0:

            if(appmenu.activemenu == 1){
                appmenu.menutabestate = 1;
            }
            else if(appmenu.activemenu == 0){
                appmenu.menutabestate = 0;
            }
            //menu[3] = al_load_bitmap("options.png")

        break;



        case 2:

         al_show_native_file_dialog(0,file_chooser);
         thepath  = al_get_native_file_dialog_path(file_chooser, 0);
         item = thepath;
         // platforms loaded into the program
        //
        if(item != 0){
            platform.orgin_bmp = al_load_bitmap(item);
            platform.platforms = al_create_sub_bitmap(platform.orgin_bmp,platform.pos_x, platform.pos_y, platform.width, platform.height);
        }

         appmenu.menutabestate = 1;



        break;


        case 3: // new case
            printf("Menu state is 3");
            appmenu.menutabestate = 1;

        break;


        case 4:



        break;

        case 5: // changes the item to paint on screen
             if(platform.orgin_bmp != 0){// by 8 go down in y reset x once 36 rest to default value
                    platform.orgin_bmp = al_load_bitmap(item);
                    platform.platforms = al_create_sub_bitmap(platform.orgin_bmp,platform.pos_x, platform.pos_y, platform.width, platform.height);
                    appmenu.menutabestate = 0;
            }

        break;

    }


}


void InitAllAllegroValue(){
    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();
    al_install_joystick();
    al_init_native_dialog_addon();
    appmenu.menutabestate = 0;
    appmenu.activemenu = 0 ;

    platform.platforms = 0;
    platform.orgin_bmp = 0;
    platform.pos_x = 0;
    platform.pos_y = 0;
    platform.width = 50;
    platform.height = 50;



    SetPathGraphics();
    al_change_directory(thepath);
    icon = al_load_bitmap("Ic.png");
    menu[0] = al_load_bitmap("Menutabe.png");
    menu[1] = al_load_bitmap("Menutabestatetwo.png");
    menu[2] = al_load_bitmap("Menutabestatenew.png");
    menu[3] = al_load_bitmap("Menutabestateload.png");
    menu[4] = al_load_bitmap("Menutabestateopen.png");
    menu[5] = al_load_bitmap("Menutabestatesave.png");
    menu[6] = al_load_bitmap("Menutabestatequit.png");
    meun_sprite_sizes[0] = al_load_bitmap("PerPixelMenu.png");
    meun_sprite_sizes[1] = al_load_bitmap("PerPixelMenu50.png");
    meun_sprite_sizes[2] = al_load_bitmap("PerPixelMenu100.png");
    meun_sprite_sizes[3] = al_load_bitmap("PerPixelMenu250.png");
    meun_sprite_sizes[4] = al_load_bitmap("PerPixelMenu1000.png");

     mymouse.mouse_bmp = al_load_bitmap("mouse.png");
    surface.que = al_create_event_queue();
    surface.fps = 1.0;
    surface.time_pt = 60.0;
    surface.gc = al_create_timer(surface.fps/surface.time_pt);
    ed_mouse = al_create_mouse_cursor( mymouse.mouse_bmp,surface.event.mouse.x, surface.event.mouse.y);



    file_chooser = al_create_native_file_dialog(path,"Load A Map","*.png;*.jpg;*.bmp",ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
}


void DestroyBitmaps(){

    al_destroy_display(surface.window);
    al_destroy_bitmap(icon);
    al_destroy_bitmap(menu[0]);
    al_destroy_bitmap(menu[1]);
    al_destroy_bitmap(menu[2]);
    al_destroy_bitmap(menu[3]);
    al_destroy_bitmap(menu[4]);
    al_destroy_bitmap(menu[5]);
    al_destroy_bitmap(menu[6]);

    al_destroy_bitmap(meun_sprite_sizes[0]);
    al_destroy_bitmap(meun_sprite_sizes[1]);
    al_destroy_bitmap(meun_sprite_sizes[2]);
    al_destroy_bitmap(meun_sprite_sizes[3]);
    al_destroy_bitmap(meun_sprite_sizes[4]);
    al_destroy_bitmap( mymouse.mouse_bmp);
    al_destroy_mouse_cursor(ed_mouse);
    al_destroy_native_file_dialog(file_chooser);
    al_destroy_bitmap(platform.orgin_bmp);
    al_destroy_bitmap(gameobjects);
    al_destroy_bitmap(platform.platforms);

}
