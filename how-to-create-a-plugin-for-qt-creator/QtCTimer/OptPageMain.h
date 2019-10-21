#pragma once

#include <coreplugin/dialogs/ioptionspage.h>

namespace QtCTimer
{

class OptPageMainWidget;
class Settings;

class OptPageMain : public Core::IOptionsPage
{
    Q_OBJECT

public:
    OptPageMain(Settings * settings, QObject * parent = nullptr);
    ~OptPageMain();

    QWidget * widget() override;

    void apply()  override;
    void finish()  override;

signals:
    void SettingsChanged();

private:
    Settings * mSettings = nullptr;

    OptPageMainWidget * mWidget = nullptr;
};

} // namespace QtCTimer
