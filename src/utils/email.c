#include "email.h"

int isValidEmail(const char *email) {
    // regex_t regex;

    // const char *pattern = "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$";

    // if (regcomp(&regex, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
    //     return 0;
    // }

    // int result = regexec(&regex, email, 0, NULL, 0);
    // regfree(&regex);

    // return result == 0;
    return 1;
}