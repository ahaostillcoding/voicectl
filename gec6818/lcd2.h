#ifndef LCD2_H
#define LCD2_H

void lcd2_init();
void lcd2_draw_point(int x, int y, int color);
void lcd2_draw_rgb888(char *rgb888, int width, int height, int x, int y);
void lcd2_uninit();

#endif