#include "FplPCH.h"
#include "RenderCommands.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Fraples
{
	RendererAPI* RenderCommands::_sRendererAPI = new OpenGLRendererAPI();
}


