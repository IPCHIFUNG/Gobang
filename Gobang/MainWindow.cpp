#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void MainWindow::setBackgroundMusic(bool isOn)	// ²¥·ÅºÍÔÝÍ£±³¾°ÒôÀÖ
{

}

void MainWindow::buttonClicked()				// ÆåÅÌ±»µã»÷ÏìÓ¦ÊÂ¼þ
{
	QString butName = sender()->objectName();

	if (butName == "Button_PVE")
		;
	else if (butName == "Button_PVE")
		;
	else if (butName == "Button_PVP")
		;
	else if (butName == "Button_Load")
		;
	else if (butName == "Button_Ranking")
		;
	else if (butName == "Button_Exit")
		;
}