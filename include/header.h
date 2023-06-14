#pragma once
#ifndef __HEADER_H__
#define __HEADER_H__

#include <iostream>
#include <thread>

#define log(x) std::cout << x << std::endl;

struct ListNode
{
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode *next) : val(val), next(next) {}
};

#endif  // __HEADER_H__