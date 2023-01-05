#include "graphics.h"

shape* shapes_to_draw[MAX_SHAPES];  // An array of pointers to shapes to draw
int32_t num_shapes = 0;

void update_graphics(void)
{
    static int32_t shape_index = 0; // Index of shape currently being drawn

    // ************ Draw Shapes ************

    const int32_t points_per_second = 30000;    // Measure of drawing speed in a straight line
    // const int32_t points_per_second = 300;    // Measure of drawing speed in a straight line

    static double lerp_factor = 0;
    static int32_t current_point_index = 0;
    int32_t next_point_index;

    point_t* points = shapes_to_draw[shape_index]->points;
    int32_t num_points = shapes_to_draw[shape_index]->num_points;

    if(current_point_index + 1 < num_points)
    {
        next_point_index = current_point_index + 1;
    } else
    {
        current_point_index = 0;
        next_point_index = 1;
        shape_index ++;
    }

    if(shape_index >= num_shapes)
    {
        shape_index = 0;
    }

    static uint64_t last_draw_time = 0;
    double dt = (micros()-last_draw_time) / 1000000.0;
    if(micros()-last_draw_time > 55)
    {
        // printf("Current shape to draw has index: %d\n", shape_index);
        last_draw_time = micros();
        
        point_t current_point   = points[current_point_index];
        point_t next_point      = points[next_point_index];

        int32_t distance = distance_between_points(current_point, next_point);
        point_t point_to_draw = lerp_points(current_point, next_point, lerp_factor);

        // Re-calculate lerp_factor
        lerp_factor += (double)points_per_second * (dt / distance);

        // Reset variables after next_point is reached
        if(lerp_factor>=1)
        {
            lerp_factor = 0;
            current_point_index = next_point_index;
        }

        // Draw point to screen         // ==> !!! Takes 38 us to update both
        dacWrite(X_PIN, point_to_draw.x);
        dacWrite(Y_PIN, point_to_draw.y);
    }

    static uint64_t last_time_measurement = 0;
    if(millis()-last_time_measurement > 1000)
    {
        last_time_measurement = millis();
        // Serial.printf("Shape index: %d\n", shape_index);

    }
}

void add_shape(shape_t* shape)
{
    shapes_to_draw[num_shapes] = shape;
    num_shapes++;
}

void clear_shapes(void)
{
    num_shapes = 0;
}

point_t lerp_points(point_t p1, point_t p2, double a)
{
    return {(1-a)*p1.x + a*p2.x, (1-a)*p1.y + a*p2.y};
}

// Determine distance between points
double distance_between_points(point_t p1, point_t p2)
{
    return sqrt((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y));
}
