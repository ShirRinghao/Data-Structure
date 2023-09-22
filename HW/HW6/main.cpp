#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

// Class to record the grid location.
class loc {
public:
  loc(int r = 0, int c = 0) : row(r), col(c) {}
  int row, col;
};

bool operator==(const loc &lhs, const loc &rhs) {
  return lhs.row == rhs.row && lhs.col == rhs.col;
}

// Function reads the input file, store all required word length in a vector of
// ints, all words in the dictionary int o a vector of string, all characters in
// the grid into a vector of vector of char.
void read(std::ifstream &dict, std::ifstream &puzzle,
          std::vector<std::vector<char>> &grid, std::vector<int> &requirement,
          std::vector<std::string> &all_words, std::vector<int> &word_length) {
  if (!dict) {
    std::cerr << "ERRPR! Dictionary file cannot be opened!" << std::endl;
    exit(1);
  };
  // Get all words in the dictionary.
  while (dict) {
    std::string curr;
    dict >> curr;
    all_words.push_back(curr);
  }
  if (!puzzle) {
    std::cerr << "ERROR! Initial grid file cannnot be opened" << std::endl;
  }
  // Get all information from initial grid file.
  while (puzzle) {
    std::string curr;
    puzzle >> curr;
    // Comments that will be ignored
    if (curr.substr(0, 1) == "!" || curr == "") {
      continue;
    }
    // line starts with '+' is the requirement word length, store them into a
    // vector
    if (curr.substr(0, 1) == "+") {
      int convert_to_int = std::stoi(curr);
      requirement.push_back(convert_to_int);
      word_length[convert_to_int - 1]++;
    } else {
      // Get all characters on the grid, store them into a vector of vector of
      // char
      std::vector<char> tmp;
      for (unsigned int i = 0; i < curr.size(); i++) {
        tmp.push_back(curr[i]);
      }
      grid.push_back(tmp);
    }
  }
}

bool search_from_loc(loc position, const std::vector<std::vector<char>> &grid,
                     const std::string &word) {
  // Case0: a word could not go to any directions, return false right away
  if (position.row + word.size() > grid.size() &&
      position.col + word.size() > grid[0].size()) {
    return false;
  }
  // Case1: not enough space for a word in current row. Word could only go
  // to the right
  else if (position.row + word.size() > grid.size()) {
    for (unsigned int i = position.col; i < word.size() + position.col; i++) {
      if (grid[position.row][i] != word[i - position.col]) {
        return false;
      }
      if (i == word.size() + position.col - 1) {
        return true;
      }
    }
  }
  // Case2: not enough space for a word in current column. Word could only
  // go downwards
  else if (position.col + word.size() > grid[0].size()) {
    for (unsigned int i = position.row; i < word.size() + position.row; i++) {
      // current letter doesn't match the letter in the word, return false
      if (grid[i][position.col] != word[i - position.row]) {
        return false;
      }
      // word is found
      if (i == word.size() + position.row - 1) {
        return true;
      }
    }
  }
  // Case3: a word could be across or down.
  else {
    // Search horizontally first.
    for (unsigned int i = position.col; i < word.size() + position.col; i++) {
      // current letter doesn't match the letter in the word, stop the loop
      if (grid[position.row][i] != word[i - position.col]) {
        break;
      }
      // Word if found

      if (i == word.size() + position.col - 1) {
        return true;
      }
    }
    // Search a word vertically
    for (unsigned int i = position.row; i < word.size() + position.row; i++) {
      // If the word is not found both vertically and horizontally on the board,
      // return false
      if (grid[i][position.col] != word[i - position.row]) {
        return false;
      }
      // Word is found
      if (i == word.size() + position.row - 1) {
        return true;
      }
    }
  }
  return true;
}

// If a word is found vertically, search if there is another word connected
// the word's tail or head without a '#' between them. If there is, then the
// solution is incorrect, function will return false
bool check_board_vertical(const loc &position, const std::string &word,
                          const std::vector<std::vector<char>> &solution) {
  // Case1: the word is in the middle of the grid
  if (position.row > 0 && word.size() + position.row < solution.size()) {
    // If the first letter before tail or the first letter after tail is not
    // '#', return false
    if (solution[position.row - 1][position.col] != '#' ||
        solution[position.row + word.size()][position.col] != '#') {
      return false;
    }
  }
  // Case2: word's head is first row, word's tail is the last row.
  // return true right away
  else if (position.row == 0 && position.row + word.size() == solution.size()) {
    return true;
  }
  // Case3: word's head is first row, and there is more rows after this word.
  else if (position.row == 0 && position.row + word.size() < solution.size()) {
    // If first letter after the word isn't '#' return false
    if (solution[word.size()][position.col] != '#') {
      return false;
    }
  }
  // Case4: word's last letter is the last column on the grid, check the first
  // letter before word if it is valid
  else {
    if (solution[position.row - 1][position.col] != '#') {
      return false;
    }
  }
  return true;
}

