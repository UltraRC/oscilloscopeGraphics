#include "graphics.h"

#define X_PIN 25
#define Y_PIN 26

line_t lines[100];
int32_t num_lines = 0;

void graphics_update(void)
{

    for(int32_t line_index=0; line_index<num_lines; line_index++)
    {
        line_t line_to_draw = lines[line_index];                                    // The current line being drawn
        int32_t line_length_squared = calculate_line_length_squared(line_to_draw);  // The length of the current line being drawn
        int32_t increment_length = 10;                                               // The distance the beam increments along a line being drawn

        int32_t x_increment = increment_length*(line_to_draw.end_x - line_to_draw.start_x) / sqrt(line_length_squared);
        int32_t y_increment = increment_length*(line_to_draw.end_y - line_to_draw.start_y) / sqrt(line_length_squared);


        int32_t drawn_length = 0;
        int32_t current_x = line_to_draw.start_x;
        int32_t current_y = line_to_draw.start_y;

        while(calculate_line_length_squared(new_line(line_to_draw.start_x, line_to_draw.start_y, current_x, current_y)) < line_length_squared)
        {
            write_x_pixel(current_x);
            write_y_pixel(current_y);

            current_x += x_increment;
            current_y += y_increment;
        }

    }

}

void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    lines[num_lines] = new_line(x1, y1, x2, y2);
    num_lines++;
}

line_t new_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    line_t line;
    line.start_x = x1;
    line.start_y = y1;
    line.end_x = x2;
    line.end_y = y2;
    return line;
}

int32_t calculate_line_length_squared(line_t line)
{
    return (line.end_x-line.start_x)*(line.end_x-line.start_x) + (line.end_y-line.start_y)*(line.end_y-line.start_y);
}

void clear_screen(void)
{
    num_lines = 0;
}

void write_x_pixel(int32_t pos)
{
    dacWrite(X_PIN, pos);
}

void write_y_pixel(int32_t pos)
{
    dacWrite(Y_PIN, pos);
}
