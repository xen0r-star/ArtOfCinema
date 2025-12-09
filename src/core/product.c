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

    char buffer[512];
    
    while(list != NULL){
        idProduct *tmpProduct = list->idPdt;
        int idTmp = tmpProduct->id;
        int qteFinal = tmpProduct->qte;

        rewind(file);
        long lineStart = 0;
        
        while (1) {
            lineStart = ftell(file);
            if (fgets(buffer, sizeof(buffer), file) == NULL) break;
            
            int idRead;
            if (sscanf(buffer, "%d", &idRead) == 1) {
                if (idTmp == idRead) {
                    char *firstPipe = strchr(buffer, '|');
                    if (firstPipe) {
                        char *secondPipe = strchr(firstPipe + 1, '|');
                        if (secondPipe) {
                            long qteOffset = (secondPipe - buffer) + 1;
                            
                            fseek(file, lineStart + qteOffset, SEEK_SET);
                            
                            fprintf(file, "%05d", qteFinal);
                            
                            fflush(file);
                            
                            break;
                        }
                    }
                }
            }
        }
        
        list = list->next;
    }
    fclose(file);
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