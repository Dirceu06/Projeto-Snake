#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "raylib.h"

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 900
#define FPS 60
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

    //icon do exe
    Image icon_imagem = LoadImage("assets/img/icon.png");
    ImageResize(&icon_imagem, 64, 64); // redimensionando imagem para o tamanho do icone
    SetWindowIcon(icon_imagem);

    // maca
    Texture2D textura_maca;
    Image maca_imagem = LoadImage("assets/img/maca.png");
    ImageResize(&maca_imagem, 50, 50); 
    textura_maca = LoadTextureFromImage(maca_imagem);


    // cobra
    Color Vermelho_cobra = (Color){255, 0, 0, 255};
    Color atualRec_cobra = Vermelho_cobra;
    int tamanho_cobra = 3;
    int direcao = RIGHT;
    float tempo_para_mudar = 0.09;
    Posicao cobra[100];
    bool movi_feita=false;

    for (int i = 0; i < tamanho_cobra; i++)
    {
        cobra[i].x = 4 - i;
        cobra[i].y = 7;
    }

    //menu
    bool tela_inicial = true;
    bool tela_jogo = false;
    bool tela_gameover = false;
    int altura_botao = -150;
    double tempo_again=0;

    double tempo_atual = GetTime();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(corFundo);

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

        // mudando a direção
        if(tela_jogo && movi_feita){
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
        }

        // cobra se movendo
        if ((GetTime() - tempo_atual > tempo_para_mudar) && tela_jogo)
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
                    tela_jogo = false;
                    tela_gameover = true;                   
                }
            }
            DrawRectangle(cobra[i].x * 50 + distanciaTabuleiroX, cobra[i].y * 50 + distanciaTabuleiroY, 50, 50, atualRec_cobra);
            DrawCircle(cobra[0].x * 50 + distanciaTabuleiroX + 25, cobra[0].y * 50 + distanciaTabuleiroY + 25, 20, WHITE);
            DrawCircle(cobra[0].x * 50 + distanciaTabuleiroX + 25, cobra[0].y * 50 + distanciaTabuleiroY + 25, 10, BLACK);
            movi_feita = true;
        }

        
        
        if(tela_inicial){
            DrawText("Snake", SCREEN_WIDTH/2 - MeasureText("Snake", 50)/2 - 500, SCREEN_HEIGHT/2 - 350, 90, WHITE);

            Rectangle jogarBtn = {SCREEN_WIDTH/2 - 550, SCREEN_HEIGHT/2-50 + altura_botao, 200, 100};
            Rectangle sairBtn = {SCREEN_WIDTH/2 - 550, SCREEN_HEIGHT/2 + 60 + altura_botao, 200, 100};

            DrawRectangleRounded(jogarBtn, 0.5, 12, WHITE);
            DrawText("Jogar", SCREEN_WIDTH/2 - MeasureText("Jogar", 30)/2 - 450, SCREEN_HEIGHT/2 - 20 + altura_botao, 30, BLACK);

            DrawRectangleRounded(sairBtn, 0.5, 12, WHITE);
            DrawText("Sair", SCREEN_WIDTH/2 - MeasureText("Sair", 30)/2 - 450, SCREEN_HEIGHT/2 + 90 + altura_botao, 30, BLACK);

            Vector2 mousePoint = GetMousePosition();
            if (CheckCollisionPointRec(mousePoint, jogarBtn)) {
                DrawRectangleRounded(jogarBtn, 0.5, 12, GRAY);
                DrawText("Jogar", SCREEN_WIDTH/2 - MeasureText("Jogar", 30)/2 - 450, SCREEN_HEIGHT/2 - 20 + altura_botao, 30, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    tela_inicial = false;
                    tela_jogo = true;
                }
            }

            if (CheckCollisionPointRec(mousePoint, sairBtn)) {
                DrawRectangleRounded(sairBtn, 0.5, 12, GRAY);
                DrawText("Sair", SCREEN_WIDTH/2 - MeasureText("Sair", 30)/2 - 450, SCREEN_HEIGHT/2 + 90 + altura_botao, 30, BLACK);

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    CloseWindow();
                    return 0;
                }
            }

        }

        if (tela_gameover){
            DrawText("Game Over", SCREEN_WIDTH/2 - MeasureText("Game Over", 50)/2 - 515, SCREEN_HEIGHT/2 - 300, 90, RED);

            Rectangle gameoverBtn = {SCREEN_WIDTH/2 - 550, SCREEN_HEIGHT/2 - 50 + altura_botao, 200, 100};
            Rectangle sairBtn = {SCREEN_WIDTH/2 - 550, SCREEN_HEIGHT/2 + 60 + altura_botao, 200, 100};
            
            DrawRectangleRounded(gameoverBtn, 0.5, 12, WHITE);
            DrawText("Again", SCREEN_WIDTH/2 - MeasureText("Again", 30)/2 - 450, SCREEN_HEIGHT/2 - 20 + altura_botao, 30, BLACK);
            
            DrawRectangleRounded(sairBtn, 0.5, 12, WHITE);
            DrawText("Sair", SCREEN_WIDTH/2 - MeasureText("Sair", 30)/2 - 450, SCREEN_HEIGHT/2 + 90 + altura_botao, 30, BLACK);
            
            Vector2 mousePoint = GetMousePosition();
            if (CheckCollisionPointRec(mousePoint, gameoverBtn)) {
                DrawRectangleRounded(gameoverBtn, 0.5, 12, GRAY);
                DrawText("Again", SCREEN_WIDTH/2 - MeasureText("Again", 30)/2 - 450, SCREEN_HEIGHT/2 - 20 + altura_botao, 30, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    tela_gameover = false;
                    tela_jogo = true;
                    tamanho_cobra = 3;
                    direcao = RIGHT;
                    tempo_again=GetTime();
                    
                    
                    for (int i = 0; i < tamanho_cobra; i++)
                    {
                        cobra[i].x = 4 - i;
                        cobra[i].y = 7;
                    }
                }
            }
            
            if (CheckCollisionPointRec(mousePoint, sairBtn)) {
                DrawRectangleRounded(sairBtn, 0.5, 12, GRAY);
                DrawText("Sair", SCREEN_WIDTH/2 - MeasureText("Sair", 30)/2 - 450, SCREEN_HEIGHT/2 + 90 + altura_botao, 30, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    CloseWindow();
                    return 0;
                }
            }
        }
        
        if(tela_jogo || tela_gameover){
            DrawText("Pontuação:", SCREEN_WIDTH/2 - MeasureText("Pontuação", 50)/2 - 550, SCREEN_HEIGHT/2 - 375, 80, WHITE);
            char PontuacaoText[10];
            sprintf(PontuacaoText, "%i", tamanho_cobra - 3);
            DrawText(PontuacaoText, SCREEN_WIDTH/2 - MeasureText("Pontuação", 50)/2 - 65, SCREEN_HEIGHT/2 - 375, 80, WHITE);
            //desenhando um timer no canto inferior esquerdo
            DrawText("Tempo:", 50, SCREEN_HEIGHT - 50, 30, WHITE);
            char TempoText[10];
            if(tela_jogo){
                sprintf(TempoText, " %.2f", GetTime()-tempo_again);
            }
            DrawText(TempoText, 150, SCREEN_HEIGHT - 50, 30, WHITE);
        }
        EndDrawing();
    }


    UnloadImage(maca_imagem);
    UnloadImage(icon_imagem);
    UnloadTexture(textura_maca);
    CloseWindow();

    return 0;
}
