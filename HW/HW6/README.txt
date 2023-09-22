HOMEWORK 6: CROSSWORD BLACKOUT


NAME:  < Linghao Shi >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Yifei Li, Xiaoyu Zhang / stackoverflow.com >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert #30 hours >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h)
The number of words in the dictionary (d)?
The total number of spaces with a letter (l)?
The total number of blacked out spaces (b)?
The number of constraints (c)?
Etc.
In my case, The number of constraints (c) controls the running time mostly.
My method is to find all possible solutions first. So if the dictionary initally has a huge amount of words, it will take a long time since it is a recursive function. Basically, recursive function has a for loop to go through every single words in the vector of string that stores all possible words. Every time I add a word, call recursion to check next word if it makes current solution valid or not. Otherwise use continue to go to next word in the loop.(it is faster this way because it won't call another recursion, but go to next possibly valid word instead). Even though I have tried to improve its speed by delete all words that will not possible occur on the grid, some puzzles are still really costly because it still has a huge possible words vector. I would say the order notation for this is O(c^d) if function runs without optimizatoin functions. My check function is also kind of costly, but compare with recursive function, it runs a lot faster. O(w*h) because it has to check every single location.

DESCRIPTION OF YOUR ADDTIONAL PUZZLES/DICTIONARIES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).
There are few special cases that should be considered:
1. two words are connected without a '#' in between (not a valid solution)
2. words length exceeds the size of the grid
3. not enough words to fulfill the requirement. For exmaple, if we need three words of length 3, we only have 2 possible words of length 3 could occur on the grid, then there is 0 solution.
4. a correct word occur in multiple location, each forms a unqiue solution

SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND
ON YOUR ADDITIONAL PUZZLES/DICTIONARIES:
# of solutions & approximate wall clock running time for different
puzzles / dictionaries for a single solution or all solutions. Be
specific about which puzzle/dictionary/parameters you were timing.

Given puzzles have contained most of the conditions. There is no other speical cases I could think of.
My puzzle is just s basic test for two connected words (it makes this specific solution invalid)
0 solution for first puzzle. My puzzle stops right away when it founds out it is not a valid solution
1 solution for second solution. 
My code could solve the second solution since a word could be in two different locations, but it should only has one solution
It will take less than a second to run since they are small puzzles and files. 
My function checks if there are two words are connected without a '#' in between (such solution will be deleted right away if found)
If the word length exceeds grid size, this word would even be added into possible words vector.
If there is not enough words to fulfill the requirement, recursive function should be ended instead of search every single word until the end of the possible word vector

Running time might be different on different cpu.
My cpu: i7-8700k
Most of the puzzles need around 1 second. 
Sporcle_dict3.txt constraintsA.txt takes around 5 seconds to get the solution which is acceptable.
The only two puzzles would take very long time is sprocle1_dict2.txt and sprocle1_dict4.txt on constraintsA.txt because they have a lot possible words, recursive function will be called many times and there are too many possible solutions.(it takes more than an hour for sporcle_dict2.txt)

case 4 described above, I couldn't solve it myself but I have written a test case for it.

MISC. COMMENTS TO GRADER:
(optional, please be concise!)
