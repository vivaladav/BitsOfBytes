#include "Settings.h"

#include <coreplugin/icore.h>

namespace QtCTimer
{

// -- KEYS --
const QString GROUP("QTC_TIMER");
const QString OPT_TIME_LIMIT("TIME_LIMIT");

// -- DEFAULTS --
const int DEF_TIME_LIMIT = 30;

Settings::Settings()
    : mTimeLimit(DEF_TIME_LIMIT)
{
}

void Settings::Load()
{
    QSettings * s = Core::ICore::settings();

    s->beginGroup(GROUP);
    mTimeLimit = s->value(OPT_TIME_LIMIT, DEF_TIME_LIMIT).toInt();
    s->endGroup();
}

void Settings::Save()
{
    QSettings * s = Core::ICore::settings();

    s->beginGroup(GROUP);
    s->setValue(OPT_TIME_LIMIT, mTimeLimit);
    s->endGroup();
}

} // namespace QtCTimer
