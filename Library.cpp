#include "Library.h"
#include "Book.h"
#include <iomanip>
#include "Member.h"
#include "Statistics.h"
#include "CompareByAuthor.h"
#include "CompareByName.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <limits>
#include <fstream>

void Library::AddBook(std::string &BC, std::string &AU, std::string &TTL, std::string &IBN)
{
    // Check for a duplicate BEFORE adding, so a duplicate never ends up in the list
    for (size_t i = 0; i < books.size(); i++)
    {
        if (books[i].GetBarcode() == BC)
        {
            throw "Book already exists";
        }
    }
    books.push_back(Book(BC, AU, TTL, IBN));
    std::cout << "Book added successfully" << std::endl;
}

void Library::AddMember(std::string &name)
{
    // Check for a duplicate BEFORE adding
    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i].GetName() == name)
        {
            throw "Member already exists";
        }
    }
    members.push_back(Member(name));
    std::cout << "Member added successfully" << std::endl;
}

void Library::RemoveBook(const std::string &barcode)
{
    for (size_t i = 0; i < books.size(); i++)
    {
        if (books[i].GetBarcode() == barcode)
        {
            if (books[i].GetAvailable() == false)
            {
                throw "Book is currently borrowed and cannot be removed";
            }
            books.erase(books.begin() + i);
            std::cout << "Book removed successfully" << std::endl;
            return;
        }
    }
    throw "Book not found";
}

void Library::RemoveMember(std::string &name)
{
    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i].GetName() == name)
        {
            if (!members[i].GetBorrowedBooks().empty())
            {
                throw "Member still has borrowed books and cannot be removed";
            }
            members.erase(members.begin() + i);
            std::cout << "Member removed successfully" << std::endl;
            return;
        }
    }
    throw "Member not found";
}
void Library::DisplayBooks()
{
    CompareByAuthor cmp;
    std::cout << std::left << std::setw(10) << "Order" << std::setw(18) << "Barcode" << std::setw(18) << "Author" << std::setw(18) << "Title" << std::setw(18) << "ISBN" << std::setw(10) << "Borrows" << std::setw(18) << "Available" << std::setw(18) << "Stars" << std::setw(18) << "Borrowed By" << std::endl;


    std::sort(books.begin(),books.end(), cmp);
   for(size_t i = 0; i < books.size(); i++)
    {
        books[i].SetBookOrder(static_cast<int>(i)+1);
        std::cout << books[i] << std::endl;
    }

    std::cout << std::endl;
}

void Library::DisplayMembers() const
{
    CompareByName cmp;
    std::cout << std::left << std::setw(20) << "ID" << std::setw(20) << "Name" << std::setw(20) << "Join Date" << std::setw(20) << "Total Read" << std::setw(20) << "Books Borrowed" << std::endl;

    std::vector<const Member *> sortedMembers;
    for (size_t i = 0; i < members.size(); i++)
    {
        sortedMembers.push_back(&members[i]);
    }

    std::sort(sortedMembers.begin(), sortedMembers.end(),
              [&cmp](const Member *a, const Member *b)
              {
                  return cmp(*a, *b);
              });

    for (size_t i = 0; i < sortedMembers.size(); i++)
    {
        std::cout << *sortedMembers[i] << std::endl;
    }
}

void Library::DisplayMember(std::string &name) const
{
    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i].GetName() == name)
        {
            std::cout << members[i] << std::endl;
            return;
        }
    }
    std::cout << "Member not found" << std::endl;
}

bool Library::SearchBook(const std::string &barcode) const
{
    for (size_t i = 0; i < books.size(); i++)
    {
        if (books[i].GetBarcode() == barcode)
        {
            std::cout << books[i] << std::endl;
            return true;
        }
    }
    std::cout << "Book not found" << std::endl;
    return false;
}

bool Library::SearchMember(std::string &name) const
{
    for (size_t i = 0; i < members.size(); i++)
    {
        if (members[i].GetName() == name)
        {
            std::cout << members[i] << std::endl;
            return true;
        }
    }
    std::cout << "Member not found" << std::endl;
    return false;
}

