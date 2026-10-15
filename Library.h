#pragma once
#include <iostream>
#include "Book.h"
#include "Member.h"
#include "Statistics.h"
#include <vector>
#include <string>
class Library{
private:
    std::vector<Book> books;
    std::vector<Member> members;

public:

    Library()=default;
    void AddBook(std::string& BC,std::string& AU,std::string& TTL,std::string& IBN);
    void AddMember(std::string& name);
    void RemoveBook(const std::string& barcode);
    void RemoveMember(std::string& name);
    void DisplayBooks();
    void DisplayMembers() const;
    void DisplayMember(std::string& name) const;
    bool SearchBook(const std::string& barcode) const;
    bool SearchMember(std::string& name) const;
    void BorrowBook(int bookOrder, int  id);
    void ReturnBook(int bookOrder, int  id);
    Statistics getStatistics() const;
    void DisplayStatistics() const;
    void ExportForChatbot(const std::string& fileName)const;

    ~Library()=default;

};
