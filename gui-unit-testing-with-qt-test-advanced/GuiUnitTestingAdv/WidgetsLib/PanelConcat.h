#pragma once

#include "WidgetsLibGlobal.h"

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;

class WIDGETSLIBSHARED_EXPORT PanelConcat : public QWidget
{
	Q_OBJECT

	MAKE_TESTABLE(PanelConcat);

public:
	explicit PanelConcat(QWidget * parent = nullptr);

signals:
	void DataAvailable(const QString & data);
	void DataCleared();

public slots:
	void ConcatData();
	void CancelData();

private:
	static const int MIN_W = 480;
	static const int MIN_H = 240;

private:
	QLineEdit * mInputA;
	QLineEdit * mInputB;

	QPushButton * mButtonConcat;
	QPushButton * mButtonCancel;

	QLabel * mLabelRes;
};

