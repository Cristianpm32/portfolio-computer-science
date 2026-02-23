#include <iostream>
#include "FoodPackage.h"

using namespace std;

FoodPackage::FoodPackage(string date_time, string product_id, int amount, float price)
{
    this->date_time = date_time;
    this->product_id = product_id;
    this->amount = amount;
    this->price = price;
}
FoodPackage::FoodPackage(const FoodPackage &orig)
{
    date_time = orig.date_time;
    product_id = orig.product_id;
    amount = orig.amount;
    price = orig.price;
}
void FoodPackage::print() const
{
    cout << this->date_time << ", " << this->product_id <<  ", " << this->amount << ", " << this->price; 
}
string FoodPackage::toString() const
{
    string info = "Data: " + this->date_time + ", Identificador: " + this->product_id + ", Quantitat: " + to_string(this->amount) + ", Preu:" + to_string(this->price);
    return info;
}