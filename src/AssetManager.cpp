#include "AssetManager.hpp"
#include <iostream>

void AssetManager::loadTextures() {
    // Временные текстуры, чтобы не было ошибок. Позже замените на загрузку из assets.
    sf::Texture dummy;
    dummy.create(32, 32);
    m_textures["bird"] = dummy;
    m_textures["pipe"] = dummy;
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
    // Попробуем загрузить системный шрифт, если нет – вернём пустой
    if (!m_font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf")) {
        // Не страшно, отображение текста пока не критично
    }
    return m_font;
}
