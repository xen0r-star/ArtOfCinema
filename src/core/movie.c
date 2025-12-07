#include "movie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static MovieNode *movieList = NULL;


int loadMovies() {
    FILE *file = fopen("data/movies.csv", "r");
    if (file == NULL) return -1;

    char buffer[1024];
    fscanf(file, "%[^\n]\n", buffer); // Skip header

    Movie movie = {0};
    char name[100], typesStr[512], desc[512], director[100], age[10], lang[50], castStr[512];
    MovieNode *tail = NULL;

    while (fscanf(file, "%5d;%99[^;];%3d;%2d;%511[^;];%3d;%511[^;];%4d;%99[^;];%9[^;];%49[^;];%2d;%511[^\n]\n",
            &movie.id, name, &movie.duration, &movie.type_count, typesStr, &movie.note,
            desc, &movie.year, director, age, lang, &movie.cast_count, castStr) == 13) {
        
        movie.name = strdup(name);
        movie.description = strdup(desc);
        movie.director = strdup(director);
        movie.ageRating = strdup(age);
        movie.language = strdup(lang);


        // Parse Types
        if (movie.type_count > 0) {
            movie.types = malloc(sizeof(char*) * movie.type_count);
            char *token = strtok(typesStr, "|");
            for (int i = 0; i < movie.type_count && token; i++) {
                movie.types[i] = strdup(token);
                token = strtok(NULL, "|");
            }
        } else {
            movie.types = NULL;
        }

        // Parse Cast
        if (movie.cast_count > 0) {
            movie.cast = malloc(sizeof(char*) * movie.cast_count);
            char *token = strtok(castStr, "|");
            for (int i = 0; i < movie.cast_count && token; i++) {
                movie.cast[i] = strdup(token);
                token = strtok(NULL, "|");
            }
        } else {
            movie.cast = NULL;
        }


        // Create and append Node
        MovieNode *newNode = malloc(sizeof(MovieNode));
        if (newNode) {
            newNode->movie = movie;
            newNode->next = NULL;

            if (movieList == NULL) {
                movieList = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }

        // Reset movie struct for next iteration
        memset(&movie, 0, sizeof(Movie));
    }

    fclose(file);
    return 0;
}




MovieNode* getMovieList() {
    return movieList;
}