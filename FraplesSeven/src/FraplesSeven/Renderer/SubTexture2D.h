#pragma once
#include <glm/glm.hpp>

#include "Texture.h"

namespace Fraples
{
	class SubTexture2D
	{
	public:
		SubTexture2D(std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
		const std::shared_ptr<Texture2D>GetTexture()const { return _mTexture; }
		const glm::vec2* GetTexCoords() const { return _mTextureCoords; }

		static std::shared_ptr<SubTexture2D> CreateFromCoords(std::shared_ptr<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize , const glm::vec2& spriteRatio = { 1, 1 });
	private:
		std::shared_ptr<Texture2D> _mTexture;
		glm::vec2 _mTextureCoords[4];
	};
}
