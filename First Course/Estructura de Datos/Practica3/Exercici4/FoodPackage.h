#ifndef FOODPACKAGE_H
#define FOODPACKAGE_H
#include <iostream>
using namespace std;
class FoodPackage
{
public:
    // Constructors

    FoodPackage(string date_time, string product_id, int amount, float price); // O(1)
    FoodPackage(const FoodPackage &orig);                                      // O(1)
    void print() const;                                                        // O(1)
    string toString() const;                                                   // O(1)

    // Consultors

    string getDateTime() const // O(1)
    {
        return this->date_time;
    }
    string getProduct_id() const // O(1)
    {
        return this->product_id;
    }
    int getAmount() const // O(1)
    {
        return this->amount;
    }
    float getPrice() const // O(1)
    {
        return this->price;
    }

    // Modificadors

    void setDateTime(string date_time) // O(1)
    {
        this->date_time = date_time;
    }

    void setProduct_id(string product_id) // O(1)
    {
        this->product_id = product_id;
    }
    void setAmount(int amount) // O(1)
    {
        this->amount = amount;
    }

    void setPrice(int price) // O(1)
    {
        this->price = price;
    }

private:
    string date_time;
    string product_id;
    int amount;
    float price;
};
#endif