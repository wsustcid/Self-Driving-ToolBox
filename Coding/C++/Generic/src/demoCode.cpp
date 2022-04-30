/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-04-25 10:44:15
 * @LastEditTime: 2022-04-30 17:09:52
 */
#include <iostream>
#include <string>
#include <fstream>

#include <vector> // 顺序性容器
#include <list>
#include <deque>
#include <map> // 关联性容器
#include <set>

#include <algorithm> // 泛型算法

#include <functional> // funcation object
// sort(vec.begin(), vec.end(), greater<int>()); 降序排序
// transform()

#include <iterator> // 迭代器

using namespace std;



/******************** 指针的算数运算 ****************************
 * 1. 本部分从实现一个find函数入手：给定一个vector和整数值
 * 返回vector内该整数值的指针
 * 2. 然后不断提升该find函数的抽象层级，实现与数值类型和容器类型剥离
 * 
 * !BUG: 为何参数引用加const，返回值类型也要加const?
*/

// 普通版本：处理单一容器类型和数值类型
const int* find_normal(const vector<int>& vec, const int &value)
{
  for (int i=0; i<vec.size(); i++) 
  {
    if (vec[i]==value) return &vec[i];
  }
  return 0;
}

// 函数模板：单一容器类型不同数值类型
template <typename elemType>
const elemType* find_template(const vector<elemType> &vec, const elemType &value)
{
  for (int i=0; i<vec.size(); i++) 
  {
    if (vec[i]==value) return &vec[i];
  }
  return 0;
}

// 模板+指针：借助数组指针(首地址+容器大小)，尝试剥离容器类型
template <typename elemType>
const elemType* find_arr(const elemType *arr, int size, const elemType &value)
{
  // 方案1：传入首地址和array大小，结合指针的下标运算对实现对数组指定范围的迭代
  if (!arr || size<1) return 0;
  for (int i=0; i<size; i++) 
  {
    if (arr[i]==value) return &arr[i];
  }
  return 0;
  // 指针的下标运算包含两步：
  //  (1). 将arr的起始地址加上索引值(会考虑指针所指类型的大小)，得到某个元素地址； 
  //  (2). 然后根据此地址进行提领操作，得到此元素值
  // arr[2] 等价于 *(arr+2): 注意这里的+号是重载后的指针的算数运算
  // 因此从外在形式来看，指针的下标运算与直接对对象进行索引操作并无不同
}

// 模板+指针：借助数组指针（首尾地址），尝试剥离容器类型
template <typename elemType>
const elemType* find_arr_vec(const elemType *first, const elemType* last, const elemType &value)
{
  // 方案2：传入首地址和结束地址的下一位置，结合在指针算数运算实现对数组的指定范围的迭代
  // 末尾元素的下一个地址扮演标兵的角色，仅仅用来比较是可以的，但读取或写入不合法
  if (!first || !last) return 0;
  for (; first!=last; first++) 
  {
    if (*first==value) return first;
  }
  return 0;
}

// 泛型编程：自定义begin() end(), 使得上述find可以扩展支持vector
template <typename elemType>
const elemType* begin_vec(const vector<elemType> &vec)
{
  // arr的首地址可以通过数组名直接传入，即使为空也没有问题，直接为0
  // 但vector名称并不是首地址，因此当其为空时无法指定其首地址
  return vec.empty() ? 0 : &vec[0];
}
template <typename elemType>
const elemType* end_vec(const vector<elemType> &vec)
{
  if (vec.size()==0) return 0;
  return &vec[vec.size()-1];
}

// 最终版本：同时支持两种形式：一对指针，或一对指向某种容器的iterator
template<typename iteratorType, typename elemType>
iteratorType find_generic(iteratorType first, iteratorType last, const elemType &value)
{
  for (;first!=last; first++) 
  { 
    if (*first==value) return first; 
  }
  return last;
}

// 使用iterator 重写 display
template <typename elemType>
void display(const vector<elemType> vec, ostream &os)
{
  // 由于使用了模板类型，因此必须显示的告诉编译器这是一个type而不是变量
  typename vector<elemType>::const_iterator iter = vec.begin();
  typename vector<elemType>::const_iterator end_iter = vec.end();
  for (; iter!=end_iter; iter++)
    os << *iter << ' ';
  os << endl;
}

