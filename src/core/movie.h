#ifndef MOVIE_H
#define MOVIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/movie.h"
#include "../main.h"

int loadMovies();
int saveMovies(MovieNode *list);
int saveAllMovies(MovieNode *list);
int addMovie(MovieNode *list);
void deleteMovie(void *movie);

MovieNode* getMovieList();
Movie* getMovieById(int id);
int searchMovieByName(const char *movieName, const char *search);


#endif