#ifndef TYPE_PROJECTION_H
#define TYPE_PROJECTION_H

typedef struct Projection {
    int id;
    int movie_id;
    char *datetime;
    int available_seats;
} Projection;

typedef struct ProjectionNode {
    Projection *projection;
    struct ProjectionNode *next;
} ProjectionNode;

#endif
