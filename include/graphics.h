#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Arduino.h>

#define MAX_POINTS_PER_SHAPE    255
#define MAX_LINES               255

#define X_PIN 25
#define Y_PIN 26

typedef struct point
{
    int32_t x;
    int32_t y;
} point_t;

typedef struct line
{
    point_t start_point;
    point_t end_point;
} line_t;

void update_graphics(void);
double distance_between_points(point_t p1, point_t p2);
point_t lerp_points(point_t p1, point_t p2, double a);
void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
void clear_screen(void);


#endif  // GRAPHICS_H