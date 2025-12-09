#include "clientQuote.h"

static const float PRICE_ADULT = 10.0f;
static const float PRICE_CHILD = 5.0f;
static const float PRICE_STUDENT = 7.5f;
static const float PRICE_SENIOR = 6.0f;

static Reservation *selectedReservation = NULL;
static int pageIndex = 0;

static float calculateTotal(Reservation *res) {
    float total = (res->qtyAdult * PRICE_ADULT) + 
                  (res->qtyChild * PRICE_CHILD) + 
                  (res->qtyStudent * PRICE_STUDENT) + 
                  (res->qtySenior * PRICE_SENIOR);
    
    ReservationSnack *snack = res->snacks;
    while (snack) {
        Product *p = getProductById(snack->productId);
        if (p) {
            total += p->price * snack->quantity;
        }
        snack = snack->next;
    }
    return total;
}

static void showDetails(void *data) {
    selectedReservation = (Reservation*)data;
    setCurrentPage(PAGE_CLIENT_QUOTE);
}

static void backToList() {
    selectedReservation = NULL;
    setCurrentPage(PAGE_CLIENT_QUOTE);
}

static void prevPage() {
    if (pageIndex > 0) {
        pageIndex--;
        setCurrentPage(PAGE_CLIENT_QUOTE);
    }
}

static void nextPage() {
    pageIndex++;
    setCurrentPage(PAGE_CLIENT_QUOTE);
}

