#pragma once

#include "Marx/Platform/DX11/DX11Includes.h"

namespace Marx
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
	public:
		void setPosition(const DX::XMFLOAT3& position) { m_position = position; recalculateViewMatrix(); }
		void setRotation(float rotation) { m_rotation = rotation; recalculateViewMatrix(); }
	public:
		const DX::XMFLOAT3& getPosition() const { return m_position; }
		float getRotation() const { return m_rotation; }
		const DX::XMMATRIX& getViewMatrix() const { return m_viewMatrix; }
		const DX::XMMATRIX& getProjectionMatrix() const { return m_projectionMatrix; }
		const DX::XMMATRIX& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }
		const DX::XMMATRIX& getViewProjectionTransposed() const { return m_viewProjectionMatrixTransposed; }
	private:
		void recalculateViewMatrix();
	private:
		DX::XMMATRIX m_viewMatrix;
		DX::XMMATRIX m_projectionMatrix;
		DX::XMMATRIX m_viewProjectionMatrix;
		DX::XMMATRIX m_viewProjectionMatrixTransposed;
		DX::XMFLOAT3 m_position = { 0.0f, 0.0f, 0.0f };
		float m_rotation = 0.0f;
	};
}