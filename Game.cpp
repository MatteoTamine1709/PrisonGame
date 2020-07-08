#include "Game.h"
#include <iostream>
#include "Log.h"
#include "Map.h"
#include "AI.h"
#include "FPSCounter.h"

int count = 0;
int lastCount = 0;

void* operator new(size_t size)
{
    std::string s = std::to_string(size);
    if (count - lastCount > 100 || count < 20) {
        LOG.All("Allocated " +  std::to_string(++count));
        lastCount = count;
    } else
        ++count;
    return (malloc(size));
}

void operator delete(void* ptr)
{
    free(ptr);
    if (lastCount - count > 100 || count < 20) {
        LOG.All("Free left : " + std::to_string(--count));
        lastCount = count;
    } else
        --count;
    if (count == 0)
        LOG.Info("All free : " + std::to_string(count));
}

Game::Game()
{
    m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Prison Game"); 
    m_window->setFramerateLimit(60);
    m_window->setPosition({ 1000, 0 });
    m_window->setView(m_view);
    player.setMap(m_map);
}

Game::Game(sf::Vector2u size, unsigned frameRate, const char* windowName)
{
    m_window = new sf::RenderWindow(sf::VideoMode(size.x, size.y), windowName);
    m_window->setFramerateLimit(frameRate);
    m_window->setPosition({ 1000, 0 });
    m_view.setSize((float)size.x, (float)size.y);
    m_view.setCenter(size.x / 2.0f, size.y / 2.0f);
    m_window->setView(m_view);
    player.setMap(m_map);
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
            player.getPath();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            ParticleProps p;
            p.ColorBegin = { 254, 212, 123, 255 };
            p.ColorEnd = { 254, 109, 41, 255 };
            p.SizeBegin = 10.0f, p.SizeVariation = 0.3f, p.SizeEnd = 0.0f;
            p.LifeTime = 1.0f;
            p.Velocity = { 0.0f, 0.0f };
            p.VelocityVariation = { 100.0f, 80.0f };
            p.Position = { (float)sf::Mouse::getPosition(*m_window).x, (float)sf::Mouse::getPosition(*m_window).y };
            for (int i = 0; i < 5; i++)
                ressourceManager.particuleEngine.Emit(p);
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
    if (Math::dist(player.Pos.x, player.Pos.y, player.Dest.x, player.Dest.y) > 10) {
        ParticleProps p;
        p.ColorBegin = { 254, 212, 123, 255 };
        p.ColorEnd = { 254, 109, 41, 255 };
        p.SizeBegin = 10.0f, p.SizeVariation = 0.3f, p.SizeEnd = 0.0f;
        p.LifeTime = 1.0f;
        p.Velocity = { 0.0f, 0.0f };
        p.VelocityVariation = { 100.0f, 80.0f };
        p.Position = { (float)player.Pos.x, (float)player.Pos.y };
        for (int i = 0; i < 5; i++)
            ressourceManager.particuleEngine.Emit(p);
    }
}

void Game::render()
{
    m_window->clear();
    for (int i = 0; i < m_animations.size(); i++)
        m_animations[i].draw(m_window);
    if (m_currentHUD != nullptr)
        m_currentHUD->draw(m_window, sf::Mouse::getPosition(*m_window));
    ressourceManager.particuleEngine.OnRender(m_window);
    player.draw(m_window);
    ressourceManager.getFPS(m_window);
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
            ressourceManager.particuleEngine.OnUpdate(lag);
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

void Game::setMap(Map* map)
{
    m_map = map;
    player.setMap(map);
}
