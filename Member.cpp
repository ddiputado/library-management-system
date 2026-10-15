#include "Member.h"
#include <chrono>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <iostream>

#include <string>

int Member::nextID = 1000;

void Member::SetID()
{
    ID = nextID;
    nextID++;
}

std::string Member::GetName() const
{
    return Name;
}

int Member::GetID() const
{
    return ID;
}
std::string Member::GetDate() const
{
    return JoinDate;
}

int Member::GetNumberOfBooksBorrowed() const
{
    return NumberOfBooksBorrowed;
}

std::vector<Book> Member::GetBorrowedBooks() const
{
    return borrowedBooks;
}

void Member::SetName(const std::string name)
{
    Name = name;
}
void Member::SetNumberOfBooksBorrowedByMember()
{
    NumberOfBooksBorrowed++;
}
void Member::SetBorrowedBooks(const Book &book)
{
    borrowedBooks.push_back(book);
}
void Member::returnBook(const Book &book)
{
    for (size_t i = 0; i < borrowedBooks.size(); i++)
    {
        if (borrowedBooks[i].GetBarcode() == book.GetBarcode())
        {
            borrowedBooks.erase(borrowedBooks.begin() + i);

            return;
        }
    }
}
bool Member::HasBorrowed(const std::string &barcode) const
{
    for (size_t i = 0; i < borrowedBooks.size(); i++)
    {
        if (borrowedBooks[i].GetBarcode() == barcode)
        {
            return true;
        }
    }
    return false;
}
bool Member::operator<(const Member &other) const
{
    if (Name < other.Name)
    {
        return true;
    }
    else if (Name == other.Name)
    {
        return ID < other.ID;
    }
    return false;
}
bool Member::operator==(const Member &other) const
{
    return ID == other.ID && Name == other.Name && JoinDate == other.JoinDate;
}
void Member::SetDate()
{
    using namespace std::chrono;

    auto currentTime = system_clock::now();
    std::time_t seconds = system_clock::to_time_t(currentTime);
    std::tm *date = std::localtime(&seconds);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << date->tm_mday << "/"
        << std::setw(2) << std::setfill('0') << date->tm_mon + 1 << "/"
        << std::setw(4) << std::setfill('0') << date->tm_year + 1900;

    JoinDate = oss.str();
}

std::ostream &operator<<(std::ostream &os, const Member &member)
{
   os<<std::left<<std::setw(20)<<member.GetID()<<std::setw(20)<<member.GetName()<<std::setw(20)<<member.GetDate()<<std::setw(20)<<member.GetNumberOfBooksBorrowed()<<std::setw(30);
   std::vector<Book> borrowed = member.GetBorrowedBooks();
   if(borrowed.size() == 0)
   {
       os<<"No borrowed books"<<std::endl;
   }
   else{

   for(size_t i=0;i<borrowed.size();i++)
   {

    if(i>0){
        for(int j=0;j<80;j++){
            os<<' ';
        }
       }
       os<<std::setw(30)<<borrowed[i].GetTitle()<<std::endl;

   }
}
  os<<std::endl;
   os<<"---------------------------------------------------------------------------------------------------"<<std::endl;
   return os;
}
