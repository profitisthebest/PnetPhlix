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

// returns true if movie A should go before movie B
bool Recommender::customCompare(const MovieAndRankHelper &MovieA, const MovieAndRankHelper &MovieB)
{
    // if Movie A has a higher score than Movie B then Movie A comes before Movie B
    if (MovieA.movie_score > MovieB.movie_score)
    {
        return true;
    }
    else if (MovieA.movie_score < MovieB.movie_score)
    { // if Movie A has a lower score than Movie B then Movie A SHOULD NOT come before Movie B
        return false;
    }
    else // if we get here then the scores are equal:
    {
        if (MovieA.movie_rating > MovieB.movie_rating)
        { // if Movie A has a higher rating than Movie B then Movie A comes before Movie B
            return true;
        }
        else if (MovieA.movie_rating < MovieB.movie_rating)
        { // if Movie A has a lower rating than Movie B then Movie A comes before Movie B
            return false;
        }
        else // scores and ratings are equal
        {
            return MovieA.movie_name < MovieB.movie_name; // Movie A is alphabetically first
        }
    }
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    // if movie_count is negative or 0 we just return an empty vector
    if (movie_count <= 0)
    {
        vector<MovieAndRank> empty_recommendations;
        return empty_recommendations;
    }
    
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
    unordered_map<Movie*, int> compatibility_map;
    
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
                compatibility_map[movies_with_director[k]] += 20;
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
                compatibility_map[movies_with_actor[k]] += 30;
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
                compatibility_map[movies_with_genre[k]] += 1;
            }
        }
    }
    
    // filter out the movies that we have already watched
    for (unordered_map<Movie*, int>::iterator it = compatibility_map.begin(); it != compatibility_map.end(); it++) // loop through the unordered map
    {
        if (find(movies_watched.begin(), movies_watched.end(), it->first) != movies_watched.end()) // if the pointer of the movie in the compatibility map IS in the pointers of movies watched
        {
            // we want to remove the id-score pair from the unordered_map
            compatibility_map.erase(it);
        }
    }
    
    // compatibility map now has only movies with compatibility score of 1+ and no movies that are already watched
    // compatibility map is mapping type Movie* ==> int
    
    // convert compatibility map into a vector of type MovieAndRankHelper
    vector<MovieAndRankHelper> helper_v;
    
    for (unordered_map<Movie*, int>::iterator i = compatibility_map.begin(); i != compatibility_map.end(); i++)
    {
        string movieID = (i->first)->get_id();
        float movieRating = (i->first)->get_rating();
        string movieName = (i->first)->get_title();
        int compatibilityScore = i->second;
        
        MovieAndRankHelper temp(movieID, compatibilityScore, movieRating, movieName);
        helper_v.push_back(temp);
    }
    
    // helper_v is now a vector of the type MovieAndRankHelper, so sort helper_v
    sort(helper_v.begin(), helper_v.end(), &customCompare);
    
    // now it is sorted so we create a new vector of recommendations and fill it with as many as wanted
    vector<MovieAndRank> recommendations;
    
    for (int i = 0; i < movie_count; i++)
    {
        string movieID = helper_v[i].movie_id;
        int compatibilityScore = helper_v[i].movie_score;
        
        MovieAndRank temp(movieID, compatibilityScore);
        recommendations.push_back(temp);
    }
        
        
    return recommendations;
}
