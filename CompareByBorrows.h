#pragma once
#include "Member.h"

class CompareByBorrows
{
public:
    bool operator()(const Member &m1, const Member &m2) const
    {
        return m1.GetNumberOfBooksBorrowed() > m2.GetNumberOfBooksBorrowed();
    }
};