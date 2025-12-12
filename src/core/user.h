#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>

#include "../pages/login.h"
#include "../types/user.h"


typedef enum Status {
    STATUS_ERROR = -1,
    STATUS_NOT_FOUND = 0,
    STATUS_FOUND = 1
} Status;


Status emailExiste(const char* email);
InfoUser checkLogin(const char* email, const char* password);

void saveUserCredentials(const char* email, const char* password);
Status setName(const char* email, const char* name);
Status setSurname(const char* email, const char* surname);

#endif