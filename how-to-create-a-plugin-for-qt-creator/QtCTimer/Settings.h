#pragma once

namespace QtCTimer
{

class Settings
{
public:
    Settings();

    // -- DATA --
    // get time in minutes
    int GetTimeLimit() const;
    // set time in minutes
    void SetTimeLimit(int val);

    // -- I/O --
    void Load();
    void Save();

    // -- OPERATORS --
    bool operator==(const Settings & other) const;
    bool operator!=(const Settings & other) const;

private:
    int mTimeLimit;
};

// -- DATA --
inline int Settings::GetTimeLimit() const { return mTimeLimit; }
inline void Settings::SetTimeLimit(int val) { mTimeLimit = val; }

// -- OPERATORS --
inline bool Settings::operator==(const Settings & other) const
{
    return	mTimeLimit == other.mTimeLimit ;
}

inline bool Settings::operator!=(const Settings & other) const
{
    return !(*this == other);
}

} // namespace QtCTimer
