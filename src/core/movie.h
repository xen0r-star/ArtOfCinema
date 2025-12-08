#ifndef MOVIE_H
#define MOVIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/movie.h"


int loadMovies();
MovieNode* getMovieList();
Movie* getMovieById(int id);
int searchMovieByName(const char *movieName, const char *search);


#endif