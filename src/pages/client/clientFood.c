#include "clientFood.h"
#include "../../core/product.h"

static int pageIndex = 0;
static char filterName[100] = "";

static void prevPage() {
    if (pageIndex > 0) {
        pageIndex--;
        setCurrentPage(PAGE_CLIENT_FOOD);
    }
}

static void nextPage() {
    pageIndex++;
    setCurrentPage(PAGE_CLIENT_FOOD);
}

static void onSearch() {
    Input *input = getInput(0);
    if (input) {
        strcpy(filterName, input->value);
        pageIndex = 0;
        setCurrentPage(PAGE_CLIENT_FOOD);
    }
}




void showClientFoodPage() {
    int columns, rows;
    sizeScreen(&columns, &rows);

    if (rows > 40) drawLogo((columns / 2) - (LOGO_WIDTH / 2), 4);

    drawFooter();
    buttonLogout();
    buttonLanguage();
    buttonBack(PAGE_CLIENT);


    int listStartY = 8;
    if (rows > 40) listStartY = 14;

    int itemHeight = 2;
    int maxItems = (rows - 6 - listStartY) / itemHeight;
    if (maxItems < 1) maxItems = 1;

    
    int startLine = (columns - (INPUT_WIDTH + 16 + 10)) / 2;
    createInput(startLine, listStartY - 4, "Recherche un produit", "Nom du produit...");
    createButton(startLine + INPUT_WIDTH + 2, listStartY - 4, 16, "Rechercher", COLOR_CYAN, STYLE_DEFAULT, onSearch);
    createButton(startLine + INPUT_WIDTH + 2 + 16 + 2, listStartY - 4, 10, "Trier", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);


    ProductNode *node = getProductList();
    
    int matchesCount = 0;
    int displayedCount = 0;
    int skipCount = pageIndex * maxItems;
    int hasMore = 0;

    while (node != NULL) {
        if (searchProductByName(node->product.name, filterName)) {
            
            if (matchesCount >= skipCount) {
                if (displayedCount < maxItems) {
                    char priceStr[16];
                    snprintf(priceStr, sizeof(priceStr), "%.2fE", node->product.price);

                    char stockStr[16];
                    snprintf(stockStr, sizeof(stockStr), "Disponible: %d", node->product.qte);

                    createText(startLine, 
                        listStartY + (displayedCount * itemHeight), 
                        node->product.name, COLOR_WHITE
                    );

                    if (node->product.qte == 0) {
                        createText(
                            startLine + INPUT_WIDTH + 3, 
                            listStartY + (displayedCount * itemHeight), 
                            stockStr, COLOR_BRIGHT_RED
                        );
                    } else {
                        createText(
                            startLine + INPUT_WIDTH + 3, 
                            listStartY + (displayedCount * itemHeight), 
                            stockStr, COLOR_BRIGHT_GREEN
                        );
                    }
                    
                    createText(
                        startLine + INPUT_WIDTH + 24, 
                        listStartY + (displayedCount * itemHeight), 
                        priceStr, COLOR_YELLOW
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


    // --- Boutons de Navigation ---
    int startBtnX = (columns - (15 + 2 + 15)) / 2;

    if (pageIndex > 0) createButton(startBtnX, rows - 5, 15, "Precedent", COLOR_GREEN, STYLE_DEFAULT, prevPage);
    else               createButton(startBtnX, rows - 5, 15, "Precedent", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);
    
    if (hasMore) createButton(startBtnX + 15 + 2, rows - 5, 15, "Suivant", COLOR_GREEN, STYLE_DEFAULT, nextPage);
    else         createButton(startBtnX + 15 + 2, rows - 5, 15, "Suivant", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);
      
}
