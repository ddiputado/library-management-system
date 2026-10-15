#include "Statistics.h"
#include "Book.h"
#include "Member.h"
#include "Library.h"
#include "CompareByBorrowed.h"
#include "CompareByBorrows.h"
#include "CompareByStars.h"
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void Statistics::SetOlderMember()
{
    if (members.empty())
    {
        this->OlderMember = Member();
        return;
    }

    this->OlderMember = members[0];
}

void Statistics::SetTop3MostBorrowedBooks()
{
    std::vector<Book> sortedBooks = books;
    CompareByBorrowed cmp;
    if (books.size() >= 3)
    {

        std::sort(sortedBooks.begin(), sortedBooks.end(), cmp);
        for (int i = 0; i < 3; ++i)
        {
            Top3MostBorrowedBooks.push_back(sortedBooks[i]);
        }
    }
}
void Statistics::SetTop3MostRatedBooks()
{
    CompareByStars cmp;
    std::vector<Book> sortedBooks = books;
    if (books.size() >= 3)
    {
        std::sort(sortedBooks.begin(), sortedBooks.end(), cmp);
        for (int i = 0; i < 3; i++)
        {
            Top3MostRatedBooks.push_back(sortedBooks.at(i));
        }
    }
}
std::vector<Book> Statistics::GetTop3MostBorrowedBooks() const
{
    return Top3MostBorrowedBooks;
}
std::vector<Member> Statistics::GetTop3MostActiveMembers() const
{
    return Top3MostActiveMembers;
}
std::vector<Book> Statistics::GetTop3MostRatedBooks() const
{
    return Top3MostRatedBooks;
}
Member Statistics::GetOlderMember() const
{
    return OlderMember;
}
int Statistics::GetTotalBooks() const
{
    return static_cast<int>(books.size());
}
int Statistics::GetTotalMembers() const
{
    return static_cast<int>(members.size());
}

void Statistics::SetTop3MostActiveMembers()
{
    CompareByBorrows cmp;
    if (members.size() >= 3)
    {
        std::sort(members.begin(), members.end(), cmp);
        for (int i = 0; i < 3; i++)
        {
            Top3MostActiveMembers.push_back(members[i]);
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Statistics &stats)
{
    os << "Total Books: " << stats.GetTotalBooks() << std::endl;
    os << "Total Members: " << stats.GetTotalMembers() << std::endl;
    os << "Oldest Member: " << stats.GetOlderMember() << std::endl;
    os << "Top 3 Most Borrowed Books: " << std::endl;
    if (stats.Top3MostBorrowedBooks.size() < 3)
    {
        os << "Not enough books to display statistics." << std::endl;
    }
    else if (stats.Top3MostBorrowedBooks.size() >= 3)
    {
        os << std::left << std::setw(10) << "Order" << std::setw(18) << "Barcode" << std::setw(18) << "Author" << std::setw(18) << "Title" << std::setw(18) << "ISBN" << std::setw(10) << "Borrows" << std::setw(18) << "Available" << std::setw(18) << "Stars" << std::setw(18) << "Borrowed By" << std::endl;
        for (int i = 0; i < 3; i++)
        {
            os << stats.GetTop3MostBorrowedBooks()[i] << std::endl;
        }
    }

    os << "Top 3 Most Active Members: " << std::endl;
    if (stats.Top3MostActiveMembers.size() < 3)
    {
        os << "Not enough members to display statistics." << std::endl;
    }
    else if (stats.Top3MostActiveMembers.size() >= 3)
    {
        os << std::left << std::setw(20) << "ID" << std::setw(20) << "Name" << std::setw(20) << "Join Date" << std::setw(20) << "Total Read" << std::setw(20) << "Books Borrowed" << std::endl;
        for (int i = 0; i < 3; i++)
        {
            os << stats.GetTop3MostActiveMembers()[i] << std::endl;
        }
    }
    os << "Top 3 Most Rated Books: " << std::endl;

    if (stats.GetTop3MostRatedBooks().size() < 3)
    {
        os << "Not enough books to display statistics." << std::endl;
    }
    else if (stats.Top3MostRatedBooks.size() >= 3)
    {
        os << std::left << std::setw(10) << "Order" << std::setw(18) << "Barcode" << std::setw(18) << "Author" << std::setw(18) << "Title" << std::setw(18) << "ISBN" << std::setw(10) << "Borrows" << std::setw(18) << "Available" << std::setw(18) << "Stars" << std::setw(18) << "Borrowed By" << std::endl;
        for (int i = 0; i < 3; i++)
        {
            os << stats.GetTop3MostRatedBooks()[i] << std::endl;
        }
    }

    return os;
}
