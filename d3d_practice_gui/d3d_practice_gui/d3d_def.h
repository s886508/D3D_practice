#pragma once
#include <d3dx10math.h>

#define WIDTH 360
#define HEIGHT 360

typedef struct _VERTEX {
	float x, y, z;
	D3DXCOLOR color;
} VERTEX;

typedef struct _MatrixBufferType {
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
} MatrixBufferType;