#include "PipeManager.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

void PipeManager::init(const sf::Texture& texture) {
    // Игнорируем текстуру, создаём свои прямоугольники
    (void)texture;
    
    m_pipeWidth = 60;
    std::srand(std::time(nullptr));
    reset();
}

void PipeManager::update(float dt) {
    // Движение и удаление
    for (auto it = m_pipes.begin(); it != m_pipes.end(); ) {
        it->topShape.move(-PIPE_SPEED * dt, 0.f);
        it->bottomShape.move(-PIPE_SPEED * dt, 0.f);
        if (it->topShape.getPosition().x + m_pipeWidth < 0.f) {
            it = m_pipes.erase(it);
        } else {
            ++it;
        }
    }

    // Генерация новых труб
    m_spawnTimer += dt;
    if (m_spawnTimer >= SPAWN_INTERVAL) {
        m_spawnTimer = 0.f;
        PipePair pipe;

        // Случайная позиция прохода (от 100 до 400)
        float gapY = 150.f + rand() % 300;
        
        // Верхняя труба (от верха до прохода)
        pipe.topShape.setSize(sf::Vector2f(m_pipeWidth, gapY));
        pipe.topShape.setFillColor(sf::Color::Green);
        pipe.topShape.setPosition(800.f, 0.f);
        
        // Нижняя труба (от прохода до низа экрана)
        float bottomHeight = 600.f - (gapY + GAP_HEIGHT);
        pipe.bottomShape.setSize(sf::Vector2f(m_pipeWidth, bottomHeight));
        pipe.bottomShape.setFillColor(sf::Color::Green);
        pipe.bottomShape.setPosition(800.f, gapY + GAP_HEIGHT);
        
        pipe.passed = false;
        m_pipes.push_back(pipe);
    }

    // Подсчёт очков
    for (auto& pipe : m_pipes) {
        if (!pipe.passed && pipe.topShape.getPosition().x + m_pipeWidth < 100.f) {
            pipe.passed = true;
            m_score++;
        }
    }
}

void PipeManager::draw(sf::RenderWindow& window) const {
    for (const auto& pipe : m_pipes) {
        window.draw(pipe.topShape);
        window.draw(pipe.bottomShape);
    }
}

bool PipeManager::checkCollision(const sf::FloatRect& birdBounds) const {
    // Проверка границ экрана
    if (birdBounds.top < 0.f || birdBounds.top + birdBounds.height > 600.f)
        return true;

    // Проверка столкновения с трубами
    for (const auto& pipe : m_pipes) {
        if (birdBounds.intersects(pipe.topShape.getGlobalBounds()) ||
            birdBounds.intersects(pipe.bottomShape.getGlobalBounds())) {
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
