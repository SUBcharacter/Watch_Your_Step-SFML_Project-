// TitleScreen.h
#pragma once

#include "IntegrationLibrary.h" // SFML 3.0 ���� ��� ���� ����
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
                cout << "�ؽ�ó ����" << endl;
            }
            Vector2i sizeI = { static_cast<int>(size.x), static_cast<int>(size.y) };
            spr.setTextureRect({ {0,0},sizeI});
            spr.setOrigin(size / 2.f); //setOrigin->��������Ʈ ���� ��ǥ
            spr.setPosition(pos); // setPosition->���� ��ǥ
        }

    };
    GameState state = TITLE;

    bool isPaused = false;
    bool wasLastPressed = false;

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

    void UpdateTitle(RenderWindow& window, Camera& camera);

    void UpdatePaused(RenderWindow& window, Camera& camera);

    void UpdateClear(RenderWindow& window, Camera& camera);
    
};


// 1. �ʿ��� ��.
// 2. ���赵 �����
// 3. �뵵 ��� ����