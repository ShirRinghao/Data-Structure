#include "course.h"

// Construct course id, course department, course code, course name, course date,
//		 begin time, end time, location for each class.
Course::Course(std::string course_id, std::string course_depart,
               std::string course_code, std::string course_name,
               char course_date, std::string begin_time, std::string end_time,
               std::string location) {
  id = course_id;
  department = course_depart;
  code = course_code;
  title = course_name;
  date = course_date;
  startTime = begin_time;
  endTime = end_time;
  loc = location;
}

// Change the date of each course from Monday to Friday into integter 1 to 5 for
//		easier time comparison.
int Course::getDay() const {
  int day = 0;
  if (date == 'M') {
    day = 1;
  } else if (date == 'T') {
    day = 2;
  } else if (date == 'W') {
    day = 3;
  } else if (date == 'R') {
    day = 4;
  } else if (date == 'F') {
    day = 5;
  }
  return day;
}

// ACCESSORS that return different information of a course.
std::string Course::getDepartment() const { return department; }

std::string Course::getRoom() const { return loc; }

std::string Course::getBegin_time() const { return startTime; }

std::string Course::getEnd_time() const { return endTime; }

std::string Course::getCode() const { return code; }

std::string Course::getDate() const {
  std::string curr_day;
  if (date == 'M') {
    curr_day = "Monday";
  } else if (date == 'T') {
    curr_day = "Tuesday";
  } else if (date == 'W') {
    curr_day = "Wednesday";
  } else if (date == 'R') {
    curr_day = "Thursday";
  } else if (date == 'F') {
    curr_day = "Friday";
  }
  return curr_day;
}

std::string Course::getID() const { return id; }

std::string Course::getTitle() const { return title; }

// Custom sort function for room.
bool roomSort(const Course &a, const Course &b) {
  if (a.getRoom() < b.getRoom() ||
      (a.getRoom() == b.getRoom() && a.getDay() < b.getDay()) ||
      (a.getRoom() == b.getRoom() && a.getDay() == b.getDay() &&
       timeSort(a, b)) ||
      (a.getRoom() == b.getRoom() && a.getDay() == b.getDay() &&
       timeSort(a, b) && a.getCode() < b.getCode())) {
    return true;
  }
  return false;
}

// Custom sort function that sort the beggening time of each classes from morning
//		to the end of the day.
bool timeSort(const Course &a, const Course &b) {
  if (a.getBegin_time()[5] == 'P' && a.getBegin_time().substr(0, 2) == "12" &&
      b.getBegin_time().substr(0, 2) != "12" && b.getBegin_time()[5] == 'P') {
    return true;

  } else if (b.getBegin_time()[5] == 'P' &&
             b.getBegin_time().substr(0, 2) == "12" &&
             a.getBegin_time().substr(0, 2) != "12" &&
             a.getBegin_time()[5] == 'P') {
    return false;

  } else if (a.getBegin_time()[5] < b.getBegin_time()[5] ||
             (a.getBegin_time()[5] == b.getBegin_time()[5] &&
              a.getBegin_time() < b.getBegin_time())) {
    return true;
  }
  return false;
}

// Custom sort function for department.
bool departSort(const Course &a, const Course &b) {
  if (a.getCode() < b.getCode() ||
      (a.getCode() == b.getCode() && a.getDay() < b.getDay()) ||
      (a.getCode() == b.getCode() && a.getDay() == b.getDay() &&
       timeSort(a, b))) {
    return true;
  }
  return false;
}

// Custom sort function when command line has custom.
bool customSort(const Course &a, const Course &b) {
  if (a.getDay() < b.getDay() ||
      (a.getDay() == b.getDay() && a.getRoom() < b.getRoom()) ||
      (a.getDay() == b.getDay() && a.getRoom() == b.getRoom() &&
       timeSort(a, b))) {
    return true;
  }
  return false;
}
