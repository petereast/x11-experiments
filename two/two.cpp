#include <iostream>
#include <X11/Xlib.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "useful_objects.h"

int main(int argc, char* argv[])
{
	printf("This program is designed to be a tester for various UI Elements in an\nupcoming project. Functionality is not important.\n");

	//Define all the X11 stuff

	Display *dsp = XOpenDisplay( NULL );
	if(!dsp){return -1;}

	int screen_number = DefaultScreen(dsp);

	//Create some colours
	//TODO: Make it switchable between colours.
	unsigned long foreground_colour = WhitePixel(dsp, screen_number);
	unsigned long background_colour = BlackPixel(dsp, screen_number);
	printf("1\n");
	//Create a window
	Window win = XCreateSimpleWindow(dsp,
		DefaultRootWindow(dsp),
		0, 0, //origin
		500, 500, //size
		0, background_colour, //border
		background_colour //background
	);

	XMapWindow(dsp, win);

	unsigned long event_mask = StructureNotifyMask;
	XSelectInput(dsp, win, event_mask);

	XEvent ev;

	do{
		XNextEvent(dsp, &ev);
	}while(ev.type != MapNotify);
	printf("1\n");
	GC gc = XCreateGC(dsp, win, 0, NULL);

	XSetForeground(dsp, gc, foreground_colour);

	//TODO: Impliment an easy text object.

	//XDrawLine(dsp, win, gc, 0, 0, 500, 500);

	//Create a background texture - for debug, but it might get carried on :P
	for (int i = -500; i != 500; i++)
	{
		XDrawLine(dsp, win, gc, i, i, 500, 500);
	}


	event_mask = ButtonReleaseMask | KeyPressMask;
	XSelectInput(dsp, win, event_mask);
	TextBox tb(dsp, win, gc, "Hello World", 50, 50), tb2(dsp, win, gc, "Goodbye World", 100, 300);
	do{
		XNextEvent(dsp, &ev);
		if(ev.type == KeyPress )
		{
			tb.update("Hellllo world!", 70, 30);
			printf("Total width: %i\n", tb.getTotalWidth());

			tb2.update("riuaboigubrgiabel", 300, 300);
		}
	}while(ev.type != ButtonRelease);

	XDestroyWindow(dsp, win);
	XCloseDisplay(dsp);


}