void showClientQuotePage() {
    loadReservation();


    int columns, rows;
    sizeScreen(&columns, &rows);

    if (rows > 40) drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);

    drawFooter();
    buttonLogout();
    buttonLanguage();
    buttonBack(PAGE_CLIENT);
    
    ReservationNode *node = getReservationList();
    User currentUser = getUser();

    if (selectedReservation == NULL) {
        int y = 8;
        if (rows > 40) y = 14;
        
        createText(ALIGN_CENTER, y, "Mes Devis / Reservations", COLOR_CYAN);
        y += 4;

        int itemHeight = 3;
        int maxItems = (rows - 6 - y) / itemHeight;
        if (maxItems < 1) maxItems = 1;

        int count = 0;
        int displayed = 0;
        int skip = pageIndex * maxItems;
        int hasMore = 0;

        int startX = (columns - 80) / 2; 
        if (startX < 2) startX = 2;

        while (node) {
            if (strcmp(node->reservation.clientEmail, currentUser.email) == 0) {
                if (count >= skip) {
                    if (displayed < maxItems) {
                        Projection *proj = getProjectionById(node->reservation.projectionId);
                        Movie *movie = proj ? getMovieById(proj->movie_id) : NULL;
                        
                        char label[100];
                        float total = calculateTotal(&node->reservation);
                        
                        if (movie && proj) {
                            snprintf(label, sizeof(label), "%s - %s (%.2f E)", movie->name, proj->datetime, total);
                        } else {
                            snprintf(label, sizeof(label), "Reservation #%d (%.2f E)", node->reservation.projectionId, total);
                        }

                        createText(startX, y, label, COLOR_WHITE);
                        createDataButton(startX + 60, y - 1, 15, "Voir details", COLOR_CYAN, STYLE_DEFAULT, showDetails, &node->reservation);

                        y += itemHeight;
                        displayed++;
                    } else {
                        hasMore = 1;
                        break;
                    }
                }
                count++;
            }
            node = node->next;
        }

        // Pagination
        int startBtnX = (columns - (15 + 2 + 15)) / 2;
        if (pageIndex > 0) createButton(startBtnX, rows - 5, 15, "Precedent", COLOR_GREEN, STYLE_DEFAULT, prevPage);
        else               createButton(startBtnX, rows - 5, 15, "Precedent", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);
        
        if (hasMore) createButton(startBtnX + 15 + 2, rows - 5, 15, "Suivant", COLOR_GREEN, STYLE_DEFAULT, nextPage);
        else         createButton(startBtnX + 15 + 2, rows - 5, 15, "Suivant", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);

    } else {
        // DETAILS VIEW
        int centerX = columns / 2;
        int y = 4;
        if (rows > 40) y = 14;

        createText(ALIGN_CENTER, y, "DETAIL DU DEVIS", COLOR_GREEN);
        y += 2;

        Projection *projection = getProjectionById(selectedReservation->projectionId);
        Movie *movie = projection ? getMovieById(projection->movie_id) : NULL;

        // Movie Info
        if (movie) {
            char movieStr[100];
            snprintf(movieStr, sizeof(movieStr), "Film : %s", movie->name);
            createText(centerX - 20, y, movieStr, COLOR_CYAN);
            y++;
            char dateStr[100];
            snprintf(dateStr, sizeof(dateStr), "Date : %s", projection->datetime);
            createText(centerX - 20, y, dateStr, COLOR_WHITE);
            y += 2;
        }

        // Tickets
        float ticketsTotal = 0;
        createText(centerX - 20, y, "Tickets :", COLOR_YELLOW);
        y++;
        
        if (selectedReservation->qtyAdult > 0) {
            char str[100];
            float sub = selectedReservation->qtyAdult * PRICE_ADULT;
            ticketsTotal += sub;
            snprintf(str, sizeof(str), "- %d x Adulte (%.2f) = %.2f E", selectedReservation->qtyAdult, PRICE_ADULT, sub);
            createText(centerX - 18, y, str, COLOR_WHITE);
            y++;
        }
        if (selectedReservation->qtyChild > 0) {
            char str[100];
            float sub = selectedReservation->qtyChild * PRICE_CHILD;
            ticketsTotal += sub;
            snprintf(str, sizeof(str), "- %d x Enfant (%.2f) = %.2f E", selectedReservation->qtyChild, PRICE_CHILD, sub);
            createText(centerX - 18, y, str, COLOR_WHITE);
            y++;
        }
        if (selectedReservation->qtyStudent > 0) {
            char str[100];
            float sub = selectedReservation->qtyStudent * PRICE_STUDENT;
            ticketsTotal += sub;
            snprintf(str, sizeof(str), "- %d x Etudiant (%.2f) = %.2f E", selectedReservation->qtyStudent, PRICE_STUDENT, sub);
            createText(centerX - 18, y, str, COLOR_WHITE);
            y++;
        }
        if (selectedReservation->qtySenior > 0) {
            char str[100];
            float sub = selectedReservation->qtySenior * PRICE_SENIOR;
            ticketsTotal += sub;
            snprintf(str, sizeof(str), "- %d x Senior (%.2f) = %.2f E", selectedReservation->qtySenior, PRICE_SENIOR, sub);
            createText(centerX - 18, y, str, COLOR_WHITE);
            y++;
        }
        y++;

        // Food
        float foodTotal = 0;
        if (selectedReservation->snacks) {
            createText(centerX - 20, y, "Snacks :", COLOR_YELLOW);
            y++;
            ReservationSnack *snack = selectedReservation->snacks;
            while (snack) {
                Product *p = getProductById(snack->productId);
                if (p) {
                    char str[100];
                    float sub = snack->quantity * p->price;
                    foodTotal += sub;
                    snprintf(str, sizeof(str), "- %d x %s (%.2f) = %.2f E", snack->quantity, p->name, p->price, sub);
                    createText(centerX - 18, y, str, COLOR_WHITE);
                    y++;
                }
                snack = snack->next;
            }
            y++;
        }

        // Total
        char totalStr[100];
        snprintf(totalStr, sizeof(totalStr), "TOTAL : %.2f E", ticketsTotal + foodTotal);
        createText(ALIGN_CENTER, y, totalStr, COLOR_GREEN);
        y += 3;

        createButton(ALIGN_CENTER, y, 20, "Retour", COLOR_CYAN, STYLE_DEFAULT, backToList);
    }
}