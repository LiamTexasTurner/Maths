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
#include "parabola.h"
#include "gauss.h"

int main(int argc, char* argv[])
{

      const char *input = argv[1];
      
      const int screen_width = 1920;
      const int screen_height = 1080;

      InitWindow(screen_width, screen_height, "raylib [core] example - 3d camera mode");

      if(strcmp(input, "parabola") == 0)
      {
            parabola();
      }
      if(strcmp(input, "gauss") == 0)
      {
            gauss();
      }

      CloseWindow();            

      return 0;
}


