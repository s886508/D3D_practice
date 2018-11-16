#pragma once

#include <QtWidgets/QDialog>
#include "ui_d3d_practice_gui.h"
#include "ID3d_engine.h"

class DisplayWindow;
class D3DCamera;
class TriangleEngine;
class TextureEngine;

class d3d_practice_gui : public QDialog
{
	Q_OBJECT

public:
	d3d_practice_gui(QWidget *parent = Q_NULLPTR);
	virtual ~d3d_practice_gui();

protected:
	void paintEvent(QPaintEvent *e) override;

protected Q_SLOTS:
	void slotRotationXChanged(int position);
	void slotRotationYChanged(int position);
	void slotRotationZChanged(int position);

	void slotPositionXChanged(int position);
	void slotPositionYChanged(int position);
	void slotPositionZChanged(int position);

private:
	void InitD3DCamera();
	void InitConnection();

private:
	Ui::d3d_practice_guiClass ui;

	DisplayWindow *m_display_window;

	std::shared_ptr<D3DCamera> m_d3d_camera;
	std::shared_ptr<ID3DEngine> m_d3d_engine;
};
