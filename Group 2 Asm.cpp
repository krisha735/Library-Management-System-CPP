//kartik's
#include <iostream>  // Provides input and output stream functionality (e.g., cin, cout)
//#include <fstream>   // reading/writing files
#include <vector>    // vector container for dynamic arrays
#include <string>    // string class for text manipulation
#include <iomanip>   //  functions for formatting output (e.g., setting precision for numbers)
#include <sstream>   //  for converting data types (e.g., numbers to strings)

//krisha's 
//#include <iostream>
#include <iomanip> // for set alignment for array printout in display function to use setw() 
#include <fstream> //  for file handling tasks like reading from or writing to files
#include <ctime>  //to get and manipulate the current date and time


using namespace std;

#define S 6 // size for the book array structure


//katik's function
// The User struct represents a user in the system, including their identification and login credentials.
struct User {
    string memberID;
    string username;
    string password;
};

// Global vector to store users dynamically
vector<User> users;

//katik's funnction and class
void registerUser();
bool loginUser();
void quitSystem();
void displayBooks();
void borrowBook();
void returnBook();
void changePassword(const string& memberID, const string& username);
void forgotPassword() ;

//krisha's class
// Book Class
// The Book class represents information about a book in a library system.
class Book {
public:
    // Public member variables
    string id;      // Unique identifier for the book
    string name;    // Title of the book
    string author;  // Author of the book
    int pubyear;    // Year the book was published
    int quantity;   // Number of copies available in the shelf

    // Constructor to initialize a Book object with default or given values
    Book(string bookID = "", string bookName = "", string bookAuthor = "",
         int publicationYear = 0, int qty = 0)
        : id(bookID), name(bookName), author(bookAuthor), pubyear(publicationYear), quantity(qty) {}
};

//krisha's functions
void Search(Book book[]);
void BookDisplay(Book book[]);
void BorrowBook(Book book[], string memberID);

//choloe's function
void ReturnBook(Book book[], string memberID);

//wong's function
void ViewRecord(Book book[], string memberID);

int main() {
   // Array of Book objects, initialized with data of collection of books in the library
	Book book[S] = {
    // Each Book object is initialized with: ID, Title, Author, Year of Publication, and Quantity
        Book("001","Bear and the Hunter","Harper Lee",1960,5),
        Book("002","War 1984","George Orwell",1949,3),
        Book("003","Sapiens","Yuval Noah Harari",2011,4),
        Book("004","Lovely Kite","Tara Westover",2018,2),
        Book("005","A Brief History of Time","Stephen Hawking",1988,6),
        Book("006","The Selfish Gene","Richard Dawkins",1976,4)
    };
    
    int choice;

    while (true) {
        cout<<"*******************************************************\n";
        cout<<"\nLibrary Lending System\n";
        cout<<"1. Register (New User)\n";
        cout<<"2. Login\n";
        cout<<"3. Forgot Password\n";
        cout<<"4. Quit System\n";
        cout<<"\n*******************************************************\n\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch (choice) {
            case 1:
                registerUser(); //function for new user
                break;
            case 2:
                if (loginUser()) {
    
				    string memberID;  
				    
				    cout<<"\nEnter your Member ID again for verification: ";
				    cin>>memberID; // to store & confirm member id
				    cin.ignore(); 
				    
				    cout<<"\nWelcome to the Library System!\n\n";
				                    
				    int option;  //variable for user selection for menu option
				    do { //menu for user selection
				        cout<<"*****************************************"<<endl;
				        cout<<"|\tLibrary System Menu\t\t|"<<endl;
				        cout<<"*****************************************"<<endl;
				        cout<<"*\t1. Search for a Book\t\t*"<<endl;
						cout<<"*\t2. Display All Books\t\t*"<<endl;
				        cout<<"*\t3. Borrow a Book\t\t*"<<endl;
				        cout<<"*\t4. Return Book\t\t\t*"<<endl;
				        cout<<"*\t5. View RecordBook\t\t*"<<endl;
				        cout<<"*\t6. Exit the System\t\t*"<<endl;
				        cout<<"*****************************************"<<endl;
				        cout<<"Enter your option: ";
				        cin >> option;
				        cin.ignore();
				                
				        switch (option) {
				            case 1: 
				                Search(book); //pass array of books to search function
				                break;
				             
							case 2: 
				            	BookDisplay(book); //pass array of books to bookdisplay function
								break;
				                   
				            case 3: 
				            	BookDisplay(book);  
				                BorrowBook(book, memberID); //pass array of books and memberID to bookdisplay function 
				                break;
				                
				            case 4: 
				               ReturnBook(book, memberID); //pass array of books and memberID to returnbook function
				               break;
				                
				            case 5: 
				                ViewRecord(book, memberID); //pass array of books and memberID to ViewRecord function
				                break;
				                
				            case 6: 
				                cout<<"Exiting the system......."<<endl; 
				                break;
				                
				            default: 
				                cout<<"Invalid choice! Please enter a valid option."<<endl;
				        }
				    } while (option != 6);
				}
				break;
            
			case 3:
                forgotPassword(); //calling forgot password function
                break;
			case 4:
                quitSystem(); //calling quit system function
                break;
                
            default:
                cout<<"Invalid option. Try again.\n";
        }
    }

    
    
}


