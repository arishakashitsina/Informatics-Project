#ifndef PIPEMANAGER_HPP
#define PIPEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

struct PipePair {
    sf::Sprite top;
    sf::Sprite bottom;
    bool passed;
};

class PipeManager {
public:
    void init(const sf::Texture& texture);
    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    bool checkCollision(const sf::FloatRect& birdBounds) const;
    int getScore() const;
    void reset();

private:
    std::vector<PipePair> m_pipes;
    float m_spawnTimer = 0.f;
    const float SPAWN_INTERVAL = 2.f;
    const float PIPE_SPEED = 200.f;
    const float GAP_HEIGHT = 200.f;
    float m_pipeWidth = 52.f;  // подберите под ширину pipe.png (можно вычислить из текстуры)
    int m_score = 0;
    sf::Texture m_texture;
};

#endif
