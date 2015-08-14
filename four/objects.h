#ifndef OBJECTS_H
#define OBJECTS_H 0x1
//README:
//This is the header containing all of the functions and classes used for creating
//and adjusting the graphics objects.

//DEFINE the macros:
#define NONETYPE 0x00
#define LINE 0x01
#define RECT 0x02
#define TEXTBOX 0x03
#define BUTTON 0x04
#define ENTRY 0x05
#define CHECKBOX 0x06
#define LABEL 0x07
#define WRAPPED_TEXT 0x08

struct Attributes{ //This will contain all of the possible attributes for the graphics
                  //items, it'll be a member of the parent class so that it'll always
                 //be accessable regardless of the type.
  int TYPE; //This'll be a macro from 0 to whatever, to be added as we go along.
           //For example: Attriblutes.TYPE = TEXTBOX;


};



#endif
