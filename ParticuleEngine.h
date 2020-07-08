#pragma once
#include <SFML/Graphics.hpp>
struct ParticleProps {
	sf::Vector2f Position;
	sf::Vector2f Velocity, VelocityVariation;
	sf::Color ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;
};

class ParticuleEngine
{
public:
	ParticuleEngine();

	void OnUpdate(sf::Time &ts);
	void OnRender(sf::RenderWindow*&window);

	void Emit(const ParticleProps& particleProps);
private:
	struct Particle {
		sf::Vector2f Position;
		sf::Vector2f Velocity;
		sf::Color ColorBegin, ColorEnd;
		double Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 999;
};

