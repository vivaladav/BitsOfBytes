#pragma once

#include <QWidget>

#include <QUrl>

class QJsonObject;

class StoryEntry : public QWidget
{
	Q_OBJECT

public:
	explicit StoryEntry(int index, const QJsonObject & obj, QWidget * parent = nullptr);

private slots:
	void OnViewClicked();

private:
	QUrl mURL;
};
