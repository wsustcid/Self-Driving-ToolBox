/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-10-30 10:38:08
 * @LastEditTime: 2021-11-09 17:28:54
 */
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<iterator>

using namespace std;

/********************** Chapter 1: Quick Start ***********************************
 * 1. 对象的定义与使用：包括几大基本数据类型及字符串与数组等
 * 2. 表达式与语句的使用：包括条件语句与循环语句
 * 3. 文件的读写
 *********************************************************************************/
void qucik_start()
{
    // 与用户交互
    char first_name[20];
    string last_name;
    cout << "Please enter your first name: ";
    cin >> first_name; // cin.getline(str)
    cout << "Hi, " << first_name << ". Please enter your last name: ";
    cin >> last_name;
    cout << "oh! Your name is "
         << first_name << " "
         << last_name << endl;
    
    // 输入数字，并存入数组处理
    cout << "Please input a series of numbers: " << endl;
    vector<int> vec;
    int num;
    while(cin >> num)
    {
        vec.push_back(num);
        if (cin.get() == '\n') break; // 读取到换行符结束
    } 
    int sum=0;
    const int n = vec.size();
    int arr[n];
    for (int i=0; i<n; i++)
    {
        arr[i] = vec[i];
        sum += vec[i];
    }
    cout << "Total Sum: " << sum << "; Average: " << float(sum)/n << endl;

    // 文件读写
    vector<string> sentence;
    string word;
    string file_path = "./file.txt", out_path="./out.txt";
    ifstream ifile(file_path);
    if (ifile)
    {
        cout << "Reading file from " << file_path<<endl;
        while(ifile>>word)
        {
            sentence.push_back(word);
        }
    }
    else cout << "Can not find file at " << file_path << endl;
    
    ofstream ofile(out_path);
    if (ofile)
    {
        for (string word : sentence)
        {
            ofile << word << " ";
        }
        cout << "The file saved to " << out_path << endl;
    }
    else cout << "Error in writing file!" << endl;
    
    // 根据平均值输出不同的单词
    int idx = sum/n;
    switch (idx)
    {
    case 0:
        cout << sentence[0]<<endl;;
        break;
    case 1:
        cout << sentence[1]<<endl;;
        break;
    case 2:
        cout << sentence[2]<<endl;;
        break;
    default:
        cout << "Hahahaha!"<<endl;
        break;
    }

    return;
}

/********************** Chapter 2: Procedural Programming *************************
 * 1. 函数的基本编写规则：特别是传值与传址
 * 2. 局部静态对象、inline函数、重载与模板函数
 *********************************************************************************/
bool fibon_elem(int pos, int &elem); // 函数声明
void print_sequence(int pos);

void fibon_main()
{
    int pos;
    bool try_flag = true;
    while (try_flag)
    {
        cout << "Please enter a position: ";
        cin >> pos;
        int elem;
        if (fibon_elem(pos, elem))
        {
            cout << "Element # " << pos << " is " << elem << endl;
            print_sequence(pos);
        }
        else cout << "Sorry, could not calculate the element # " << pos << endl;

        cout << "Would you like to try again ? y/n" << endl;
        char yn; cin >> yn;
        if (yn=='n') try_flag = false; 
    }
    
}

bool fibon_elem(int pos, int &elem) // 函数定义
{
    // 检查位置是否合理
    if (pos<=0 || pos>1024)
    {
        elem = 0;
        return false;
    }
    // 初始条件
    elem = 1;
    int n_2 = 1, n_1 = 1;
    for (int i=3; i<=pos; i++)
    {
        elem = n_1 + n_2;
        n_2 = n_1;
        n_1 = elem;
    }
    return true;
}

void print_sequence(int pos) // 函数定义
{
    // 检查位置是否合理
    if (pos<=0 || pos>1024)
    {
        cout << "Invalid position: " << pos << endl;
    }
    cout << "The Fibonacci Sequence for " << pos << " position: \n\t";
    switch(pos)
    {
        default:
        case 2: cout << "1 ";
        case 1: cout << "1 "; break;
    }
    // 初始条件
    int elem = 1;
    int n_2 = 1, n_1 = 1;
    for (int i=3; i<=pos; i++)
    {
        elem = n_1 + n_2;
        n_2 = n_1;
        n_1 = elem;
        cout << elem << ((i%10)==0 ? "\n\t" : " ");
    }
    cout << endl;
}


// Pentagonal
void pent_main(); // 主函数
const vector<int>* pent_gen(int pos); // 数列生成函数
void display_msg(const vector<int> *vec, int pos, const string &msg_type="int");
inline bool isValid(int pos)
{
    if (pos<1 || pos>10000) return false;
    return true;
}

const vector<int>* pent_gen(int pos)
{
    static vector<int> vec; // 以局部静态定义在这里，就不用再从外部传入了;
    if (vec.size()<pos)
    {
        for (int i=vec.size()+1; i<=pos; i++) vec.push_back(i*(3*i-1)/2);
    }
    
    return &vec; // 函数调用结束也不会销毁，因此可以安全的返回地址
}

