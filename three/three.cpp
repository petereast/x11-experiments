#include <cstdio>
#include "objects.h"
#include <iostream>

int main(int argc, char* argv[])
{
  printf("hello world");
  X11_data xd = initialise_x11(1000, 100);
  TextBox(xd, 12, 12, "HEllo world!", "9*15");

  while(true)
  {
    drawGraphics();
  }

  return 0;
}
