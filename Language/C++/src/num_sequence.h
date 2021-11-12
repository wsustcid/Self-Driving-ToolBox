/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-12 19:56:40
 * @LastEditTime: 2021-11-12 20:01:27
 */

#include<vector>
using namespace std;

class num_sequence{
public:
    typedef void (num_sequence::*PtrType)(int);
    
    // _pmf 可以指向下列任何一个函数
    void fibonacci(int);
    void pell(int);
    void lucas(int);
    void triangular(int);
    void sequare(int);
    void pentagonal(int);

private:
    PtrType _pmf;
    vector<int>* _elem; // 指向目前所用的vector
    static const int num_seq = 7;
    static PtrType func_tbl[num_seq]; // 存放成员函数地址
    static vector<vector<int>> seq; // 存放数列

}