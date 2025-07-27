#pragma once

#include <string>    
#include <vector>    
#include <optional>  

#include "IntegrationLibrary.h"


class TitleScreen {
public:
      TitleScreen(const std::string& backgroundTexturePath);

    
    void run(sf::RenderWindow& window);

private:
    sf::Texture backgroundTexture;               
    std::optional<sf::Sprite> backgroundSprite;  

    sf::Font font;                               
    std::optional<sf::Text> titleText;           

    std::vector<std::string> m_optionStrings;    
    std::vector<sf::Text> m_optionTexts;         
    int m_selectedOptionIndex;                   

    std::vector<std::string> m_optionImagePath;     
    std::vector<sf::Texture> m_optionImageTextures; 
    std::vector<sf::Sprite> m_optionImageSprites;   

    const sf::Color m_defaultOptionColor = sf::Color::White;
    const sf::Color m_highlightOptionColor = sf::Color::Yellow; 
    sf::Clock m_keyPressClock;
    sf::Time m_keyPressDelay = sf::milliseconds(200); 
};