#include <cassert>
#include <iostream>
#include <set>
#include <string>

// simple homemade smart pointers
#include "ds_smart_pointers.h"

// ====================================================
// BALLOON: a toy class with dynamically allocated memory
// ====================================================

#define MAX_NUM_ROPES 10

class Balloon {
public:
  // CONSTRUCTOR & DESTRUCTOR
  Balloon(const std::string &name_) : name(name_) {
    std::cout << "Balloon constructor " << name << std::endl;
    num_ropes = 0;
    ropes = new Balloon *[MAX_NUM_ROPES];
  }
  ~Balloon() {
    std::cout << "Balloon destructor " << name << std::endl;
    // don't try to destroy attached balloons, just delete array
    delete[] ropes;
  }

  // ACCESSORS
  const std::string &getName() const { return name; }
  int numRopes() const { return num_ropes; }
  Balloon *getRope(int i) const { return ropes[i]; }

  // print the balloons we are attached to
  void print() {
    std::cout << "Balloon " << name << " is connected to: ";
    for (int i = 0; i < num_ropes; i++) {
      std::cout << ropes[i]->name << " ";
    }
    if (num_ropes == 0)
      std::cout << "nothing";
    std::cout << std::endl;
  }
  // add a rope connecting this balloon to another
  void addRope(Balloon *b) {
    assert(num_ropes < MAX_NUM_ROPES);
    ropes[num_ropes] = b;
    num_ropes++;
  }
  // detach a rope connecting this balloon to another
  void removeRope(Balloon *b) {
    for (int i = 0; i < MAX_NUM_ROPES; i++) {
      if (ropes[i] == b) {
        ropes[i] = ropes[num_ropes - 1];
        num_ropes--;
        break;
      }
    }
  }

private:
  std::string name;
  int num_ropes;
  // a dynamically allocated C-style array of ropes connecting to other Balloons
  Balloon **ropes;
};

void get_balloons(Balloon *b, std::set<Balloon *> &balloons) {
  for (unsigned int i = 0; i < b->numRopes(); i++) {
    if (balloons.insert(b->getRope(i)).second)
      get_balloons(b->getRope(i), balloons);
  }
}

void deleteAll(Balloon *b) {
  std::set<Balloon *> balloons;
  balloons.insert(b);
  get_balloons(b, balloons);
  for (std::set<Balloon *>::iterator itr = balloons.begin();
       itr != balloons.end(); ++itr) {
    delete *itr;
  }
}

// ====================================================
// ====================================================

int main() {

  std::cout << "start of main" << std::endl;

  // ====================================================
  // CYCLIC STRUCTURES
  // ====================================================

  // FOR CHECKPOINT 3

  Balloon *jacob(new Balloon("Dora the Explorer"));
  Balloon *katherine(new Balloon("Kung Fu Panda"));
  Balloon *larry(new Balloon("Scooby Doo"));
  Balloon *miranda(new Balloon("SpongeBob SquarePants"));
  Balloon *nicole(new Balloon("Papa Smurf"));

  jacob->addRope(katherine);
  katherine->addRope(larry);
  larry->addRope(jacob);
  miranda->addRope(jacob);
  nicole->addRope(miranda);
  larry->addRope(nicole);

  katherine = NULL;
  larry = NULL;
  miranda = NULL;
  nicole = NULL;

  // jacob points to a cyclic structure!

  // to cleanup this structure:
  deleteAll(jacob);

  jacob = NULL;

  std::cout << "end of main" << std::endl;
  return 0;

  //
  // NOTE: when smart pointers go out of scope, the destructors for
  //       those objects will be called automatically
  //
}

// ====================================================
