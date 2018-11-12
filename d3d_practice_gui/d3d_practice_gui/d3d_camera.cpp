#include <D3DX10math.h>
#include "d3d_camera.h"

D3DCamera::D3DCamera() : 
m_position_x(0.f),
m_position_y(0.f),
m_position_z(0.f),
m_rotation_x(0.f),
m_rotation_y(0.f),
m_rotation_z(0.f)
{

}

void D3DCamera::SetPosition(float x, float y, float z) {
	m_position_x = x;
	m_position_y = y;
	m_position_z = z;
}

void D3DCamera::SetRotation(float x, float y, float z) {
	m_rotation_x = x;
	m_rotation_y = y;
	m_rotation_z = z;
}

D3DXVECTOR3 D3DCamera::GetPosition() {
	return D3DXVECTOR3(m_position_x, m_position_y, m_position_z);
}

D3DXVECTOR3 D3DCamera::GetRotation() {
	return D3DXVECTOR3(m_rotation_x, m_rotation_y, m_rotation_z);
}

void D3DCamera::Render() {
	D3DXVECTOR3 up, position, look_at;
	D3DXMATRIX rotation_matrix;
	float yaw, pitch, roll;

	up.x = 0.f;
	up.y = 1.f;
	up.z = 0.f;

	position.x = m_position_x;
	position.y = m_position_y;
	position.z = m_position_z;

	look_at.x = 0.f;
	look_at.y = 0.f;
	look_at.z = 1.f;

	pitch = m_rotation_x * 0.0174532925f;
	yaw = m_rotation_y * 0.0174532925f;
	roll = m_rotation_z * 0.0174532925f;

	D3DXMatrixRotationYawPitchRoll(&rotation_matrix, yaw, pitch, roll);

	D3DXVec3TransformCoord(&look_at, &look_at, &rotation_matrix);
	D3DXVec3TransformCoord(&up, &up, &rotation_matrix);

	look_at = position + look_at;

	D3DXMatrixLookAtLH(&m_view_matrix, &position, &look_at, &up);
}

void D3DCamera::GetViewMatrix(D3DXMATRIX& matrix) {
	Render();

	matrix = m_view_matrix;
}