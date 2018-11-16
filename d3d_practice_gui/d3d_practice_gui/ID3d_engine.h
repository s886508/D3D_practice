#pragma once

struct D3DXMATRIX;

struct ID3DEngine {
	virtual ~ID3DEngine() = default;

	virtual void Init(HWND hwnd) = 0;
	virtual bool RenderFrame(const D3DXMATRIX &view_matrix) = 0;
};
