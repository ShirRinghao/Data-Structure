// #ifndef __course_h_
// #define __course_h_
#include <cstdlib>
#include <string>
#include <vector>

class Course {
public:
  // CONSTRUCTOR
  Course(std::string course_id, std::string course_depart,
         std::string course_code, std::string course_name, char course_date,
         std::string begin_time, std::string end_time, std::string location);

  // ACCESSORS
  int getDay() const;
  std::string getDepartment() const;
  std::string getRoom() const;
  std::string getBegin_time() const;
  std::string getEnd_time() const;
  std::string getCode() const;
  std::string getDate() const;
  std::string getID() const;
  std::string getTitle() const;

private:
  // REPRESENTATION (member varables)
  char date;
  std::string id;
  std::string department;
  std::string code;
  std::string title;
  std::string startTime;
  std::string endTime;
  std::string loc;
};

// Custom sort function that works for room, department, and custom (from
//		command line).
bool roomSort(const Course &a, const Course &b);

bool timeSort(const Course &a, const Course &b);

bool departSort(const Course &a, const Course &b);

bool customSort(const Course &a, const Course &b);
// #endif
