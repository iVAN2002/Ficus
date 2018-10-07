#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
 
#include <tty.h>
#include <vga.h>
#include <io.h>
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
 
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;
 
void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}
 
void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) {
	unsigned char uc = c;
	terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
	
	terminal_curupdate();
}


void fillchar(uint16_t c, uint16_t *str[])
{
	int l = sizeof(str) / sizeof(uint16_t *);

	for (int i = 0; i < l; i++)
	{
		str[i] = &c;
	}
}

void terminal_curupdate()
{
	uint16_t offset = (terminal_row * VGA_WIDTH) + terminal_column;
	port_writeb(0x3D4, 14);
    port_writeb(0x3D5, offset >> 8);
    port_writeb(0x3D4, 15);
    port_writeb(0x3D5, offset);
}

void terminal_newline(void)
{
	if ((terminal_row + 1) == VGA_HEIGHT)
	{
		uint16_t *temp_line[VGA_WIDTH];

		for (size_t y = 1; y < VGA_HEIGHT; y++)
		{
			// Очищаем временную строку
			fillchar(vga_entry('\0', terminal_color), temp_line);

			// Читаем строку на экране
			for (size_t x = 0; x < VGA_WIDTH; x++)
			{
				const size_t i1 = VGA_WIDTH * y + x;
				const size_t i2 = VGA_WIDTH * (y - 1) + x;
				terminal_buffer[i2] = terminal_buffer[i1];
			}
		}

		// Очищаем последнюю строку
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry('\0', terminal_color);
		}
	}
	else
	{
		terminal_row++;
	}
	terminal_column = 0;
	
	terminal_curupdate();
}
 
void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		if (data[i] == '\n')
		{
			terminal_newline();
		} else
		{
			terminal_putchar(data[i]);
		}
}
 
void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}
