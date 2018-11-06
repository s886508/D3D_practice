#pragma once

#include <QtWidgets/QDialog>
#include "ui_d3d_practice_gui.h"

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

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

	bool RenderFrame();

private:
	Ui::d3d_practice_guiClass ui;

	DisplayWindow *m_display_window;

	// D3D
	IDXGISwapChain			*m_swapchain;
	ID3D11Device			*m_device;
	ID3D11DeviceContext		*m_device_context;
	ID3D11RenderTargetView	*m_render_target_view;
};
