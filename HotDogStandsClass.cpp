#ifndef HOTDOG_STAND_CLASS_CPP
#define HOTDOG_STAND_CLASS_CPP

#include "HotDogStandsClass.h"
#include <iomanip>

using namespace std;

unsigned HotDogStandsClass::globalSoldCountUns = 0;

void HotDogStandsClass::hotDogsBuyUns(unsigned count) {
	//$$


}
ostream& operator<<(ostream& os, const HotDogStandsClass& obj) {
    os << "Stand Id: " << obj.identificationStr << endl
        << "Address: " << obj.addressStr << endl
        << "Price: " <<fixed << setprecision(2)<< obj.hotdogPriceFl <<  endl
        << "Inventory: " << obj.inventoryAmountUns << endl
        << "Store Sold: " << obj.soldAmountUns << " at $" << obj.hotdogPriceFl << " ea." << endl;
    return os;
}
#endif