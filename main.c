#include "allegroDisplay.h"
#include "allegroUtil.h"
#include "asteroidsLib.h"
#include "allegroSprites.h"
#include "allegroFx.h"
#include "allegroKeyboard.h"
#include "allegroAudio.h"

int main(){
   mustInit(al_init(), "allegro");
    mustInit(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    mustInit(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    mustInit(queue, "queue");

    disp_init();

    audio_init();

    mustInit(al_init_image_addon(), "image");
    sprites_init();

    hud_init();

    mustInit(al_init_primitives_addon(), "primitives");

    mustInit(al_install_audio(), "audio");
    mustInit(al_init_acodec_addon(), "audio codecs");
    mustInit(al_reserve_samples(16), "reserve samples");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    keyboard_init();
    fx_init();
    shots_init();
    ship_init();
    aliens_init();
    stars_init();

    frames = 0;
    score = 0;

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                fx_update();
                shots_update();
                stars_update();
                ship_update();
                aliens_update();
                hud_update();

                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                redraw = true;
                frames++;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        keyboard_update(&event);

        if(redraw && al_is_event_queue_empty(queue))
        {
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0,0,0));

            stars_draw();
            aliens_draw();
            shots_draw();
            fx_draw();
            ship_draw();

            hud_draw();

            disp_post_draw();
            redraw = false;
        }
    }

    sprites_deinit();
    hud_deinit();
    audio_deinit();
    disp_deinit();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

     return 0;

}