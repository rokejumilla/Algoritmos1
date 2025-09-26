#ifndef PRESENTATION_H
#define PRESENTATION_H

#include "raylib.h"
#include <string>
#include <vector>

class Presentation {
public:
    Presentation(int screenW, int screenH, const std::string& ownerName);
    void Update();   // lógica de entrada
    void Draw();     // dibujado por frame
    void Unload();   // por si necesitamos liberar recursos

private:
    int screenW, screenH;
    std::string ownerName;

    // Mensajes secundarios (se recorren al presionar SPACE)
    std::vector<std::string> messages;
    int msgIndex; // índice actual en messages

    // Mostrar u ocultar notas (la parte que "ten en cuenta")
    bool showNotes;

    // Colores personalizados
    Color darkRed;
    Color lightRed;
    Color figureColor;
};

#endif // PRESENTATION_H
