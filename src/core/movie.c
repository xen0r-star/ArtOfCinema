#include "movie.h"

int loadMovies() {
    FILE *file = fopen("../data/movies.dat", "r");
    if (file == NULL) return -1;

    fscanf(file, "%[^\n]\n"); // Skip header line

    Movie movie;
    while (
        fscanf(file, "%") != EOF
    ) {
        /* code */
    }
    

    fclose(file);
    return 0;
}