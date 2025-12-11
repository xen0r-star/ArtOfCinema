#include "user.h"


Status emailExiste(const char* email) {
    FILE *fdat = fopen(DATA_FILE, "r");
    if (fdat == NULL) return STATUS_ERROR;

    char buffer[38];
    while(fscanf(fdat, "%37s%*[^\n]", buffer) != EOF) {
        if (_stricmp(buffer, email) == 0) {
            fclose(fdat);
            return STATUS_FOUND;
        }
    }
    
    fclose(fdat);
    return STATUS_NOT_FOUND;
}

InfoUser checkLogin(const char* email, const char* password) {
    FILE *fdat = fopen(DATA_FILE, "r");
    if (fdat == NULL) return (InfoUser){ROLE_ERROR, "", ""};
    
    char fileEmail[38];
    char filePassword[38];
    while(fscanf(fdat, "%37s %37s", fileEmail, filePassword) != EOF) {
        if (_stricmp(fileEmail, email) == 0 && strcmp(filePassword, password) == 0) {
            char role[9], tpmN[38], tpmP[38];
            fscanf(fdat,"%37s %37s %8s", tpmN, tpmP, role);
            fclose(fdat);

            InfoUser user;
            strcpy(user.name, tpmN);
            strcpy(user.surname, tpmP);

            if (strcmp(role, "CLIENT") == 0) user.role = ROLE_CLIENT;
            else if (strcmp(role, "DIRECTOR") == 0) user.role = ROLE_DIRECTOR;
            else user.role = ROLE_NONE;

            return user;

        } else {
            fscanf(fdat, "%*[^\n]");
        }
    }

    fclose(fdat);
    return (InfoUser){ROLE_ERROR, "", ""};
}



void saveUserCredentials(const char* email, const char* password) {
    FILE *fdat = fopen(DATA_FILE, "a");
    if (fdat == NULL) return;

    char emailLower[38];
    strncpy(emailLower, email, 37);
    emailLower[37] = '\0';
    _strlwr(emailLower);

    fprintf(fdat, "%-37s %-37s %37s %37s %-8s\n", emailLower, password, "", "", "CLIENT");
    fclose(fdat);
}


Status setName(const char* email, const char* name) {
    FILE *fdat = fopen(DATA_FILE, "r+");
    if (fdat == NULL) return STATUS_ERROR;

    char buffer[38];
    long pos = ftell(fdat);
    while(fscanf(fdat, "%37s", buffer) != EOF) {
        if (_stricmp(buffer, email) == 0) {
            fseek(fdat, pos + 78, SEEK_SET);
            fprintf(fdat, "%-37s", name);

            fclose(fdat);
            return STATUS_FOUND;
        }
        
        fscanf(fdat, "%*[^\n]");
        pos = ftell(fdat);
    }

    fclose(fdat);
    return STATUS_NOT_FOUND;
}

Status setSurname(const char* email, const char* surname) {
    FILE *fdat = fopen(DATA_FILE, "r+");
    if (fdat == NULL) return STATUS_ERROR;
    
    char buffer[38];
    long pos = ftell(fdat);
    while(fscanf(fdat, "%37s", buffer) != EOF) {
        if (_stricmp(buffer, email) == 0) {
            fseek(fdat, pos + 116, SEEK_SET);
            fprintf(fdat, "%-37s", surname);

            fclose(fdat);
            return STATUS_FOUND;
        }
        
        fscanf(fdat, "%*[^\n]");
        pos = ftell(fdat);
    }

    fclose(fdat);
    return STATUS_NOT_FOUND;
}
