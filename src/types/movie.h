#ifndef TYPE_MOVIE_H
#define TYPE_MOVIE_H


typedef struct Movie {
    int id;
    float version;
    char *name;
    int duration;
    char **types;
    int type_count;

    int note;
    char *description;
    int year;
    char *director;
    char *ageRating;
    char *language;

    char **cast;
    int cast_count;
} Movie;

typedef struct MovieNode {
    Movie *movie;
    struct MovieNode *next;
} MovieNode;

#endif