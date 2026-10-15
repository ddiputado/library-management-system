#pragma once
#include "Book.h"
#include <iostream>

class CompareByBorrowed
{
public:
    bool operator()(const Book &m1, const Book &m2) const
    {
        return m1.GetBorrowed() > m2.GetBorrowed();
    }
};