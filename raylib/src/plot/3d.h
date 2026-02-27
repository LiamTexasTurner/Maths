#include "raylib.h"

float orbit_camera_update_azimuth(const float azimuth,
                                  const float mouse_dx,
                                  const float dt)
{
      return azimuth + 1.0f * dt * -mouse_dx;
}

float orbit_camera_update_altitude(const float altitude,
                                   const float mouse_dy,
                                   const float dt)
{
      return clampf(altitude + 1.0f * dt * mouse_dy, 0.0, 0.4f * PIf);
}

float otbit_camera_update_distance(const float distace,
                                  const float dt)
{
      return clampf(distace + 20.f * dt * -GetMouseWheelMove() * 20.0f, 0.1f, 100.0f);
}

void orbit_camera_update(Camera& cam,
                         float& camera_azimuth,
                         float& camera_altitude,
                         float& camera_distance,
                         const vec3 target,
                         const float mouse_dx,
                         const float mouse_dy,
                         const float dt)
{
      camera_azimuth = orbit_camera_update_azimuth(camera_azimuth, mouse_dx, dt);
      camera_altitude = orbit_camera_update_altitude(camera_altitude, mouse_dy, dt);
      camera_distance = otbit_camera_update_distance(camera_distance, dt);
      
      quat rotation_azimuth = quat_from_angle_axis(camera_azimuth, vec3(0,1,0));
      vec3 position = quat_mul_vec3(rotation_azimuth, vec3(0,0,camera_distance));
      vec3 axis = normalize(cross(position, vec3(0,1,0)));

      quat rotation_altitude = quat_from_angle_axis(camera_altitude, axis);

      vec3 eye = target + quat_mul_vec3(rotation_altitude, position);

      cam.target = Vector3{target.x, target.y, target.z};
      cam.position = Vector3{eye.x, eye.y, eye.z};
      
}


void three_d_mode()
{

      Camera3D camera = { 0 };
      camera.position = Vector3{ 15.0f, 3.0f, 5.0f };
      camera.target = Vector3{ 0.0f, 1.0f, 0.0f };
      camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
      camera.fovy = 45.0f;
      camera.projection = CAMERA_PERSPECTIVE;
    
      float camera_azimuth = -5.0f;
      float camera_altitude = 0.4f;
      float camera_distance = 30.0f;
    
      
      Vector3 cube_position = { 0.0f, 0.0f, 0.0f };

      SetTargetFPS(60);
   
      while (!WindowShouldClose())   
      {
            BeginDrawing();

            if (IsKeyPressed(KEY_Q))   
            {
                  break;                 
            }

            orbit_camera_update(
            camera, 
            camera_azimuth,
            camera_altitude,
            camera_distance,
            vec3(0, 1, 0),
            (IsMouseButtonDown(0)) ? GetMouseDelta().x : 0.0f,
            (IsMouseButtonDown(0)) ? GetMouseDelta().y : 0.0f,
            GetFrameTime() * 0.1f);
        

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

	      DrawLine3D((Vector3){0,-100,0},(Vector3){0,100,0}, GREEN);
	      DrawLine3D((Vector3){-100,0,0},(Vector3){100,0,0}, RED);
            DrawLine3D((Vector3){0,0,100},(Vector3){0,0,-100}, BLUE);
            
	      DrawCube((Vector3){0,0,0}, 0.1, 1000, 0.1, GREEN);
	      DrawCube((Vector3){0,0,0}, 1000, 0.1, 0.1, RED);
            DrawCube((Vector3){0,0,0}, 0.1, 0.1, 1000, BLUE);

            DrawGrid(25.5f, 1.0f);
            
            DrawCubeWires((Vector3){0,0,0}, 24, 24, 24, GRAY);
            
            EndMode3D();

            EndDrawing();        
      }
      
}
