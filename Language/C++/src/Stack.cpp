/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-10 10:27:12
 * @LastEditTime: 2021-11-10 14:47:50
 */

#include "Stack.h"

// 5. non-inline member funtion
bool Stack::pop(string &elem)
{
    if (empty()) return false; // 因为已经进行了类作用域解析，成员函数可直接使用

    elem = _stack.back();
    _stack.pop_back();
    return true;
}

bool Stack::peek(string &elem)
{
    if (empty()) return false;

    elem = _stack.back();
    return true;
}

bool Stack::push(const string &elem)
{
    if (full()) return false;

    _stack.push_back(elem);
    return true;
}

bool Stack::find(const string &elem)
{
    if (empty()) return false;
    for (string str : _stack) if (str==elem) return true;
    return false;
}

int Stack::count(const string &elem)
{
    if (empty()) return 0;
    int count =0;
    for (string str : _stack) if (str==elem) count++;
    return count;
}