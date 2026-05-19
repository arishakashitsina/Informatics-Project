#include "AssetManager.hpp"
#include <iostream>

void AssetManager::loadTextures() {
    // Временные текстуры, чтобы не было ошибок. Позже замените на загрузку из assets.
    sf::Texture dummy;
    dummy.create(32, 32);
    m_textures["bird"] = dummy;
    m_textures["pipe"] = dummy;
    m_textures["bird"].loadFromFile("assets/bird.png");
    m_textures["pipe"].loadFromFile("assets/pipe.png");
}

void AssetManager::loadSounds() {
    // Пока ничего не загружаем
}

sf::Texture& AssetManager::getTexture(const std::string& name) {
    return m_textures[name];
}

void AssetManager::playSound(const std::string& name) {
    // заглушка
}

sf::Font& AssetManager::getFont() {
    if (m_font.getInfo().family.empty()) {
        if (!m_font.loadFromFile("assets/font.ttf")) {
            std::cerr << "Failed to load font from assets/font.ttf\n";
            // fallback
            if (!m_font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf")) {
                std::cerr << "Failed to load fallback font\n";
            } else {
                std::cout << "Loaded fallback font\n";
            }
        } else {
            std::cout << "Loaded font from assets/font.ttf\n";
        }
    }
    return m_font;
}
