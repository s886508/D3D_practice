#include "display_window.h"
#include "d3d_practice_gui.h"
#include "d3d_def.h"
#include "d3d_camera.h"
#include "d3d_triangle_engine.h"
#include "d3d_texture_engine.h"
#include "d3d_diffuselighting_engine.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

d3d_practice_gui::d3d_practice_gui(QWidget *parent)
	: QDialog(parent),
	m_display_window(new DisplayWindow(this)),
	m_d3d_camera(new D3DCamera()),
	m_d3d_engine(new DiffuseLightingEngine())
{
	ui.setupUi(this);

	InitConnection();

	if (m_display_window) {
		m_display_window->setGeometry(10, 10, WIDTH, HEIGHT);
		InitD3DCamera();
		m_d3d_engine->Init((HWND)m_display_window->winId());
	}
}

d3d_practice_gui::~d3d_practice_gui() {
	m_d3d_camera = nullptr;
	m_d3d_engine = nullptr;
}

void d3d_practice_gui::InitConnection() {
	connect(ui.camera_slider_rotation_x, &QSlider::sliderMoved, this, &d3d_practice_gui::slotRotationXChanged);
	connect(ui.camera_slider_rotation_y, &QSlider::sliderMoved, this, &d3d_practice_gui::slotRotationYChanged);
	connect(ui.camera_slider_rotation_z, &QSlider::sliderMoved, this, &d3d_practice_gui::slotRotationZChanged);
	connect(ui.camera_slider_rotation_x, &QSlider::valueChanged, this, &d3d_practice_gui::slotRotationXChanged);
	connect(ui.camera_slider_rotation_y, &QSlider::valueChanged, this, &d3d_practice_gui::slotRotationYChanged);
	connect(ui.camera_slider_rotation_z, &QSlider::valueChanged, this, &d3d_practice_gui::slotRotationZChanged);

	connect(ui.camera_slider_position_x, &QSlider::sliderMoved, this, &d3d_practice_gui::slotPositionXChanged);
	connect(ui.camera_slider_position_y, &QSlider::sliderMoved, this, &d3d_practice_gui::slotPositionYChanged);
	connect(ui.camera_slider_position_z, &QSlider::sliderMoved, this, &d3d_practice_gui::slotPositionZChanged);
	connect(ui.camera_slider_position_x, &QSlider::valueChanged, this, &d3d_practice_gui::slotPositionXChanged);
	connect(ui.camera_slider_position_y, &QSlider::valueChanged, this, &d3d_practice_gui::slotPositionYChanged);
	connect(ui.camera_slider_position_z, &QSlider::valueChanged, this, &d3d_practice_gui::slotPositionZChanged);
}

void d3d_practice_gui::paintEvent(QPaintEvent *e) {
	D3DXMATRIX view_matrix;
	if (m_d3d_camera)
		m_d3d_camera->GetViewMatrix(view_matrix);
	if (!m_d3d_engine->RenderFrame(view_matrix))
		QWidget::paintEvent(e);
}

void d3d_practice_gui::InitD3DCamera() {
	if (m_d3d_camera) {
		m_d3d_camera->SetPositionX(0.f);
		m_d3d_camera->SetPositionY(0.f);
		m_d3d_camera->SetPositionZ(-10.f);
	}
}

void d3d_practice_gui::slotRotationXChanged(int position) {
	if (m_d3d_camera) {
		m_d3d_camera->SetRotationX(position);
		update();
	}
}

void d3d_practice_gui::slotRotationYChanged(int position) {
	if (m_d3d_camera) {
		m_d3d_camera->SetRotationY(position);
		update();
	}
}

void d3d_practice_gui::slotRotationZChanged(int position) {
	if (m_d3d_camera) {
		m_d3d_camera->SetRotationZ(position);
		update();
	}
}

void d3d_practice_gui::slotPositionXChanged(int position) {
	if (m_d3d_camera) {
		m_d3d_camera->SetPositionX(position);
		update();
	}
}

void d3d_practice_gui::slotPositionYChanged(int position) {
	if (m_d3d_camera) {
		m_d3d_camera->SetPositionY(position);
		update();
	}
}

void d3d_practice_gui::slotPositionZChanged(int position) {
	if (m_d3d_camera) {
		m_d3d_camera->SetPositionZ(position);
		update();
	}
}