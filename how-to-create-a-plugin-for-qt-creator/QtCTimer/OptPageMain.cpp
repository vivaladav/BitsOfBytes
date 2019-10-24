#include "OptPageMain.h"

#include "OptPageMainWidget.h"
#include "Settings.h"

namespace QtCTimer
{

OptPageMain::OptPageMain(Settings * settings, QObject * parent)
    : IOptionsPage(parent)
    , mSettings(settings)
{
    setId("QtCTimerSettings");
    setDisplayName("General");
    setCategory("QtC Timer");
    setDisplayCategory("QtC Timer");
    setCategoryIcon(Utils::Icon(":/imgs/icon_timer.png"));
}

QWidget * OptPageMain::widget()
{
    if(nullptr == mWidget)
        mWidget = new OptPageMainWidget(mSettings);

    return mWidget;
}

void OptPageMain::apply()
{
    const Settings newSettings = mWidget->GenerateSettings();

    if(newSettings != *mSettings)
    {
        *mSettings = newSettings;

        mSettings->Save();

        emit SettingsChanged();
    }
}
void OptPageMain::finish()
{
    delete mWidget;
    mWidget = nullptr;
}

} // namespace QtCTimer
