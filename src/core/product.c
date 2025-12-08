#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static ProductNode *productList = NULL;


int loadProducts() {
    FILE *file = fopen("data/products.csv", "r");
    if (file == NULL) return -1;

    char buffer[1024];
    fscanf(file, "%[^\n]\n", buffer); // Skip header

    
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