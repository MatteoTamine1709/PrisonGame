#include "Game.h"
#include <iostream>

Game::Game()
{
    m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Prison Game"); 
    m_window->setFramerateLimit(60);
    m_window->setPosition({ m_window->getPosition().x, 0 });
}

Game::~Game()
{

}

void Game::handleEvent(void)
{
    sf::Event event;

    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window->close();
        if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            m_window->close();
    }
}

void Game::update(void)
{

}

void Game::fixedUpdate(void)
{
    for (int i = 0; i < m_animations.size(); i++)
        m_animations[i].update();

}

void Game::render()
{
    m_window->clear();
    for (int i = 0; i < m_animations.size(); i++)
        m_animations[i].draw(m_window);
    m_window->display();
}

void Game::run(void)
{
    constexpr unsigned TPS = 30; //ticks per seconds
    const sf::Time timePerUpdate = sf::seconds(1.0f / float(TPS));
    unsigned ticks = 0;

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    auto lag = sf::Time::Zero;

    while (m_window->isOpen()) {

        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        while (lag >= timePerUpdate) {
            ticks++;
            lag -= timePerUpdate;
            fixedUpdate();
        }
        handleEvent();
        update();
        render();
    }
}

void Game::push_animation(Animation& animation)
{
    m_animations.push_back(animation);
}
