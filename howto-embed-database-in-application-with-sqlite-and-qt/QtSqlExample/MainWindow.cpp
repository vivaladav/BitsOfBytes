#include "MainWindow.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget * parent)
	: QMainWindow(parent)
{
	// window title
	setWindowTitle("Qt SQL and SQLite");

	// -- set fixed size --
	const int WIN_W = 320;
	const int WIN_H = 180;
	setMinimumSize(WIN_W, WIN_H);
	setMaximumSize(WIN_W, WIN_H);

	// create GUI
	BuildWindow();

	// -- DATABASE INIT --
	DatabaseConnect();
	DatabaseInit();
	DatabasePopulate();
}

// ===== PRIVATE =====
void MainWindow::BuildWindow()
{
	QWidget * content = new QWidget;
	setCentralWidget(content);

	// main layout
	QVBoxLayout * layoutMain = new QVBoxLayout;
	content->setLayout(layoutMain);

	// -- VERT SPACER --
	layoutMain->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));

	// -- INPUT ROW --
	QHBoxLayout * layoutRow = new QHBoxLayout;
	layoutMain->addLayout(layoutRow);

	// input field
	mInputText = new QLineEdit;
	mInputText->setPlaceholderText("1 - 10");
	mInputText->setValidator(new QIntValidator(mInputText));

	connect(mInputText, &QLineEdit::textChanged, this, &MainWindow::OnInput);

	layoutRow->addWidget(mInputText);

	// search button
	mButtonSearch = new QPushButton("SEARCH");
	mButtonSearch->setEnabled(false);

	connect(mButtonSearch, &QPushButton::clicked, this, &MainWindow::OnSearchClicked);

	layoutRow->addWidget(mButtonSearch);

	// -- OUTPUT ROW --
	mOutputText = new QLabel("...");
	mOutputText->setAlignment(Qt::AlignCenter);
	layoutMain->addWidget(mOutputText);

	// -- VERT SPACER --
	layoutMain->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void MainWindow::DatabaseConnect()
{
	const QString DRIVER("QSQLITE");

	if(QSqlDatabase::isDriverAvailable(DRIVER))
	{
		QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

		db.setDatabaseName(":memory:");

		if(!db.open())
			qWarning() << "MainWindow::DatabaseConnect - ERROR: " << db.lastError().text();
	}
	else
		qWarning() << "MainWindow::DatabaseConnect - ERROR: no driver " << DRIVER << " available";
}

void MainWindow::DatabaseInit()
{
	QSqlQuery query("CREATE TABLE people (id INTEGER PRIMARY KEY, name TEXT)");

	if(!query.isActive())
		qWarning() << "MainWindow::DatabaseInit - ERROR: " << query.lastError().text();

}

void MainWindow::DatabasePopulate()
{
	QSqlQuery query;

	if(!query.exec("INSERT INTO people(name) VALUES('Eddie Guerrero')"))
		qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
	if(!query.exec("INSERT INTO people(name) VALUES('Gordon Ramsay')"))
		qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
	if(!query.exec("INSERT INTO people(name) VALUES('Alan Sugar')"))
		qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
	if(!query.exec("INSERT INTO people(name) VALUES('Dana Scully')"))
		qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
	if(!query.exec("INSERT INTO people(name) VALUES('Lila	Wolfe')"))
		qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
	if(!query.exec("INSERT INTO people(name) VALUES('Ashley Williams')"))
		qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
	if(!query.exec("INSERT INTO people(name) VALUES('Karen Bryant')"))
		qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
	if(!query.exec("INSERT INTO people(name) VALUES('Jon Snow')"))
		qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
	if(!query.exec("INSERT INTO people(name) VALUES('Linus Torvalds')"))
		qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
	if(!query.exec("INSERT INTO people(name) VALUES('Hayley Moore')"))
		qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
}

// ===== PRIVATE SLOTS =====
void MainWindow::OnInput()
{
	if(mInputText->text().length() > 0)
		mButtonSearch->setEnabled(true);
	else
		mButtonSearch->setEnabled(false);
}

void MainWindow::OnSearchClicked()
{
	QSqlQuery query;
	query.prepare("SELECT name FROM people WHERE id = ?");
	query.addBindValue(mInputText->text().toInt());

	if(!query.exec())
		qWarning() << "MainWindow::OnSearchClicked - ERROR: " << query.lastError().text();

	if(query.first())
		mOutputText->setText(query.value(0).toString());
	else
		mOutputText->setText("person not found");
}
