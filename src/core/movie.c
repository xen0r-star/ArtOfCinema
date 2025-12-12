#include "movie.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define DATA_FILE "data/movies.dat"
#define DATA_FILE_TEMP "data/moviesTmp.dat"

static MovieNode *movieListMain = NULL;
static MovieNode *tail = NULL;
// ⚠️ ENUM COMME DANS USER.H POUR RETURN ERROR OU PAS
static bool initMovie = false;
static int nMovie = 0;

int loadMovies() {
    if(initMovie) return 0;
    initMovie = true;

    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) return 0;

    int id, duration, type_count, note, year, cast_count;
    float version;
    char name[100], typesStr[512], desc[512], director[100], age[10], lang[50], castStr[512];

    while (fscanf(file, "%5d;%99[^;];%3f;%3d;%2d;%511[^;];%3d;%511[^;];%4d;%99[^;];%9[^;];%49[^;];%2d;%511[^\n]\n", &id, name, &version, &duration, &type_count, typesStr, &note, desc, &year, director, age, lang, &cast_count, castStr) == 14) {
        Movie *newMovie = calloc(1, sizeof(Movie));

        newMovie->id = id;
        newMovie->version = version;
        newMovie->name = strdup(name);
        newMovie->duration = duration;
        newMovie->type_count = type_count;
        newMovie->note = note;
        newMovie->year = year;
        newMovie->cast_count = cast_count;
        newMovie->description = strdup(desc);
        newMovie->director = strdup(director);
        newMovie->ageRating = strdup(age);
        newMovie->language = strdup(lang);

        // Parse Types
        if (newMovie->type_count > 0) {
            newMovie->types = malloc(sizeof(char*) * newMovie->type_count);
            char *token = strtok(typesStr, "|");
            for (int i = 0; i < newMovie->type_count && token; i++) {
                newMovie->types[i] = strdup(token);
                token = strtok(NULL, "|");
            }

        } else {
            newMovie->types = NULL;
        }

        // Parse Cast
        if (newMovie->cast_count > 0) {
            newMovie->cast = malloc(sizeof(char*) * newMovie->cast_count);
            char *token = strtok(castStr, "|");
            for (int i = 0; i < newMovie->cast_count && token; i++) {
                newMovie->cast[i] = strdup(token);
                token = strtok(NULL, "|");
            }
            
        } else {
            newMovie->cast = NULL;
        }


        // Create and append Node
        MovieNode *newNode = malloc(sizeof(MovieNode));
        if (newNode) {
            newNode->movie = newMovie;
            newNode->next = NULL;

            if (movieListMain == NULL) {
                movieListMain = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        nMovie++;
    }
    fclose(file);
    return 1;
}

int saveMovies(MovieNode *list) {
    FILE *file = fopen(DATA_FILE, "r+");
    if (file == NULL) return -1;

    char buffer[512];
    while(list != NULL){
        Movie *tmpMovie = list->movie;

        rewind(file);
        long lineStart = 0;
        
        while (1) {
            lineStart = ftell(file);
            if (fgets(buffer, sizeof(buffer), file) == NULL) break;
            
            int idRead;
            if (sscanf(buffer, "%d", &idRead) == 1) {
                if (tmpMovie->id == idRead) {
                    char *firstPipe = strchr(buffer, '|');
                    if (firstPipe) {
                        char *secondPipe = strchr(firstPipe + 1, '|');
                        if (secondPipe) {
                            long qteOffset = (secondPipe - buffer) + 1;
                            
                            fseek(file, lineStart + qteOffset, SEEK_SET);
                            
                            MovieNode *curr = movieListMain;
                            while (curr != NULL) {
                                if (curr->movie->id == tmpMovie->id) {
                                    // curr->movie->qte = tmpMovie->qte;
                                    break;
                                }
                                curr = curr->next;
                            }
                            
                            // fprintf(file, "%05d", tmpMovie->qte);
                            
                            fflush(file);
                            
                            break;
                        }
                    }
                }
            }
        }
        
        list = list->next;
    }
    fclose(file);
    return 0;
}

int saveAllMovies(MovieNode *list) {
    FILE *file = fopen(DATA_FILE, "r+");
    if (file == NULL) return 0;

    char buffer[512];
    
    while(list != NULL){
        Movie *tmpMovie = list->movie;
        
        rewind(file);
        long lineStart = 0;
        
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            lineStart = ftell(file) - strlen(buffer);
            int idRead;

            if (sscanf(buffer, "%d", &idRead) == 1) {
                if (tmpMovie->id == idRead) {
                    char *firstPipe = strchr(buffer, '|');
                    if (firstPipe) {
                        long startWriteOffset = (firstPipe - buffer) +1;
                        fseek(file, lineStart + startWriteOffset, SEEK_SET);
                            
                        // fprintf(file, "%-30s|%05d|%8.2f\n", tmpMovie->name, tmpMovie->qte, tmpMovie->price);
                        fflush(file);
                        break;
                    }
                }
            }
        }
        
        list = list->next;
    }
    fclose(file);
    return 1;
}

