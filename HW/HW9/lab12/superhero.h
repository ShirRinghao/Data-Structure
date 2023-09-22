#ifndef _SUPERHERO_H_
#define _SUPERHERO_H_

#include <iostream>
#include <fstream>
#include <string>

class Superhero{
public:
	Superhero(std::string _name, std::string _true_identity, std::string _power){
		name = _name;
		true_identity = _true_identity;
		power = _power;
		is_hero = true;
	}

	std::string getName() const {
		return name;
	}
	std::string getPower() const{
		return power;
	}
	std::string getTrueIdentity() const{
		return true_identity;
	}

	bool isGood() const {return is_hero;}

	bool operator==(const std::string& identity){
		return true_identity ==identity;
	}

	bool operator!=(const std::string& identity){
		return true_identity != identity;
	}

	bool operator==(const Superhero& h){
		if(name == h.getName() || true_identity == h.getTrueIdentity() ||
		   power == h.getPower() || is_hero == h.isGood())
			return true;
		return false;
	}

	void operator-(){
		is_hero = !is_hero;
	}

	bool operator>(Superhero right){
		if(power == "Fire" && right.power == "Wood") return true;
		if(power == "Water" && right.power == "Fire") return true;
		if(power == "Wood" && right.power == "Water") return true;
		return false;
	}

private:
	std::string name;
	std::string true_identity;
	std::string power;
	bool is_hero;
};
std::ostream& operator<<(std::ostream& ostr, Superhero& hero){
	if(hero.isGood()){
		ostr << "Superhero ";
	}else{
		ostr << "Supervillain ";
	}
	ostr << hero.getName() << " has power " << hero.getPower() <<std::endl;
	return ostr;
}

#endif
