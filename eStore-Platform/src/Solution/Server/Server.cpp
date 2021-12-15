#include "Server.h"

using namespace std;

/* NU MODIFICATI */
Server::Server() {}

/* NU MODIFICATI */
Server *Server::GetInstance()
{
	if (!instance)
	{
		instance = new Server;
	}

	return instance;
}

/* NU MODIFICATI */
Server::~Server()
{
	if (instance != NULL)
		instance = NULL;

	if (!__UserID__ProductsCart__.empty())
		__UserID__ProductsCart__.clear();
}

void Server::set__UserID__ProductsCart__()
{
	for (list<User *>::iterator it = usr.begin(); it != usr.end(); it++)
	{
		int empty_user = (*it)->getUserID();						 //stochez id-ul userilor
		ShoppingCart *shop_cart = new ShoppingCart;					 // creez un obiect de tip ShoppingCart nou
		pair<int, ShoppingCart *> empty_cart(empty_user, shop_cart); //adaug in map
		__UserID__ProductsCart__.insert(empty_cart);
	}
}

list<Product *> &Server::getProductsList()
{
	return prod;
}

list<User *> &Server::getUsersList()
{
	return usr;
}

map<int, ShoppingCart *> Server::get__UserID__ProductsCart__()
{
	return __UserID__ProductsCart__;
}

bool Server::requestAddProduct(int userID, int productID, int quantity)
{
	if (quantity <= 0) //daca cantitatea nu exista
	{
		return false;
	}

	User *current_user = nullptr;
	for (list<User *>::iterator it = usr.begin(); it != usr.end(); it++)
	{
		if (userID == (*it)->getUserID()) // verific daca exista userid
		{
			current_user = (*it);
			break;
		}
	}

	if (current_user == nullptr) // daca nu exita userul
	{
		return false;
	}

	Product *current_product = nullptr;
	for (list<Product *>::iterator it = prod.begin(); it != prod.end(); it++) //iterez prin lista de produse
	{
		if (productID == (*it)->getId()) //verific daca exista produsul
		{
			current_product = (*it);
			break;
		}
	}
	if (current_product == nullptr) //cazul un care nu exista produsul
	{
		return false;
	}
	//cazurile pentru cantitati
	int cart_quantity = __UserID__ProductsCart__[userID]->getQuantity(productID);
	if (current_product->checkQuantity(quantity) == false)
	{
		return false;
	}
	if (cart_quantity == -1) //daca nu exista produsul in cosul de cumparaturi
	{

		__UserID__ProductsCart__[userID]->addProduct(productID, quantity); //adaug produsul
		current_product->decreaseQuantity(quantity);					   //modific cantitatea din produsului pe server
		return true;
	}
	else //daca produsul exista in cosul de cumparaturi
	{

		__UserID__ProductsCart__[userID]->raiseQuantity(productID, quantity); //cresc cantitatea
		current_product->decreaseQuantity(quantity);						  //modific cantitatea din produsului pe server
		return true;
	}

	return false;
}

bool Server::requestDeleteProduct(int userID, int productID, int quantity)
{
	if (quantity <= 0) // daca cantitatea nu exista
	{
		return false;
	}

	User *current_user = nullptr;
	for (list<User *>::iterator it = usr.begin(); it != usr.end(); it++) //verific daca exista userul
	{
		if (userID == (*it)->getUserID())
		{
			current_user = (*it);
			break;
		}
	}
	if (current_user == nullptr) // in cazul in care nu exista
	{
		return false;
	}

	Product *current_product = nullptr;
	for (list<Product *>::iterator it = prod.begin(); it != prod.end(); it++)
	{
		if (productID == (*it)->getId()) //verific daca exista produsul
		{
			current_product = (*it);
			break;
		}
	}
	if (current_product == nullptr) //in cazul in care nu exista
	{
		return false;
	}
	//cazurile pentru cantitati
	int cart_quantity = __UserID__ProductsCart__[userID]->getQuantity(productID);
	if (cart_quantity == -1) //daca cantitatea nu exista
	{
		return false;
	}

	else

	{
		if (quantity < cart_quantity) //daca vreau sa sterg o cantitate mai mica decat cea existenta in cos
		{
			__UserID__ProductsCart__[userID]->lowerQuantity(productID, quantity); //scad cantitatea
			current_product->increaseQuantity(quantity);						  // actualizez in server
			return true;
		}
		if (quantity >= cart_quantity) // daca vreau sa sterg o cantitate mai mare sau egala cu cea din cos
		{
			current_product->increaseQuantity(cart_quantity);			// adaug in server cantitatea initiala din cos
			__UserID__ProductsCart__[userID]->deleteProduct(productID); // sterg produsul din cos

			return true;
		}
	}

	return false;
}

/* NU MODIFICATI */
void Server::populateProducts(const json &input)
{
	prod = ObjectFactory::getProductList(input["shoppingCart"]);
}

/* NU MODIFICATI */
void Server::populateUsers(const json &input)
{
	usr = ObjectFactory::getUserList(input["useri"]);
}