// Function does the same things as previous function, but it checks if the word
// is valid on the grid horizontally
bool check_board_horizontal(const loc &position, const std::string &word,
                            const std::vector<std::vector<char>> &solution) {
  // Case1: word is in the middle of the grid
  if (position.col > 0 && word.size() + position.col < solution[0].size()) {
    if (solution[position.row][position.col - 1] != '#' ||
        solution[position.row][position.col + word.size()] != '#') {
      return false;
    }
  }
  // Case2: word's head is first row, word's tail is the last row.
  // return true right away
  else if (position.col == 0 &&
           position.col + word.size() == solution[0].size()) {
    return true;
  }
  // Case3: word is at the start of the column
  else if (position.col == 0 &&
           position.col + word.size() < solution[0].size()) {
    if (solution[position.row][word.size()] != '#') {
      return false;
    }
  }
  // Case4: word is at the end of the column
  else {
    if (solution[position.row][position.col - 1] != '#') {
      return false;
    }
  }
  return true;
}

// Function that delete all words that will not possibly occur on the grid
// according to their length and length requirement from the grid.
void sortDictionary(std::vector<int> &all_length,
                    std::vector<std::string> &all_words,
                    const std::vector<int> &requirement,
                    const std::vector<std::vector<char>> &grid) {
  // Step1: find all words in the dictionary that don't match the requirement
  // word length, delete them from the dictionary

  // Find all possible length of the words, store them into a vector of int.

  for (unsigned int i = 0; i < requirement.size(); i++) {
    all_length.push_back(requirement[i]);
  }
  std::sort(all_length.begin(), all_length.end());
  // Search all words from the dictionary, if word's length matches the
  // requirement on the grid. If not delete the word.
  std::vector<std::string>::iterator itr = all_words.begin();
  for (; itr != all_words.end(); itr++) {
    bool find = false;
    for (unsigned int i = 0; i < all_length.size(); i++) {
      // If the word is found, go to the next word
      if ((int)(*itr).size() == all_length[i]) {
        find = true;
        break;
      }
    }
    // If the word is not found, delete it from dictionary
    if (!find) {
      all_words.erase(itr);
      itr--;
    }
  }
  // Step2: Search if the grid contain a word at any location in the grid, if
  // not, delete that word.
  for (std::vector<std::string>::iterator itr = all_words.begin();
       itr != all_words.end(); itr++) {
    std::vector<loc> first_letter;
    // first find any location in the grid that contains the first letter of the
    // word
    for (unsigned int r = 0; r < grid.size(); r++) {
      for (unsigned int c = 0; c < grid[r].size(); c++) {
        if (grid[r][c] == (*itr)[0]) {
          first_letter.push_back(loc(r, c));
        }
      }
    }
    // Search by using the first letter location found above
    // If the word is not found in the grid, delete it from the all_words list.
    for (unsigned int i = 0; i < first_letter.size(); i++) {
      if (search_from_loc(first_letter[i], grid, *itr)) {
        break;
      }
      if (!search_from_loc(first_letter[i], grid, *itr) &&
          i == first_letter.size() - 1) {
        all_words.erase(itr);
        itr--;
      }
    }
  }
}

// Final check if it is one of the valid solution(s) by comparing word length
// with the requirment
bool words_are_found(const std::vector<int> &word_length,
                     const std::vector<int> &current_word) {
  for (unsigned int i = 0; i < word_length.size(); i++) {
    if (word_length[i] != current_word[i]) {
      return false;
    }
  }
  return true;
}

// Recursive function that find all combinations of the solutions
// Passing in a vector of ints to record all words needed for this solution. A
// standard word length represents the requirement for the solution.
void find_all_combo(int steps, int index,
                    const std::vector<std::string> &all_words,
                    std::vector<std::string> &single_solution,
                    std::vector<std::vector<std::string>> &all_solutions,
                    const std::vector<int> &word_length,
                    std::vector<int> &current_length) {
  // Base case: one solution is found when the required number of words have
  // been added into vector of string
  if (steps == 0) {
    if (words_are_found(word_length, current_length)) {
      // Store this possible solution into all solutions (vector of vector of
      // strings)
      all_solutions.push_back(single_solution);
    }
    return;
  }
  for (int i = index; i < (int)all_words.size(); i++) {
    // Case1: when there are not enough words to fill a possible combination
    if ((int)all_words.size() - i < steps) {
      return;
    }
    // If the current word matches the required word by checking its word
    // length.
    if (current_length[all_words[i].size() - 1] <
        word_length[all_words[i].size() - 1]) {
      // Word matches the requirement
      current_length[all_words[i].size() - 1]++;
      single_solution.push_back(all_words[i]);
    } else {
      // If we don't need this word length in our solution or such word length
      // has already been fulfilled by other words, then go to the next word in
      // the possible words vector
      continue;
    }
    // call recursive function to find other words in a single solution
    find_all_combo(steps - 1, i + 1, all_words, single_solution, all_solutions,
                   word_length, current_length);
    // Delete the last word in single solution in order to find other possible
    // combination. Continue to search the next word
    if (single_solution[single_solution.size() - 1] == all_words[i]) {
      current_length[all_words[i].size() - 1]--;
      single_solution.pop_back();
      continue;
    }
  }
  return;
}