void Library::BorrowBook( int bookOrder, int id)
{
    // Find both the book and the member first, and only change anything
    // once every check has passed.
    int bookIndex = -1;
    int memberIndex = -1;
    for (size_t i = 0; i < books.size(); i++)
    {
        if (books[i].GetBookOrder() == bookOrder)
        {
            bookIndex = static_cast<int>(i);
            break;
        }
    }
    for (size_t j = 0; j < members.size(); j++)
    {
        if (members[j].GetID() == id)
        {
            memberIndex = static_cast<int>(j);
            break;
        }
    }
    if (bookIndex == -1 || memberIndex == -1)
    {
        std::cout << "Book or member not found" << std::endl;
        return;
    }

    Book &book = books[bookIndex];
    Member &member = members[memberIndex];

    if (book.GetAvailable() == false)
    {
        throw "Book is not available";
    }
    if (member.GetBorrowedBooks().size() >= 3)
    {
        throw "Member has already borrowed 3 books";
    }

    book.Borrow();
    book.SetAvailable(false);
    book.SetBorrowedBy(id);
    member.SetBorrowedBooks(book);
    member.SetNumberOfBooksBorrowedByMember();
    std::cout << "Book borrowed by member" << std::endl;
}

void Library::ReturnBook(int bookOrder, int id)
{
    int bookIndex = -1;
    int memberIndex = -1;
    for (size_t i = 0; i < books.size(); i++)
    {
        if (books[i].GetBookOrder() == bookOrder)
        {
            bookIndex = static_cast<int>(i);
            break;
        }
    }
    for (size_t j = 0; j < members.size(); j++)
    {
        if (members[j].GetID() == id)
        {
            memberIndex = static_cast<int>(j);
            break;
        }
    }
    if (bookIndex == -1 || memberIndex == -1)
    {
        std::cout << "Book or member not found" << std::endl;
        return;
    }

    Book &book = books[bookIndex];
    Member &member = members[memberIndex];

    if (book.GetAvailable() == true)
    {
        throw "Book is already available";
    }
    if (!member.HasBorrowed(book.GetBarcode()))
    {
        throw "This member did not borrow this book";
    }

    // Keep asking until the rating is a number from 1 to 5
    int st = 0;
    while (true)
    {
        std::cout << "Rate the book from 1 to 5 stars :";
        if (std::cin >> st && st >= 1 && st <= 5)
        {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid rating" << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    book.SetStars(st);
    book.SetAvailable(true);
    book.SetBorrowedBy(0);
    member.returnBook(book);
    std::cout << "Book returned by member" << std::endl;
}

Statistics Library::getStatistics() const
{
    return Statistics(books, members);
}

void Library::DisplayStatistics() const
{
    std::cout << getStatistics() << std::endl;
}

void  Library::ExportForChatbot(const std::string &fileName) const
{
    std::ofstream out(fileName);
    if(!out)
    {
        throw "Could not create the export file";
    }

    int availableCount = 0;
    for (size_t i = 0; i < books.size(); i++)
    {
        const Book &b = books[i];

        out <<"The book \"" << b.GetTitle()<< "\" by " << b.GetAuthor()
            <<" (ISBN "<< b.GetISBN() << ") is "
            << (b.GetAvailable() ? "available to borrow" : "currently borrowed and not available")
            <<". It has been borrowed " << b.GetBorrowed() << " times";
        
            if (b.GetStars() > 0)
            {
                out << " and has an average rating of " << b.GetStars() <<" out of 5 stars";
            }
            else
            {
                out<< " and has no ratings yet";
            }
            out << ".\n";
            if(b.GetAvailable())
            {
                availableCount++;
            }
    }
    out<<"List of all the books in the library's collection (full catalogue): ";
    for(size_t i=0; i <books.size(); i++)
    {
        out <<"\"" << books[i].GetTitle() <<"\" by " << books[i].GetAuthor();
        if(i+1 <books.size())
        {
            out<<", ";
        }
    }
    out <<".\n";
    out << "The library has "<<books.size()<<" books in total, and "
        <<availableCount << " of them are available to borrow right now. \n";
    out << "The library has " << members.size() << " registered members.\n"; 
}