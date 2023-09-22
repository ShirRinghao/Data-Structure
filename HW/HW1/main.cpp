#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//Fucntion that completes dilation.
//Three parameters: a vector of all infomation, a copy of such vector for editing
//		and output (pass in by reference), and a char letter to replace adjacent
//		spots when dilation is satisfied.
//Function uses two for loops to check all spots in a string vector whether a spot
//		satisfies dilation and such spot is inside the picture or not.
void dilation(std::vector<std::string> allinfo,
              std::vector<std::string> &output, char replace[]) {
  for (int i = 0; i < (int)allinfo.size(); i++) {
    for (int j = 0; j < (int)allinfo[i].size(); j++) {
      if (allinfo[i][j] == replace[0]) {
        if (i - 1 >= 0)
          output[i - 1][j] = replace[0];
        if (i + 1 < (int)output.size())
          output[i + 1][j] = replace[0];
        if (j - 1 >= 0)
          output[i][j - 1] = replace[0];
        if (j + 1 < (int)output[i].size())
          output[i][j + 1] = replace[0];
      }
    }
  }
}

//Fucntion that completes dilation.
//Three parameters: a vector of all infomation, a copy of such vector for editing
//		and output (pass in by reference), and a char letter to replace a specific
//		spot when erosion is satisfied at such spot.
//Function uses two for loops to check all spots in a string vector whether a spot
//		satisfies erosion and such spot is inside the picture or not.
void erosion(std::vector<std::string> allinfo, std::vector<std::string> &output,
             char original[], char replace[]) {
  for (int i = 0; i < (int)allinfo.size(); i++) {
    for (int j = 0; j < (int)allinfo[i].size(); j++) {
      if (allinfo[i][j] == original[0]) {
        if (i - 1 >= 0 && allinfo[i - 1][j] == replace[0]) {
          output[i][j] = replace[0];
          continue;
        }
        if (i + 1 < (int)allinfo.size() && allinfo[i + 1][j] == replace[0]) {
          output[i][j] = replace[0];
          continue;
        }
        if (j - 1 >= 0 && allinfo[i][j - 1] == replace[0]) {
          output[i][j] = replace[0];
          continue;
        }
        if (j + 1 < (int)allinfo[i].size() && allinfo[i][j + 1] == replace[0]) {
          output[i][j] = replace[0];
          continue;
        }
      }
    }
  }
}

//Fucntion that completes dilation.
//Three parameters: a vector of all infomation, a copy of such vector for editing
//		and output (pass in by reference), and a char letter to replace a specific
//		spot when replacement is satisfied at such spot.
//Function uses two for loops to check all spots in a string vector whether a spot
//		satisfies replacement or not.
void replace(std::vector<std::string> allinfo, std::vector<std::string> &output,
             char original[], char replace[]) {
  for (unsigned int i = 0; i < allinfo.size(); i++) {
    for (unsigned int j = 0; j < allinfo[i].size(); j++) {
      if (allinfo[i][j] == original[0])
        output[i][j] = replace[0];
    }
  }
}

int main(int argc, char *argv[]) {
  //Function reads input file, store all information line by line into a string
  //		vector. If the input file cannot be opened, display error message.
  std::vector<std::string> allinfo;
  std::ifstream infile(argv[1]);
  if (!infile) {
    std::cerr << "File cannot be opened" << std::endl;
    exit(1);
  }
  while (infile) {
    std::string curr;
    infile >> curr;
    if (curr == "")
      break;
    allinfo.push_back(curr);
  }
  //create a copy of original string vector for editing and future output.
  std::vector<std::string> output(allinfo);
  //Function takes different commands, it will run differently according to
  //		different conditions.
  if (std::string(argv[3]) == "dilation") {
    dilation(allinfo, output, argv[4]);
  }
  else if (std::string(argv[3]) == "replace") {
    replace(allinfo, output, argv[4], argv[5]);
  }
  else if (std::string(argv[3]) == "erosion") {
    erosion(allinfo, output, argv[4], argv[5]);
  }
  else if (std::string(argv[3]) == "closing") {
    dilation(allinfo, output, argv[4]);
	//Store the result of dilation function into a temporay vector.
    const std::vector<std::string> temp_vector(output);
	//Passing in temporay vector into next function that will be runned.
    erosion(temp_vector, output, argv[4], argv[5]);
  }
  else if (std::string(argv[3]) == "opening") {
    erosion(allinfo, output, argv[4], argv[5]);
	//Store the result of erosion function into a temporay vector.
    const std::vector<std::string> temp_vector(output);
	//Passing in temporay vector into next function that will be runned.
    dilation(temp_vector, output, argv[4]);
  }
  else{
	  std::cerr << "Unknown command" << std::endl;
  }
  std::ofstream outfile(argv[2]);
  //After every single spot has been checked, write all information that will be
  //		outputed into requested file as it has been mentioned in command line.
  if (!outfile.good()) {
    std::cerr << "Can't open " << argv[2] << " to write.\n";
    exit(1);
  }
  for (unsigned int i = 0; i < output.size(); i++) {
    outfile << output[i] << std::endl;
  }
  return 0;
}
