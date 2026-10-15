#pragma once
#include "Book.h"
#include <iostream>
class CompareByStars
{
public:
    bool operator()(const Book &m1, const Book &m2) const
    {
        return m1.GetStars() > m2.GetStars();
    }
};