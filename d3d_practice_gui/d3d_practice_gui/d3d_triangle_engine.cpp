#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include "d3d_def.h"
#include "d3d_triangle_engine.h"

TriangleEngine::TriangleEngine() :
	m_swapchain(nullptr),
	m_device(nullptr),
	m_device_context(nullptr),
	m_render_target_view(nullptr),
	m_vertex_shader(nullptr),
	m_pixel_shader(nullptr),
	m_vertex_buffer(nullptr),
	m_matrix_buffer(nullptr),
	m_index_buffer(nullptr),
	m_input_layout(nullptr), 
	m_depth_stencil_buffer(nullptr),
	m_depth_stencil_state(nullptr),
	m_depth_stencil_view(nullptr),
	m_rasterizer_state(nullptr)
{

}

TriangleEngine::~TriangleEngine() {
	CleanD3D();
}

void TriangleEngine::Init(HWND hwnd) {
	InitD3D(hwnd);
	InitD3DBuffer();
	InitD3DPipeline();
}

void TriangleEngine::InitD3D(HWND hwnd) {
	DXGI_SWAP_CHAIN_DESC scd;

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Width = WIDTH;
	scd.BufferDesc.Height = HEIGHT;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hwnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = 0;

	auto hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, NULL,
		D3D11_SDK_VERSION, &scd, &m_swapchain, &m_device, NULL, &m_device_context);

	ID3D11Texture2D *back_buffer = nullptr;
	if (m_swapchain)
		m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer);
	if (m_device && back_buffer)
		m_device->CreateRenderTargetView(back_buffer, NULL, &m_render_target_view);
	if (back_buffer)
		back_buffer->Release();

	if (m_device) {
		D3D11_TEXTURE2D_DESC depth_texture_desc;
		ZeroMemory(&depth_texture_desc, sizeof(D3D11_TEXTURE2D_DESC));
		depth_texture_desc.Width = WIDTH;
		depth_texture_desc.Height = HEIGHT;
		depth_texture_desc.MipLevels = 1;
		depth_texture_desc.ArraySize = 1;
		depth_texture_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_texture_desc.SampleDesc.Count = 1;
		depth_texture_desc.SampleDesc.Quality = 0;
		depth_texture_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_texture_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth_texture_desc.CPUAccessFlags = 0;
		depth_texture_desc.MiscFlags = 0;

		m_device->CreateTexture2D(&depth_texture_desc, NULL, &m_depth_stencil_buffer);

		D3D11_DEPTH_STENCIL_DESC depth_stecil_desc;
		depth_stecil_desc.DepthEnable = true;
		depth_stecil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depth_stecil_desc.DepthFunc = D3D11_COMPARISON_LESS;

		depth_stecil_desc.StencilEnable = true;
		depth_stecil_desc.StencilReadMask = 0xFF;
		depth_stecil_desc.StencilWriteMask = 0xFF;

		depth_stecil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depth_stecil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depth_stecil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depth_stecil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		depth_stecil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depth_stecil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depth_stecil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depth_stecil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		m_device->CreateDepthStencilState(&depth_stecil_desc, &m_depth_stencil_state);

		if (m_device_context)
			m_device_context->OMSetDepthStencilState(m_depth_stencil_state, 1);

		D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
		ZeroMemory(&depth_stencil_view_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

		depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depth_stencil_view_desc.Texture2D.MipSlice = 0;

		m_device->CreateDepthStencilView(m_depth_stencil_buffer, &depth_stencil_view_desc, &m_depth_stencil_view);

		if (m_device_context)
			m_device_context->OMSetRenderTargets(1, &m_render_target_view, m_depth_stencil_view);

		D3D11_RASTERIZER_DESC raster_desc;
		ZeroMemory(&raster_desc, sizeof(D3D11_RASTERIZER_DESC));
		raster_desc.AntialiasedLineEnable = false;
		raster_desc.CullMode = D3D11_CULL_BACK;
		raster_desc.DepthBias = 0;
		raster_desc.DepthBiasClamp = 0.f;;
		raster_desc.DepthClipEnable = true;
		raster_desc.FillMode = D3D11_FILL_SOLID;
		raster_desc.FrontCounterClockwise = false;
		raster_desc.MultisampleEnable = false;
		raster_desc.ScissorEnable = false;
		raster_desc.SlopeScaledDepthBias = 0.f;

		m_device->CreateRasterizerState(&raster_desc, &m_rasterizer_state);

		if (m_device_context)
			m_device_context->RSSetState(m_rasterizer_state);
	}

	if (m_device_context) {
		D3D11_VIEWPORT view_port;
		ZeroMemory(&view_port, sizeof(D3D11_VIEWPORT));
		view_port.TopLeftX = 0;
		view_port.TopLeftY = 0;
		view_port.Width = WIDTH;
		view_port.Height = HEIGHT;
		view_port.MinDepth = 0.f;
		view_port.MaxDepth = 1.f;

		m_device_context->RSSetViewports(1, &view_port);
	}

	const auto filed_of_view = (float)D3DX_PI / 4.f;
	const auto screen_aspect_ratio = (float)WIDTH / (float)HEIGHT;
	const auto screen_depth = 1000.f;
	const auto screen_near = 0.1f;

	D3DXMatrixPerspectiveFovLH(&m_projection_matrix, filed_of_view, screen_aspect_ratio, screen_near, screen_depth);
	D3DXMatrixIdentity(&m_world_matrix);
	D3DXMatrixOrthoLH(&m_ortho_matrix, (float)WIDTH, (float)HEIGHT, screen_near, screen_depth);
}

