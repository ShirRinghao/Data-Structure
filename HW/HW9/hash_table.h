#ifndef hash_table_h_
#define hash_table_h_

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// A class that store full information of a specific movie in order
class Original_Movie {
public:
  std::string name;
  std::string year;
  std::string length;
  std::vector<std::string> genre;
  std::vector<std::string> actors;
  std::vector<std::string> roles;
};

// A class that store all information of a specific movie as a string and a
// pointer to a class that has its all information
class Movie {
public:
  // Default and copy constructor
  Movie() : info(""), ptr(NULL) {}
  Movie(const std::string &other_info, Original_Movie *other_ptr)
      : info(other_info), ptr(other_ptr) {}
  std::string info;
  Original_Movie *ptr;
};

// Hash table
class hash_table {
public:
  // default constructor
  hash_table();

  hash_table(const int &size);
  // modify functions
  void set_table(const int &size, const float &occupancy);
  void insert(const std::string &a_movie, Original_Movie *ptr);

  // Function finds the index that contains the information we need by hashing
  // the passing string
  int search(const std::string &movie) { return Hash_Func(movie); };
  // Function that checks if the index that pass in contains the same
  // information
  bool checkindex(const int &index, const std::string &movie) {
    return (m_data[index][0].info == movie);
  }
  int size() const { return m_table; }
  // Function that checks if a spot can be directly inserted without linear
  // probing
  bool checkempty(const int &index) { return m_data[index][0].ptr == NULL; }
  // Add a pointer to all possible answers vector for later output
  void AddPointer(const int &index,
                  std::vector<Original_Movie *> &all_answers) const;

private:
  float m_entries;   // current number of entries
  int m_table;       // size of the table
  float m_occupancy; // occupancy limit
  std::vector<std::vector<Movie>> m_data;
  // vector of strings to store all data
  void resize();                          // Resize the table
  int Hash_Func(const std::string &info); // Hash function find index
};
#endif
