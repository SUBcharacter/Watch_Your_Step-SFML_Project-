// TitleScreen.h
#pragma once

#include "IntegrationLibrary.h" // SFML 3.0 관련 헤더 포함 가정
#include "Camera.h"
#include "GameManager.h"

enum GameState
{
    TITLE,
    GAMEPLAY,
    CLEAR,
    EXIT
};

enum class TitleButton {
    StartGame,
    ExitGame,
    None
};

class TitleScreen {
private:
    struct SpriteUse
    {
        Texture tex;
        Sprite spr;


        SpriteUse(const string& texturePath, Vector2f size, Vector2f pos)
            :spr(tex)
        {
            if (!tex.loadFromFile(texturePath))
            {
                cout << "텍스처 없음" << endl;
            }
            Vector2i sizeI = { static_cast<int>(size.x), static_cast<int>(size.y) };
            spr.setTextureRect({ {0,0},sizeI});
            spr.setOrigin(size / 2.f); //setOrigin->스프라이트 내부 좌표
            spr.setPosition(pos); // setPosition->월드 좌표
        }

    };
    GameState state = TITLE;

    bool isPaused = false;
    bool wasLastPressed = false;
    Vector2f playerStart = { 1000, 100 };

    SpriteUse backGround;
    SpriteUse startGame;
    SpriteUse exitGame;

    SpriteUse pauseBack;
    SpriteUse continueGame;
    SpriteUse breakGame;

    SpriteUse clearBack;
    SpriteUse repeatGame;


   
public:

    TitleScreen();
  
    void run();

    void Draw(RenderWindow& window);

    void UpdateTitle(RenderWindow& window, Camera& camera, Player& player);

    void UpdatePaused(RenderWindow& window, Camera& camera);

    void UpdateClear(RenderWindow& window, Camera& camera, Player& player);
    
};