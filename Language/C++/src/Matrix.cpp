/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-10 16:31:27
 * @LastEditTime: 2021-11-12 15:44:58
 */

#include "Matrix.h"

Matrix& Matrix::operator=(const Matrix &rhs)
{
    if (this != &rhs)
    {
        _row = rhs._row; _col = rhs._col;
        int elem_cnt = _row * _col;
        delete [] _pmat;
        // 深拷贝
        _pmat = new double[elem_cnt]; // 重新分配指针并拷贝内容，而不是浅拷贝直接指向同一位置
        for (int i=0; i<elem_cnt; i++) _pmat[i] = rhs._pmat[i];
    }

    return *this;
}