//kartik's
// Function to register a new user
void registerUser() {
    string username, password;  

    
    cout<<"\nEnter a new username: ";
    cin>>username;

    // Check if the entered username already exists in the 'users' list
    for (const auto& user : users) {
        if (user.username == username) {  // If a match is found
            cout<<"Username already exists. Try again.\n";
            return;  // Exit the function
        }
    }

    cout<<"Enter a new password: ";
    cin>>password;

    // Generate a new unique Member ID
    int newID = users.size() + 1;  // Calculate a new ID based on the size of the 'users' list
    stringstream ss;  // String stream to create the formatted ID
    ss<<"LIB"<<setw(3)<<setfill('0')<<newID;  // Format ID as 'LIB###' (e.g., LIB001)
    string memberID = ss.str();  // Store the formatted ID as a string

    // Add the new user to the 'users' list
    users.push_back({memberID, username, password});

    // Notify the user of successful registration and display their unique Member ID
    cout<<"\nRegistration successful! Your Member ID is: " << memberID << "\n";
}


// Function to log in a user
bool loginUser() {
    string memberID, username, password;
    cout<<"\nEnter Member ID: ";
    cin>>memberID;
    cout<<"Enter Username: ";
    cin>>username;
    cout<<"Enter Password: ";
    cin>>password;

	// Loop through the list of users to check if the entered credentials match
    for (const auto& user : users) {
    	 // Verify if Member ID, username, and password match for any existing user
        if (user.memberID == memberID && user.username == username && user.password == password) {
            cout<<"\nLogin successful! Welcome, "<<username<<"!\n";
            return true;
        }
    }
    cout<<"\nInvalid Member ID, Username, or Password. Please try again.\n";
    return false;
}

//function if users forgot password
void forgotPassword() {
    string memberID;

    // Prompt the user for their Member ID
    cout << "\nEnter your Member ID: ";
    cin >> memberID;

    // Find the user in the vector
    for (auto& user : users) { // 'users' is assumed to be a global vector storing user data
        if (user.memberID == memberID) {
            // Show the current password
            cout<<"\nYour current password is: " << user.password << "\n";

            // Ask if they want to change the password
            char choice;
            cout<<"Do you want to change your password? (y/n): ";
            cin>>choice;

            if (choice == 'y' || choice == 'Y') {
                string newPassword;
                cout<<"Enter your new password: ";
                cin>>newPassword;

                // Update the password in the vector
                user.password = newPassword;
                cout<<"\nPassword updated successfully!\n";
            } else {
                cout<<"\nPassword remains unchanged.\n";
            }
            return; // Exit the function after processing the request
        }
    }

    // If no matching Member ID is found
    cout << "\nMember ID not found. Please try again.\n";
}


