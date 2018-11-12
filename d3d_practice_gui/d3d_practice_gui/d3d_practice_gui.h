#pragma once

#include <QtWidgets/QDialog>
#include <d3dx10math.h>
#include "ui_d3d_practice_gui.h"

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

class DisplayWindow;
class D3DCamera;

class d3d_practice_gui : public QDialog
{
	Q_OBJECT

public:
	d3d_practice_gui(QWidget *parent = Q_NULLPTR);
	virtual ~d3d_practice_gui();

protected:
	void paintEvent(QPaintEvent *e) override;

private:
	void InitD3D(HWND hwnd);
	void CleanD3D();
	void InitD3DPipeline();
	void InitD3DBuffer();

	void InitD3DCamera();

	void SetShaderParam();
	bool RenderFrame();
	void RenderTriangle();

	void CreateTriangle();

private:
	Ui::d3d_practice_guiClass ui;

	DisplayWindow *m_display_window;

	std::shared_ptr<D3DCamera> m_d3d_camera;

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
