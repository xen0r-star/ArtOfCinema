#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ProductNode *productList = NULL;


int loadProducts() {
    FILE *file = fopen("data/products.csv", "r");
    if (file == NULL) return -1;

    char buffer[1024];
    fscanf(file, "%[^\n]\n", buffer); // Skip header

    
    Product product = {0};
    char name[50];
    float prix;
    int qte;
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