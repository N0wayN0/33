#include "utils.h"
#include "layout.h"
#include "app1.h"
#include "overlay.h"
#include "fb_only.h"
#include "utils.h"
#include "input_events.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>

#define BATT_LEVEL "/data/cpp_proj/moje_cpp/main_project/robie/bat_level.sh"
#define FLASH "/data/cpp_proj/moje_cpp/main_project/robie/flash.sh"
//#define BATT_LEVEL "/system/xbin/bateria"
#define POWEROFF "/system/xbin/poweroff"
//#define TEST "/data/cpp_proj/moje_cpp/main_project/robie/vib.sh"
#define IP_ADDRESS "/data/cpp_proj/moje_cpp/main_project/robie/get_ip.sh"
#define VIBRATOR "/sys/class/timed_output/vibrator/enable"
#define BRIGHTNESS "/sys/class/leds/lcd-backlight/brightness"

static void endit() {
    vibrate();
    touch_clear_areas();
    close_ION();
    close_fb();
    close_input();
    printf("\nkoniec\n");
    exit(0);
}
static void kleen3() {
    printf("\n(%s) pictures[3]: set to 0\n",__func__);
    cleanup_pictures(3);
}
static void kleen5() {
    printf("\n(%s) pictures[5]: set to 0\n",__func__);
    cleanup_pictures(5);
}
static void kleenall() {
    printf("\n(%s) All pictures[] will be cleared\n",__func__);
    cleanup_all_pictures();
}

static void getXres() {
    char buf[256];
    refresh_layout();
    snprintf(buf, sizeof(buf), "Xres=%d", getFbXres());
    draw_text(buf,800,20,"#ffffff",1);
    fb_swap();
}

static void getYres() {
    char buf[256];
    refresh_layout();
    snprintf(buf, sizeof(buf), "Yres=%d", getFbYres());
    draw_text(buf,800,20,"#ffffff",1);
    fb_swap();
}

static void set_brightness(int value) {
    printf("\n(%s) Set Brightness %d\n",__func__, value);
    write_int(BRIGHTNESS, value);
}

const struct element layout1[] = { 
    { .id = 1,  .type = ELEM_BACKGROUND, .x = 0,   .y = 0,   .w = 800, .h = 480, .action = "btn_ok", .clickable=1},
    { .id = 2,  .type = ELEM_LABEL,      .x = 20,  .y = 20,  .w = 200, .h = 80, .action = "btn_cancel", .clickable=1 },
    { .id = 3,  .type = ELEM_BUTTON,     .x = 100, .y = 1100, .w = 180, .h = 80,
      .action = "btn_battery", .clickable=1, .on_click=get_battery,
      .color="#00ff00", .label="bateria" },
    { .id = 4,  .type = ELEM_BUTTON,     .x = 100, .y = 1200, .w = 200, .h = 80,
      .action = "btn_getIP", .clickable=1, .on_click=get_ip,
      .color="#33afcc", .label="Get IP" },
    { .id = 5,  .type = ELEM_BUTTON,     .x = 100, .y = 1400, .w = 230, .h = 80,
      .action = "btn_vibrate", .clickable=1, .on_click=vibrate,
      .color="#f34f3c", .label="vibrate" },
    { .id = 6,  .type = ELEM_BUTTON,     .x = 900, .y = 1800, .w = 150, .h = 80,
      .action = "btn_exit", .clickable=1, .on_click=endit,
      .color="#ff0000", .label="EXIT" },
    { .id = 7,  .type = ELEM_BUTTON,     .x = 700, .y = 200, .w = 180, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=show_crop1,
      .color="#ffff00", .label="crop1" },
    { .id = 77,  .type = ELEM_BUTTON,     .x = 900, .y = 200, .w = 180, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=show_crop2,
      .color="#ffff00", .label="crop2" },
    { .id = 8,  .type = ELEM_BUTTON,     .x = 700, .y = 350, .w = 360, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=hide_crop,
      .color="#ffff00", .label="hide and remove" },
    { .id = 9,  .type = ELEM_BUTTON,     .x = 700, .y = 500, .w = 220, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=remove_all_ov,
      .color="#ffff00", .label="unset All" },
    { .id = 10,  .type = ELEM_BUTTON,     .x = 100, .y = 1500, .w = 300, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=kleen3,
      .color="#ef956c", .label="clear slot 3" },
    { .id = 11,  .type = ELEM_BUTTON,     .x = 100, .y = 1600, .w = 300, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=kleen5,
      .color="#ef956c", .label="clear slot 5" },
    { .id = 15,  .type = ELEM_BUTTON,     .x = 100, .y = 1700, .w = 360, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=kleenall,
      .color="#ef956c", .label="clear all slots" },
    { .id = 17,  .type = ELEM_BUTTON,     .x = 100, .y = 1800, .w = 250, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=getXres,
      .color="#72e4ab", .label="get X res" },
    { .id = 18,  .type = ELEM_BUTTON,     .x = 400, .y = 1800, .w = 250, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=getYres,
      .color="#72e4ab", .label="get Y res" },
    { .id = 19,  .type = ELEM_BUTTON,     .x = 100, .y = 900, .w = 150, .h = 120,
      .action = "btn_bad", .clickable=1 },
    { .id = 22,  .type = ELEM_BUTTON,     .x = 1000, .y = 800, .w = 80, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=set_brightness,
      .color="#72e4ab", .label="10", .data=10 },
    { .id = 23,  .type = ELEM_BUTTON,     .x = 1000, .y = 900, .w = 80, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=set_brightness,
      .color="#72e4ab", .label="50", .data=50 },
    { .id = 24,  .type = ELEM_BUTTON,     .x = 1000, .y = 1000, .w = 80, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=set_brightness,
      .color="#72e4ab", .label="80", .data=80 },
    { .id = 25,  .type = ELEM_BUTTON,     .x = 1000, .y = 1100, .w = 80, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=set_brightness,
      .color="#72e4ab", .label="100", .data=100 },
    { .id = 27,  .type = ELEM_BUTTON,     .x = 1000, .y = 1200, .w = 80, .h = 80,
      .action = "btn_test", .clickable=1, .on_click=set_brightness,
      .color="#72e4ab", .label="160", .data=160 },
    { .id = 99,  .type = ELEM_BUTTON,     .x = 700, .y = 1400, .w = 200, .h = 100,
      .action = "btn_show_L2", .clickable=1, .on_click=show_layout2,
      .color="#33afcc", .label="layout2" },
};

