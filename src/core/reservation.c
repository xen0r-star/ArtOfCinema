#include "reservation.h"


void saveReservation(Reservation *reservation) {
    FILE *file = fopen("data/reservation.dat", "a");

    if (!file) return;

    fprintf(file, "%-37s %-37s %-37s ", reservation->clientEmail, reservation->clientName, reservation->clientSurname);
    fprintf(file, "%05d ", reservation->projectionId);
    fprintf(file, "%02d %02d %02d %02d ", 
            reservation->qtyAdult, reservation->qtyChild,
            reservation->qtyStudent, reservation->qtySenior);

    fprintf(file, "%03d ", reservation->snackCount);
    ReservationSnack *snack = reservation->snacks;
    if (snack) {
        while (snack) {
            fprintf(file, "%05d %01d ", snack->productId, snack->quantity);
            snack = snack->next;
        }
    }

    fprintf(file, "\n");
    fclose(file);
}



static ReservationNode *reservationList = NULL;

void loadReservation() {
    ReservationNode *current = reservationList;
    while (current != NULL) {
        ReservationNode *next = current->next;
        
        ReservationSnack *snack = current->reservation.snacks;
        while (snack != NULL) {
            ReservationSnack *nextSnack = snack->next;
            free(snack);
            snack = nextSnack;
        }
        
        free(current);
        current = next;
    }
    reservationList = NULL;


    FILE *file = fopen("data/reservation.dat", "r");
    if (!file) return;

    Reservation reservation = {0};
    ReservationNode *tail = NULL;

    while (fscanf(file, "%37s %37s %37s %05d %02d %02d %02d %02d %03d",
                reservation.clientEmail,
                reservation.clientName,
                reservation.clientSurname,
                &reservation.projectionId,
                &reservation.qtyAdult,
                &reservation.qtyChild,
                &reservation.qtyStudent,
                &reservation.qtySenior,
                &reservation.snackCount) != EOF) {

        reservation.snacks = NULL;
        ReservationSnack **snackReser = &reservation.snacks;

        for (int i = 0; i < reservation.snackCount; i++) {
            int productId, quantity;
            if (fscanf(file, "%05d %01d", &productId, &quantity) == 2) {
                ReservationSnack *snack = malloc(sizeof(ReservationSnack));
                if (snack) {
                    snack->productId = productId;
                    snack->quantity = quantity;
                    snack->next = NULL;

                    *snackReser = snack;
                    snackReser = &snack->next;
                }
            }
        }

        ReservationNode *newNode = malloc(sizeof(ReservationNode));
        if (newNode) {
            newNode->reservation = reservation;
            newNode->next = NULL;

            if (reservationList == NULL) {
                reservationList = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }

        // Reset movie struct for next iteration
        memset(&reservation, 0, sizeof(Reservation));
    }

    fclose(file);
    return;
}

ReservationNode* getReservationList() {
    return reservationList;
}