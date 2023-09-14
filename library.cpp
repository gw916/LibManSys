/*------------------------------------------
    Program 1: Library 

    Course: CS 251, Fall 2023.
    System: Linux x86_64 and G++
    Author: Gerard W. Wilbert
 ---------------------------------------------*/

/* Help organize books in a library
Has functionalities to add to library, clear library, display library, load entries,
search entry, remove entry, writing to a file, and show checkout stats and print each invalid entry
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// Function prototypes for all the glorious function decomposition
void AddToLibrary(vector<string>& books, vector<string>& ISBN, vector<int>& Checkouts);
void clearLibrary(vector<string>& books, vector<string>& ISBN, vector<int>& Checkouts);
void displayLibrary(vector<string> books, vector<string> ISBN, vector<int> Checkouts);
string getCheckString(int CheckNum);
void getISBNDigits(vector<int>& isbNumbers, string ISBN);
void invalidEntries(vector<string> books, vector<string> ISBN, vector<int> Checkouts);
bool isbnCalc(vector<int> isbNumbers);
void loadLibraryfromFile(string src_file, vector<string>& books, vector<string>& ISBN, vector<int>& Checkouts);
void outputLibrarytoFIle(string src_file, vector<string> books, vector<string> ISBN, vector<int> Checkouts);
void printCheckOut(vector<string> books, vector<int> Checkouts);
void printMenu();
void removeLibrary(vector<string>& books, vector<string>& ISBN, vector<int>& Checkouts);
void removeLib(vector<string>& books, vector<string>& ISBN, vector<int>& Checkouts, bool remove, int removePos);
void searchLibrary(vector<string> books, vector<string> ISBN, vector<int> Checkouts);
void searchLib(vector<string> books, vector<string> ISBN, vector<int> Checkoutsk, bool search, int searchPos);
int main()
{
    string command;
    vector<string> bookTitles; // Each part of a book has title, isbn, a checkout and each has vector
    vector<string> isbnNums;  // each vector is the same size
    vector<int> CheckoutNums;

    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;
  // The while loop does the menu functionality
    do 
    {
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";

        getline(cin, command);
        cout << endl;

        if(command == "A" || command == "a") {
            AddToLibrary(bookTitles, isbnNums, CheckoutNums);  // Add to Library
        }
        else if(command == "C" || command == "c") {
            clearLibrary(bookTitles, isbnNums, CheckoutNums); // Clear library
        }
        else if (command == "D" || command == "d") {
            displayLibrary(bookTitles, isbnNums, CheckoutNums); // display library
        }

        else if(command == "i" || command == "I") {
            invalidEntries(bookTitles, isbnNums, CheckoutNums); // invalid entries
        }

        else if (command == "L" || command == "l") {
            string file; // variable for the file name that will be read in
            cout << "What database to read from? "; 
            getline(cin, file);
            cout << endl;
            loadLibraryfromFile(file, bookTitles, isbnNums, CheckoutNums); // load file
            
        }

        else if (command == "O" || command == "o") {
            string writeFile; //used to output file
            cout << "Where should the database output to? ";
            getline(cin, writeFile);
            cout << endl;
            outputLibrarytoFIle(writeFile, bookTitles, isbnNums, CheckoutNums); // output to file
        }

        else if(command == "p" || command == "P") {
            printCheckOut(bookTitles, CheckoutNums); // checkout stats
        }

        else if(command == "R" || command == "r") {
            removeLibrary(bookTitles, isbnNums, CheckoutNums); // remove entry
        }

        else if(command == "s" || command == "S") {
            searchLibrary(bookTitles, isbnNums, CheckoutNums); // search enrtry
        }
        else if(command == "X" || command == "x") { // exit
            break;
        }
        else {
            cout << "Unknown Command" << endl; 
        }
        cout << endl;
    } while (!(command == "x" || command == "X"));

    return 0;
}
// Used to add a new book to the library
// passes by reference each vector so that they can change in size.
// Book titles can't have commas
void AddToLibrary(vector<string>& books, vector<string>& ISBN, vector<int>& Checkouts) {
    string bookTitle;
    string isbnNum;
    int found; // used to recieve the idx of the comma if there is one
    cout << "What is the book title? ";
    getline(cin, bookTitle);
    cout << endl;
    found = bookTitle.find(',');
    if(found != string::npos) { // if there is a idx with a comma
        cout << "The book title cannot contain commas." << endl;
    }else { // if there is not a idx with a comma. 
        books.push_back(bookTitle);
        cout << "What is the 13-digit ISBN (with hyphens)? ";
        getline(cin, isbnNum);
        cout << endl;
        ISBN.push_back(isbnNum); // Add to each corresponding vector
        Checkouts.push_back(0);
        cout << "The Following Entry Was Added" << endl;
        cout << "-----------------------------" << endl;
        cout << bookTitle << " --- "  << isbnNum << " --- In Library" << endl;
    }

    }
    // Clears each of the vectors.

    void clearLibrary(vector<string>& books, vector<string>& ISBN, vector<int>& Checkouts) {
        books.clear();
        ISBN.clear();
        Checkouts.clear();
        cout << "Your library is now empty." << endl;
    }

    // Displays your current library
    // Libraries need to have books
    void displayLibrary(vector<string> books, vector<string> ISBN, vector<int> Checkouts) {
        string CheckString; // get string that corresponds to the integer of checkout
        cout << "Your Current Library" << endl;
        cout << "--------------------" << endl;
        if(books.size() == 0) {
            cout << "The library has no books." << endl;
        }
        for(int i = 0; i < books.size(); i++) {
            cout << books.at(i) << " --- " << ISBN.at(i) << " --- ";
            CheckString = getCheckString(Checkouts.at(i));
            cout << CheckString << endl;
        }
    }
    // Takes in the integer for the checkout 
    // Also can be given a position
    string getCheckString(int CheckNum) {
        string CheckString;
        if(CheckNum == 0) {
                CheckString = "In Library";
            }
            else if(CheckNum == 1){
                CheckString = "Checked Out";
            }

            else if(CheckNum == 2){
                CheckString = "On Loan";
            }

            else if(CheckNum == 3){
                CheckString = "Unknown State";
            }

            else {
                CheckString = "Invalid State";
            }
        return CheckString;
    }
   // Used to count each of the digits in the isbn 
   // for the invalid entries function
   // Passes in a vector that holds all the digits
    void getISBNDigits(vector<int>& isbNumbers, string ISBN ){
        char ISBNchar;
        for(int i = 0; i < ISBN.size(); i++) {
            ISBNchar = ISBN.at(i);
            if(isdigit(ISBNchar)) { // check if the specific character in the isbn is a number.
                isbNumbers.push_back(ISBNchar);
            }
            else{
                continue;
            }
        }

    }
   // prints each of the incalid entries 
   // Passes by value each of the vectors 
   // Vector don't change in size
    void invalidEntries(vector<string> books, vector<string> ISBN, vector<int> Checkouts) {
        bool nobooks = false; // Checks if there is no books which no error would be printed
        vector<int> invaildIdx; // stores the indexex of the invalids
        vector<int> isbNumbers;
        int invaildCheckPos;
        if(books.size() == 0) { // if books size is 0 there's no books
            nobooks = true;
        }
        else {
            for(int i = 0; i < books.size(); i++) {
                getISBNDigits(isbNumbers, ISBN.at(i)); // collects the digits for each ISBN in vector
                if(Checkouts.at(i) != 0 && Checkouts.at(i) != 1 && Checkouts.at(i) != 2 && Checkouts.at(i) != 3) { // Checkout Numbers can't be anything besides these numbers
                    invaildCheckPos = i;
                    invaildIdx.push_back(invaildCheckPos);
                }
                else if(isbNumbers.size() != 13) { // there should be exactly 13 digits
                    invaildCheckPos = i;
                    invaildIdx.push_back(invaildCheckPos);
                }
                else if(!isbnCalc(isbNumbers)) { // The calculation of the first 12 digit should equal the last digit
                    invaildCheckPos = i;
                    invaildIdx.push_back(invaildCheckPos);
                }
                isbNumbers.clear(); // clears out the digits at the end.
                
            }
        }
        cout << "The Following Library Entries Have Invalid Data" << endl;
        cout << "-----------------------------------------------" << endl;
        if(nobooks == true) {
            cout << "The library has no books." << endl;
        }
        else if(invaildIdx.size() > 0) { // prints the each book with a invalid entry
            for(int j = 0; j <invaildIdx.size(); j++) {
                int Libidx = invaildIdx.at(j);
                cout << books.at(Libidx) << " --- " << ISBN.at(Libidx) << " --- ";
                string checkString = getCheckString(Checkouts.at(Libidx));
                cout << checkString << endl;
            }
        }
        else {
            cout << "The library has no invalid entries." << endl;
        }
    }
// Does the calculation to get the last digit
    bool isbnCalc(vector<int> isbNumbers) {
        int checkDigit = isbNumbers.at(12) - '0'; // converts to integer from ASCII value, and is the digit that needs to be check for valid
        int sum = 0; // starts with the sum
        int secstage; 
        int actDigit; 
        for(int r = 0; r < (isbNumbers.size() - 1); r++) {
            if(((r + 1) % 2) == 1) {
                sum += isbNumbers.at(r) - '0';
            }
            else if (((r + 1) % 2) == 0) { // multplies each even num by 3
                sum += ((isbNumbers.at(r) - '0')* 3) ;
            }
        }
        secstage = sum % 10; // gets reminder from the function
        actDigit = 10 - secstage;
        if(checkDigit == actDigit) {
            return true;
        }
        else {
            return false;
        }
    }
    // load file
    // vectors must change in size
    void loadLibraryfromFile(string src_file, vector<string>& books, vector<string>& ISBN, vector<int>& Checkouts) {
        string line;
        ifstream libraryfile(src_file);
        if(!libraryfile.is_open()) {
            cout << "Could not find the database file." << endl;
        }
        else {
            string line;
            string bookTitle;
            string isbnNum;
            int commaidx; 
            int readinCount = 0; 
            int spaceidx;
            string checkoutN; // string used to get substr then use stoi to make it into a int.
            int checkoutNum;
              while(getline(libraryfile, line)) {
                readinCount += 1;
                commaidx = line.find(',');
                if (commaidx != string::npos) {
                    bookTitle = line.substr(0, commaidx);
                    spaceidx = line.find(' ', commaidx); 
                    commaidx = line.find(',', spaceidx);
                    if(commaidx != string::npos) {   
                        isbnNum = line.substr((spaceidx + 1), commaidx - spaceidx - 1);
                        spaceidx = line.find(' ', commaidx);
                        checkoutN = line.substr(spaceidx, line.size());
                        checkoutNum = stoi(checkoutN);
                        books.push_back(bookTitle);
                        ISBN.push_back(isbnNum);
                        Checkouts.push_back(checkoutNum);   
                    }else { // if there isn't a second set of comma and space
                        isbnNum = line.substr(spaceidx + 1, line.size());
                        checkoutNum = 0;
                        books.push_back(bookTitle);
                        ISBN.push_back(isbnNum);
                        Checkouts.push_back(checkoutNum);
                    }
                }
                else { // If there is no commas and spaces due to there only being a book
                    bookTitle = line.substr(0, line.size());
                    isbnNum = "000-0-00-000000-0";
                    checkoutNum = 0;
                    books.push_back(bookTitle);
                    ISBN.push_back(isbnNum);
                    Checkouts.push_back(checkoutNum);
            
                }

            }
            cout << "Read in " << readinCount << " lines from the file." << endl;
        }
    }
    // write library to a file
    void outputLibrarytoFIle(string src_file, vector<string> books, vector<string> ISBN, vector<int> Checkouts) {
        ofstream newLibfile(src_file);
        int outputCount = 0;
        if(!newLibfile.is_open()) {
            cout << "Could not open database file for writing." << endl;
        }
        else {
            for(int i = 0; i < books.size(); i++) {
                outputCount += 1;
                newLibfile << books.at(i) << ", " << ISBN.at(i) << ", " << Checkouts.at(i) << endl;
            }
        }
        cout << outputCount << " lines of data written to " << src_file << endl;
    }
    // print the checkiut stats
    void printCheckOut(vector<string> books, vector<int> Checkouts) {
        int inLibCount = 0; // int 0
        int checkoutCount = 0; // int 1
        int onLoanCount = 0; // int 2
        int unknownCount = 0; // int 3
        int otherCount = 0; // invalids
        for(int i = 0; i < Checkouts.size(); i++) {
            if(Checkouts.at(i) == 0) {
               inLibCount += 1;
            }
            else if(Checkouts.at(i) == 1){
                checkoutCount += 1;
            }

            else if(Checkouts.at(i) == 2){
                onLoanCount += 1;
            }

            else if(Checkouts.at(i) == 3){
                unknownCount += 1;
            }

            else {
                otherCount += 1;
            }
        }
        cout << "Your Current Library's Stats" << endl;
        cout << "----------------------------" << endl;
        cout << "Total Books: " << books.size() << endl; 
        cout << "   In Library: " << inLibCount << endl;
        cout << "   Checked Out: " << checkoutCount << endl;
        cout << "   On Loan: " << onLoanCount << endl;
        cout << "   Unknown: " << unknownCount << endl;
        cout << "   Other: " << otherCount << endl;
    }
/// @brief print out the main menu of the management system
void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;    
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;    
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;      
    cout << "S - Search For A Library Entry" << endl;    
    cout << "X - Exit Program" << endl;
}

// removee a entry from library
// vector change in size
void removeLibrary(vector<string>& books, vector<string>& ISBN, vector<int>& Checkouts) {
    string input;
    int inputNum;
    int removePos;
    bool Condition = false;
    string inputBook, inputIsbn;
    cout << "Would you like remove by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin, input);
    inputNum = stoi(input);
    cout << endl;
    if(inputNum == 1) {
        cout << "Enter the book name: ";
        getline(cin, inputBook);
        cout << endl;
        for(int i = 0; i < books.size(); i++) {
            if(books.at(i) == inputBook) { 
                Condition = true;
                removePos = i;
            }
            else {
                continue;
            }
        }
       removeLib(books, ISBN, Checkouts, Condition, removePos); 
    }
    else if(inputNum == 2){
        cout << "Enter the book 13-digit ISBN (with dashes): ";
        getline(cin, inputIsbn);
        cout << endl;
        for(int i = 0; i < ISBN.size(); i++) {
            if(ISBN.at(i) == inputIsbn) {
                Condition = true;
                removePos = i;
            }
            else {
                continue;
            }
            
        }
        removeLib(books, ISBN, Checkouts, Condition, removePos);
    }

    else {
        cout << "Invalid remove by choice option" << endl;
    }
    
}
// Second part of Remove that makes the code look a cleaner and less redudant
void removeLib(vector<string>& books, vector<string>& ISBN, vector<int>& Checkouts, bool condition, int removePos) {
    if(condition != false) {
        cout << "The Following Entry Was Removed From The Library" << endl;
        cout << "------------------------------------------------" << endl;
        cout << books.at(removePos) << " --- " << ISBN.at(removePos) << " --- ";
        string CheckString = getCheckString(Checkouts.at(removePos));
        cout << CheckString << endl;
        vector<string> :: iterator removebook = books.begin() + removePos;
        vector<string> :: iterator removeISbn = ISBN.begin() + removePos;
        vector<int> :: iterator removeCheck = Checkouts.begin() + removePos;
        books.erase(removebook);
        ISBN.erase(removeISbn);
        Checkouts.erase(removeCheck);

    }
    else {
        cout << "The Following Entry Was Removed From The Library" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "No matching entry found in the library." << endl;
    }
}

// Searches the library for an entry

void searchLibrary(vector<string> books, vector<string> ISBN, vector<int> Checkouts) {\
    string input;
    int inputNum;
    int searchPos;
    bool search = false;
    string inputBook, inputIsbn;
    cout << "Would you like to search by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin, input);
    inputNum = stoi(input);
    cout << endl;
    if(inputNum == 1) {
        cout << "Enter the book name: ";
        getline(cin, inputBook);
        cout << endl;
        for(int i = 0; i < books.size(); i++) {
            if(books.at(i) == inputBook) {
                searchPos = i;
                search = true;
            }
            else {
                continue;
            }
        }
        searchLib(books, ISBN, Checkouts, search, searchPos);
    }
    else if(inputNum == 2){
        cout << "Enter the book 13-digit ISBN (with dashes): ";
        getline(cin, inputIsbn);
        cout << endl;
        for(int i = 0; i < ISBN.size(); i++) {
            if(ISBN.at(i) == inputIsbn) {
                search = true;
                searchPos = i;
            }
            else {
                continue;
            }
            
        }
        searchLib(books, ISBN, Checkouts, search, searchPos);
    }

    else {
        cout << "Invalid search by choice option" << endl;
    }

    
}
// Second part of search lib that helps with decomposition
void searchLib(vector<string> books, vector<string> ISBN, vector<int> Checkouts, bool search, int searchPos) {
     if(search != false) {
    cout << "The Following Are Your Search Results" << endl;
    cout << "-------------------------------------" << endl;
    cout << books.at(searchPos) << " --- " << ISBN.at(searchPos) << " --- ";
     string CheckString = getCheckString(Checkouts.at(searchPos));
    cout << CheckString;
    }
    else {
        cout << "The Following Are Your Search Results" << endl;
        cout << "-------------------------------------" << endl;
        cout << "No matching entry found in the library." << endl;
    }
}