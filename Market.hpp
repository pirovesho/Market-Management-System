#include <iostream>
#include <string>
#include <vector>

//Declaration of the class that will hold all attributes (data and methods) of the products of the market
class Product{
  private:
    int code;
    std::string name;
    std::string category;
    int quantity;
    double price;
    float review;
    int reviewDisplay;
    char sector;

  public:
    //Constructor
    Product(std::string newName, std::string newCategory, int newQuantity, double newPrice, float newReview, char newSector, int newCode);

    void convertReviewDisplay();
    void fixName();
    void fixCategory();
    void fixSector();
    void displayAllProductInfo();
    void addCode(int index);

    //-----ACCESS DATA OF A PRODUCT-----
    std::string getName(); 
    int getCode(); 
    std::string getCategory();
    int getQuantity();
    double getPrice();
    float getReview();
    int getReviewDisplay();
    char getSector();


    //-----UPDATE DATA OF A PRODUCT-----
    void updateName(std::string newName);
    void updateCategory(std::string newCategory);
    void updateQuantity(int newQuantity);
    void updatePrice(double newPrice);
    void updateReview(float newReview);
    void updateSector(char newSector);

    

};

//"Market" class will hold the whole products and the functions implemeted to them
class Market{
  std::vector <Product> products;

  public:
    void addProduct(); 
    void removeProduct(); 
    void updateProduct(); 
    void searchProduct(); 
    void displayAll(); 
    void loadFromFile(); 
    void saveToFile();

};


//Display the main menu
void displayMainMenu();

//Displays the header of the table of products
void displayTableHeader();

//Print horizontal separation line of table
void drawLine();

//Display all attributes that the user can update into a product
void displayProductAttributes();

//Update the attribute chosen by user to the product
void updateAttribute(int choice, Product &productToUpdate);

//Wait for user to press Enter to go on
void waitForEnter();