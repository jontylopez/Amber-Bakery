#include <iostream>
#include <string>
#include <fstream> 

using namespace std;
// this is the code i use for search option.
void searchItem() {
    string searchItemName;
    cout << "Enter the name of the item to search: ";
    cin.ignore(); // I used ignore to Clear the newline character from the input buffer
    getline(cin, searchItemName);

    ifstream inputFile("item_details.txt");

    if (!inputFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inputFile, line)) {
        if (line.find("Item Name: " + searchItemName) != string::npos) {
            // Item found, print its details
            found = true;
            cout << "Item Details:\n";
            cout << line << endl;
            for (int i = 0; i < 2; i++) {
                getline(inputFile, line); // Print the next two lines (price and quantity)
                cout << line << endl;
            }
            cout << "---------------------------" << endl;
        }
    }

    inputFile.close();

    if (!found) {
        cout << "Item not found in the inventory." << endl;
    }
}

    
//This is the coding part i used to view saved items
void viewItem(){
    ifstream inputFile("item_details.txt");

    if (!inputFile) {
        cerr << "ERROR!! item_details.txt not found." << endl;
        return;
    }

    string line;
    cout << "Inventory Items:\n";
    while (getline(inputFile, line)) {
        if (line.find("Item Name: ") != string::npos) {
            // Item name found, print the item details
            cout << line << endl;
            for (int i = 0; i < 2; i++) {
                getline(inputFile, line); // Print the next two lines (price and quantity)
                cout << line << endl;
            }
            cout << "---------------------------" << endl;
        }
    }

    inputFile.close();
}



/*This is the part i use to enter new entries to the system! 
the entire code is depend on this little part because the save file is created in this part */

void enterItem(){
    string itemName;
    double itemPrice, itemQuantity;
    cout << "Item Name:";
    cin >> itemName;
    cout << "Item Price:";
    cin >> itemPrice;
    cout << "Quantity:";
    cin >> itemQuantity;
    //Here is the step I create the save file
    ofstream outputFile("item_details.txt", ios::app);
    if(!outputFile){
        cerr << "ERROR!! item_details.txt not found.\n";
        return;
    }
// This is the style i want to write the data on txt file
outputFile << "Item Name: " << itemName << endl;
outputFile << "Item Price: " << itemPrice << endl;
outputFile << "Item Quantity: " << itemQuantity << endl;
outputFile << "---------------------------" << endl;
//closing file
outputFile.close();
cout << "Item Added Successfully! \n";
    
}
//This code is the code I create to delete items
void deleteItem(){
    string itemToDelete;
    cout << "Enter Item Name to delete: ";
    cin >> itemToDelete;

    ifstream inputFile("item_details.txt");
    ofstream tempFile("temp_item_details.txt");

    if (!inputFile || !tempFile) {
        cerr << "ERROR!! item_details.txt not found." << endl;
        return;
    }

    bool found = false;
    string line;

    while (getline(inputFile, line)) {
        if (line.find("Item Name: " + itemToDelete) != string::npos) {
            // Item found, skip this entry
            found = true;
            for (int i = 0; i < 3; i++) {
                getline(inputFile, line); // Skip the next three lines
            }
        } else {
            // Item not found, write to the temporary file
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if (found) {
        remove("item_details.txt"); // Delete the original file
        rename("temp_item_details.txt", "item_details.txt"); // Rename the temporary file
        cout << "Item deleted successfully!" << endl;
    } else {
        cout << "Item not found in the inventory." << endl;
        remove("temp_item_details.txt"); // Remove the temporary file
    }

}
/*Down here I tried to develop a selling function, by connecting with txt file to 
update the available quantity after sale*/
struct Item {
    string name;
    double price;
    int quantity;
};

void sellItem(){
    string itemName;
    int quantityToSell;
    double totalCost = 0.0;

    cout << "Enter Item Name to sell: ";
    cin.ignore(); // Clear the newline character from the input buffer
    getline(cin, itemName);

    ifstream inputFile("item_details.txt");
    
    if (!inputFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    Item item;
    bool itemFound = false;

    while (inputFile >> item.name >> item.price >> item.quantity) {
        if (item.name == itemName) {
            itemFound = true;
            break;
        }
    }

    inputFile.close();

    if (!itemFound) {
        cout << "Item not found in the inventory." << endl;
        return;
    }

    cout << "Available quantity: " << item.quantity << endl;
    cout << "Enter the quantity to sell: ";
    cin >> quantityToSell;

    if (quantityToSell <= 0 || quantityToSell > item.quantity) {
        cout << "Invalid quantity or not enough quantity available." << endl;
        return;
    }

    totalCost = quantityToSell * item.price;
    item.quantity -= quantityToSell;

    ofstream outputFile("item_details.txt");
    
    if (!outputFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    outputFile << item.name << " " << item.price << " " << item.quantity << endl;

    outputFile.close();

    cout << "Item sold successfully!" << endl;
    cout << "Total Cost: $" << totalCost << endl;
}
/*Above this point all the code are for the main function belo. to work main funtion 
properly i declared everything above! lets go to main function*/
int main(){

bool loggedIn = false;

while (!loggedIn){//! is like not

//this is the login code
string username, password;
cout << "\n~~~~~~~~~~~~~~~~~~~~~~~\n";
cout << "Welcome to Amber Bakery\n";
cout << "~~~~~~~~~~~~~~~~~~~~~~~\n\n";
cout << "Please Login\n";
cout << "Enter Username: \n";
cin >> username;
cout << "Enter Password: \n";
cin >> password;

if (username == "user" && password == "1234"){
    loggedIn = true;
    cout << "Login Success!\n";
} else {
cout << "Login Failed, Try Again\n";
}
}
//when logged in you can see the main menu down here!
while (true){
    cout << "\n Main Menu \n";
    cout << "1-Search Item\n";
    cout << "2-View Items\n";
    cout << "3-Manage Items\n";
    cout << "4-Sales Management\n";
    cout << "5-Company Details\n";
    cout << "6-Logout\n";
    cout << "Enter Choice: \n";
    int choice;
    cin >> choice;
    switch (choice){
case 1://search Option
searchItem();
    break;
case 2://view option
viewItem();
    break;
case 3://Manage option
cout << "1-Enter New\n";
cout << "2-Delete Item\n";
cout << "3-Main Menu\n";
cout << "Enter choice:";
cin >> choice;
switch(choice){
    case 1://in manage option this is the new entry option
    enterItem();
    break;
    case 2://in manage option this is the delete entry option
    deleteItem();
    break;
    case 3:// this is to go back to main menu
    break;
}
    break;
case 4:
sellItem();//sell item option
    break;
case 5://here I entered company details
    cout << "Name- Amber Bakery\n";
    cout << "Location- London\n";
    cout << "Tel- +44773351031\n";
    cout << "email- amberbakery@gmail.com\n";
    cout << "We undertake all the Birthday events,Holiday Parties and Weddings\n";
    break;
case 6://logout
    loggedIn = false;
    cout << "Logged Out Successfully!\n";
    return 0;
    }
}

    return 0;
}