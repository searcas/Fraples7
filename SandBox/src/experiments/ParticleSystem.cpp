#include "ParticleSystem.h"
#include "Random.h"

#include <glm/gtx/compatibility.hpp>

Fraples::Experiment::ParticleSystem::ParticleSystem(uint32_t maxParticles) : _mPoolIndex(maxParticles - 1)
{
	_mParticlePool.resize(maxParticles);
}

void Fraples::Experiment::ParticleSystem::OnUpdate(TimeSteps ts)
{
	for (auto& particle : _mParticlePool)
	{
		if (!particle.Active)
		{
			continue;
		}
		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}
		particle.LifeRemaining -= ts;
		particle.Position += particle.Veolocity * (float)ts;
		particle.Rotation += 0.01f * ts;
	}
}

void Fraples::Experiment::ParticleSystem::OnRender(OrthographicCamera& ortho)
{
	Fraples::Renderer2D::BeginScene(ortho);
	for (auto& particle : _mParticlePool)
	{
		if (!particle.Active)
			continue;

		float life = particle.LifeRemaining / particle.LifeTime;
		glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
		//glm::vec4 color = { 1.0f, 1.0f, Random::Float(),1.0f };
		float size = glm::lerp(particle.SizeEnd, particle.SizeBegin, life);

		glm::vec3 position = { particle.Position.x,particle.Position.y, 0.2f};
		//TODO:
		//make random color for fun
		Fraples::Renderer2D::RenderRotatedQuad(particle.Position, {size, size}, (particle.Rotation), color);
	}
	Fraples::Renderer2D::EndScene();
}

void Fraples::Experiment::ParticleSystem::Emit(const ParticleProps& particleProps)
{
	Particle& particle = _mParticlePool[_mPoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

	//velocity
	particle.Veolocity = particleProps.Velocity;
	particle.Veolocity.x += particleProps.VelocityVariation.x * (Random::Float() - 0.5f);
	particle.Veolocity.y += particleProps.VelocityVariation.y * (Random::Float() - 0.5f);

	//color 
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;
	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	_mPoolIndex = --_mPoolIndex % _mParticlePool.size();
}
