#include "OptPageMainWidget.h"

#include "Settings.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QSpinBox>
#include <QVBoxLayout>

namespace QtCTimer
{

OptPageMainWidget::OptPageMainWidget(const Settings * settings)
{
    QVBoxLayout * layout = new QVBoxLayout(this);

    // -- ROW activity time limit --
    QHBoxLayout * layoutRow = new QHBoxLayout;
    layout->addLayout(layoutRow);

    mInputTime = new QSpinBox;
    mInputTime->setMinimum(0);
    mInputTime->setMaximum(24 * 60 - 1);
    mInputTime->setValue(settings->GetTimeLimit());
    mInputTime->setSingleStep(1);
    mInputTime->setMaximumWidth(50);
    layoutRow->addWidget(mInputTime);

    QLabel * label = new QLabel(tr("Time (in minutes) to generate a warning"));
    layoutRow->addWidget(label);

    // -- VERTICAL SPACER --
    layout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

Settings OptPageMainWidget::GenerateSettings() const
{
    Settings settings;

    settings.SetTimeLimit(mInputTime->value());

    return settings;
}

} // namespace QtCTimer
