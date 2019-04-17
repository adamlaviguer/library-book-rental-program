//Adam Laviguer
//Section 02
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
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
Book * searchBook(vector<Book *> myBooks, int id) {
    return nullptr;
}
*/

int readPersons(vector<Person *> & myCardholders);
void readBooks(vector<Book *> & myBooks);
void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders);
void bookCheckout(vector<Person *> & myCardholders, vector<Book *> & myBooks);
bool validCardID(vector<Person *> &myCardholders, int cardID, int &personIndex);
bool validBookID(vector<Book *> &myBooks, int bookID, int &bookIndex);
void bookReturn(vector<Book *> & myBooks);
void bookSearch(vector<Book *> & myBooks);
void viewRentals(vector<Book *> & myBooks);
void viewCardholderRentals(vector<Person *> &myCardholders, vector<Book *> & myBooks);
void openCard(vector<Person *> & myCardholders, int &nextID);
void closeCard(vector<Person *> & myCardholders);
void updateRecords(vector<Person *> & myCardholders, vector<Book *> & myBooks);

int main()
{

    vector<Book *> myBooks;
    vector<Person *> myCardholders;
    int nextID=readPersons(myCardholders);
    readBooks(myBooks);
    readRentals(myBooks, myCardholders);
    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
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
                bookReturn(myBooks);
                break;

            case 3:
                // View all available books
                bookSearch(myBooks);
                break;

            case 4:
                // View all outstanding rentals
                viewRentals(myBooks);
                break;

            case 5:
                // View outstanding rentals for a cardholder
                viewCardholderRentals(myCardholders, myBooks);
                break;

            case 6:
                // Open new library card
                openCard(myCardholders, nextID);
                break;

            case 7:
                // Close library card
                closeCard(myCardholders);
                break;

            case 8:
                // Must update records in files here before exiting the program
                updateRecords(myCardholders, myBooks);
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
    int cardNo, largestID;
    bool act;
    string fName, lName;
    Person * personPtr = NULL;
    while (inData>>cardNo) {
        inData>>act>>fName>>lName;
        personPtr = new Person(cardNo, act, fName, lName);
        myCardholders.push_back(personPtr);
        largestID = cardNo;
        //test code//cout<<personPtr->getId()<<" "<<personPtr->isActive()<<" "<<personPtr->fullName()<<endl;
    }
    inData.close();
    return largestID+1;
}

void readBooks(vector<Book *> & myBooks) {
    ifstream inData;
    inData.open("books.txt", ios::in);
    int id;
    string bookName, auth, cat, line;
    Book * bookPtr = NULL;
    while (inData>>id) {
        getline(inData, line);
        getline(inData, bookName);
        getline(inData, auth);
        getline(inData, cat);
        getline(inData, line);
        bookPtr = new Book(id, bookName, auth, cat);
        myBooks.push_back(bookPtr);
    }
    inData.close();
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    ifstream inData;
    inData.open("rentals.txt", ios::in);
    int bookID, cardID;
    while (inData>>bookID) {
        inData>>cardID;
        for (int i=0; i<myBooks.size(); i++){
            if (bookID==myBooks.at(i)->getId()){
                for (int j=0; j<myCardholders.size(); j++){
                    if (cardID==myCardholders.at(j)->getId()){
                        myBooks.at(i)->setPersonPtr(myCardholders.at(j));
                    }
                }
            }
        }
    }
    inData.close();
}

bool validCardID(vector<Person *> &myCardholders, int cardID, int &personIndex){
    for (int i=0; i<myCardholders.size(); i++){
        if (cardID==myCardholders.at(i)->getId() && myCardholders.at(i)->isActive()==true){
            personIndex=i;
            return true;
        }
    }
    return false;
}

bool validBookID(vector<Book *> &myBooks, int bookID, int &bookIndex){
    for (int i=0; i<myBooks.size(); i++){
        if (bookID==myBooks.at(i)->getId()){
            bookIndex=i;
            return true;
        }
    }
    return false;
}

void bookCheckout(vector<Person *> &myCardholders, vector<Book *> &myBooks){
    int cardID, bookID, personIndex, bookIndex;
    //get the users card ID
    cout<<"\nPlease enter the card ID: ";
    cin>>cardID;
    cin.ignore();

    if (validCardID(myCardholders, cardID, personIndex)){
        cout<<"Cardholder: "<<myCardholders.at(personIndex)->fullName()<<endl;
    }
    else{
        cout<<"Card ID not found"<<endl<<endl;
        return;
    }
    //get the users book ID
    cout<<"Please enter the book ID: ";
    cin>>bookID;
    cin.ignore();

    if (validBookID(myBooks, bookID, bookIndex)==true){
        if (myBooks.at(bookIndex)->getPersonPtr()==NULL){
            cout<<"Title: "<<myBooks.at(bookIndex)->getTitle()<<endl;
            myBooks.at(bookIndex)->setPersonPtr(myCardholders.at(personIndex));
            cout<<"Rental Completed"<<endl;
            //test code//cout<<myBooks.at(bookIndex)->getPersonPtr()->fullName();
        }
        else{
            cout<<"Book already checked out"<<endl<<endl;
            return;
        }
    }
    else{
        cout<<"Book ID not found"<<endl<<endl;
        return;
    }
}

void bookReturn(vector<Book *> & myBooks){
    int bookID, bookIndex;

    //get the users book ID
    cout<<"\nPlease enter the book ID to return: ";
    cin>>bookID;
    cin.ignore();

    if (validBookID(myBooks, bookID, bookIndex)==true){
        if (myBooks.at(bookIndex)->getPersonPtr()==NULL){
            cout<<"Book not yet checked out"<<endl<<endl;
            return;
        }
        else{
            cout<<"Title: "<<myBooks.at(bookIndex)->getTitle()<<endl;
            myBooks.at(bookIndex)->setPersonPtr(NULL);
            cout<<"Return Completed"<<endl;
        }
    }
    else{
        cout<<"Book ID not found"<<endl<<endl;
        return;
    }
}

