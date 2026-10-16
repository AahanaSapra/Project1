#include "Date.h"
#include <cctype>
#include <cstdlib>

// TODO: Implement isValid() and daysBetween() below.
//
// You may create your own helper functions in this .cpp file for tasks such as:
//   - leap-year detection
//   - determining the number of days in a month
//   - converting a Date to a serial-day value
//
// These helpers are implementation details. They do NOT need to be declared
// in Date.h. Do not add a constructor or member functions to Date.

// Anonymous namespace to define helper functions
namespace {
    // Determine whether given year is a leap year
    bool isLeap(int year) {
        if ((year % 4 == 0) && (year % 100 != 0)) { // Divisble by 4 and NOT 100
            return true;
        }
        else if ((year % 400) == 0) { // Divisible by 400
            return true;
        }
        return false;
    }

    // Return number of days in given month
    int monthLen(int month, int year) {
        if (month == 2) {
            if (isLeap(year)) {
                return 29;
            }
            return 28;
        }
        else if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) {
            return 30;
        }
        return 31;
    }

    // Convert calendar date to serial number
    int toSerial(int day, int month, int year) {
        int totalDays = 0;

        // Add days for all prior years starting from 1900
        for (int y = 1900; y < year; y++) {
            if (isLeap(y)) {
                totalDays += 366;
            }
            else {
                totalDays += 365;
            }
        }

        // Add days for all prior months in current year
        for (int m = 1; m < month; m++) {
            totalDays += monthLen(m, year);
        }

        // Add days of current month
        totalDays += day;

        return totalDays;
    }
}

namespace DateUtil {

    bool parseISO(const std::string& s, Date& out) {
        // Enforce "YYYY-MM-DD" with digits in the correct positions
        if (s.size() != 10 || s[4] != '-' || s[7] != '-') return false;
        for (int i : {0, 1, 2, 3, 5, 6, 8, 9}) if (!std::isdigit((unsigned char)s[i])) return false;
        out.y = std::atoi(s.substr(0, 4).c_str());
        out.m = std::atoi(s.substr(5, 2).c_str());
        out.d = std::atoi(s.substr(8, 2).c_str());
        return true;
    }

    bool isValid(const Date& dt) {
        // TODO: return true only if dt is a real calendar date (handle leap years)
        if ((dt.y < 1) || (dt.m < 1) || (dt.m > 12) || (dt.d < 1) || (dt.d > monthLen(dt.m, dt.y))) {
            return false;
        }
        return true;
    }

    bool sameDay(const Date& a, const Date& b) {
        // Exact same calendar date
        return (a.y == b.y) && (a.m == b.m) && (a.d == b.d);
    }

    int daysBetween(const Date& a, const Date& b) {
        // TODO: compute nonnegative difference in days between a and b.
        // You may implement via a serial-day function (e.g., Rata Die).
        int aSerial = toSerial(a.d, a.m, a.y);
        int bSerial = toSerial(b.d, b.m, b.y);

        if (aSerial > bSerial) {
            return (aSerial - bSerial);
        }

        return (bSerial - aSerial);
    }

} // namespace DateUtil
