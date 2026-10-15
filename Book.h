#pragma once
#include <iostream>
#include <string>
class Book{
private:
std::string barcode,title,isbn;
int Borrowed=0,stars=0,borrowedBy=0,totalStars=0,bookOrder=0;
bool available=true;
std::string author="n/a";
public:
Book()=default;
Book(std::string BC,std::string AU,std::string TTL,std::string IBN){
    SetBarcode(BC);
    SetAuthor(AU);
    SetTitle(TTL);
    SetISBN(IBN);
}
void SetBarcode(const std::string BC);
void SetAuthor(const std::string AU);
void SetTitle(const std::string TTL);
void SetISBN(const std::string IBN);
void Borrow();
void SetStars(int s);
void SetAvailable(bool a);
void SetBorrowedBy(int id);
void SetBookOrder(int order);


std::string GetBarcode()const ;
std::string GetAuthor()const ;
std::string GetTitle()const ;
std::string GetISBN()const ;
int GetStars()const ;
bool GetAvailable()const ;
int GetBorrowed()const ;
int GetBorrowedBy()const ;
int GetBookOrder()const ;

// Copy/move constructors and assignment operators are left to the compiler,
// so every member (including totalStars and bookOrder) is copied correctly.
friend std::ostream& operator<<(std::ostream& os, const Book& book);
bool operator<(const Book& other) const;
bool operator==(const Book& other) const;


~Book()=default;




};
