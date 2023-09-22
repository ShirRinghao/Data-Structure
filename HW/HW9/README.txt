HOMEWORK 9: IMDB SEARCH


NAME:  < Linghao Shi >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Yifei Li, Yihen Lu, Xiaoyu Zhang, Hongyu Li, Daming Xu/http://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map
https://stackoverflow.com/questions/9552295/using-recursion-and-backtracking-to-generate-all-possible-combinations>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 35 hours >


HASH FUNCTION DESCRIPTION
My hash function hash a string that contains the information for a single query and all possible combinations of a movie object
While adding value of every single character in the string, times it to 101. 
In this case, a longer string will end up with a much bigger number than a shorter string, so those two will end up with very apart from each other. Thus this function satisfies the requirement to make all things as spread out as possible.
At the end, times 8, use aboslute value and % by the size of the table to make sure the index returned is a valid, not negative index on the current table.






HASH TABLE IMPLEMENTATION
I have stored all the data in a vector of vector of Movie class (this is the hash table).
Movie class has two varaibles, a pointer that points to the full version of this movie, and a string that contains the value of a movie that could be partial (64 possible combinations for a single movie)
There is another class called Orgianll_Movie that stores the full verison of a movie for later output.
If a query have many solutions, then we could find all those solutions in a single index, since all matching items will have the same hash value, and be pushed in to a vector in the same index. For all the solutions, using their own pointer to direct to right place that contains the full information of this movie

If the program tries to insert a movie in an index which contains a movie that doesn't match the movie we are tryig to insert. Simply using loop to go through every index after current index unilt it find an empty one. If we reach the end of the table, start searching an empty spot again at the beginning

When entries number / table size is bigger than occupancy, resize using available insert function




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


