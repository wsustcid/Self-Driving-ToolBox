/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-10 14:56:27
 * @LastEditTime: 2021-11-12 19:07:29
 */

#include "Triangular.h"
#include <algorithm>
using namespace std;

// 5. static data member
vector<int> Triangular::_elems;

// 1. 构造函数
Triangular::Triangular()
{
    _length = 1;
    _beg_pos = 1;
    _next = 0;
}

Triangular::Triangular(int len)
{
    _length = len > 0 ? len : 1;
    _beg_pos = 1;
    _next = 0;
}

// 4. mutable data member
Triangular::Triangular(int len, int bp): 
    _name("Triangualr"),
    _length(len > 0 ? len : 1),
    _beg_pos(bp > 0 ? bp : 1)
{
    _next  = _beg_pos -1;
    int elem_cnt = _beg_pos + _length - 1;
    if (_elems.size()<elem_cnt)
    {
        gen_elements(elem_cnt);
    }
}

// 2. const member function
int Triangular::elem(int pos) const
{
    return _elems[pos-1];
}

// 3. non-const member function 
bool Triangular::next(int &val)
{
    if (_next < _beg_pos + _length-1)
    {
        val = _elems[_next++];
        return true;
    }
    return false;
}

// 6. static membere function
bool Triangular::is_elem(int value)
{
    if (!_elems.size() || _elems[_elems.size()-1]<value)
    {
        gen_elements_to_value(value);
    }

    vector<int>::iterator found_it;
    vector<int>::iterator end_it = _elems.end();
    found_it = find(_elems.begin(), end_it, value);
    
    return found_it != end_it;
}

void Triangular::gen_elements_to_value(int value)
{
    int ix = _elems.size();
    if (!ix) { _elems.push_back(1); ix = 1;}
    while(_elems[ix-1]<value && ix< _max_elems)
    {
        ++ix;
        _elems.push_back(ix*(ix+1)/2);
    }
    if (ix == _max_elems) cout << "oops: value too large!" <<endl;
}

void Triangular::gen_elements(int length)
{
    if (length < 0 || length > _max_elems) {cout << "Wrong length"<<endl; return;}
    if (_elems.size() < length)
    {
        int ix = _elems.size() ?_elems.size()+1 : 1;
        for (; ix<=length; ++ix) _elems.push_back(ix*(ix+1)/2);
    }
}

Triangular& Triangular::operator=( const Triangular &rhs )
{
	if ( this != &rhs ) { 
   		_length = rhs._length;
		_beg_pos = rhs._beg_pos;
		_next = 1;
	}

   return *this;
}

void Triangular::display(int length, int beg_pos, ostream &os)
{
    for (int i=beg_pos; i<beg_pos+length; i++)
    {
        os << _elems[i-1];
    }
}

