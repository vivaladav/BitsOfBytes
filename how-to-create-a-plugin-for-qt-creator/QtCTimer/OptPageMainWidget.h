#pragma once

#include <QWidget>

class QSpinBox;

namespace QtCTimer
{

class Settings;

class OptPageMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptPageMainWidget(const Settings * settings);

    Settings GenerateSettings() const;

private:
    QSpinBox * mInputTime;
};

} // namespace QtCTimer
