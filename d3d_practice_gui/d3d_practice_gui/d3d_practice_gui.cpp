#include "d3d_practice_gui.h"
#include "display_window.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

d3d_practice_gui::d3d_practice_gui(QWidget *parent)
	: QDialog(parent),
	m_display_window(new DisplayWindow(this)),
	m_swapchain(nullptr),
	m_device(nullptr),
	m_device_context(nullptr),
	m_render_target_view(nullptr)
{
	ui.setupUi(this);

	if (m_display_window) {
		m_display_window->setGeometry(50, 50, 320, 240);
		InitD3D((HWND)m_display_window->winId());
	}
	
}

d3d_practice_gui::~d3d_practice_gui() {
	CleanD3D();
}

void d3d_practice_gui::InitD3D(HWND hwnd) {
	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hwnd;
	scd.SampleDesc.Count = 4;
	scd.Windowed = true;

	auto hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &scd, &m_swapchain, &m_device, NULL, &m_device_context);
	assert(SUCCEEDED(hr));

	ID3D11Texture2D *back_buffer = nullptr;
	if (m_swapchain)
		m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
	if (m_device && back_buffer)
		m_device->CreateRenderTargetView(back_buffer, NULL, &m_render_target_view);
	if (back_buffer)
		back_buffer->Release();
	if (m_device_context) {
		m_device_context->OMSetRenderTargets(1, &m_render_target_view, NULL);

		D3D11_VIEWPORT view_port;
		ZeroMemory(&view_port, sizeof(D3D11_VIEWPORT));
		view_port.TopLeftX = 0;
		view_port.TopLeftY = 0;
		view_port.Width = 320;
		view_port.Height = 240;

		m_device_context->RSSetViewports(1, &view_port);
	}
}

void d3d_practice_gui::CleanD3D() {
	if (m_swapchain)
		m_swapchain->Release();
	if (m_render_target_view)
		m_render_target_view->Release();
	if (m_device)
		m_device->Release();
	if (m_device_context)
		m_device_context->Release();
}

void d3d_practice_gui::paintEvent(QPaintEvent *e) {
	if (!RenderFrame())
		QWidget::paintEvent(e);
}

bool d3d_practice_gui::RenderFrame() {
	if (m_device_context)
		m_device_context->ClearRenderTargetView(m_render_target_view, D3DXCOLOR(1.f, 0.2f, 0.4f, 1.f));

	// ToDo: Rendering frame onto back buffer.

	if (m_swapchain)
		m_swapchain->Present(0, 0);

	return true;
}