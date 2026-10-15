#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Library.h"
#include "Statistics.h"
#include <iomanip>
#include <limits>
using namespace std;

int main()
{
    string choice = "-1";
    Library library;

    std::cout << "Welcome to the Library Management System!" << std::endl;
    while (choice != "0")
    {
        cout << "1. Add Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. Register Member" << endl;
        cout << "4. Unregister Member" << endl;
        cout << "5. Borrow Book" << endl;
        cout << "6. Return Book" << endl;
        cout << "7. Display Books" << endl;
        cout << "8. Display Members" << endl;
        cout << "9. Show Statistics" << endl;
        cout << "10. Load Books from File" << endl;
        cout << "11. Register Member from File" << endl;
        cout << "12. Export for Chatbot"<<endl;
        cout << "0. Exit" << endl;
        cout << "Option: ";
        getline(cin, choice);

        if (choice == "1")
        {
            string BC, AU, TTL, IBN;
            while (true)
            {
                try
                {

                    string inputLine;
                    cout << "Enter Book Info (Barcode|Author|Title|ISBN)or '0' to return to menu: ";
                    getline(cin, inputLine);

                    if (inputLine == "0")
                    {
                        break;
                    }

                    stringstream ss(inputLine);
                    getline(ss, BC, '|');
                    getline(ss, AU, '|');
                    getline(ss, TTL, '|');
                    getline(ss, IBN, '|');

                    library.AddBook(BC, AU, TTL, IBN);
                    cout << endl;
                    inputLine.clear();
                }

                catch (const char *msg)
                {
                    cout << msg << endl;
                }
            }
        }
        else if (choice == "2")
        {
            string BC;
            while (true)
            {
                cout << "Enter Book Barcode or '0' to return to menu: ";
                getline(cin, BC);
                if (BC == "0")
                {
                    break;
                }
                try
                {
                    library.RemoveBook(BC);
                    break;
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                }
            }
            cout << endl;
        }
        else if (choice == "3")
        {
            string name;
            while (true)
            {
                cout << "Enter Member Name or '0' to return to menu: ";
                getline(cin, name);
                if (name == "0")
                {
                    break;
                }
                std::cout << std::left << std::setw(20) << "ID" << std::setw(20) << "Name" << std::setw(20) << "Join Date" << std::setw(20) << "Total Read" << std::setw(20) << "Books Borrowed" << std::endl;
                try
                {
                    library.AddMember(name);
                    library.DisplayMember(name);
                    cout << endl;
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                }
            }
        }
        else if (choice == "4")
        {
            string name;
            while (true)
            {
                cout << "Enter Member Name or '0' to return to menu: ";
                getline(cin, name);
                if (name == "0")
                {
                    break;
                }
                try
                {
                    library.RemoveMember(name);
                    break;
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                }
                cout << endl;
            }
        }
        else if (choice == "5")
        {
            while (true)
            {
                library.DisplayBooks();
                cout << endl;
                
                int id, bookOrder;
                cout << "Enter Book Order or '0' to return to menu: ";
                if (!(cin >> bookOrder))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a number" << endl;
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (bookOrder == 0)
                {
                    break;
                }
                cout << "Enter Member ID or '0' to return to menu: ";
                if (!(cin >> id))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a number" << endl;
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (id == 0)
                {
                    break;
                }
                try
                {
                    library.BorrowBook(bookOrder, id);
                    cout << endl;
                    break;
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                }
            }
        }
        else if (choice == "6")
        {
            while (true)
            {
                library.DisplayBooks();
                cout << endl;
               
                int id, bookOrder;
                cout << "Enter Book Order or '0' to return to menu: ";
                if (!(cin >> bookOrder))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a number" << endl;
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (bookOrder == 0)
                {
                    break;
                }
                cout << "Enter Member ID or '0' to return to menu: ";
                if (!(cin >> id))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a number" << endl;
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (id == 0)
                {
                    break;
                }
                try
                {
                    library.ReturnBook(bookOrder,id);
                    cout << endl;
                    break;
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                }
            }
        }
        else if (choice == "7")
        {
            library.DisplayBooks();
            cout << endl;
        }
        else if (choice == "8")
        {
            library.DisplayMembers();
            cout << endl;
        }
        else if (choice == "9")
        {
            try
            {
                library.DisplayStatistics();
            }
            catch (const char *msg)
            {
                cout << msg << endl;
            }
            cout << endl;
        }
        else if (choice == "0")
        {
            cout << "Exiting..." << endl;
        }
        else if (choice == "10")
        {
            string fileName;
            cout << "Enter the Books file name:";
            getline(cin, fileName);
            ifstream file(fileName);

            if (!file)
            {
                cout << "Error opening file " << fileName << endl;
                continue;
            }
            string line;
            while (std::getline(file, line))
            {
                if (!line.empty() && line.back() == '\r')
                {
                    line.pop_back(); // remove Windows line ending
                }
                std::stringstream ss(line);
                std::string BC, AU, TTL, IBN;

                if (std::getline(ss, BC, '|') &&
                    std::getline(ss, AU, '|') &&
                    std::getline(ss, TTL, '|') &&
                    std::getline(ss, IBN))
                {

                    try
                    {
                        library.AddBook(BC, AU, TTL, IBN);
                    }
                    catch (const char *msg)
                    {
                        cout << "Skipped line \"" << line << "\": " << msg << endl;
                    }
                }
                else
                {
                    std::cerr << "Invalid line format: " << line << std::endl;
                }
            }
            file.close();
        }
        else if (choice == "11")
        {
            string fileNamee;
            cout << "Enter the Members file name:";
            getline(cin, fileNamee);
            ifstream file(fileNamee);

            if (!file)
            {
                cout << "Error opening file " << fileNamee << endl;
                continue;
            }
            string Line;
            while (std::getline(file, Line))
            {
                if (!Line.empty() && Line.back() == '\r')
                {
                    Line.pop_back(); // remove Windows line ending
                }
                std::stringstream ss(Line);
                std::string name;

                if (std::getline(ss, name))
                {

                    try
                    {
                        library.AddMember(name);
                    }
                    catch (const char *msg)
                    {
                        cout << "Skipped member \"" << name << "\": " << msg << endl;
                    }
                }
                else
                {
                    std::cerr << "Invalid Names format: " << Line << std::endl;
                }
            }
            file.close();
        }
        else if(choice == "12" ){
            string fileName;
            cout << "Enter the export file path: ";
            getline(cin,fileName);
            try
            {
                library.ExportForChatbot(fileName);
                cout << "Exported for the chatbot." << endl;
            }  
            catch(const char *msg)
            {
                cout << msg <<endl;
            } 
        }
        else
        {
            choice = "-1";
        }
    }
}
