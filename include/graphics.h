#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Arduino.h>

#define MAX_POINTS_PER_SHAPE    255
#define MAX_SHAPES              255

#define X_PIN 25
#define Y_PIN 26

typedef struct point
{
    int32_t x;
    int32_t y;
} point_t;

typedef struct shape
{
    point_t points[MAX_POINTS_PER_SHAPE];
    int32_t num_points;
} shape_t;

void update_graphics(void);
double distance_between_points(point_t p1, point_t p2);
point_t lerp_points(point_t p1, point_t p2, double a);
void add_shape(shape_t* shape);
void clear_shapes(void);


#endif  // GRAPHICS_H