#pragma once
#include <vector>
#include "Book.h"
#include "Member.h"
#include <iostream>
#include <string>
class Statistics
{
private:
    int TotalBooks, TotalMembers;
    std::vector<Book > books;
    std::vector<Member > members;
    std::vector<Book > Top3MostBorrowedBooks;
    std::vector<Member > Top3MostActiveMembers;
    std::vector<Book    > Top3MostRatedBooks;
    Member OlderMember;

public:
    Statistics() = default;
    Statistics(const std::vector<Book> &Bookss, const std::vector<Member> &Memberss)
    {  
        books = Bookss;
        members = Memberss;
        if (books.empty())
        {
            throw "No books available";
        }
        if (members.empty())
        {
            throw "No members available";
        }
        SetOlderMember();
        SetTop3MostBorrowedBooks();
        SetTop3MostActiveMembers();
        SetTop3MostRatedBooks();
    }
    void SetOlderMember();
    void SetTop3MostBorrowedBooks();
    void SetTop3MostActiveMembers();
    void SetTop3MostRatedBooks();
    std::vector<Book > GetTop3MostBorrowedBooks() const;
    std::vector<Member > GetTop3MostActiveMembers() const;
    std::vector<Book > GetTop3MostRatedBooks() const;
    int GetTotalBooks() const;
    int GetTotalMembers() const;
    Member GetOlderMember() const;
    friend std::ostream &operator<<(std::ostream &os, const Statistics &stats);
    ~Statistics() = default;
};