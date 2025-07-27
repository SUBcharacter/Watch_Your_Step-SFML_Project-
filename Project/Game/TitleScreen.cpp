#include "TitleScreen.h" 

#include <iostream>      
#include <string>        
#include <vector>
#include <algorithm> 


TitleScreen::TitleScreen(const string& backgroundTexturePath)
{
    //  1. 배경 텍스처 로드  
    if (!backgroundTexture.loadFromFile(backgroundTexturePath))
    {
        cerr << "에러: 배경 텍스처(" << backgroundTexturePath << ")를 로드할 수 없습니다." << endl;
    }
    else 
    {
        backgroundSprite.emplace(backgroundTexture); 
    }

    //  2. 폰트 로드 
    if (!font.openFromFile("Assets/KoPubWorld Batang Bold.ttf"))
    {
        cerr << "에러: 폰트 (Assets/KoPubWorld Batang Bold.ttf)를 로드할 수 없습니다." << endl;
    }
    else 
    {
        //  3. 타이틀 텍스트 설정
        titleText.emplace(font); 
        titleText->setString("Welcome to the TitleScreen Screen!");
        titleText->setCharacterSize(48);
        titleText->setFillColor(Color::White);

        //   4. 선택지 문자열 및 이미지 경로 설정  
        m_optionStrings = { "게임 시작", "옵션", "나가기" };
        m_optionImagePath = {
            "Assets/TextBTN_Big.png",
            "Assets/TextBTN_Big.png",
            "Assets/TextBTN_Big.png"
        };
        m_selectedOptionIndex = 0; // 초기 선택은 첫 번째 옵션

        //   5. 각 선택지 텍스트 객체 생성 및 기본 설정  
        m_optionTexts.clear(); 
        for (size_t i = 0; i < m_optionStrings.size(); ++i) {
            sf::Text optionText(font); 
            optionText.setString(m_optionStrings[i]);
            optionText.setCharacterSize(36);      
            optionText.setFillColor(m_defaultOptionColor); 
            m_optionTexts.push_back(optionText); 
        }

        //   6. 각 선택지 이미지 텍스처 생성  
        m_optionImageTextures.clear(); 
        m_optionImageSprites.clear();  

        for (const auto& path : m_optionImagePath) {
            sf::Texture texture;
            if (!texture.loadFromFile(path)) {
                cerr << "에러: 옵션 이미지(" << path << ")를 로드할 수 없습니다." << endl;
                m_optionImageTextures.emplace_back();
                m_optionImageSprites.emplace_back(); 
            }
            else {
                m_optionImageTextures.push_back(std::move(texture));
                m_optionImageSprites.emplace_back(m_optionImageTextures.back());
            }
        }
    } 
}

