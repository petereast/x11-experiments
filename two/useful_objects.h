//Prevent this from being imported twice
#ifndef _USEFUL_OBJECTS_H_ADDED
#define _USEFUL_OBJECTS_H_ADDED 0x1

#include <X11/Xlib.h>
#include <string.h>


class TextBox
{
public:
  TextBox();
};

TextBox::TextBox  {
    XFontStruct *font_info;

    int string_length = strlen(text);

    XDrawString(dsp, win, gc, x, y, text, string_length);

    //Now draw a box around the text...
    int width = XTextWidth(font_info, text, string_length);
    int height = font_info->ascent + font_info->descent;

    int padding = 5; //Padding of 5 pixels

    //Draw the box;
    XDrawLine(dsp, win, gc, x-padding, y-padding, x+width+padding, y+padding); //Top
    XDrawLine(dsp, win, gc, x-padding, y-padding, x-padding, y-padding-height); //left-side
    XDrawLine(dsp, win, gc, x+width+padding, y-padding-height, x+width+padding, y+padding); //right side
    XDrawLine(dsp, win, gc, x-padding, y-height-padding, x+width+padding, y-height-padding); //bottom
  }




#endif
