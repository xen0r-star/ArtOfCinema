#include "email.h"


bool isValidEmail(const char *email) {
    const char *at = strchr(email, '@');    // Look for the '@'

    if (!at || at == email) return false;   // '@' absent or at the beginning
    if (!strchr(at, '.'))   return false;   // '.' absent after '@'

    return true;
}
