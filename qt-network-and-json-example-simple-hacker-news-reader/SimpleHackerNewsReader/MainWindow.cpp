#include "MainWindow.h"

#include "StoryEntry.h"

#include <QByteArray>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

MainWindow::MainWindow(QWidget * parent)
	: QMainWindow(parent)
	, mPanelStories(nullptr)
	, mNetMan(new QNetworkAccessManager(this))
	, mNetReply(nullptr)
	, mDataBuffer(new QByteArray)
{
	// == WINDOW SETTINGS ==
	setWindowTitle("Simple Hacker News Reader");

	const int WIN_W = 1024;
	const int WIN_H = 550;
	setMinimumSize(WIN_W, WIN_H);
	setMaximumSize(WIN_W, WIN_H);

	// create GUI
	BuildWindow();
}

MainWindow::~MainWindow()
{
	delete mDataBuffer;
}

void MainWindow::BuildWindow()
{
	// -- MAIN WIDGET --
	QWidget * content = new QWidget;
	setCentralWidget(content);

	QVBoxLayout * layoutMain = new QVBoxLayout;
	content->setLayout(layoutMain);

	// -- REFRESH BUTTON --
	mButtonRefresh = new QPushButton("REFRESH");
	mButtonRefresh->setFixedWidth(200);

	layoutMain->addWidget(mButtonRefresh, 0, Qt::AlignHCenter);

	connect(mButtonRefresh, &QPushButton::clicked, this, &MainWindow::OnRefreshClicked);

	// -- VERT SPACER --
	layoutMain->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void MainWindow::ReadStory()
{
	const QString STR = QString("https://hacker-news.firebaseio.com/v0/item/%1.json").arg(mLatestStoriesID[mCurrStory++]);
	const QUrl STORY_URL(STR);

	mNetReply = mNetMan->get(QNetworkRequest(STORY_URL));

	connect(mNetReply, &QIODevice::readyRead, this, &MainWindow::OnDataReadyToRead);
	connect(mNetReply, &QNetworkReply::finished, this, &MainWindow::OnStoryReadFinished);
}

void MainWindow::NetworkCleanup()
{
	mNetReply->deleteLater();
	mNetReply = nullptr;

	mDataBuffer->clear();
}

// == PRIVATE SLOTS ==
void MainWindow::OnRefreshClicked()
{
	// disable button while processing data
	mButtonRefresh->setEnabled(false);

	// -- DOWNLOAD LIST OF STORIES --
	const QUrl STORIES_LIST_URL("https://hacker-news.firebaseio.com/v0/newstories.json");
	mNetReply = mNetMan->get(QNetworkRequest(STORIES_LIST_URL));

	connect(mNetReply, &QIODevice::readyRead, this, &MainWindow::OnDataReadyToRead);
	connect(mNetReply, &QNetworkReply::finished, this, &MainWindow::OnListReadFinished);
}

void MainWindow::OnDataReadyToRead()
{
	mDataBuffer->append(mNetReply->readAll());
}

void MainWindow::OnListReadFinished()
{
	QJsonDocument doc = QJsonDocument::fromJson(*mDataBuffer);
	QJsonArray array = doc.array();

	// -- STORE LATEST 10 STORIES ID --
	for(int i = 0; i < NUM_STORIES_SHOWED; ++i)
		mLatestStoriesID[i] = array[i].toInt();

	// -- CLEAN UP --
	NetworkCleanup();

	// -- SET UP PANEL STORIES --
	delete mPanelStories;

	mPanelStories = new QWidget;
	centralWidget()->layout()->addWidget(mPanelStories);

	QVBoxLayout * layout = new QVBoxLayout;
	mPanelStories->setLayout(layout);

	// -- START READING STORIES --
	mCurrStory = 0;

	ReadStory();
}

void MainWindow::OnStoryReadFinished()
{
	QJsonDocument doc = QJsonDocument::fromJson(*mDataBuffer);

	// -- ADD STORY --
	StoryEntry * entry = new StoryEntry(mCurrStory, doc.object());
	mPanelStories->layout()->addWidget(entry);

	// -- CLEAN UP --
	NetworkCleanup();

	// -- NEXT STORY OR FINISH --
	if(mCurrStory < NUM_STORIES_SHOWED)
		ReadStory();
	else
		mButtonRefresh->setEnabled(true);
}

