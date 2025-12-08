#ifndef TYPE_PRODUCT_H
#define TYPE_PRODUCT_H


typedef struct Product {
    int id;
    char *name;
    int qte;
    float price;
} Product;

typedef struct ProductNode {
    Product product;
    struct ProductNode *next;
} ProductNode;

#endif