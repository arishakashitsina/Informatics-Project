#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class AssetManager {
public:
    void loadTextures();
    void loadSounds();
    sf::Texture& getTexture(const std::string& name);
    void playSound(const std::string& name);
    sf::Font& getFont();

private:
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
    std::unordered_map<std::string, sf::Sound> m_sounds;
    sf::Font m_font;
};

#endif
