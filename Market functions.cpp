#include <string>
#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <limits>
#include "Market.hpp"



//-------------------------------****------------------------------- METHODS OF "PRODUCT" CLASS -------------------------------****-------------------------------



//Created an object with all attributes, except "Review Display", (it is calculated based on Review)
Product::Product(std::string newName, std::string newCategory, int newQuantity, double newPrice, float newReview, char newSector, int newCode) 
: name(newName), category(newCategory), quantity(newQuantity), price(newPrice), review(newReview), sector(newSector), code(newCode) {}


//Calculate the "Review Display" and store it
void Product::convertReviewDisplay(){
  reviewDisplay = (int)review;
}


//Make all names start with upper letter
void Product::fixName(){
    name[0] = std::towupper(name[0]);
}

//Make all category sections start with upper latter
void Product::fixCategory(){
    category[0] = std::toupper(category[0]);
}

//Make all sectors upper letters
void Product::fixSector(){
    sector = std::toupper(sector);
}

//Display header table
void displayTableHeader(){
     drawLine();
     
     //Print header (setw sets the column at a specific width)
        std::cout << std::left 
          << std::setw(3) << "Code" 
          << "   "
          << std::setw(25) << "Name" 
          << std::setw(15) << "Category"
          << std::setw(10) << "Quantity" 
          << std::setw(10) << "Price" 
          << std::setw(8) << "Review" 
          << std::setw(15) << "Review Display" 
          << std::setw(8)  << "Sector" << "\n";
    
    drawLine();
}

//Display all data of a product
void Product::displayAllProductInfo() {

    // print product data
        std::cout << std::right 
          << std::setw(3) << std::setfill('0') << code
          << std::setfill(' ') 
          << "   " << std::left
          << std::setw(25) << name
          << std::setw(15) << category
          << std::setw(10) << quantity
          << std::setw(10) << price
          << std::setw(8) << review
          << std::setw(15) << reviewDisplay
          << std::setw(8)  << sector << "\n";
          
}

//Adds the code based on the index of a product
void Product::addCode(int index){
    code = index + 1;
}



//-----*****-----Functions To Access Data-----*****-----
std::string Product::getName(){
    return name;
}

int Product::getCode(){
    return code;
}

std::string Product::getCategory(){
    return category;
}

int Product::getQuantity(){
    return quantity;
}

double Product::getPrice(){
    return price;
}

float Product::getReview(){
    return review;
}

int Product::getReviewDisplay(){
    return reviewDisplay;
}

char Product::getSector(){
    return sector;
}


//-----*****-----Functions To Update Data Of A Product-----*****-----

void Product::updateName(std::string newName){
    name = newName;
}

void Product::updateCategory(std::string newCategory){
    category = newCategory;
}

void Product::updateQuantity(int newQuantity){
    quantity = newQuantity;
}

void Product::updatePrice(double newPrice){
    price = newPrice;
}

void Product::updateReview(float newReview){
    review = newReview;
}

void Product::updateSector(char newSector){
    sector = std::toupper(newSector);
}



//-------------------------------****------------------------------- METHODS OF "MARKET" CLASS -------------------------------****-------------------------------


//Adds new products to the vector (data of the new products are inputed by user)
void Market::addProduct(){

    std::string name;
    std::string category;
    int quantity;
    double price;
    float review;
    char location;


    std::cout << "Enter product name: ";
    //std::getline(std::cin, name);
    std::cin >> name;

    std::cout << "Enter product category: ";
    //std::getline(std::cin, category);
    std::cin >> category;

    std::cout << "Enter quantity: ";
    std::cin >> quantity;

    std::cout << "Enter price: ";
    std::cin >> price;

    std::cout << "Enter review: ";
    std::cin >> review;

    std::cout << "Enter location (sector): ";
    std::cin >> location;

    Product currentProduct (name, category, quantity, price, review, location, products.size() + 1);

    currentProduct.convertReviewDisplay();
    currentProduct.fixName();
    currentProduct.fixCategory();
    currentProduct.fixSector();

    products.push_back(currentProduct);

    system("clear"); //Clears terminal
    std::cout << "Product Added Successfully ✅\n\n";

    displayAll();

    waitForEnter();
}


void Market::displayAll(){

    displayTableHeader();

    for(int i =0; i < products.size(); i++){
        products[i].displayAllProductInfo();

    }

    drawLine();
}


