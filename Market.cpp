#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> 
#include "Market.hpp"

int main(){
    Market myMarket;

    int choice;

    myMarket.loadFromFile();

  do {

        system("clear"); // Linux/macOS

         displayMainMenu();

        std::cin >> choice;


        switch(choice) {
            case 1:
                myMarket.addProduct();
                break;
            case 2: {
                myMarket.displayAll();
                waitForEnter();
                break;
            }
            case 3:
                myMarket.updateProduct();
                break;
            case 4:
                myMarket.removeProduct();
                break;
            case 5:
                myMarket.searchProduct();
                break;
            case 6: 
                myMarket.saveToFile();
                break;
            default:
                std::cout << "\n\nInvalid choice! Please enter a number from 1 to 7. ⚠️\n" << std::endl;
                waitForEnter();
        }

  } while (choice != 6);

    return 0;
}