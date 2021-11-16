/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-12 19:56:40
 * @LastEditTime: 2021-11-15 19:54:46
 */
#include<iostream>
#include<vector>
using namespace std;

// 抽象基类
class num_sequence{
public:
    // 派生类覆盖
    virtual ~num_sequence() {};
    virtual const char* what_am_i() const = 0; // 返回确切的数列类型
    
    // 公共接口，供派生类直接继承
    int elem( int pos ) const; // 返回pos位置上的元素
    ostream& print( ostream &os=cout ) const; // 将所有元素写入os

    int length() { return _length; };
    int beg_pos() { return _beg_pos; };
    static int max_elems(){return 64;}; // 返回支持的最大位置值

protected:
    virtual void gen_elems( int pos) const = 0; // 产生直到pos位置的所有元素

    bool check_integrity( int pos, int size ) const; // 检查pos是否为有效位置
    
    num_sequence(int len, int bp, vector<int> &re): 
    _length(len), _beg_pos(bp), _relems(re) {}

    int _length;
    int _beg_pos;
    vector<int>& _relems;

};


 // 派生类
class Fibonacci : public num_sequence {
public:
    Fibonacci(int len=1, int beg_pos=1);

    virtual const char* what_am_i() const { return "Fibonacci"; };

protected:
    virtual void gen_elems(int pos) const;
    static vector<int> _elems;
    
};

inline Fibonacci::Fibonacci(int len, int beg_pos): num_sequence(len, beg_pos, _elems) {}
