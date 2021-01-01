#pragma once

namespace Marx
{
	class Shader
	{
	public:
		virtual ~Shader() {};
	public:
		virtual void bind() const = 0;
	public:
		static std::string loadShaderSrcFromFile(const std::string& filename);
	};
}