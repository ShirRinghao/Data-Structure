#include "course.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

// Function takes a vector of class that contains all information from an input
// 		file (passed in by reference), an output file and the department
// 		name that needs to be searched and print out.
void department(const std::vector<Course> &allinfo, std::ofstream &output,
                char depart_name[]) {
  // Create a vector of class that stores all courses match department search
  // 		and all of these courses will be output to user.
  std::vector<Course> depart;
  for (unsigned int i = 0; i < allinfo.size(); i++) {
    if (allinfo[i].getDepartment() == depart_name) {
      depart.push_back(allinfo[i]);
    }
  }
  // While no course found, end the program.
  // Else, sort the course vector by a custom sort function.
  if (depart.size() == 0) {
    output << "No data available." << std::endl;
    exit(0);
  }
  sort(depart.begin(), depart.end(), departSort);
  // Setting up initial length for each output category, first use a for loop to
  // 		find the max length for each category, then use another for loop
  // to
  //  	format all information for output.
  int max_num = 9, max_title = 11, max_day = 3, max_start = 10, max_end = 8;
  output << "Dept " << depart_name << std::endl;
  for (unsigned int i = 0; i < depart.size(); i++) {
    int temp_title = 0, temp_day = 0;
    temp_title = depart[i].getTitle().length();
    temp_day = depart[i].getDate().length();
    max_title = std::max(max_title, temp_title);
    max_day = std::max(max_day, temp_day);
  }
  // Formatting the headline.
  output << std::left << std::setw(max_num + 2) << std::setfill(' ')
         << "Coursenum" << std::setw(max_title + 2) << "Class Title"
         << std::setw(max_day + 2) << "Day" << std::setw(max_start + 2)
         << "Start Time" << std::setw(max_end) << "End Time" << std::endl;
  output << std::string(max_num, '-') << "  " << std::string(max_title, '-')
         << "  " << std::string(max_day, '-') << "  "
         << std::string(max_start, '-') << "  " << std::string(max_end, '-')
         << std::endl;
  // Formatting all output information.
  for (unsigned int i = 0; i < depart.size(); i++) {
    output << std::setw(max_num + 2) << std::setfill(' ') << depart[i].getCode()
           << std::setw(max_title + 2) << depart[i].getTitle()
           << std::setw(max_day + 2) << depart[i].getDate()
           << std::setw(max_start + 2) << depart[i].getBegin_time()
           << std::setw(max_end) << depart[i].getEnd_time() << std::endl;
  }
  output << depart.size() << " entries" << std::endl;
}

// Function takes a vector of class that contains all information from an input
// 		file (passed in by reference), an output file and the room name
//   (if there is one) that needs to be searched and print out.

// When no specific room is mentioned, function finds all unique course and then
// 		print them by alphabetical order. If a specific room is
// 		mentioned,
//		search for all courses that match the room, print them out.
void room(const std::vector<Course> &allinfo, std::ofstream &output,
          char room_name[] = "") {
  std::vector<std::string> allrooms;
  // Nested for loops to find all unqiue rooms without duplicates in the file
  // 		for later output.
  // If a specific room is mentioned, find that specific room if it is in the
  //		file.
  bool room_name_found = (room_name == "") ? true : false;
  for (unsigned int i = 0; i < allinfo.size(); i++) {
    bool find = false;
    for (unsigned int j = 0; j < allrooms.size(); j++) {
      if (allinfo[i].getRoom() == allrooms[j]) {
        find = true;
        break;
      }
    }
    if (!find) {
      if (allinfo[i].getRoom() == room_name) {
        room_name_found = true;
      }
      allrooms.push_back(allinfo[i].getRoom());
    }
  }
  // If a specific room is mentioned, clear allrooms, add that specific room
  // 		into the vector for output.
  // No course matches requirement, then end the program.
  if (!room_name_found || allrooms.size() == 0) {
    output << "No data available." << std::endl;
    exit(0);
  }
  // sort allrooms by alphabetical order.
  sort(allrooms.begin(), allrooms.end());
  // for loops that deal output allrooms one by one.
  for (unsigned int i = 0; i < allrooms.size(); i++) {
    // Create a temporary vector of course class to store all courses that is
    // 		held in a specific room.
    std::vector<Course> temp_course;
    // Course that matches a specific room, add them into temporary class
    // 		vector.
    for (unsigned int j = 0; j < allinfo.size(); j++) {
      if (allinfo[j].getRoom() == allrooms[i]) {
        temp_course.push_back(allinfo[j]);
      }
    }
    // sort temporary vector by custom sort function.
    sort(temp_course.begin(), temp_course.end(), roomSort);
    // find the max length for each category, then use another for loop to
    // 		format all information for output.
    int max_num = 9, max_title = 11, max_day = 3, max_start = 10, max_end = 8,
        max_depart = 4;
    output << "Room " << allrooms[i] << std::endl;
    for (unsigned int j = 0; j < temp_course.size(); j++) {
      int temp_depart = 0, temp_title = 0, temp_day = 0;
      temp_depart = temp_course[j].getDepartment().length();
      temp_title = temp_course[j].getTitle().length();
      temp_day = temp_course[j].getDate().length();
      max_title = std::max(max_title, temp_title);
      max_day = std::max(max_day, temp_day);
      max_depart = std::max(max_depart, temp_depart);
    }
    // Formatting headline.
    output << std::left << std::setw(max_depart + 2) << std::setfill(' ')
           << "Dept" << std::setw(max_num + 2) << "Coursenum"
           << std::setw(max_title + 2) << "Class Title"
           << std::setw(max_day + 2) << "Day" << std::setw(max_start + 2)
           << "Start Time" << std::setw(max_end) << "End Time" << std::endl;
    output << std::string(max_depart, '-') << "  " << std::string(max_num, '-')
           << "  " << std::string(max_title, '-') << "  "
           << std::string(max_day, '-') << "  " << std::string(max_start, '-')
           << "  " << std::string(max_end, '-') << std::endl;
    // Formatting all courses information and put them into output file one by
    // 		one.
    for (unsigned int j = 0; j < temp_course.size(); j++) {
      output << std::setw(max_depart + 2) << std::setfill(' ')
             << temp_course[j].getDepartment() << std::setw(max_num + 2)
             << temp_course[j].getCode() << std::setw(max_title + 2)
             << temp_course[j].getTitle() << std::setw(max_day + 2)
             << temp_course[j].getDate() << std::setw(max_start + 2)
             << temp_course[j].getBegin_time() << std::setw(max_end)
             << temp_course[j].getEnd_time() << std::endl;
    }
    // Output the amount of entries for each room.
    if (i == allrooms.size() - 1) {
      output << temp_course.size() << " entries" << std::endl;
    } else {
      output << temp_course.size() << " entries\n" << std::endl;
    }
  }
}

