#ifndef TYPE_RESERVATION_H
#define TYPE_RESERVATION_H


typedef struct ReservationSnack {
    int productId;
    int quantity;
    struct ReservationSnack *next;
} ReservationSnack;

typedef struct Reservation {
    char clientEmail[38];
    char clientName[38];
    char clientSurname[38];

    int projectionId;
    int qtyAdult;
    int qtyChild;
    int qtyStudent;
    int qtySenior;

    int snackCount;
    ReservationSnack *snacks; 
} Reservation;

typedef struct ReservationNode {
    Reservation reservation;
    struct ReservationNode *next;
} ReservationNode;

#endif