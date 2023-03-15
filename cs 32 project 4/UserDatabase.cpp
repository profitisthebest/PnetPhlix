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
        m_map.insert(email, tempUser); // key = email, value = user

        // skip the new line
        getline(infile, temp);
    }

    return true;
}

User *UserDatabase::get_user_from_email(const string &email) const
{
    TreeMultimap<string, User *>::Iterator itr = m_map.find(email);
    
    // there should only be one user per email so we just dereference the iterator right away to get the user pointer
    
    if (itr.is_valid()) // if the iterator is valid
    {
        User* temp = itr.get_value();
        return temp;
    }
    else return nullptr;
}
