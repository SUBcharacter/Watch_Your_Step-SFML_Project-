// TitleScreen.h
#pragma once

#include <string>     // std::string
#include <vector>     // std::vector
#include <optional>   // std::optional

#include "IntegrationLibrary.h"


class TitleScreen {
public:
    // ������: ��� �ؽ�ó ���� ��θ� ���ڷ� �޽��ϴ�.
    TitleScreen(const std::string& backgroundTexturePath);

    // run �Լ�: Ÿ��Ʋ ȭ���� ���� ������ �����ϰ� �����츦 ������Ʈ�մϴ�.
    void run(sf::RenderWindow& window); // sf::RenderWindow Ÿ�� ���

private:
    // --- 1. ��� ���� ��� ---
    sf::Texture backgroundTexture;                 // ��� �̹��� �ؽ�ó ������
    std::optional<sf::Sprite> backgroundSprite;    // ��� �̹����� �׸� ��������Ʈ (optional�� �����ϰ� ����)

    // --- 2. ��Ʈ �� Ÿ��Ʋ �ؽ�Ʈ ��� ---
    sf::Font font;                                 // ��Ʈ ������
    std::optional<sf::Text> titleText;             // Ÿ��Ʋ �ؽ�Ʈ (optional�� �����ϰ� ����)

    // --- 3. ������ ���� ��� ---
    std::vector<std::string> m_optionStrings;      // "���� ����", "�ɼ�", "������" �� ������ ���ڿ�
    std::vector<sf::Text> m_optionTexts;           // �� ������ ���ڿ��� �������� sf::Text ��ü��
    int m_selectedOptionIndex;                     // ���� ���õ� �������� �ε��� (0���� ����)

    // --- 4. ������ �̹��� ���� ��� (��� ��������Ʈ�� �̸� ����� �׸��� ���) ---
    std::vector<std::string> m_optionImagePath;      // �� �������� ���ε� �̹��� ���� ��� (��: Assets/start.png)
    std::vector<sf::Texture> m_optionImageTextures;  // �� ������ �̹��� �ؽ�ó ������ (��������Ʈ�� �����ϹǷ� ���� ����)
    std::vector<sf::Sprite> m_optionImageSprites;    // �� ������ �̹��� ��������Ʈ (��� �׷���)

    // --- 5. ��Ÿ�ϸ� �� ���� ���� ��� ---
    const sf::Color m_defaultOptionColor = sf::Color::White; // ���õ��� ���� �ɼ��� ����
    const sf::Color m_highlightOptionColor = sf::Color::Yellow; // ���õ� �ɼ��� ����
    sf::Clock m_keyPressClock; // Ű �Է� ������ ������ ���� Ŭ��
    sf::Time m_keyPressDelay = sf::milliseconds(200); // Ű �Է� ������ �ð�
};