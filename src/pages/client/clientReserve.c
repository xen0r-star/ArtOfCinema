#include "clientReserve.h"
#include "../../core/product.h"


static const float PRICE_ADULT = 10.0f;
static const float PRICE_CHILD = 5.0f;
static const float PRICE_STUDENT = 7.5f;
static const float PRICE_SENIOR = 6.0f;

static int pageIndex = 0;
static char filterTitle[100] = "";
static char filterDate[100] = "";
static int showSortMovie = 0;
static int reserveProjectionId = -1;
static StepReserve step = RESERVE_STEP_TICKETS;

static char filterFoodName[100] = "";
static int foodPageIndex = 0;

typedef struct {
    int productId;
    int quantity;
} SelectedFood;

#define MAX_SELECTED_FOOD 20
static SelectedFood selectedFoods[MAX_SELECTED_FOOD];


static int qtyAdult = 0;
static int qtyChild = 0;
static int qtyStudent = 0;
static int qtySenior = 0;


static void resetReservation() {
    qtyAdult = 0;
    qtyChild = 0;
    qtyStudent = 0;
    qtySenior = 0;
    
    // Reset Food
    for (int i = 0; i < MAX_SELECTED_FOOD; i++) {
        selectedFoods[i].productId = 0;
        selectedFoods[i].quantity = 0;
    }
    step = RESERVE_STEP_TICKETS;
    foodPageIndex = 0;
    strcpy(filterFoodName, "");
}



static int getFoodQty(int productId) {
    for (int i = 0; i < MAX_SELECTED_FOOD; i++) {
        if (selectedFoods[i].productId == productId) {
            return selectedFoods[i].quantity;
        }
    }
    return 0;
}

static void incFoodQty(void *data) {
    int productId = *(int*)data;
    Product *p = getProductById(productId);
    
    if (p) {
        for (int i = 0; i < MAX_SELECTED_FOOD; i++) {
            if (selectedFoods[i].productId == productId) {
                if (selectedFoods[i].quantity < 9 && selectedFoods[i].quantity < p->qte) {
                    selectedFoods[i].quantity++;
                    setCurrentPage(PAGE_CLIENT_RESERVE);
                    return;
                }
                return;
            }
        }
        
        for (int i = 0; i < MAX_SELECTED_FOOD; i++) {
            if (selectedFoods[i].productId == 0) {
                selectedFoods[i].productId = productId;
                if (p->qte > 0) selectedFoods[i].quantity = 1;
                setCurrentPage(PAGE_CLIENT_RESERVE);
                return;
            }
        }
    }
}

static void decFoodQty(void *data) {
    int productId = *(int*)data;
    for (int i = 0; i < MAX_SELECTED_FOOD; i++) {
        if (selectedFoods[i].productId == productId) {
            if (selectedFoods[i].quantity > 0) {
                selectedFoods[i].quantity--;
                if (selectedFoods[i].quantity == 0) {
                    selectedFoods[i].productId = 0; // Remove
                }
                setCurrentPage(PAGE_CLIENT_RESERVE);
                return;
            }
            return;
        }
    }
}

static void prevFoodPage() {
    if (foodPageIndex > 0) {
        foodPageIndex--;
        setCurrentPage(PAGE_CLIENT_RESERVE);
    }
}

static void nextFoodPage() {
    foodPageIndex++;
    setCurrentPage(PAGE_CLIENT_RESERVE);
}

static void onSearchFood() {
    Input *input = getInput(0);
    if (input) {
        strcpy(filterFoodName, input->value);
        foodPageIndex = 0;
        setCurrentPage(PAGE_CLIENT_RESERVE);
    }
}



static void cancelReservation() {
    reserveProjectionId = -1;
    resetReservation();
    setCurrentPage(PAGE_CLIENT_RESERVE);
}

static void confirmTicket() {
    step = RESERVE_STEP_FOOD;
    setCurrentPage(PAGE_CLIENT_RESERVE);
}

