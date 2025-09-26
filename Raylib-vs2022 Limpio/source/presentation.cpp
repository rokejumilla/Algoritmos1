#include "presentation.h"
#include "raylib.h"
#include <string>
#include <vector>

// Constructor
Presentation::Presentation(int screenW, int screenH, const std::string& ownerName)
    : screenW(screenW), screenH(screenH), ownerName(ownerName),
    msgIndex(0), showNotes(false)
{
    // Inicializar mensajes (las 2 originales + las 2 que pediste)
    messages.push_back("Estoy cursando algoritmos 1");
    messages.push_back("Esta es una plantilla de presentación");
    messages.push_back("estoy haciendo el primer ejercicio");
    messages.push_back("Esta es mi carta de presentación");

    // Asignar canales de color explícitamente (evita problemas de inicialización)
    darkRed.r = 139; darkRed.g = 0;   darkRed.b = 0;   darkRed.a = 255;
    lightRed.r = 255; lightRed.g = 102; lightRed.b = 102; lightRed.a = 255;

    // color de la figura (usamos rojo claro)
    figureColor.r = lightRed.r;
    figureColor.g = lightRed.g;
    figureColor.b = lightRed.b;
    figureColor.a = lightRed.a;
}

void Presentation::Update()
{
    // Avanzar al siguiente mensaje con la tecla SPACE (recorre el vector)
    if (IsKeyPressed(KEY_SPACE)) {
        if (!messages.empty()) {
            msgIndex = (msgIndex + 1) % (int)messages.size();
        }
    }

    // Mostrar/ocultar las notas de entrega con 'E'
    if (IsKeyPressed(KEY_E)) showNotes = !showNotes;
}

void Presentation::Draw()
{
    // Fondo: rojo oscuro
    ClearBackground(darkRed);

    // Texto principal (nombre) centrado
    int fontSize = 40;
    int textW = MeasureText(ownerName.c_str(), fontSize);
    int x = (screenW - textW) / 2;
    int y = screenH / 4;
    DrawText(ownerName.c_str(), x, y, fontSize, RAYWHITE);

    // Figura: rectángulo
    Rectangle rect = { (float)(screenW / 2 - 120), (float)(screenH / 2 - 40), 240.0f, 80.0f };
    DrawRectangleRec(rect, figureColor); // rectángulo con color personalizado

    // Borde del rectángulo: uso DrawRectangleLines (firmas clásicas)
    DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, LIGHTGRAY);

    // Mensaje secundario: se toma del vector messages según msgIndex
    std::string currentMsg = " "; // por defecto un espacio para evitar MeasureText(0)
    if (!messages.empty()) currentMsg = messages[msgIndex];

    // Alternar color según índice (ejemplo: índices pares -> lightRed, impares -> blanco)
    Color currentColor = (msgIndex % 2 == 0) ? lightRed : RAYWHITE;

    int subFont = 20;
    int subW = MeasureText(currentMsg.c_str(), subFont);
    int subX = (screenW - subW) / 2;
    int subY = (int)(rect.y + rect.height + 20);
    DrawText(currentMsg.c_str(), subX, subY, subFont, currentColor);

    // Instrucciones
    DrawText("Presione SPACE para cambiar mensaje.", 10, screenH - 60, 16, RAYWHITE);
    DrawText("Presione E para ver/ocultar las notas de entrega. Presione ESC para salir.", 10, screenH - 40, 16, RAYWHITE);

    // Mostrar notas (si corresponde). Dibujo con DrawText por línea (evita DrawTextRec)
    if (showNotes) {
        // Recuadro semitransparente
        Rectangle rec = { 40.0f, 40.0f, (float)(screenW - 80), 160.0f };
        Color bg = { 0, 0, 0, 160 };
        DrawRectangleRec(rec, bg);
        DrawRectangleLines((int)rec.x, (int)rec.y, (int)rec.width, (int)rec.height, LIGHTGRAY);

        // Texto multilinea: separamos por '\n' y dibujamos línea a línea
        std::vector<std::string> lines;
        std::string notes =
            "NOTAS SOBRE ENTREGAS (Lucas):\n"
            " - Entregas completas: solucion VS2022, con todos .cpp y .h.\n"
            " - No se evaluaran entregas sueltas (.cpp solitario, .sln suelto, estructuras incompletas).\n"
            " - Debe incluir Raylib integrado (o lib/include correctamente configurados).\n"
            " - Si dudas: revisar apuntes y el proyecto base antes de preguntar.";

        // Split simple por '\n'
        size_t start = 0;
        while (true) {
            size_t pos = notes.find('\n', start);
            if (pos == std::string::npos) {
                lines.push_back(notes.substr(start));
                break;
            }
            else {
                lines.push_back(notes.substr(start, pos - start));
                start = pos + 1;
            }
        }

        int fontSizeNotes = 14;
        int lineSpacing = 4;
        int drawX = (int)rec.x + 8;
        int drawY = (int)rec.y + 8;
        for (size_t i = 0; i < lines.size(); ++i) {
            DrawText(lines[i].c_str(), drawX, drawY + (int)i * (fontSizeNotes + lineSpacing), fontSizeNotes, RAYWHITE);
        }
    }
}

void Presentation::Unload()
{
    // Si hubieras cargado recursos (fuentes o texturas) los liberarías aquí
}
