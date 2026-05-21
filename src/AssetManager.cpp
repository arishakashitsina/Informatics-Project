#include "AssetManager.hpp"
#include <iostream>
#include <stdexcept>

void AssetManager::loadTextures() {
    sf::Texture birdTexture;
    if (!birdTexture.loadFromFile("assets/bird.png")) {
        throw std::runtime_error("Failed to load texture: assets/bird.png");
    }
    m_textures["bird"] = birdTexture;

    sf::Texture pipeTexture;
    if (!pipeTexture.loadFromFile("assets/pipe.png")) {
        throw std::runtime_error("Failed to load texture: assets/pipe.png");
    }
    m_textures["pipe"] = pipeTexture;
}

void AssetManager::loadSounds() {
    const std::pair<std::string, std::string> soundFiles[] = {
        {"jump", "assets/jump.wav"},
        {"score", "assets/score.wav"},
        {"hit", "assets/hit.wav"}
    };

    for (const auto& soundFile : soundFiles) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(soundFile.second)) {
            std::cerr << "Warning: failed to load sound " << soundFile.second << '\n';
            continue;
        }

        m_soundBuffers[soundFile.first] = buffer;
        m_sounds[soundFile.first].setBuffer(m_soundBuffers[soundFile.first]);
    }
}

sf::Texture& AssetManager::getTexture(const std::string& name) {
    auto it = m_textures.find(name);
    if (it == m_textures.end()) {
        throw std::runtime_error("Texture not found: " + name);
    }
    return it->second;
}

void AssetManager::playSound(const std::string& name) {
    auto it = m_sounds.find(name);
    if (it == m_sounds.end()) {
        std::cerr << "Warning: sound not found: " << name << '\n';
        return;
    }
    it->second.play();
}

sf::Font& AssetManager::getFont() {
    if (m_font.getInfo().family.empty()) {
        if (!m_font.loadFromFile("assets/font.ttf")) {
            throw std::runtime_error("Failed to load font: assets/font.ttf");
        }
    }
    return m_font;
}