// Function that initiate the recursive function
void initial_combo(const std::vector<int> &all_length,
                   const std::vector<std::string> &all_words,
                   std::vector<std::vector<std::string>> &all_solutions,
                   const std::vector<int> &word_length) {
  // A vector to store a possible solution
  std::vector<std::string> one_solution;
  // A vector to record the current words in one_solution by their word length
  std::vector<int> current_length(10, 0);
  // Size is the number of words we need for one solution
  const int size = (int)all_length.size();
  find_all_combo(size, 0, all_words, one_solution, all_solutions, word_length,
                 current_length);
}

void check_solution(std::vector<std::vector<std::vector<char>>> &all_solutions,
                    const std::vector<std::vector<char>> &grid,
                    const std::vector<std::string> &words) {
  // Create a grid start with '#' filled at all locations
  std::vector<std::vector<char>> solution;
  std::vector<std::vector<bool>> across;
  std::vector<std::vector<bool>> down;
  for (unsigned int i = 0; i < grid.size(); i++) {
    std::vector<char> solution_row;
    std::vector<bool> across_row;
    std::vector<bool> down_row;
    for (unsigned int j = 0; j < grid[0].size(); j++) {
      solution_row.push_back('#');
      across_row.push_back(false);
      down_row.push_back(false);
    }
    solution.push_back(solution_row);
    across.push_back(across_row);
    down.push_back(down_row);
  }
  // At this point, all words in the vector have already been checked to be
  // a part of a possible solution and will occur on the board. So mark them
  // right away if its path is found

  // for all the words in one possibe solution, find each word's location,
  // replace '#' on such path by word's character
  for (unsigned int i = 0; i < words.size(); i++) {
    // Loop that go through all the words in one possible solution
    std::vector<loc> first_letter;
    // Loop that find all possible starting point for a single word
    for (unsigned int j = 0; j < grid.size(); j++) {
      for (unsigned int k = 0; k < grid[0].size(); k++) {
        if (grid[j][k] == words[i][0]) {
          first_letter.push_back(loc(j, k));
        }
      }
    }
    // Check each possible starting location using available function
    for (unsigned int j = 0; j < first_letter.size(); j++) {
      if (search_from_loc(first_letter[j], grid, words[i])) {
        std::string last_character(1, words[i][words[i].size() - 1]);
        // If the word is going down, check the last letter on the grid from
        // the starting point, if the function returns true, then it is
        // going across.
        if (first_letter[j].row + words[i].size() > grid.size()) {
          // correct path is found, mark its path on the solution grid and on
          // across vector true by using for loop
          for (unsigned int k = first_letter[j].col;
               k < words[i].size() + first_letter[j].col; k++) {
            solution[first_letter[j].row][k] =
                words[i][k - first_letter[j].col];
            across[first_letter[j].row][k] = true;
          }
          // Check if there is another at its head or tail
          if (!check_board_horizontal(first_letter[j], words[i], solution)) {
            return;
          }
        }
        // Otherwise the word is going down
        else if (first_letter[j].col + words[i].size() > grid[0].size()) {
          for (unsigned int k = first_letter[j].row;
               k < words[i].size() + first_letter[j].row; k++) {
            // correct path is found, mark its path on the solution grid and on
            // down vector true by using for loop
            solution[k][first_letter[j].col] =
                words[i][k - first_letter[j].row];
            down[k][first_letter[j].col] = true;
          }
          // Check if there is another at its head or tail
          if (!check_board_vertical(first_letter[j], words[i], solution)) {
            return;
          }
        }
        // Search word in both vertical and horizontal direction
        else {
          bool find = false;
          for (unsigned int x = first_letter[j].col;
               x < words[i].size() + first_letter[j].col; x++) {
            // Word is incorrect
            if (grid[first_letter[j].row][x] !=
                words[i][x - first_letter[j].col]) {
              break;
            }
            if (x == words[i].size() + first_letter[j].col - 1) {
              // correct path is found, mark its path on the solution grid and
              // on across vector true by using for loop
              for (unsigned int k = first_letter[j].col;
                   k < words[i].size() + first_letter[j].col; k++) {
                solution[first_letter[j].row][k] =
                    words[i][k - first_letter[j].col];
                across[first_letter[j].row][k] = true;
                find = true;
              }
            }
            // Check if there is another at its head or tail
            if (!check_board_horizontal(first_letter[j], words[i], solution) &&
                find) {
              return;
            }
          }
          if (!find) {
            // If not found on the gridd horizontal, then it must be vertically
            // placed on the grid
            for (unsigned int k = first_letter[j].row;
                 k < words[i].size() + first_letter[j].row; k++) {
              // correct path is found, mark its path on the solution grid and
              // on down vector true by using for loop
              solution[k][first_letter[j].col] =
                  words[i][k - first_letter[j].row];
              down[k][first_letter[j].col] = true;
            }
            // Check if there is another at its head or tail
            if (!check_board_vertical(first_letter[j], words[i], solution)) {
              return;
            }
          }
        }
      }
    }
  }

  // Codes below check if the current words combination is actually a valid
  // solution
  for (unsigned int i = 0; i < grid.size(); i++) {
    for (unsigned int j = 0; j < grid[0].size(); j++) {
      if (solution[i][j] != '#') {
        if (i + 1 == grid.size() && j + 1 == grid[0].size()) {
          if (solution[i][j - 1] != '#' && across[i][j - 1] == false) {
            return;
          }
          if (solution[i - 1][j] != '#' && down[i - 1][j] == false) {
            return;
          }
        } else if (i + 1 == grid.size()) {
          if (solution[i][j + 1] != '#' && across[i][j + 1] == false) {
            return;
          }
        } else if (j + 1 == grid[0].size()) {
          if (solution[i + 1][j] != '#' && down[i + 1][j] == false) {
            return;
          }
        } else {
          if (solution[i + 1][j] != '#' && down[i + 1][j] == false) {
            return;
          }
          if (solution[i][j + 1] != '#' && across[i][j + 1] == false) {
            return;
          }
        }
      }
    }
  }
  all_solutions.push_back(solution);
  return;
}