void TriangleEngine::CleanD3D() {
	if (m_vertex_buffer) {
		m_vertex_buffer->Release();
		m_vertex_buffer = nullptr;
	}

	if (m_index_buffer) {
		m_index_buffer->Release();
		m_index_buffer = nullptr;
	}

	if (m_matrix_buffer) {
		m_matrix_buffer->Release();
		m_matrix_buffer = nullptr;
	}

	if (m_rasterizer_state) {
		m_rasterizer_state->Release();
		m_rasterizer_state = nullptr;
	}

	if (m_depth_stencil_view) {
		m_depth_stencil_view->Release();
		m_depth_stencil_view = nullptr;
	}

	if (m_depth_stencil_state) {
		m_depth_stencil_state->Release();
		m_depth_stencil_state = nullptr;
	}

	if (m_depth_stencil_buffer) {
		m_depth_stencil_buffer->Release();
		m_depth_stencil_buffer = nullptr;
	}

	if (m_input_layout) {
		m_input_layout->Release();
		m_input_layout = nullptr;
	}

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

void TriangleEngine::InitD3DPipeline() {
	ID3D10Blob *vertex_blob = nullptr, *pixel_blob = nullptr;
	D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, 0, &vertex_blob, 0, 0);
	D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, 0, &pixel_blob, 0, 0);

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

void TriangleEngine::InitD3DBuffer() {
	if (m_device) {
		{
			VERTEX *vertex = new VERTEX[3];
			vertex[0].x = -1.f, vertex[0].y = -1.f, vertex[0].z = 0.f;
			vertex[0].color = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
			vertex[1].x = 0.f, vertex[1].y = 1.f, vertex[1].z = 0.f;
			vertex[1].color = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
			vertex[2].x = 1.f, vertex[2].y = -1.f, vertex[2].z = 0.f;
			vertex[2].color = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);

			D3D11_BUFFER_DESC buf_desc;
			ZeroMemory(&buf_desc, sizeof(D3D11_BUFFER_DESC));

			buf_desc.Usage = D3D11_USAGE_DYNAMIC;
			buf_desc.ByteWidth = sizeof(VERTEX) * 3;  // For drawgin triangle currently.
			buf_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			D3D11_SUBRESOURCE_DATA vertex_data;
			vertex_data.pSysMem = vertex;
			vertex_data.SysMemPitch = 0;
			vertex_data.SysMemSlicePitch = 0;

			m_device->CreateBuffer(&buf_desc, &vertex_data, &m_vertex_buffer);
		}

		{
			unsigned long *index = new unsigned long[3];
			index[0] = 0;
			index[1] = 1;
			index[2] = 2;

			D3D11_BUFFER_DESC buf_desc;
			ZeroMemory(&buf_desc, sizeof(D3D11_BUFFER_DESC));

			buf_desc.Usage = D3D11_USAGE_DEFAULT;
			buf_desc.ByteWidth = sizeof(unsigned long) * 3;
			buf_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			buf_desc.CPUAccessFlags = 0;
			buf_desc.MiscFlags = 0;
			buf_desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA index_data;
			index_data.pSysMem = index;
			index_data.SysMemPitch = 0;
			index_data.SysMemSlicePitch = 0;

			m_device->CreateBuffer(&buf_desc, &index_data, &m_index_buffer);
		}

		{
			D3D11_BUFFER_DESC buf_desc;
			ZeroMemory(&buf_desc, sizeof(D3D11_BUFFER_DESC));

			buf_desc.Usage = D3D11_USAGE_DYNAMIC;
			buf_desc.ByteWidth = sizeof(MatrixBufferType);
			buf_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			buf_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			buf_desc.MiscFlags = 0;
			buf_desc.StructureByteStride = 0;

			m_device->CreateBuffer(&buf_desc, NULL, &m_matrix_buffer);
		}
	}
}

void TriangleEngine::SetShaderParam(const D3DXMATRIX &view_matrix) {
	D3D11_MAPPED_SUBRESOURCE ms;
	MatrixBufferType *data = nullptr;

	D3DXMATRIX world_matrix(m_world_matrix), projection_matrix(m_projection_matrix);

	/*D3DXMatrixTranspose(&world_matrix, &world_matrix);
	D3DXMatrixTranspose(&view_matrix, &view_matrix);
	D3DXMatrixTranspose(&projection_matrix, &projection_matrix);*/

	if (m_device_context)
		m_device_context->Map(m_matrix_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);

	data = (MatrixBufferType*)ms.pData;
	data->world = world_matrix;
	data->view = view_matrix;
	data->projection = projection_matrix;

	if (m_device_context) {
		m_device_context->Unmap(m_matrix_buffer, 0);
		m_device_context->VSSetConstantBuffers(0, 1, &m_matrix_buffer);
	}
}

bool TriangleEngine::RenderFrame(const D3DXMATRIX &view_matrix) {
	if (m_device_context) {
		m_device_context->ClearRenderTargetView(m_render_target_view, D3DXCOLOR(1.f, 0.2f, 0.4f, 1.f));
		m_device_context->ClearDepthStencilView(m_depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}

	RenderTriangle();
	SetShaderParam(view_matrix);
	// Draw to back buffer
	if (m_device_context)
		m_device_context->DrawIndexed(3, 0, 0);

	if (m_swapchain)
		m_swapchain->Present(0, 0);

	return true;
}

void TriangleEngine::RenderTriangle() {
	if (m_device_context) {
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;

		m_device_context->IASetVertexBuffers(0, 1, &m_vertex_buffer, &stride, &offset);
		m_device_context->IASetIndexBuffer(m_index_buffer, DXGI_FORMAT_R32_UINT, 0);
		m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}