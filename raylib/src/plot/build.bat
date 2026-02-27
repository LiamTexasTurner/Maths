@echo off
g++ main.cpp -o ..\..\build\plot\plot.exe -std=c++17 -I"c:\raylib_src\src" -L"c:\raylib_src\src" -lraylib -lopengl32 -lgdi32 -lwinmm && call c:\Maths\raylib\build\plot\plot.exe "3d"
