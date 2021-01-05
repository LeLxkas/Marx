#include "mxpch.h"
#include "Camera.h"

namespace Marx
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_projectionMatrix(DX::XMMatrixOrthographicOffCenterLH(left, right, bottom, top, -1.0f, 1.0f))
	{}

	void OrthographicCamera::recalculateViewMatrix()
	{
		DX::XMMATRIX transform = DX::XMMatrixTranslation(m_position.x, m_position.y, m_position.z) *
			DX::XMMatrixRotationZ(DX::XMConvertToRadians(m_rotation));

		m_viewMatrix = DX::XMMatrixInverse(NULL, transform);
		m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;
		m_viewProjectionMatrixTransposed = DX::XMMatrixTranspose(m_viewProjectionMatrix);
	}
}