#ifndef TYPE_MOVIE_H
#define TYPE_MOVIE_H

typedef enum Type {
    TYPE_NONE,
    TYPE_ACTION,
    TYPE_COMEDY,
    TYPE_DRAMA,
    TYPE_HORROR,
    TYPE_SCI_FI,
    TYPE_ROMANCE,
    TYPE_THRILLER,
    TYPE_DOCUMENTARY,
    TYPE_ANIMATION,
} Type;

typedef struct Movie {
    int id;
    char *name;
    int duration;
    Type *types;
    int type_count;

    float note;
    char *description;
    int year;
    char *director;
    char *ageRating;
    char *language;

    char **cast;
    int cast_count;
} Movie;

#endif