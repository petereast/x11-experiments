//Prevent this from being imported twice
#ifndef _USEFUL_OBJECTS_H_ADDED
#define _USEFUL_OBJECTS_H_ADDED 0x1

#include <X11/Xlib.h>
#include <string.h>
#include <stdio.h>



class TextBox
{
  XFontStruct *font_info;
  Display *disp;
  Window wind;
  GC gc_;
public:
  TextBox(Display *dsp, Window win, GC gc, char* text, int x, int y);
  int width, height, x_pos, y_pos;
  char *str;

  void update(char* text, int x, int y);
};

TextBox::TextBox( Display *dsp, Window win, GC gc, char* text, int x, int y) {
    //Load a font
    //XFontStruct **font_info; not sure if I need this
    this -> x_pos = x;
    this -> y_pos = y;
    this -> disp = dsp;
    this -> wind = win;
    this -> gc_ = gc;
    this -> str = text;

    char *fontname = "6x13";
    if((font_info = XLoadQueryFont(dsp, fontname)) == NULL)
    {
      printf("Error loading the font :(\n");
      exit(-1);
    }

    XSetFont(dsp, gc, font_info->fid);
    this.update(this->str, this->x_pos, this->y_pos);
  }

  TextBox::update(char* text, int x, int y)
  {
    this -> x_pos = x;
    this -> y_pos = y;
    this -> str = text;
    int string_length = strlen(this->str);
    printf("this workded\n");
    XDrawString(this->dsip, this->wind, this->gc_, this->x_pos, this->y_pos, this->str, string_length);

    //Now draw a box around the text...
    printf("still working\n");
    width = XTextWidth(font_info, text, string_length);
    height = font_info->ascent + font_info->descent;
    printf("Width: %i, Height: %i", width, height);
    printf("Not working anymore\n");
    int padding = 5; //Padding of 5 pixels

    //Draw the box;
    XDrawLine(disp, wind, gc_, x-padding, y+padding, x+width+padding, y+padding); //Top
    XDrawLine(disp, wind, gc_, x-padding, y+padding, x-padding, y-padding-height); //left-side
    XDrawLine(disp, wind, gc_, x+width+padding, y-padding-height, x+width+padding, y+padding); //right side
    XDrawLine(disp, wind, gc_, x-padding, y-padding-height, x+width+padding, y-height-padding); //bottom
  }




#endif
