HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Linghao Shi >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Luoyan Zhangm, Yifei Li / www.stackoverflow.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < #15 hours>



TESTING & DEBUGGING STRATEGY:
Testing:
I have written test cases for those special conditions:
Deleting last element in the list using pop_front.
Deleting last element in the list using pop_back.
Insert into an empty list and  erase last few elements in the list.
Erase all elements in the first node, first node will be deleted.
Erase all elements in the last node, last node will be deleted.
Serval inserts to test whether it will overflow successfully, insert correctly into first position and last position in the list.
and a test for copy constructor.

Debugging:
sometimes it shows as segmentation fault and no data could be outputed using backtrace. I have to set a break point, using step, and next to go through the program and prints out values of different variable until they go wrong.
I have seem inaccessible memory location many times when I connect two nodes incorrectly, the program cannot access to the correct memory location.
GDB has helped me a lot in this assginment.


ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case?

Basically UnrolledLL has two pointers, one connnects the tail and the other connects the head. It is easier to find the last position in the list, comparing with stl list, you have to use a loop to find the last element in the list. Moreover, UnrolledLL is doubly linked, which means every single node will a pointer points to the previous node and a pointer points to the next node. It is more convenient to search in the UnrolledLL than stl list, however, it take a bit work to implement it. Even though UnrolledLL is similiar with dslist (they are both doubly linked list) , UnrolledLL has an array to store more information in every node, it should be more useful than dslist.

size(): O(1);
empty(): O(1);
clear(): O(n);
push_front(): O(1);
push_back(): O(1);
pop_front(): O(1);
pop_back(): O(1);
begin(): O(1);
end(): O(1);
insert(): O(1);
erase(): O(1);
copy_list(): O(n);
destroy_list(): O(n);
front(): O(1);
back(): O(1);
print(): O(n);
operator=: O(n);
operator==: O(n);
operator!=(): O(n);

Worst case:
while we are calling function, the worst case should be all nodes in the list all have only one element left in the node. At this time, there will be lots of node classes store all the heap. If we could combine all elements fit into one node, it could save a lot of memory spaces.
When we are calling erase, pop back or pop front function, we could get to 1 1 1 condition by erasing all the elements in the node but one left.
When we are calling insert, push back or push front function, if a node is full, then we have to create a new node to store that individual element, which waste some space.

EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:
Optional, please be concise!
