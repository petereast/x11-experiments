//Ensure the module isn't imported more than once
#ifndef OBJECTS_H
#define OBJECTS_H 0xF
//Now that we're safe, include some modules
#include <X11/Xlib.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

//finished including modules

struct X11_data
{
  Display *display;
  Window window;
  XFontStruct* fontInfo;
  GC gc;
  int screen_number;
  unsigned long background_colour;
  unsigned long foreground_colour;

  unsigned long event_mask;

  XEvent event;

};

X11_data initialise_x11(int window_height, int window_width)
{
  X11_data x;
  x.display = XOpenDisplay( NULL );
  if(!x.display){exit(-1);}

  x.screen_number = DefaultScreen(x.display);

  x.foreground_colour = WhitePixel(x.display, x.screen_number);
  x.background_colour = BlackPixel(x.display, x.screen_number);

  x.window = XCreateSimpleWindow(
    x.display,
    DefaultRootWindow(x.display),
    0, 0,
    window_height, window_width,
    0, x.background_colour,
    x.background_colour
  );

  XMapWindow(x.display, x.window);

  x.event_mask = StructureNotifyMask;

  do{
    XNextEvent(x.display, &x.event);
  }while(x.event.type != MapNotify);

  x.gc = XCreateGC(x.display, x.window, 0, NULL);

  XSetForeground(x.display, x.gc, x.foreground_colour);

  return x;
}

class GraphicItem
{
protected:
  char* id;
  int x, y; //x and y positions of the item
  int height, width; // height and width of the item
  X11_data x_data;
public:
  //add some functions here!
  char* getId();
  void setId(char* id);
};

char* GraphicItem::getId()
{
  return id;
}

void GraphicItem::setId(char* id)
{
  this->id = id;
}

class TextBox : public GraphicItem
{
protected:
  char* text;
  int padding = 5;
public:
  void Draw(bool initial); //Function to draw the textbox
  void Update(int x, int y, char* text, bool initial);
  TextBox(X11_data& xd, int x, int y, char* text, char* font);
};

void TextBox::Draw(bool initial)
{
  if(initial) //if this is the first time the function is run...
  {
    //calculate the dimentions of the text
    int textwidth = XTextWidth(x_data.fontInfo, text, strlen(text));

    this->width = textwidth+(padding*2);
    this->height = x_data.fontInfo->ascent + x_data.fontInfo->descent + (padding*2);

  }
  //clear the area!
  XClearArea(x_data.display, x_data.window, x-padding, y-padding, x+width, y+width, true);

  //Draw the text
  XDrawString(x_data.display, x_data.window, x_data.gc, x, y, text, strlen(text));

  //Draw the box
  XDrawLine(x_data.display, x_data.window, x_data.gc, x-padding, y-padding, x+width+padding, y-padding);
  XDrawLine(x_data.display, x_data.window, x_data.gc, x-padding, y-padding, x-padding, y+height+padding);
  XDrawLine(x_data.display, x_data.window, x_data.gc, x-padding, y+height+padding, x+width+padding, y+height+padding);
  XDrawLine(x_data.display, x_data.window, x_data.gc, x+width+padding, y-padding, x+width+padding, y+height+padding);
}

void TextBox::Update(int x, int y, char* text, bool initial)
{
  this -> x = x;
  this -> y = y;
  this -> text = text;

  Draw(initial);

}

TextBox::TextBox(X11_data& xd, int x, int y, char* text, char* font)
{
  this->x_data = xd;
  //load a font...
  if((x_data.fontInfo = XLoadQueryFont(x_data.display, font)) == NULL)
  {
    printf("[X11 ERROR] '%s' isn't a valid font, using 6x13 instead.", font);
    x_data.fontInfo = XLoadQueryFont(x_data.display, "6x13");
  }
  XSetFont(x_data.display, x_data.window, x_data.gc, x_data.fontInfo->fid);

  Update(x, y, text, true);
}



//Define some arrays and general functions

std::vector<GraphicItem> Graphics_Array;

void addGraphicItem(GraphicItem gi)
{
  Graphics_Array.push_back(gi);
}

void drawGraphics()
{
  for(std::vector<GraphicItem>::iterator it = Graphics_Array.begin(); it != Graphics_Array.end(); ++it )
  {
    *it.Draw(False);
  }
}


//end of header file
#endif
