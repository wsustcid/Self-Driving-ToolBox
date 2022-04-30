/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-04-22 10:24:56
 * @LastEditTime: 2022-04-24 16:08:13
 */


#include "NumericSeq.h"

using namespace std;


/************* 通过传引用获取多个函数返回值 ******************/
bool fibon_elem(int pos, int &elem)
{
  /** 指定数列中的元素位置，计算该位置的元素值，返回是否计算成功
   * 1. 采用传引用的方式返回计算结果，而不是通过函数返回值返回
   * 2. 可以处理位置无效的情况，且可以返回多个值
  */
  if (pos<=0 || pos>1024)
  {
    elem = 0; return false;
  }
  elem = 1;
  int elem_1 = 1, elem_2 = 1;
  for (int i=3; i<=pos; i++)
  {
    elem = elem_1 + elem_2;
    elem_2 = elem_1;
    elem_1 = elem;
  }
  return true;
}


/******************* switch 语句使用技巧 **********************/
bool print_sequence(int pos)
{
  if (pos<=0 || pos>1024)
  {
    cerr << "Invalid position: " << pos << endl;
    return false; 
  }
  cout << "The whole sequence is: " << endl;
  switch (pos)
  {
    // 注意这里case的写法
    default:
    case 2:
      cout << "1 ";
    case 1:
      cout << "1 ";
      break;
  }

  int elem, elem_1=1, elem_2 = 1;
  for (int i=3; i<=pos; i++)
  {
    elem = elem_1 + elem_2;
    elem_2 = elem_1;
    elem_1 = elem;
    cout << elem << (!(i%10) ? "\n" : " ");
  }

  return true;
}

/******************传引用 与 参数指定默认值 *********************/
void display(const vector<int> &vec, ostream &os)
{   
    /**os 默认输出到cout，但也可以指定输出至文件
     * 1. 注意！这里函数定义中中没有指定默认值，但声明中指定了
     * 2. 因此调用时可以只指定一个参数
    */
    for (int i=0; i<vec.size(); i++) os << vec[i] << ' ';
    os << endl;
}

void display(const vector<int> *vec)
{
    /**参数以指针的方式传递：调用时 display(&vec)
     * 传指针和传引用的区别在于指针有可能不指向某个具体的对象，
     * 因此提领指针时，一定要先判断指针是否为0；
     * 而传引用不用判断，因为引用必然会绑定某个对象之上
     * int &rval = ival; // rval为引用，即ival的别名，定义时必须绑定且无法更改
    */
    if (!vec) return; //
    for (int i=0; i<vec->size(); i++) cout << (*vec)[i] << ' ';
    cout << endl;
}

void swap(vector<int> &vec, int pos_1, int pos_2)
{
    int tmp = vec[pos_1];
    vec[pos_1] = vec[pos_2];
    vec[pos_2] = tmp;
}

void bubble_sort(vector<int> &vec)
{
    /** 两层循环组成，第一层逐个确定最小值；第二层通过两两比较寻找该位置最小值 */
    if (vec.size()<2) return;
    for (int i=0; i<vec.size(); i++)
    {
        for (int j=i+1; j<vec.size(); j++)
        {
            if (vec[j]<vec[i]) swap(vec[i], vec[j]);
        }
    }
}

void print_msg(string &msg, ostream &os = cout)
{
  if (msg.empty()) return;
  os << msg; 
}

void print_msg(string &msg, ofstream *ofile=0)
{
  /**为函数参数指定默认值
   * 1. 可以根据实际需求在调用时自主决定是否输出到文件
   * 2. 注意这里必须传递ofile对象的地址而非引用，因为这样才能将默认值设定为0
   * 3. 引用则必须要代表某个对象*/
  if (ofile!=0)
  {
      (*ofile) << msg;
  }
  cout << msg; 
}


/****************** 局部静态对象 ************************/
const vector<int>* fibon_seq(int size)
{
  if (!is_size_ok(size)) return 0; // 返回空指针
  static vector<int> elems;
  for (int i=elems.size(); i<size; i++)
  {
    if (i==0 || i==1) elems.push_back(1);
    else elems.push_back(elems[i-1]+elems[i-2]);
  }
  return &elems; // 因为是局部静态对象，不会被销毁，所以可以返回其地址
}


/***************** 模板函数 *****************************/
template <typename elemType>
void display_msg(const string &msg, const vector<elemType> &vec)
{
    cout << msg;
    for (int i=0; i<vec.size(); i++)
    {
        elemType elem = vec[i];
        cout << elem << ' ';
    }

    // 后续使用时和普通函数类型，只需要传入具体的参数即可
}

/**************** 函数指针 *****************************
 * 1. 刚刚已经实现了fib_seq，可以根据指定序列长度返回具体的数列
 * 2. 但如果想要调用他数列，还需要再单独写一个调用函数吗？
 * 3. 消除这一关联的方式是使用函数指针
 * */

