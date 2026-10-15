#pragma once
#include <iostream>
#include "Book.h"
#include <string>
#include <vector>

class Member{
private:
static int nextID;
int ID=0,NumberOfBooksBorrowed=0;
std::string Name,JoinDate;
// Stores copies of the borrowed books (not pointers), because pointers into
// the Library's vector become invalid when that vector grows or is sorted.
std::vector<Book> borrowedBooks;

public:
Member()=default;
Member(std::string name){
SetName(name);
SetID();
SetDate();
}

void SetID();
void SetDate();
void SetName(const std::string name);
void SetNumberOfBooksBorrowedByMember();
void SetBorrowedBooks(const Book& book);
void returnBook(const Book& book);
bool HasBorrowed(const std::string& barcode) const;

int GetID()const;
std::string GetDate()const;
std::string GetName()const;
int GetNumberOfBooksBorrowed()const;
std::vector<Book> GetBorrowedBooks()const;
// Copy/move constructors and assignment operators are left to the compiler.
friend std::ostream& operator<<(std::ostream& os, const Member& member);
bool operator<(const Member& other) const;
bool operator==(const Member& other) const;
~Member()=default;
};
