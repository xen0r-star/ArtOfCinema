#ifndef PROJECTION_H
#define PROJECTION_H

#include "../types/projection.h"

typedef enum ProjStatus {
    PRSTATUS_ERROR = -1,
    PRSTATUS_NERROR_NSUCCES = 0,
    PRSTATUS_SUCCESS = 1
} ProjStatus;

int loadProjections();
int addProjection(Projection *projection);

ProjectionNode* getProjectionList();
Projection* getProjectionById(int id);

#endif
