#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define earthRadiusKm 6371.0
#ifndef M_PI
#define M_PI 3.14
#endif

// TODO: You must fill in all ?????? with the correct types.
typedef long int ID_TYPE;                     // Type for user IDs
typedef std::pair<double, double> COORD_TYPE; // Type for a coordinate (latitude
                                              // and longitude)
typedef std::map<ID_TYPE, std::vector<ID_TYPE>>
    ADJ_TYPE;                                   // Adjacency Lists type
typedef std::map<ID_TYPE, COORD_TYPE> GEO_TYPE; // Positional "dictionary"

// Function forward declarations. DO NOT CHANGE these.
double deg2rad(double deg);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void loadConnections(ADJ_TYPE &adj_lists, std::ifstream &loadfile);
void loadLocations(GEO_TYPE &locations, std::ifstream &loadfile);
void printAllUsersWithinDistance(const GEO_TYPE &locations,
                                 std::ofstream &outfile,
                                 const ID_TYPE &start_id, double max_distance);
void printDegreesHistogram(const ADJ_TYPE &adj_lists, std::ofstream &outfile);
void printDegreesOfAll(const ADJ_TYPE &adj_lists, std::ofstream &outfile);
void printFriendsWithDegree(const ADJ_TYPE &adj_lists, std::ofstream &outfile,
                            const ID_TYPE &start_id, unsigned int degree);
void printFriendsWithinDistance(const ADJ_TYPE &adj_lists,
                                const GEO_TYPE &locations,
                                std::ofstream &outfile, const ID_TYPE &start_id,
                                double max_distance);
void printUsersWithinIDRange(std::ofstream &outfile,
                             ADJ_TYPE::const_iterator begin,
                             ADJ_TYPE::const_iterator end,
                             ADJ_TYPE::const_iterator start_it,
                             unsigned int offset);

// DO NOT CHANGE THIS FUNCTION
int main(int argc, char **argv) {
  ADJ_TYPE adj_lists;
  GEO_TYPE locations;

  if (argc != 3) {
    std::cout << "Correct usage is " << argv[0]
              << " [commands file] [output file]" << std::endl;
    return -1;
  }

  std::ifstream commands(argv[1]);
  if (!commands) {
    std::cerr << "Problem opening " << argv[1] << " for reading!" << std::endl;
    return -1;
  }

  std::ofstream outfile(argv[2]);
  if (!outfile) {
    std::cerr << "Problem opening " << argv[2] << " for writing!" << std::endl;
    return -1;
  }

  std::string token; // Read the next command
  while (commands >> token) {
    if (token == "load-connections") {
      std::string filename;
      commands >> filename;

      std::ifstream loadfile(filename.c_str());
      if (!loadfile) {
        std::cerr << "Problem opening " << filename
                  << " for reading connections." << std::endl;
        return -1;
      }

      loadConnections(adj_lists, loadfile);
    } else if (token == "load-locations") {
      std::string filename;
      commands >> filename;

      std::ifstream loadfile(filename.c_str());
      if (!loadfile) {
        std::cerr << "Problem opening " << filename << " for reading locations."
                  << std::endl;
        return -1;
      }

      loadLocations(locations, loadfile);
    } else if (token == "print-degrees") {
      printDegreesOfAll(adj_lists, outfile);
    } else if (token == "print-degree-histogram") {
      printDegreesHistogram(adj_lists, outfile);
    } else if (token == "all-users-within-distance") {
      ID_TYPE start_id;
      double max_distance; // In kilometers
      commands >> start_id >> max_distance;

      printAllUsersWithinDistance(locations, outfile, start_id, max_distance);
    } else if (token == "friends-within-distance") {
      ID_TYPE start_id;
      double max_distance; // In kilometers
      commands >> start_id >> max_distance;

      printFriendsWithinDistance(adj_lists, locations, outfile, start_id,
                                 max_distance);
    } else if (token == "friends-with-degree") {
      ID_TYPE start_id, degree;
      commands >> start_id >> degree;

      printFriendsWithDegree(adj_lists, outfile, start_id, degree);
    } else if (token == "nodes-within-ID-range") {
      ID_TYPE start_id, offset;
      commands >> start_id >> offset;

      printUsersWithinIDRange(outfile, adj_lists.begin(), adj_lists.end(),
                              adj_lists.find(start_id), offset);
    } else {
      std::cerr << "Unknown token \"" << token << "\"" << std::endl;
      return -1;
    }
  }

  return 0;
}

