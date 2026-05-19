#ifndef BIRD_HPP
#define BIRD_HPP

#include <SFML/Graphics.hpp>

class Bird {
public:
    void init(const sf::Texture& texture);
    void update(float dt);
    void jump();
    sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow& window) const;
    void reset();

private:
    sf::Sprite m_sprite;
    float m_velocity = 0.f;
    const float GRAVITY = 1000.f;
    const float JUMP_FORCE = -300.f;
    sf::Vector2f m_startPosition = sf::Vector2f(100.f, 300.f);
};

#endif