// 注意：上述操作的基础是所处理的类型提供了 equality 运算符，如果操作对象没有提供，则无法处理。
// 1. 解决方案之一是传入一个函数指针，取代原本的 equality 运算符；
// 2. 或者使用 function object

/*********************** 单元测试 *********************************/
void findTest()
{
  const int size = 5; 
  int ia[size] = {1,2,3,4,5}; 
  int value = 3;
  vector<int> ivec(ia, ia+size); 
  list<int> ilist(ia, ia+size);
  vector<string> svec = {"aa", "bb", "cc"};
  string svalue = "bb";

  const int *res1 = find_normal(ivec, value); 
  if (res1) cout << "V1: " << *res1 << endl;

  const string *res2 = find_template(svec, svalue);
  if (res2) cout << "V2: " << *res2 << endl;

  const int *res3 = find_arr(ia, size, value);
  if (res3) cout << "V3: " << *res3 << endl;
  
  const int *res4 = find_arr_vec(begin_vec(ivec), end_vec(ivec), value);
  if(res4) cout << "V4: " << *res4 << endl;
  
  // iterator: 用法与指针相同
  vector<int>::iterator it = find_generic(ivec.begin(), ivec.end(), value);
  list<int>::const_iterator iter = find_generic(ilist.begin(), ilist.end(), value); 
  if (it != ivec.end()) cout << "V5: " << *it << endl;
  if (iter != ilist.end()) cout << "V5: " << *iter << endl; 

}

/********************* 顺序性容器基本操作 *************************/
// 所有容器的共同操作 （包括string 类）
// 1. equality(==) inequality(!=):返回true 或 false
// 2. assignment (=): 将某个容器复制给另一个容器
// 3. empty(); size(); clear();
// 4. begin() end()
// 5. insert(): 将单一或某个范围内的元素插入容器; erase();
void comp(vector<int> &v1, vector<int> v2)
{
  if (v1==v2) return;
  if (v1.empty() != v2.empty()) return;
  vector<int> t = v1.size()>v2.size()?v1:v2;
  t.clear();
}

// 顺序性容器五种定义方式
void seq_container_define()
{
  list<string> slist; // 产生空容器
  list<int> ilist(1024); // 产生特定大小容器, 默认值初始化
  vector<int> ivec(10, -1); // 产生特定大小容器，指定值初始化
  int ia[3] = {1,2,3}; // 通过一对iterator产生容器
  vector<int> fib(ia, ia+3);
  list<string> strlist(slist); // 通过某个容器产生新容器
}

//特殊化插入操作：push_back(), push_front();
//四种通用插入方法
void insert_methods()
{
  // 1. iterator insert(iterator position, elemType value): 将value插入指定位置之前，并返回一个iterator指向插入的元素
  list<int> increase_list(1);
  int val = 3;
  list<int>::iterator it = increase_list.begin();
  while (it != increase_list.end())
  {
    if (*it >= val)
    {
      increase_list.insert(it, val);
      break;
    }
    ++it;
  }
  if (it==increase_list.end()) increase_list.push_back(val);

  // 2. void insert(interator pos, int count, elemType value): 在pos之前插入count个value
  it = increase_list.begin();
  increase_list.insert(it, 3, -1);

  // 3. void insert(iterator pos, iter first, iter last): 在pos之前插入[first, last)范围内的元素
  int ia[4] = {1,2,3,4};
  increase_list.insert(it, ia, ia+4);

  // 4. iterator insert(pos)：在pos之前插入元素，值为类型默认值
}

// 特殊化删除操作：pop_back(); pop_front()
// 两种通用删除方法
void erase_methods()
{
  // 1. iterator erase(iter pos):删除指定位置元素
  list<int> ilist = {1,2,3,4,5};
  list<int>::iterator it = ilist.begin();
  ilist.erase(it);

  // 2. iterator erase(iter1, iter2):删除[iter1, iter2)之间的元素
  list<int>::iterator first = find(ilist.begin(), ilist.end(), 2);
  list<int>::iterator end = find(ilist.begin(), ilist.end(), 4);
  ilist.erase(first, end); // 注意不支持指针偏移， first+2
  
  // 上述两种删除操作返回的都是删除的最后一个元素的下一个位置
}


/************************ 常用泛型算法 ***************************/

