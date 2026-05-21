#include "Game.hpp"
#include <cmath>
#include <fstream>
#include <iostream>

namespace {
void drawCloud(sf::RenderWindow& window, const sf::Vector2f& center, float scale, const sf::Color& color) {
    sf::CircleShape puffA(24.f * scale);
    puffA.setFillColor(color);
    puffA.setPosition(center.x - 30.f * scale, center.y);

    sf::CircleShape puffB(30.f * scale);
    puffB.setFillColor(color);
    puffB.setPosition(center.x, center.y - 12.f * scale);

    sf::CircleShape puffC(22.f * scale);
    puffC.setFillColor(color);
    puffC.setPosition(center.x + 30.f * scale, center.y + 4.f * scale);

    window.draw(puffA);
    window.draw(puffB);
    window.draw(puffC);
}
} // namespace

Game::Game()
    : m_window(sf::VideoMode(800, 600), "Flappy Bird")
    , m_isRunning(true)
    , m_score(0)
    , m_highScore(0)
{
    m_assets.loadTextures();
    m_scoreText.setFont(m_assets.getFont());
    m_scoreText.setCharacterSize(40);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(20, 20);

    m_highScoreText.setFont(m_assets.getFont());
    m_highScoreText.setCharacterSize(30);
    m_highScoreText.setFillColor(sf::Color::White);
    m_highScoreText.setPosition(20, 70);
    m_assets.loadSounds();
    m_bird.init(m_assets.getTexture("bird"));
    m_pipes.init(m_assets.getTexture("pipe"));
    m_cloudAnchorsSlow = {
        {120.f, 90.f},
        {420.f, 130.f},
        {690.f, 80.f}
    };
    m_cloudAnchorsFast = {
        {240.f, 200.f},
        {560.f, 240.f},
        {760.f, 180.f}
    };

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
            m_assets.playSound("jump");
        }
    }
}

void Game::update(float dt) {
    m_backgroundTime += dt;
    m_cloudOffsetSlow += 20.f * dt;
    m_cloudOffsetFast += 35.f * dt;
    if (m_cloudOffsetSlow > 800.f) m_cloudOffsetSlow -= 800.f;
    if (m_cloudOffsetFast > 800.f) m_cloudOffsetFast -= 800.f;

    m_bird.update(dt);
    m_pipes.update(dt);

    if (m_pipes.checkCollision(m_bird.getBounds())) {
        m_isRunning = false;
        m_assets.playSound("hit");
    }

    int newScore = m_pipes.getScore();
    if (newScore > m_score) {
        m_score = newScore;
        m_assets.playSound("score");
        if (m_score > m_highScore) m_highScore = m_score;
    }
}

void Game::render() {
    m_window.clear();
    drawBackground();
    m_bird.draw(m_window);
    m_pipes.draw(m_window);
    
    m_scoreText.setString("Score: " + std::to_string(m_score));
    m_highScoreText.setString("Best: " + std::to_string(m_highScore));
    
    m_window.draw(m_scoreText);
    m_window.draw(m_highScoreText);
    
    m_window.display();
}

void Game::drawBackground() {
    sf::VertexArray sunset(sf::Quads, 4);
    sunset[0].position = sf::Vector2f(0.f, 0.f);
    sunset[1].position = sf::Vector2f(800.f, 0.f);
    sunset[2].position = sf::Vector2f(800.f, 600.f);
    sunset[3].position = sf::Vector2f(0.f, 600.f);
    sunset[0].color = sf::Color(255, 170, 200);
    sunset[1].color = sf::Color(255, 165, 195);
    sunset[2].color = sf::Color(255, 125, 165);
    sunset[3].color = sf::Color(255, 135, 175);
    m_window.draw(sunset);

    sf::CircleShape sun(65.f);
    sun.setFillColor(sf::Color(255, 212, 128, 220));
    sun.setPosition(545.f, 65.f + std::sin(m_backgroundTime * 0.25f) * 6.f);
    m_window.draw(sun);

    const sf::Color cloudSlow(255, 236, 244, 200);
    const sf::Color cloudFast(255, 228, 238, 215);
    for (const sf::Vector2f& anchor : m_cloudAnchorsSlow) {
        float x = anchor.x - m_cloudOffsetSlow;
        if (x < -140.f) x += 940.f;
        drawCloud(m_window, {x, anchor.y}, 1.0f, cloudSlow);
    }
    for (const sf::Vector2f& anchor : m_cloudAnchorsFast) {
        float x = anchor.x - m_cloudOffsetFast;
        if (x < -140.f) x += 940.f;
        drawCloud(m_window, {x, anchor.y}, 0.85f, cloudFast);
    }
}
