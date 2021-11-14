#include "FplPCH.h"
#include "SubTexture2D.h"

namespace Fraples
{



	Fraples::SubTexture2D::SubTexture2D(std::shared_ptr<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		:_mTexture(texture)
	{
		_mTextureCoords[0] = { min.x, min.y };
		_mTextureCoords[1] = { max.x, min.y };
		_mTextureCoords[2] = { max.x, max.y };
		_mTextureCoords[3] = { min.x, max.y };
	}


	std::shared_ptr<SubTexture2D> Fraples::SubTexture2D::CreateFromCoords(std::shared_ptr<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize, const glm::vec2& spriteRatio )
	{
		glm::vec2 min = { (coords.x * spriteSize.x) / texture->GetWidth(), (coords.y * spriteSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + spriteRatio.x) * spriteSize.x) / texture->GetWidth(), ((coords.y + spriteRatio.y) * spriteSize.y) / texture->GetHeight() };
		return std::make_shared<SubTexture2D>(texture, min, max);
	}

}