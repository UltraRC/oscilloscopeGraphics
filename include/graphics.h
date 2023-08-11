#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Arduino.h>

typedef struct
{
    int32_t start_x;
    int32_t start_y;
    int32_t end_x;
    int32_t end_y;
} line_t;

void graphics_update(void);
void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
line_t new_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
int32_t calculate_line_length_squared(line_t line);
void clear_screen(void);
void write_x_pixel(int32_t pos);
void write_y_pixel(int32_t pos);

#endif  // GRAPHICS_H