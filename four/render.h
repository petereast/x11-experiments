#ifndef RENDER_H
#define RENDER_H 0x1
//README:
//This header will contain all of the functions which use the descriptive classes
//defined in "objects.h". It will also contain all of the classes for adding new
//elements to the rendering stack

X11_data initialise_x11(int window_height, int window_width)
{
  fprintf(stdout, "[ln32]");
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
  fprintf(stdout, "[ln53]");
  XSelectInput(x.display, x.window, x.event_mask);
  do{
    XNextEvent(x.display, &x.event);
  }while(x.event.type != MapNotify);
  printf("[ln58]");


  x.gc = XCreateGC(x.display, x.window, 0, NULL);

  XSetForeground(x.display, x.gc, x.foreground_colour);

  return x;
}



#endif
