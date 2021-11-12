/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-10 16:31:20
 * @LastEditTime: 2021-11-12 15:38:11
 */

class Matrix{
public:
    Matrix(int row, int col): _row(row), _col(col)
    {
        _pmat = new double[row*col]; // 资源分配
    }

    ~Matrix()
    {
        delete [] _pmat; // 资源释放
    }

    Matrix& operator=(const Matrix &rhs);

private:
    int _row, _col;
    double* _pmat;
};