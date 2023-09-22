#ifndef table_h_
#define table_h_
#include <iostream>
#include <vector>
template <class T> class Table {
public:
  // Typedefs
  typedef unsigned int size_type;

  // Constructors
  Table() { this->create(); }
  Table(size_type r, size_type c, const T &t = T()) { this->create(r, c, t); }
  Table(const Table &v) { copy(v); }

  // Operators
  Table &operator=(const Table &t);
  // Extra credit
  T *&operator[](int r) { return values[r]; }

  // Bool function that checks whether the table is empty
  bool empty() { return rows * cols == 0; }

  // Destructor
  ~Table() { clear_values(); }

  // Accessors
  size_type numRows() const { return rows; }
  size_type numColumns() const { return cols; }
  T get(const size_type r, const size_type c) const {
    // If the user has an invalid request, send error message.
    if (!check_bound(r, c)) {
      std::cerr << "ERROR! Out of bounds from get function." << std::endl;
      exit(1);
    }
    return values[r][c];
  }

  // Member functions
  void push_back_row(const std::vector<T> &new_row);
  void push_back_column(const std::vector<T> &new_col);
  void push_back_rows(const Table<T> &new_rows);
  void push_back_columns(const Table<T> &new_cols);
  void pop_back_row();
  void pop_back_column();
  void set(const size_type r, const size_type c, const T &val);
  void print() const;

private:
  // Representations
  size_type rows, cols;
  T **values;

  // Private member functions
  void create();
  void create(size_type rows, size_type cols, const T &val);
  void copy(const Table<T> &v);

  // Destructor that deletes all pointers in values
  void clear_values();

  // Check if user is trying to access an invalid position
  bool check_bound(size_type r, size_type c) const {
    return r < rows && c < cols;
  }
};

// Create an empty default table (null pointers everywhere).
template <class T> void Table<T>::create() {
  rows = cols = 0;
  values = NULL;
}

// Create a vector with size rows, cols, each location equals to given value.
template <class T>
void Table<T>::create(size_type r, size_type c, const T &val) {
  rows = r;
  cols = c;
  values = new T *[r];
  for (size_type i = 0; i < r; i++) {
    values[i] = new T[c];
    for (size_type j = 0; j < c; j++) {
      values[i][j] = val;
    }
  }
}

// Copy a vector with size rows, cols from another table passed in by reference.
template <class T> void Table<T>::copy(const Table<T> &v) {
  rows = v.rows;
  cols = v.cols;
  values = new T *[rows];
  for (size_type i = 0; i < rows; i++) {
    values[i] = new T[cols];
    for (size_type j = 0; j < cols; j++) {
      values[i][j] = v.values[i][j];
    }
  }
}

// operator= takes a table passed in by reference.
template <class T> Table<T> &Table<T>::operator=(const Table<T> &t) {
  // If the table is initially empty, copy it directly.
  if (rows * cols == 0) {
    copy(t);
  } else {
    // If not initially empty, call clear_values to delete all pointers in
    // values and then copy it.
    clear_values();
    copy(t);
  }
  return *this;
}

// Function that delete all pointers in the table, cleans out everything on
// heap.
template <class T> void Table<T>::clear_values() {
  for (size_type i = 0; i < rows; i++) {
    delete[] values[i];
  }
  delete[] values;
}

template <class T> void Table<T>::push_back_row(const std::vector<T> &new_row) {
  // Check if table is initially empty (0*0)
  if (empty()) {
    std::cerr << "ERROR! The table is empty from push_back_row." << std::endl;
    exit(1);
  }
  // Check if trying to add a row with different column size
  if (cols != new_row.size()) {
    std::cerr << "ERROR! An attempt to push back a row with different "
                 "number of columns."
              << std::endl;
    exit(1);
  }
  // Create a temporary table with one more rows than values, copy everything
  // from values into temporary table except last row.
  T **temp = new T *[rows + 1];
  for (size_type i = 0; i < rows; i++) {
    temp[i] = new T[cols];
    for (size_type j = 0; j < cols; j++) {
      temp[i][j] = values[i][j];
    }
  }
  // Declare last row that will be added, using for loop to read the table which
  // is passed in by reference, add whatever needs to be pushed back into added
  // row.
  temp[rows] = new T[cols];
  for (size_type i = 0; i < new_row.size(); i++) {
    temp[rows][i] = new_row[i];
  }
  // empty values to store temporary table with correct number of columns and
  // rows
  clear_values();
  values = temp;
  rows++;
}

