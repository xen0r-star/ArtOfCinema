#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/product.h"


int loadProducts();
ProductNode* getProductList();
Product* getProductById(int id);

#endif