bool is_elem(vector<int>&vec, int elem)
{
  vector<int>::iterator max_value_iter = max_element(vec.begin(), vec.end());
  if (*max_value_iter < elem)
  {
    return true;
  }
  if (*max_value_iter==elem) return true;

  vector<int> tmp(vec.size());
  copy(vec.begin(), vec.end(), tmp.begin());
  
  sort(tmp.begin(), tmp.end());

  return binary_search(tmp.begin(), tmp.end(), elem);
}

/************************ 仿函数 *****************************
 * 1. 对于普通函数，函数名加上function call 运算符，即 ()，便可实现函数调用
 * 2. 而对于某个类，如果对其进行 () 运算符重载，他就成了一个仿函数，使用实例化对象名结合（），亦可以实现函数调用的效果 
*/

template <class T>
class MyPlus
{
public:
  T operator() (const T &x, const T &y) const
  {
    return x+y;
  }
};

template <class T>
class MyMinus
{
public:
  T operator () (const T &x, const T &y) const
  {
    return x-y;
  }
};

// 测试
void funcationCallTest()
{
  MyPlus<int> plus_obj;
  MyMinus<int> minus_obj;
  int x = 1, y = 1;
  cout << "1+1 = " << plus_obj(x, y) << endl;
  cout << "1-1 = " << minus_obj(x, y) << endl;
  cout << MyMinus<int>()(x, y) << endl;//产生临时对象并调动
}

/******************** 泛型算法设计 *****************************
 * 1. 给定一个vector,返回一个vector,其内存储所有小于10的元素
 * 2. 将比较值参数化
 * 3. 将比较关系参数化：允许 大于，小于等
*/
// 1. 普通版本
vector<int> filter_less_than(const vector<int> &vec, const int &value)
{
  vector<int> res;
  for (int i=0; i<vec.size(); i++)
  {
    if (vec[i]<value) res.push_back(vec[i]);
  }
  return res;
}

// 2. 通过函数调用去掉 < 运算符
bool less_than(int v1, int v2){ return v1<v2 ? true : false;}
bool greater_than(int v1, int v2){ return v1>v2 ? true : false;}

vector<int> filter_cmp(const vector<int> &vec, const int &val, bool (*cmp)(int, int))
{
  // 比较函数参数定义为 函数指针
  vector<int> res;
  for (int i=0; i<vec.size(); i++)
  {
    if (less_than(vec[i], val)) res.push_back(vec[i]);
  }

  return res;
}

// 3. 借助function object 代替 函数指针调用比较函数
vector<int> filter_fun_obj(const vector<int> &vec, const int &val, 
                           less<int> lt)
{
  // less<type> function object 需要传入两个参数，但我们其实只需要传入一个，另一个是固定的，因此希望将第二个参数进行绑定
  // function adapter 可以将function object的参数绑定至某特定值，使二元function object变为一元
  // 注意：这里less<int>是一个模板类， lt是一个类对象，但加上()可以当做函数使用
  vector<int> res;
  vector<int>::const_iterator iter = vec.begin();
  while((iter=find_if(iter, vec.end(), bind(lt, placeholders::_1, val))) != vec.end())
  {
    res.push_back(*iter);
    iter++;
  }
  return res;
}

// 4. 泛型设计：
//   1. 消除与vector元素类型的关联：函数模板
//   2. 消除容器类型的关联: 传入iterator
//   3. 消除比较方式的关联：传入 function object
template <typename inIter, typename outIter, 
          typename elemType, typename funcObj>
outIter filter_generic(inIter first, inIter last, outIter at, const elemType& value, funcObj cmp)
{
  while((first=find_if(first, last, bind(cmp, placeholders::_1, value)))!=last)
  {
    *at++ = *first++; // 借助目标容器的迭代器完成值的填充
  }
  return at;
}

// 后续还可以使用 negator实现多种判断方式，比如大于等于10的元素,可以使用
// not1(bind(less<int>(), _1, 10))实现取反

