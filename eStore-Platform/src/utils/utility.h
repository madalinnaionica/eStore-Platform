#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "../Solution/Product/NonFoodProduct.h"
#include "../Solution/Product/FoodProduct.h"
#include "../Solution/Product/Product.h"
#include "../Solution/Product/ResealedProduct.h"
#include "../Solution/Product/ReturnedProduct.h"
#include "../Solution/User/User.h"

class Utility{

public:

  static bool compare_reasealed_products(ResealedProduct*, ResealedProduct*);
  static bool compare_food_products(FoodProduct*, FoodProduct*);
  static bool compare_user_id(User*, User*);

};