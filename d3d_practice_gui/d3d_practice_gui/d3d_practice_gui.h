#pragma once

#include <QtWidgets/QDialog>
#include "ui_d3d_practice_gui.h"

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11Buffer;
struct ID3D11InputLayout;

class DisplayWindow;

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

	bool RenderFrame();
	void RenderTriangle();

	void CreateTriangle();

private:
	Ui::d3d_practice_guiClass ui;

	DisplayWindow *m_display_window;

	// D3D
	IDXGISwapChain			*m_swapchain;
	ID3D11Device			*m_device;
	ID3D11DeviceContext		*m_device_context;
	ID3D11RenderTargetView	*m_render_target_view;

	ID3D11VertexShader		*m_vertex_shader;
	ID3D11PixelShader		*m_pixel_shader;

	ID3D11Buffer			*m_vertex_buffer;
	ID3D11InputLayout		*m_input_layout;
};
