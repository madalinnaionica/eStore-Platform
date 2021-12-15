#include "QuerySolver.h"

using namespace std;

/* NU MODIFICATI */
QuerySolver::QuerySolver()
{
  server = Server::GetInstance();
}

/* NU MODIFICATI */
QuerySolver::~QuerySolver()
{
  if (server != nullptr)
  {
    server = nullptr;
  }
}

list<Product *> QuerySolver::Query_3a()
{

  list<Product *> discounted_espressors;       //se creaza o lista de produse in care voi stoca ulterior toate produsele din server
  list<Product *> discounted_espressors_empty; // se creeaza o lista goala de espressoare in care voi stoca produsele ce indeplinesc conditiile cerute
  discounted_espressors = server->getProductsList();
  for (list<Product *>::iterator it = discounted_espressors.begin(); it != discounted_espressors.end(); it++)
  {
    if ((*it)->getCategory() == "espressor" && (*it)->getProductType() == "REDUS") //testez daca produsele fac parte din categoria espressoarelor si sunr si reduse
    {
      discounted_espressors_empty.push_back(*it); //daca acestea indeplinesc conditiile le adaug in lista
    }
  }
  return discounted_espressors_empty;
}

list<User *> QuerySolver::Query_3b()
{
  //analog cerintei 3a
  list<User *> nonpremium_users;       //se creeaza o lista de useri in care stochez ulterior userii din server
  list<User *> nonpremium_users_empty; // se creeaza o lista goala de useri nonpremium care va fi populata in cazul in care userii indepilinesc cerintele
  nonpremium_users = server->getUsersList();
  for (list<User *>::iterator it = nonpremium_users.begin(); it != nonpremium_users.end(); it++)
  {
    if ((*it)->getTransportCost() <= 11.5 && (*it)->getUserType() == "NONPREMIUM") //testez daca userii indeplinesc cerintele
    {
      nonpremium_users_empty.push_back(*it); //populez lista
    }
  }
  return nonpremium_users_empty;
}

list<Product *> QuerySolver::Query_3c()
{
  //abordare destul de asemanatoare cu 3a si 3b
  list<Product *> resealed_products_empty; //se creaza o lista de produse  noua in care stochez ulterior produsele din server
  list<Product *> resealed_products;
  resealed_products = server->getProductsList();                                                      //stocam in lista de produse toate produsele
  for (list<Product *>::iterator it = resealed_products.begin(); it != resealed_products.end(); it++) //iteram prin lista
  {
    if ((*it)->getProductType() == "RESIGILAT") //veridicam daca produsul este resigilat
    {
      resealed_products_empty.push_back(*it); //stocam in lista produsele resigilate
    }
  }

  list<ResealedProduct *> resealed_products_empty0; // se creaza o lista de produse resigilate noua
  for (list<Product *>::iterator it = resealed_products_empty.begin(); it != resealed_products_empty.end(); it++)
  {
    ResealedProduct *x = dynamic_cast<ResealedProduct *>(*it); //se face dynamic cast pentru a putea avea acces la metoda getReason
    if (x != nullptr)
    {
      if ((x)->getReason() == "lipsa_accesorii") //verificam daca produsul are ca si caracteristica lipsa accesorii
      {
        resealed_products_empty0.push_back(x); //stocam obiectele in lista de produse resigilate
      }
    }
  }

  resealed_products_empty0.sort(Utility::compare_reasealed_products); //se face sortare in functie de pret din clasa utility

  list<Product *> resealed_products_empty1;
  for (list<ResealedProduct *>::iterator it = resealed_products_empty0.begin(); it != resealed_products_empty0.end(); it++)
  {
    resealed_products_empty1.push_back(*it);
  }

  return resealed_products_empty1; //returnam o lista de produse
}

list<Product *> QuerySolver::Query_3d()
{
  list<Product *> food_products_empty; //se creaza o lista de produse  noua
  list<Product *> food_products;
  food_products = server->getProductsList();                                                  //stocam in lista de produse toate produsele
  for (list<Product *>::iterator it = food_products.begin(); it != food_products.end(); it++) //iteram prin lista
  {
    if ((*it)->getProductType() == "ALIMENTAR") //veridicam daca produsul este alimentar
    {
      food_products_empty.push_back(*it); //stocam in lista produsele alimentare
    }
  }

  list<FoodProduct *> food_products_empty0;
  for (list<Product *>::iterator it = food_products_empty.begin(); it != food_products_empty.end(); it++)
  {
    FoodProduct *x = dynamic_cast<FoodProduct *>(*it); //se face dynamic cast pentru a transforma lista de produse in lista de FoodProducts pentru a i se face sortarea
    if (x != nullptr)
    {
      food_products_empty0.push_back(x);
    }
  }

  food_products_empty0.sort(Utility::compare_food_products); //se face sortarea a doua obiecte de tip FoodProduct

  list<Product *> food_products_empty1;
  for (list<FoodProduct *>::iterator it = food_products_empty0.begin(); it != food_products_empty0.end(); it++)
  {
    food_products_empty1.push_back(*it);
  }

  return food_products_empty1; //se returneaza o lista de produse
}

