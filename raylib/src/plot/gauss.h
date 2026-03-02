#include "raylib.h"
#include <bits/stdc++.h>
using namespace std;

#define N 3

int forwardElim(double mat[N][N + 1]);

void backSub(double mat[N][N + 1]);

void gaussianElimination(double mat[N][N + 1])
{
      int singular_flag = forwardElim(mat);

      if (singular_flag != -1)
      {
            printf("Singular Matrix.\n");

            if (mat[singular_flag][N])
                  printf("Inconsistent System.");
            else
                  printf("May have infinitely many solutions.");

            return;
      }
      

      backSub(mat);
}

void swap_row(double mat[N][N + 1], int i, int j)
{
      for (int k = 0; k <= N; k++)
      {
            double temp = mat[i][k];
            mat[i][k] = mat[j][k];
            mat[j][k] = temp;
      }
}

void print(double mat[N][N + 1])
{
      for (int i = 0; i < N; i++, printf("\n"))
            for (int j = 0; j <= N; j++)
                  printf("%lf ", mat[i][j]);

      printf("\n");
}

int forwardElim(double mat[N][N + 1])
{
      for (int k = 0; k < N; k++)
      {
            int i_max = k;
            int v_max = mat[i_max][k];

            for (int i = k + 1; i < N; i++)
                  if (abs(mat[i][k]) > v_max)
                        v_max = mat[i][k], i_max = i;

            if (!mat[k][i_max])
                  return k;

            if (i_max != k)
                  swap_row(mat, k, i_max);

            for (int i = k + 1; i < N; i++)
            {
                  double f = mat[i][k] / mat[k][k];

                  for (int j = k + 1; j <= N; j++)
                        mat[i][j] -= mat[k][j] * f;

                  mat[i][k] = 0;
            }
      }
      return -1;
}

void backSub(double mat[N][N + 1])
{
      double x[N];

      for (int i = N - 1; i >= 0; i--)
      {
            x[i] = mat[i][N];

            for (int j = i + 1; j < N; j++)
            {
                  x[i] -= mat[i][j] * x[j];
            }

            x[i] = x[i] / mat[i][i];
      }
      
      DrawCube(Vector3{(float)x[0], (float)x[1], (float)x[2]}, 0.2f, 0.2f, 0.2f, MAGENTA);
}


struct vector4
{
      float x;
      float y;
      float z;
      float w;
};

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

      cam.fovy += -GetMouseWheelMove();

      cam.target = Vector3{target.x, target.y, target.z};
      cam.position = Vector3{eye.x, eye.y, eye.z};
}


static void DrawPlaneFromEquation(float a, float b, float c, float d,
                                  Vector3 centerHint, float halfSize,
                                  Color fill, Color outline)
{
      //fliped because open gl y is up and desmos is z up and different y dir 
      //Vector3 n = (Vector3){ a, c, -b };

      Vector3 n = (Vector3){ a, b, c };
      
      float nLen = Vector3Length(n);
      if (nLen < 1e-6f) return; // invalid plane

      Vector3 nHat = Vector3Scale(n, 1.0f/nLen);

      // Choose a point p0 on the plane near centerHint.
      // Project centerHint onto the plane along the normal:
      // plane: n·p = d
      // p0 = centerHint - nHat * ((n·centerHint - d)/|n|)
      float dist = (Vector3DotProduct(n, centerHint) - d) / nLen;
      Vector3 p0 = Vector3Subtract(centerHint, Vector3Scale(nHat, dist));

      // Build an orthonormal basis (u, v) spanning the plane.
      // Pick a helper vector not parallel to nHat.
      Vector3 helper = (fabsf(nHat.y) < 0.99f) ? (Vector3){0,1,0} : (Vector3){1,0,0};

      Vector3 u = Vector3Normalize(Vector3CrossProduct(nHat, helper));
      Vector3 v = Vector3Normalize(Vector3CrossProduct(nHat, u));

      float s = halfSize;

      Vector3 p1 = Vector3Add(p0, Vector3Add(Vector3Scale(u, -s), Vector3Scale(v, -s)));
      Vector3 p2 = Vector3Add(p0, Vector3Add(Vector3Scale(u, -s), Vector3Scale(v,  s)));
      Vector3 p3 = Vector3Add(p0, Vector3Add(Vector3Scale(u,  s), Vector3Scale(v,  s)));
      Vector3 p4 = Vector3Add(p0, Vector3Add(Vector3Scale(u,  s), Vector3Scale(v, -s)));

      DrawTriangle3D(p1, p2, p3, fill);
      DrawTriangle3D(p1, p3, p4, fill);
      
      DrawTriangle3D(p3, p2, p1, fill);
      DrawTriangle3D(p4, p3, p1, fill);

      DrawLine3D(p1, p2, outline);
      DrawLine3D(p2, p3, outline);
      DrawLine3D(p3, p4, outline);
      DrawLine3D(p4, p1, outline);

}

