#include "PipeManager.hpp"
#include <cstdlib>
#include <ctime>

void PipeManager::init(const sf::Texture& texture) {
    m_texture = texture;
    m_pipeWidth = texture.getSize().x;
    std::srand(std::time(nullptr));
    reset();
}

void PipeManager::update(float dt) {
    // Движение и удаление
    for (auto it = m_pipes.begin(); it != m_pipes.end(); ) {
        it->top.move(-PIPE_SPEED * dt, 0.f);
        it->bottom.move(-PIPE_SPEED * dt, 0.f);
        if (it->top.getPosition().x + m_pipeWidth < 0.f) {
            it = m_pipes.erase(it);
        } else {
            ++it;
        }
    }

    // Генерация
    m_spawnTimer += dt;
    if (m_spawnTimer >= SPAWN_INTERVAL) {
        m_spawnTimer = 0.f;
        PipePair pipe;

        float gapY = 150.f + rand() % 250;
        float topHeight = gapY;
        float bottomY = gapY + GAP_HEIGHT;
        float bottomHeight = 600.f - bottomY;

        // Верхняя труба (перевёрнутая)
        pipe.top.setTexture(m_texture);
        pipe.top.setTextureRect(sf::IntRect(0, 0, m_pipeWidth, topHeight));
        pipe.top.setOrigin(0, 0);
        pipe.top.setPosition(800.f, 0.f);
        pipe.top.setScale(1.f, -1.f);  // переворот по Y

        // Нижняя труба
        pipe.bottom.setTexture(m_texture);
        pipe.bottom.setTextureRect(sf::IntRect(0, bottomY, m_pipeWidth, bottomHeight));
        pipe.bottom.setOrigin(0, 0);
        pipe.bottom.setPosition(800.f, bottomY);
        pipe.bottom.setScale(1.f, 1.f);

        pipe.passed = false;
        m_pipes.push_back(pipe);
    }

    // Обновление счёта (пройденные трубы)
    // Этот код может быть вынесен в отдельный метод, но для простоты добавим здесь
    for (auto& pipe : m_pipes) {
        if (!pipe.passed && pipe.top.getPosition().x + m_pipeWidth < 100.f) { // птица на x=100
            pipe.passed = true;
            m_score++;
        }
    }
}

void PipeManager::draw(sf::RenderWindow& window) const {
    for (const auto& pipe : m_pipes) {
        window.draw(pipe.top);
        window.draw(pipe.bottom);
    }
}

bool PipeManager::checkCollision(const sf::FloatRect& birdBounds) const {
    if (birdBounds.top < 0.f || birdBounds.top + birdBounds.height > 600.f)
        return true;

    for (const auto& pipe : m_pipes) {
        if (birdBounds.intersects(pipe.top.getGlobalBounds()) ||
            birdBounds.intersects(pipe.bottom.getGlobalBounds())) {
            return true;
        }
    }
    return false;
}

int PipeManager::getScore() const {
    return m_score;
}

void PipeManager::reset() {
    m_pipes.clear();
    m_spawnTimer = 0.f;
    m_score = 0;
}
