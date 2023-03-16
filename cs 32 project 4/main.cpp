#include "UserDatabase.h"
#include "User.h"
#include "Movie.h"
#include "MovieDatabase.h"
#include <iostream>
#include <string>
#include <chrono>
#include <cassert>
using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "/Users/supjames/Desktop/cs 32 project 4/cs 32 project 4/users.txt";
const string MOVIE_DATAFILE = "/Users/supjames/Desktop/cs 32 project 4/cs 32 project 4/movies.txt";

int main()
{
    
    auto start = chrono::steady_clock::now();
	UserDatabase udb;
    bool udb_bool = udb.load(USER_DATAFILE);
    auto stop = chrono::steady_clock::now();
    
	if (!udb_bool)  // if load returned false
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}
    else
    {
        cout << "User database loaded" << endl;
        cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
    }
    
    cout << endl;
    
    auto moviestart = chrono::steady_clock::now();
    MovieDatabase mdb;
    bool mdb_bool = mdb.load(MOVIE_DATAFILE);
    auto moviestop = chrono::steady_clock::now();
    if (!mdb_bool)  // if load returned false
    {
        cout << "Failed to load movie data file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }
    else
    {
        cout << "Movie database loaded" << endl;
        cout << "Took " << (chrono::duration_cast<chrono::milliseconds>(moviestop - moviestart).count()) << "ms" << endl;
    }
    
    
}