// This function converts decimal degrees to radians
// From https://stackoverflow.com/a/10205532
// DO NOT CHANGE THIS FUNCTION
double deg2rad(double deg) { return (deg * M_PI / 180); }

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * Taken from https://stackoverflow.com/a/10205532
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 * DO NOT CHANGE THIS FUNCTION
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  return 2.0 * earthRadiusKm *
         asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

//////////////////TODO: IMPLEMENT ALL FUNCTIONS BELOW THIS
/// POINT////////////////////

/**
 * Loads a list of connections in the format "a b" meaning b is a friend of a
 * into the adjacency lists data structure. a and b are IDs.
 * @param adj_lists Adjacency lists structure
 * @param loadfile File to read from
 */
void loadConnections(ADJ_TYPE &adj_lists, std::ifstream &loadfile) {
  ID_TYPE id_a, id_b;
  // Using while loop to add each individual into the map, if the map has more
  // than one friends with him, use push back calls on vector to add multiple
  // friends
  while (loadfile >> id_a >> id_b) {
    adj_lists[id_a].push_back(id_b);
  }
}

/**
 * Loads a list of locations in the format "id latitude longitude"
 * @param locations Location lookup table
 * @param loadfile File to read from
 */
void loadLocations(GEO_TYPE &locations, std::ifstream &loadfile) {
  ID_TYPE id;
  double latitude, longitude;
  // Using while loop to add each individual with its location into the map
  while (loadfile >> id >> latitude >> longitude) {
    locations[id] = std::make_pair(latitude, longitude);
  }
}

/**
 * Prints all users within a certain distance of a particular user.
 * Sorted from shortest distance to user to longest distance to user.
 * Rounds down to the next lowest km if the difference is a decimal
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can be
 */
void printAllUsersWithinDistance(const GEO_TYPE &locations,
                                 std::ofstream &outfile,
                                 const ID_TYPE &start_id, double max_distance) {
  GEO_TYPE::const_iterator itr1 = locations.begin();
  double m_lat, m_long;
  // Using for loop to find a specific individual, record his/her location
  // is in the list
  for (; itr1 != locations.end(); itr1++) {
    if ((*itr1).first == start_id) {
      m_lat = (*itr1).second.first;
      m_long = (*itr1).second.second;
      break;
    }
  }
  // Didn't find this person, output this result.
  if (itr1 == locations.end()) {
    outfile << "User ID " << start_id << " does not have a recorded location."
            << std::endl;
    return;
  }
  std::map<int, std::vector<ID_TYPE>> count;
  // Using for loop to calculate all other people's distance away from a
  // specific user
  for (itr1 = locations.begin(); itr1 != locations.end(); itr1++) {
    if (start_id == (*itr1).first) {
      continue;
    }
    int curr_distance = (int)distanceEarth(m_lat, m_long, (*itr1).second.first,
                                           (*itr1).second.second);
    // If a person is close enough to a specific user, add him and the distance
    // between them into a map.
    if (curr_distance <= max_distance) {
      count[curr_distance].push_back((*itr1).first);
    }
  }
  // If nobody is close enough to a specific user, output this resutl.
  if (count.size() == 0) {
    outfile << "There are no users within " << max_distance << " km of user "
            << start_id << std::endl;
  } else {
    // If there is one or there are more than one users that are close enough,
    // output them in order.
    outfile << "User IDs within " << max_distance << " km of user " << start_id
            << ":" << std::endl;
    std::map<int, std::vector<ID_TYPE>>::const_iterator itr2 = count.begin();
    // Output by the order from closest distance to furthest distance from the
    // user.
    for (itr2 = count.begin(); itr2 != count.end(); itr2++) {
      outfile << " " << (*itr2).first << " km:";
      for (unsigned int i = 0; i < (*itr2).second.size(); i++) {
        outfile << " " << (*itr2).second[i];
      }
      outfile << std::endl;
    }
  }
}

