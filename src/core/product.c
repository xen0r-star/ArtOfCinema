#include "product.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

static ProductNode *productList = NULL;

static bool initProduct = false;

int loadProducts() {
    if(initProduct) return 0;
    initProduct = true;
    
    FILE *file = fopen("data/products.csv", "r");
    if (file == NULL) return -1;
    
    // char buffer[1024]; ⚠️
    // fscanf(file, "%[^\n]\n", buffer); // Skip header ⚠️

    Product product = {0};
    char name[50];
    ProductNode *tail = NULL;
    while (fscanf(file, "%5d|%49[^|]|%5d|%10f",
            &product.id, name, &product.qte, &product.price) == 4) {
        
        product.name = strdup(name);

        // Create and append Node
        ProductNode *newNode = malloc(sizeof(ProductNode));
        if (newNode) {
            newNode->product = product;
            newNode->next = NULL;

            if (productList == NULL) {
                productList = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }

        // Reset product struct for next iteration
        memset(&product, 0, sizeof(Product));
    }

    fclose(file);
    return 0;
}

int saveProducts(idProductList *list) {
    FILE *file = fopen("data/products.csv", "r+");
    if (file == NULL) return -1;

    cursor(2, 2);
    
    while(list != NULL){
        idProduct *tmpProduct = list->idPdt;
        int idTmp = tmpProduct->id;
        int qteFinal = tmpProduct->qte;

        int idRead = -1;
        int line = 1;

        rewind(file);
        // Sleep(5000);
        printf("Recherche de l'ID %d...", idTmp);
        // Sleep(5000);
        while (fscanf(file, "%5d %*[^\n]\n", &idRead) ==  1) {
            // Sleep(5000);
            printf("Comparaison de %05d et %05d", idTmp, idRead);
            // Sleep(5000);
            if (idTmp == idRead) {
                long pos = ftell(file);
                fseek(file, pos - 12, SEEK_SET);
                fprintf(file, "%05d", qteFinal);
                // Sleep(5000);
                printf("ID %05d trouvé à la ligne %d remplacer par QTE : %d", idTmp, line, qteFinal);                
                // Sleep(5000);
                break;
            }
            line++;
        }
        printf("Sortie de la recherche");
        // Sleep(5000);
        idProductList *toDelete = list;
        /* if (list->next != NULL){
            Sleep(5000);
            cursor(2, 2);
            printf("PAS DE NEXT");
            Sleep(3000);
        } else {
            Sleep(5000);
            cursor(2, 2);
            printf("NEXT PRESENT");
            Sleep(3000);
        } */
        list = list->next;

        // if (toDelete->idPdt != NULL)
            // free(toDelete->idPdt);
        
        // free(toDelete);
    }
    fclose(file);
    if (list != NULL) list = NULL;
    return 0;
}

ProductNode* getProductList() {
    return productList;
}

Product* getProductById(int id) {
    ProductNode *current = productList;
    while (current != NULL) {
        if (current->product.id == id) {
            return &current->product;
        }
        current = current->next;
    }
    return NULL;
}

int searchProductByName(const char *productName, const char *search) {
    if (!search || strlen(search) == 0) return 1;
    if (!productName) return 0;

    char h[512], n[512];
    strncpy(h, productName, 511); h[511] = 0;
    strncpy(n, search, 511); n[511] = 0;

    for(int i = 0; h[i]; i++) h[i] = tolower(h[i]);
    for(int i = 0; n[i]; i++) n[i] = tolower(n[i]);

    return strstr(h, n) != NULL;
}