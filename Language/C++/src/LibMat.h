/*
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-13 20:51:28
 * @LastEditTime: 2021-11-14 11:08:03
 */

class LibMat{
public:
    LibMat() { cout << "LibMat::LibMat() default constructor! \n"; }
    virtual ~LibMat() { cout << "LibMat::~LibMat() destructor! \n"; }
    
    virtual void print() const {cout << "LibMat::print() -- I am a LibMat object!  \n";}

private:

};


class Book : public LibMat{
public:
    Book(const string &title, const string &author): _title(title), _author(author)
    { cout << "Book::Book :" << _title << ' ' << _author << "constructor \n";}
    
    // 析构函数是虚函数是为了什么？
    virtual ~Book(){ cout << "Book::~Book() destructor! \n"; }

    virtual void print() const
    {
        cout << "Book::print() -- Book Object! \n";
        cout << "My title: " << _title << endl;
        cout << "My author: " << _author << endl;
    }

    // non-virtual inline function
    const string& title() const { return _title; }
    const string& author() const { return _author; }

protected:
    string _title;
    string _author;
};

class AudioBook : public Book{
public:
    AudioBook (const string &title, const string &author, const string &narrator):
        Book(title, author), _narrator(narrator)
        {
            cout<< "AudioBook:AudioBook constructor \n";
        }
    // 为何这里不是虚函数？
    ~AudioBook() { cout << "AudioBook::~AudioBook destructor! \n"; }

    virtual void print() const{
        cout << "AudioBook::print() -- AudioBook object! \n";
        // Book中定义的数据成员可直接使用，就像是自己的一样
        cout << _title << ' ' << _author << ' ' <<  _narrator << endl;
    }

    const string& narraotr() const { return _narrator; }

private:
    string _narrator;
};