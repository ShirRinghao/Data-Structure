HOMEWORK 7: SPATIALLY-EMBEDDED ADJACENCY MAPS


NAME:  < Linghao Shi >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< stackoverflow.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < #10 hours >



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity along with a short
justification for each of the functions below:

n: The total number of users
l: The total number of users with a location
d: The total number of users with degree >= 1
m: The total number of connections
p: The number of users that a function will print out

*After the homework is done, I have realized that I used for loop to find things in a map, which order notation is O(n). However, what I should do is to use find function because order notation for find is O(log n) which is a lot faster. So for functions below, all find order notation is in O(n)

loadConnections(): O(m)
Program has to go through entire list of connections file

loadLocations(): O(l)
Program has to go through entire list of locations file

printAllUsersWithinDistance():  O(n) + O(l) + O(p)
Program has to go through entire list of connections file to find a person first, then go through entire list of locations file to check if they are in range, then output the results

printDegreesHistogram(): O(n) + O(p)
Program has to go through entire list of connections file, then output the results

printDegreesOfAll(): O(n) + O(p) or O(n) + O(d)
(since we are printing the results in the for loop, the running time of printing is very quick and could be ignored)
Program has to go through entire list of connections file, then output the results
In this case, p and d are the same thing, since either one represents the total number of users that will be outputted.

printFriendsWithDegree():
assume N friends of a specific individual are found
O(n) + O(N*n) + O(p)
Program has to go through entire list of connections file to find a person's friends, check all his friends if they have the correct number of degrees, then output the results

printFriendsWithinDistance():
assume N friends of a specific individual are found
O(l) + O(n) + O(N*n) + O(p)
Program has to go through entire list of connections file and locations file to find a person's location and friends. For N number of friends that are found, calculate each distance between that person and his friends, then output the results

printUsersWithinIDRange():
O(n) + O(p)
Program has to go through entire list of connections twice to find the start_id and any other users that are in range to the start_id. But we can through out the coefficient 2 so we get O(n), then we need to output the results, so we get O(p)



MISC. COMMENTS TO GRADER:
(optional, please be concise!)
