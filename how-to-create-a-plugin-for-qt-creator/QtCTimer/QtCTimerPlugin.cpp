#include "QtCTimerPlugin.h"

#include "OptPageMain.h"
#include "Settings.h"

#include <coreplugin/icore.h>

#include <QMessageBox>
#include <QMainWindow>
#include <QTime>
#include <QTimer>

namespace QtCTimer
{

QtCTimerPlugin::QtCTimerPlugin()
{
    // Create your members
}

QtCTimerPlugin::~QtCTimerPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
    delete mTimer;
    delete mSettings;
}

bool QtCTimerPlugin::initialize(const QStringList & arguments, QString * errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    // -- OPTIONS PAGE --
    mSettings = new Settings;
    mSettings->Load();

    mOptionsPage = new OptPageMain(mSettings, this);
    connect(mOptionsPage, &OptPageMain::SettingsChanged, this, &QtCTimerPlugin::UpdateTimer);

    // -- TIMING --
    mTimer = new QTimer;
    UpdateTimer();
    connect(mTimer, &QTimer::timeout, this, &QtCTimerPlugin::OnTimeout);
    mTimer->start();

    return true;
}

void QtCTimerPlugin::OnTimeout()
{
    mTimer->stop();

    QTime t(0, 0, 0);
    t = t.addSecs(mSettings->GetTimeLimit() * 60);

    QMessageBox::warning(Core::ICore::mainWindow(),
                         tr("Take a break!"),
                         tr("You have been using Qt Creator for %1.").arg(t.toString("hh:mm:ss")));

    mTimer->start();
}

void QtCTimerPlugin::UpdateTimer()
{
    const int t = 1000 * 60 * mSettings->GetTimeLimit();
    mTimer->setInterval(t);
}

void QtCTimerPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag QtCTimerPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)

    mTimer->stop();
    mTimer->disconnect();

    mOptionsPage->disconnect();

    return SynchronousShutdown;
}

} // namespace QtCTimer
