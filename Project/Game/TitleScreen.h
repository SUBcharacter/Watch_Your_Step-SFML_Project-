#pragma once
#include "IntegrationLibrary.h"

class TitleScreen {
public:
    TitleScreen(const string& backgroundTexturePath);

    void run(RenderWindow& window);

private:
    Texture backgroundTexture;
    Sprite backgroundSprite;   // 이 부분에서 기본 생성자 오류가 발생할 수 있습니다.

    Font font;
    Text titleText;            // 이 부분에서 기본 생성자 오류가 발생할 수 있습니다.
};


// 참고점
// 1. AI 의존하지 말것. AI 검색용도로만 사용할 것.
// 2. 안된다고 포기하지 말것
// 3. AI가 준 코드를 이해하고 사용할 것
//