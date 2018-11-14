#pragma once

struct D3DXVECTOR3;
struct D3DXMATRIX;

class D3DCamera {
public:
	D3DCamera();
	~D3DCamera() = default;

public:
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetPositionZ(float z);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);

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