void display_msg(const vector<int> *vec, int pos, const string &msg_type)
{
    for (int i=0; i<pos; i++) cout << (*vec)[i] << ((i+1)%10==0 ? "\n": " ");
}

void pent_main()
{
    int pos = 15;
    if (isValid(pos))
    {
        const vector<int>* pt_vec = pent_gen(pos);
        display_msg(pt_vec, pos);
    }
    else cout << "Wrong pos!";
    
}

// 函数重载
// inline int max(int a, int b) { return a>b?a:b; }
// inline float max(float a, float b) { return a>b?a:b; }
// inline string max(const string a, const string b) { return a>b?a:b; }
// inline int max(const vector<int> &vec) { return *max_element(vec.begin(), vec.end()); }
// inline float max(const vector<float> &vec) { return *max_element(vec.begin(), vec.end()); }
// inline string max(const vector<string> &vec) { return *max_element(vec.begin(), vec.end()); }
// inline int max(const int* parray, int size) { return *max_element(parray, parray+size);}
// inline float max(const float* parray, int size) { return *max_element(parray, parray+size);}
// inline string max(const string* parray, int size) { return *max_element(parray, parray+size);}


// 使用模板结合重载重新定义上述九个函数
template <typename Type> inline Type MAX(Type a, Type b) {return a>b?a:b;}
template <typename elemType>
inline elemType MAX(const vector<elemType> &vec) { return *max_element(vec.begin(), vec.end()); }
template <typename arrType>
inline arrType MAX(const arrType* parray, int size) { return *max_element(parray, parray+size);}

void max_main()
{
    int iarr[] = {12, 70, 2, 169, 1, 5, 29};
    vector<int> ivec(iarr, iarr+7);
    float farr[] = {2.5, 24.8, 18.7, 4.1, 23.9};
    vector<float> fvec(farr, farr+5);
    string sarr[] = {"we", "were", "her", "pride", "of", "ten"};
    vector<string> svec(sarr, sarr+6);

    int imax = MAX(MAX(ivec), MAX(iarr, 7));
    float fmax = MAX(MAX(fvec), MAX(farr, 5));
    string smax = MAX(MAX(svec), MAX(sarr, 6));
    cout << "imax: " << imax<< endl;
    cout << "fmax: " << fmax<< endl;
    cout << "smax: " << smax<< endl;
}


/********************** Chapter 3: Generic Programming *************************
 * 1. 容器的定义、初始化、插入、查询、迭代遍历
 * 2. iostream iterator
 *********************************************************************************/
void countWords_main()
{
    // 字数统计容器
    string word;
    unordered_map<string, int> wordCounts;
    unordered_set<string> exclude_words = {"Apple", "Banana", "Mango"};
    // 文件读入+单词统计
    string file_path = "./file.txt";
    ifstream ifile(file_path);
    if (ifile)
    {
        cout << "Loading file from " << file_path << endl;
        while(ifile>>word)
        {
            if (exclude_words.count(word)) continue;
            wordCounts[word]++;
        }
    }
    else cout << "Failed loading file from " << file_path << endl;
    // 统计结果输出
    unordered_map<string, int>::iterator iter=wordCounts.begin();
    for (; iter!=wordCounts.end(); iter++)
    {
        cout << iter->first << ": " << iter->second<< endl;  
    }
}

// 定义函数对象
class LessThan {
public:
    bool operator() (const string &s1, const string &s2) {return s1.size() < s2.size();}
};

void sortWords_main()
{
    // 字数统计容器
    string word;
    vector<string> words;
    unordered_set<string> mem;
    // 文件读入+单词统计
    string file_path = "./file.txt";
    ifstream ifile(file_path);
    if (ifile)
    {
        cout << "Loading file from " << file_path << endl;
        while(ifile>>word)
        {
            if (mem.count(word)) continue;
            else mem.insert(word);
            words.push_back(word);
        }
    }
    else cout << "Failed loading file from " << file_path << endl;
    // 排序
    sort(words.begin(), words.end(), LessThan());
    // 排序结果输出
    vector<string>::iterator iter=words.begin();
    while(iter!=words.end())
    {
        cout << *iter++ << " ";  
    }
}

// 定义function object，用于区分奇偶数
class even_elem{
public:
    bool operator()(int elem) {return elem%2?false:true; }
};

void iostream_main()
{
    // 定义两个istream_iterator，从标准输入读入
    istream_iterator<int> is(cin), eof;
    vector<int> vec;
    copy(is, eof, back_inserter(vec));
    // send an EOF to the standard input stream from the terminal 
    // by pressing CTRL-Z on Windows or CTRL-D on Linux.

    // 使用泛型算法partition()区分奇偶
    vector<int>::iterator division = partition(vec.begin(), vec.end(), even_elem());
    
    ofstream even_file("./even_file.txt"), odd_file("./odd_file.txt");
    ostream_iterator<int> os1(odd_file, " "), os2(even_file, " ");
    if (even_file && odd_file)
    {
        copy(vec.begin(), division, os2);
        copy(division, vec.end(), os1);
    }
    
}


int main()
{
    // qucik_start();
    // fibon_main();
    // pent_main();
    // max_main();
    // countWords_main();
    // sortWords_main();
    iostream_main();

}