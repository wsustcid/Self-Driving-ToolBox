/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-15 09:53:32
 * @LastEditTime: 2021-11-15 16:30:43
 */

#include "num_sequence.h"

bool num_sequence::check_integrity( int pos ) const
{
    if (pos <=0 || pos > _max_elems)
    {
        cerr << "!! invalid position: " << pos << "Cannot honor requeset\n";
        return false;
    }
    return true;
}

// ostream& operator<<(ostream &os, const num_sequence &ns)
// {
//     return ns.print(os);
// }


// Fibonacci
int Fibonacci::elem(int pos) const
{
    if (!check_integrity(pos)) return 0;
    
    if (pos > _elems.size()) Fibonacci::gen_elems(pos); // 这里直接解析

    return _elems[pos-1];
}

void Fibonacci::gen_elems(int pos) const
{
    if (_elems.empty())
    {
        _elems.push_back(1);
        _elems.push_back(1);
    }

    if (_elems.size()<=pos)
    {
        int ix = _elems.size();
        int n_2 = _elems[ix-2];
        int n_1 = _elems[ix-1];

        for (; ix<=pos; ++ix)
        {
            int elem = n_1 + n_2;
            _elems.push_back(elem);
            n_2 = n_1; n_1 = elem;
        }
    }
}

ostream& Fibonacci::print(ostream &os) const
{
    int elem_pos = _beg_pos -1;
    int end_pos = elem_pos + _length;
    if (end_pos > _elems.size()) Fibonacci::gen_elems(end_pos);
    
    while(elem_pos < end_pos)
        os << _elems[elem_pos++] << ' ';

    return os;
}