static void confirmFood() {
    step = RESERVE_STEP_CONFIRM;
    setCurrentPage(PAGE_CLIENT_RESERVE);
}

static void confirmReservation() {
    step = RESERVE_STEP_DONE;

    Reservation reservation = {0};
    strcpy(reservation.clientEmail, getUser().email);
    strcpy(reservation.clientName, getUser().name);
    strcpy(reservation.clientSurname, getUser().surname);

    reservation.projectionId = reserveProjectionId;
    reservation.qtyAdult = qtyAdult;
    reservation.qtyChild = qtyChild;
    reservation.qtyStudent = qtyStudent;
    reservation.qtySenior = qtySenior;

    reservation.snackCount = 0;
    ReservationSnack *lastSnack = NULL;
    for (int i = 0; i < MAX_SELECTED_FOOD; i++) {
        if (selectedFoods[i].productId != 0 && selectedFoods[i].quantity > 0) {
            ReservationSnack *snack = malloc(sizeof(ReservationSnack));
            if (snack) {
                snack->productId = selectedFoods[i].productId;
                snack->quantity = selectedFoods[i].quantity;
                snack->next = NULL;

                if (lastSnack == NULL) reservation.snacks = snack;
                else                   lastSnack->next = snack;

                lastSnack = snack;
                reservation.snackCount++;
            }
        }
    }

    saveReservation(&reservation);
    setCurrentPage(PAGE_CLIENT_RESERVE);
}




static void incQty(void *data) {
    int *qty = (int*)data;
    Projection *p = getProjectionById(reserveProjectionId);
    if (p && (qtyAdult + qtyChild + qtyStudent + qtySenior) < p->available_seats && *qty < 99) {
        (*qty)++;
        setCurrentPage(PAGE_CLIENT_RESERVE);
    }
}

static void decQty(void *data) { 
    int *qty = (int*)data;
    if (*qty > 0) { 
        (*qty)--; 
        setCurrentPage(PAGE_CLIENT_RESERVE); 
    } 
}



static void drawTicketControl(int x, int y, const char* name, float price, int* qty, int alignRight) {
    char label[64];
    char strQty[4];
    snprintf(label, sizeof(label), "%8s (%5.2f E)", name, price);
    snprintf(strQty, sizeof(strQty), "%02d", *qty);

    int labelX, btnDecX, qtyX, btnIncX;

    if (alignRight) {
        int len = strlen(label);
        labelX = x - len;
        btnDecX = x - (len + 11);
        qtyX = x - (len + 7);
        btnIncX = x - (len + 4);

    } else {
        labelX = x + 11;
        btnDecX = x;
        qtyX = x + 4;
        btnIncX = x + 7;
    }

    createText(labelX, y + 1, label, TEXT_COLOR);
    createDataButton(btnDecX, y, 3, "-", WARNING_COLOR, STYLE_DEFAULT, decQty, qty);
    createText(qtyX, y + 1, strQty, TEXT_COLOR);
    createDataButton(btnIncX, y, 3, "+", SUCCESS_COLOR, STYLE_DEFAULT, incQty, qty);
}




static void prevPage() {
    if (pageIndex > 0) {
        pageIndex--;
        setCurrentPage(PAGE_CLIENT_RESERVE);
    }
}

static void nextPage() {
    pageIndex++;
    setCurrentPage(PAGE_CLIENT_RESERVE);
}

static void onSearch() {
    Input *input = getInput(0);
    if (input) {
        strcpy(filterTitle, input->value);
        strcpy(filterDate, "");
        pageIndex = 0;
        setCurrentPage(PAGE_CLIENT_RESERVE);
    }
}

static void onSortMovie() {
    Input *input = getInput(0);
    if (input) {
        strcpy(filterDate, input->value);
        strcpy(filterTitle, "");
        pageIndex = 0;
        showSortMovie = 0;
        setCurrentPage(PAGE_CLIENT_RESERVE);
    }
}

