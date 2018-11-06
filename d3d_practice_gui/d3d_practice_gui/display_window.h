#pragma once
#include <qwidget.h>

class DisplayWindow : public QWidget {
	Q_OBJECT

public:
	DisplayWindow(QWidget *parent = nullptr);
	virtual ~DisplayWindow() = default;

protected:
	QPaintEngine* paintEngine() const override;
};
