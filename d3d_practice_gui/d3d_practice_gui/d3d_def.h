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

typedef struct _VERTEX3 {
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;
	D3DXVECTOR3 normal;
} VERTEX3;

typedef struct _MatrixBufferType {
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
} MatrixBufferType;

typedef struct _LightBufferTYpe {
	D3DXVECTOR4 diffuseColor;
	D3DXVECTOR3 lightDirection;
	float padding; // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
} LightBufferType;