#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/product.h"
#include "../utils/screen.h"
#include "../main.h"

int loadProducts();
int saveProducts(ProductNode *list);
int addProduct(ProductNode *list);
void deleteProduct(void *product);

ProductNode* getProductList();
Product* getProductById(int id);
int searchProductByName(const char *productName, const char *search);

#endif