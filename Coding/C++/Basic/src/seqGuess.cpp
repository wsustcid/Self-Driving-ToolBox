/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-04-18 11:01:44
 * @LastEditTime: 2022-04-20 17:22:41
 */

/********************** 用户猜测数列游戏 ***********************
 * 1. 从文件读取用户数据
 * 2. 引导用户猜测6种数列的下一个数值
 * 3. 将用户游戏结果写入文件
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // rand() srand()
#include <fstream>
#include <cstring> // strlen()

using namespace std;


string getUserInfo()
{
    /**通过终端进行输入输出
     * 询问用户姓名，确保用户名称大于两个字符
     * 使用c-style 字符串
    */
    string usr_name;
    const int min_size = 2, max_size = 10;
    char name[max_size+5];
    cout << "Please enter your name: ";
    // 直至输入合法长度的字符串
    while(cin >> name)
    {
        if (strlen(name)<min_size || strlen(name)>max_size)
        {
            cout << "Your name must between 2 and 10 characters!" 
                 << "Enter your name again: ";
            continue;
        }
        break;
    }
    usr_name = name;
    cout << "Hi, " << usr_name << "!" << endl;
    
    return usr_name;
}


bool loadUsrInfo(const string &usr_name, const string &file_path, int &num_tries, int &num_correct)
{
    /**从数据库中读取用户信息，不存在则创建*/
    string name;
    int tmp1, tmp2;
    bool is_found = false;
    ifstream ifile(file_path);
    if (ifile)
    {
        while(ifile >> name)
        {
            ifile >> tmp1 >> tmp2;
            if (name==usr_name)
            {
                num_tries = tmp1;
                num_correct = tmp2;
                is_found = true;
                cout << "Your data is found! "<< endl;
                cout << "Num Tries: " << num_tries << '\n'
                     << "Num Correct: " << num_correct
                     << endl;
                return true;
            }
        }
    }
    else cout << "Cannot open " << file_path << endl;
    // 写入新数据
    if (!is_found)
    {
        ofstream outfile(file_path, ios_base::app);
        if (outfile)
        {
            num_tries = 0, num_correct = 0;
            outfile << usr_name << ' ' << num_tries << ' ' << num_correct << endl;
            cout << "Your data is created!" << endl;
            return true;
        }
        else cout << "Cannot written!" << endl;
    }
    return false;
}

void saveUsrInfo(const string &usr_name, const string &file_path, int &num_tries, int &num_correct)
{
    /**从数据库中读取用户数据，覆盖结果*/
    string name;
    int tmp1, tmp2;
    // BUG: 无法写入结果，无法覆盖
    fstream iofile(file_path, ios_base::in|ios_base::out);// 读写模式
    if (iofile)
    {   
        int idx = 0;
        while(iofile >> name)
        {
            iofile >> tmp1 >> tmp2;
            idx = sizeof(name) + sizeof(tmp1) + sizeof(tmp2);
            if (name==usr_name)
            {
                iofile.seekp(idx, ios::beg);
                iofile << usr_name << ' ' << num_tries << ' ' << num_correct;
                cout << "Write!!"<<endl;
            }

            idx++;
        }
    }
    else cout << "Cannot open " << file_path << endl;
}

void usrGuessSequence(const string &usr_name, const string &file_path, int &num_tries, int &num_correct)
{
    /**用户猜测数列的下一个数值，并统计其得分
     * 1. 某个数列猜错了询问是否继续猜
     * 2. 猜对了询问是否换数列
    */
    // 创建数列
    const int seq_size = 18;
    int elem_seq[seq_size] = {
        1, 2, 3, // Fibonacci
        3, 4, 7, // Lucas
        2, 5, 12, // Pell
        3, 6, 10, // Triangular
        4, 9, 16, // Square
        5, 12, 22, // Pentagonal
    };
    // 数组名为数组元素起始地址
    // cout << *elem_seq << endl;
    // cout << *(elem_seq+17);
    vector<int> fibonacci(elem_seq, elem_seq+3), 
                lucas(elem_seq+3, elem_seq+6), 
                pell(elem_seq+6, elem_seq+9), 
                triangular(elem_seq+9, elem_seq+12), 
                square(elem_seq+12, elem_seq+15), 
                pentagonal(elem_seq+15, elem_seq+18);
    const int seq_cnt = 6;
    string seq_names[seq_cnt] = {"Fibonacci", "Lucas", "Pell",
                           "Triangular", "Square", "Pentagonal"};
    // 将每个数列的地址存入数组
    vector<int>* seq_addres[seq_cnt] = {&fibonacci, &lucas, &pell, &triangular, &square, &pentagonal};
    // 为数列的访问顺序增加随机性
    srand(seq_cnt); // 随机数生成器种子

    // 进行游戏
    float usr_score(0.0);
    char usr_rsp;
    
    while(true)
    {
        int seq_idx = rand() % seq_cnt; // rand()会返回[0,int]之间的整数
        const vector<int> *seq_ptr = seq_addres[seq_idx];
        int usr_guess;
        cout << "First element is : " << (*seq_ptr)[0] << endl;
        cout << "Second element is : " << (*seq_ptr)[1] << endl;
        cout << "Please enter next element: ";
        cin >> usr_guess;
        num_tries++;

        while(usr_guess != (*seq_ptr)[2])
        {
            switch (num_tries)
            {
                case 1:
                    cout << "Not correct! \n";
                    break;
                case 2:
                    cout << "Not correct!! \n";
                    break;
                default:
                    cout << "Not correct... \n";
                    break;
            }
            cout << "Are you ready to try again? Y/N" << endl;
            cin >> usr_rsp;
            if (usr_rsp=='N'|| usr_rsp=='n') break;
            
            cout << "Please enter next element: ";
            cin >> usr_guess;
            num_tries++;
        }
        if (usr_guess == (*seq_ptr)[2]) num_correct++;

        // 是否更换数列
        cout << "Try another sequence? Y/N" << endl;
        cin >> usr_rsp;
        if (usr_rsp=='N' || usr_rsp=='n') break;
    }
    cout << "The game is done!" << endl;
    usr_score = num_correct/float(num_tries);
    cout << "Your score is " << usr_score << endl;

    saveUsrInfo(usr_name, file_path, num_tries, num_correct);
    cout << "Your data have been saved, Bye!" << endl;
}


void vector_demo()
{   /** vector的使用示例 */

    vector<int> vec(7);
    for (unsigned int i=0; i<vec.size(); i++)
    {
        vec[i] = i;
    }
    // 使用指针直接访问元素
    vector<int>* vec_ptr = &vec;
    for (size_t i=0; i<vec_ptr->size(); i++)
    {
        cout << (*vec_ptr)[i] << ' '; // 下标运算符优先级较高
    }
    cout << endl;
    // 使用迭代器
    for (vector<int>::iterator it=vec_ptr->begin(); it !=vec_ptr->end(); it++)
    {
        cout << *it << ' ';
    }

    // 通过指针访问类成员函数
    // if (seq_ptr && !seq_ptr->empty())
    
}


int main(int argc, char** argv)
{
    // 读取创建用户信息
    string usr_name = getUserInfo();
    string file_path = "usr_database.txt";
    int num_tries, num_correct;
    loadUsrInfo(usr_name, file_path, num_tries, num_correct);
    usrGuessSequence(usr_name, file_path, num_tries, num_correct);

    return 0;

}

