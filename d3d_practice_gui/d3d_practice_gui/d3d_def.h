#pragma once

typedef struct _VERTEX {
	float x, y, z;
	D3DXCOLOR color;
} VERTEX;

typedef struct _MatrixBufferType {
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
} MatrixBufferType;