/**
 * Prints a sorted list of degrees (smallest to largest) along with how many
 * users have that degree. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesHistogram(const ADJ_TYPE &adj_lists, std::ofstream &outfile) {
  // A map which key is number of friends, and value is how many people who
  // have that number of friends.
  std::map<int, int> count;
  ADJ_TYPE::const_iterator itr = adj_lists.begin();
  // Using for loop to find all individuals who have at least one friend,
  // categorize them by the number of friends they have.
  for (; itr != adj_lists.end(); itr++) {
    if ((*itr).second.size() == 0) {
      continue;
    }
    ++count[(*itr).second.size()];
  }
  std::map<int, int>::const_iterator itr2 = count.begin();
  // Output the results in the map using for loop
  outfile << "Histogram for " << adj_lists.size() << " users:" << std::endl;
  for (; itr2 != count.end(); itr2++) {
    outfile << " Degree " << (*itr2).first << ": " << (*itr2).second
            << std::endl;
  }
}

/**
 * Prints a sorted list of user IDs (smallest to largest) along with the
 * degree for each user. Only prints for degree >=1.
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 */
void printDegreesOfAll(const ADJ_TYPE &adj_lists, std::ofstream &outfile) {
  ADJ_TYPE::const_iterator itr = adj_lists.begin();
  // Using for loop to find all individual who have at least one friend, then
  // output in ID order.
  outfile << "Degrees for " << adj_lists.size() << " users:" << std::endl;
  for (; itr != adj_lists.end(); itr++) {
    if ((*itr).second.size() > 0) {
      outfile << " " << (*itr).first << ": Degree " << (*itr).second.size()
              << std::endl;
    }
  }
}

/**
 * Prints all friends of a particular user who have a particular degree.
 * Sorted by user ID (from smallest to largest).
 * @param adj_lists Adjacency lists structure
 * @param outfile File to write output to
 * @param start_id User whose friends we are looking at
 * @param degree The degree of friends we want to print. Will be >=1.
 */
void printFriendsWithDegree(const ADJ_TYPE &adj_lists, std::ofstream &outfile,
                            const ID_TYPE &start_id, unsigned int degree) {
  ADJ_TYPE::const_iterator itr1 = adj_lists.begin();
  ADJ_TYPE::const_iterator itr2 = itr1;
  std::vector<ID_TYPE> all_friends;
  std::map<ID_TYPE, int> match_degree;
  // Using for loop to find the user we need. Then add all his friends into a
  // vector for later use.
  for (; itr1 != adj_lists.end(); itr1++) {
    if ((*itr1).first == start_id) {
      for (unsigned int i = 0; i < (*itr1).second.size(); i++) {
        all_friends.push_back((*itr1).second[i]);
      }
      break;
    }
  }
  // If we didn't find this person, output the result.
  if (itr1 == adj_lists.end()) {
    outfile << "There is no user with friends and ID " << start_id << std::endl;
    return;
  }
  // using for loop to find if any friends of a specific user have the correct
  // number of friends. If he/she does, add to the map.
  for (unsigned int i = 0; i < all_friends.size(); i++) {
    for (; itr2 != adj_lists.end(); itr2++) {
      if ((*itr2).first == all_friends[i]) {
        if ((*itr2).second.size() == degree) {
          match_degree[all_friends[i]] = degree;
        }
      }
    }
    itr2 = adj_lists.begin();
  }
  // If no user matches the requirement, output the result.
  if (match_degree.size() == 0) {
    outfile << "User " << start_id << " has 0 friend(s) with degree " << degree
            << std::endl;
  } else {
    // If there is one or more than one users match degrees, output the results.
    outfile << "User " << start_id << " has " << match_degree.size()
            << " friend(s) with degree " << degree << ":";
    std::map<ID_TYPE, int>::const_iterator itr3 = match_degree.begin();
    for (; itr3 != match_degree.end(); itr3++) {
      outfile << " " << (*itr3).first;
    }
    outfile << std::endl;
  }
}

/**
 * Prints friends of a particular user within a certain distance of that user.
 * Sorted from shortest distance to user to longest distance to user.
 * @param adj_lists Adjacency lists structure
 * @param locations Location lookup table
 * @param outfile File to write output to
 * @param start_id User we are using as our "origin" (i.e. 0 distance)
 * @param max_distance Maximum distance from start_id that a printed user can
 * be
 */
