//Prevent this from being imported twice
#ifndef _USEFUL_OBJECTS_H_ADDED
#define _USEFUL_OBJECTS_H_ADDED 0x1

#include <X11/Xlib.h>
#include <string.h>
#include <stdio.h>

class GraphicItem
{
protected:
 XFontStruct *font_info;
 Display *disp;
 Window wind;
 GC gc_;
 int width, height, x_pos,y_pos, abswidth, absheight;
 int padding; //Padding of 5 pixels
 char *str;
public:
 int getTotalWidth();
 int getTotalHeight();
 //void update(char* text, int x, int y);
 void draw();
};

class TextBox : public GraphicItem
{
public:
  TextBox(Display *dsp, Window win, GC gc, char* text, int x, int y);
  void update(char* text, int x, int y);
  void draw();
};
void TextBox::Draw()
{
  //Clear the destination area for the box;
  XClearArea(this -> disp, this -> wind, this->x_pos-padding-1, this->y_pos-(this -> absheight)+padding-1, this->abswidth+3, this->absheight+3, true);
  int string_length = strlen(this->str);
  XDrawString(this->disp, this->wind, this->gc_, this->x_pos, this->y_pos, this->str, string_length);

  //Now draw a box around the text...
  //To do this, we must first work out the dimentions
  width = XTextWidth(font_info, this->str, string_length);
  height = font_info->ascent + font_info->descent;

  //publicise the dimentions so that they can be used in other parts of the program
  this -> abswidth  = width + 2*padding;
  this -> absheight = height + 2*padding;

  //Draw the box
  XDrawLine(disp, wind, gc_, x_pos-padding, y_pos+padding, x_pos+width+padding, y_pos+padding); //Top
  XDrawLine(disp, wind, gc_, x_pos-padding, y_pos+padding,x_pos-padding, y_pos-padding-height); //left-side
  XDrawLine(disp, wind, gc_, x_pos+width+padding, y_pos-padding-height, x_pos+width+padding, y_pos+padding); //right side
  XDrawLine(disp, wind, gc_, x_pos-padding, y_pos-padding-height, x_pos+width+padding, y_pos-height-padding); //bottom
}
TextBox::TextBox( Display *dsp, Window win, GC gc, char* text, int x, int y) {
    //Load a font
    //XFontStruct **font_info; not sure if I need this
    x_pos = x;
    y_pos = y;
    disp = dsp;
    wind = win;
    gc_ = gc;
    str = text;

    padding = 5;

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
    //Before moving the TextBox, first we must clear the old one...
    //It'll clear an extra pixel surrounding the object.
    XClearArea(this -> disp, this -> wind, this->x_pos-padding-1, this->y_pos-(this -> absheight)+padding-1, this->abswidth+3, this->absheight+3, true);
    padding = 5;
    this -> x_pos = x;
    this -> y_pos = y;
    this -> str = text;
    this -> draw();
  }

int GraphicItem::getTotalWidth() { return abswidth; }
int GraphicItem::getTotalHeight() { return absheight;}



#endif
