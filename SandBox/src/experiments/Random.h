#pragma once
#include <random>

namespace Fraples
{
	class Random
	{
	public:
		static void Init()
		{
			_sRandomEngine.seed(std::random_device()());
		}
		static float Float()
		{
			return (float)_sDist(_sRandomEngine) / (float)std::numeric_limits<uint32_t>::max();
		}
	private:
		inline static std::mt19937 _sRandomEngine;
		inline static std::uniform_int_distribution<std::mt19937::result_type>_sDist;

	};
}