#include "Game.h"
#include <iostream>
#include "Log.h"
#include "Map.h"
#include "AI.h"

int count = 0;

void* operator new(size_t size)
{
    LOG.All("Allocated " + std::to_string(++count));
    return (malloc(size));
}

void operator delete(void* ptr)
{
    LOG.All("Free left : " + std::to_string(--count));
    free(ptr);
}

Game::Game()
{
    m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Prison Game"); 
    m_window->setFramerateLimit(60);
    m_window->setPosition({ m_window->getPosition().x, 0 });
    m_window->setView(m_view);
}

Game::Game(sf::Vector2u size, unsigned frameRate, const char* windowName)
{
    m_window = new sf::RenderWindow(sf::VideoMode(size.x, size.y), windowName);
    m_window->setFramerateLimit(frameRate);
    m_window->setPosition({ m_window->getPosition().x, 0 });
    m_view.setSize(size.x, size.y);
    m_view.setCenter(size.x / 2, size.y / 2);
    m_window->setView(m_view);
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
        if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            player.onClick(m_window);
            AI* ai = new AI(*map);
            ai->pos = std::make_pair(8, 0);
            ai->dest = std::make_pair(0, 0);
            for (int i = 0; i < 1000; i++) {
                ressourceManager.push_ai(ai);
            }
        }
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
    ressourceManager.processAI();
    player.move();
}

void Game::render()
{
    m_window->clear();
    for (int i = 0; i < m_animations.size(); i++)
        m_animations[i].draw(m_window);
    if (m_currentHUD != nullptr)
        m_currentHUD->draw(m_window, sf::Mouse::getPosition(*m_window));
    player.draw(m_window);
    m_window->display();
}

void Game::run(void)
{
    constexpr unsigned TPS = 60; //ticks per seconds
    const sf::Time timePerUpdate = sf::seconds(1.0f / float(TPS));
    unsigned ticks = 0;

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    auto lag = sf::Time::Zero;
    int x = 0;

    while (m_window->isOpen()) {

        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        while (lag >= timePerUpdate) {
            ticks++;
            lag -= timePerUpdate;
            fixedUpdate();
                /*for (int i = 0; i < ressourceManager.aiQueue.size(); i++) {
                    ressourceManager.aiQueue.front()->getPath();
                }*/
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
            LOG.Warn ("Hud with same name already loaded\n");
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
