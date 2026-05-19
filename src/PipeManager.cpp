#include "PipeManager.hpp"

void PipeManager::init(const sf::Texture& texture) {
    // заглушка
}

void PipeManager::update(float dt) {
    // заглушка
}

void PipeManager::draw(sf::RenderWindow& window) const {
    // заглушка
}

bool PipeManager::checkCollision(const sf::FloatRect& birdBounds) const {
    return false; // пока нет коллизий
}

int PipeManager::getScore() const {
    return 0; // пока ноль
}
void PipeManager::reset() {
    // Пока оставляем пустым. Позже участник, отвечающий за трубы, добавит очистку вектора и сброс счёта.
}
