#include <iostream>
using namespace std;

#include "TimeCode.h"

// Constructor initializes time from hours, minutes, and seconds, handling rollover
TimeCode::TimeCode(unsigned int hr, unsigned int min, unsigned long long sec) {
    t = ComponentsToSeconds(hr, min, sec);
}

// Copy constructor from Zybook
TimeCode::TimeCode(const TimeCode& tc) {
    t = tc.t;
}

//Checks for over 59 errors for minutes and seconds
void TimeCode::SetHours(unsigned int hours) {
    t = ComponentsToSeconds(hours, GetMinutes(), GetSeconds());
}

void TimeCode::SetMinutes(unsigned int minutes) {
    if (minutes > 59) {
        throw invalid_argument("Invalid argument: Minutes cannot exceed 59");
    }
    t = ComponentsToSeconds(GetHours(), minutes, GetSeconds());
}

void TimeCode::SetSeconds(unsigned int seconds) {
    if (seconds > 59) {
        throw invalid_argument("Invalid argument: Seconds cannot exceed 59");
    }
    t = ComponentsToSeconds(GetHours(), GetMinutes(), seconds);
}

// Resets the time value to zero
void TimeCode::reset() {
    t = 0;
}

// Get functions return the respective time components
unsigned int TimeCode::GetHours() const {
    return t / 3600;
}

unsigned int TimeCode::GetMinutes() const {
    return (t % 3600) / 60;
}

unsigned int TimeCode::GetSeconds() const {
    return t % 60;
}

// Retrieves the individual components by reference
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const {
    hr = GetHours();
    min = GetMinutes();
    sec = GetSeconds();
}

// Converts hours, minutes, and seconds into a total second count
unsigned long long TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long sec) {
    return (static_cast<unsigned long long>(hr) * 3600) + (min * 60) + sec;
}

// Returns a string representation of the TimeCode
string TimeCode::ToString() const {
    return to_string(GetHours()) + ":" + to_string(GetMinutes()) + ":" + to_string(GetSeconds());
}

// Operator overloads
TimeCode TimeCode::operator+(const TimeCode& other) const {
    return TimeCode(0, 0, t + other.t);
}

TimeCode TimeCode::operator-(const TimeCode& other) const {
    if (t < other.t) {
        throw invalid_argument("Negative timecodes are not allowed.");
    }
    return TimeCode(0, 0, t - other.t);
}

TimeCode TimeCode::operator*(double a) const {
    return TimeCode(0, 0, static_cast<unsigned long long>(t * a));
}

TimeCode TimeCode::operator/(double a) const {
    if (a == 0) {
        throw invalid_argument("Invalid argument: Division by zero");
    }
    return TimeCode(0, 0, static_cast<unsigned long long>(t / a));
}


