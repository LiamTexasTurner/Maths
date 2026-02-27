#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stdio.h>
#include <string.h>
#include "orange/common.h"
#include "orange/mat.h"
#include "orange/vec.h"
#include "orange/quat.h"
#include "orange/array.h"
#include "gauss_elim.h"
#include "2d.h"
#include "3d.h"

int main(int argc, char* argv[])
{

      const char *input = argv[1];
      
      const int screen_width = 1920;
      const int screen_height = 1080;

      InitWindow(screen_width, screen_height, "raylib [core] example - 3d camera mode");

      if(strcmp(input, "2d") == 0)
      {
            two_d_mode();
      }
      if(strcmp(input, "3d") == 0)
      {
            three_d_mode();
      }

      CloseWindow();            

      return 0;
}