void bookSearch(vector<Book *> & myBooks){
    int count=0;
    for (int i=0;i<myBooks.size();i++){
        if (myBooks.at(i)->getPersonPtr()==NULL){
            cout<<"\nBook ID: "<<myBooks.at(i)->getId()<<"\nTitle: "<<myBooks.at(i)->getTitle()<<
            "\nAuthor: "<<myBooks.at(i)->getAuthor()<<"\nCategory: "<<myBooks.at(i)->getCategory()<<endl;
            count++;
        }
    }
    if (count==0){
        cout<<"\nNo available books"<<endl<<endl;
    }
}

void viewRentals(vector<Book *> & myBooks){
    int count=0;
    for (int i=0;i<myBooks.size();i++){
        if (myBooks.at(i)->getPersonPtr()!=NULL){
            cout<<"\nBook ID: "<<myBooks.at(i)->getId()<<"\nTitle: "<<myBooks.at(i)->getTitle()<<
            "\nAuthor: "<<myBooks.at(i)->getAuthor()<<"\nCardholder: "<<myBooks.at(i)->getPersonPtr()->fullName()<<
            "\nCard ID: "<<myBooks.at(i)->getPersonPtr()->getId()<<endl;
            count++;
        }
    }
    if (count==0){
        cout<<"\nNo outstanding rentals"<<endl<<endl;
    }
}

void viewCardholderRentals(vector<Person *> &myCardholders, vector<Book *> & myBooks){
    int cardID, personIndex;
    //get the users card ID
    cout<<"\nPlease enter the card ID: ";
    cin>>cardID;
    cin.ignore();

    int count=0;
    if (validCardID(myCardholders, cardID, personIndex)){
        cout<<"Cardholder: "<<myCardholders.at(personIndex)->fullName()<<endl;
        for (int i=0;i<myBooks.size();i++){
            if (myBooks.at(i)->getPersonPtr()!=NULL && myBooks.at(i)->getPersonPtr()->getId()==cardID){
                cout<<"\nBook ID: "<<myBooks.at(i)->getId()<<"\nTitle: "<<myBooks.at(i)->getTitle()<<
                "\nAuthor: "<<myBooks.at(i)->getAuthor()<<endl;
                count++;
            }
        }
        if (count==0){
            cout<<"No books currently checked out"<<endl;
        }
    }
    else{
        cout<<"Card ID not found"<<endl<<endl;
        return;
    }
}

void openCard(vector<Person *> & myCardholders, int &nextID) {
    string fName, lName, fullName;
    cout<<"\nPlease enter the first name: ";
    getline(cin, fName);
    cout<<"Please enter the last name: ";
    getline(cin, lName);
    fullName=fName+" "+lName;
    int count=0;
    Person * personPtr = NULL;
    for (int i=0; i<myCardholders.size(); i++){
        if (myCardholders.at(i)->fullName()==fullName && myCardholders.at(i)->isActive()==false){
            myCardholders.at(i)->setActive(true);
            cout<<"Card ID "<<myCardholders.at(i)->getId()<<" active"<<
            "\nCardholder: "<<myCardholders.at(i)->fullName()<<endl;
            count++;
        }
    }
    if (count==0){
        personPtr = new Person(nextID, true, fName, lName);
        myCardholders.push_back(personPtr);
        cout<<"Card ID "<<personPtr->getId()<<" active"<<
        "\nCardholder: "<<personPtr->fullName()<<endl;
        nextID++;
    }
}

void closeCard(vector<Person *> & myCardholders){
    int cardID, personIndex;
    char choice;
    //get the users card ID
    cout<<"\nPlease enter the card ID: ";
    cin>>cardID;
    cin.ignore();

    int count=0;
    for (int i=0; i<myCardholders.size(); i++){
        if (cardID==myCardholders.at(i)->getId() && myCardholders.at(i)->isActive()==true){
            cout<<"Cardholder: "<<myCardholders.at(i)->fullName()<<endl;
            cout<<"Are you sure you want to deactivate card (y/n)? ";
            cin>>choice;
            if (toupper(choice)=='Y'){
                myCardholders.at(i)->setActive(false);
                cout<<"Card ID deactivated"<<endl;
            }
            else if (toupper(choice)=='N'){
                return;
            }
            else if (cardID==myCardholders.at(i)->getId() && myCardholders.at(i)->isActive()==false){
                cout<<"Cardholder: "<<myCardholders.at(i)->fullName()<<endl;
                cout<<"Card ID is already inactive"<<endl;
                count++;
            }
            count++;
        }
    }
    if (count==0){
        cout<<"Card ID not found"<<endl<<endl;
        return;
    }
}

void updateRecords(vector<Person *> & myCardholders, vector<Book *> & myBooks){
    ofstream outPersons, outRentals;
    outPersons.open("persons.txt", ios::out);
    for (int i=0; i<myCardholders.size(); i++){
        outPersons<<myCardholders.at(i)->getId()<<" "<<myCardholders.at(i)->isActive()<<" "<<
        myCardholders.at(i)->fullName()<<endl;
    }
    outPersons.close();
    outRentals.open("rentals.txt", ios::out);
    for (int i=0;i<myBooks.size();i++){
        if (myBooks.at(i)->getPersonPtr()!=NULL){
            outRentals<<myBooks.at(i)->getId()<<" "<<myBooks.at(i)->getPersonPtr()->getId()<<endl;
        }
    }
    outRentals.close();
}
