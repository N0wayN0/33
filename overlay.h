#ifndef OVERLAY_H
#define OVERLAY_H

#include <stdint.h>
#include <linux/msm_mdp.h>

struct memPicture {
    unsigned char *mem_buf;
    int size;
    int mem_fd;
    int width;
    int height;
    char name[32];
    struct ion_handle_data handle_data;
    char *filename;
};

struct lista { 
    uint32_t count;
    struct mdp_blit_req req[6];
};

// print info
void print_memory_info(struct memPicture *mem);
void print_overlay_info(const struct mdp_overlay *ov);
int target_has_overlay(char *version);
// ion stuff
int free_ION_mem();
int alloc_ION_mem();
void close_ION(void);
int place_file_to_ion();
int cleanup_pictures(int id); // clear slot 
int cleanup_all_pictures();
int add_bitmap_to_ion(const char *name);
int load_ui_atlas(const char *name);
int load_file_to_ion(struct memPicture *mem, const char *filename);
// overlay
void init_overlays(void);
int prepare_overlay_for_canvas(void);
int display_overlay_canvas(int ion_slot);
void software_blit(int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y);
int prepare_overlay2(const char *name);
int crop_overlay2(int x, int y, int w, int h);
int paste_overlay2(int x, int y, int w, int h);
int display_overlay2(int ov_slot, int ion_slot);
int cleanup_overlay2(int id);  //overlays array and unset from hw
int unset_overlay2(int id); //unset from hw
int unset_all_overlays();

//int allocate_new_overlay(struct mdp_overlay *overlay);
//int display_overlay(struct msmfb_overlay_data *ovdata);
//void crop_overly(void);

int prepare_canvas();
int display_canvas();
int blit_to_canvas();

add_to_blit_list(const char *type, const struct element *e);
void blit_now(void);

#endif
