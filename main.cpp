#include "raylib.h"

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 700;

    const int playerSpeed = 8;
    const int ballSpeedIncrease = 1; // 1

    const int player1Height = 100; // 100
    const int player1Width = 20; // 20

    const int player2Height = 100;
    const int player2Width = 20;

    const int ballSize = 20; // 10

    int ballSpeed = 3;
    int yIncrement = 1;
    int xIncrement = 1;

    int player1Score = 0;
    int player2Score = 0;

    InitWindow(screenWidth, screenHeight, "Brypong");

    Rectangle player1 = { 30, (float)screenHeight/2-50, player1Width, player1Height };
    Rectangle player2 = { screenWidth-50, (float)screenHeight/2-50, player2Width, player2Height };

    Rectangle ball = { (float)screenWidth/2, (float)screenHeight/2, ballSize, ballSize };

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        // PLayer Inputs Handling
        if(IsKeyDown(KEY_W) && player1.y >= 10) player1.y -= playerSpeed;
        if(IsKeyDown(KEY_S) && player1.y <= screenHeight-player1.height-10) player1.y += playerSpeed;

        if(IsKeyDown(KEY_UP) && player2.y >= 10) player2.y -= playerSpeed;
        if(IsKeyDown(KEY_DOWN) && player2.y <= screenHeight-player2.height-10) player2.y += playerSpeed;

        // Move Ball
        ball.x += ballSpeed * xIncrement;
        ball.y += ballSpeed * yIncrement;
        if (ball.y <= 10) {
            yIncrement = 1;
        } else if (ball.y >= screenHeight-ballSize) {
            yIncrement = -1;
        }
        if (CheckCollisionRecs(ball, player1)) {
            xIncrement = 1;
            ballSpeed += ballSpeedIncrease;
        } else if (CheckCollisionRecs(ball, player2)) {
            xIncrement = -1;
            ballSpeed += ballSpeedIncrease;
        }

        // Check Bounds
        if (ball.x <= 0) {
            ball.x = (float)screenWidth/2;
            ball.y = (float)screenHeight/2;
            player2Score += 1;
            ballSpeed = 3;
        } else if (ball.x >= screenWidth) {
            ball.x = (float)screenWidth/2;
            ball.y = (float)screenHeight/2;
            player1Score += 1;
            ballSpeed = 3;
        }

        // Draw
        BeginDrawing();
            
            ClearBackground(BLACK);
            
            DrawRectangleRec(player1, WHITE);
            DrawRectangleRec(player2, WHITE);

            DrawRectangleRec(ball, WHITE);

            // Render Points
            DrawText(TextFormat("%d", player1Score), screenWidth/2-270, 50, 50, WHITE);
            DrawText(TextFormat("%d", player2Score), screenWidth/2+270, 50, 50, WHITE);

            DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