// Function to exit system
void quitSystem() {
    cout<<"\nThank you for using this system! Goodbye!\n";
    exit(0);
}

//krisha's
// Book Display Function
void BookDisplay(Book book[]) {
    cout<<"********************************************************************************************"<<endl;
    cout<<"|\t\t\t\t\tList of Books\t\t\t\t           |" << endl;
    cout<<"********************************************************************************************"<<endl;
    cout<<left<<setw(10)<<"Book ID"<<setw(30)<<"Book Name"<<setw(25)<<"Author"<<setw(15)<<"Pub. Year"<<setw(8)<<"Quantity   |"<<endl;
    cout<< "--------------------------------------------------------------------------------------------"<<endl;
    for (int i = 0; i < S; ++i) {
        cout<<left<<setw(10)<<book[i].id 
            <<setw(30)<<book[i].name 
            <<setw(25)<<book[i].author 
            <<setw(15)<<book[i].pubyear 
            <<setw(15)<<book[i].quantity<<endl;
    }
    cout<<"--------------------------------------------------------------------------------------------"<<endl;
}


//Krisha- Book Borrowing Function
//file processing function for borrowing books
void BorrowBook(Book book[], string memberID) {
    string bookID;
    cout << "\nEnter the Book ID to borrow: ";
    getline(cin, bookID);
    
    // Find the book using linear search
    bool found = false;
    int bookIndex = -1;
    for (int i = 0; i < S; i++) {
        if (book[i].id == bookID && book[i].quantity > 0) {
            found = true;
            bookIndex = i;
            book[i].quantity--;
            break;
        }
    }
    
    if (!found) {
        cout << "\nBook not available or invalid Book ID!" << endl;
        return;
    }
    
    // Get date
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    // Format the dates to avoid spaces - use dashes or underscores instead
    // tm_mday gives the day of the month, tm_mon gives the month (0-indexed, so +1),and tm_year gives the years since 1900 (hence adding 1900).
	string loanDate = to_string(ltm->tm_mday) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(1900 + ltm->tm_year);
    
    // / Calculate the due date, which is 14 days after the loan date of a book
    ltm->tm_mday += 14;
    mktime(ltm); //Normalize the date structure to handle month/year overflow
    string dueDate = to_string(ltm->tm_mday) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(1900 + ltm->tm_year); /// Format due date same way as the loan date

    
    // Save to file - with properly formatted dates
    ofstream write("borrowed_books.txt", ios::app);
    write << memberID << " " << bookID << " " << loanDate << " " << dueDate << endl;
    write.close();
    
    cout<<"\nBook borrowed successfully! Due date: "<<dueDate<<endl;
}

// Book Search Function using linear searching function
void Search(Book book[]) {
    int opt;
    string detail;
    
    do {
        cout<<"*********************************"<<endl;
        cout<<"|\tSearch for a Book\t|"<<endl;
        cout<<"*********************************"<<endl;
        cout<<"Filtering Option"<<endl;
        cout<<"\t1. -> ID\n\t2. -> Name\n\t3. -> Author\n\t4. -> Publication Year"<<endl;
        cout<<"Enter the filter option to search: ";
        cin>>opt;
        cin.ignore();

        if (opt < 1 || opt > 4)
            cout<<"Invalid Input! Please enter option (1/2/3/4)!"<<endl;
    } while (opt < 1 || opt > 4);
    
    cout<<"Enter the detail based on filter selection: ";
    getline(cin, detail);
    cout<<"*********************************\n"<<endl;
    
    //linear searching to search the book based on filter  and details porvided by user
    bool found = false;
    for (int i = 0; i < S; i++) {
        if ((opt == 1 && book[i].id == detail) ||   
            (opt == 2 && book[i].name == detail) ||
            (opt == 3 && book[i].author == detail) ||
            (opt == 4 && to_string(book[i].pubyear) == detail)) {
            
            found = true;
            cout<<"\n---------------------------------"<<endl;
            cout<<"|\tBook Found\t\t|"<<endl;
            cout<<"---------------------------------"<<endl;
            cout<<"Book ID: "<<book[i].id<<endl;
            cout<<"Book Name: "<<book[i].name<<endl;
            cout<<"Author: "<<book[i].author<<endl;
            cout<<"Publication Year: "<<book[i].pubyear<<endl;
            cout<<"Quantity Available: "<<book[i].quantity<<endl;
            cout<<"---------------------------------\n"<<endl;
            break;
        }
    }
    if (!found) {
        cout<<"Book Not Found!"<<endl;
    }
}

