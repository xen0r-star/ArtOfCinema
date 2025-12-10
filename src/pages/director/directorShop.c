#include "directorShop.h"

static int pageIndex = 0;
static ProductNode *WaitingProducts = NULL;
static int cooldown = 0;

static void addIdList(void *product){
    Product *pdt = product;
    int idP = pdt->id;
    int qteP = pdt->qte;

    ProductNode *curr = WaitingProducts;
    while (curr != NULL) {
        if (curr->product->id == idP) {
            curr->product->qte = qteP;
            return;
        }
        curr = curr->next;
    }

    ProductNode *newNode = malloc(sizeof(ProductNode));
    if (newNode) {
        Product *newPdt = malloc(sizeof(Product));
        newPdt->id = idP;
        newPdt->qte = qteP;
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
}

static void addQteProd(void *product){
    Product *pdt = product;
    int *value = &pdt->qte;
    if ((*value) + 1 > 999) {
        if (cooldown == 1) return;
        cooldown = 1;
        createText(ALIGN_CENTER , 12, _T("director.qte.err"), COLOR_RED);
        Sleep(1000);
        cooldown = 0;
    } else {
        (*value)++;
        addIdList(pdt);
    }
    setCurrentPage(PAGE_DIRECTOR_SHOP);
}

static void remQteProd(void *product){
    Product *pdt = product;
    int *value = &pdt->qte;
    if ((*value) - 1 < 0) {
        createText(ALIGN_CENTER , 12, _T("director.qte.errm"), COLOR_RED);
        Sleep(3000);
    } else {
        (*value)--;
        addIdList(pdt);
    }
    setCurrentPage(PAGE_DIRECTOR_SHOP);
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

        if (product) {
            char id[6], qte[6], price[11];

            snprintf(id, sizeof(id), "%5d", node->product->id);
            snprintf(qte, sizeof(qte), "%5d", node->product->qte);
            snprintf(price, sizeof(price), "%4f", node->product->price);

            createText(columns*0.12, listStartY + (i * itemHeight), id, COLOR_WHITE);
            createText(columns*0.20, listStartY + (i * itemHeight), node->product->name, COLOR_WHITE);
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

void showDirectorShopPage(){
    int columns, rows;
    sizeScreen(&columns, &rows);

    drawLogo((columns / 2) - (LOGO_WIDTH / 2), 1);
    drawFooter();
    buttonLanguage();

    createText(ALIGN_CENTER, 7, _T("director.s.lbl"), COLOR_GREEN);
    createText(ALIGN_CENTER, 9, _T("director.s.desc"), COLOR_WHITE);
    createDataButton(columns - 20, rows - 3, 20, _T("save"), COLOR_WHITE, STYLE_DEFAULT, saveProduct, WaitingProducts);

    createMenu(ALIGN_CENTER, 11, columns*0.8, COLOR_GREEN, STYLE_DEFAULT, "director.s.tbl", NULL, NULL, NULL);

    buttonBack(PAGE_DIRECTOR);

    initItem(columns, rows);        // Initialisation + affichage du stock
}