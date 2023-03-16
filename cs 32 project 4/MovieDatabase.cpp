#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

MovieDatabase::MovieDatabase()
{
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    string temp;
    while(getline(infile, temp)) // get first line (the ID of the movie)
    {
        string id = temp;
        
        string name;
        if (!getline(infile, name)) return false; // get the name of the movie
        
        string release_year;
        if (!getline(infile, release_year)) return false; // get the release year of the movie
        
       
        string single;
        
        
        vector<string> seperatecommasDirectors; // get all of the directors in the next line
        if (!getline(infile, single)) return false; // get the entire line into a string called single
        stringstream dd(single); // put the whole line into a stringstream
        while (getline(dd, single, ',')) // seperate by commas
        {
            // here we have the indiviudal directors names
            seperatecommasDirectors.push_back(single);
        }

    
        vector<string> seperatecommasActors; // get all of the actors in the next line
        if (!getline(infile, single)) return false; // get the entire line into a string called single
        stringstream aa(single); // put the whole line into a stringstream
        while (getline(aa, single, ',')) // seperate by commas
        {
            seperatecommasActors.push_back(single);
        }
        
        
        vector<string> seperatecommasGenres; // get all of the genres in the next line
        if (!getline(infile, single)) return false; // get the entire line into single
        stringstream gg(single); // put the whole line into a stringstream variable
        while (getline(gg, single, ',')) // seperate by commas
        {
            seperatecommasGenres.push_back(single);
        }
        
        string rating;
        if (!getline(infile, rating)) return false; // get the rating as a string
        float num_rating = stof(rating); // convert it to a float
        
        
        // create a new instance of the Movie
        Movie* tempMovie = new Movie(id, name, release_year, seperatecommasDirectors, seperatecommasActors, seperatecommasGenres, num_rating);
        int i = 0;
        
        // associate each movie with its ID
        m_map_idToMovie.insert(id, tempMovie);
        
        // associate the movie with its key per each type of TreeMultimap we have in moviedatabase
        for(i = 0; i < seperatecommasDirectors.size(); i++)
        {
            m_map_directorToMovie.insert(seperatecommasDirectors[i], tempMovie); // associate the movie with its directors
        }
        
        for(i = 0; i < seperatecommasActors.size(); i++)
        {
            m_map_actorToMovie.insert(seperatecommasActors[i], tempMovie); // associate the movie with its actors
        }
        
        for(i = 0; i < seperatecommasGenres.size(); i++)
        {
            m_map_genreToMovie.insert(seperatecommasGenres[i], tempMovie); // associate the movie with its genres
        }
        
        // skip the new line
        getline(infile, temp);
    }
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<string, Movie*>::Iterator itr = m_map_idToMovie.find(id);
    
    // only one movie per ID
    
    if (itr.is_valid()) // if the iterator is valid
    {
        Movie* temp = itr.get_value();
        return temp;
    }
    else return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    
    TreeMultimap<string, Movie*>::Iterator itr = m_map_directorToMovie.find(director);
    
    // could be multiple movies per iterator so need to iterate through and get each movie into a vector
    vector<Movie*> temp;
    while(itr.is_valid())
    {
        temp.push_back(itr.get_value());
        itr.advance();
    }
    
    return temp;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    TreeMultimap<string, Movie*>::Iterator itr = m_map_actorToMovie.find(actor);
    
    // could be multiple movies per iterator so need to iterate through and get each movie into a vector
    vector<Movie*> temp;
    while(itr.is_valid())
    {
        temp.push_back(itr.get_value());
        itr.advance();
    }
    
    return temp;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    TreeMultimap<string, Movie*>::Iterator itr = m_map_genreToMovie.find(genre);
    
    // could be multiple movies per iterator so need to iterate through and get each movie into a vector
    vector<Movie*> temp;
    while(itr.is_valid())
    {
        temp.push_back(itr.get_value());
        itr.advance();
    }
    
    return temp;
}
