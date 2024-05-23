#include <stdio.h>
#include "font_types.h"
#include "mzapo_parlcd.h"
#include "font_prop14x16.c"
#include "font_rom8x16.c"

// array with colors, based on message
unsigned int fb[320*480*2]; 

font_descriptor_t *fdes = &font_winFreeSystem14x16;
int scale=4;


// draw pixel
void draw_pixel(int x, int y, unsigned int color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}
 
// draw pixel based on scale
void draw_pixel_big(int x, int y, unsigned int color) {
  int i,j;
  for (i=0; i<scale; i++) {
    for (j=0; j<scale; j++) {
      draw_pixel(x+i, y+j, color);
    }
  }
}
 
// gets char width
int char_width(int ch) {
  int width;
  if (!fdes->width) {
    width = fdes->maxwidth;
  } else {
    width = fdes->width[ch-fdes->firstchar];
  }
  return width;
}
 

// draw char to array fb based on char width, scale and other parameters
void draw_char(int x, int y, char ch, unsigned int color) {
  int w = char_width(ch);
  const font_bits_t *ptr;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    if (fdes->offset) {
      ptr = &fdes->bits[fdes->offset[ch-fdes->firstchar]];
    } else {
      int bw = (fdes->maxwidth+15)/16;
      ptr = &fdes->bits[(ch-fdes->firstchar)*bw*fdes->height];
    }
    int i, j;
    for (i=0; i<fdes->height; i++) {
      font_bits_t val = *ptr;
      for (j=0; j<w; j++) {
        if ((val&0x8000)!=0) {
          draw_pixel_big(x+scale*j, y+scale*i, color);
        }
        val<<=1;
      }
      ptr++;
    }
  }
}

// calls other methods to create array and then writes it to lcd display
void print_message(const char *message, int x, int y, unsigned int color, unsigned char* mem_base) {
  
  int i;
  for (i = 0; message[i] != '\0'; i++) {
    draw_char(x , y, message[i], color);
    x += (char_width(message[i]) * 4);
  }
  parlcd_write_cmd(mem_base, 0x2c);
  for (i = 0; i < 480 * 320; i++) {
    parlcd_write_data(mem_base, fb[i]);
  }


}
