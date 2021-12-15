#include "utility.h"

bool Utility::compare_reasealed_products(ResealedProduct* price1, ResealedProduct* price2)
{   
    return price1->getPrice() < price2->getPrice();
}

bool Utility::compare_food_products(FoodProduct* food1, FoodProduct* food2)
{
    if(food1->getName() < food2->getName())
    return true;
    if(food1->getName() > food2->getName())
    return false;
    if(food1->getCountryOfOrigin() < food2->getCountryOfOrigin())
    return true;
    if(food1->getCountryOfOrigin() > food2->getCountryOfOrigin())
    return false;
    if(food1->getLeiPerKg() < food2->getLeiPerKg())
    return true;
    if(food1->getLeiPerKg() > food2->getLeiPerKg())
    return false;
}

bool Utility::compare_user_id(User* user1, User* user2)
{
    return user1->getUserID() < user2->getUserID();
}
