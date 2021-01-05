#include "mxpch.h"
#include "Renderer.h"

namespace Marx
{
	Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

	void Renderer::beginScene(const OrthographicCamera& camera)
	{
		s_sceneData->viewProjectionMatrix = camera.getViewProjectionTransposed();
	}

	void Renderer::endScene()
	{
	}

	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		static D3D11ConstantBuffer constBuffer(0, sizeof(DX::XMMATRIX), nullptr);

		shader->bind();
		vertexArray->bind();
		constBuffer.update(&s_sceneData->viewProjectionMatrix);
		constBuffer.bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}