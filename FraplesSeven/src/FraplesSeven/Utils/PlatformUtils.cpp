#include "FplPCH.h"
#include <commdlg.h>
#include "GLFW/glfw3.h"
#include "PlatformUtils.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW//glfw3native.h"
#include "FraplesSeven/Core/App.h"
namespace Fraples
{
	std::string FileDialogs::OpenFile(const char* filter)
	{
		OPENFILENAME openfile;
		CHAR szFile[MAX_PATH] = {0};
		ZeroMemory(&openfile, sizeof(OPENFILENAME));
		openfile.lStructSize = sizeof(OPENFILENAME);
		openfile.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::GetApp().GetWindow().GetNativeWindow());
		openfile.lpstrFile = szFile;
		openfile.nMaxFile = sizeof(szFile);
		openfile.lpstrFilter = filter;
		openfile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileName(&openfile) == TRUE)
		{
			return std::string((const char*)openfile.lpstrFile);
		}
		return std::string();
	}
	std::string FileDialogs::SaveFile(const char* filter)
	{
		OPENFILENAME openfile;
		CHAR szFile[MAX_PATH] = { 0 };
		ZeroMemory(&openfile, sizeof(OPENFILENAME));
		openfile.lStructSize = sizeof(OPENFILENAME);
		openfile.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::GetApp().GetWindow().GetNativeWindow());
		openfile.lpstrFile = szFile;
		openfile.nMaxFile = sizeof(szFile);
		openfile.lpstrFilter = filter;
		openfile.nMaxCustFilter = 3;
		openfile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileName(&openfile) == TRUE)
		{
			return std::string((const char*)openfile.lpstrFile);
		}
		return std::string();

	}
}