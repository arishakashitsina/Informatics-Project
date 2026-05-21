#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Bird.hpp"
#include "PipeManager.hpp"
#include "AssetManager.hpp"
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();
    void drawBackground();

    sf::RenderWindow m_window;
    sf::Text m_scoreText;
    sf::Text m_highScoreText;
    Bird m_bird;
    PipeManager m_pipes;
    AssetManager m_assets;
    bool m_isRunning;
    int m_score;
    int m_highScore;
    float m_backgroundTime = 0.f;
    float m_cloudOffsetSlow = 0.f;
    float m_cloudOffsetFast = 0.f;
    std::vector<sf::Vector2f> m_cloudAnchorsSlow;
    std::vector<sf::Vector2f> m_cloudAnchorsFast;
    void reset();
};

#endif
