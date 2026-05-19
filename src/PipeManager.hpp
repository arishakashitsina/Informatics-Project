#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct PipePair {
    sf::RectangleShape topShape;
    sf::RectangleShape bottomShape;
    bool passed = false;
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
    static constexpr float PIPE_SPEED = 200.f;
    static constexpr float SPAWN_INTERVAL = 2.f;
    static constexpr float GAP_HEIGHT = 200.f;
    
    std::vector<PipePair> m_pipes;
    float m_pipeWidth = 60;
    float m_spawnTimer = 0.f;
    int m_score = 0;
};