bool seq_elem(int pos, int &elem, const vector<int>* (*seq_ptr)(int)=0)
{
    // 1. 函数名加括号是为何将其与变量名区分，否则函数名会被认为是变量的指针名
    // 2. 括号内加*代表seq_ptr是指向这个函数的指针，与 int *p 类似
    // 3. 初值设为0，表示未指向任何函数
    // 4. 也可以拿某个函数的地址作为初值：也就是函数名
    // python直接可以传递函数名就是这个原理，其实传递的就是函数的地址

    if (!seq_ptr) cout << "Wrong"; // 确保指向了函数
    // 具体调用方式普通函数相同
    const vector<int>* pseq = seq_ptr(pos); // 这里不在是函数名调用，而是通过函数的指针调用的
    return true;
    
}




/*********************  单元测试 *************************/
void getRange()
{
  /* 查询某个类型的最大值或最小值*/
  int max_int = numeric_limits<int>::max();
  double min_double = numeric_limits<double>::min();

  cout << "Max value of Int: " << max_int << endl;
  cout << "Min value of double: " << min_double << endl;
}

void usrReqSeq()
{
  /** 根据用户请求，打印序列值*/
  cout << "Please enter the pos: "<< endl;
  int pos, elem;
  while(cin>>pos)
  {
    if (fibon_elem(pos, elem))
    {
      cout << "The elem at pos #" << pos << " is: " << elem<<endl;
    }
    if (print_sequence(pos))
    {
      cout << "\n---------------\n";
    }
  }
}

void bubble_sort_test()
{
    int iarr[10] = {8,3,1,2,5,7,9,0,4,6};
    vector<int> vec(iarr, iarr+10);
    bubble_sort(vec);
    // ofstream ofile("log.txt");
    // display(vec, ofile);
    display(vec); // display(&vec);
}

inline void fibon_test()
{
    int pos, elem;
    cout << "Please enter sequence pos: ";
    cin >> pos;
    const vector<int>* seq_prt = fibon_seq(pos);
    if (!seq_prt)
    {
        elem = 0; return;
    }
    elem = (*seq_prt)[pos-1];
    cout << "The elem is: " << elem << endl;
}

// 函数指针
const vector<int>* lucas_seq(int size);
const vector<int>* pell_seq(int size);
const vector<int>* triang_seq(int size);
const vector<int>* square_seq(int size);
const vector<int>* pent_seq(int size);
void seq_test()
{
    // 循环显示各个数列，不用再一一指定各函数名称进行调用
    // 函数指针数组: int* parr[]
    const vector<int>* (*seq_ptr_array[])(int) = {fibon_seq};
    // , lucas_seq, pell_seq, triang_seq, square_seq, pent_seq};
    // 建立名称到索引额映射
    enum ns_type {ns_fibon, ns_lucus, ns_pell, ns_triang, ns_square, ns_pent};
    
    const vector<int>* (*seq_ptr)(int); // seq_ptr是一个指针，指向参数列表为int, 返回值类型为 vector<int>* 的函数
    seq_ptr = seq_ptr_array[ns_fibon];
}


/******************** 使用函数重载和模板实现max函数 ******************
 * 使其能处理一下情况：
 * 1. 两个整数; 2. 两个浮点数；3. 两个字符串
 * 4. 一个整数vector； 5. 一个浮点数vector; 6. 一个字符串vector
 * 7. 一个整数数组和数组大小的整数值；8. 浮点数数组和大小；9. 字符串数组和大小
*/

template <typename elemType>
elemType Max(elemType m1, elemType m2)
{
    if (m1 < m2) return m2;
    return m1;
}

template <typename elemType>
elemType Max(vector<elemType> &mvec)
{
    sort(mvec.begin(), mvec.end());
    return mvec[mvec.size()-1];
}

template <typename elemType>
elemType Max(elemType arr[], const int sz)
{
    sort(arr, arr+sz);
    return arr[sz-1];
}

void maxTest()
{
    int im1 = 3, im2 = 5;
    double dm1 = 3.0, dm2 = 5.0;
    string sm1 = "abc", sm2 = "ade";

    vector<int> imarr = {5,2,3};
    vector<double> dmarr = {5.0,2.0,3.0};
    vector<string> smarr = {"abc", "ade", "ccc"};
    
    const int sz = 3;
    int iarr[sz] = {5, 2, 3};
    double darr[sz] = {5.0, 2.0, 3.0};
    string sarr[sz] = {"abc", "ade", "ccc"};
    
    cout << Max(im1, im2) << endl;
    cout << Max(dm1, dm2) << endl;
    cout << Max(sm1, sm2) << endl;

    cout << Max(imarr) << endl;
    cout << Max(dmarr) << endl;
    cout << Max(smarr) << endl;

    cout << Max(iarr, sz) << endl;
    cout << Max(darr, sz) << endl;
    cout << Max(sarr, sz) << endl;   
}


/************************ main ****************************/

int main(int argc, char** argv)
{
    // getRange();
    // usrReqSeq();
    // bubble_sort_test();
    // fibon_test();
    maxTest();
}