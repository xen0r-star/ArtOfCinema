#ifndef RESERVATION_H
#define RESERVATION_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/reservation.h"


void saveReservation(Reservation *reservation);

void loadReservation();
ReservationNode* getReservationList();

#endif