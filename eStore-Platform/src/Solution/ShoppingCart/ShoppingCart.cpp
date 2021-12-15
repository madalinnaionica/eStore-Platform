#include "ShoppingCart.h"

ShoppingCart::ShoppingCart()
{
	this->payMethod = "-";
}

ShoppingCart::ShoppingCart(const string &payMethod)
{
	this->payMethod = payMethod;
}

string &ShoppingCart::getPayMethod()
{
	return payMethod;
}

void ShoppingCart::setPayMethod(const string &payMethod)
{
	this->payMethod = payMethod;
}

void ShoppingCart::addProduct(int id, int quantity)
{
	shoppingCart.insert(pair<int, int>(id, quantity));
}

void ShoppingCart::raiseQuantity(int id, int quantity)
{
	map<int, int>::iterator quantity_risen;
	quantity_risen = shoppingCart.find(id);
	quantity_risen->second += quantity;
}

void ShoppingCart::lowerQuantity(int id, int quantity)
{
	map<int, int>::iterator quantity_descend;
	quantity_descend = shoppingCart.find(id);
	quantity_descend->second -= quantity;
}

int ShoppingCart::getQuantity(int productID)
{
	map<int, int>::iterator shoppingCart_it;
	shoppingCart_it = shoppingCart.find(productID); //daca produsul exista in cos il returnez, daca nu returnez -1
	if (shoppingCart_it != shoppingCart.end())
	{
		return shoppingCart_it->second;
	}
	else
	{
		return -1;
	}
}

void ShoppingCart::deleteProduct(int productID)
{
	shoppingCart.erase(productID);
}

map<int, int> &ShoppingCart::getShoppingCart()
{
	return shoppingCart;
}

void ShoppingCart::displayShoppingCart()
{
	if (this->shoppingCart.empty())
		cout << "Cosul este gol";
}

json ShoppingCart::toJSON()
{
	return json(*this);
}