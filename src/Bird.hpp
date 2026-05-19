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

private:
    sf::Sprite m_sprite;
    float m_velocity;
    const float GRAVITY = 1000.f;
    const float JUMP_FORCE = -300.f;
};

#endif
