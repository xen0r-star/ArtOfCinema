#ifndef TYPE_USER_H
#define TYPE_USER_H

typedef enum Role {
    ROLE_NONE,
    ROLE_CLIENT,
    ROLE_DIRECTOR,
    ROLE_ERROR
} Role;

typedef struct User {
    int logged;
    Role role;
    char email[38];
    char name[38];
    char surname[38];
} User;

typedef struct InfoUser {
    Role role;
    char name[38];
    char surname[38];
} InfoUser;


#endif