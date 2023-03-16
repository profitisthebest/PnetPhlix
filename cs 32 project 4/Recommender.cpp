#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    m_user_database = const_cast<UserDatabase*>(& user_database);
    m_movie_database = const_cast<MovieDatabase*>(& movie_database);
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    // get the user using their email
    User* thisUser = m_user_database->get_user_from_email(user_email);
    
    // get all of the movies that the user has watched
    vector<string> movies_watched_ids = thisUser->get_watch_history(); // get the IDs of the movies
    
    vector<Movie*> movies_watched; // get the actual movie object for each ID we have and push onto movies_watched vector
    for (int i = 0; i < movies_watched_ids.size(); i++)
    {
        Movie* temp = m_movie_database->get_movie_from_id(movies_watched_ids[i]);
        movies_watched.push_back(temp);
    }
    // the vector movies_watched is now filled with movie object that the user has watched before
    
    
    // unordered set to keep track of the compatibility score of movies
    // ID -> compatibility_score
    unordered_map<string, int> compatibility_map;
    
    // for each movie that the user has watched
    for (int i = 0; i < movies_watched.size(); i++)
    {
        // go through the directors of the movie
        vector<string> movie_directors = movies_watched[i]->get_directors(); // get the directors
        for (int j = 0; j < movie_directors.size(); j++) // for every director of the movie
        {
            // find all movies with that director
            vector<Movie*> movies_with_director = m_movie_database->get_movies_with_actor(movie_directors[j]);
            
            // add 20 points to their compatibility score and insert into the unordered map
            for (int k = 0; k < movies_with_director.size(); k++)
            {
                compatibility_map[movies_with_director[k]->get_id()] += 20;
            }
        }
        
        // go through the actors of the movie
        vector<string> movie_actors = movies_watched[i]->get_actors(); // get the actors
        for (int j = 0; j < movie_actors.size(); j++) // for every actor of the movie
        {
            // find all movies with that actor
            vector<Movie*> movies_with_actor = m_movie_database->get_movies_with_actor(movie_actors[j]);
            
            // add 30 points to their compatibility score and insert into the unordered map if not already in
            for (int k = 0; k < movies_with_actor.size(); k++)
            {
                compatibility_map[movies_with_actor[k]->get_id()] += 30;
            }
        }
        
        // go through the genres of the movie
        vector<string> movie_genres = movies_watched[i]->get_genres(); // get the genres
        for (int j = 0; j < movie_genres.size(); j++) // for each genre of the movie
        {
            
            // find all movies with that genre
            vector<Movie*> movies_with_genre = m_movie_database->get_movies_with_genre(movie_genres[j]);
            
            // add 1 point to their compatibility score and insert into the unordered map if not already in
            for (int k = 0; k < movies_with_genre.size(); k++)
            {
                compatibility_map[movies_with_genre[k]->get_id()] += 1;
            }
        }
    }
    
    // filter out the movies that we have already watched
    for (auto i : compatibility_map)
    {
        if (find(movies_watched_ids.begin(), movies_watched_ids.end(), i.first) != movies_watched_ids.end()) // if the ID of the movie in the compatibility map IS in the IDs of movies watched
        {
            // we want to remove the id-score pair from the unordered_map
            // compatibility_map.erase(i);
        }
    }
        
        
        
        
        
        
    return vector<MovieAndRank>();  // Replace this line with correct code.
}
