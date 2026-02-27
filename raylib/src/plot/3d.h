void three_d_mode()
{
      Camera3D camera = { 0 };
      camera.position = (Vector3){ 10.0f, 50.0f, 50.0f }; 
      camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };     
      camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         
      camera.fovy = 25.0f;                               
      camera.projection = CAMERA_PERSPECTIVE;

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

	      DrawLine3D((Vector3){0,-100,0},(Vector3){0,100,0}, GREEN);
	      DrawLine3D((Vector3){-100,0,0},(Vector3){100,0,0}, RED);
            DrawLine3D((Vector3){0,0,100},(Vector3){0,0,-100}, BLUE);
            
	      DrawCube((Vector3){0,0,0}, 0.1, 1000, 0.1, GREEN);
	      DrawCube((Vector3){0,0,0}, 1000, 0.1, 0.1, RED);
            DrawCube((Vector3){0,0,0}, 0.1, 0.1, 1000, BLUE);
            
            EndMode3D();

            EndDrawing();        
      }
      
}
