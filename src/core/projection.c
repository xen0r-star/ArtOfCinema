#include "projection.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "data/projections.dat"

static ProjectionNode *projectionList = NULL;
static ProjectionNode *tail = NULL;
static bool initProjection = false;
static int nProjection = 0;

int loadProjections() {
    if(initProjection) return 0;
    initProjection = true;

    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL) return -1;

    int id, movie_id, available_seats;
    char datetime[50];

    

    while (fscanf(file, "%5d;%5d;%49[^;];%4d\n", 
            &id, &movie_id, datetime, &available_seats) == 4) {
        
        Projection *projection = calloc(1, sizeof(Projection));

        projection->id = id;
        projection->movie_id = movie_id;
        projection->available_seats = available_seats;
        projection->datetime = strdup(datetime);

        // Create and append node
        ProjectionNode *newNode = malloc(sizeof(ProjectionNode));
        if (newNode) {
            newNode->projection = projection;
            newNode->next = NULL;

            if (projectionList == NULL) {
                projectionList = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        nProjection++;
    }
    fclose(file);
    return 1;
}

int addProjection(Projection *projection) {
    Projection *pj = projection;
    if (pj == NULL) return PRSTATUS_ERROR;
    pj->id = nProjection + 1;
    
    FILE *file = fopen(DATA_FILE, "a");
    if (file == NULL) return PRSTATUS_ERROR;

    pj->id = nProjection + 1;
    fprintf(file, "%d;%d;%s;%d\n", pj->id, pj->movie_id, pj->datetime, pj->available_seats);

    ProjectionNode *newNode = malloc(sizeof(ProjectionNode));
    if (newNode) {
        newNode->projection = pj;
        newNode->next = NULL;

        if (projectionList == NULL) {
            projectionList = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    nProjection++;
    fclose(file);
    return PRSTATUS_SUCCESS;
}

ProjectionNode* getProjectionList() {
    return projectionList;
}

Projection* getProjectionById(int id) {
    ProjectionNode *current = projectionList;
    while (current != NULL) {
        if (current->projection->id == id) {
            return current->projection;
        }
        current = current->next;
    }
    return NULL;
}