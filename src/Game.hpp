#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Bird.hpp"
#include "PipeManager.hpp"
#include "AssetManager.hpp"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

    sf::RenderWindow m_window;
    sf::Text m_scoreText;
    sf::Text m_highScoreText;
    Bird m_bird;
    PipeManager m_pipes;
    AssetManager m_assets;
    bool m_isRunning;
    int m_score;
    int m_highScore;
    void reset();
};

#endif
