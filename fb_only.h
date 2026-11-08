#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

//#define FB_OFF(fbx,fby) ((fbx+vinfo.xoffset)*pinc+(fby+vinfo.yoffset)*finfo.line_length)
#define FB_OFF(fbx,fby) ((fbx+vinfo.xoffset)*pinc+(fby+back_buffer_y)*finfo.line_length)



void put_pixel(int x, int y, const char *hex_rgb);
void fb_swap();
int getFbXres();
int getFbYres();
int init_fb();
void close_fb();

#endif
