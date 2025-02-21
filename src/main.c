#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "raylib.h"

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 900
#define FPS 90
#define corFundo DARKGRAY

typedef struct
{
    int x;
    int y;
} Posicao;

typedef enum
{
    UP = 1,
    DOWN,
    LEFT,
    RIGHT
} Teclas;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Projeto Snake"); // iniciando a janela
    SetTargetFPS(FPS);
    Color LIGHTGREEN = (Color){144, 238, 144, 255};
    Color atualRec = LIGHTGREEN;
    static bool ja_foi = false;
    int macaX, macaY;
    macaX = GetRandomValue(0, 14);
    macaY = GetRandomValue(0, 14);

    int distanciaTabuleiroX = 650;
    int distanciaTabuleiroY = 75;

    // maca
    Texture2D textura_maca;
    Image maca_imagem = LoadImage("assets/img/maca.png");
    ImageResize(&maca_imagem, 50, 50); // redimensionando imagem para o tamanho do display do quadrado
    textura_maca = LoadTextureFromImage(maca_imagem);

    // cara da cobra
    Texture2D textura_cobra;

    // cobra
    Color Vermelho_cobra = (Color){255, 0, 0, 255};
    Color atualRec_cobra = Vermelho_cobra;
    int tamanho_cobra = 3;
    int direcao = RIGHT;
    float tempo_para_mudar = 0.125;
    Posicao cobra[100];

    for (int i = 0; i < tamanho_cobra; i++)
    {
        cobra[i].x = 4 - i;
        cobra[i].y = 7;
    }

    double tempo_atual = GetTime();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(corFundo);
        DrawText("Projeto Snake", 10, 10, 20, WHITE);

        // Desenhando o tabuleiro e a maça
        for (int linha = 0; linha < 15; linha++)
        {
            for (int coluna = 0; coluna < 15; coluna++)
            {
                if (coluna == 0 && linha == 0)
                    ja_foi = false;
                atualRec = (ja_foi = !ja_foi) ? LIGHTGREEN : GREEN;

                DrawRectangle(coluna * 50 + distanciaTabuleiroX, linha * 50 + distanciaTabuleiroY, 50, 50, atualRec);
            }
        }
        DrawTexture(textura_maca, macaX * 50 + distanciaTabuleiroX, macaY * 50 + distanciaTabuleiroY, WHITE);

        // cobra se movendo
        if (GetTime() - tempo_atual > tempo_para_mudar)
        {
            switch (direcao)
            {
            case UP:
                for (int i = tamanho_cobra; i > 0; i--)
                {
                    cobra[i].x = cobra[i - 1].x;
                    cobra[i].y = cobra[i - 1].y;
                }
                cobra[0].y -= 1;
                break;
            case DOWN:
                for (int i = tamanho_cobra; i > 0; i--)
                {
                    cobra[i].x = cobra[i - 1].x;
                    cobra[i].y = cobra[i - 1].y;
                }
                cobra[0].y += 1;
                break;
            case LEFT:
                for (int i = tamanho_cobra; i > 0; i--)
                {
                    cobra[i].x = cobra[i - 1].x;
                    cobra[i].y = cobra[i - 1].y;
                }
                cobra[0].x -= 1;
                break;
            case RIGHT:
                for (int i = tamanho_cobra; i > 0; i--)
                {
                    cobra[i].x = cobra[i - 1].x;
                    cobra[i].y = cobra[i - 1].y;
                }
                cobra[0].x += 1;
                break;
            default:
                break;
            }

            tempo_atual = GetTime();
        }

        // desenhando a cobra
        for (int i = 0; i < tamanho_cobra; i++)
        {
            if (i == 0)
            {
                atualRec_cobra = BLUE;
            }
            else
            {
                atualRec_cobra = Vermelho_cobra;
            }
            if (cobra[i].x == macaX && cobra[i].y == macaY)
            {
                tamanho_cobra++;
                macaX = GetRandomValue(0, 14);
                macaY = GetRandomValue(0, 14);
            }

            // identificando se ela bateu na borda, se sim ela ir para o lado oposto do mapa
            if (cobra[i].x < 0) cobra[i].x = 14; 
            else if (cobra[i].x > 14) cobra[i].x = 0;

            if (cobra[i].y < 0) cobra[i].y = 14; 
            else if (cobra[i].y > 14) cobra[i].y = 0;

            //identificando se ela bateu em si propria
            for (int j = i + 1; j < tamanho_cobra; j++)
            {
                if (cobra[i].x == cobra[j].x && cobra[i].y == cobra[j].y)
                {
                    ClearBackground(BLACK);
                    DrawText("Game Over!", (SCREEN_WIDTH - MeasureText("Game Over!", 30)) / 2, (SCREEN_HEIGHT - MeasureText("Game Over!", 30)) / 2, 30, WHITE);
                   
                }
            }

            DrawRectangle(cobra[i].x * 50 + distanciaTabuleiroX, cobra[i].y * 50 + distanciaTabuleiroY, 50, 50, atualRec_cobra);
        }

        // mudando a direção
        if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && direcao != DOWN)
        {
            direcao = UP;
        }
        else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && direcao != UP)
        {
            direcao = DOWN;
        }
        else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && direcao != RIGHT)
        {
            direcao = LEFT;
        }
        else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && direcao != LEFT)
        {
            direcao = RIGHT;
        }

        EndDrawing();
    }

    UnloadImage(maca_imagem);
    UnloadTexture(textura_maca);
    CloseWindow();

    return 0;
}
