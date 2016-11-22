#include "StoryEntry.h"

#include <QDesktopServices>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <QJsonObject>

#include <QDebug>

StoryEntry::StoryEntry(int index, const QJsonObject & obj, QWidget * parent) : QWidget(parent)
{
	// -- NEWS URL --
	QJsonObject::const_iterator it = obj.constFind("url");

	if(it != obj.end())
		mURL.setUrl(it.value().toString());
	else
		mURL.setUrl(QString("https://news.ycombinator.com/item?id=%1").arg(obj["id"].toInt()));

	// -- LAYOUT --
	QHBoxLayout * layout = new QHBoxLayout;
	setLayout(layout);

	// -- INDEX --
	QLabel * label = new QLabel(QString("%1.").arg(index, 2));
	layout->addWidget(label);

	// -- TITLE --
	QFont fontTitle;
	fontTitle.setPointSize(10);
	fontTitle.setBold(true);

	label = new QLabel(obj["title"].toString());
	label->setFont(fontTitle);
	layout->addWidget(label);

	// -- HOST --
	label = new QLabel(QString("(%1)").arg(mURL.host()));
	layout->addWidget(label);

	// -- SPACER --
	layout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));

	// -- POINTS --
	const int POINTS = obj["score"].toInt();

	if(1 == POINTS)
		label = new QLabel("1 point");
	else
		label = new QLabel(QString("%1 points").arg(POINTS));

	layout->addWidget(label);

	// -- SPACER --
	layout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Fixed, QSizePolicy::Minimum));

	// -- VIEW BUTTON --
	QPushButton * button = new QPushButton("VIEW");
	button->setFixedWidth(100);
	layout->addWidget(button);

	connect(button, &QPushButton::clicked, this, &StoryEntry::OnViewClicked);
}


// == PRIVATE SLOTS ==

void StoryEntry::OnViewClicked()
{
	QDesktopServices::openUrl(mURL);
}
