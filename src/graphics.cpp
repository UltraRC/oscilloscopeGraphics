#include "graphics.h"

// #define POINT_DENSITY           1000                // [px/px] ~ Number of points along a line
#define BEAM_SPEED              100                 // [px/s] ~ Number of pixels per second that the beam travels at

#define DRAW_UPDATE_RATE        1                   // [Hz] ~ Frequency that the lines are redrawn to the screen
#define POINT_UPDATE_FREQUENCY  1000                // [Hz] ~ Frequency that the beam is advanced to the next point

line_t lines_to_draw[MAX_LINES];                    // An array of pointers to shapes to draw
int32_t num_lines = 0;

void update_graphics(void)
{
    static int32_t line_index = 0;              // Index of line currently being drawn
    static double lerp_factor = 0;

    static uint64_t last_draw_time = 0;
    static uint64_t last_draw_time_entered = 0;
    // double dt_last_draw_time = (micros()-last_draw_time) / 1000000.0;

    if(micros()-last_draw_time > 1000000/DRAW_UPDATE_RATE)
    {
        last_draw_time_entered = micros();
        
        static uint64_t last_point_advance_time = 0;
        double dt_last_point_advance_time = (micros()-last_point_advance_time) / 1000000.0;

        if(micros()-last_point_advance_time > 1000000/POINT_UPDATE_FREQUENCY)
        {
            last_point_advance_time = micros();

            Serial.printf("line_index = %d\n", line_index);

            point_t current_point   = lines_to_draw[line_index].start_point;
            point_t next_point      = lines_to_draw[line_index].end_point;

            int32_t distance = distance_between_points(current_point, next_point);
            point_t point_to_draw = lerp_points(current_point, next_point, lerp_factor);

            // Draw point to screen
            dacWrite(X_PIN, point_to_draw.x);
            dacWrite(Y_PIN, point_to_draw.y);

            // Re-calculate lerp_factor
            lerp_factor += (double)BEAM_SPEED * (dt_last_point_advance_time / distance);

            // Reset variables after next_point is reached
            if(lerp_factor>=1)
            {
                lerp_factor = 0;
                line_index++;
            }
        }

        if(line_index > num_lines)
        {
            last_draw_time = last_draw_time_entered;    // Reset draw timer
            line_index = 0;                             // Reset line index
            dacWrite(X_PIN, 255);                         // Send beam to (0,0)
            dacWrite(Y_PIN, 255);
        }
    }

    static uint64_t last_time_measurement = 0;
    if(millis()-last_time_measurement > 1000)
    {
        last_time_measurement = millis();
        // Serial.printf("Shape index: %d\n", shape_index);

    }
}


// void update_graphics(void)
// {
//     static int32_t line_index = 0;              // Index of line currently being drawn

//     // ************ Draw Lines ************

//     static double lerp_factor = 0;
//     static int32_t current_point_index = 0;
//     int32_t next_point_index;

//     point_t* points = shapes_to_draw[shape_index]->points;
//     int32_t num_points = shapes_to_draw[shape_index]->num_points;

//     if(current_point_index + 1 < num_points)
//     {
//         next_point_index = current_point_index + 1;
//     } else
//     {
//         current_point_index = 0;
//         next_point_index = 1;
//         shape_index ++;
//     }

//     if(shape_index >= num_shapes)
//     {
//         shape_index = 0;
//     }

//     static uint64_t last_draw_time = 0;
//     double dt = (micros()-last_draw_time) / 1000000.0;
//     if(micros()-last_draw_time > 1000000/DRAW_UPDATE_RATE)
//     {
//         last_draw_time = micros();
        
//         point_t current_point   = points[current_point_index];
//         point_t next_point      = points[next_point_index];

//         int32_t distance = distance_between_points(current_point, next_point);
//         point_t point_to_draw = lerp_points(current_point, next_point, lerp_factor);

//         // Re-calculate lerp_factor
//         lerp_factor += (double)points_per_second * (dt / distance);

//         // Reset variables after next_point is reached
//         if(lerp_factor>=1)
//         {
//             lerp_factor = 0;
//             current_point_index = next_point_index;
//         }

//         // Draw point to screen         // ==> !!! Takes 38 us to update both
//         dacWrite(X_PIN, point_to_draw.x);
//         dacWrite(Y_PIN, point_to_draw.y);
//     }

//     static uint64_t last_time_measurement = 0;
//     if(millis()-last_time_measurement > 1000)
//     {
//         last_time_measurement = millis();
//         // Serial.printf("Shape index: %d\n", shape_index);

//     }
// }

void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    point_t point_1 = {x1, y1};
    point_t point_2 = {x2, y2};
    
    line_t line = {point_1, point_2};
    lines_to_draw[num_lines++] = line;
}

void clear_screen(void)
{
    num_lines = 0;
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
