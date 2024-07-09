/*a program that stocks hotdogs for sale, sells them and stores the amount sold globally and at each store*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "HotDogStandsClass.h"
#include "TransactionsClass.h"

using namespace std;

int main() {
    string address, line, tempString;
    float price;
    unsigned inventory, soldAmount;
    fstream infoHotdog("infoHotDogStands.txt");
    
    int HotdogStandFileCount = 0;

    while (getline(infoHotdog, line)) {
        HotdogStandFileCount++;
    }
    HotDogStandsClass* HotdogStand = new HotDogStandsClass[HotdogStandFileCount];

    infoHotdog.clear(); // Clear the end-of-file flag
    infoHotdog.seekg(0, ios::beg);
    
    int i = 0;
    for (int i = 0; i < HotdogStandFileCount; i++) {
        getline(infoHotdog, line);
        stringstream ss(line);

        getline(ss, tempString, ',');
        HotdogStand[i].setIdStr(tempString);

        getline(ss, address, ',');
        HotdogStand[i].setAddressStr(address);

        getline(ss, tempString, ',');
        price = stof(tempString);
        HotdogStand[i].setPriceFl(price);

        getline(ss, tempString, ',');
        inventory = stof(tempString);
        HotdogStand[i].setInventoryAmountUns(inventory);

        getline(ss, tempString, ',');
        soldAmount = stoi(tempString);
        HotdogStand[i].setSoldAmountUns(soldAmount);
    }
    fstream InfoGlobal("infoGlobalSold.txt");

    InfoGlobal >> HotdogStand->globalSoldCountUns;


    

    for (int j = 0; j < HotdogStandFileCount; j++) {
        cout << HotdogStand[j];
        cout << endl;
    }
    cout << "Global Sold: " << HotdogStand->globalSoldCountUns << endl;
  
    cout << "Press the enter key once or twice to continue..." << endl;
    cin.ignore();
    cin.get();

    cout << "Process Transactions: \n";
    cout << "=====================\n\n";
    cout << "-----------------------------\n\n";


    fstream infoHotdogTransactions("infoHotDogStandsTransactions.txt");

    int TransactionFileCount = 0;

    while (getline(infoHotdogTransactions, line)) {
        TransactionFileCount++;
    }
    infoHotdogTransactions.clear(); // Clear the end-of-file flag
    infoHotdogTransactions.seekg(0, ios::beg);

    
    TransactionsClass* HotdogStandTransactions = new TransactionsClass[TransactionFileCount];
    int hotDognum = 0;
    int sold = 0;
    for (int k = 0; k < TransactionFileCount; k++) {

        cout << "HotDog Stand Current Status :\n";
        

        getline(infoHotdogTransactions, line);
        stringstream ss(line);

        getline(ss, tempString, ',');
        HotdogStandTransactions[k].setIdentifcationStr(tempString);
        for (int i = 0; i < HotdogStandFileCount; i++) {
            if (HotdogStandTransactions[k].getIdentifcationStr() == HotdogStand[i].getIdStr()) {
                cout << HotdogStand[i];
                hotDognum = i;
                break;
            }
        }

        cout << "Transactions: \n";
        cout << "Transaction Stand Id : " << HotdogStandTransactions[k].getIdentifcationStr() << endl;

        getline(ss, address, ',');
        HotdogStandTransactions[k].setTransactionIdStr(address);
        cout << "Transaction Id : " << HotdogStandTransactions[k].getTransactionIdStr() << endl;


        getline(ss, tempString, ',');
        price = stof(tempString);
        HotdogStandTransactions[k].setTransactionArgumentUns(price);
        cout << "Transaction Argument : " << HotdogStandTransactions[k].getTransactionArgumentUns() << endl << endl;
        if (HotdogStandTransactions[k].getTransactionIdStr() == "stock inventory") {
            HotdogStand[hotDognum].setInventoryAmountUns(HotdogStandTransactions[k].getTransactionArgumentUns());
        }
        else if (HotdogStandTransactions[k].getTransactionIdStr() == "buy") {
            if (HotdogStand[hotDognum].getInventoryAmountUns() > 0) {
                if (HotdogStand[hotDognum].getInventoryAmountUns() >= HotdogStandTransactions[k].getTransactionArgumentUns()) {

                    HotdogStand[hotDognum].setSoldAmountUns(HotdogStand[hotDognum].getSoldAmountUns() + HotdogStandTransactions[k].getTransactionArgumentUns());
                    HotdogStand[hotDognum].setInventoryAmountUns(HotdogStand[hotDognum].getInventoryAmountUns() - HotdogStandTransactions[k].getTransactionArgumentUns());
                    HotdogStand->globalSoldCountUns += HotdogStandTransactions[k].getTransactionArgumentUns();
                }
                else {
                    cout << "*We only have "<< HotdogStand[hotDognum].getInventoryAmountUns() << " hotdogs left.*\n\n";
                }
                
            }
            else {
                cout << "*There are not any more hotdogs left to be sold*\n";
            }

            
        }

        cout << "HotDog Stand Status After Transaction : \n\n";
        cout << HotdogStand[hotDognum] << endl;

        cout << "Global Sold: " << HotdogStand->globalSoldCountUns << endl << endl;
        
        cout << "Press the enter key once or twice to continue..." << endl;
        cin.ignore();
        cin.get();
        cout << "-----------------------------\n\n";
        
    }
    
    cout << "Final states of stands:\n";
    cout << "=======================\n\n";

    for (int j = 0; j < HotdogStandFileCount; j++) {
        cout << HotdogStand[j];
        cout << endl ;
    }

    cout << endl <<"Global Sold: " << HotdogStand->globalSoldCountUns << endl << endl;
    
 //   ofstream outputHotDogFile("infoHotDogStands.txt");


    for (int i = 0; i < HotdogStandFileCount; i++) {
        infoHotdog << HotdogStand[i] << endl << endl;;
    }

    infoHotdog.close();

  //  ofstream globalsold("infoGlobalSold.txt");

    InfoGlobal << HotdogStand->globalSoldCountUns;

    InfoGlobal.close();

    delete[] HotdogStand;
    delete[] HotdogStandTransactions;

    cout << "Please press enter key once or twice to continue..." << endl << endl;
    cout << "Please press enter key once or twice to end..." << endl << endl;
    cin.ignore();
    cin.get();


    
    return 0;
}
