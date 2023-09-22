HOMEWORK 3: RESIZABLE TABLE


NAME:  < Linghao Shi >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Luoyan Zhang, https://stackoverflow.com/>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert # 10 hours >



ORDER NOTATION:

Write each answer in terms of n = the number of rows and m = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get O(1)

set O(1)

numRows O(1)

numColumns O(1)

push_back_row O(n*m)

push_back_column O(n*m)

pop_back_row O(n*m)

pop_back_column O(n*m)

print O(n*m)


TESTING & DEBUGGING STRATEGY:
Discuss your strategy for testing & debugging your program.
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Table class design & implementation?

I have used gdb and Dr. Memory for debug and testing for memory leak.
For corner cases, I have created a 1*1 table, and then use pop_back_column and
pop_back_row to test if the table could possibly pop its last row/column, it should 
results in a 1*0 or 0*1 table and should be successfully outputted. Moreover, 
if the table is 1*0 or 0*1, pushing back column or row will detect it, then automatically 
end the program if that ever happens.

For table's compacity of different type of objects, I have tried std::string,
char, and int. All of them work out.

Also, I have tested copy and assginment constructor. For destructor, I simply
created a table which has never been used. The table has been destructed when
it goes out of the scope.

I have created couple test cases for invalid request: set or get function request 
a spot that is not in the table (out of bound).
And trying to push back an empty row or column. All of these test cases should 
send an error message on the screen and end the program.

EXTRA CREDIT:
Indicate here if you implemented push_back for multiple rows or
multiple columns and/or rewrote your code using pointers instead of
subscripts for extra credit.  Also document the order notation for
your multi-row and multi-column push_back functions.

push_back_rows O(n*m)
push_back_columns O(n*m)
Basically for push_back_rows and push_back_cols, it is almost the same as pushing
back one row or one column. Instead of only pushing back one row or column, using
for loop to store all values into temporary table, then delete values table
from heap, give temporary table back to values.

Operator[]:
Using * to dereference pointers and get value at certain positions.

MISC. COMMENTS TO GRADER:
(optional, please be concise!)
