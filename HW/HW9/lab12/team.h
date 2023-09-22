#ifndef _TEAM_H_
#define _TEAM_H_

#include <string>
#include <iostream>
#include <list>

#include "superhero.h"

class Team {

public:
  Team(){};
  Team operator=(const Team& new_team){return new_team;}

  // accessor function
  std::string getName() const;

  // adding and removing a single superhero
  void operator+=(const Superhero &a);
  void operator-=(Superhero a);

  //Team operator+(const Team& a);
  //Team operator+(const Superhero& h);
  // adding two teams together or a team and a superhero together
  // makes a team.  these functions must be member functions to allow
  // access to the list of superheroes.
  friend Team operator+(const Team &a, const Team &b);
  friend Team operator+(const Team &a, const Superhero &b);

private:
  // REPRESENATION
  std::list<Superhero> superheroes;
};





bool isvowel(char c) {
  if (!isalpha(c)) return false;
  char c2 = tolower(c);
  return (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u');
}

bool isconsonant(char c) {
  return (isalpha(c) && !isvowel(c));
}

std::string Team::getName() const {
  if (superheroes.size() == 0)
    return "";
  std::string answer;
  std::list<Superhero>::const_iterator itr;
  for (itr = superheroes.begin(); itr != superheroes.end(); itr++) {
    char first_consonant = ' ';
    char first_vowel = ' ';
    std::string true_identity = itr->getTrueIdentity();
    for (int j = 0; j < true_identity.size(); j++) {
      if (first_consonant == ' ' && isconsonant(true_identity[j]))
        first_consonant = tolower(true_identity[j]);
      if (first_vowel == ' ' && isvowel(true_identity[j]))
        first_vowel = tolower(true_identity[j]);
    }
    answer.push_back(first_consonant);
    answer.push_back(first_vowel);
  }

  answer[0] = toupper(answer[0]);
  return answer;
}


void Team::operator+=(const Superhero &a){
  superheroes.push_back(a);
}
void Team::operator-=(Superhero a){
  std::list<Superhero>::iterator itr;
  for(itr = superheroes.begin();itr != superheroes.end(); itr++){
    if((*itr) == a){
      superheroes.erase(itr);
      break;
    }
  }
}

Team operator+(const Superhero &a, const Superhero &b){
  Team new_team;
  new_team += a;
  new_team += b;
  return new_team;
}

Team operator+(const Team &a, const Team &b){
  Team new_team = a;
  for(std::list<Superhero>::const_iterator itr = b.superheroes.begin();
      itr != b.superheroes.end();++itr){
    new_team += *itr;
  }
  return new_team;
}

Team operator+(const Team &a, const Superhero &b){
  Team new_team = a;
  new_team+=b;
  return new_team;
}

#endif
