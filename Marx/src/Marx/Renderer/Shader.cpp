#include "mxpch.h"
#include "Shader.h"

namespace Marx
{
	std::string Shader::loadShaderSrcFromFile(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			MX_CORE_ERROR("Cannot open file '{0}'", filename);
			return std::string();
		}
		uint32_t fsize = (uint32_t)file.tellg();
		std::vector<char> buff(fsize);
		file.seekg(0);
		file.read(buff.data(), fsize);
		file.close();
		return std::string(buff.data(), fsize);
	}
}