/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-12 16:04:00
 * @LastEditTime: 2021-11-12 16:17:59
 */
#include<vector>
using namespace std;

class LessThan{
public:
    LessThan(int val): _val(val) {}
    int comp_val() const {return _val;} // 基值的读取
    void comp_val(int nval) {_val = nval;} // 基值的写入

    bool operator()(int _value) const;
private:
    int _val;
};

inline LessThan::operator()(int value) const
{
    return value < _val;
}

/*** function Object 的使用 ****/
// 1. LessThan object 的定义方式和一般对象并没有什么不同，我们直接将function call运算符应用到
//    具体的对象身上，便可以调用function call运算符

int count_less_than(const vector<int> &vec, int value)
{
    LessThan lt(value);

    int count = 0;
    for (int i=0; i<vec.size(); i++)
    {
        if (lt(vec[ix])) ++count;
    }
    return count;
}

// 2. 通常我们会把function object作为函数参数传给泛型算法
void print_less_than(const vector<int> &vec, int val, ostream &os=cout)
{
    LessThan lt(val);
    vctor<int>::const_iterator it = vec.begin(), it_end = vec.end();
    os << "Elements less than " << lt.comp_val() <<endl;
    while((it=find_if(it, it_end, lt)) != it_end)
    {
        os << *it << ' ';
        ++it;
    }
}