list<User *> QuerySolver::Query_3e()
{
  list<User *> users_list;
  users_list = server->getUsersList(); //am creat o lista de useri cu userii din server
  map<string, int> users_map;          // se creeaza un map unde voi stoca uletrior judetul si userii, cu id-ul lor
  for (list<User *>::iterator ip = users_list.begin(); ip != users_list.end(); ip++)
  {
    users_map.insert(pair<string, int>((*ip)->getDeliveryData().getCounty(), (*ip)->getUserID())); //am pus in map judetul si userii
  }

  map<string, int> county_map;                                                       //se creaza un map de frecventa
  for (list<User *>::iterator it = users_list.begin(); it != users_list.end(); it++) //iterez prin lista de useri
  {
    string county = (*it)->getDeliveryData().getCounty(); // imi stochez intr-un string judetul, pentru comparare
    if (county_map.find(county) == county_map.end())      //daca nu gasesc judetul respectiv se creeaza un nou entry
    {
      county_map.insert(pair<string, int>(county, 1));
    }
    else
    {
      county_map[county] += 1; //daca se gaseste incrementez cu 1
    }
  }

  //determin judetul cu numarul maxim de useri
  int max_users = 0; //declar un numar maxim de useri pentru a compara
  string max_county_users;
  for (map<string, int>::iterator ip = county_map.begin(); ip != county_map.end(); ip++) //parcurg mapul creat anterior si caut maximul (algoritm normal)
  {
    if (ip->second > max_users)
    {
      max_users = ip->second;
      max_county_users = ip->first;
    }
  }

  list<User *> empty_users_list;
  for (list<User *>::iterator it = users_list.begin(); it != users_list.end(); it++) //parcurg lista de useri
  {
    if ((*it)->getBillingData().getBlock() == "-" && (*it)->getDeliveryData().getBlock() == "-") //testez daca locuiesc la casa
    {
      if ((*it)->getDeliveryData().getCounty().compare(max_county_users) == 0) //si daca locuiesc in judetul cu cei mai multi utilizatori
      {
        empty_users_list.push_back(*it);
      }
    }
  }
  empty_users_list.sort(Utility::compare_user_id); //sortez dupa id
  return empty_users_list;
}

list<User *> QuerySolver::Query_3f()
{
  list<Product *> product_list;
  product_list = server->getProductsList(); //lista de produse din server

  list<User *> empty_users_list;
  list<User *> users_list;
  users_list = server->getUsersList(); //lista de useri din server
  for (list<User *>::iterator it = users_list.begin(); it != users_list.end(); it++)
  {
    if ((*it)->getUserType() == "PREMIUM") //testez daca sunt premium
    {
      empty_users_list.push_back(*it); //populez lista cu useri premium
    }
  }

  list<User *> empty_premium_user; // se creaza o lista de useri premium noua
  for (list<User *>::iterator it = empty_users_list.begin(); it != empty_users_list.end(); it++)
  {
    PremiumUser *x = dynamic_cast<PremiumUser *>(*it); // se face dynamic cast pentru a accesa metoda getDiscounts
    for (map<int, int>::iterator ip = (x)->getDiscounts().begin(); ip != (x)->getDiscounts().end(); ip++)
    {
      int id_product = ip->first;                    // stochez id-ul produsului
      string id_string = std::to_string(id_product); // transfrom id-ul int in string pentru verificare
      bool found = false;
      for (list<Product *>::iterator finder = product_list.begin(); finder != product_list.end(); finder++)
      {
        if (id_product == (*finder)->getId()) //daca id-ul din map coincide cu id-ul din lista de pe server
        {
          found = true; // daca da, ma opresc din cautare
          break;
        }
      }
      if (found == true && (id_string.at(0) == '3' || id_string.at(0) == '5' || id_string.at(0) == '2' || id_string.at(0) == '4') && (id_string.at(1) == '1' || id_string.at(1) == '6'))
      { // pentru ca orice produs poate fi redus am considerat ca acesta poate fi fie nelimentar, fie redus, fie resigilat, fie returnat + cea de-a doua conditie pentru a fi telefon sau imprimanta
        empty_premium_user.push_back(*it);
        break; // daca am gasit populez lista si ma opresc din cautare
      }
    }
  }
  empty_premium_user.sort(Utility::compare_user_id);
  return empty_premium_user;
}
