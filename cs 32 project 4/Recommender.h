#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>

class UserDatabase;
class MovieDatabase;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
    UserDatabase* m_user_database;
    MovieDatabase* m_movie_database;
    
    struct MovieAndRankHelper
    {
        MovieAndRankHelper(std::string movieID, int movieScore, float movieRating, const std::string movieName) : movie_id(movieID), movie_score(movieScore), movie_name(movieName), movie_rating(movieRating) {}
        
        std::string movie_id;
        std::string movie_name;
        int movie_score;
        float movie_rating;
    };
    static bool customCompare(const MovieAndRankHelper& MovieA, const MovieAndRankHelper& MovieB);
};

#endif // RECOMMENDER_INCLUDED
