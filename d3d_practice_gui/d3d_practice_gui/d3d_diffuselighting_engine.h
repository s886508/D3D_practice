#pragma once
#include "ID3d_engine.h"

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11Buffer;
struct ID3D11InputLayout;
struct ID3D11Texture2D;
struct ID3D11DepthStencilState;
struct ID3D11DepthStencilView;
struct ID3D11RasterizerState;
struct ID3D11ShaderResourceView;
struct ID3D11SamplerState;

class DiffuseLightingEngine : public ID3DEngine {
public:
	DiffuseLightingEngine();
	virtual ~DiffuseLightingEngine();

public:
	void Init(HWND hwnd) override;
	bool RenderFrame(const D3DXMATRIX &view_matrix) override;

private:
	void InitD3D(HWND hwnd);
	void CleanD3D();
	void InitD3DPipeline();
	void InitD3DBuffer();
	void InitD3DTexture();
	
	void SetShaderParam(D3DXMATRIX view_matrix);
	void RenderTriangle();

private:
	// D3D
	IDXGISwapChain			*m_swapchain;
	ID3D11Device			*m_device;
	ID3D11DeviceContext		*m_device_context;
	ID3D11RenderTargetView	*m_render_target_view;

	ID3D11VertexShader		*m_vertex_shader;
	ID3D11PixelShader		*m_pixel_shader;

	ID3D11Buffer			*m_vertex_buffer;
	ID3D11Buffer			*m_matrix_buffer;
	ID3D11Buffer			*m_index_buffer;
	ID3D11Buffer			*m_light_buffer;
	ID3D11InputLayout		*m_input_layout;

	ID3D11Texture2D			*m_depth_stencil_buffer;
	ID3D11DepthStencilState	*m_depth_stencil_state;
	ID3D11DepthStencilView	*m_depth_stencil_view;
	ID3D11RasterizerState	*m_rasterizer_state;

	ID3D11ShaderResourceView *m_texture;
	ID3D11SamplerState		*m_sampler_state;

	D3DXMATRIX				m_projection_matrix;
	D3DXMATRIX				m_world_matrix;
	D3DXMATRIX				m_ortho_matrix;

	D3DXVECTOR4				m_diffuse_color;
	D3DXVECTOR3				m_light_direction;
};