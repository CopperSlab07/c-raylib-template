#include <raylib.h>

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   450
#define FPS             60
#define BG_COLOR        0x323232FF
#define FG_COLOR        0x32FF32FF

int main(void){
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello!");
    SetTargetFPS(FPS);
    Vector2 player_origin = {
        .x = 50,
        .y = 50
    };
    Rectangle player = {
        .x      = (WINDOW_WIDTH) / 2,
        .y      = (WINDOW_HEIGHT) / 2,
        .width  = player_origin.x * 2,
        .height = player_origin.y * 2,
    };
    float rotation = 0;
    while(!WindowShouldClose()){
        rotation += GetFrameTime() * 100;
        if(rotation > 360) rotation -= 360;

        BeginDrawing();
        ClearBackground(GetColor(BG_COLOR));
        DrawRectanglePro(player, player_origin, rotation, GetColor(FG_COLOR));
        EndDrawing();
    }
    CloseWindow();
}
