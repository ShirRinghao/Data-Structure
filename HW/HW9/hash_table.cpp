#include "hash_table.h"

// Default constructor, setting all values to zero
hash_table::hash_table() {
  m_table = 0;
  m_occupancy = 0;
  m_entries = 0.0;
}

// Function that takes in a string of a movie and a pointer points to its full
// information class, find the index that can be inserted, then insert into hash
// table
void hash_table::insert(const std::string &a_movie, Original_Movie *ptr) {
  // Checking if we need to resize the table
  if (m_entries / m_table >= m_occupancy) {
    resize();
  }
  // Find the index using hash function
  int index = Hash_Func(a_movie);
  // If spot is filled by different movie, using while loop to find the first
  // index that is not empty or is contained the same information as passed in
  // string
  while (a_movie != m_data[index][0].info && m_data[index][0].ptr != NULL) {
    index++;
    // If we reach the end of a table, start again from the beginning
    if (index == m_table) {
      index = 0;
    }
  }
  // Case1: this spot is empty
  if (m_data[index][0].info == "" && m_data[index][0].ptr == NULL) {
    m_data[index][0].info = a_movie;
    m_data[index][0].ptr = ptr;
  }
  // Case2: the index contains the same information
  else {
    Movie tmp_movie(a_movie, ptr);
    m_data[index].push_back(tmp_movie);
  }
  m_entries += 1;
}

// Borrow the hash function code from below website
// http://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-
// when-using-hash-map

// Hash the pass in string, return an absolute value of index
int hash_table::Hash_Func(const std::string &info) {
  int value = 0;
  for (unsigned int i = 0; i < info.size(); ++i) {
    value *= 101;
    value += info[i];
  }
  return std::abs((value * 8) % m_table);
}

// Function that sets the table as given size and occupancy
void hash_table::set_table(const int &table_size, const float &occupancy) {
  m_table = table_size;
  m_occupancy = occupancy;
  // Using for loop to initialize all index with a vector of Movie class
  for (int i = 0; i < m_table; i++) {
    std::vector<Movie> tmp_vector;
    Movie tmp_movie;
    tmp_vector.push_back(tmp_movie);
    this->m_data.push_back(tmp_vector);
  }
}

// Function that resize the table when it reaches occupancy limit
void hash_table::resize() {
  m_table *= 2;
  m_entries = 0.0;
  // Create a temporary table to store all info
  hash_table tmp_table;
  tmp_table.set_table(m_table, m_occupancy);
  // for every index that contains values, use for loop to insert into a new
  // index on a larger table
  for (int i = 0; i < (m_table / 2); i++) {
    for (unsigned int j = 0; j < m_data[i].size(); j++) {
      if (m_data[i][j].ptr != NULL) {
        tmp_table.insert(m_data[i][j].info, m_data[i][j].ptr);
      }
    }
  }
  // clear the current table, make a copy from tmp table
  this->m_data.clear();
  this->m_data = tmp_table.m_data;
}

// Function that finds all answers in an index on the hashtable, pushing all
// pointers into a vector that contains all correct answers pointer
void hash_table::AddPointer(const int &index,
                            std::vector<Original_Movie *> &all_answers) const {
  for (unsigned int i = 0; i < m_data[index].size(); i++) {
    all_answers.push_back(m_data[index][i].ptr);
  }
}
