#include "hash_table.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Below two functions from my own homework 6 recursion functions and it can be
// referenced to the following webiste
// https://stackoverflow.com/questions/9552295/
// using-recursion-and-backtracking-to-generate-all-possible-combinations

void helper(const std::vector<std::string> &all_info,
            std::vector<std::vector<std::string>> &all_entries,
            std::vector<std::string> one_entry, int index, int start) {
  // Base case: all info has been through
  if (index == (int)all_info.size())
    return;
  // Case1: a vector with only one information out of six category is a possible
  // and valid entry
  if (one_entry.size() > 0)
    all_entries.push_back(one_entry);
  // Normal case: go through all index
  for (unsigned int i = start; i < all_info.size(); i++) {
    one_entry.push_back(all_info[i]);
    helper(all_info, all_entries, one_entry, index + 1, i + 1);
    one_entry.pop_back();
  }
}

// Function that finds all possible combination of a single movie, add them into
// all entries vectors
void find_combo(const std::vector<std::string> &all_info,
                std::vector<std::vector<std::string>> &all_entries) {
  std::vector<std::string> one_entry;
  // push back the a empty version of current movie
  all_entries.push_back(one_entry);
  // starting from index 0
  int index = 0;
  int start = 0;
  helper(all_info, all_entries, one_entry, index, start);
}

// Function that reads all movies, and insert them into hash table
void read_movies(const std::string &movies_file, hash_table &table,
                 std::vector<Original_Movie *> &all_full_version) {
  std::string line;
  std::ifstream all_movies(movies_file);
  std::string name;
  int counter = 0;
  // While loop that reads all information from the files
  // Every single loop means a movie has been read
  while (all_movies >> name) {
    // Pointer that points to the class that has full information of the movie
    Original_Movie *full_version = new Original_Movie;
    std::vector<std::string> vector_all_info;
    std::string year, length, actors, genre, roles, all_info;
    int num_actors, num_genre, num_roles;
    all_movies >> year >> length;
    // Adding all information into below two vectors without dulipcates
    (*full_version).name = name;
    (*full_version).year = year;
    (*full_version).length = length;
    vector_all_info.push_back(name);
    vector_all_info.push_back(year);
    vector_all_info.push_back(length);
    all_movies >> num_genre;
    std::string tmp_genre;
    // Adding all genre into a string
    for (int i = 0; i < num_genre; i++) {
      all_movies >> tmp_genre;
      (*full_version).genre.push_back(tmp_genre);
      genre += tmp_genre;
    }
    vector_all_info.push_back(genre);
    all_movies >> num_actors;
    std::string tmp_actors;
    // Adding all actors name into a string
    for (int i = 0; i < num_actors; i++) {
      all_movies >> tmp_actors;
      (*full_version).actors.push_back(tmp_actors);
      actors += tmp_actors;
    }
    vector_all_info.push_back(actors);
    all_movies >> num_roles;
    std::string tmp_roles;
    // Adding all roles into a string
    for (int i = 0; i < num_roles; i++) {
      all_movies >> tmp_roles;
      (*full_version).roles.push_back(tmp_roles);
      roles += tmp_roles;
    }
    vector_all_info.push_back(roles);
    // All information have been added, push it into a vector of class
    all_full_version.push_back(full_version);
    // Add all information into a string for hashing
    all_info = name + year + length + genre + actors + roles;

    // Locate memory address
    Original_Movie *tmp = all_full_version[counter];
    // Insert into hash table
    table.insert(all_info, tmp);
    // Find all possible combinations, add them into all_entries
    std::vector<std::vector<std::string>> all_entries;
    find_combo(vector_all_info, all_entries);

    // Insert all possible combinations from vector all_entries into indexes on
    // hash table
    for (unsigned int i = 0; i < all_entries.size(); i++) {
      std::string tmp_string;
      for (unsigned int j = 0; j < all_entries[i].size(); j++) {
        tmp_string += all_entries[i][j];
      }
      table.insert(tmp_string, tmp);
    }
    counter++;
  }
}

// Function that reads all actors, store each actor into a map, key is its
// number, value is its name
void read_actors(const std::string &file,
                 std::map<std::string, std::string> &all_actors) {
  std::string num, name;
  std::ifstream infile(file);
  while (infile >> num) {
    infile >> name;
    all_actors.insert(std::make_pair(num, name));
  }
}

