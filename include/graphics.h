#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Arduino.h>

// Macros for enabling the DACs
#define RTCIO_PAD_PDAC1_MUX_SEL (BIT(17))
#define RTCIO_PAD_PDAC2_MUX_SEL (BIT(17))

void graphics_update(void);
void draw_center_rectangle(int32_t width, int32_t height, int32_t xpos, int32_t ypos);
void draw_corner_rectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
int32_t draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
void clear_screen(void);

#endif  // GRAPHICS_H