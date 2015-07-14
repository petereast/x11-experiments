#include <X11/Xlib.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>


int main(int argc, char* argv[])
{
	//printf("Hello world!");
	
	Display *dsp = XOpenDisplay( NULL );
	if(! dsp){ return -1;}
	
	
	int screen_number = DefaultScreen(dsp);
	
	unsigned long white WhitePixel(dsp, screen_number);
	unsigned long black BlackPixel(dsp, screen_number);
		
	
	Window win 	= XCreateSimpleWindow(dsp,
									DefaultRootWindow(dsp),
									50, 50,
									400, 400,
									0, black,
									white);
	XMapWindow(dsp, win);
	
	long event_mask = StructureNotifyMask;
	XSelectInput( dsp, win, event_mask);
	
	XEvent evt;
	
	do{
		XNextEvent(dsp, &evt); //Calls XFlush, whatever that is
	}while( evt.type != MapNotify);
	
	GC gc = XCreateGC(dsp, win, 0, NULL );
	
	XSetForeground(dsp, gc, black);
	
	XDrawLine(dsp, win, gc, 10, 10, 100, 100);
	XDrawLine(dsp, win, gc, 100, 10, 10, 100);
	
	event_mask = ButtonPressMask|ButtonReleaseMask|KeyPressMask;
	XSelectInput(dsp, win, event_mask);
	
	do{
		XNextEvent(dsp, &evt);
		if(evt.type == KeyPress)
		{
			XDrawLine(dsp, win, gc, 0, 0, rand()*400, 400);
		}
	}while(true);
	
	XDestroyWindow(dsp, win);
	XCloseDisplay(dsp);
	
	
	
	return 0;
}