const struct layout app1_layout1 = {
    .name = "layout1",
    .elements = layout1,
    .count = sizeof(layout1) / sizeof(layout1[0]),
};

static void get_battery() {
    char *output_buffer = NULL;
    if (execute_and_capture(BATT_LEVEL, &output_buffer) == 0) {
        refresh_layout();
        draw_text(output_buffer,20,20,"#ffffff",1);
        fb_swap();
        //hexdump(output_buffer,104);
        free(output_buffer);
    } else {
        printf("Failed to execute command\n");
        return 1;
    }
}

static void get_ip() {
    char *output_buffer = NULL;
    if (execute_and_capture(IP_ADDRESS, &output_buffer) == 0) {
        refresh_layout();
        draw_text(output_buffer,20,20,"#ffffff",1);
        fb_swap();
        //hexdump(output_buffer,104);
        printf("get ip command\n");
        free(output_buffer);
    } else {
        printf("Failed to execute command\n");
        return 1;
    }

}

static void test_tylko() {
        draw_text("output_buffer",20,600,"#ffffff",1);
        fb_swap();
}

static void show_layout1() {
    create_layout(&app1_layout1);
    fb_swap();
}

int crop_id = 0;
int pic_id = 0;
static void show_crop1() {
    pic_id = add_bitmap_to_ion("pic2.jpg");
    printf("\n(%s) pic_id: %d \n",__func__, pic_id);
    int ov_slot = prepare_overlay2("pic2.jpg");
    
    char buf[256];
    refresh_layout();
    snprintf(buf, sizeof(buf), "pictures[%d]\noverlays[%d]", pic_id, ov_slot);
    draw_text(buf,800,20,"#ffffff",1);
    fb_swap();
    
    crop_overlay2(0, 0, 800, 800);
    paste_overlay2(100, 100, 600, 600);
    crop_id = display_overlay2(ov_slot, pic_id);
    if (crop_id < 0) {
        refresh_layout();
        snprintf(buf, sizeof(buf), "pictures[%d]\noverlays[%d]", pic_id, crop_id);
        draw_text(buf,800,20,"#ffffff",1);
        fb_swap();
    }
}

static void show_crop2() {
    pic_id = add_bitmap_to_ion("pic1.jpg");
    int ov_slot = prepare_overlay2("pic1.jpg");
    
    char buf[256];
    refresh_layout();
    snprintf(buf, sizeof(buf), "pictures[%d]\noverlays[%d]", pic_id, ov_slot);
    draw_text(buf,800,20,"#ffffff",1);
    fb_swap();
    
    crop_overlay2(200, 0, 800, 800);
    paste_overlay2(300, 700, 600, 600);
    crop_id = display_overlay2(ov_slot, pic_id);
}
static void hide_crop() {
    cleanup_overlay2(crop_id);
    cleanup_pictures(pic_id);
}

static void remove_all_ov() {
    unset_all_overlays();
}

static void vibrate() {
    write_int(VIBRATOR, 100);
}
////-------------------------------------------------
const struct element layout2[] = { 
    { .id = 5,  .type = ELEM_BUTTON,     .x = 700, .y = 200, .w = 190, .h = 100,
      .action = "btn_battery", .clickable=1, .on_click=poweroff,
      .color="#ff0000", .label="poweroff" },
    { .id = 8,  .type = ELEM_BUTTON,     .x = 700, .y = 400, .w = 200, .h = 100,
      .action = "btn_getIP", .clickable=1, .on_click=get_ip,
      .color="#33afcc", .label="Get IP" },
    { .id = 19,  .type = ELEM_BUTTON,     .x = 700, .y = 1400, .w = 200, .h = 100,
      .action = "btn_show_L1", .clickable=1, .on_click=show_layout1,
      .color="#33afcc", .label="layout1" },
    { .id = 12,  .type = ELEM_BUTTON,     .x = 100, .y = 1200, .w = 200, .h = 100,
      .action = "btn_flash", .clickable=1, .on_click=service_flash,
      .color="#33afcc", .label="flash" },
};
const struct layout app1_layout2 = {
    .name = "layout2",
    .elements = layout2,
    .count = sizeof(layout2) / sizeof(layout2[0]),
};

static void show_layout2() {
    create_layout(&app1_layout2);
    fb_swap();
}

static void poweroff() {
    char *output_buffer = NULL;
    execute_and_capture(POWEROFF, &output_buffer);
}

static void service_flash() {
    char *argv[] = { FLASH, NULL };
    run_background(argv[0], argv);
}
