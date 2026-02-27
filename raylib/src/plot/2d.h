float Parabola_1(float x)
{
      return (x - 5) * (5 * x + 2);
}
float Parabola_2(float x)
{
      return (-1.0f/3.0f) * (x+2)*(x+8);
}
float Parabola_3(float x)
{
      return 3 * (x+2)*(x+2) - 4;
}

float plot_one(float x)
{
      return (float)(x + 3.0f) / 2.0f;
}
float plot_two(float x)
{
      return 2.0f * x;
}

void plot_line(float (*func)(float), Color col)
{
      Vector3 old_pos = (Vector3){-50.f, -50.f, 1.0f};
      for(int i = -50; i < 50; i++)
      {
            float x = (float)i;
            float y = func(x);
            Vector3 pos = (Vector3){x, y, 1.0f};
            DrawCube(pos, 0.1f, 0.1f, 0.1f, col);
            DrawCylinderEx(old_pos, pos, 0.1f, 0.1f, 8, col);
            old_pos = pos;
      }
}

void PlotParabola(float (*func)(float))
{
	float xMin = -50;
	float xMax = 50;
	float step = 0.25f;
	Vector3 oldPos = {-100,-100,0 };
      bool hasOld = false;

      for (float x = xMin; x <= xMax; x += step)
      {
            float y = func(x);

            Vector3 newPos = (Vector3){ x, y, 1.0f };

            DrawCube(newPos, 0.1f, 0.1f, 0.1f, MAGENTA);
		
            DrawCylinderEx(oldPos, newPos, 0.05f, 0.05f, 8, MAGENTA);

            oldPos = newPos;        
      }
}


void two_d_mode()
{
      Camera3D camera = { 0 };
      camera.position = (Vector3){ 0.0f, 0.0f, 50.0f }; 
      camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };     
      camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         
      camera.fovy = 25.0f;                               
      camera.projection = CAMERA_ORTHOGRAPHIC;

      Vector3 cube_position = { 0.0f, 0.0f, 0.0f };

      SetTargetFPS(60);
   
      while (!WindowShouldClose())   
      {
            BeginDrawing();

            if (IsKeyPressed(KEY_Q))   
            {
                  break;                 
            }

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
	      // for(int i = 0; i < 50; i ++)
	      // {
	      // 	int GridPoint = i - 25;
	      // 	DrawLine3D(Vector3{GridPoint, -100,0},Vector3{GridPoint,100,0}, GRAY);
	      // 	DrawLine3D(Vector3{-100, GridPoint,0},Vector3{100,GridPoint,0}, GRAY);
	      // }

	      DrawLine3D(Vector3{0,-100,0},Vector3{0,100,0}, GREEN);
	      DrawLine3D(Vector3{-100,0,0},Vector3{100,0,0}, RED);
            
	      DrawCube(Vector3{0,0,0}, 0.1, 1000, 0.1, GREEN);
	      DrawCube(Vector3{0,0,0}, 1000, 0.1, 0.1, RED);

            plot_line(plot_one, MAGENTA);
            
            EndMode3D();

            EndDrawing();        
      }
      
}
