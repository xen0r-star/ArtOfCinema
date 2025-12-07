#include "projection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ProjectionNode *projectionList = NULL;

int loadProjections() {
    FILE *file = fopen("data/projections.csv", "r");
    if (file == NULL) return -1;

    char buffer[1024];
    fscanf(file, "%[^\n]\n", buffer); // Skip header

    Projection projection = {0};
    char datetime[50];
    ProjectionNode *tail = NULL;

    while (fscanf(file, "%5d;%5d;%49[^;];%4d\n", 
            &projection.id, &projection.movie_id, datetime, &projection.available_seats) == 4) {
        
        projection.datetime = strdup(datetime);

        // Create and append Node
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
        // Reset for next iteration
        memset(&projection, 0, sizeof(Projection));
    }

    fclose(file);
    return 0;
}

ProjectionNode* getProjectionList() {
    return projectionList;
}
