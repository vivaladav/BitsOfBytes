#pragma once

#include <QMainWindow>

class QLabel;
class QLineEdit;
class QPushButton;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget * parent = nullptr);

private:
	void BuildWindow();

	void DatabaseConnect();
	void DatabaseInit();
	void DatabasePopulate();

private slots:
	void OnInput();
	void OnSearchClicked();

private:
	QLineEdit * mInputText;
	QPushButton * mButtonSearch;
	QLabel * mOutputText;
};