//Get the code of the product to be deleted
void Market::removeProduct(){
    int productCode;

    displayAll();

    std::cout << "\n\nEnter the code of the product you want to remove: ";
    std::cin >> productCode;

    bool controll = false;

    //Controlls if the product is in the list
    for(int i = 0; i < products.size(); i++){
        if(products[i].getCode() == productCode){
            controll = true;
            products.erase(products.begin() + i);
        }
    }

    if(controll == true) {
        for (int i = 0; i < products.size(); i++){
            products[i].addCode(i);
        }

        std::cout << "\nRemove Done Successfully! ✅\n";

    }else {
        std::cout << "No Product with code " << productCode << " Was Found ❌\n";
    }

    waitForEnter();

}

//Get the name of a product and update it
void Market::updateProduct(){
    int productCode;

    displayAll();

    std::cout << "\n\nEnter the code of the product you want to update: ";
    std::cin >> productCode;

    bool controll = false;
    int index;

    //Controlls if the product is in the list
    for(int i = 0; i < products.size(); i++){
        if(products[i].getCode() == productCode){
            controll = true;
            index = i;
        }
    }

    if (controll == true) {
        int choice;

        do {

            std::cout << "---------------------------------------------------------\n";
            std::cout << "You are currently updating product with code: " << productCode << "\n";
            std::cout << "---------------------------------------------------------\n\n";

            displayProductAttributes();

            std::cout << "Enter the attribute to be chenged: ";
            std::cin >> choice;

            updateAttribute(choice, products[index]);

            displayAll();

            waitForEnter();

        } while (choice != 7);

        

    }else {
        std::cout << "Product Not Found! ❌\n";
    }

    waitForEnter();
}

//Search a product by name or code and display if it is found
void Market::searchProduct(){
    int choice;

    do {

        std::cout << "=== Product Search Menu ===\n";
        std::cout << "1. Search by Name\n";
        std::cout << "2. Search by Code\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1){ //Search by name
            std::string nameToSearch;

            //Get the name of the product to be searches
            std::cout << "Enter the name of the product to search: ";
            std::cin >> nameToSearch;

            nameToSearch[0] = std::toupper(nameToSearch[0]);

            bool controll = false;

            //Controll if there is a product with that name
            for (int i = 0; i < products.size(); i++){
                if (products[i].getName() == nameToSearch){
                    controll = true;
                    break;
                }
            }

            if(controll == true){
                displayTableHeader();
                
                //Display all products with that name
                for (int i = 0; i < products.size(); i++){
                    if (products[i].getName() == nameToSearch){
                        products[i].displayAllProductInfo();
                    }
                }

                drawLine();

                std::cout << "Product Found Successfully! ✅\n";

            }else{
                std::cout << "Product Not Found! ❌\n";

            }

        } else if (choice == 2){//Search by code
            int codeToSearch;

            std::cout << "Enter the code of the product to search: ";
            std::cin >> codeToSearch;

            bool controll = false;
            int index; //Will store the index of the product found with given code

            //Controll if there is a product with that code
            for (int i = 0; i < products.size(); i++){
                if (products[i].getCode() == codeToSearch){
                    controll = true;
                    index = i;
                    break;
                }
            }

            if(controll == true){
                displayTableHeader();
                
                products[index].displayAllProductInfo();

                drawLine();

                std::cout << "Product Found Successfully ✅\n";

            }else{
                std::cout << "Product Not Found! ❌\n";

            }
        }else if (choice != 3) {
            std::cout << "Invalid Input! ⚠️\n";

        }

        waitForEnter();

    } while (choice != 3);
}

//-----*****-----FUNCTIONS THAT WORK WITH THE FILE-----*****-----

//Load all data from file to vector
void Market::loadFromFile(){

    //Clears the vector before adding elements into it
    products.clear();


    std::fstream file("Database.txt", std::ios::in);

    int code;
    std::string name;
    std::string category;
    int quantity;
    double price;
    float review;
    int reviewDisplay;
    char sector;

    while (file >> code >> name >> category >> quantity >> price >> review >> reviewDisplay >> sector) {
        Product productRead(name, category, quantity, price, review, sector, code);

        productRead.convertReviewDisplay();
        productRead.fixName();
        productRead.fixCategory();
        productRead.fixSector();


        products.push_back(productRead);
    }

    file.close();
}

void Market::saveToFile(){
    std::fstream file("Database.txt", std::ios::in | std::ios::out);

    for (int i = 0; i < products.size(); i++){
        file << std::right
             << std::setw(3)  << std::setfill('0') << products[i].getCode() << std::left << std::setfill(' ') << "   "
             << std::setw(25) << products[i].getName()
             << std::setw(15) << products[i].getCategory()
             << std::setw(10) << products[i].getQuantity()
             << std::setw(10) << products[i].getPrice()
             << std::setw(8) << products[i].getReview()
             << std::setw(15) << products[i].getReviewDisplay()
             << std::setw(8)  << products[i].getSector() << std::endl;
    }

    file.close();
}


