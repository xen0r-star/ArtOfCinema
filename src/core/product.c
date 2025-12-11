#include "product.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

static ProductNode *productListMain = NULL;
static ProductNode *tail = NULL;

static bool initProduct = false;

int loadProducts() {
    if(initProduct) return 0;
    initProduct = true;
    
    FILE *file = fopen("data/products.dat", "r");
    if (file == NULL) return 0;

    int tempId, tempQte;
    float tempPrice;
    char tempName[50];

    while (fscanf(file, "%5d;%49[^;];%5d;%10f",
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
    return 1;
}

int saveProducts(ProductNode *list) {
    FILE *file = fopen("data/products.dat", "r+");
    if (file == NULL) return 0;

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
    return 1;
}

int saveAllProducts(ProductNode *list) {
    FILE *file = fopen("data/products.dat", "r+");
    if (file == NULL) return 0;

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
    return 1;
}

int addProduct(ProductNode *list) { // ⚠️ VERIF DES ENTREES A FAIRE AU NIVEAU DU "FORM"
    FILE *file = fopen("data/products.dat", "a");
    if (file == NULL) return 0;

    while(list != NULL){
        Product *tmpProduct = list->product;
        fprintf(file, "%05d;%s;%05d;%.2f\n", tmpProduct->id, tmpProduct->name, tmpProduct->qte, tmpProduct->price);
        
        // Create and append Node
        ProductNode *newNode = malloc(sizeof(ProductNode));
        if (newNode) {
            newNode->product = tmpProduct;
            newNode->next = NULL;

            if (productListMain == NULL) {
                productListMain = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        list = list->next;
    }
    fclose(file);
    return 1;
}

void deleteProduct(void *product){
    Product *pd = product; 
    if (pd == NULL) return;

    FILE *file = fopen("data/products.dat", "r");
    FILE *fileTemp = fopen("data/productsTmp.dat", "w");
    if (file == NULL || fileTemp == NULL) return;
    int targetId = pd->id;

    ProductNode *current = productListMain;
    ProductNode  *prev = NULL;

    while (current != NULL) {
        if (current->product->id == targetId) {
            if (prev == NULL) {
                productListMain = current->next;
            } else {
                prev->next = current->next;
            }
            int id, qte;
            float price;
            char name[50];
            while (fscanf(file, "%5d;%49[^;];%5d;%10f\n", 
                            &id, name, &qte, &price) == 4) {

                if (targetId == id) {
                    continue;
                }
                fprintf(fileTemp, "%05d;%s;%05d;%.2f\n", id, name, qte, price);
            }
            fclose(file);
            fclose(fileTemp);
            remove("data/products.dat");
            rename("data/productsTmp.dat", "data/products.dat");
            free(current);
            setCurrentPage(PAGE_DIRECTOR_SHOP);
            return;

        }
        prev = current;
        current = current->next;
    }
    cursor(2, 2);
    fclose(file);
    fclose(fileTemp);
    setCurrentPage(PAGE_DIRECTOR_FILM);
    return;
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