//CHLOE'S FUNCTION
 //file processing function for returning books
void ReturnBook(Book book[], string memberID) {
    string bookID;
    cout << "\nEnter the Book ID to return: ";
    getline(cin, bookID);
    
    // Update book quantity
    for (int i = 0; i < S; i++) {
        if (book[i].id == bookID) {
            book[i].quantity++;
            break;
        }
    }
    
    // Update file
    ifstream read("borrowed_books.txt");
    ofstream temp("temp.txt"); // the temporary file is to  replace the original file or to  use as the updated version of the data is the book is returned
    string line;
    bool found = false;
    
    while (getline(read, line)) {
        stringstream ss(line);
        string id, bID, loanDate, dueDate;
        
        // Extracts values from the stream 'ss' into the variables 'id', 'bID', 'loanDate', and 'dueDate'
        if (ss >> id >> bID >> loanDate >> dueDate) {
            if (id == memberID && bID == bookID) {
                found = true; // Skip this record
            
			} else {
            // If the record doesn't match the provided IDs, it is written to a temporary stream/file `temp`.
       		 // The data 'id', 'bID', 'loanDate', and 'dueDate' is appended as a new line.
                temp << id << " " << bID << " " << loanDate << " " << dueDate << endl;
            
			}
            
        }
    }
    
    read.close();
    temp.close();
    
    remove("borrowed_books.txt");
    rename("temp.txt", "borrowed_books.txt");
    
    if (found) {
        cout<<"\nBook returned successfully!"<<endl;
    } else {
        cout<<"\nRecord not found!"<<endl;
    }
}


//wong's
// Update the function declaration to include the book array
void ViewRecord(Book book[], string memberID) {
    ifstream read("borrowed_books.txt");
    if (read.fail()) {
        cout<<"No borrowing records found."<<endl;
        return;
    }
    
    cout<<"\n--- Your Borrowed Books ---"<<endl;
    
    string line;
    bool found = false;
    
    // Read the file line by line
    while (getline(read, line)) {
        stringstream ss(line);
        string id, bookID, loanDate, dueDate;
        
        // Parse the line to extract id, bookID, loanDate, and dueDate
        if (ss >> id >> bookID >> loanDate >> dueDate) {
            if (id == memberID) {
                found = true;
                
                // Find book details
                string bookName = "", author = "";
                int pubYear = 0;
                
                for (int i = 0; i < S; i++) {
                    if (book[i].id == bookID) {
                        bookName = book[i].name;
                        author = book[i].author;
                        pubYear = book[i].pubyear;
                        break;
                    }
                }
                
                cout<<"\nBook ID: "<< bookID<<endl;
                cout<<"Book Name: "<< bookName<<endl; 
                cout<<"Author: "<<author<<endl;
                cout<<"Publication Year: "<<pubYear<<endl;
                cout<<"Loan Date: "<<loanDate<<endl;
                cout<<"Due Date: "<<dueDate<<endl;
                cout<<"------------------------"<<endl;
            }
        }
    }
    
    // Display a message if no borrowed books are found for that member .
    if (!found) {
        cout<<"No books currently borrowed."<<endl;
    }
    
    read.close();
}