void print_board(
    const std::string &solution_mode, const std::string &output_mode,
    const std::vector<std::vector<std::vector<char>>> &all_solutions) {
  // If the solution vector size is zero, or its count only:
  if (all_solutions.size() == 0 || output_mode == "count_only") {
    std::cout << "Number of solution(s): " << all_solutions.size() << std::endl;
    return;
  }
  // Print all possible solutions
  if (output_mode == "print_boards" && solution_mode == "all_solutions") {
    std::cout << "Number of solution(s): " << all_solutions.size() << std::endl;
    for (unsigned int i = 0; i < all_solutions.size(); i++) {
      std::cout << "Board:" << std::endl;
      for (unsigned int j = 0; j < all_solutions[0].size(); j++) {
        for (unsigned int k = 0; k < all_solutions[0][0].size(); k++) {
          std::cout << all_solutions[i][j][k];
        }
        std::cout << std::endl;
      }
    }
  }
  // Print the first solution in solution vector
  else if (solution_mode == "one_solution") {
    std::cout << "Number of solution(s): 1" << std::endl;
    std::cout << "Boards:" << std::endl;
    for (unsigned int i = 0; i < all_solutions[0].size(); i++) {
      for (unsigned int j = 0; j < all_solutions[0][i].size(); j++) {
        std::cout << all_solutions[0][i][j];
      }
      std::cout << std::endl;
    }
  }
}

int main(int argc, char const *argv[]) {
  if (argc != 4 && argc != 5) {
    std::cerr << "ERROR! Wrong number of arguments in the command line" << '\n';
    exit(1);
  }
  std::ifstream dict(argv[1]);
  std::ifstream puzzle(argv[2]);
  std::vector<std::vector<char>> grid;
  std::vector<int> requirement;
  std::vector<std::string> all_words;
  std::vector<int> all_length;
  // Step 1: read the entire puzzle using read function
  std::vector<int> word_length(10, 0);
  read(dict, puzzle, grid, requirement, all_words, word_length);
  // Step 2: erase all the words will not be on the grid or word has wrong
  // length from the dictionary
  sortDictionary(all_length, all_words, requirement, grid);
  // Step 3: Find all possible solution by sorting all possible length of
  // the word first.
  std::vector<std::vector<std::string>> all_combo;
  initial_combo(all_length, all_words, all_combo, word_length);
  // Step 4: check each possible solution from all_combo vector if they are
  // valid.
  std::vector<std::vector<std::vector<char>>> all_solutions;
  for (unsigned int i = 0; i < all_combo.size(); i++) {
    check_solution(all_solutions, grid, all_combo[i]);
  }
  // Step5: output the results as the command line requires
  print_board(argv[3], argv[4], all_solutions);
  return 0;
}
