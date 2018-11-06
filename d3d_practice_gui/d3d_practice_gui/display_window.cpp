#include "display_window.h"

DisplayWindow::DisplayWindow(QWidget *parent /*= nullptr*/) :QWidget(parent) {
	setAttribute(Qt::WA_NativeWindow);
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);
}

QPaintEngine* DisplayWindow::paintEngine() const {
	return nullptr;
}