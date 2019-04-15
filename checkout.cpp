//Adam Laviguer
//Section 02
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

/* You are not obligated to use these function declarations - they're just given as examples
void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    return;
}

void openCard(vector<Person *> & myCardholders, int nextID) {
    return;
}

Book * searchBook(vector<Book *> myBooks, int id) {
    return nullptr;
}
*/

int readPersons(vector<Person *> & myCardholders);
void readBooks(vector<Book *> & myBooks);
void bookCheckout(vector<Person *> & myCardholders, vector<Book *> & myBooks);
bool validCardID(vector<Person *> &myCardholders, int &cardID);
bool validBookID(vector<Book *> &myBooks, int &bookID);

int main()
{
    vector<Book *> myBooks;
    vector<Person *> myCardholders;
    readPersons(myCardholders);
    readBooks(myBooks);
    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
        vector<Book *> myBooks;
        vector<Person *> myCardholders;
        printMenu();
        cin >> choice;
        cin.ignore();
        switch(choice)
        {
            case 1:
                // Book checkout
                bookCheckout(myCardholders, myBooks);
                break;

            case 2:
                // Book return
                break;

            case 3:
                // View all available books
                break;

            case 4:
                // View all outstanding rentals
                break;

            case 5:
                // View outstanding rentals for a cardholder
                break;

            case 6:
                // Open new library card
                break;

            case 7:
                // Close library card
                break;

            case 8:
                // Must update records in files here before exiting the program
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}


//function declarations----------------------------------------------
int readPersons(vector<Person *> & myCardholders) {
    ifstream inData;
    inData.open("persons.txt", ios::in);
    int cardNo, largestID, nextID;
    bool act;
    string fName, lName;
    while (!inData.eof()) {
        inData>>cardNo>>act>>fName>>lName;
        //cout<<cardNo<<" "<<act<<" "<<fName<<" "<<lName<<endl;
        Person * personPtr;
        personPtr = new Person(cardNo, act, fName, lName);
        myCardholders.push_back(personPtr);
        largestID = cardNo;
        cout<<personPtr->getId()<<" "<<personPtr->isActive()<<" "<<personPtr->fullName()<<endl;
        cout<<myCardholders.size()<<"*Size of myCardholders test*"<<endl;
    }
    inData.close();
    nextID=largestID+1;
    return nextID;
}

void readBooks(vector<Book *> & myBooks) {
    ifstream inData;
    inData.open("books.txt", ios::in);
    int id;
    string bookName, auth, cat, line;
    while (inData>>id) {
        getline(inData, line);
        getline(inData, bookName);
        getline(inData, auth);
        getline(inData, cat);
        getline(inData, line);
        Book * bookPtr;
        bookPtr = new Book(id, bookName, auth, cat);
        myBooks.push_back(bookPtr);
    }
    inData.close();
}

bool validCardID(vector<Person *> &myCardholders, int &cardID){
    cout<<myCardholders.size()<<"*Size of myCardholders test*"<<endl;
    for (int i=0; i<myCardholders.size(); i++){
        cout<<myCardholders.at(i)->getId()<<"*test*"<<endl;
        if (cardID==myCardholders.at(i)->getId()){
            return true;
        }
    }
    return false;
}

bool validBookID(vector<Book *> &myBooks, int &bookID){
    for (int i=0; i<myBooks.size(); i++){
        if (bookID==myBooks.at(i)->getId()){
            return true;
        }
    }
    return false;
}

void bookCheckout(vector<Person *> &myCardholders, vector<Book *> &myBooks){
    //get the users card ID
    int cardID;
    cout<<"Please enter the card ID: ";
    cin>>cardID;
    cin.ignore();

    cout<<myCardholders.size()<<"*Size of myCardholders test*"<<endl;
    bool valid=validCardID(myCardholders, cardID);
    cout<<valid<<"*Validity test*"<<endl;
    if (valid){
        cout<<"Card ID is valid."<<endl;
    }
    else{
        cout<<"Card ID "<<cardID<<" not found"<<endl;
        bookCheckout(myCardholders, myBooks);
    }
    //get the users book ID
    int bookID;
    cout<<"Please enter the book ID: ";
    cin>>bookID;
    cin.ignore();
    if (validBookID(myBooks, bookID)==true){
        cout<<"Book ID is valid."<<endl;
    }
    else{
        cout<<"Book ID not found"<<endl;
    }
}
