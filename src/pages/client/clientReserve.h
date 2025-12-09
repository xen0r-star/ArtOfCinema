#ifndef CLIENTRESERVE_H
#define CLIENTRESERVE_H


#include "../../components/logo.h"
#include "../../components/footer.h"
#include "../../components/text.h"
#include "../../components/button.h"
#include "../../components/logout.h"
#include "../../components/language.h"
#include "../../components/back.h"

#include "../../core/reservation.h"


typedef enum StepReserve {
    RESERVE_STEP_TICKETS,
    RESERVE_STEP_FOOD,
    RESERVE_STEP_CONFIRM,
    RESERVE_STEP_DONE
} StepReserve;


void showClientReservePage();

#endif