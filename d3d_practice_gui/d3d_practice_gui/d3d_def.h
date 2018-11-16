#pragma once
#include <d3dx10math.h>

#define WIDTH 360
#define HEIGHT 360

typedef struct _VERTEX {
	float x, y, z;
	D3DXCOLOR color;
} VERTEX;

typedef struct _VERTEX2 {
	float x, y, z;
	D3DXVECTOR2 texture;
} VERTEX2;

typedef struct _MatrixBufferType {
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
} MatrixBufferType;