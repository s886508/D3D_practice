#include "d3d_practice_gui.h"
#include "display_window.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
#include "d3d_def.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

d3d_practice_gui::d3d_practice_gui(QWidget *parent)
	: QDialog(parent),
	m_display_window(new DisplayWindow(this)),
	m_swapchain(nullptr),
	m_device(nullptr),
	m_device_context(nullptr),
	m_render_target_view(nullptr),
	m_vertex_shader(nullptr),
	m_pixel_shader(nullptr),
	m_vertex_buffer(nullptr),
	m_input_layout(nullptr)
{
	ui.setupUi(this);

	if (m_display_window) {
		m_display_window->setGeometry(10, 10, 360, 360);
		InitD3D((HWND)m_display_window->winId());
		InitD3DPipeline();
		InitD3DBuffer();
		CreateTriangle();
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
		view_port.Width = 360;
		view_port.Height = 360;

		m_device_context->RSSetViewports(1, &view_port);
	}
}

void d3d_practice_gui::CleanD3D() {
	if (m_vertex_shader) {
		m_vertex_shader->Release();
		m_vertex_shader = nullptr;
	}

	if (m_pixel_shader) {
		m_pixel_shader->Release();
		m_pixel_shader = nullptr;
	}

	if (m_swapchain) {
		m_swapchain->Release();
		m_swapchain = nullptr;
	}
		
	if (m_render_target_view) {
		m_render_target_view->Release();
		m_render_target_view = nullptr;
	}
		
	if (m_device) {
		m_device->Release();
		m_device = nullptr;
	}
		
	if (m_device_context) {
		m_device_context->Release();
		m_device_context = nullptr;
	}
}

void d3d_practice_gui::InitD3DPipeline() {
	ID3D10Blob *vertex_blob = nullptr, *pixel_blob = nullptr;
	D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &vertex_blob, 0, 0);
	D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &pixel_blob, 0, 0);
	
	if (m_device) {
		if (vertex_blob)
			m_device->CreateVertexShader(vertex_blob->GetBufferPointer(), vertex_blob->GetBufferSize(), NULL, &m_vertex_shader);
		if (pixel_blob)
			m_device->CreatePixelShader(pixel_blob->GetBufferPointer(), pixel_blob->GetBufferSize(), NULL, &m_pixel_shader);
	}

	if (m_device_context) {
		m_device_context->VSSetShader(m_vertex_shader, 0, 0);
		m_device_context->PSSetShader(m_pixel_shader, 0, 0);
	}

	// Init input layout
	D3D11_INPUT_ELEMENT_DESC ie_desc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	if (m_device && m_vertex_shader) {
		m_device->CreateInputLayout(ie_desc, 2, vertex_blob->GetBufferPointer(), vertex_blob->GetBufferSize(), &m_input_layout);
	}

	if (m_device_context) {
		m_device_context->IASetInputLayout(m_input_layout);
	}
}

void d3d_practice_gui::InitD3DBuffer() {
	if (m_device) {
		D3D11_BUFFER_DESC buf_desc;
		ZeroMemory(&buf_desc, sizeof(D3D11_BUFFER_DESC));

		buf_desc.Usage = D3D11_USAGE_DYNAMIC;
		buf_desc.ByteWidth = sizeof(VERTEX) * 3;  // For drawgin triangle currently.
		buf_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		m_device->CreateBuffer(&buf_desc, NULL, &m_vertex_buffer);
	}
}

void d3d_practice_gui::paintEvent(QPaintEvent *e) {
	if (!RenderFrame())
		QWidget::paintEvent(e);
}

bool d3d_practice_gui::RenderFrame() {
	if (m_device_context)
		m_device_context->ClearRenderTargetView(m_render_target_view, D3DXCOLOR(1.f, 0.2f, 0.4f, 1.f));

	// Rendering frame onto back buffer.
	RenderTriangle();

	if (m_swapchain)
		m_swapchain->Present(0, 0);

	return true;
}

void d3d_practice_gui::RenderTriangle() {
	if (m_device_context) {
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;

		m_device_context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);
		m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Draw to back buffer
		m_device_context->Draw(3, 0);
	}
}

void d3d_practice_gui::CreateTriangle() {
	VERTEX v[] = {
		{0.f, 0.5f, 0.f, D3DXCOLOR(1.f, 0.f, 0.f, 1.f)},
		{0.45f, -0.5f, 0.f, D3DXCOLOR(0.f, 1.f, 0.f, 1.f)},
		{-0.45f, -0.5f, 0.f, D3DXCOLOR(0.f, 0.f, 1.f, 1.f)}
	};

	if (m_device_context) {
		D3D11_MAPPED_SUBRESOURCE ms;
		m_device_context->Map(m_vertex_buffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, v, sizeof(v));
		m_device_context->Unmap(m_vertex_buffer, NULL);
	}
}
