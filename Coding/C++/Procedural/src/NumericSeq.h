/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-04-23 11:17:12
 * @LastEditTime: 2022-04-24 16:03:38
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits> // numeric_limits

using namespace std;

// 函数声明：函数声明后才能被调用
bool fibon_elem(int, int&);
bool print_sequence(int pos);
void print_msg(const string &msg, ostream &os);

// 函数参数指定默认值
void display(const vector<int>&, ostream& =cout);
void display(const vector<int> *vec);

// inline 函数: 定义通常放置于头文件中
inline bool is_size_ok(int size)
{
    const int max_size = 1024;
    if (size<=0 || size>max_size)
    {
        cerr << "Invalid size! "<< endl;
        return false;
    }
    return true;
}

// 函数重载: 根据参数匹配具体的函数
void display_msg(char ch);
void display_msg(const string&);
void display_msg(const string&, int);
void display_msg(const string&, int, int);
//无法重载：ostream& display_msg(char ch); bool display_msg(char ch);


// 模板函数: 从单一的函数内容中抽离出不同的参数类型信息
void display_msg(const string&, const vector<int>&);
void display_msg(const string&, const vector<double>&);
void display_msg(const string&, const vector<string>&);

// 函数重载配合函数模板，使得通过一个函数名就可以处理多种情况：不论是函数参数还是参数类型


// 对象声明：file scope 内定义的对象如果可能被多个文件使用，就应该将其放于头文件中进行声明，关键字为 extern
const int seq_cnt = 6; // const对象声明不用加关键字
extern const vector<int>* (*seq_array[seq_cnt])(int); // 这个对象本身并不是const的，其指向内容是const