void printFriendsWithinDistance(const ADJ_TYPE &adj_lists,
                                const GEO_TYPE &locations,
                                std::ofstream &outfile, const ID_TYPE &start_id,
                                double max_distance) {
  GEO_TYPE::const_iterator itr1 = locations.begin();
  ADJ_TYPE::const_iterator itr2 = adj_lists.begin();
  // First check if it is a valid ID
  for (; itr2 != adj_lists.end(); itr2++) {
    if ((*itr2).first == start_id) {
      break;
    }
  }
  // Invalid ID, output results.
  if (itr2 == adj_lists.end()) {
    outfile << "There is no user with friends and ID " << start_id << std::endl;
    return;
  }
  // Find this person's location and record the number for later calculation
  double m_lat, m_long;
  for (; itr1 != locations.end(); itr1++) {
    if ((*itr1).first == start_id) {
      m_lat = (*itr1).second.first;
      m_long = (*itr1).second.second;
      break;
    }
  }
  // If this user's location is not found, output the results.
  if (itr1 == locations.end()) {
    outfile << "User ID " << start_id << " does not have a recorded location."
            << std::endl;
    return;
  }
  std::map<double, std::vector<ID_TYPE>> distance;
  std::vector<ID_TYPE> all_friends;
  // Using for loop to finds all a specific user's friends, add them into a
  // vector.
  for (itr2 = adj_lists.begin(); itr2 != adj_lists.end(); itr2++) {
    if ((*itr2).first == start_id) {
      for (unsigned int i = 0; i < (*itr2).second.size(); i++) {
        all_friends.push_back((*itr2).second[i]);
      }
      break;
    }
  }
  // Using for loop to calculate distance between a specific user and his
  // friends, if distance is in the range, add them into a map with its distance
  // and ID
  for (unsigned int i = 0; i < all_friends.size(); i++) {
    for (itr1 = locations.begin(); itr1 != locations.end(); itr1++) {
      if ((*itr1).first == all_friends[i]) {
        double curr_lat = (*itr1).second.first;
        double curr_long = (*itr1).second.second;
        double curr_distance =
            distanceEarth(m_lat, m_long, curr_lat, curr_long);
        if (curr_distance <= max_distance) {
          distance[curr_distance].push_back(all_friends[i]);
        }
        break;
      }
    }
  }
  // Case1: no friends is close enough
  if (distance.size() == 0) {
    outfile << "There are no friends within " << max_distance << " km of user "
            << start_id << std::endl;
    return;
  } else {
    // Case2: one or more than one friends distance is within the range
    outfile << "Friends within " << max_distance << " km of user " << start_id
            << ":" << std::endl;
    // Output them in order of closest distance to furthest distance
    for (std::map<double, std::vector<ID_TYPE>>::const_iterator itr2 =
             distance.begin();
         itr2 != distance.end(); itr2++) {
      outfile << " " << (*itr2).first << " km:";
      for (unsigned int i = 0; i < (*itr2).second.size(); i++) {
        outfile << " " << (*itr2).second[i];
      }
      outfile << std::endl;
    }
  }
}

/**
 * Prints users with an ID that is "close" to a particular user's ID.
 * Sorted from smallest to largest user ID.
 * Only prints for degree >=1.
 *
 * If there are M IDs that should be printed this function should only use
 * ADJ_TYPE::const_iterator::operator++ / ADJ_TYPE::const_iterator::operator--
 * O(M) times
 *
 * @param outfile File to write output to
 * @param begin The .begin() iterator for the adjacency lists structure
 * @param end The .end() iterator for the adjacency lists structure
 * @param start_it Iterator for user we are using as our baseline (i.e. 0
 * diifference) It is possible that the start_it was not found in the data.
 * @param offset Maximum absolute difference from start_id that a printed
 * user's ID can have
 */
void printUsersWithinIDRange(std::ofstream &outfile,
                             ADJ_TYPE::const_iterator begin,
                             ADJ_TYPE::const_iterator end,
                             ADJ_TYPE::const_iterator start_it,
                             unsigned int offset) {
  std::vector<ID_TYPE> match_id;
  ADJ_TYPE::const_iterator itr = begin;
  // First to check if it is an valid id in the map
  for (; itr != end; itr++) {
    if ((*itr).first == (*start_it).first) {
      break;
    }
  }
  // If not, output the results.
  if (itr == end) {
    outfile << "There is no user with the requested ID" << std::endl;
    return;
  }
  // Using for loop to find all individuals within the range, add them into a
  // vector
  for (; begin != end && (*begin).first <= (*start_it).first + offset;
       begin++) {
    if ((*begin).first >= (*start_it).first - offset &&
        (*begin).first <= (*start_it).first + offset) {
      if ((*begin).first != (*start_it).first) {
        match_id.push_back((*begin).first);
      }
    }
  }
  // Case1: nobody is in the range
  if (match_id.size() == 0) {
    outfile << "There are no users with an ID within +/-" << offset << " of "
            << (*start_it).first << std::endl;
  } else {
    // Case2: one or more than one users in the range
    outfile << "Users with an ID within +/-" << offset << " of "
            << (*start_it).first << ":";
    for (unsigned int i = 0; i < match_id.size(); i++) {
      outfile << " " << match_id[i];
    }
    outfile << std::endl;
  }
}
