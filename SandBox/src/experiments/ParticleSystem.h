#pragma once
#include "Fraples.h"


namespace Fraples
{
	namespace Experiment
	{
		struct ParticleProps
		{
			glm::vec2 Position;
			glm::vec2 Velocity, VelocityVariation;
			glm::vec4 ColorBegin, ColorEnd;
			float SizeBegin, SizeEnd, SizeVariation;
			float LifeTime = 1.0f;
		};

		class ParticleSystem
		{
		public:
			ParticleSystem(uint32_t maxParticles = 100000);
			~ParticleSystem() = default;
			void OnUpdate(TimeSteps ts);
			void OnRender(OrthographicCamera& ortho);
			void Emit(const ParticleProps& particleProps);
		public:
			struct Particle
			{
				glm::vec2 Position;
				glm::vec2 Veolocity;
				glm::vec4 ColorBegin, ColorEnd;
				float Rotation = 0.0f;
				float SizeBegin, SizeEnd;
				float LifeTime = 1.0f;
				float LifeRemaining = 0.0f;

				bool Active = false;
			};

			std::vector<Particle> _mParticlePool;
			uint32_t _mPoolIndex = 0;
		};
	}

}
