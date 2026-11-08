#include "layout.h"
#include "shapes.h"
#include "input_events.h"
#include "overlay.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include "overlay.h"
#include "fonts_only.h"

const struct layout *current_layout;

typedef struct ui_crop {
    int sx, sy, sw, sh;     /* rectangle inside ui_atlas.png */
};
const struct ui_crop ui_theme[] = {
{0, 0, 100, 200},
{0, 0, 100, 200},
{0, 0, 100, 200}, };

static void create_button(const struct element *e)
{
    //printf("(%s) ----- pointer --> %p \n",__func__, (void*)e);
    //printf("(%s) Element type: Button\n",__func__);
    // 1. Render the button: rounded rect + border + label
    char *color = "#665544";
    if (e->color[0] == '#') {
        //printf("(%s) e->color: %s \n", __func__, e->color);
        color = e->color;
    }
    //printf("(%s) color: %s \n", __func__, color);
    //draw_rounded_rect(e->x, e->y, e->w, e->h, 20, color);
    software_blit(700, 200, e->w, e->h, e->x, e->y);
    draw_text(e->label, e->x + 10 , e->y + 20, "#FFFFFF", 1);

    //printf("(%s) ----- element pointer for blit --> %p \n",__func__, (void*)e);
    //add_to_blit_list("button", e);

//    sleep(3);
    // 3. add Touch area
    //printf("(%s) clickable: %d \n", __func__, e->clickable);
    if (e->clickable == 1) {
        struct touch_area area = {
            .id      = e->id,
            .x       = e->x,
            .y       = e->y,
            .w       = e->w,
            .h       = e->h,
            .enabled = 1,
        };  
        strncpy(area.action, e->action, sizeof(area.action) - 1);
        //printf("(%s) ----- pointer --> %p \n",__func__, (void*)&area);
        touch_add_area(&area);
    }  
}

//static void create_textview(const struct layout_element *e)
//{
    // Draw rectangle with border, draw text
    // No touch area text views aren't clickable
    // (unless you later add clickable textviews, then register)
//}


void refresh_layout() {
    printf("(%s) ----- current layout pointer --> %p \n",__func__, (void*)current_layout);
    printf("(%s) Layout name: %s \n", __func__, current_layout->name);
    create_layout(current_layout);
}


void create_layout(const struct layout *layout) {
//    printf("(%s) ----- pointer --> %p \n",__func__, (void*)layout);
    touch_clear_areas();
    prepare_canvas();
    int len = layout->count;
//    printf("(%s) Layout name: %s \n", __func__, layout->name);
//    printf("(%s) Elements No: %d \n", __func__, layout->count);
    current_layout = layout;
    for  (int i = 0; i < len; i++) {
        const struct element *e = &layout->elements[i];
        const struct ui_crop *s = &ui_theme[e->type];
//        printf("\n----------\n(%s) action:  %s \n", __func__, e->action);
        switch (e->type) {
//            case ELEM_BACKGROUND: create_background(e); break;
//            case ELEM_STATIC:     create_static(e);     break;
//            case ELEM_LABEL:      create_label(e);      break;
//            case ELEM_TEXTVIEW:   create_textview(e);   break;
            case ELEM_BUTTON:     create_button(e);     break;
//            case ELEM_CHECKBOX:   create_checkbox(e);   break;
//            case ELEM_RADIO:      create_radio(e);      break;
//            case ELEM_SLIDER:     create_slider(e);     break;

            default:
                printf("(%s) unknown element type %d\n", __func__, e->type);
                break;
      }  // swtch
    }  // for 
//    printf("(%s) ----- BLIT -----\n", __func__);
//    blit_now();
    display_canvas();
}

void execute(int id) {
    printf("(%s) ----- current --> %p \n",__func__, (void*)current_layout);
    int len = current_layout->count;
    printf("(%s) Layout name: %s \n", __func__, current_layout->name);
    for  (int i = 0; i < len; i++) {
        const struct element *e = &current_layout->elements[i];
        if (e->id == id) {
            printf("(%s) Found element %d action %s\n", __func__, e->id, e->action);    
            if (e->on_click) {
                printf("run\n");
                e->on_click(e->data);
            }
        }
    }
}

