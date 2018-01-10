#include "PanelConcat.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QString>
#include <QVBoxLayout>

PanelConcat::PanelConcat(QWidget *parent)
	: QWidget(parent)
{
	setMinimumWidth(MIN_W);
	setMinimumHeight(MIN_H);

	QVBoxLayout * layout = new QVBoxLayout;
	setLayout(layout);

	// -- ROW 0 --
	QHBoxLayout * layoutRow = new QHBoxLayout;
	layout->addLayout(layoutRow);

	mInputA = new QLineEdit(this);
	layoutRow->addWidget(mInputA);

	layoutRow->addSpacerItem(new QSpacerItem(10, 1, QSizePolicy::Minimum, QSizePolicy::Maximum));

	mInputB = new QLineEdit(this);
	layoutRow->addWidget(mInputB);

	// -- SPACER --
	layout->addSpacerItem(new QSpacerItem(1, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));

	// -- ROW 1 --
	layoutRow = new QHBoxLayout;
	layout->addLayout(layoutRow);

	layoutRow->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum));

	mButtonConcat = new QPushButton("CONCAT", this);
	layoutRow->addWidget(mButtonConcat);

	connect(mButtonConcat, &QPushButton::clicked, this, &PanelConcat::ConcatData);

	layoutRow->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum));

	mButtonCancel = new QPushButton("CANCEL", this);
	layoutRow->addWidget(mButtonCancel);

	connect(mButtonCancel, &QPushButton::clicked, this, &PanelConcat::CancelData);

	layoutRow->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Maximum));

	// -- SPACER --
	layout->addSpacerItem(new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

	// -- ROW 2 --
	mLabelRes = new QLabel(this);
	layout->addWidget(mLabelRes,0, Qt::AlignCenter);

	// -- SPACER --
	layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void PanelConcat::ConcatData()
{
	mLabelRes->setText(mInputA->text() + mInputB->text());

	emit DataAvailable(mLabelRes->text());
}

void PanelConcat::CancelData()
{
	mInputA->clear();
	mInputB->clear();

	mLabelRes->clear();

	emit DataCleared();
}
