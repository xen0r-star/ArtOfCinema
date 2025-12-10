#ifndef TYPE_PRODUCT_H
#define TYPE_PRODUCT_H

#define MAX_IDL 5
#define MAX_NAMEL 50
#define MAX_QTEL 5
#define MAX_PRICEL 10


typedef struct Product {
    int id;
    char *name;
    int qte;
    float price;
} Product;

typedef struct ProductNode {
    Product *product;
    struct ProductNode *next;
} ProductNode;

#endif