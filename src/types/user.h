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
    
} User;


#endif