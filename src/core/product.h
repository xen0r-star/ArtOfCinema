#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/product.h"
#include "../utils/screen.h"


int loadProducts();
int saveProducts(idProductList *idProductList);
ProductNode* getProductList();
Product* getProductById(int id);
int searchProductByName(const char *productName, const char *search);

#endif