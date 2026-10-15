#pragma once
#include "Member.h"
class CompareByName
{
public:
    bool operator()(const Member &a, const Member &b) const
    {
        return a.GetName() < b.GetName();
    }
};