#include "clientReserve.h"
#include "../../core/product.h"


static const float PRICE_ADULT = 10.0f;
static const float PRICE_CHILD = 5.0f;
static const float PRICE_STUDENT = 7.5f;
static const float PRICE_SENIOR = 6.0f;

static int pageIndex = 0;
static char filterTitle[100] = "";
static int reserveProjectionId = -1;
static int isFoodStep = 0;

static char filterFoodName[100] = "";
static int foodPageIndex = 0;

typedef struct {
    int productId;
    int quantity;
} SelectedFood;

#define MAX_SELECTED_FOOD 100
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
    isFoodStep = 0;
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



static void cancelReservation() {
    reserveProjectionId = -1;
    resetReservation();
    setCurrentPage(PAGE_CLIENT_RESERVE);
}

static void finalConfirmReservation() {
    // TODO: Save reservation logic here (Movie + Food)
    // For now just reset
    reserveProjectionId = -1;
    resetReservation();
    setCurrentPage(PAGE_CLIENT_RESERVE);
}

static void confirmReservation() {
    isFoodStep = 1;
    setCurrentPage(PAGE_CLIENT_RESERVE);
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
    snprintf(label, sizeof(label), "%s (%.2f E)", name, price);
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

    createText(labelX, y + 1, label, COLOR_WHITE);
    createDataButton(btnDecX, y, 3, "-", COLOR_RED, STYLE_DEFAULT, decQty, qty);
    createText(qtyX, y + 1, strQty, COLOR_WHITE);
    createDataButton(btnIncX, y, 3, "+", COLOR_GREEN, STYLE_DEFAULT, incQty, qty);
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
        pageIndex = 0;
        setCurrentPage(PAGE_CLIENT_RESERVE);
    }
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
    buttonLogout();
    buttonLanguage();
    buttonBack(PAGE_CLIENT);


    if (reserveProjectionId == -1) {
        int listStartY = 8;
        if (rows > 40) listStartY = 14;

        int itemHeight = 2;
        int maxItems = (rows - 6 - listStartY) / itemHeight;
        if (maxItems < 1) maxItems = 1;


        int startLine = (columns - (INPUT_WIDTH + 16 + 10 + 4)) / 2;
        createInput(startLine, listStartY - 4, "Recherche un film", "Titre du film...");
        createButton(startLine + INPUT_WIDTH + 2, listStartY - 4, 16, "Rechercher", COLOR_CYAN, STYLE_DEFAULT, onSearch);
        createButton(startLine + INPUT_WIDTH + 2 + 16 + 2, listStartY - 4, 10, "Trier", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);
    
    
        ProjectionNode *node = getProjectionList();
        
        int matchesCount = 0;
        int displayedCount = 0;
        int skipCount = pageIndex * maxItems;
        int hasMore = 0;
    
        while (node != NULL) {
            Movie *movie = getMovieById(node->projection.movie_id);
            
            if (movie && searchMovieByName(movie->name, filterTitle)) {
                
                if (matchesCount >= skipCount) {
                    if (displayedCount < maxItems) {
                        char str[16];
                        snprintf(str, sizeof(str), "%4d places", node->projection.available_seats);
    
                        createText(startLine, 
                            listStartY + (displayedCount * itemHeight), 
                            movie->name, COLOR_WHITE
                        );
                        createText(
                            startLine + INPUT_WIDTH - 10, 
                            listStartY + (displayedCount * itemHeight), 
                            node->projection.datetime, COLOR_WHITE
                        );
                        createText(
                            startLine + INPUT_WIDTH + 8, 
                            listStartY + (displayedCount * itemHeight), 
                            str, COLOR_WHITE
                        );
    
                        createDataButton(
                            startLine + INPUT_WIDTH + 21, 
                            listStartY + (displayedCount * itemHeight) - 1, 
                            10, "Reserver", 
                            COLOR_CYAN, STYLE_BORDERLESS, 
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
    
        if (pageIndex > 0) createButton(startBtnX, rows - 5, 15, "Precedent", COLOR_GREEN, STYLE_DEFAULT, prevPage);
        else               createButton(startBtnX, rows - 5, 15, "Precedent", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);
        
        if (hasMore) createButton(startBtnX + 15 + 2, rows - 5, 15, "Suivant", COLOR_GREEN, STYLE_DEFAULT, nextPage);
        else         createButton(startBtnX + 15 + 2, rows - 5, 15, "Suivant", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);
        
    } else {
        Projection *projection = getProjectionById(reserveProjectionId);
        
        if (projection) {
            Movie *movie = getMovieById(projection->movie_id);
            
            int centerX = columns / 2;
            
            if (!isFoodStep) {
                // Info Film
                if (movie) {
                    createText(ALIGN_CENTER, 11, movie->name, COLOR_CYAN);
                }

                int startX = columns * 0.2;
                int endX = columns - (columns * 0.2);
                
                char dateStr[64];
                snprintf(dateStr, sizeof(dateStr), "Seance: %s", projection->datetime);
                createText(startX, 13, dateStr, COLOR_WHITE);

                char seatStr[64];
                snprintf(seatStr, sizeof(seatStr), "Places disponibles: %d", projection->available_seats);
                createText(endX - strlen(seatStr), 13, seatStr, COLOR_BRIGHT_GREEN);


                drawTicketControl(startX, 15, "Adulte", PRICE_ADULT, &qtyAdult, 0);
                drawTicketControl(endX, 15, "Enfant", PRICE_CHILD, &qtyChild, 1);
                
                drawTicketControl(startX, 18, "Etudiant", PRICE_STUDENT, &qtyStudent, 0);
                drawTicketControl(endX, 18, "Senior", PRICE_SENIOR, &qtySenior, 1);


                // Total
                float total = (qtyAdult * PRICE_ADULT) + (qtyChild * PRICE_CHILD) + (qtyStudent * PRICE_STUDENT) + (qtySenior * PRICE_SENIOR);
                char totalStr[64];
                snprintf(totalStr, sizeof(totalStr), "TOTAL: %.2f E", total);
                createText(centerX - (strlen(totalStr) / 2), rows - 9, totalStr, COLOR_YELLOW);


                // Actions
                createButton(centerX - 16, rows - 7, 15, "Annuler", COLOR_RED, STYLE_DEFAULT, cancelReservation);
                if (total > 0) createButton(centerX + 1, rows - 7, 15, "Confirmer", COLOR_GREEN, STYLE_DEFAULT, confirmReservation);
                else           createButton(centerX + 1, rows - 7, 15, "Confirmer", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);

            } else {
                int listStartY = 8;
                if (rows > 40) listStartY = 14;

                int itemHeight = 3;
                int maxItems = (rows - 6 - listStartY - 4) / itemHeight; // -4 for bottom buttons
                if (maxItems < 1) maxItems = 1;


                int startLine = (columns - (INPUT_WIDTH + 16 + 10)) / 2;
                createInput(startLine, listStartY - 4, "Recherche un produit", "Nom du produit...");
                createButton(startLine + INPUT_WIDTH + 2, listStartY - 4, 16, "Rechercher", COLOR_CYAN, STYLE_DEFAULT, onSearchFood);
                createButton(startLine + INPUT_WIDTH + 2 + 16 + 2, listStartY - 4, 10, "Trier", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);
    

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
                    if (searchProductByName(node->product.name, filterFoodName)) {
                        if (matchesCount >= skipCount) {
                            if (displayedCount < maxItems) {
                                int y = listStartY + (displayedCount * itemHeight);
                                
                                createText(startLine, y, node->product.name, COLOR_WHITE);
                                
                                char priceStr[16];
                                snprintf(priceStr, sizeof(priceStr), "%.2f E", node->product.price);
                                createText(startLine + 25, y, priceStr, COLOR_YELLOW);

                                char stockStr[16];
                                snprintf(stockStr, sizeof(stockStr), "Stock: %d", node->product.qte);
                                createText(startLine + 35, y, stockStr, (node->product.qte > 0 ? COLOR_GREEN : COLOR_RED));

                                int currentQty = getFoodQty(node->product.id);
                                char qtyStr[4];
                                snprintf(qtyStr, sizeof(qtyStr), "%d", currentQty);
                                
                                int ctrlX = startLine + 50;
                                createDataButton(ctrlX, y - 1, 3, "-", COLOR_RED, STYLE_DEFAULT, decFoodQty, &node->product.id);
                                createText(ctrlX + 4, y, qtyStr, COLOR_WHITE);
                                createDataButton(ctrlX + 7, y - 1, 3, "+", COLOR_GREEN, STYLE_DEFAULT, incFoodQty, &node->product.id);

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
                if (foodPageIndex > 0) createButton(startBtnX, rows - 9, 15, "Precedent", COLOR_GREEN, STYLE_DEFAULT, prevFoodPage);
                else                   createButton(startBtnX, rows - 9, 15, "Precedent", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);
                
                if (hasMore) createButton(startBtnX + 15 + 2, rows - 9, 15, "Suivant", COLOR_GREEN, STYLE_DEFAULT, nextFoodPage);
                else         createButton(startBtnX + 15 + 2, rows - 9, 15, "Suivant", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);

                // Totals
                float movieTotal = (qtyAdult * PRICE_ADULT) + (qtyChild * PRICE_CHILD) + (qtyStudent * PRICE_STUDENT) + (qtySenior * PRICE_SENIOR);
                char totalStr[100];
                snprintf(totalStr, sizeof(totalStr), "Film: %.2fE  +  Snack: %.2fE  =  TOTAL: %.2fE", movieTotal, foodTotal, movieTotal + foodTotal);
                createText(centerX - (strlen(totalStr) / 2), rows - 5, totalStr, COLOR_YELLOW);

                // Actions
                createButton(centerX - 16, rows - 3, 15, "Annuler", COLOR_RED, STYLE_DEFAULT, cancelReservation);
                createButton(centerX + 1, rows - 3, 15, "Confirmer", COLOR_GREEN, STYLE_DEFAULT, finalConfirmReservation);
            }

        } else {
            cancelReservation();
        }
    }
}