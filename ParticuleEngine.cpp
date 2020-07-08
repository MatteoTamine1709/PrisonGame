#include "ParticuleEngine.h"
#include "Math.h"
#include <cmath>
#include <iostream>

ParticuleEngine::ParticuleEngine()
{
	m_ParticlePool.resize(1000);
}

void ParticuleEngine::OnUpdate(sf::Time &ts)
{
	for (auto& particle : m_ParticlePool) {
		if (!particle.Active)
			continue;
		if (particle.LifeRemaining <= 0.0f) {
			particle.Active = false;
			continue;
		}
		particle.LifeRemaining -= ts.asSeconds();
		particle.Position.x += particle.Velocity.x * ts.asSeconds();
		particle.Position.y += particle.Velocity.y * ts.asSeconds();
		particle.Rotation += (double)0.01f * ts.asSeconds();
	}
}

float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}

void ParticuleEngine::OnRender(sf::RenderWindow *&window)
{
	for (auto& particle : m_ParticlePool) {
		if (!particle.Active)
			continue;
		float life = particle.LifeRemaining / particle.LifeTime;
		sf::Color color;
		color.r = particle.ColorEnd.r + life * (particle.ColorBegin.r - particle.ColorEnd.r);
		color.g = particle.ColorEnd.g + life * (particle.ColorBegin.g - particle.ColorEnd.g);
		color.b = particle.ColorEnd.b + life * (particle.ColorBegin.b - particle.ColorEnd.b);
		color.a =  particle.ColorEnd.a + life * (particle.ColorBegin.a - particle.ColorEnd.a);
		float size = lerp(particle.SizeEnd, particle.SizeBegin, life);
		sf::RectangleShape rect({ size, size });
		rect.setPosition(particle.Position);
		rect.setRotation(particle.Rotation);
		rect.setFillColor(color);
		window->draw(rect);
	}
}

void ParticuleEngine::Emit(const ParticleProps& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = (double)std::rand() * 2.0f * M_PI;

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * ((float)(std::rand() % 100) / 100.0f - 0.5f);
	particle.Velocity.y += particleProps.VelocityVariation.y * ((float)(std::rand() % 100) / 100.0f - 0.5f);

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * ((float)(std::rand() % 100) / 100.0f - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}