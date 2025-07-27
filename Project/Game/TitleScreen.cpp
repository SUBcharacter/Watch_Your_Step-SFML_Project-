#include "TitleScreen.h" // �ڽ��� ��� ���� ����

// ǥ�� ���̺귯�� �����
#include <iostream>      
// ���ڿ�, ���� ��
#include <string>        
#include <vector>
#include <algorithm> // std::min ��� ���� ����

// TitleScreen Ŭ������ ������ ����
// ��ü�� ������ �� ���, ��Ʈ, �ؽ�Ʈ, ������ �̹��� �� ��� �ڿ��� �ε��ϰ� �ʱ�ȭ�մϴ�.
TitleScreen::TitleScreen(const string& backgroundTexturePath)
{
    // --- 1. ��� �ؽ�ó �ε� ---
    if (!backgroundTexture.loadFromFile(backgroundTexturePath))
    {
        cerr << "����: ��� �ؽ�ó(" << backgroundTexturePath << ")�� �ε��� �� �����ϴ�." << endl;
    }
    else // �ε� ���� �ÿ��� ��������Ʈ ����
    {
        backgroundSprite.emplace(backgroundTexture); // optional �ȿ� sf::Sprite ����
    }

    // --- 2. ��Ʈ �ε� ---
    // 'openFromFile'�� 'loadFromFile'�� ����. ��Ʈ �ε� ���� �ÿ��� �޽����� ǥ�������� ������ ���.
    if (!font.openFromFile("Assets/KoPubWorld Batang Bold.ttf"))
    {
        cerr << "����: ��Ʈ (Assets/KoPubWorld Batang Bold.ttf)�� �ε��� �� �����ϴ�." << endl;
        // ��Ʈ �ε� ���� �� �ؽ�Ʈ ��ü���� emplace���� �ʾ� draw()���� �ڵ����� �ɷ����� ��.
    }
    else // ��Ʈ �ε� ���� �ÿ��� �ؽ�Ʈ ��ü�� ���� �� ����
    {
        // --- 3. Ÿ��Ʋ �ؽ�Ʈ ���� ---
        titleText.emplace(font); // optional �ȿ� sf::Text ���� (font ���ڷ� ����)
        titleText->setString("Welcome to the TitleScreen Screen!");
        titleText->setCharacterSize(48);
        titleText->setFillColor(Color::White);

        // --- 4. ������ ���ڿ� �� �̹��� ��� ���� ---
        m_optionStrings = { "���� ����", "�ɼ�", "������" };
        m_optionImagePath = {
            "Assets/TextBTN_Big.png",
            "Assets/TextBTN_Big.png",
            "Assets/TextBTN_Big.png"
        };
        m_selectedOptionIndex = 0; // �ʱ� ������ ù ��° �ɼ�

        // --- 5. �� ������ �ؽ�Ʈ ��ü ���� �� �⺻ ���� ---
        m_optionTexts.clear(); // Ȥ�� �� ���� ������ Ŭ����
        for (size_t i = 0; i < m_optionStrings.size(); ++i) {
            sf::Text optionText(font); // ��Ʈ�� ���ڷ� �����Ͽ� sf::Text ��ü ����
            optionText.setString(m_optionStrings[i]);
            optionText.setCharacterSize(36);      // ������ �ؽ�Ʈ ũ��
            optionText.setFillColor(m_defaultOptionColor); // �⺻ ����
            m_optionTexts.push_back(optionText); // ���Ϳ� �߰�
        }

        // --- 6. �� ������ �̹��� �ؽ�ó �ε� �� ��������Ʈ ���� ---
        m_optionImageTextures.clear(); // ���� Ŭ����
        m_optionImageSprites.clear();  // ���� Ŭ����

        for (const auto& path : m_optionImagePath) {
            sf::Texture texture;
            if (!texture.loadFromFile(path)) {
                cerr << "����: �ɼ� �̹���(" << path << ")�� �ε��� �� �����ϴ�." << endl;
                m_optionImageTextures.emplace_back(); // �� �ؽ�ó �߰� (���� ũ�� ������ ����)
                m_optionImageSprites.emplace_back(); // �� ��������Ʈ �߰� (sf::Sprite �⺻ ������ ���� ����)
            }
            else {
                m_optionImageTextures.push_back(std::move(texture)); // �ؽ�ó �̵��Ͽ� �߰�
                // m_optionImageTextures.back()�� ������ ������ �ؽ�ó�� ���� ������ ��ȯ�մϴ�.
                // sf::Sprite�� Texture�� ���� ������ �����ϹǷ�, Texture�� �Ҹ�Ǹ� �� �˴ϴ�.
                m_optionImageSprites.emplace_back(m_optionImageTextures.back());
            }
        }
    } // End of font.loadFromFile else block
}


