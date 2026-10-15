#include "Book.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <cctype>


void Book::SetBarcode(const std::string BC)
{
    
    if(BC.size()!=12){
        throw "The barcode must be 12 digits";
    }
    barcode=BC;
}


    

    void Book::SetAuthor(const std::string AU)
    {
        if(AU.empty()){
            throw "Must input Author name";
        }
        author=AU;
    }

    void Book::SetTitle(const std::string TTL)
    {
        if(TTL.empty()){
            throw "Must input Title name";
        }
        title=TTL;
    }

    void Book::SetISBN(const std::string IBN)
    {
        if(IBN.size()!=17){
            throw "ISBN must be in this format:XXX-X-XX-XXXXXX-X";
        }
        if(IBN.substr(0,3)!="978"&&IBN.substr(0,3)!="979"){
            throw "ISBN must start with 978-... or 979-...";
        }
        if(IBN[4]<'0'||IBN[4]>'7'){
            throw "4th digit must be 0-7";                                    
        }                           
        for(int i=6;i<8;i++){
          if(!isdigit(static_cast<unsigned char>(IBN[i]))){
            throw "ISBN must be in this format:XXX-X-XX-XXXXXX-X";
          }
            
        }
        for(int i=9;i<15;i++){
            if(!isdigit(static_cast<unsigned char>(IBN[i]))){
              throw "ISBN must be in this format:XXX-X-XX-XXXXXX-X";
            }
              
          }
          if(!isdigit(static_cast<unsigned char>(IBN[16]))||IBN[3]!='-'||IBN[5]!='-'||IBN[8]!='-'||IBN[15]!='-'){
            throw "ISBN must be in this format:XXX-X-XX-XXXXXX-X";
          }
          isbn=IBN;
    }

    void Book::Borrow()
    {
        Borrowed++;
    }

    void Book::SetStars(int s)
    {
        
        
        if(s<1||s>5){
            throw "Invalid rating";
        }
        totalStars += s;
        if(Borrowed>0){
            stars = totalStars / Borrowed;
        }

    }
    
    
    

    void Book::SetAvailable(bool a)
    {
        available=a;
    }

    void Book::SetBorrowedBy(int id)
    {
        
        borrowedBy=id;
    }

    void Book::SetBookOrder(int order)
    {
        bookOrder=order;
    }

    std::string Book::GetBarcode()const
    {
        return barcode;
    }

    std::string Book::GetAuthor() const
    {
        return author;
    }

    std::string Book::GetTitle() const
    {
        return title;
    }

    std::string Book::GetISBN() const
    {
        return isbn;
    }

    bool Book::GetAvailable() const
    {
        return available;

       
    }
    int Book::GetBorrowed() const
    {
        return Borrowed;
        
    }
    int Book::GetBorrowedBy() const
    {
        return borrowedBy;
    }
    int Book::GetBookOrder() const
    {
        return bookOrder;
    }
    int Book::GetStars() const
    {
        return stars;
    }
    bool Book::operator<(const Book &other) const
    {
        if(title < other.title)
        {
            return true;
        }
        else if(title == other.title)
        {
            return author < other.author;
        }
        else{
            return false;
        }
        
    }

    bool Book::operator==(const Book &other) const
    {
        return barcode == other.barcode ;
    }

    std::ostream &operator<<(std::ostream &os, const Book &book)
    {
        std::string shortenedTitle;
        std::string shortenedAuthor;
        if(book.GetTitle().size() > 12)
        {
            shortenedTitle = book.GetTitle().substr(0, 12) + "...";
        }
        else
        {
            shortenedTitle = book.GetTitle();
        }
        if(book.GetAuthor().size() > 13)
        {
            shortenedAuthor = book.GetAuthor().substr(0, 13) + "...";
        }
        else
        {
            shortenedAuthor = book.GetAuthor();
        }
        os <<std::left<<std::setw(10)<< book.GetBookOrder() <<std::setw(18)<<  book.GetBarcode() <<std::setw(18)<<shortenedAuthor<<std::setw(18)<< shortenedTitle <<std::setw(19)<<book.GetISBN() <<std::setw(10)<<book.GetBorrowed()<<std::setw(18);


        if(book.GetAvailable()==true)
        {
            os <<std::left<< "Yes";
        }
        else
        {
            os <<std::left<< "No";
        }
        os << std::setw(18);
       
        if(book.GetStars() == 0)
        {
            os <<std::left<< "No rating yet";
        }
        else
        {
            os <<std::left<< book.GetStars();
        }
        os << std::setw(18);
     if(book.GetBorrowedBy()>0){
        os << book.GetBorrowedBy() << "\n";
     }
     else{
        os<<"Not Borrowed Yet"<<"\n";
     }
         os << "-----------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
        return os;

    }
