/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Date {
    int day, month, year;

    int dayNumber() const {
        int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        int y = year - (month < 3);
        int dayNum = (y + y / 4 - y / 100 + y / 400 + t[month - 1] + day) % 7;
        if (dayNum == 0) {
          dayNum = 7;
        }
        return dayNum;
    }

    int daysInMonth(int m, int y) const {
        if (m == 2) {
            if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
                return 29;
            else
                return 28;
        } else if (m == 4 || m == 6 || m == 9 || m == 11) {
            return 30;
        } else {
            return 31;
        }
    }

    bool isValidDate() const {
        if (month < 1 || month > 12 || day < 1 || day > daysInMonth(month, year) || year < 0) {
            return false;
        }
        return true;
    }

    int newDate(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
        if (!isValidDate()) {
            return 1;
        }
        return 0;
    }

    string getDayOfWeek() {
        string days[] = {" ", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        if (!isValidDate()) return "Invalid Date";
        int dayIndex = dayNumber();
        return days[dayIndex];
    }

    void printDate() {
        string months[13] = {" ", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        if (isValidDate()) {
            cout << months[month] << " " << day << ", " << year << "\n";
        } else {
            cout << "Invalid Date\n";
        }
    }

   static int calculateDifference(const Date& from, const Date& to)  {
        static int increment[12] = { 1, -2, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };
        int daysInc = 0;
        if (to.day - from.day < 0) {
            int month = to.month - 2; 
            if (month < 0)
                month = 11; 
            daysInc = increment[month];
            if ((month == 1) && (to.year % 4 == 0))
                daysInc++; 
        }

        int total1 = from.year * 360 + from.month * 30 + from.day;
        int total2 = to.year * 360 + to.month * 30 + to.day;
        int diff = total2 - total1;
        int years = diff / 360;
        int months = (diff - years * 360) / 30;
        int days = diff - years * 360 - months * 30 + daysInc;

        if (from.day == 1 && to.day == 31) {
            months--;
            days = 30;
        }

        return diff;
    }
    bool operator<(const Date& date) const {
        if (!isValidDate() || !date.isValidDate()) return false;
        if (year != date.year) return year < date.year;
        if (month != date.month) return month < date.month;
        return day < date.day;
    }
};

int main() {
    Date ma, ba, ra;
    if (ma.newDate(17, 1, 2024) == 1 || ba.newDate(12, 7, 2034) == 1 || ra.newDate(25, 9, 2001) == 1) {
        cout << "Error: Invalid date.\n";
        return 1;
    }

    vector<Date> dates;
    dates.push_back(ma);
    dates.push_back({2, 1, 2020});

    sort (dates.begin(), dates.end());
  
    for (auto d:dates) {
    d.printDate();
    }
    return 0;
}
