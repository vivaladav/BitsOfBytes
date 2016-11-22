#pragma once

#include <QMainWindow>

class QByteArray;
class QNetworkAccessManager;
class QNetworkReply;
class QPushButton;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget * parent = nullptr);
	~MainWindow();

private:
	void BuildWindow();

	void ReadStory();

	void NetworkCleanup();

private slots:
	void OnRefreshClicked();

	void OnDataReadyToRead();
	void OnListReadFinished();
	void OnStoryReadFinished();

private:
	static const int NUM_STORIES_SHOWED = 10;

private:
	int mLatestStoriesID[NUM_STORIES_SHOWED];

	QPushButton * mButtonRefresh;

	QWidget * mPanelStories;

	QNetworkAccessManager * mNetMan;
	QNetworkReply * mNetReply;
	QByteArray * mDataBuffer;

	int mCurrStory;
};
