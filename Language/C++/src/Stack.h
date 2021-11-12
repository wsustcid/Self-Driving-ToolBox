/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-10 10:27:05
 * @LastEditTime: 2021-11-10 14:44:03
 */

#include<vector>
#include<string>
using namespace std;

class Stack; // 1. class 前置声明：关键字class + 类名

// 2. class 定义：声明 + 主体
class Stack
{
public: 
    bool push(const string&);
    bool pop(string &elem);
    bool peek(string &elem);

    bool empty();
    bool full();

    int size() {return _stack.size();} // 成员函数定义

    bool find(const string &elem);
    int count(const string &elem);

private:
    vector<string> _stack;

};

// 3. inline member function
inline bool Stack::empty()
{
    return _stack.empty();
}

inline bool Stack::full()
{
    return _stack.size() == _stack.max_size();
}