void custom(const std::vector<Course> &allinfo, std::ofstream &output) {
  // Create a vector of string to store all courses in the file, sort them by
  // earlies time of the week. Then prints out the information of the earliest
  // course.
  std::vector<Course> allcourses;
  for (unsigned int i = 0; i < allinfo.size(); i++) {
    allcourses.push_back(allinfo[i]);
  }
  if (allcourses.size() == 0) {
    output << "No data available." << std::endl;
    exit(0);
  }
  sort(allcourses.begin(), allcourses.end(), customSort);
  output << "The earlies class of the week is " << allcourses[0].getTitle()
         << " on Monday at " << allcourses[0].getBegin_time() << " in room "
         << allcourses[0].getRoom() << "." << std::endl;
  // Using for loops to find how mony courses on each day from Monday to Friday.
  int class_monday = 0, class_tuesday = 0, class_wednesday = 0,
      class_thursday = 0, class_friday = 0;
  for (unsigned int i = 0; i < allcourses.size(); i++) {
    if (allcourses[i].getDay() == 1) {
      class_monday += 1;
    } else if (allcourses[i].getDay() == 2) {
      class_tuesday += 1;
    } else if (allcourses[i].getDay() == 3) {
      class_wednesday += 1;
    } else if (allcourses[i].getDay() == 4) {
      class_thursday += 1;
    } else {
      class_friday += 1;
    }
  }
  // Format the output.
  output << "There are " << class_monday << " different classes on Monday.\n"
         << "There are " << class_tuesday << " different classes on Tuesday.\n"
         << "There are " << class_wednesday
         << " different classes on Wednesday.\n"
         << "There are " << class_thursday
         << " different classes on Thursday.\n"
         << "There are " << class_friday << " different classes on Friday.\n";
}

int main(int argc, char *argv[]) {
  // Open the input file and read, then open the output file to write, create
  // 		a vecctor to store all information.
  std::ifstream infile(argv[1]);
  std::ofstream outfile(argv[2]);
  std::vector<Course> allinfo;
  if (!infile) {
    std::cerr << "File cannot be opened" << std::endl;
    exit(1);
  }

  // Using for loop to add allinformation, if a class has two or more
  // 		different days of class time, add them one by one into class
  // 		vector.
  while (infile) {
    std::string id, department, course_code, course_name, date, begin_time,
        end_time, location;
    infile >> id >> department >> course_code >> course_name >> date >>
        begin_time >> end_time >> location;
    for (unsigned int i = 0; i < date.length(); i++) {
      allinfo.push_back(Course(id, department, course_code, course_name,
                               date[i], begin_time, end_time, location));
    }
  }
  // If the input file is empty, end the program.
  if (allinfo.size() == 0) {
    outfile << "No data available." << std::endl;
    return 0;
  }
  // For different commands, program will run different functions to handle
  // 		each situation. If the command is other than dept, room and
  // custom, send
  //		error messege and end the program.
  if (std::string(argv[3]) == "dept") {
    department(allinfo, outfile, argv[4]);
  } else if (std::string(argv[3]) == "room") {
    if (argc == 5)
      room(allinfo, outfile, argv[4]);
    else
      room(allinfo, outfile);
  } else if (std::string(argv[3]) == "custom") {
    custom(allinfo, outfile);
  } else {
    std::cerr << "ERROR: Unknown Command: " << argv[3] << '\n';
    exit(1);
  }
  outfile << std::endl;
  return 0;
}
