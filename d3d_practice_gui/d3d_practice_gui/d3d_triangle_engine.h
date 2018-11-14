#pragma once

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

class TriangleEngine {
public:
	TriangleEngine();
	virtual ~TriangleEngine();

public:
	void Init(HWND hwnd);

	bool RenderFrame(const D3DXMATRIX &view_matrix);

private:
	void InitD3D(HWND hwnd);
	void CleanD3D();
	void InitD3DPipeline();
	void InitD3DBuffer();
	
	void SetShaderParam(const D3DXMATRIX &view_matrix);
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
	ID3D11InputLayout		*m_input_layout;

	ID3D11Texture2D			*m_depth_stencil_buffer;
	ID3D11DepthStencilState	*m_depth_stencil_state;
	ID3D11DepthStencilView	*m_depth_stencil_view;
	ID3D11RasterizerState	*m_rasterizer_state;

	D3DXMATRIX				m_projection_matrix;
	D3DXMATRIX				m_world_matrix;
	D3DXMATRIX				m_ortho_matrix;
};