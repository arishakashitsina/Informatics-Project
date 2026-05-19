#include "Bird.hpp"
#include <cmath>

void Bird::init(const sf::Texture& texture) {
    m_sprite.setTexture(texture);
    // Устанавливаем "центр" спрайта для вращения (по центру)
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    reset(); // устанавливаем начальную позицию и скорость
}

void Bird::update(float dt) {
    // гравитация
    m_velocity += GRAVITY * dt;
    // перемещение
    m_sprite.move(0.f, m_velocity * dt);
    // поворот спрайта в зависимости от скорости (от -45 до +45 градусов)
    float rotation = m_velocity * 0.1f;
    if (rotation > 45.f) rotation = 45.f;
    if (rotation < -45.f) rotation = -45.f;
    m_sprite.setRotation(rotation);
}

void Bird::jump() {
    m_velocity = JUMP_FORCE;
    // небольшой наклон вверх при прыжке
    m_sprite.setRotation(-30.f);
}

sf::FloatRect Bird::getBounds() const {
    return m_sprite.getGlobalBounds();
}

void Bird::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

void Bird::reset() {
    m_sprite.setPosition(m_startPosition);
    m_velocity = 0.f;
    m_sprite.setRotation(0.f);
}
