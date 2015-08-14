#include <cstdio>
#include "objects.h"
#include <iostream>

int main(int argc, char* argv[])
{
  printf("hello world\n");
  X11_data xd = initialise_x11(1000, 100);
  printf("hello world\n");
  TextBox tb = TextBox(xd, 12, 12, "HEllo world!", "9*15");
  tb.setId("textbox1");
  addGraphicItem(tb);
  //TODO: Create a reference system that will allow events to be passed to and from
  //using a really easy function like OGetNextEvent(xd, [XEventMask])
  while((getNextEvent(xd, StructureNotifyMask | KeyPressMask)) != NULL)
  {
    //printf("test\n");
    tb.Draw(false);
    //At this point I have realised that there are critical failures in the
    //underlying infastructure that this software will eventually rely on
    //a render pipeline and a stack of discriptive objects which is passed into a
    //rendering function.
  }

  return 0;
}