template <class T>
void Table<T>::push_back_column(const std::vector<T> &new_col) {
  // Check if table is initially empty (0*0)
  if (empty()) {
    std::cerr << "ERROR! The table is empty from push_back_column."
              << std::endl;
    exit(1);
  }
  // Check if trying to add a row with different row size
  if (new_col.size() != rows) {
    std::cerr << "ERROR! An attempt to push back a column with different "
                 "number of rows."
              << std::endl;
    exit(1);
  }
  // Declare a temporary table to store everything copied from values.
  T **temp = new T *[rows];
  for (size_type i = 0; i < rows; i++) {
    // size of columns + 1 for all rows
    temp[i] = new T[cols + 1];
    // Copy information from values except the added column
    for (size_type j = 0; j < cols; j++) {
      temp[i][j] = values[i][j];
    }
    // push back a column for each row.
    temp[i][cols] = new_col[i];
  }
  // empty values to store temporary table with correct number of columns and
  // rows
  clear_values();
  values = temp;
  cols++;
}

template <class T> void Table<T>::push_back_rows(const Table<T> &new_rows) {
  // Check if table is initially empty (0*0)
  if (empty()) {
    std::cerr << "ERROR! The table is empty from push_back_column."
              << std::endl;
    exit(1);
  }
  if (new_rows.cols != cols) {
    std::cerr << "ERROR! An attempt to push back a table with different "
                 "number of columns."
              << std::endl;
    exit(1);
  }
  // Create a temporary table with new size of rows (rows+ new_rows.rows)
  T **temp = new T *[rows + new_rows.rows];
  // Copy everything from values into temporary table
  for (size_type i = 0; i < rows; i++) {
    temp[i] = new T[cols];
    for (size_type j = 0; j < cols; j++) {
      temp[i][j] = values[i][j];
    }
  }
  // Add new_rows into temporary table
  for (size_type i = rows; i < rows + new_rows.rows; i++) {
    temp[i] = new T[cols];
    for (size_type j = 0; j < cols; j++) {
      temp[i][j] = new_rows.get(i - rows, j);
    }
  }
  // empty values to store temporary table with correct number of columns and
  // rows
  clear_values();
  values = temp;
  rows += new_rows.rows;
}

template <class T> void Table<T>::push_back_columns(const Table<T> &new_cols) {
  // Error checking
  if (new_cols.cols == 0) {
    std::cerr << "ERROR! An attempt to push back an empty table from "
                 "push_back_columns."
              << std::endl;
    exit(1);
  }
  if (new_cols.rows != rows) {
    std::cerr << "ERROR! An attempt to push back a table with different "
                 "number of rows."
              << std::endl;
    exit(1);
  }
  // Create a temporary table with the same row size
  T **temp = new T *[rows];
  // For each row, create a new size of columne (cols + new_cols.cols)
  // Copy everything from values into temporary table until added columns
  for (size_type i = 0; i < rows; i++) {
    temp[i] = new T[cols + new_cols.cols];
    for (size_type j = 0; j < cols; j++) {
      temp[i][j] = values[i][j];
    }
    // Copy all columns that need to be added into new created columns each row
    for (size_type j = cols; j < cols + new_cols.cols; j++) {
      temp[i][j] = new_cols.get(i, j - cols);
    }
  }
  // empty values to store temporary table with correct number of columns and
  // rows
  clear_values();
  values = temp;
  cols += new_cols.cols;
}

template <class T> void Table<T>::pop_back_column() {
  // Error checking when table is empty
  if (empty()) {
    std::cerr << "ERROR! The table is empty from pop_back_column." << '\n';
    exit(1);
  }
  // Create a temporary table with the same number of rows
  T **temp = new T *[rows];
  for (size_type i = 0; i < rows; i++) {
    // Create new column numbers for each row
    temp[i] = new T[cols - 1];
    for (size_type j = 0; j < cols - 1; j++) {
      // Copy all information from values into temporary table until cols-1.
      temp[i][j] = values[i][j];
    }
  }
  // empty values to store temporary table with correct number of columns and
  // rows
  clear_values();
  cols--;
  values = temp;
}

template <class T> void Table<T>::pop_back_row() {
  // Error checking
  if (empty()) {
    std::cerr << "ERROR! The table is empty from pop_back_row." << '\n';
    exit(1);
  }
  // Create a temporary table with size rows-1
  T **temp = new T *[rows - 1];
  for (size_type i = 0; i < rows - 1; i++) {
    // Create the same number of columns each row
    temp[i] = new T[cols];
    for (size_type j = 0; j < cols; j++) {
      // copy all information from values into temporary table until
      // values[rows-1]
      temp[i][j] = values[i][j];
    }
  }
  // empty values to store temporary table with correct number of columns and
  // rows
  clear_values();
  values = temp;
  rows--;
}

template <class T> void Table<T>::print() const {
  // Prints out the table
  std::cout << "table: " << rows << " rows, " << cols << " cols" << std::endl;
  // For loop that prints out values store in each position
  for (size_type i = 0; i < rows; i++) {
    for (size_type j = 0; j < cols; j++) {
      std::cout << values[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

template <class T>
void Table<T>::set(const size_type r, const size_type c, const T &val) {
  // Invalid request of set function
  if (!(check_bound(r, c))) {
    std::cerr << "ERROR! out of bound. Set command was unsuccessful!"
              << std::endl;
    exit(1);
  }
  // set values
  values[r][c] = val;
}

#endif
