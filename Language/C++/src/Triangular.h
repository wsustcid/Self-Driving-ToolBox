/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-10 14:56:18
 * @LastEditTime: 2021-11-12 19:08:12
 */
// #ifndef TRIANGULAR_H
// #define TRIANGULAR_H
#include<string>
#include<vector>
#include<iostream>
using namespace std;

/*Iterator Class **/
class Triangular_iterator{
    // friend int operator*(const Triangular_iterator &rhs);
public:
    Triangular_iterator(int index): _index(index-1) {} // 直接初始化减1，不用每次访问时减1
    bool operator==(const Triangular_iterator &) const;
    bool operator!=(const Triangular_iterator &) const;
    int  operator*() const;
    Triangular_iterator& operator++(); // 前置
    Triangular_iterator operator++(int); // 后置

private:
    void check_integrity() const;
    int _index;
};


/** Triangular Class **/
class Triangular
{
    // 8. friend
    friend class Triangular_iterator;
    // friend inline int operator*(const Triangular_iterator &rhs);
public:
    // 1. 构造函数
    Triangular(); // 1.1 默认构造函数，不接受任何参数，直接指定默认值
    Triangular(int len); // 1.2 接受一个参数
    Triangular(int len, int beg_pos); // 1.3 接受两个参数; 
    // 我们也可以为每个参数提供了默认值:Triangular(int len=1, int beg_pos=1);

    // 2. const member function
    int length() const { return _length; }
    int beg_pos() const { return _beg_pos; }
    int elem(int pos) const;

    // 3. non-const member function
    bool next(int &val) ;
    void next_reset() { _next = _beg_pos+1; }

    // 6. static member function
    static bool is_elem(int value);
    static void gen_elements(int length);
    static void gen_elements_to_value(int value);
    static void display(int length, int beg_pos, ostream &os=cout);
    
    Triangular& operator=( const Triangular &rhs );
    
    // 7. Iterator class
    typedef Triangular_iterator iterator; // 这样用户就不用知道iterator class的实际名称
    Triangular_iterator begin() const {return Triangular_iterator(_beg_pos); }
    Triangular_iterator end() const {return Triangular_iterator(_beg_pos+_length); }

    // 8. friend
    // friend int Triangular_iterator::operator*() const;
    
    // friend void Triangular_iterator::check_integrity();

private:
    int _length;  // 元素个数
    int _beg_pos; // 起始位置
    // 4. mutable data member
    mutable int _next;    // 下一个迭代目标

    string _name;

    // 5. static data member
    static vector<int> _elems;
    static const int _max_elems = 1024;
};




inline bool Triangular_iterator::operator==(const Triangular_iterator &rhs) const
{
    return _index == rhs._index;
}

inline bool Triangular_iterator::operator!=(const Triangular_iterator &rhs) const
{
    return !(*this == rhs); // 当某个运算符和另一个运算符性质相反时，我们直接用后者实现前者
}

// member function的定义方式
inline int Triangular_iterator::operator*() const
{
    check_integrity();
    return Triangular::_elems[_index];
}
// non-member function 的定义方式
// non-member function 的参数列表中，一定会比相应的member运算符多出一个参数，也就是this指针
// 对member运算符而言，这个this指针隐式的代表左操作数
// inline int operator*(const Triangular_iterator &rhs)
// {   
//     // 注意，这是一个non-member function,就不具有访问non-public member 的权利
//     rhs.check_integrity();
//     return Triangular::_elems[_index];
// }

class iterator_overflow{};

inline void Triangular_iterator::check_integrity() const
{
    if (_index >= Triangular::_max_elems) throw iterator_overflow();

    if (_index >= Triangular::_elems.size())
    {
        Triangular::gen_elements(_index+1);
    }
}

inline Triangular_iterator& Triangular_iterator::operator++()
{
    ++_index;
    check_integrity();
    return *this;
}

inline Triangular_iterator Triangular_iterator::operator++(int)
{
    // 这里我们为何加了个int参数呢？它从哪里来，又到哪里去？
    // 编译器会自动为后置版产生一个int参数，其值为0，我们不用关注
    Triangular_iterator tmp = *this;
    ++_index;
    check_integrity();
    return tmp;
}