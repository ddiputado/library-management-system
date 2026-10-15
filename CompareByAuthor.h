#pragma once
#include "Book.h"
#include <string>

class CompareByAuthor
{
    public:
    bool operator()(const Book &a, const Book &b)const
    {
        return a.GetAuthor() < b.GetAuthor();
    }
};