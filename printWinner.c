#include "font_types.h"

void print_message(const char *message, int x, int y, unsigned short color, unsigned char* mem_base) {
  int i;
  for (i = 0; message[i] != '\0'; i++) {
    draw_char(x + i * char_width(message[i]) * 4, y, message[i], color);
  }
  parlcd_write_cmd(mem_base, 0x2c);
  for (i = 0; i < 480 * 320; i++) {
    parlcd_write_data(mem_base, fb[i]);
  }
}

int printWinner(unsigned char *parcld_mem_base) {

  font_descriptor_t fdes = font_winFreeSystem14x16;

  // Print "Player1Won" on the display
  print_message("Player1Won", 100, 150, hsv2rgb_lcd(120, 255, 255), parcld_mem_base); // Green color

  printf("Goodbye\n");
  return 0;
}