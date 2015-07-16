//Prevent this from being imported twice
#ifndef _USEFUL_OBJECTS_H_ADDED
#define _USEFUL_OBJECTS_H_ADDED 0x1

#include <X11/Xlib.h>
#include <string.h>
#include <stdio.h>



class TextBox
{
public:
  TextBox(Display *dsp, Window win, GC gc, char* text, int x, int y);
};

TextBox::TextBox( Display *dsp, Window win, GC gc, char* text, int x, int y) {
    XFontStruct *font_info;

    int string_length = strlen(text);
    printf("this workded\n");
    XDrawString(dsp, win, gc, x, y, text, string_length);

    //Now draw a box around the text...
    printf("still working\n");
    int width = 100;//XTextWidth(font_info, text, string_length);
    int height = 12;//font_info->ascent + font_info->descent;
    printf("Not working anymore\n");
    int padding = 5; //Padding of 5 pixels

    //Draw the box;
    XDrawLine(dsp, win, gc, x-padding, y-padding, x+width+padding, y+padding); //Top
    //XDrawLine(dsp, win, gc, x-padding, y-padding, x-padding, y-padding-height); //left-side
    //XDrawLine(dsp, win, gc, x+width+padding, y-padding-height, x+width+padding, y+padding); //right side
    //XDrawLine(dsp, win, gc, x-padding, y-(height+padding), x+width+padding, y-height-padding); //bottom
  }




#endif