void genericTest()
{
  int iarr[] = {1,2,3,4,5,6,7,8,9};
  vector<int> vec(iarr, iarr+9);
  vector<int> res;
  int val = 5;

  // 1.
  cout << "1. " << endl; 
  res = filter_less_than(vec, val);
  display(res, cout);
  res.clear();

  // 2.
  cout << "2. " << endl;
  res = filter_cmp(vec, val, greater_than);
  display(res, cout);
  res.clear();

  // 3. 
  cout << "3. " << endl;
  res = filter_fun_obj(vec, val, less<int>());
  display(res, cout);
  res.clear();

  // 4. 
  cout << "4. " << endl;
  res.resize(9); // 必须指定尺寸，不能为空; （输出时还会把没用的0输出）
  filter_generic(iarr, iarr+9, res.begin(), val, greater<int>());
  display(res, cout);
  res.clear();

  // 5. 借助back_inserter 实现对元素的复制
  cout << "5. " << endl;
  filter_generic(iarr,iarr+9, back_inserter(res), val, greater<int>());
  display(res, cout);
  res.clear();

}


/************************ 关联性容器 **************************/
void correContainerUsage()
{
  // map的定义与使用
  map<string, int> words; // 用于统计字符出现的个数
  words["vermeer"] = 1; // 建立key-value的映射；
  // 取值直接 words["vermeer"]
  
  string tword;
  while(cin>>tword)
  {
    words[tword]++; // 进行数据统计；
    // 如果tword不在map内，则会被自动创建，默认值为0
  } 
    
  // 使用map对象的first member 和 second member
  map<string, int>::iterator it = words.begin();
  for (; it!=words.end(); it++) 
  {
    cout << "key:" << it->first 
         << "value:" << it->second 
         << endl;
  }
  
  // 查询map内的对象 // 
  int count = 0;
  // 1. 直接通过索引进行查询，但查询后不存在的对象会将其加入map，并指定默认值
  if(!(count=words["vermeer"])) cout << count<< endl;;
  
  // 2. 使用map的find()函数，注意不是泛型算法的find();找不到返回end()
  it = words.find("vermeer"); 
  if (it!=words.end()) cout << it->second << endl;
  
  // 3. 使用count函数返回其在map中的个数：0 or 1
  if (words.count("vermeer")) cout << count<< endl;;

  // set的定义与使用
  vector<int> vec = {1,6,5,6,3,4};
  // 1. 赋值：//set元素依据其所属类型默认的less-than运算符进行排列
  set<int> iset; 
  iset.insert(10); // 插入单一元素
  iset.insert(vec.begin(), vec.end()); //插入某个范围元素
  count = iset.count(10);

  // set迭代
  set<int>::iterator iter = iset.begin();
  for (; iter!=iset.end(); it++)
  {
     cout << *iter << ' ';
  }
  // 另外，泛型算法中有不少和set相关的算法
  // set_intersetion(); 
  // set_union(); 
  // set_difference(); 
  // set_symmetric_difference();
}


/************************ Iterator Inserter *******************
 * 1. 在之前的实现中我们使用迭代器将源端容器中的元素赋值给目的端容器，*at=*iter;
 * // 但前提条件是目的端容器必须足够大，需要实现指定大小，不能指定空容器
 * 2. 当然理想情况是指定一个空容器，然后根据情况不断插入元素。
 * 3. 借助对元素进行复制行为的算法：copy(), copy_backwards(), remove_copy(), replace_copy(), unique_copy()等
 * 4. 标准库提供了三种 insertion adapter，可以避免使用容器的assignment运算符
 * 
 * 
*/


/************************* iostream Iterator ******************
 * 任务：从标准输入设备读取一串string元素，存入vector，然后输出到标准输出设备
*/
void iostreamIterTest()
{
  
  // 1. 常规写法
  string word;
  vector<string> texts;
  while(cin >> word)
  {
    texts.push_back(word);
  }
  for(int i=0; i<texts.size(); i++)
  {
    cout << texts[i] << ' ';
  }
  cout << endl;

  // 2. 使用iostream 迭代器
  // 获取输入：和普通迭代器一样，首先需要定义迭代的范围， first 和 last
  istream_iterator<string> is(cin); // 将其与输入设备绑定
  istream_iterator<string> eof; // 不绑定，代表 end-of-file

  // 存入容器
  copy(is, eof, back_inserter(texts));

  // 输出至标注输入设备
  ostream_iterator<string> os(cout, " ");
  copy(texts.begin(), texts.end(), os);

  // 3. 如果是从文件读取和输出
  // ifstream in_file("input_file.txt"); // 代替 cin
  // ofstream out_file("output_file.txt");// 代替 cout
}


int main(int argc, char** argv)
{
  // findTest();
  // funcationCallTest();
  // genericTest();
  iostreamIterTest();
}