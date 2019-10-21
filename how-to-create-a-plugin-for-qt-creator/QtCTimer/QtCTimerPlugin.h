#pragma once

#include <extensionsystem/iplugin.h>

class QTimer;

namespace QtCTimer
{

class OptPageMain;
class Settings;

class QtCTimerPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "QtCTimer.json")

public:
    QtCTimerPlugin();
    ~QtCTimerPlugin();

    bool initialize(const QStringList & arguments, QString * errorString) override;
    void extensionsInitialized() override;
    ShutdownFlag aboutToShutdown() override;

private slots:
    void OnTimeout();
    void UpdateTimer();

private:
    OptPageMain * mOptionsPage = nullptr;
    Settings * mSettings = nullptr;
    QTimer * mTimer = nullptr;
};

} // namespace QtCTimer