void TitleScreen::run(sf::RenderWindow& window) 
{
   
    sf::Vector2u windowSize = window.getSize(); 
    float centerX = static_cast<float>(windowSize.x / 2.0f);
    float centerY = static_cast<float>(windowSize.y / 2.0f);

    // 1. 배경 스프라이트 크기 및 위치 조정
    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0) {
        float scaleX = static_cast<float>(windowSize.x) / backgroundTexture.getSize().x;
        float scaleY = static_cast<float>(windowSize.y) / backgroundTexture.getSize().y;
        if (backgroundSprite.has_value()) { 
            backgroundSprite->setScale({ scaleX, scaleY }); 
            backgroundSprite->setPosition({ 0.f, 0.f }); 
        }
    }

    // 2. 타이틀 텍스트 위치 및 원점 설정
    if (titleText.has_value()) { 
        sf::FloatRect textRect = titleText->getLocalBounds();
        titleText->setOrigin({ (textRect.position.x + textRect.size.x / 2.0f),
                               (textRect.position.y + textRect.size.y / 2.0f) });
        titleText->setPosition({ centerX, centerY - 150.f }); 

    float optionStartY = centerY + 50.f;
    for (size_t i = 0; i < m_optionTexts.size(); ++i) {
        sf::FloatRect optionRect = m_optionTexts[i].getLocalBounds();
        m_optionTexts[i].setOrigin({ (optionRect.position.x + optionRect.size.x / 2.0f),
                                     (optionRect.position.y + optionRect.size.y / 2.0f) });
        m_optionTexts[i].setPosition({ centerX, optionStartY + i * 50.f });
    }

   
    for (size_t i = 0; i < m_optionImageSprites.size(); ++i)
    {
        const sf::Texture& texture = m_optionImageSprites[i].getTexture();
        if (texture.getSize().x > 0 && texture.getSize().y > 0) {
            std::cout << "Sprite " << i << " has a valid texture. Processing..." << std::endl;
            { 
                sf::FloatRect imageRect = m_optionImageSprites[i].getLocalBounds();
                m_optionImageSprites[i].setOrigin({ (imageRect.position.x + imageRect.size.x / 2.0f),
                                                     (imageRect.position.y + imageRect.size.y / 2.0f) });
               m_optionImageSprites[i].setPosition({ centerX - 150.f, optionStartY + i * 50.f });
                m_optionImageSprites[i].setScale({ 0.5f, 0.5f }); 
            }
        }

        // 메인 게임 루프  
        while (window.isOpen()) {
            while (const optional<sf::Event> eventOpt = window.pollEvent())
            {
                const sf::Event& event = *eventOpt; 

               
                if (event.is<sf::Event::Closed>()) {
                    window.close();
                    return; 
                }
                else if (const auto* keypressed = event.getIf<sf::Event::KeyPressed>()) {
     
                    if (m_keyPressClock.getElapsedTime() < m_keyPressDelay) {
                        continue;
                    }
                    m_keyPressClock.restart(); 

                  
                    if (keypressed->scancode == sf::Keyboard::Scancode::Up) {
                        m_selectedOptionIndex = (m_selectedOptionIndex - 1 + m_optionTexts.size()) % m_optionTexts.size();
                    }
                    else if (keypressed->scancode == sf::Keyboard::Scancode::Down) {
                        m_selectedOptionIndex = (m_selectedOptionIndex + 1) % m_optionTexts.size();
                    }
       
                    else if (keypressed->scancode == sf::Keyboard::Scancode::Enter ||
                        keypressed->scancode == sf::Keyboard::Scancode::Escape) {
                        window.close();
                        return;
                    }
                }
            }

            for (size_t i = 0; i < m_optionTexts.size(); ++i) {
                if (i == m_selectedOptionIndex) {
                    m_optionTexts[i].setFillColor(m_highlightOptionColor); 
                    m_optionTexts[i].setCharacterSize(40); 

                  
                    const sf::Texture& texture = m_optionImageSprites[i].getTexture();
                    if (texture.getSize().x > 0 && texture.getSize().y > 0) {
                        m_optionImageSprites[i].setColor(sf::Color::White);
                        m_optionImageSprites[i].setScale({ 0.6f, 0.6f });   
                    }
             }
                else {
                    m_optionTexts[i].setFillColor(m_defaultOptionColor);
                    m_optionTexts[i].setCharacterSize(36); 

                    const sf::Texture& texture = m_optionImageSprites[i].getTexture();
                    if (texture.getSize().x > 0 && texture.getSize().y > 0) { 
                        m_optionImageSprites[i].setColor(sf::Color(150, 150, 150));
                        m_optionImageSprites[i].setScale({ 0.5f, 0.5f });            
                    }
                   
                }
            }

            window.clear(Color::Blue);

          
            if (backgroundSprite.has_value()) {
                window.draw(*backgroundSprite);
            }

            if (titleText.has_value()) {
                window.draw(*titleText);
            }

            for (const auto& optSprite : m_optionImageSprites) { 
                const sf::Texture& texture = optSprite.getTexture(); 
                if (texture.getSize().x > 0 && texture.getSize().y > 0) { 
                    window.draw(optSprite); 
                }
            }

            
            for (const auto& text : m_optionTexts) {
                window.draw(text);
            }

            window.display(); 
        }
    }
}