//-------------------------------****------------------------------- ADDED FUNCTIONS -------------------------------****-------------------------------

//Display main menu
void displayMainMenu(){
    std::cout << "===== MARKET MANAGEMENT SYSTEM =====" << std::endl
         << "1. Add Product" << std::endl
         << "2. View All Products" << std::endl
         << "3. Update Product" << std::endl
         << "4. Delete Product" << std::endl
         << "5. Search Product" << std::endl
         << "6. Save and Exit" << std::endl
         << "Enter your choice (1-6): ";
}

//Display all choices the user can choose to update attribute of a product
void displayProductAttributes(){
    std::cout << "\nWhich attribute do you want to change?\n";
    std::cout << "1. Name \n";
    std::cout << "2. Category \n";
    std::cout << "3. Quantity \n";
    std::cout << "4. Price \n";
    std::cout << "5. Review \n";
    std::cout << "6. Sector \n";
    std::cout << "7. Exit \n";
}

//Display the horizontal table separator
void drawLine(){
    std::cout << "------------------------------------------------------------------------------------------------------\n"; 
}

//For the given choice and given product update based on the user input
void updateAttribute(int choice, Product &productToUpdate){
    switch (choice) {
        case 1: {
            std::string newName;

            std::cout << "New name (press Enter to cancel): ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, newName);

            if (newName.empty()){ // User pressed Enter, so skip updating

                std::cout << "Update Canceled Successfully ✅\n";

            } else {
                newName[0] = std::toupper(newName[0]);

                productToUpdate.updateName(newName);

                std::cout << "Product Updated Successfully! ✅\n";
            }

            break;
        }
          
        case 2: {
            std::string newCategory;

            std::cout << "New category (press Enter to cancel): ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::getline(std::cin, newCategory);

            if (newCategory.empty()) { // User pressed Enter, so skip updating

                std::cout << "Update Canceled Successfully ✅\n";

            } else {
                newCategory[0] = std::toupper(newCategory[0]);

                productToUpdate.updateCategory(newCategory);

                std::cout << "Product Updated Successfully! ✅\n";
            }

            break;
        }

        case 3: {
            std::string newQuantityString;

            std::cout << "New quantity (press Enter to cancel): ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, newQuantityString);

            if (newQuantityString.empty()) { // User pressed Enter, so skip updating

                std::cout << "Update Canceled Successfully ✅\n";

            } else {
                //Convert String input into Int
                int newQuantity = std::stoi(newQuantityString);

                productToUpdate.updateQuantity(newQuantity);

                std::cout << "Product Updated Successfully! ✅\n";
            }

            break;    
        }

        case 4: {
             std::string newPriceString;

             std::cout << "New price (press Enter to cancel): ";
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::getline(std::cin, newPriceString);

             if (newPriceString.empty()) { // User pressed Enter, so skip updating

                std::cout << "Update Canceled Successfully ✅\n";

             } else {
                //Convert String input into Double
                double newPrice = std::stod(newPriceString);

                productToUpdate.updatePrice(newPrice);

                std::cout << "Product Updated Successfully! ✅\n";
             }

             break; 
        }

        case 5: {
              std::string newReviewString;

              std::cout << "New review (press Enter to cancel): ";
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              std::getline(std::cin, newReviewString);

              if (newReviewString.empty()) { // User pressed Enter, so skip updating

                std::cout << "Update Canceled Successfully ✅\n";

              } else {
                //Convert String input into Float
                float newReview = std::stof(newReviewString);

                productToUpdate.updateReview(newReview);

                std::cout << "Product Updated Successfully! ✅\n";
              }
              
              break;
        }
        
        case 6: {
            std::string newSectorString;

            std::cout << "New sector (press Enter to cancel): ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, newSectorString);

            if (newSectorString.empty()) { // User pressed Enter, so skip updating
                

                std::cout << "Update Canceled Successfully ✅\n";

            } else {
                //Convert String input into Char
                char newSector = newSectorString[0];

                productToUpdate.updateSector(newSector);

                std::cout << "Product Updated Successfully! ✅\n";
            }

            break;
        }

        case 7: {
            break;
        }

        default: {
            std::cout << "Invalid Input! ⚠️\n";
        }
          
    }
}


void waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush leftover input
    std::cin.get(); // wait for Enter
}