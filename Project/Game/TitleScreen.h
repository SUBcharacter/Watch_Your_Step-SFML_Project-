// TitleScreen.h
#pragma once

#include <string>     // std::string
#include <vector>     // std::vector
#include <optional>   // std::optional

#include "IntegrationLibrary.h"


class TitleScreen {
public:
    // 생성자: 배경 텍스처 파일 경로를 인자로 받습니다.
    TitleScreen(const std::string& backgroundTexturePath);

    // run 함수: 타이틀 화면의 메인 루프를 실행하고 윈도우를 업데이트합니다.
    void run(sf::RenderWindow& window); // sf::RenderWindow 타입 명시

private:
    // --- 1. 배경 관련 멤버 ---
    sf::Texture backgroundTexture;                 // 배경 이미지 텍스처 데이터
    std::optional<sf::Sprite> backgroundSprite;    // 배경 이미지를 그릴 스프라이트 (optional로 안전하게 관리)

    // --- 2. 폰트 및 타이틀 텍스트 멤버 ---
    sf::Font font;                                 // 폰트 데이터
    std::optional<sf::Text> titleText;             // 타이틀 텍스트 (optional로 안전하게 관리)

    // --- 3. 선택지 관련 멤버 ---
    std::vector<std::string> m_optionStrings;      // "게임 시작", "옵션", "나가기" 등 선택지 문자열
    std::vector<sf::Text> m_optionTexts;           // 각 선택지 문자열을 렌더링할 sf::Text 객체들
    int m_selectedOptionIndex;                     // 현재 선택된 선택지의 인덱스 (0부터 시작)

    // --- 4. 선택지 이미지 관련 멤버 (모든 스프라이트를 미리 만들고 그리기 방식) ---
    std::vector<std::string> m_optionImagePath;      // 각 선택지에 매핑될 이미지 파일 경로 (예: Assets/start.png)
    std::vector<sf::Texture> m_optionImageTextures;  // 각 선택지 이미지 텍스처 데이터 (스프라이트가 참조하므로 원본 보관)
    std::vector<sf::Sprite> m_optionImageSprites;    // 각 선택지 이미지 스프라이트 (모두 그려짐)

    // --- 5. 스타일링 및 제어 관련 멤버 ---
    const sf::Color m_defaultOptionColor = sf::Color::White; // 선택되지 않은 옵션의 색상
    const sf::Color m_highlightOptionColor = sf::Color::Yellow; // 선택된 옵션의 색상
    sf::Clock m_keyPressClock; // 키 입력 딜레이 측정을 위한 클럭
    sf::Time m_keyPressDelay = sf::milliseconds(200); // 키 입력 딜레이 시간
};