// TitleScreen.h
#pragma once

#include "IntegrationLibrary.h" // SFML 3.0 ���� ��� ���� ����

enum GameState
{
    TITLE,
    GAMEPLAY,
};

enum class TitleButton {
    StartGame,
    ExitGame,
    None
};

class TitleScreen {
public:
    TitleScreen( RenderWindow& window, const std::string& backgroundTexturePath);
    ~TitleScreen();

    void run();

private:
    struct m_Sprite
    {
        Texture tex;
        Sprite spr;


    };

     RenderWindow& m_window;

     View m_titleV;
     View m_gameV;

    GameState m_state;

     Texture b_texture;
     Sprite b_Sprite;

    int m_selIdx;

    const  Color m_defCol =  Color::White;
    const  Color m_highCol =  Color::Yellow;

     Clock m_keyClk;
     Time m_keyDly;

     Texture m_indTex; // ������ ��������Ʈ�� �ؽ�ó
     Sprite m_indSpr;   // ������ ��������Ʈ

     std::vector<Sprite> m_optionBtns;


    void initViews();
    void setupElements(const std::string& b_textureP);
    void setupOptions();
    void initGPElems();

    void update(float dt);
    void render();

    void h_TitleEvs(const  Event& event);
    void h_GameEvs(const  Event& event);

    void u_TitleS(float deltaTime);
    void u_GameS(float deltaTime);
    void handleEvs();

    void r_TitleState();
    void r_GameState();

    TitleButton getBtnClicked(const  Vector2f& mousePos);
};


// 1. �ʿ��� ��.
// 2. ���赵 �����
// 3. �뵵 ��� ����