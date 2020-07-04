#include "Game.h"
#include <iostream>

int count = 0;

void* operator new(size_t size)
{
    std::cout << "Allocated " << ++count << " blocks of memory\n";
    return (malloc(size));
}

void operator delete(void* ptr)
{
    std::cout << --count << " block to free\n";
    free(ptr);
}

Game::Game()
{
    m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Prison Game"); 
    m_window->setFramerateLimit(60);
    m_window->setPosition({ m_window->getPosition().x, 0 });
}

Game::~Game()
{
    delete (m_window);
}

void Game::handleEvent(void)
{
    sf::Event event;

    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window->close();
        if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            m_window->close();
        if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            m_currentHUD != nullptr)
            m_currentHUD->onClick(sf::Mouse::getPosition(*m_window));
    }
}

void Game::update(void)
{

}

void Game::fixedUpdate(void)
{
    for (int i = 0; i < m_animations.size(); i++)
        m_animations[i].update();
    if (m_currentHUD != nullptr)
        m_currentHUD->update();

}

void Game::render()
{
    m_window->clear();
    for (int i = 0; i < m_animations.size(); i++)
        m_animations[i].draw(m_window);
    if (m_currentHUD != nullptr)
        m_currentHUD->draw(m_window, sf::Mouse::getPosition(*m_window));
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

void Game::push_animation(Animation &animation)
{
    m_animations.push_back(animation);
}

void Game::push_hud(const std::string& name, HUD& hud)
{
    for (int i = 0; i < m_HUDS.size(); i++) {
        if (name.compare(*m_HUDS[i].first) == 0) {
            m_currentHUD = m_HUDS[i].second;
            std::cout << "Hud with same name already loaded\n";
            return;
        }
    }
    m_currentHUD = &hud;
    m_HUDS.push_back(std::make_pair(&name, &hud));
}

void Game::changeHUD(const std::string& name)
{
    for (int i = 0; i < m_HUDS.size(); i++) {
        if (name.compare(*m_HUDS[i].first) == 0) {
            m_currentHUD = m_HUDS[i].second;
            break;
        }
    }
}
