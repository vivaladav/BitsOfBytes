#include "MainWindow.h"

#include "PanelConcat.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	PanelConcat * panel = new PanelConcat(this);

	setCentralWidget(panel);
}

