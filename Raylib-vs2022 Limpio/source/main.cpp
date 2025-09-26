#include "raylib.h"
#include "presentation.h"
#include <string>

int main()
{
    const int screenW = 1000;
    const int screenH = 600;

    // Título de la ventana con tu nombre (tal como pediste)
    const std::string windowTitle = "Tarjeta - Santino Jumilla";

    InitWindow(screenW, screenH, windowTitle.c_str());
    SetTargetFPS(60);

    Presentation pres(screenW, screenH, "Santino Jumilla");

    while (!WindowShouldClose())    // Detect window close (Esc se detecta como Key)
    {
        // Salir con ESC
        if (IsKeyPressed(KEY_ESCAPE)) break;

        // Actualización lógica
        pres.Update();

        // Dibujo por frame
        BeginDrawing();
        pres.Draw();
        EndDrawing();
    }

    pres.Unload();
    CloseWindow();

    return 0;
}
