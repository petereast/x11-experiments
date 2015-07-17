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
  int getTotalWidth();
  int getTotalHeight();
protected:
  int width, height, x_pos, y_pos, abswidth, absheight;
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
    this->update(this->str, this->x_pos, this->y_pos);
  }

void  TextBox::update(char* text, int x, int y)
  {
    this -> x_pos = x;
    this -> y_pos = y;
    this -> str = text;
    int string_length = strlen(this->str);

    int padding = 5; //Padding of 5 pixels
    XDrawString(this->disp, this->wind, this->gc_, this->x_pos, this->y_pos, this->str, string_length);

    //Now draw a box around the text...
    //To do this, we must first work out the dimentions
    width = XTextWidth(font_info, text, string_length);
    height = font_info->ascent + font_info->descent;

    //publicise the dimentions so that they can be used in other parts of the program
    this -> abswidth  = width + 2*padding;
    this -> absheight = height + 2*padding;

    //Draw the box
    XDrawLine(this -> disp, this -> wind, gc_, this -> x_pos-padding, this -> y_pos+padding, this -> x_pos+width+padding, this -> y_pos+padding); //Top
    XDrawLine(this -> disp, this -> wind, gc_, this -> x_pos-padding, this -> y_pos+padding, this -> x_pos-padding, this -> y_pos-padding-height); //left-side
    XDrawLine(this -> disp, this -> wind, gc_, this -> x_pos+width+padding, this -> y_pos-padding-height, this -> x_pos+width+padding, this -> y_pos+padding); //right side
    XDrawLine(this -> disp, this -> wind, gc_, this -> x_pos-padding, this -> y_pos-padding-height, this -> x_pos+width+padding, this -> y_pos-height-padding); //bottom
  }

int TextBox::getTotalWidth() { return this -> abswidth; }
int TextBox::getTotalHeight() { return this -> absheight;}



#endif
