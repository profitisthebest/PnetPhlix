#include "UserDatabase.h"
#include "User.h"
#include "treemm.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

UserDatabase::UserDatabase()
{
    // Replace this line with correct code.
}

bool UserDatabase::load(const string &filename) // must specify the complete path
{

    ifstream infile(filename);
    string temp;
    if (!infile)
        return false;

    while (getline(infile, temp)) // get the name (first line)
    {
        string name = temp;
        string email;
        // get the email and f its already in the bst as a key
        if (!getline(infile, email))
            return false;
        if (m_map.find(email) != m_map.end())
            return false; // **** CHANGE THIS TO .SEARCH and NULLPTR later when finished treemm.h

        // get number of movies watched and convert into int
        string movieNumString;
        if (!getline(infile, movieNumString))
            return false;
        int movieNum = stoi(movieNumString);

        vector<string> movies_watched;
        // get the all of the movies into a vector
        for (int i = 0; i < movieNum; i++)
        {
            string movieID;
            if (!getline(infile, movieID))
                return false;                  // get the movieID
            movies_watched.push_back(movieID); // add the movieID to the vector of movies watched
        }

        // construct a new person and add to tree
        User *tempUser = new User(name, email, movies_watched);
        m_map.insert({email, tempUser}); // CHANGE THIS LATER

        // skip the new line
        getline(infile, temp);
    }

    return true;
}

User *UserDatabase::get_user_from_email(const string &email) const
{
    User *tempUser = nullptr;

    map<string, User *>::const_iterator itr = m_map.find(email);
    if (itr != m_map.end())
    {
        User *tempUser = itr->second; // gives the User pointer
    }

    return tempUser; // return nullptr if the email doesn't map to anything
}