// run �Լ�: Ÿ��Ʋ ȭ���� ���� ������ �����ϰ� �����츦 ������Ʈ�մϴ�.
// �� �Լ��� �����찡 �����ִ� ���� ȭ���� ǥ���ϰ� �̺�Ʈ�� ó���մϴ�.
void TitleScreen::run(sf::RenderWindow& window) // sf::RenderWindow Ÿ�� ���
{
    // --- A. �ʱ� ��ġ, ũ��, ���� ���� (�� �Լ� ȣ�� �� �� �� ���� ����) ---
    sf::Vector2u windowSize = window.getSize(); // ���� ������ ũ�� ��������
    float centerX = static_cast<float>(windowSize.x / 2.0f);
    float centerY = static_cast<float>(windowSize.y / 2.0f);

    // 1. ��� ��������Ʈ ũ�� �� ��ġ ����
    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0) { // �ؽ�ó ��ȿ�� �˻�
        float scaleX = static_cast<float>(windowSize.x) / backgroundTexture.getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / backgroundTexture.getSize().y;
        if (backgroundSprite.has_value()) { // optional�� ���� �ִ��� Ȯ��
            backgroundSprite->setScale({ scaleX, scaleY }); // â ũ�⿡ �°� ������ ����
            backgroundSprite->setPosition({ 0.f, 0.f }); // �»�ܿ� ��ġ
        }
    }

    // 2. Ÿ��Ʋ �ؽ�Ʈ ��ġ �� ���� ����
    if (titleText.has_value()) { // optional�� ���� �ִ��� Ȯ��
        sf::FloatRect textRect = titleText->getLocalBounds();
        // �ؽ�Ʈ �߾��� �������� ���� (SFML 3.0.0�� sf::FloatRect ���: position.x, position.y)
        titleText->setOrigin({ (textRect.position.x + textRect.size.x / 2.0f),
                               (textRect.position.y + textRect.size.y / 2.0f) });
        titleText->setPosition({ centerX, centerY - 150.f }); // ȭ�� �߾� ��ܿ� ��ġ
    }

    // 3. ������ �ؽ�Ʈ�� ��ġ �� ���� ����
    float optionStartY = centerY + 50.f; // �ɼ� ��� ���� Y ��ǥ
    for (size_t i = 0; i < m_optionTexts.size(); ++i) {
        sf::FloatRect optionRect = m_optionTexts[i].getLocalBounds();
        // �� ������ �ؽ�Ʈ�� �߾��� �������� ����
        m_optionTexts[i].setOrigin({ (optionRect.position.x + optionRect.size.x / 2.0f),
                                     (optionRect.position.y + optionRect.size.y / 2.0f) });
        // �� ������ �ؽ�Ʈ�� ������ ��ġ�� ��ġ (���η� ����)
        m_optionTexts[i].setPosition({ centerX, optionStartY + i * 50.f });
    }

    // 4. ������ �̹��� ��������Ʈ�� ��ġ �� ���� ����
    // �� �̹����� ��ġ�� �ش��ϴ� �ؽ�Ʈ�� ��ġ ��ó�� ��ġ
    for (size_t i = 0; i < m_optionImageSprites.size(); ++i)
    {
        const sf::Texture& texture = m_optionImageSprites[i].getTexture();
        if (texture.getSize().x > 0 && texture.getSize().y > 0) {
            std::cout << "Sprite " << i << " has a valid texture. Processing..." << std::endl;
            { // optional�� ���� �ִ��� Ȯ��
                sf::FloatRect imageRect = m_optionImageSprites[i].getLocalBounds();
                // �̹��� �߾��� �������� ����
                m_optionImageSprites[i].setOrigin({ (imageRect.position.x + imageRect.size.x / 2.0f),
                                                     (imageRect.position.y + imageRect.size.y / 2.0f) });
                // �� �̹����� �ش� �ؽ�Ʈ ��(���� 150�ȼ�)�� ��ġ (���� �ʿ�)
                m_optionImageSprites[i].setPosition({ centerX - 150.f, optionStartY + i * 50.f });
                m_optionImageSprites[i].setScale({ 0.5f, 0.5f }); // �⺻ ũ�� ���� (�ʿ��)
            }
        }

        // --- B. ���� ���� ���� ---
        while (window.isOpen()) {
            // --- 1. �̺�Ʈ ó�� ---
            while (const optional<sf::Event> eventOpt = window.pollEvent()) // SFML 3.0.0 �̺�Ʈ ����
            {
                const sf::Event& event = *eventOpt; // optional���� ���� sf::Event ����

                // ���� �̺�Ʈ (â �ݱ�, ESC�� ����)
                if (event.is<sf::Event::Closed>()) {
                    window.close();
                    return; // �Լ� ����
                }
                else if (const auto* keypressed = event.getIf<sf::Event::KeyPressed>()) {
                    // Ű �Է� ������ üũ (���� �ݺ� �Է� ����)
                    if (m_keyPressClock.getElapsedTime() < m_keyPressDelay) {
                        continue; // ������ �ð� ������ �Է� ����
                    }
                    m_keyPressClock.restart(); // ������ Ŭ�� �����

                    // ����Ű ó��
                    if (keypressed->scancode == sf::Keyboard::Scancode::Up) {
                        m_selectedOptionIndex = (m_selectedOptionIndex - 1 + m_optionTexts.size()) % m_optionTexts.size();
                    }
                    else if (keypressed->scancode == sf::Keyboard::Scancode::Down) {
                        m_selectedOptionIndex = (m_selectedOptionIndex + 1) % m_optionTexts.size();
                    }
                    // Enter �Ǵ� Escape Ű �Է� �� ���� (�׽�Ʈ��)
                    else if (keypressed->scancode == sf::Keyboard::Scancode::Enter ||
                        keypressed->scancode == sf::Keyboard::Scancode::Escape) {
                        window.close(); // ���� ���ӿ����� ���� ��ȯ ����
                        return;
                    }
                }
            }

            // --- 2. �ð��� ������Ʈ (�� ������) ---
            // ������ �ؽ�Ʈ ���� �� ũ�� ���� (���̶���Ʈ ȿ��)
         // for ������ ���۰� ���� (���� ����)
            for (size_t i = 0; i < m_optionTexts.size(); ++i) {
                if (i == m_selectedOptionIndex) {
                    m_optionTexts[i].setFillColor(m_highlightOptionColor); // ���õ� �ɼ��� ���̶���Ʈ ����
                    m_optionTexts[i].setCharacterSize(40); // ���õ� ���� �ణ ũ��

                    // m_optionImageSprites[i]�� ��ȿ�� sf::Sprite ��ü�̰� �ؽ�ó�� �Ҵ�Ǿ� �ִ��� Ȯ��
                    const sf::Texture& texture = m_optionImageSprites[i].getTexture();
                    if (texture.getSize().x > 0 && texture.getSize().y > 0) { // <-- ��ȿ�� �˻� ����
                        m_optionImageSprites[i].setColor(sf::Color::White); // ���õ� �̹����� ���
                        m_optionImageSprites[i].setScale({ 0.6f, 0.6f });     // �ణ ũ��
                    }
             }
                else {
                    m_optionTexts[i].setFillColor(m_defaultOptionColor); // ���õ��� ���� �ɼ��� �⺻ ����
                    m_optionTexts[i].setCharacterSize(36); // �⺻ ũ��

                    // m_optionImageSprites[i]�� ��ȿ�� sf::Sprite ��ü�̰� �ؽ�ó�� �Ҵ�Ǿ� �ִ��� Ȯ��
                    const sf::Texture& texture = m_optionImageSprites[i].getTexture();
                    if (texture.getSize().x > 0 && texture.getSize().y > 0) { // <-- ��ȿ�� �˻� ����
                        m_optionImageSprites[i].setColor(sf::Color(150, 150, 150)); // �ణ ��Ӱ�
                        m_optionImageSprites[i].setScale({ 0.5f, 0.5f });             // �⺻ ũ��
                    }
                    // --- ���� �� ---
                }
            }

            // --- 3. �׸��� ---
            window.clear(Color::Blue); // �� �����Ӹ��� ȭ���� ����� ���ο� ������ �׸��ϴ� (�Ķ�������)

            // ��� ��������Ʈ �׸��� (Optional üũ)
            if (backgroundSprite.has_value()) {
                window.draw(*backgroundSprite);
            }

            // Ÿ��Ʋ �ؽ�Ʈ �׸��� (Optional üũ)
            if (titleText.has_value()) {
                window.draw(*titleText);
            }

            // m_optionImageSprites�� std::vector<sf::Sprite> Ÿ���� ���
            for (const auto& optSprite : m_optionImageSprites) { // optSprite�� const sf::Sprite& Ÿ��
                // �ؽ�ó�� ��ȿ���� Ȯ���ϴ� �Լ��� �ʿ���
                const sf::Texture& texture = optSprite.getTexture(); // optSprite�� sf::Sprite ��
                if (texture.getSize().x > 0 && texture.getSize().y > 0) { // �ؽ�ó�� ��ȿ�� ��쿡�� �׸�
                    window.draw(optSprite); // * ���� �ٷ� optSprite �׸���
                }
            }

            // ������ �ؽ�Ʈ�� ���߿� �׸��� (�̹��� ���� ������)
            for (const auto& text : m_optionTexts) {
                window.draw(text);
            }

            window.display(); // �׸� ������ ȭ�鿡 ǥ��
        }
    }
}