#include <X11/Xlib.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <string.h>


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
									5, black,
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

	//XDrawLine(dsp, win, gc, 10, 10, 100, 100);
	//XDrawLine(dsp, win, gc, 100, 10, 10, 100);
	int xpoints[10] = {100, 40, 05, 20, 40 ,50 , 30, 20, 11, 300};
	//for(int i = 0; i!= 200; i++)
	//{
	//	XDrawLine(dsp, win, gc, i*2, 0, i*2, (i^3)+4*i);
	//}
	//Let's add some text
	//Create a font
	XFontStruct *font_info;

	char *string1 = "hello world I say hello";
	int string1_length = strlen(string1);

	XDrawString(dsp, win, gc, 50, 50, string1, string1_length);


	event_mask = ButtonPressMask|ButtonReleaseMask|KeyPressMask;
	XSelectInput(dsp, win, event_mask);
	srand((int) time(0));
	int x = 1;
	int y = (x*x)+(3*x)+3;
	do{
		XNextEvent(dsp, &evt);
		if(evt.type == KeyPress)
		{
			x++;
			printf("%i\t%i", x, y);
			XDrawLine(dsp, win, gc, 0, 0, 10*x, 10*y);
			y = (x*x)+(3*x)+3;
		}
	}while(true);

	XDestroyWindow(dsp, win);
	XCloseDisplay(dsp);



	return 0;
}