// Function that prints out all correct solutions for a single query
void print_results(const std::vector<Original_Movie *> &all_answers,
                   std::vector<Original_Movie *> &all_full_version,
                   std::map<std::string, std::string> &all_actors) {
  // Print out how many solutions found
  std::cout << "Printing " << all_answers.size() << " result(s):" << std::endl;

  // For every single solution, print their infor in the correct order
  for (unsigned int i = 0; i < all_answers.size(); i++) {
    std::cout << all_answers[i]->name << std::endl;
    std::cout << all_answers[i]->year << std::endl;
    std::cout << all_answers[i]->length << std::endl;
    std::cout << all_answers[i]->genre.size();
    for (unsigned int j = 0; j < all_answers[i]->genre.size(); j++) {
      std::cout << " " << all_answers[i]->genre[j];
    }
    std::cout << std::endl << all_answers[i]->actors.size();
    // For actors and its roles, use for loop to match them up
    for (unsigned int j = 0; j < all_answers[i]->actors.size(); j++) {
      std::map<std::string, std::string>::iterator itr =
          all_actors.find(all_answers[i]->actors[j]);
      std::cout << " " << (*itr).second << " (" << all_answers[i]->roles[j]
                << ")";
    }
    std::cout << std::endl;
  }
}

// Function that searches for the index that contains the correct answers
void search(hash_table &table, const std::string &a_movie,
            std::vector<Original_Movie *> &all_full_version,
            std::map<std::string, std::string> &all_actors) {
  std::vector<Original_Movie *> all_answers;
  int index = table.search(a_movie);
  // Calculate the index that may contains the correct value, if doesn't match,
  // use while loop to search the next index until an empty spot is found
  while (!table.checkindex(index, a_movie)) {
    if (table.checkempty(index)) {
      std::cout << "No results for query." << std::endl;
      return;
    }
    index++;
    // Reaches the end of hash table, start again from its beginning
    if (index == table.size()) {
      index = 0;
    }
  }
  // Add all pointers that points the correct solutions
  table.AddPointer(index, all_answers);
  // Function that prints out the results
  print_results(all_answers, all_full_version, all_actors);
}

// Function that reads all input
void read_input(hash_table &table,
                std::vector<Original_Movie *> &all_full_version) {
  std::string line, movies_file, actors_file;
  std::map<std::string, std::string> all_actors;
  // Read table size, occupancy and files that need to be opened
  int table_size = 0;
  float occupancy = 0;
  // Get table_size, occupany, movie file and actor file from input
  while (std::cin >> line) {
    if (line == "table_size")
      std::cin >> table_size;
    else if (line == "occupancy")
      std::cin >> occupancy;
    else if (line == "movies")
      std::cin >> movies_file;
    else if (line == "actors")
      std::cin >> actors_file;
    else
      break;
  }
  // Read movie and actors file
  read_movies(movies_file, table, all_full_version);
  read_actors(actors_file, all_actors);
  std::string name;
  while (std::cin >> name) {
    // Command quit, end the program
    if (name == "quit") {
      break;
    }
    // Starting of a single query
    if (name == "query") {
      std::cin >> name;
    }
    // Below codes read all information about a single movie, add them into a
    // tmp string, then add them all together into info stirng
    std::string year, length, actors, roles, genre;
    int num_genre, num_roles, num_actors;
    std::cin >> year >> length >> num_genre;
    // Check the number eof genre, actors and roles, make sure the correct size
    // of each is added
    if (num_genre != 0) {
      std::string tmp_genre;
      for (int i = 0; i < num_genre; i++) {
        std::cin >> tmp_genre;
        genre += tmp_genre;
      }
    }
    std::cin >> num_actors;
    if (num_actors != 0) {
      std::string tmp_actors;
      for (int i = 0; i < num_actors; i++) {
        std::cin >> tmp_actors;
        actors += tmp_actors;
      }
    }
    std::cin >> num_roles;
    if (num_actors != 0) {
      std::string tmp_role;
      for (int i = 0; i < num_roles; i++) {
        std::cin >> tmp_role;
        roles += tmp_role;
      }
    }
    // Check if name, year, length could be anything
    std::string info;
    if (name != "?") {
      info += name;
    }
    if (year != "?") {
      info += year;
    }
    if (length != "?") {
      info += length;
    }
    info = info + genre + actors + roles;
    // Search this query on hash table
    search(table, info, all_full_version, all_actors);
  }
}

int main() {
  // hash table to store all information
  hash_table table;
  // set table to a default value
  table.set_table(100, 0.5);
  // A vector of pointers that point to all movie that has full information
  std::vector<Original_Movie *> all_full_version;
  // Reading input and output the results
  read_input(table, all_full_version);
  // Deleting all pointers.
  for (unsigned int i = 0; i < all_full_version.size(); i++) {
    delete all_full_version[i];
  }
  return 0;
}
