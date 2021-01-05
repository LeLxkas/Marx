#pragma once

namespace Marx
{
	class Shader
	{
	public:
		static Shader* create(const std::string& vertexSrc, const std::string& pixelSrc);
	public:
		virtual ~Shader() {};
	public:
		virtual void bind() const = 0;
	public:
		static std::string loadShaderSrcFromFile(const std::string& filename);
	};
}