void gauss()
{

      Camera3D camera = { 0 };
      camera.position = Vector3{ 15.0f, 3.0f, 5.0f };
      camera.target = Vector3{ 0.0f, 1.0f, 0.0f };
      camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
      camera.fovy = 10.0f;
      camera.projection = CAMERA_ORTHOGRAPHIC;
    
      float camera_azimuth = -110.0f;
      float camera_altitude = 0.4f;
      float camera_distance = 30.0f;
    
      Vector3 cube_position = { 0.0f, 0.0f, 0.0f };

      SetTargetFPS(60);

      //https://www.desmos.com/3d/t8yhgcr0k9
      vector4 row1 = vector4{1.0f, 2.0f, 1.0f, 2.0f};
      vector4 row2 = vector4{3.0f, 8.0f, 1.0f, 12.f};
      vector4 row3 = vector4{0.0f, 4.0f, 1.0f, 2.0f};

      double mat[N][N + 1] = {{row1.x, row1.y, row1.z, row1.w}, {row2.x, row2.y, row2.z, row2.w}, {row3.x, row3.y, row3.z, row3.w}};


            
      
   
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

            gaussianElimination(mat);

	      DrawLine3D((Vector3){0,-8,0},(Vector3){0,8,0}, GREEN);
	      DrawLine3D((Vector3){-8,0,0},(Vector3){8,0,0}, RED);
            DrawLine3D((Vector3){0,0,8},(Vector3){0,0,-8}, BLUE);
            
	      DrawCube((Vector3){0,0,0}, 0.1, 8, 0.1, GREEN);
	      DrawCube((Vector3){0,0,0}, 8, 0.1, 0.1, RED);
            DrawCube((Vector3){0,0,0}, 0.1, 0.1, 8, BLUE);

            DrawGrid(8.5f, 1.0f);
            
            DrawCubeWires((Vector3){0,0,0}, 8, 8, 8, GRAY);

            
            DrawPlaneFromEquation( row1.x,row1.y,row1.z,row1.w,
                                  (Vector3){0,0,0},      // center hint (where to draw the patch around)
                                  5.0f,                 // half-size of the quad
                                  (Color){0,0,199,160},
                                  DARKBLUE
                                  );
            
            DrawPlaneFromEquation( row2.x,row2.y,row2.z,row2.w,
                                  (Vector3){0,0,0},      // center hint (where to draw the patch around)
                                  5.0f,                 // half-size of the quad
                                  (Color){199,0,0,160},
                                  RED
                                  );

            DrawPlaneFromEquation( row3.x,row3.y,row3.z,row3.w,
                                  (Vector3){0,0,0},      // center hint (where to draw the patch around)
                                  5.0f,                 // half-size of the quad
                                  (Color){0,199,0,160},
                                  GREEN
                                  );

            
            EndMode3D();

            EndDrawing();        
      }
      
}
