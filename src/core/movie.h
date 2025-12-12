#ifndef MOVIE_H
#define MOVIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/movie.h"
#include "../main.h"



typedef enum MovStatus {
    MSTATUS_ERROR = -1,
    MSTATUS_NERROR_NSUCCES = 0,
    MSTATUS_SUCCESS = 1
} MovStatus;

int loadMovies();
int saveMovies(MovieNode *list);
int saveAllMovies(MovieNode *list);
int addMovie(Movie *movie);
void deleteMovie(void *movie);
int getNMovie();

MovieNode* getMovieList();
Movie* getMovieById(int id);
int searchMovieByName(const char *movieName, const char *search);


#endif