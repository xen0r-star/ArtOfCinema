#include "directorShop.h"

static int pageIndex = 0;
static ProductNode *WaitingProducts = NULL;

static void addInList(Product *product, int calcul) {
    Product *pdt = product;
    int idP = pdt->id;

    ProductNode *curr = WaitingProducts;
    while (curr != NULL) {
        if (curr->product->id == idP) {
            if (curr->product->qte + calcul > 999) {
                createText(ALIGN_CENTER , 10, _T("director.qte.errp"), COLOR_RED);
                Sleep(1000);
                setCurrentPage(PAGE_DIRECTOR_SHOP);
                return;
            }
            if (curr->product->qte + calcul < 0) {
                createText(ALIGN_CENTER , 12, _T("director.qte.errm"), COLOR_RED);
                Sleep(1000);
                setCurrentPage(PAGE_DIRECTOR_SHOP);
                return;
            }

            curr->product->qte += calcul;

            setCurrentPage(PAGE_DIRECTOR_SHOP);
            return;
        }
        curr = curr->next;
    }
    setCurrentPage(PAGE_DIRECTOR_SHOP);
}

static void addQteProd(void *product){
    addInList(product, +1);
}

static void remQteProd(void *product){
    addInList(product, -1);
}

static void advancedProd(void *test){
    int *value = test;
    value = value + 0;
}

static void prevPage(){
    if (pageIndex > 0){
        pageIndex--;
        setCurrentPage(PAGE_DIRECTOR_SHOP);
    }
}

static void nextPage(){
    pageIndex++;
    setCurrentPage(PAGE_DIRECTOR_SHOP);
}

static void initItem(int columns, int rows){
    int listStartY = 15;
    int itemHeight = 3;
    int maxItems = (rows - 3 - listStartY) / itemHeight;
    if (maxItems < 1) maxItems = 1;

    ProductNode* node = getProductList();

    int skipCount = pageIndex * maxItems;
    int skipped = 0;

    while (node != NULL && skipped < skipCount){
        node = node->next;
        skipped++;
    }

    int i = 0;
    while (i < maxItems && node != NULL){
        Product *product = getProductById(node->product->id);
        int final_qte;
        if (product) {
            char id[11], qte[8], price[11];
            /* BETA */
            ProductNode *curr = WaitingProducts;
            while (curr != NULL) {
                if (curr->product->id == node->product->id) {
                    final_qte = curr->product->qte;
                    break;
                }
                curr = curr->next;
            }

            if (curr == NULL) {
                ProductNode *newNode = malloc(sizeof(ProductNode));
                if (newNode) {
                    Product *newPdt = malloc(sizeof(Product));
                    newPdt->id = node->product->id;
                    newPdt->qte = node->product->qte;
                    newNode->product = newPdt;
                    newNode->next = NULL;

                    if (WaitingProducts == NULL) {
                        WaitingProducts = newNode;
                        
                    } else {
                        ProductNode *temp = WaitingProducts;
                        while(temp->next != NULL) {
                            temp = temp->next; 
                        }
                        temp->next = newNode;
                    }
                }
                final_qte = node->product->qte;
            }
            /* BETA */


            snprintf(id, sizeof(id), "ID : %05d", node->product->id);
            snprintf(qte, sizeof(qte), "x%-5d", final_qte);
            snprintf(price, sizeof(price), "%8.2f E", node->product->price);

            createText(columns*0.12, listStartY + (i * itemHeight), id, COLOR_WHITE);
            createText(columns*0.25, listStartY + (i * itemHeight), node->product->name, COLOR_WHITE);
            createText(columns*0.45, listStartY + (i * itemHeight), qte, COLOR_WHITE);
            createText(columns*0.55, listStartY + (i * itemHeight), price, COLOR_WHITE);
            createDataButton(columns*0.75, listStartY + (i * itemHeight) - 1, 5, "+", COLOR_GREEN, STYLE_DEFAULT, addQteProd, node->product);
            createDataButton(columns*0.80, listStartY + (i * itemHeight) - 1, 5, "-", COLOR_RED, STYLE_DEFAULT, remQteProd, node->product);
            createDataButton(columns*0.85, listStartY + (i * itemHeight) - 1, 5, "...", COLOR_BLUE, STYLE_DEFAULT, advancedProd, node->product);
            // DANS "..." AJOUTER POSSIIBILITE DE RESERVER DE LA NOURRITURE
        }
        i++;
        node = node->next;
    }

    int startBtnX = (columns - (32)) / 2;
    if (pageIndex > 0)
        createButton(startBtnX, rows - 3, 15, "Precedent", COLOR_GREEN, STYLE_DEFAULT, prevPage);
    else
        createButton(startBtnX, rows - 3, 15, "Precedent", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);

    if (node != NULL)
        createButton(startBtnX + 17, rows - 3, 15, "Suivant", COLOR_GREEN, STYLE_DEFAULT, nextPage);
    else
        createButton(startBtnX + 17, rows - 3, 15, "Suivant", COLOR_BRIGHT_BLACK, STYLE_DEFAULT, NULL);

}

static void showReservF(){

}

static void skipWaitingSave(void *val) {
    int value = *((int *)val);
    if (value == 0) {
        setCurrentPage(PAGE_DIRECTOR_SHOP);
        return;
    }
    setCurrentPage(PAGE_DIRECTOR);      
}

static void verifyReturnSave() {
    resetPage();
    int columns, rows;
    sizeScreen(&columns, &rows);
    int VRAI = 1, FAUX = 0;
    if (WaitingProducts != NULL) {
        drawLogo((columns / 2) - (LOGO_WIDTH / 2), 1);
        drawFooter();
        buttonLanguage();

        createText(ALIGN_CENTER, ALIGN_CENTER, "Etes-vous sure de quitter sans sauvegarder ?", COLOR_CYAN);
        createDataButton(columns*0.4, rows*0.2, 15, "Non", COLOR_RED, STYLE_DEFAULT, skipWaitingSave, &FAUX);
        createDataButton(columns*0.6, rows*0.2, 15, "Oui", COLOR_GREEN, STYLE_DEFAULT, skipWaitingSave, &VRAI);
        WaitingProducts = NULL;
        return;
    }
    setCurrentPage(PAGE_DIRECTOR);
}

static void forceSave() {
    saveProducts(WaitingProducts);
    WaitingProducts = NULL;
    setCurrentPage(PAGE_DIRECTOR);
}

void showDirectorShopPage(){
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 1);
    drawFooter();
    buttonLanguage();

    createText(ALIGN_CENTER, 7, _T("director.s.lbl"), COLOR_GREEN);
    createText(ALIGN_CENTER, 9, _T("director.s.desc"), COLOR_WHITE);
    createButton(columns - 20, rows - 3, 20, _T("save"), COLOR_WHITE, STYLE_DEFAULT, forceSave);

    createMenu(ALIGN_CENTER, 11, columns*0.8, COLOR_GREEN, STYLE_DEFAULT, "director.s.tbl", NULL, NULL, NULL);

    createButton(1, ALIGN_TOP, 6, _T("return"), COLOR_RED, STYLE_BORDERLESS, verifyReturnSave);
    // buttonBack(PAGE_DIRECTOR);

    initItem(columns, rows);        // Initialisation + affichage du stock
}