int addMovie(Movie *movie) {
    Movie *mv = movie;
    if (mv == NULL) return MSTATUS_ERROR;
    mv->id = nMovie + 1;
    
    FILE *file = fopen(DATA_FILE, "a");
    if (file == NULL) return MSTATUS_ERROR;

    char types[511];
    types[0] = '\0';

    for (int i = 0; i < mv->type_count; i++) {
        snprintf(types + strlen(types), sizeof(types) - strlen(types),"%s", mv->types[i]);

        if (i < mv->type_count - 1) {
            snprintf(types + strlen(types), sizeof(types) - strlen(types), "|");
        }
    }
    
    char cast[511];
    cast[0] = '\0';

    for(int i = 0; i < mv->cast_count; i++){
        snprintf(cast + strlen(cast), sizeof(cast) - strlen(cast),"%s", mv->cast[i]);
        if (i < mv->cast_count - 1) {
            snprintf(cast + strlen(cast), sizeof(cast) - strlen(cast), "|");
        }
    }

    fprintf(file, "%d;%s;%.1f;%d;%d;%s;%d;%s;%d;%s;%s;%s;%d;%s\n", mv->id, mv->name, mv->version, mv->duration, mv->type_count, types, mv->note, mv->description, mv->year, mv->director, mv->ageRating, mv->language, mv->cast_count, cast);

    MovieNode *newNode = malloc(sizeof(MovieNode));
    if (newNode) {
        newNode->movie = mv;
        newNode->next = NULL;

        if (movieListMain == NULL) {
            movieListMain = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    nMovie++;
    fclose(file);
    return MSTATUS_SUCCESS;
}

void deleteMovie(void *movie) {
    Movie *mv = movie; 
    if (mv == NULL) return;

    FILE *file = fopen(DATA_FILE, "r");
    FILE *fileTemp = fopen(DATA_FILE_TEMP, "w");
    if (file == NULL || fileTemp == NULL) return;

    int targetId = mv->id;

    MovieNode *current = movieListMain;
    MovieNode  *prev = NULL;

    while (current != NULL) {
        if (current->movie->id == targetId) {
            if (prev == NULL) {
                movieListMain = current->next;
            } else {
                prev->next = current->next;
            }
            int id, duration, type_count, note, year, cast_count;
            float version;
            char name[100], typesStr[512], desc[512], director[100], age[10], lang[50], castStr[512];

            while (fscanf(file, "%5d;%99[^;];%3f;%3d;%2d;%511[^;];%3d;%511[^;];%4d;%99[^;];%9[^;];%49[^;];%2d;%511[^\n]\n", 
                            &id, name, &version, &duration, &type_count, typesStr, 
                            &note, desc, &year, director, age, lang,
                            &cast_count, castStr) == 14) {

                if (targetId == id) {
                    continue;
                }

                fprintf(fileTemp, "%d;%s;%.1f;%d;%d;", id, name, version, duration, type_count);
                // Traitement des types de film
                if (type_count > 0) {
                    char type[50];
                    char *types = typesStr;
                    
                    int ret2line = 0;
                    for(int i = 0; i < type_count; i++){
                        if (sscanf(types, "%49[^|]|%n", type, &ret2line) == 1) {
                            fprintf(fileTemp, "%s", type);
                            types += ret2line;

                            if (i < type_count - 1) {
                                fprintf(fileTemp, "|");
                            } else {
                                fprintf(fileTemp, ";");
                            }
                        } else {
                            break;
                        }
                        
                    }
                }
                // Traitement des cast de film
                fprintf(fileTemp, "%d;%s;%d;%s;%s;%s;%d;", note, desc, year, director, age, lang, cast_count);
                if (cast_count > 0) {
                    char cast[50];
                    char *casts = castStr;

                    for(int i = 0; i < cast_count; i++){
                        int ret2line = 0;
                        if (sscanf(casts, "%49[^|]|%n", cast, &ret2line) == 1) {
                            fprintf(fileTemp, "%s", cast);
                            casts += ret2line;

                            if (i < cast_count - 1) {
                                fprintf(fileTemp, "|");
                            } else {
                                fprintf(fileTemp, "\n");
                            }
                        } else {
                            break;
                        }
                    }
                } else {
                    fprintf(fileTemp, "\n");
                }
            }
            fclose(file);
            fclose(fileTemp);
            remove(DATA_FILE);
            rename(DATA_FILE_TEMP, DATA_FILE);
            free(current);
            setCurrentPage(PAGE_DIRECTOR_FILM);
            nMovie--;
            return;

        }
        prev = current;
        current = current->next;
    }
    cursor(2, 2);
    fclose(file);
    fclose(fileTemp);
    setCurrentPage(PAGE_DIRECTOR_FILM);
    return;
}

int getNMovie() {
    return nMovie;
}

MovieNode* getMovieList() {
    return movieListMain;
}

Movie* getMovieById(int id) {
    MovieNode *current = movieListMain;
    while (current != NULL) {
        if (current->movie->id == id) {
            return current->movie;
        }
        current = current->next;
    }
    return NULL;
}

int searchMovieByName(const char *movieName, const char *search) {
    if (!search || strlen(search) == 0) return 1;
    if (!movieName) return 0;

    char h[512], n[512];
    strncpy(h, movieName, 511); 
    h[511] = 0;
    
    strncpy(n, search, 511); 
    n[511] = 0;

    for(int i = 0; h[i]; i++) h[i] = tolower(h[i]);
    for(int i = 0; n[i]; i++) n[i] = tolower(n[i]);

    return strstr(h, n) != NULL;
}