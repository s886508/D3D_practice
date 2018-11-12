#pragma once

class D3DCamera {
public:
	D3DCamera();
	~D3DCamera() = default;

public:
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void GetViewMatrix(D3DXMATRIX& matrix);

private:
	void Render();

private:
	float m_position_x, m_position_y, m_position_z;
	float m_rotation_x, m_rotation_y, m_rotation_z;
	D3DXMATRIX m_view_matrix;

};
