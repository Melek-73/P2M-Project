/*
 * lcd_utils.c
 *
 *  Created on: 17 mars 2026
 *      Author: foura
 */

#include <stdint.h>


#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_RED     0xF800
#define COLOR_GREEN   0x07E0
#define COLOR_BLUE    0x001F
#define COLOR_YELLOW  0xFFE0
#define COLOR_CYAN    0x07FF
#define COLOR_MAGENTA 0xF81F
#define COLOR_ORANGE  0xFD20
#define COLOR_GRAY    0x8410

#define LCD_WIDTH  480
#define LCD_HEIGHT 272

uint16_t *framebuffer = (uint16_t *)0xC0000000;

void LCD_FillScreen(uint16_t color)
{
    for (int i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++)
    {
        framebuffer[i] = color;
    }
}

void Display_Color_From_Class(uint8_t class_id)
{
    switch(class_id)
    {
        case 1: LCD_FillScreen(COLOR_RED); break;
        case 2: LCD_FillScreen(COLOR_BLACK); break;
        case 3: LCD_FillScreen(COLOR_BLUE); break;
        case 4: LCD_FillScreen(COLOR_GREEN); break;
        case 5: LCD_FillScreen(COLOR_WHITE); break;
        case 6: LCD_FillScreen(COLOR_YELLOW); break;
        case 7: LCD_FillScreen(COLOR_CYAN); break;
        case 8: LCD_FillScreen(COLOR_MAGENTA); break;
        case 9: LCD_FillScreen(COLOR_ORANGE); break;
        case 10: LCD_FillScreen(COLOR_GRAY); break;

        default: LCD_FillScreen(COLOR_BLACK); break;
    }
}

