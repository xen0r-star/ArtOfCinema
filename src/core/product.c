#include "product.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

static ProductNode *productListMain = NULL;

static bool initProduct = false;

int loadProducts() {
    if(initProduct) return 0;
    initProduct = true;
    
    FILE *file = fopen("data/products.dat", "r");
    if (file == NULL) return -1;

    int tempId, tempQte;
    float tempPrice;
    char tempName[50];

    ProductNode *tail = NULL;
    while (fscanf(file, "%5d|%50[^|]|%5d|%10f",
           &tempId, tempName, &tempQte, &tempPrice) == 4) {
        
        Product *newProduct = calloc(1, sizeof(Product));

        newProduct->id = tempId;
        newProduct->qte = tempQte;
        newProduct->price = tempPrice;
        newProduct->name = strdup(tempName);

        // Create and append Node
        ProductNode *newNode = malloc(sizeof(ProductNode));
        if (newNode) {
            newNode->product = newProduct;
            newNode->next = NULL;

            if (productListMain == NULL) {
                productListMain = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    fclose(file);
    return 0;
}

int saveProducts(ProductNode *list) {
    FILE *file = fopen("data/products.dat", "r+");
    if (file == NULL) return -1;

    char buffer[512];
    while(list != NULL){
        Product *tmpProduct = list->product;

        rewind(file);
        long lineStart = 0;
        
        while (1) {
            lineStart = ftell(file);
            if (fgets(buffer, sizeof(buffer), file) == NULL) break;
            
            int idRead;
            if (sscanf(buffer, "%d", &idRead) == 1) {
                if (tmpProduct->id == idRead) {
                    char *firstPipe = strchr(buffer, '|');
                    if (firstPipe) {
                        char *secondPipe = strchr(firstPipe + 1, '|');
                        if (secondPipe) {
                            long qteOffset = (secondPipe - buffer) + 1;
                            
                            fseek(file, lineStart + qteOffset, SEEK_SET);
                            
                            ProductNode *curr = productListMain;
                            while (curr != NULL) {
                                if (curr->product->id == tmpProduct->id) {
                                    curr->product->qte = tmpProduct->qte;
                                    break;
                                }
                                curr = curr->next;
                            }
                            
                            fprintf(file, "%05d", tmpProduct->qte);
                            
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

int saveAllProducts(ProductNode *list) {
    FILE *file = fopen("data/products.dat", "r+");
    if (file == NULL) return -1;

    char buffer[512];
    
    while(list != NULL){
        Product *tmpProduct = list->product;
        
        rewind(file);
        long lineStart = 0;
        
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            lineStart = ftell(file) - strlen(buffer);
            int idRead;

            if (sscanf(buffer, "%d", &idRead) == 1) {
                if (tmpProduct->id == idRead) {
                    char *firstPipe = strchr(buffer, '|');
                    if (firstPipe) {
                        long startWriteOffset = (firstPipe - buffer) +1;
                        fseek(file, lineStart + startWriteOffset, SEEK_SET);
                            
                        fprintf(file, "%-30s|%05d|%8.2f\n", tmpProduct->name, tmpProduct->qte, tmpProduct->price);
                        fflush(file);
                        break;
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
    return productListMain;
}

Product* getProductById(int id) {
    ProductNode *current = productListMain;
    while (current != NULL) {
        if (current->product->id == id) {
            return current->product;
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