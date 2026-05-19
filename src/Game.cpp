#include "Game.hpp"
#include <fstream>
#include <iostream>

Game::Game()
    : m_window(sf::VideoMode(800, 600), "Flappy Bird")
    , m_isRunning(true)
    , m_score(0)
    , m_highScore(0)
{
    m_assets.loadTextures();
    m_assets.loadSounds();
    m_bird.init(m_assets.getTexture("bird"));
    m_pipes.init(m_assets.getTexture("pipe"));

    // загрузка рекорда из файла (если есть)
    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> m_highScore;
    }
}

void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen() && m_isRunning) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
    // сохраняем рекорд
    std::ofstream file("highscore.txt");
    if (file.is_open()) {
        file << m_highScore;
    }
}

void Game::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            m_bird.jump();
            // позже добавим звук: m_assets.playSound("jump");
        }
    }
}

void Game::update(float dt) {
    m_bird.update(dt);
    m_pipes.update(dt);

    if (m_pipes.checkCollision(m_bird.getBounds())) {
        m_isRunning = false;
        // m_assets.playSound("hit");
    }

    int newScore = m_pipes.getScore();
    if (newScore > m_score) {
        m_score = newScore;
        // m_assets.playSound("score");
        if (m_score > m_highScore) m_highScore = m_score;
    }
}

void Game::render() {
    m_window.clear(sf::Color::Cyan);
    m_bird.draw(m_window);
    m_pipes.draw(m_window);
    // Здесь позже добавим отображение счёта
    m_window.display();
}
