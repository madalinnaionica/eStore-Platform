#include "Product.h"
using namespace std;

Product::~Product() {}

bool Product::checkQuantity(int requestedQuantity)
{
	if (requestedQuantity <= this->quantity)
		return true;
	else
		return false;
}

Product::Product(const string &category, int id, const string &name, int quantity)
{
	this->category = category;
	this->id = id;
	this->name = name;
	this->quantity = quantity;
}

Product::Product(const Product &p)
{
	category = p.category;
	id = p.id;
	name = p.name;
	quantity = p.quantity;
}

Product::Product()
{
	category = "NULL";
	id = 0;
	name = "NULL";
	quantity = 0;
}

void Product::decreaseQuantity(int requestedQuantity)
{
	quantity -= requestedQuantity ;
}

void Product::increaseQuantity(int requestedQuantity)
{
	quantity += requestedQuantity;
}

void Product::setCategory(const string &category)
{
	this->category = category;
}

void Product::setId(int id)
{
	this->id = id;
}

void Product::setQuantity(int quantity)
{
	this->quantity = quantity;
}

void Product::setName(const string &)
{
	this->name = name;
}

string &Product::getCategory()
{
	return category;
}

int Product::getQuantity()
{
	return quantity;
}

int Product::getId()
{
	return id;
}

string &Product::getName()
{
	return name;
}

const Product &Product::operator=(const Product &a)
{
	category = a.category;
	id = a.id;
	name = a.name;
	quantity = a.quantity;
	return *this;
}

json Product::toJSON()
{
	return json(*this);
}