static void changeDisplaySortMovie() {
    showSortMovie = !showSortMovie;
    setCurrentPage(PAGE_CLIENT_RESERVE);
}

static void reserveMovie(void* data) {
    int* projectionId = (int*)data;
    reserveProjectionId = *projectionId;
    resetReservation();
    setCurrentPage(PAGE_CLIENT_RESERVE);
}



void showClientReservePage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    if (rows > 40) drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);

    drawFooter();
    buttonSetting();
    buttonBack(PAGE_CLIENT);


    if (reserveProjectionId == -1) {
        int listStartY = 8;
        if (rows > 40) listStartY = 14;

        int itemHeight = 2;
        int maxItems = (rows - 6 - listStartY) / itemHeight;
        if (maxItems < 1) maxItems = 1;


        int startLine = (columns - (INPUT_WIDTH + 16 + 10 + 4)) / 2;
        if (showSortMovie) {
            createInput(startLine, listStartY - 4, _T("client.date"), _T("client.date.format"));
            createButton(startLine + INPUT_WIDTH + 2, listStartY - 4, 16, _T("search"), PRIMARY_COLOR, STYLE_DEFAULT, onSortMovie);
            createButton(startLine + INPUT_WIDTH + 2 + 16 + 2, listStartY - 4, 10, _T("close"), WARNING_COLOR, STYLE_DEFAULT, changeDisplaySortMovie);
        } else {
            createInput(startLine, listStartY - 4, _T("client.sch.flm"), _T("client.sch.plh2"));
            createButton(startLine + INPUT_WIDTH + 2, listStartY - 4, 16, _T("search"), PRIMARY_COLOR, STYLE_DEFAULT, onSearch);
            createButton(startLine + INPUT_WIDTH + 2 + 16 + 2, listStartY - 4, 10, _T("client.date.UPPERCASE"), TERTIARY_COLOR, STYLE_DEFAULT, changeDisplaySortMovie);
        }
    
    
        ProjectionNode *node = getProjectionList();
        
        int matchesCount = 0;
        int displayedCount = 0;
        int skipCount = pageIndex * maxItems;
        int hasMore = 0;
    
        while (node != NULL) {
            Movie *movie = getMovieById(node->projection.movie_id);
            
            int match = 0;
            if (movie) {
                if (strlen(filterDate) > 0) {
                    if (strstr(node->projection.datetime, filterDate) != NULL) match = 1;
                } else if (searchMovieByName(movie->name, filterTitle)) {
                    match = 1;
                }
            }

            if (match) {
                if (matchesCount >= skipCount) {
                    if (displayedCount < maxItems) {
                        createText(startLine, 
                            listStartY + (displayedCount * itemHeight), 
                            movie->name, TERTIARY_COLOR
                        );
                        createText(
                            startLine + INPUT_WIDTH - 10, 
                            listStartY + (displayedCount * itemHeight), 
                            node->projection.datetime, TEXT_COLOR
                        );

                        char str[16];
                        if (node->projection.available_seats == 0) {
                            strcpy(str, _T("full"));
                            createText(
                                startLine + INPUT_WIDTH + 8, 
                                listStartY + (displayedCount * itemHeight), 
                                str, WARNING_COLOR
                            );

                        } else {
                            snprintf(str, sizeof(str),  _T("seats"), node->projection.available_seats);
                            createText(
                                startLine + INPUT_WIDTH + 8, 
                                listStartY + (displayedCount * itemHeight), 
                                str, SUCCESS_COLOR
                            );
                        }
    
                        createDataButton(
                            startLine + INPUT_WIDTH + 21, 
                            listStartY + (displayedCount * itemHeight) - 1, 
                            10, _T("client.btn.view.reserve"), 
                            TERTIARY_COLOR, STYLE_BORDERLESS, 
                            reserveMovie, &node->projection.id
                        );
                        displayedCount++;
    
                    } else {
                        hasMore = 1;
                        break;
                    }
                }
                matchesCount++;
            }
            node = node->next;
        }
    
        
        int startBtnX = (columns - (15 + 2 + 15)) / 2;
    
        if (pageIndex > 0) createButton(startBtnX, rows - 5, 15, _T("prev"), TERTIARY_COLOR, STYLE_DEFAULT, prevPage);
        else               createButton(startBtnX, rows - 5, 15, _T("prev"), TEXTSECONDARY_COLOR, STYLE_DEFAULT, NULL);
        
        if (hasMore) createButton(startBtnX + 15 + 2, rows - 5, 15, _T("next"), TERTIARY_COLOR, STYLE_DEFAULT, nextPage);
        else         createButton(startBtnX + 15 + 2, rows - 5, 15, _T("next"), TEXTSECONDARY_COLOR, STYLE_DEFAULT, NULL);
        
    } else {
        Projection *projection = getProjectionById(reserveProjectionId);
        
        if (projection) {
            Movie *movie = getMovieById(projection->movie_id);
            
            int centerX = columns / 2;
            
            if (step == RESERVE_STEP_TICKETS) {
                int y = 4;
                if (rows > 40) y = 11;

                // Info Film
                if (movie) {
                    createText(ALIGN_CENTER, y, movie->name, PRIMARY_COLOR);
                }

                int startX = columns * 0.2;
                int endX = columns - (columns * 0.2);
                
                char dateStr[64];
                snprintf(dateStr, sizeof(dateStr), _T("session"), projection->datetime);
                createText(startX, y + 2, dateStr, TERTIARY_COLOR);

                char seatStr[64];
                snprintf(seatStr, sizeof(seatStr), _T("seatavl"), projection->available_seats);
                createText(endX - strlen(seatStr), y + 2, seatStr, TERTIARY_COLOR);


                drawTicketControl(startX, y + 4, _T("adult"), PRICE_ADULT, &qtyAdult, 0);
                drawTicketControl(endX, y + 4, _T("kid"), PRICE_CHILD, &qtyChild, 1);
                
                drawTicketControl(startX, y + 7, _T("student"), PRICE_STUDENT, &qtyStudent, 0);
                drawTicketControl(endX, y + 7, _T("senior"), PRICE_SENIOR, &qtySenior, 1);

                // Total
                float total = (qtyAdult * PRICE_ADULT) + (qtyChild * PRICE_CHILD) + (qtyStudent * PRICE_STUDENT) + (qtySenior * PRICE_SENIOR);
                char totalStr[64];
                snprintf(totalStr, sizeof(totalStr), _T("tot"), total);
                createText(centerX - (strlen(totalStr) / 2), rows - 9, totalStr, TERTIARY_COLOR);


                // Actions
                createButton(centerX - 16, rows - 7, 15, _T("cancel"), WARNING_COLOR, STYLE_DEFAULT, cancelReservation);
                if (total > 0) createButton(centerX + 1, rows - 7, 15, _T("confirm"), SUCCESS_COLOR, STYLE_DEFAULT, confirmTicket);
                else           createButton(centerX + 1, rows - 7, 15, _T("confirm"), TEXTSECONDARY_COLOR, STYLE_DEFAULT, NULL);

            } else if (step == RESERVE_STEP_FOOD) {
                int y = 8;
                if (rows > 40) y = 14;

                int itemHeight = 3;
                int maxItems = (rows - 6 - y - 4) / itemHeight; // -4 for bottom buttons
                if (maxItems < 1) maxItems = 1;


                int startLine = (columns - (INPUT_WIDTH + 16 + 2)) / 2;
                createInput(startLine, y - 4, _T("client.sch.pdt"), _T("client.sch.plh"));
                createButton(startLine + INPUT_WIDTH + 2, y - 4, 16, _T("search"), PRIMARY_COLOR, STYLE_DEFAULT, onSearchFood);
    

                ProductNode *node = getProductList();

                int matchesCount = 0;
                int displayedCount = 0;
                int skipCount = foodPageIndex * maxItems;
                int hasMore = 0;

                float foodTotal = 0;
                for (int i=0; i<MAX_SELECTED_FOOD; i++) {
                    if (selectedFoods[i].productId != 0) {
                        Product *p = getProductById(selectedFoods[i].productId);
                        if (p) foodTotal += p->price * selectedFoods[i].quantity;
                    }
                }

                while (node != NULL) {
                    int match = 0;
                    if (searchProductByName(node->product->name, filterFoodName)) {
                        match = 1;
                    }

                    if (match) {
                        if (matchesCount >= skipCount) {
                            if (displayedCount < maxItems) {
                                int itemY = y + (displayedCount * itemHeight);
                                
                                createText(startLine, itemY, node->product->name, TERTIARY_COLOR);
                                
                                char priceStr[16];
                                snprintf(priceStr, sizeof(priceStr), "%.2f E", node->product->price);
                                createText(startLine + 25, itemY, priceStr, TEXT_COLOR);

                                char stockStr[16];
                                snprintf(stockStr, sizeof(stockStr), _T("stock"), node->product->qte);
                                createText(startLine + 35, itemY, stockStr, (node->product->qte > 0 ? SUCCESS_COLOR : WARNING_COLOR));

                                int currentQty = getFoodQty(node->product->id);
                                char qtyStr[4];
                                snprintf(qtyStr, sizeof(qtyStr), "%d", currentQty);
                                
                                int ctrlX = startLine + 49;
                                createDataButton(ctrlX, itemY - 1, 3, "-", WARNING_COLOR, STYLE_DEFAULT, decFoodQty, &node->product->id);
                                createText(ctrlX + 4, itemY, qtyStr, TEXT_COLOR);
                                createDataButton(ctrlX + 7, itemY - 1, 3, "+", SUCCESS_COLOR, STYLE_DEFAULT, incFoodQty, &node->product->id);

                                displayedCount++;

                            } else {
                                hasMore = 1;
                                break;
                            }
                        }
                        matchesCount++;
                    }
                    node = node->next;
                }

                // Pagination
                int startBtnX = (columns - (15 + 2 + 15)) / 2;
                if (foodPageIndex > 0) createButton(startBtnX, rows - 9, 15, _T("prev"), TERTIARY_COLOR, STYLE_DEFAULT, prevFoodPage);
                else                   createButton(startBtnX, rows - 9, 15, _T("prev"), TEXTSECONDARY_COLOR, STYLE_DEFAULT, NULL);
                
                if (hasMore) createButton(startBtnX + 15 + 2, rows - 9, 15, _T("next"), TERTIARY_COLOR, STYLE_DEFAULT, nextFoodPage);
                else         createButton(startBtnX + 15 + 2, rows - 9, 15, _T("next"), TEXTSECONDARY_COLOR, STYLE_DEFAULT, NULL);

                // Totals
                float movieTotal = (qtyAdult * PRICE_ADULT) + (qtyChild * PRICE_CHILD) + (qtyStudent * PRICE_STUDENT) + (qtySenior * PRICE_SENIOR);
                char totalStr[100];
                snprintf(totalStr, sizeof(totalStr), _T("filmsnacktot"), movieTotal, foodTotal, movieTotal + foodTotal);
                createText(centerX - (strlen(totalStr) / 2), rows - 5, totalStr, TERTIARY_COLOR);

                // Actions
                createButton(centerX - 16, rows - 3, 15, _T("cancel"), WARNING_COLOR, STYLE_DEFAULT, cancelReservation);
                createButton(centerX + 1, rows - 3, 15, _T("confirm"), SUCCESS_COLOR, STYLE_DEFAULT, confirmFood);
            
            } else if (step == RESERVE_STEP_CONFIRM) {
                int y = 8;
                if (rows > 40) y = 14;

                createText(ALIGN_CENTER, y, _T("cfmres"), TERTIARY_COLOR);
                createButton(centerX - 16, y + 2, 15, _T("cancel"), WARNING_COLOR, STYLE_DEFAULT, cancelReservation);
                createButton(centerX + 1, y + 2, 15, _T("confirm"), SUCCESS_COLOR, STYLE_DEFAULT, confirmReservation);

            } else if (step == RESERVE_STEP_DONE) {
                int y = 4;
                if (rows > 40) y = 14;

                createText(ALIGN_CENTER, y, _T("resconfirm"), SUCCESS_COLOR);
                y += 2;

                // Movie Info
                if (movie) {
                    char movieStr[100];
                    snprintf(movieStr, sizeof(movieStr), _T("movie"), movie->name);
                    createText(centerX - 20, y, movieStr, PRIMARY_COLOR);
                    y++;
                    char dateStr[100];
                    snprintf(dateStr, sizeof(dateStr), _T("date"), projection->datetime);
                    createText(centerX - 20, y, dateStr, TEXT_COLOR);
                    y += 2;
                }

                // Tickets
                float ticketsTotal = 0;
                createText(centerX - 20, y, _T("ticket"), TERTIARY_COLOR);
                y++;
                
                if (qtyAdult > 0) {
                    char str[100];
                    float sub = qtyAdult * PRICE_ADULT;
                    ticketsTotal += sub;
                    snprintf(str, sizeof(str), _T("adultprc"), qtyAdult, PRICE_ADULT, sub);
                    createText(centerX - 18, y, str, TEXT_COLOR);
                    y++;
                }
                if (qtyChild > 0) {
                    char str[100];
                    float sub = qtyChild * PRICE_CHILD;
                    ticketsTotal += sub;
                    snprintf(str, sizeof(str), _T("kidprc"), qtyChild, PRICE_CHILD, sub);
                    createText(centerX - 18, y, str, TEXT_COLOR);
                    y++;
                }
                if (qtyStudent > 0) {
                    char str[100];
                    float sub = qtyStudent * PRICE_STUDENT;
                    ticketsTotal += sub;
                    snprintf(str, sizeof(str), _T("studentprc"), qtyStudent, PRICE_STUDENT, sub);
                    createText(centerX - 18, y, str, TEXT_COLOR);
                    y++;
                }
                if (qtySenior > 0) {
                    char str[100];
                    float sub = qtySenior * PRICE_SENIOR;
                    ticketsTotal += sub;
                    snprintf(str, sizeof(str), _T("seniorprc"), qtySenior, PRICE_SENIOR, sub);
                    createText(centerX - 18, y, str, TEXT_COLOR);
                    y++;
                }
                y++;

                // Food
                float foodTotal = 0;
                int hasFood = 0;
                for (int i=0; i<MAX_SELECTED_FOOD; i++) {
                    if (selectedFoods[i].productId != 0) {
                        hasFood = 1;
                        break;
                    }
                }

                if (hasFood) {
                    createText(centerX - 20, y, _T("snacks"), TERTIARY_COLOR);
                    y++;
                    for (int i=0; i<MAX_SELECTED_FOOD; i++) {
                        if (selectedFoods[i].productId != 0) {
                            Product *p = getProductById(selectedFoods[i].productId);
                            if (p) {
                                char str[100];
                                float sub = selectedFoods[i].quantity * p->price;
                                foodTotal += sub;
                                snprintf(str, sizeof(str), "- %d x %s (%.2f) = %.2f E", selectedFoods[i].quantity, p->name, p->price, sub);
                                createText(centerX - 18, y, str, TEXT_COLOR);
                                y++;
                            }
                        }
                    }
                    y++;
                }

                // Total
                char totalStr[100];
                snprintf(totalStr, sizeof(totalStr), _T("totpaiement"), ticketsTotal + foodTotal);
                createText(ALIGN_CENTER, y, totalStr, SUCCESS_COLOR);
                y += 3;

                createButton(ALIGN_CENTER, y, 20, _T("finish"), TERTIARY_COLOR, STYLE_DEFAULT, cancelReservation);

            } else {
                cancelReservation();
            }

        } else {
            cancelReservation();
        }
    }
}