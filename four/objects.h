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
  int ID; //This is for identifiaction, it should be unique.
  int X, Y; ///The X and Y positions of the upper corner of the object.
  int height, width; //The calculated height and width of an object.
  int padding; //the padding of object's borders.
  char * text; //the writing to be put into the label or the button or the text box;
};

class GraphicItem{
protected:
  Attributes attr;
public:
  GraphicItem(Attributes attributes);
  virtual void callback(){pritnf("This is a callback");}
  virtual void draw()
}

GraphicItem::GraphicItem(Attributes attributes)
{
  this->attr = attributes;

}



#endif
