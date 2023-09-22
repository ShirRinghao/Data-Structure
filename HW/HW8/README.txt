HOMEWORK 8: ROPES


NAME:  < Linghao Shi >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Xiaoyu Zhang, Yifei Li / stackoverflow.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  <# 25 hours >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each
of the following operations two ways: 1) with a balanced Rope, 2) with an
extremely unbalanced Rope. Explain what you considered an extremely
unbalanced rope for the string "Hello my name is Simon".

assume N is the number of the nodes in the rope

Copy Constructor: O(N)
since we have to go through every single nodes to copy

Construct from Node*:
assume M nodes in the rope after Node*
worst and average case is O(M) since in my function, it has to copy every single nodes after Node*

Index:
worst case and average case: O(P)
Both have to go through an entire path from root to leaf to find the characters

Report:
worst case O(N): string size is the size of the rope, which means we have to go through every single nodes to get all characters
average case O(P): Going through the longest path to find a word

iterator operator++:
worst case: O(P) have to go from the root to a left most leaf on the right hand side of the root
O(1): simply go to the next rode on the right hand side

Split:
average and worst case: O(P) reduced from O(2P)
worst case: it takes O(P) to go to an leaf, then if we have to split every single node from the leaf to root, then total running time is O(2P) and will be reduced to O(P)
since we have to use the same method as index to find the first charater, which is O(P). Any other nodes that needed to be split won't take a lot extra time, so it is O(P) for split

Concat:
assume M nodes in the rope after Node* we want to make a copy
average case and worst case: O(M) or O(P) same as construct from Node*, we have to copy every single nodes on the right subtree and update all weights by going all the way to the right subtree

TESTING & DEBUGGING STRATEGY:
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?

These are the special cases I could think of:
Split: sometimes we have to split more than two branches, or split at the beginning or at the end of a rope
Report and Index: searching an index out of bound, or the string or char we pass in already has value in it
Copy constructor and assignment operator: need to copy or assign an empty rope

For above special cases, the program shouldn't crash. I have created rope to test them to see after running those special cases, if they can output the correct value. If my code couldn't complete any of these tests, that means I didn't cover all the corner cases, and these tests have been commented out

MISC. COMMENTS TO GRADER:
(optional, please be concise!)
