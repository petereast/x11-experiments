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
  while(true)
  {
    //printf("test\n");
    tb.Draw(false);
  }

  return 0;
}
