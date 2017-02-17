#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* You are given the following information, but you may prefer to do some research for yourself.

1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)? */

bool divides(unsigned a, unsigned b){
	return b % a == 0;
}

typedef enum DAYS {
	MONDAY    = 0,
	TUESDAY   = 1,
	WEDNESDAY = 2,
	THURSDAY  = 3,
	FRIDAY    = 4,
	SATURDAY  = 5,
	SUNDAY    = 6,
} DAYS;

static unsigned DAYS_IN_MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap_year (unsigned year){
	return divides(4, year) && (divides(400, year) || !divides(100, year));
}

unsigned days_in_month(unsigned month, unsigned year){
	if (month >= 12){
		exit(1);
	}
	unsigned days = DAYS_IN_MONTH[month];
	if (month == 1 && is_leap_year(year)){
		days++;
	}
	return days;
}

unsigned count_first_of_month_between (unsigned m_s, unsigned y_s, unsigned m_e, unsigned y_e, unsigned target){
	//day, month, year start and end
	//start inclusive end exclusive
	unsigned count = 0;
	unsigned current_year   = 1900;
	unsigned current_month  = 0;
	unsigned first_of_month = MONDAY;
	
	while (current_year < y_s || current_month < m_s){
		first_of_month += days_in_month(current_month, current_year);
		first_of_month %= 7;
		current_month++;
		if (current_month == 12){
			current_month = 0;
			current_year++;
		}
	}
	while (current_year < y_e || current_month < m_e ){
		if (first_of_month == target){
			count++;
		}
		first_of_month += days_in_month(current_month, current_year);
		first_of_month %= 7;
		current_month++;
		if (current_month == 12){
			current_month = 0;
			current_year++;
		}
	}
	return count;
}

int main(){
	printf("%u\n", count_first_of_month_between(0, 1901, 1, 2001, SUNDAY));
	return 0;
}