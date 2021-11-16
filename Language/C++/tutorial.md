<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-11 16:52:54
 * @LastEditTime: 2021-11-16 19:57:18
-->
<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-10-27 22:21:52
 * @LastEditTime: 2021-11-11 16:49:15
-->
- [1. C++ 简明教程](#1-c-简明教程)
  - [1.1 快速入门](#11-快速入门)
    - [1.1.1 对象](#111-对象)
    - [1.1.2 表达式](#112-表达式)
    - [1.1.3 语句](#113-语句)
    - [1.1.4 函数](#114-函数)
    - [1.1.5 类](#115-类)
    - [1.1.6 指针](#116-指针)
    - [1.1.7 文件读写](#117-文件读写)
  - [1.2 面向过程编程](#12-面向过程编程)
    - [1.2.1 函数编写规则](#121-函数编写规则)
    - [1.2.2 inline函数](#122-inline函数)
    - [1.2.3 重载函数](#123-重载函数)
    - [1.2.4 模板函数](#124-模板函数)
    - [1.2.5 函数指针](#125-函数指针)
    - [1.2.6 头文件](#126-头文件)
  - [1.3 泛型编程](#13-泛型编程)
    - [1.3.1 泛型程序设计](#131-泛型程序设计)
    - [1.3.2 容器](#132-容器)
      - [1.3.2.1 顺序性容器](#1321-顺序性容器)
      - [1.3.2.2 关联性容器](#1322-关联性容器)
      - [1.3.2.3 容器类操作函数](#1323-容器类操作函数)
    - [1.3.3 泛型指针(iterator)](#133-泛型指针iterator)
    - [1.3.4 泛型算法](#134-泛型算法)
    - [1.3.5 设计泛型算法](#135-设计泛型算法)
    - [1.3.6 典型 Iterator](#136-典型-iterator)
  - [1.4 基于对象编程](#14-基于对象编程)
    - [1.4.1 类的基础实现](#141-类的基础实现)
    - [1.4.2 构造函数与析构函数](#142-构造函数与析构函数)
    - [1.4.3 定常成员函数与可变数据成员](#143-定常成员函数与可变数据成员)
    - [1.4.4 this指针](#144-this指针)
    - [1.4.5 静态类成员](#145-静态类成员)
    - [1.4.6 Iterator Class](#146-iterator-class)
    - [1.4.7 Friend](#147-friend)
    - [1.4.8 拷贝赋值运算符(copy assignment operator)](#148-拷贝赋值运算符copy-assignment-operator)
    - [1.4.9 Function Object](#149-function-object)
    - [1.4.10 重载 iostream 运算符](#1410-重载-iostream-运算符)
    - [1.4.11 指向类成员函数的指针](#1411-指向类成员函数的指针)
  - [1.5 面向对象编程](#15-面向对象编程)
    - [1.5.1 面向对象的基本概念](#151-面向对象的基本概念)
    - [1.5.2 定义抽象基类](#152-定义抽象基类)
    - [1.5.3 定义派生类](#153-定义派生类)
    - [1.5.4 初始化、析构、复制](#154-初始化析构复制)
  - [1.6 基于模板编程](#16-基于模板编程)
    - [1.6.1 模板类实现](#161-模板类实现)
  - [7. 异常处理](#7-异常处理)
    - [7.1 抛出异常](#71-抛出异常)
    - [7.2 捕获异常](#72-捕获异常)
    - [7.3 提炼异常](#73-提炼异常)
    - [7.4 局部资源管理](#74-局部资源管理)

# 1. C++ 简明教程
学习任何一种编程语言，初期要快速了解的核心知识无非就是以下三大块：
  - 首先要明确其可以操作的基本数据类型及其定义、初始化方式，以及基础的运算符如算数运算、关系运算、逻辑运算等表示形式，明确了这两点就可以写出基本的运算语句
  - 然后明确条件语句和循环语句的写法，以及函数的定义方式，我们就可以写出基本的函数了
  - 最后在学习一些该语言特有的复合类型如数组、指针等，以及一些标准的库函数，就可以利用该语言特性写出更高级别的代码

以上三大块在刚开始入门时切记不要追求广度和深度，每一部分都浅浅的知道最基础、最典型、最常用的部分即可，然后不断练习，上手实践，在后续使用中不断的扩充广度以及适时的根据项目需要增加了解的深度。

## 1.1 快速入门
### 1.1.1 对象
对象是我们程序中可以操作的基本单位，为了定义对象，我们必须为它命名，并明确其数据类型，有时还可以对其初始化赋予其初始值
  - 对象的名称可以使任意字母（区分大小写）、数字、下划线的组合，且不能以数字开头，也不能与程序语言本身已经定义的关键字完全一致
  - 每个对象都要属于某个特定的数据类型，其决定了对象所能持有的数值范围以及其应该占用的内存空间大小，
    - 可以是基本的内置数据类型，也可以是自定义的类型
  - 对象的初始化有两种语法，一种是常规的使用赋值语句`=`进行初始化，另一种是使用构造函数语法，如`int num(0)`
    - 二者的区别在于赋值语句仅能对对象进行进行单一值的初始化，如果对象需要多个初值，比如复数对象，就需要使用构造函数初始化语法：`complex<double> purei(0,7)`

基本的内置数据类型包括整数(int), 浮点数(float), 字符(char), 以及布尔值(bool)
  - int 包括`signed int` 和 `unsigned int`，表示范围为4个字节，还有`short`2个字节以及`long`8个字节
  - 浮点数`float`为单精度，还有`double` 双精度以及`long double`长双精度
  - 字符常量由一组单引号括住，通常分为两类：一类是可打印字符，如字母、数字、标点符号等；另一类是不可打印字符，如换行符`\n`,制表符`\t`等
  - 布尔对象的值为`true` 或 `false`

对象除了有类型这一必要属性之外，还有可变对象和常量对象之分
  - 通常我们对象的值一般都会在程序运行过程中改变，这种就是普通的直接用数据类型定义的对象
  - 如果某个对象比如圆周率等，其值永远不会改变，或我们需要防止其被无意中改动，就用`const`关键字可以定义为常量，如`const int MAXNUM = 100`
  - const的对象在定义时必须进行初始化，且一旦获得初值以后，就无法再有任何变动，任何企图为其指定新值的操作都会产生编译错误

### 1.1.2 表达式
利用运算符对对象进行相关运算，便构成了基本的表达式。内置数据类型都可以运用以下几种基本运算符：
  - 算数运算符：包括`+, -, *, /, %`; 注意：两个整数相除会产生另一个整数，小数部分直接舍弃
  - 关系运算符：结果不是true,就是false,包括`==, !=, >, <, >=, <=`
  - 逻辑运算符：包括`&&, ||, !`
  - 复合赋值运算符：用于在对象身上使用某个运算符，并重新赋值给该对象，包括`+=, -=, *=, /=, %=`

除以上几种运算符，还有一些其他常用运算符：
  - 条件运算符： `expr ? 如果expr为true，执行这里 : 否则，执行这里`, 构成了条件表达式
  - 递增递减运算符：`cnt++, cnt--`; 注意，递增递减都有前置和后置两种形式，前置是先递增后再来拿使用，后置相反

注意，当使用内置的运算符时，如果同一个表达式中包含多个运算符，其求值顺序是由每个运算符事先定义的优先级决定的，可使用小括号来改变内置运算符的优先级。各种运算符的优先级从高到低罗列如下（同一行优先级相同，按顺序由左至右运算）：
  - 逻辑运算符 `!`, 此运算符优先级最高，与其他一起使用时要特别注意，比如判断偶数`! val%2`就不同
  - 算数运算符 `*, /, %`
  - 算数运算符 `+, -`
  - 关系运算符 `<, >, <=, >=`
  - 关系运算符 `==, !=`
  - 逻辑运算符 `&&`
  - 逻辑运算符 `||`
  - 赋值运算符 `=`

### 1.1.3 语句
目前，我们已经学会了如何使用数据类型定义对象，并结合运算符撰写表达式进行算数运算或关系、逻辑运算。但仅仅依靠这些还无法编写真正的程序，还需要结合条件语句和循环语句，便构成了任何复杂代码的基石：
  - if 语句让我们依据某个表达式的结果(true or false)来决定是否执行其后一条或多条语句，else 子句可以用于连续检验多个测试条件
  - 循环语句让我们根据某个表达式的结果(true or false)重复执行单一的或连续的多条语句

**条件语句**
  - if 语句中的条件表达式必须写在括号内，如果该表达式为真，其后紧接着的一条语句便会被执行，如果想要连续执行多条语句，则需要用用括号将其括住形成语句块
  - else 子句除了作为if条件不满足的情况，还可以和if结合，继续对判断情况进行细分 `else if (expr)`
  - 当if-else 子句比较多时，较难进行精准划分，如果判断条件的值属于整数类型，我们可以改用switch语句来代替一大堆的`if-else-if`子句
  - 关键字switch之后紧接一个由小括号括住的表达式，该表达式的值必须是整数，然后跟一组case标签，每个标签之后都指定一个常量表达式。当switch后表达式的值被计算出之后，便依次和每个case标签的值进行比较，如果找到相符的case标签，则执行该语句，找不到便执行default标签，如果default未定义，则不执行任何操作
  - 注意，每个case标签内部最后都会加一个break语句，如果不加，则不会跳出switch语句，执行完此case后，还会继续执行后面的case

  ```c++
  swith (num_tries)
  {
    case 1:
        cout << xxx;
        break;
    case 2:
        cout << xxx;
        break;
    default:
        cout << xxx;
        break;
  }
  ```

**循环语句**
  - 只要条件表达式不断成立（运算结果为true），循环语句便会不断的执行单一语句或整个语句块，我们通过在循环体内部对表达式元素值进行更新从而确定是否继续迭代
  - 当然我们也可以利用`break`语句来跳出当前循环(最近的循环)，或使用`continue`语句跳过后续的语句，从下一次循环继续
  - 典型的循环语句包括while循环和for循环，while循环与条件语句类似，都是`关键字(expr)`,后跟中括号括住的语句块
  - for循环的基本形式为`for (init-statement; condition; expression) {statement}` 分别指定初始迭代条件、迭代判断条件和每次迭代后的迭代控制表达式

### 1.1.4 函数
基于以上概念，我们根据具体问题的需要定义需要处理的对象，通过相关表达式，并结合条件和循环语句，就可以撰写具有特定功能的函数，根据输入，计算我们想要的输出，从而解决特定的具体问题。c++ 函数的定义包含四个部分：
  - 返回值类型: 一般用于返回运算的结果，没有时可以定义为 `void`;
  - 函数名称: 这个由自己定义
  - 参数列表: 用两个括号括住，里面包含函数需要输入的参数，格式为`(参数类型 参数名, 参数类型 参数名)`
  - 以及函数体: 用大括号标出，在其内部编写相关代码，如对输入数据进行处理以及返回操作结果

注意，每个c++程序都是从一个名为`main`的函数开始执行，必须定义且只能有一个。

### 1.1.5 类
而C++的强大之处并不在于以上任意一种编程语言都具有的基本特性，还在于其对数据对象的抽象能力，即class的定义与使用。

所谓类，就是用户自定义的数据类型，class机制让我们可以将各种基础数据类型进行重新组织，并定义一些基础操作，作为新的数据类型加入到我们的程序中，从而在程序内实现对类型层次化的抽象：
  - 比如一个照相机通常包含三维的空间位置、三维的视角方向以及一个窗口的宽-高比，总计七个浮点数
  - 如果我们单独定义七个浮点数，必然会让我们在“照相机的抽象性质”和“对应于其七个浮点数”之间来还切换
  - 如果我们先定义一个由三个浮点数组成的`Point3D`类，再用两个`Point3D`和一个浮点数组成一个`Camera`类，这样我们就可以直接对照相机进行操作，而不是单独操作对应的浮点数

class的定义，一般分为两部分，分别写在不同的文件中：
  - 头文件：用来声明该类所提供的各种操作行为
  - 程序代码文件：包含这些操作行为的实现内容

要想使用某个类，我们必须先在程序中包含其头文件，这样程序就可以知道该class的定义。
 - 比如最常用的标准“输入/输出库”，里面包含了相关的整套class，用来支持对终端和文件的输入与输出，我们通过`#include <iostream> ` 来声明对该类的使用
 - 我们可以直接利用已经定义好的`cout`对象，结合output运算符`<<`，将数据定向到`cout`,如`cout<<"Hello World"`

在声明头文件之后，我们通常会加一个`using namespace std;` 用来指明在本代码文件内，我们默认使用标准库的命名空间，`std`就是c++标准库所驻之命名空间的名称。
  - 命名空间`namespace`是一种将库名称封装起来的方法
  - 如果我们代码文件内有两个不同的实体`entity`具有相同的名称，则无法区分二者，我们使用命名空间，就可以将二者进行区分。
  - 我们声明使用的命名空间，就可以将其包含的名称曝光，这样在使用时就可以直接使用，否则就得用`std::cout`

c++自定义的基础数据类型功能有限，除了自己根据需要定义相关类，C++及其标准库中还包含了其他数据类型，其中数组是最常用的数据类型之一，数组有array和vector两种实现方式，二者都是为了对同一类型的数据以序列的形式进行组织。

**Array 与 Vector**
  - 要定义array，必须分别指定元素类型、array名称及其尺寸大小：`int arr[10]`，定义是也可不指定大小`int arr[]={x,x}`，编译器会根据初值的数量进行推断
  - array对象初始化可直接使用中括号指定每个元素的值，元素个数不能超过array指定的尺寸，可以小于(未指定的默认为0)
  - vector定义前必须包含vector头文件，因为vector是一个模板类，因此必须在类名后的尖括号内指定元素类型，大小则写在对象名后的小括号中：`vector<int> vec(10)`
  - vector的初始化由6种方式：(1). 默认初始化，不指定，全部为0 `vector<int> vec;` (2). 拷贝初始化，直接拷贝另一个vecto的元素`vector<int> vec(vec1);` (3). 列表初始化`vector<int> vec={1,2};` (4). 指定范围初始化`vector<int> vec(vec1.begin()+2, vec1.end()-1);` (5). 默认值初始化 `vector<int> vec(7);` (6). 指定值初始化 `vector<int> vec(7,3);`
  - 无论是array还是vector，都可以通过索引(从0开始)指定容器中的某个位置，从而访问该位置上的元素

### 1.1.6 指针
上一节我们通过名称+索引访问vector内的每个元素，这一节我们将使用使用指针，通过操作指针(代表某个特定的地址)，而不再直接操作对象，为程序引入一层间接性。
  - 指针即是某个特定类型对象的地址，因此和定义对象一样，定义指针同样需要指定其指向元素的类型，为了和定义对象相区分，元素类型后还要加上星号,如`int *pr`，代表指向某个int型对象的指针
  - 指针代表地址，因此其初始化就是给他指定某个对象的地址，需要用到取地址符`&`，即 `pr = &ival`
  - 进一步的，如果要访问指针所指内存地址上的对象，依然使用星号 `int a = *pr`进行提领操作
  - 注意：因为指针可以不指向任何对象(其地址为0)，因此在对指针进行提领操作之前要确定其指向某个对象`if (pr)`
**dot成员选择运算符与arrow成员选择运算符**
  - 通常类对象都会包含一系列可以调用的对象，我们可以使用对象名结合dot运算符进行调用`vec.empty()`
  - 如果我们定义了该对象的指针，我们则可以通过指针，结合arrow运算符进行调用`vec->empty()`
  - 指针还可以和下表运算符结合吗？当然可以！只要先进行提领就可以了`*vec[1]`,同样在提领前一定要先判断指针有效性！

### 1.1.7 文件读写
我们通过函数来完成具体的功能，而函数的输入输出除了通过终端进行输入输出以外，还可以通过文件进行长久的保存和读取
```c++
#include<fstream> // 包含文件读写类的定义

// 写文件
ofstream outfile("data.txt"); // 定义输出内容到指定文件的file stream对象，同时传入文件地址
// 若文件不存在，则会自动创建；
// 默认会从头开始写，可以设定追加模式 ofstream outfile("adta.txt", ios_base::app);
// 文件有可能打开失败，因此在进行写入操作之前，我们必须确定文件的确已经打开成功: 直接检验类对象的真伪
if (outfile)
{
  outfile<< usr_name << ' ' ;
}

// 读文件
ifstream infile("data.txt") 
if (infile)
{
  while(infile>>name)
  {
    // 一直读到文件末尾
  }
}

// 读写文件
fstream iofile("data.txt", ios_base::in|ios_base::app); // 指定追加模式
if (iofile)
{
  iofile.seekg(0); //将文件重新定位至起始处，否则会在文件末尾
}

```


## 1.2 面向过程编程
面向过程是一种以事件为中心的编程思想，编程时把要解决问题的步骤分析出来，然后通过具体函数把这些步骤逐一实现，最后在一步一步的具体步骤中再按顺序逐个调用函数，最终完成整个操作流程。

以下五子棋问题为例，面向过程的设计思路是首先分析解决这个问题的步骤：
  - （1）开始游戏（2）黑子先走（3）绘制画面（4）判断输赢（5）轮到白子（6）绘制画面（7）判断输赢（8）返回步骤（2）（9）输出最后结果。
  - 以上每个步骤都可以编写成一个个的子函数，最后在下五子棋的主函数里依次调用上面的函数
 
因此，面向过程的编程始终关注的是怎么一步一步地解决问题，通过编写函数，从而实现解决步骤的顺序执行。显然，函数是面向过程编程的核心，本章我们就来深入的探讨函数的编写规则，并简要讨论重载、模板函数以及函数指针的使用技巧。

### 1.2.1 函数编写规则
**函数定义**
  - 每一个函数必须定义以下四个部分：返回类型、函数名、参数列表、函数体
  - 函数声明不必提供函数体，只需要指明返回类型、函数名、参数列表即可，即函数原型：`int fibo(int pos);`
    - 函数必须先被声明，然后才能被调用
    - 函数声明让编译器得以检查后续出现的使用方式是否正确，比如是否输入了足够的参数、参数的类型是否正确等；
  - 函数定义包括函数原型+函数体：注意，在函数体内，函数只能返回一个值

**传值与传址**
  - 当我们调用一个函数时，会在内存中建立起一块特殊区域，称为“程序堆栈”，这块特殊区域提供了每个函数参数的存储空间，及函数内新定义对象的内存空间，这些对象被称为 局部对象
  - 一旦函数调用结束，这块内存就会被释放掉，局部对象也就不复存在
  - 当我们使用常规方式将对象通过函数参数传入时，默认情形下其值会被赋值一份，创建一个新的局部对象，这种方式称为 **传值**：即在函数外部传给函数参数的对象和函数内部实际操作的对象，二者之间没有任何的关系
  - 要让二者产生关联的方式是 **传址**：即将参数声明为一个引用 `int &elem`：当我们以传址的方式将对象作为函数参数传入时，对象本身并不会复制出一份，复制的是对象的地址，因此我们在函数内部对该对象进行的任何操作，都是相当于通过地址，直接操作的原始对象
  - 这样做的好处除了某些功能上的需求以外，还可以大大降低复制大行对象所带来的额外的负担
  - 注意：在c++中，引用一旦确定，便不可修改，不可以改变某个引用所代表的对象
  - 同时，我们对引用的操作，就等价于操作该引用所代表的对象，因为引用，其实就是对象的别名
  - 进一步的，我们虽然使用了传址，但又不想函数对该对象进行修改，则我们可以声明一个定常引用`const vector<int> &vec`
  - 既然传引用就是传址，我们当然也可以直接显式的传址：`const vector<int> *vec`, 效果是一样的，只是具体用法会有所不同: 比如使用时需要先提领`(*vec)[idx]`，提领前先判断地址有效性，实际调用时传递给参数的是地址而非对象名`dispaly(&vec)`

**作用域及范围**
  - 之前已经讲了程序堆栈的概念，因此，除了static对象，函数内部定义的对象，只存在于函数执行期间，如果将这些局部对象的地址返回，将会在运行时出错
  - 为对象分配的内存，其存活时间称为存储期或范围。每次函数执行，都会为其内部对象分配内存，函数调用结束时释放内存，我们称函数内部的对象具有 局部性范围 (local extent)
  - 对象在程序内的存活区域称为该对象的scope (作用域)，比如函数内定义的对象，仅在该函数内部存活，具有local scope, 在函数外声明的对象，则具有 file scope, 从其声明点至文件末尾都是可见的
  - 注意，对于内置类型的对象，如果定义在file scope之内，则必定被初始化为0. 但如果被定义域local scope之内，除非指定初值，否则不会被初始化

**动态内存管理**
  - 不论是 local scope 还是 file scope，其内存都是由系统自动管理的
  - 还有一种存储期形式称为 dynamic extent (动态范围)：其内存由程序的空闲空间分配而来，也称作堆内存：这种内存由程序员自行管理，分配和释放分别通过 `new` 和 `delete` 表达式实现
  - 使用new从heap分配来的对象，具有dynamic extent,可以持续存活，直到以delete表达式释放为止
  - 注意，如果不使用delete表达式，从heap分配而来的对象就永远不会被释放，这称为 memory leak （内存泄露）

  ```c++
  int *pi;
  pi = new int; // 先由heap分配出一个int类型的对象，再将其地址赋值给pi; 这里并没有指定初值
  // 指定初值的方式
  pi = new int(10); // 同样先由heap分配除一个int类型的对象，将其地址赋值给pi，同时将此对象的值初始化为102，注意是对象的值，并不是对象的地址
  // 从heap中分配数组
  int *pia = new int[24]; //包含24个整数的数组，pia初始化为数组第一个元素的地址，数组中每个元素的值并未初始化
  delete pi; // 释放pi所指向的对象
  delete [] pia; // 删除数组中的所有对象
  ```

**默认参数值**
  - c++ 运行我们为全部或部分参数设定默认值，这样可以在函数调用时根据不同情况采用默认值，或使用不同的参数从而实现特定的效果,如 `void display(string msg, ostream &os=cout)`,默认将输出传给cout,我们实际调用也可以提供输出到文件的对象
  - 如果我们为某个参数提供了默认值，这一参数右侧的所有参数都必须要有默认值：因为默认值的解析是从最右边开始进行
  - 默认值只能够指定一次：可以在函数声明处，也可以在函数定义处，但不能两个地方都指定
    - 因为函数声明一般都会放在头文件，每个打算使用该函数的文件，都需要包含该头文件 (函数定义放在程序的代码文件，该文件只被编译一次，当我们想要使用该函数时，会将它链接到我们的程序中来)，也就是说，头文件为函数带来更高的可见性
  - 因此，为了更高的可见性，我们一般将默认值放在函数声明处

  ```c++
  void print_msg(string &msg, ofstream *ofile=0)
  {
    // 注意这里必须传递ofile对象的地址而非引用，因为这样才能将默认值设定为0
    // 而引用则必须要代表某个对象
    if (ofile!=0)
    {
      (*file) << msg;
    }
    cout << msg; 
  }
  ```

**局部静态对象**
  - 和局部非静态对象不同，局部静态对象(local static object)所处的内存空间，即使在不同的函数调用过程中，依然持续存在，不会像之前提到的局部对象那样，函数调用一次，生成并释放一次，而是可以在之前基础上继续使用
  
  ```c++
  const vector<int>* fibon_seq(int size)
  {
    static vector<int> elems;
    for (int i=elem.size(); i<size; i++)
    {
      if (ix==0 || ix==1) elems.push_back(i);
      else elems.push_back(elems[i-1]+elems[i-2]);
    }
    return &elems; // 因为是局部静态对象，所以可以返回其地址
  }
  ```

### 1.2.2 inline函数
有时为了逻辑的清晰性和代码可读性，我们会将不同的小功能封装成一个个的小函数，然后在同一个大函数中逐一调用。但这样也会带来性能的损失，inline函数可以克服这一缺点。

将函数声明为inline，表示要求编译器在每个函数的调用点上，将函数的内容展开。因此面对一个inline函数，编译器可将该函数的调用操作改为以一份函数代码的副本代替，这将是我们获得性能改善。在实现将多个函数写入同一个大函数的同时，依然维持多个独立的运算单元。
  - 具体使用方式为在函数前面加上关键字inline，如 `inline bool fibon_elem(int pos, int &elem)`
  - 通常，体积较小、常被调用，且所从事的计算并不复杂，这类函数最适合被声明为inline函数
  - inline函数的定义，通常被放在头文件中

### 1.2.3 重载函数
当我们面临多个功能类似，可能只是输入参数的类型、数量有细微差别时，按照传统的函数定义方法，我们就需要声明并定义不同的函数，这个是可以理解的，毕竟处理方式是不同的，但我们真的需要使用不同的函数名称吗？根据参数列表的不同不就可以区分了吗？这样调用时岂不是更为方便，而无需单独记忆每个函数的名称，这就是**函数重载**：
  - 函数重载机制规定参数列表不同(可能是参数类型不同，也可能是参数个数不同)的两个或多个函数，可以拥有相同的函数名称
  - 在实际调用时，编译器将根据调用者提供的实际参数拿来和每个重载函数的参数进行比对，找出其中符合的进行调用，因此，每个重载函数的参数列表必须和其他重载函数不同！
  - 对于重载方法，不要试图通过给予不同的返回值类型（参数列表完全相同）加以区分。 因为方法在调用时可以不将返回值赋值给一个对应的变量，这样就没有特征区分。
  - 因此，在进行函数重载时，函数返回类型可以相同也可以不同，我们要保证的是函数名称必须相同，参数列表必须不同！

  ```c++
  // 函数重载
  void display_msg(const string&, const vector<int>&);
  void display_msg(const string&, const vector<double>&);
  void display_msg(const string&, const vector<string>&);
  ```
### 1.2.4 模板函数
上一小节的最后我们给出了一个较为特别的函数重载的例子，这三个函数除了第二个参数类型不同以外，函数体对数据的处理过程基本一致，这时我们使用函数重载仅仅是减轻了我们调用时的麻烦，进行函数定义时仍然进行了多次内容相似的定义，万一还有其他类型，我们还要不同的复制粘贴函数定义，然后做一点小修改。

那么有没有一种机制，可以将单一函数的内容与希望处理的各种不同的参数类型绑定起来呢？这就是函数模板(function template):
  - 函数模板将参数列表中指定的全部(或部分)参数的类型信息抽离出来，在实际调用时再由用户进行具体指定
  - 函数模板以关键字 template 开场，其后紧接用尖括号包围起来的一个或多个标识符，表示我们希望推迟决定的数据类型。
  - 这些标识符事实上扮演者占位符的角色，用来放置函数参数列表即函数体中的某些实际**数据类型**。用户每次利用这一模板产生函数时，都必须提供确实的类型信息
  - 借助函数模板，我们可以通过它产生无数函数，elemType可以被绑定为任意内置类型或用户自定义类型

  ```c++
  // 关键字 typename 后接 elemType表示 elemType在display_msg函数汇总只是一个暂时放置类型的占位符
  template <typename elemType> void display_msg(const string &msg, const vector<elemType> &vec)
  {
    cout << msg;
    for (int ix=0; ix<vec.size(); ++ix>)
    {
      elemType t = vec[ix]; cout << t;
    }
  }

  // 更进一步的，函数重载和函数模板也可以同时使用
  template <typename elemType> void display_msg(const string &msg, const list<elemType> &lt);

  int main() 
  {
    vector<int> vec = {1,2,3};
    string msg = "Hello";
	  display_msg(msg, vec); // 在这里编译器会将elemType绑定为int类型，产生包含具体类型的函数实例
  }
  ```

### 1.2.5 函数指针
接下来我们使用函数指针来进一步增加函数的灵活性
  - 所谓函数指针，从字面理解就是指向函数的指针，和相比指向普通数据类型指针`int *pr`,多了参数列表，代表它指向的是一个函数
  - 函数指针的定义包含：函数的返回类型、参数列表、指针符号*、以及这个函数指针的名称： `const vector<int>* (*seq_ptr)(int)`; 注意，指针和指针名必须括在一起，否则就会和返回值类型结合，变成一个普通函数的定义，返回值类型为指针的指针
  - 这样我们就可以用这个函数指针用作参数，将其指向不同的函数，实现灵活调用

  ```c++
  // 使用函数指针作为函数参数，方便在其内部调用不同函数
  bool seq_elem(int pos, int &elem, const vector<int>* (*seq_ptr)(int))
  {
    const vector<int>* pseq = seq_ptr(pos); // 由函数指针指向的函数，调用方式和普通函数相同
    // 当前为了安全起见，我们在调用前可以先检验地址有效性 if (seq_ptr)
    // 也可以在参数列表中给函数指针赋初值 const vector<int>* (*seq_ptr)(int)=0; 代表不指向任何函数
    if (!pseq){elem = 0; return false};
    elem = (*pseq)[pos-1];
    return true;
  }

  // 具体调用时如何传入函数地址？  函数名即是！
  // 为了可以不断指定多个函数，我们可以定义一个存放函数指针的数组
  const vector<int>* (*seq_array[])(int) = {fibon_seq, lucas_seq, pell_seq};
  // 在使用时直接索引即可
  seq_ptr = seq_array[idx];

  // 但索引不方便记忆，我们可以使用枚举实现常量到索引的映射
  enum ns_type {ns_fibon, ns_lucas, ns_pell}; // enum之后的标识符可有可无
  // 第一个枚举值为0，第二个为1，以此类推
  seq_ptr = seq_array[ns_fibon];
  ```

### 1.2.6 头文件
在上一节中，我们定义了`seq_elem`函数，在调用该函数前，我们必须声明他，但如果我们要在五个程序文件中调用，我们就必须进行五次声明操作。为了避免分别进行五次声明，我们将函数声明统一放在头文件中，这样在每个程序代码文件中只需要include该头文件，就包含了这些函数声明
  - 使用头文件统一管理函数声明，我们只需要维护一份声明即可，如果其参数列表或返回类型需要改变，也只需要更改此份声明即可
  - 头文件的扩展名为`.h`,标准库没有扩展名
  - 因为函数的定义只能有一份，因此我们不能把函数定义放如头文件，否则当多个代码文件都包含这个头文件时会引发重复定义
  
只定义一次的规则也有例外：
  - inline函数：为了能够扩展inline函数的内容，在每个调用点上，编译器都需要取得其定义并将其展开，因此我们必须将inline函数定义在头文件中
  - 在file scope内定义的对象，如果可能被多个文件访问，同样也可以放在头文件中。但由于对象的定义就像函数一样，只能定义一次，我们如果在头文件中用普通的定义方式定义，就会被当做定义，之后就会引发重复定义，因此我们要在头文件内对对象进行声明而非定义，声明方式为加关键字 `extern`
  - 指针数组对象的声明： `extern const vector<int>* (*seq_array[seq_cnt])(int)`
  - 但const object的声明并不用extern: `const int seq_int=6;` 这是一个例外约定，约定const object只要一出文件便不可见，因此允许我们在多个程序代码中多次定义
  - 那刚才的指针数组就不是const object 吗？当然不是！它是一个指向const object的指针，但它本身并不是一个const object;

最后需要说明的是，在包含头文件时
  - 如果头文件和包含此文件的程序代码文件位于同一磁盘目录下，我们便使用双引号`#include "NumSeq.h"`
  - 如果在不同的磁盘目录下，我们边用尖括号：这样此文件会被认定为标准的或项目专属的头文件，编译器会现在默认的磁盘目录中寻找对应文件；
  - 否则认为是由用户提供的，会由包含此文件的文件所在的磁盘目录开始找起


## 1.3 泛型编程
### 1.3.1 泛型程序设计
泛型程序设计是程序设计语言的一种风格或范式。泛型允许程序员在 强类型设计语言 中编写代码时使用一些以后才指定的类型，在实例化时作为参数指明这些类型。各种程序设计语言和其编译器、运行环境对泛型的支持均不一样，C++中的泛型称之为模板。

上一章节我们便介绍了模板的概念，模板是c++程序设计语言中的一个重要特征，而标准模板库正是基于此特征的大型软件库，其大量影响了c++标准程序库，但并非是其中的一部分，使得c++编程语言在有了同java一样强大的类库的同时，保有了更大的可扩展性。STL定义了一套概念体系，为泛型程序设计提供了逻辑基础，主要包含四个组件，分别为：算法、容器、函数、迭代器。具体来讲，STL将“在数据上执行的操作” 与 “要执行操作的数据” 分开，分别用如下概念进行指代：
  - 容器：包含、放置数据的地方
  - 迭代器：在容器中指出一个位置、或成对使用用于划定一个区域，用来限定操作所涉及到的数据范围，是算法和容器的桥梁，将迭代器作为算法的参数，通过迭代器来访问容器而不是把容器直接作为算法的参数
  - 函数对象：将函数对象作为算法的参数而不是将函数所执行的运算作为算法的一部分
  - 算法：要执行的操作; 使用STL中提供的或自定义的迭代器和函数对象，配合STL的算法，可以组合出各种各样的功能，且具有泛型特征。

**容器**  
容器从数据组织方式上可以分为两类：
  - 一种是顺序性容器，依次维护第一个、第二个 ...直到最后一个元素，我们在顺序性容器上主要进行所谓的迭代操作，主要有：`vector, list, forward_list, deque, array`
  - 一种是关联容器，用于快速查找容器中的元素值，主要有：`set, multiset, map, multimap, unordered_set, unordered_multiset, unordered_map, unordered_multimap`
  - 其他类型容器：`bitset, valarray`

**迭代器**  
迭代器是泛化的指针，通过使用迭代器，开发者可以操作数据结构而无需关心其内部的实现。根据迭代器操作方式的不同，迭代器分为五种：
  - 输入迭代器
  - 输出迭代器
  - 前向迭代器
  - 双向迭代器
  - 随机访问迭代器

**算法**  
STL提供了一些常见的算法，如排序和搜索等
  - 这些算法与数据结构的实现进行了分离
  - 因此，可以对自定义的数据结构使用这些算法，只需要让自定义的数据结构拥有算法所预期的迭代器

**函数对象**  
  - 狭义的函数对象即 重载了操作符() 的类的实例
  - 广义来讲所有可用 x(...) 形式调用的x都可称为函数对象，或可调用对象

**适配器(Adapter)**  
适配器是一个模板类，用于提供接口映射


### 1.3.2 容器
#### 1.3.2.1 顺序性容器  
顺序性容器用来维护一组排列有序、类型相同的元素，其典型代表是vector和list
  - vector用一块连续内存来存放元素，vector内的每个元素都被存储在距离起始点的固定偏移位置上，因此对与随机访问效率很高，但插入和删除由于需要移动其他元素，效率较低
  - list以双向链接而非连续内存来存储内容，每个元素都包含三个字段：value, back和front指针，在任意位置插入删除效率较高，但随机访问需要遍历，因此效率较低
  - 第三种顺序性容器是deque(双端队列): 其行为和vector颇为相似，都是以连续内存存储元素，但和vector不同的是，该队列的每一端都可以添加元素或删除元素，对于前后端元素的插入和删除操作，效率更高 (标准库的queue便是以deque实现)
  
  ```c++
  // 要使用顺序性容器，必须包含相关头文件
  #include <vector>
  #include <list>
  #include <deque>
  // 顺序性容器定义：五种方式
  list<string> slist;  // 1. 产生空容器
  vector<string> svec(32); // 2. 产生特定大小容器，元素初值为类型默认值
  list<string> slist(16, "unassigned"); // 3. 产生特定大小容器，并为每个元素指定初值
  int ia[3] = {1,1,2};
  vector<int> fibon(ia, ia+3); // 4. 通过一对iterator产生容器
  vector<int> vec(fibon); // 5. 通过某个容器产生新容器
  // 常用操作函数
  .push_back();  // 末尾插入
  .pop_back();   // 末尾删除
  .push_front(); // 首端插入 （list和deque）
  .pop_front();  // 首端删除
  .front();      // 返回首端值； pop并不会返回值
  .back();       // 返回末尾值
  // 通用的插入函数insert
  iterator insert(iterator position); // 1. 在position之前插入元素，初值为默认值
  iterator insert(iterator position, elemType value); // 2. 将value插入position之前，返回一个iterator指向被插入元素
  void insert(iterator position, int count, elemType value); // 3. 在position之前插入 count个元素，元素值都和value值相同
  void insert(iterator1 position, iterator2 first, iterator2 last); // 4. 在position之前插入 [first, last) 所标的各个元素
  // 通用的删除函数erase
  iterator erase(iterator pos); // 1.删除pos所指元素
  iterator erase(iterator first, iterator last); // 2. 删除 [first, last) 内元素
  // 返回的iterator均是被删除的最后一个元素的下一个位置
  ```
#### 1.3.2.2 关联性容器
关联性容器主要包括map和set:
  - map是一对对的key-value组合，key用于查找，value用来表示我们要存储或取出的数据；注意任何一个key值在map内最多只有一份
  - set仅含有key，通过对key查询，判断该值是否存在于容器中

  ```c++
  // map的定义与使用
  #include<map>
  #include<string>
  map<string, int> words; // 用于统计字符出现的个数
  words["vermeer"] = 1; // 建立key-value的映射；取值直接 words["vermeer"]即可
  while(cin>>tword) words[tword]++; // 进行数据统计；如果tword不在map内，则会被自动创建，默认值为0
  // 使用map对象的first member 和 second member
  map<string, int>::iterator it = words.begin();
  for (; it!=words.end(); it++) cout << "key:" << it.first << "value:" << it.second <<end;
  // 查询map内的对象
  int count = 0;
  if(!(count=words["vermeer"])) // 1. 直接通过索引进行查询，但查询后会将其加入map
  it = words.find("vermeer") // 2. 使用map的find()函数，注意不是泛型算法的find();找不到返回end()
  if (word.count("vermeer")) // 3. 使用count函数返回其在map中的个数：0 or 1
  
  // set的定义与使用
  vector<int> vec = {1,2,2,3,4};
  set<int> iset(vec.begin(), vec.end()); //set元素依据其所属类型默认的less-than运算符进行排列
  iset.insert(ival); // 插入单一元素
  iset.insert(vec.begin(), vec.end()); //插入某个范围元素
  // set迭代
  for (; it!=set.end(); it++) cout << *it;
  // 另外，泛型算法中有不少和set相关的算法
  set_intersetion(); set_union(); 
  set_difference(); set_symmetric_difference();
  ```

#### 1.3.2.3 容器类操作函数
下列为所有容器类（以及string类）的共通操作：
  - equality(==) 和 inequality (!=) 运算符：返回true或false
  - assignment (=) 运算符：将某个容器复制给另一个容器
  - empty(): 容器无任何元素时返回true，否则返回false
  - size(): 返回容器内目前持有的元素个数
  - clear(): 删除所有元素
  - begin(): 返回一个iterator，指向容器的第一个元素
  - end(): 返回一个iterator，指向容器的最后一个元素的下一个位置
  - insert(): 将单一或某个范围内的元素插入容器
  - erase(): 将容器内单一或某个范围内的元素删除

注意：insert()和erase()的行为视容器本身为顺序性容器或关联性容器的不同而有所不同。


### 1.3.3 泛型指针(iterator)
首先假定我们的任务是需要实现一个find函数，给定一个存储整数的vector以及一个整数值，如果此值存在，则返回一个指向该值的指针，否则返回0，我们很容易给出下面的实现
  ```c++
  int* find(const vector<int> &vec, int &value){
    for (int i=0; i<vec.size(); i++) {if (vec[ix]==value) return &vec[ix];}
    return 0;
  }
  ```

接下来如果又要求我们的find函数不仅可以处理整数，也可以处理浮点数等其他任何类型，该怎么做呢？显然，结合我们第二章节的知识，我们可以使用函数模板进行实现，前提只需要保证该类型定义有equality(相等)运算符即可。
  ```c++
  template <typename elemType>
  elemType* find(const vector<elemType> &vec, int &value){
    for (int i=0; i<vec.size(); i++) {if (vec[ix]==value) return &vec[ix];}
    return 0;
  }
  ```

更进一步，如果再要求不仅可以处理vector,也能处理array，该怎么做呢？当然我们可以使用函数重载进行分别定义，但还有其他更好的可以仅定义一份函数的方案吗？我们从两份函数的不同之处出发，二者的区别就在于传入的参数不同，其内部处理逻辑都是一致的，那么我们能不能传入同样的参数呢？解决方案就是我们使用指针作为参数，传入vector或array的首地址，然后通过该指针不断的在内存中迭代寻找剩余元素，这样就实现了操作对象和具体容器类型的剥离。
  ```c++
  // 方案1：传入首地址和array大小，结合指针的下标运算对实现对数组指定范围的迭代
  template <typename elemType>
  elemType* find(const elemType *arr, int size, const elemType &value){
    if (!arr || size<1) return 0;
    for (int i=0; i<size; i++) {if (arr[ix]==value) return &arr[ix];}
    // 指针的下标运算包含两步：(1). 将arr的起始地址加上索引值(会考虑指针所指类型的大小)，得到某个元素的地址； (2). 然后根据此地址进行提领操作，得到此元素值
    // 因此从外在形式来看，指针的下标运算与直接对对象进行索引操作并无不同
    return 0;
  }
  // 方案2：传入首地址和结束地址的下一位置，结合在指针算数运算实现对数组的指定范围的迭代
  template <typename elemType>
  elemType* find(const elemType *first, const elemType*last, const elemType &value){
    if (!first || !last) return 0;
    for (; first!=last; first++) {if (*first==value) return first;}
    return 0;
  // 使用
  int ia[8] = {1,2,3,4,5,6,7,8};
  int *pi = find(ia, ia+8, ia[3]); // ia+8是最后一个元素的下一个地址
  // 如果我们要对此地址进行读取或写入，是不合法的，但如果当作标兵用来比较，是可以的
  }
  ```

上述实现很好的解决了array的问题，但vector可以吗？几乎已经可以了！只需要再考虑一点特殊情况，vector为空时的情况，这是如果再传入其首地址，就会导致运行错误，我们可以再传入前执行非空检查`if (!vec.empty()`，但不够通用，我们将其进行封装
  ```c++
  template <typename elemType>
  inline elemType* begin(const vector<elemType> vec) {return vec.empty()? 0 : &vec[0];}
  ```
同样，我们也封装一个end()函数，用来返回vector最后与一个元素的下一个地址，我们便最终得到了一个可以应用于任意vector的find函数
  ```c++
  find(begin(vec), end(vec), search_value);
  ```

但我们就止步于此吗？还能让此函数进一步泛化到能够处理标准库中所有的容器类吗？比如list?
  - list也是一个容器，不同的是，list的元素不是存在一段地址连续的内存空间中，而是以一组指针相互链接(linked)，分别通过forward和backward指针分别指向下一个和上一个元素
  - 因此，指针的算数运算并不适用于list，因此之前我们假设元素都存在连续内存空间中，我们便可以根据当前指针，加上元素大小，指向下一个元素

解决方案就是在底层指针的行为之上提供一层抽象，取代程序原本的“指针直接操作”的方式。我们把底层指针的处理通通放在此抽象层中，这样用户就无需直接面对指针操作！
  - 具体来讲，我们需要定义一组迭代对象，其提供和内置运算符(++, *, ==, !=)相同的运算符，这样我们就可以使用和指针相同的语法来进行迭代检索
  - 比如first和last都是list的iterator，我希望它能够像指针一样`while (first!=last){cout << *first; ++first;}`，但实际上他的提领(*)运算符，不等(!=)运算符，自增(++)运算符都是我们由我们iterator class内相关的inline函数提供的
  - 虽然内部实现和指针的算数运算不同，但外在表现都是相同的，这就是“底层指针行为之上的抽象”： 如果他是一个list的iterator，递增函数会沿着list的指针前进到下一个元素；如果是一个vector的iterator，递增函数就是根据当前地址加上元素大小到达下一个元素；外在表现上，我们的操作都是和我们之前操作指针一样直接使用 `++first`!

在后续章节中，我们会讲解如何实现这个iterator class，这里我们先关注如何定义并使用标准容器的iterator：
  - 每个标准容器都提供一个begin()操作函数，可以返回一个指向第一个元素的iterator
  - 以及一个名为end()的操作函数，指向最后一个元素的下一个位置
  - 对于iterator的定义我们需要考虑两个方面：
    - (1). 首先这份定义应该提供迭代对象(某个容器)的类型，用来决定如何访问下一元素; 
    - (2). 其次也要指明iterator所指的元素类型，决定了iterator提领操作的返回值
  - iterator定义的标准语法为`vector<string>::iterator iter = vec.begin()`
    - 表示iter被定义为一个iterator，指向一个vector，其内部元素类型为string,初值指向第一个元素
    - 双冒号表示此iterator是位于string vector定义内的嵌套类型
  - 明确了定义和获取方式，后续使用比如赋值、比较、递增、提领等操作和指针并无二致
  - 和指针类似，我们要通过iter调用底部string元素所提供的操作，可以使用arrow运算符：`iter->size()`
  
  ```c++
  // 现在我们来重写find()，让他同时支持两种形式：一对指针，或一对指向某种容器的iterator
  template<typename iteratorType, typename elemType>
  iteratorType find(iteratorType first, iteratorType last, const elemType &value){
    for (, first!=last; first++) { if (*first==value) return first; }
    return last;
  }
  // 使用find同时处理array, vector 和 list
  const int asize = 5; int ia[size] = {1,2,3,4,5}; 
  vector<int> ivec(ia, ia+size); list<int> ilist(ia, ia+size);
  int *pia = find(ia, ia+size, 3);
  vector<int>::iterator it = find(ivec.begin(), ivec.end(), 3);
  list<int>::const_iterator iter = find(ilist.begin(), ilist.end(), 3); //只读
  ```

到此为止，我们已经让find()有了极大地通用性，我们可以不用关注元素类型，也不用关注容器类型。但还有一个小细节是我们find在实现过程中用到了底部元素的equality运算符，如果底部元素是我们自定义的其他类型，并没有提供这个运算符，或者用户希望赋予equality 运算符不同的意义，此find元素又不行了：
  - 解决方案之一是传入一个函数指针，取代原本固定使用的equality 运算符
  - 或者运用所谓的 function object (一种特殊的class，第四章会进行介绍)
  - 因此我们下一阶段的目标便是将find变成真正的泛型算法（如标准库中的find_if(),能够介绍函数指针或function object，取代底部元素的equality运算符）


### 1.3.4 泛型算法
泛型算法提供了许多可用于容器类即数组类型上的操作，这些算法之所以被称为泛型，是因为它们和要操作的元素类型无关，比如元素类型无论是int,double,还是string,都不影响算法的实现，同样也和容器类彼此独立（不论容器是vector、list或array）
  - 前一章节已经介绍过，要达到“与操作对象的类型相互独立”的目的，可以使用 函数模板 技术
  - 进一步要实现“与容器无关”，那就不要直接在容器身上进行操作，通过借由一对iterator(first 和 last),表示我们要进行迭代的元素范围：
    - `first==last`: 只作用于first所指元素
    - `first!=last`: 首先作用于first所指元素，然后将first递增，指向下一个位置，然后比较二者是否相等，如此持续进行，直到first等于last为止
  
本节介绍一些典型的泛型算法的应用，欲使用泛型算法，首先得包含对应的头文件：`#include<algorithm>`
1. find(): 用于搜索无序集合中是否存在某值，搜索范围由iterator [first, last) 标出，如果找到目标，返回一个iterator指向该值，否则指向last
2. binary_search(): 用于有序集合的搜索，找到返回true,否则false
3. count(): 返回数值相符的元素数目
4. search(): 对比某个容器内是否存在某个子序列，找到返回iteartor指向子序列起始处，否则指向末尾
5. max_element(): 返回范围内的最大值
6. copy(): 复制容器，两个iterator参数标识出复制范围，第三个iterator指向复制行为的目的地的第一个元素

C++标准库中总共有超过60个泛型算法，一些典型的为
  - 搜索算法 (search algorithm): `find(), count(), adjacent_find(), find_if(), count_if(), binary_search(), find_first_of()`
  - 排序(sort)及次序整理(ordering)算法: `sort(), merge(), partial_sort(), partition(), random_shuffle(), reverse(), ratate()`
  - 复制(copy)、删除(delete)、替换(substitution)算法: ` copy(), remove(), remove_if(), replace(), replace_if(), swap(), unique() `
  - 关系(relational)算法: `equal(), include(), mismatch()`
  - 生成(generation)与质变(mutation)算法:` fill(), for_each(), generate(), transform() `
  - 数值(numeric)算法: ` accmulate(), adjacent_difference(), partial_sum(), inner_product() `
  - 集合(set)算法: ` set_union(), set_difference() `


### 1.3.5 设计泛型算法
考虑一个新任务，给定一个整数vector，返回一个新的vector，仅包含原vector中小于10的所有数值。我们很容器便可以写出一个普通的filter函数：
  ```c++
  vector<int> filter(const vector<int> &vec, int less_than_val)
  {
    vector<int> fvec;
    for (int x : vec) if (x<less_than_val) fvec.push_back(x);
    return fvec;
  }
  ```

接下来增加以下函数的弹性，我们希望允许用户指定不同比较操作，如大于、小于，那么如何才能将 “比较操作” 参数化呢？可以用函数调用来取代less-than运算符：加入第三个参数pred,用它来指定一个函数指针，其参数列表有两个整数，返回值为bool
  ```c++
  // 首先我们预定义一些可传给filter()的关系比较函数
  bool less_than(int v1, int v2) {return v1<v2 ? true : false; }
  bool greater_than(int v1, int v2) {return v1>v2 ? true : false; }
  // 定义新的filter函数
  vector<int> filter(const vector<int> &vec, int filter_value, bool (*pred)(int, int))
  {
    vector<int> fvec;
    for (int x : vec) if (pred(x, filter_value)) fvec.push_back(x);
    return fvec;
  }
  // 调用filter()
  vector<int> res = fileter(vec, value, less_than); // 函数名即为函数地址
  ```

在继续优化filter()之前我们先来了解 function object 以及 function object adapter的概念。

**Function Object**  
  - 所谓function object，是某种class的实例对象，这类class对function call运算符`()`做了重载操作，如此一来，可使function object被当做一般函数来使用（仿函数）
  - function object实现了我们原本用独立函数进行定义的事物，这样做的原因主要是为了效率。令call运算符称为inline，可以消除 “通过函数指针来调用函数”时需要付出的额外的代价
  - 标准库事先定义了一组function object,分为算数运算、关系运算、逻辑运算三大类：
    - 六个算术运算：plus<type>, minus<type>, negate<type>, multiplies<type>, divides<type>, modules<type>
    - 六个关系运算：less<type>, less_equal<type>, greater<type>, greater_equal<type>, equal_to<type>, not_equal_to<type>
    - 三个逻辑运算：logical_and<type>, logical_or<type>, logical_not<type>
  ```c++
  #include<functional> // 预使用事先定义的function object, 需要包含相关头文件
  sort(vec.begin(), vec.end(), greater<int>()); // 利用call运算符，将function object当做普通函数调用
  ```

**Function Object Adapter**  
  - 一般来讲，function object 期望外界传入两个值，有时我们希望他是一个一元运算符，比如每个元素和指定元素进行比较，这就需要我们把其第二个参数绑定至用户指定的数值，这时便需要标准库所提供的adapter
  - funtion object adapter 会对function object进行修改操作：所谓binder adapter (绑定适配器)会将function object的参数绑定至某特定值，使binary function object 转化为 unary function object
  - 标准库提供了两个binder adapter: `bind1st`会将指定值绑定至第一操作数；`bind2nd`会将指定值绑定至第二操作数
  - 如 `bind2nd(less<int>, val)`: 将val绑定于less<int>的第二个参数上，于是，less<int>会将每个元素拿来和val比较

重新回到之前的例子，我们用泛型算法find_if()来代替实现过程中的for循环，将find_if反复作用于数列，找出符合条件的每一个元素，所谓“条件”则由我们刚才提到的function object确定
  ```c++
  vector<int> filter(const vector<int> &vec, int val, less<int> &lt)
  {
    vector<int> fvec;
    vector<int>::const_iterator iter = vec.begin();
    while( (iter=find_if(iter, vec.end(), bind2nd(lt, val))) != vec.end() )
    {
      fvec.push_back(*iter);
      iter++;
    }
    return fvec;
  }
  ```

最后，采用上节介绍的套路，我们来消除filter 与 vector元素类型、vector容器类型之间的依赖关系：
  - 使用函数模板来消除元素间的依赖性
  - 传入一对iterator[first, last)来消除容器类型的依赖性
  - 额外传入一个ieterator，指向结果容器，用于复制筛选出的元素

  ```c++
  template<typename InputIterator, typename OutputIterator, typename elemType, typename Comp>
  OutputIterator filter(InputIterator first, InputIterator last, OutputIterator at, const ElemType &val, Comp pred)
  {
    while( (first=find_if(first, last, bind2nd(pred, val))) != last ) *at++ = *first++;
    return at;
  }
  // 调用
  filter(ivec.begin(), ivec.end(), ivec2.begin(), value, greater<int>());
  ```

另一种adapter是所谓的negator，他会对function object的真伪值取反：
  - not1 可对unary function object的真伪值取反：比如找出大于等于10的元素`not1(bind2nd(less<int>,10))`
  - not2 可对binary function object的真伪值取反


### 1.3.6 典型 Iterator
**Iterator Inserter**  
先前我们通过两个iterator进行值拷贝，`*at++=*first++`,这种情况下，目的端的容器必须足够大，用于存储被赋值进来的每个元素，但filter()无法知道每次对at递增之后，at是否仍然指向一个有效的容器位置。为了解决整个问题，标准库提供了三个所谓的insertion adapter，这些adapter让我们得以避免使用容器的assignment运算符：
  - back_inserter() 会以容器的push_back()函数取代assignment运算符：`unique_copy(ivec.begin(), ivec.end(), back_inserter(res_vec));`
  - inserter() 会以容器的insert()函数取代assignment运算符，inserter()接受两个参数，一个是容器，另一个是iterator，指向容器的插入操作起点：` unique_copy(ivec.begin(), ivec.end(), inserter(res_vec, res_vec.end() )); `
  - front_inserter() 会以容器的push_front()函数取代assignment运算符，这个inserter只适用于list和deque: ` copy(ilist.begin(), ilist.end(), front_inserter(res_list)); `
  - 注意这些adapter并不能用于array上，array并不支持元素插入操作

回到之前的filter的例子，我们调用filter时不再传入目标容器的iterator，而是采用vector的back_inserter，这样目标容器就可以是一个空的容器，然后不断在容器末端执行插入：
  - `filter(ivec.begin(), ivec.end(), back_inserter(ivec2), value, greater<int>());`

**iostream Iterator**  
考虑一个新任务，从标准输入设备读取一串string元素，将他们存到vector内，并进行排序，最后再将这些字符串写回标准输出设备。常规写法并不必说，这里我们来看如何使用iterator实现。

标准库定义有供输入输出使用的iostream iterator类，称为 istream_iterator 和 ostream_iterator，分别支持单一类型的元素读取和写入
  - 首先为了使用这两个类，我们要包含其头文件 `#include<iterator>`
  - 其次，就像所有的iterator一样，我们需要一对first和last iterator，用来标识元素范围
  - 对于first，我们定义为 "绑定至标准输入设备" 的 istream_iterator：`istream_iterator<string> is(cin)`
  - 对于last， 我们希望它表示 "要读取的最后一个元素的下一位置"，对标准输入设备而言，就是 end-of-file, 我们只需要在定义时不为他指定istream对象即可： `istream_iterator<string> eof`
  - 对于ostream_iterator,我们需要用它表示字符串元素的输出位置，我们用ostream_iterator绑定标准输出设备：`ostream_iterator<string> os(cout, " ");`,第二个从参数表示输出各元素之间的分隔符

  ```c++
  // 完整示例代码
  #include<iostream>
  #include<iterator>
  #include<algorithm>
  #include<vector>
  #include<stirng>
  using namespace std;

  int main()
  {
    istream_iterator<string> is(cin); // 如果我们需要从文件读入，绑定ifstream对象即可
    // ifstream in_file("input_file.txt"); istream_iterator<string> is(in_file)
    istream_iterator<string> eof;
    vector<string> text;
    copy(is, eof, back_inserter(text));

    sort(text.begin(), text.end());

    ostream_iterator os(cout, " "); // 若输出到文件，绑定ofstream: // ofstream out_file("out_file.txt");
    copy(text.begin(), text.end(), os);
  }
  ```


## 1.4 基于对象编程
在之前的章节中，我们已经广泛运用了很多常用的class: string、vector 以及提供输入输出功能的iostream class。在本章节中，我们来尝试设计并实现自己的class:
  - class 名称被视为一个类型名称，就像内置类型int,double一样，class的初始化方式根据其构造函数定义，通常有多种方式，最基本的范式为`string str("dummy")`
  - 每个class都会提供一组操作函数，让我们作用于其实例化后的对象上。这些操作函数包括具名函数，如size()和empty()，以及重载运算符，如equality和assignment运算符
  - class一般由两部分组成：一组公开的(public)操作函数和运算符； 以及一组私有的(private)实现细节；
  - 公开的操作函数函数和运算符被称为class的成员函数(member function)，代表这个class的公开接口，class的用户只能访问其公开接口
  - class的private 实现细节可由成员函数的定义以及与此class相关的任何数据组成

class的用户无需关注class的实现细节，只是利用其公开接口就进行编程，因此，只要类的接口没有更改，即使其实现细节重新打造，所有应用程序代码也不需要进行任何改动，这便是基于对象编程的基本思想。

### 1.4.1 类的基础实现
本节我们先从编写一个最基本的类开始。但在具体实现一个类之前，我们先从 “抽象”(abstraction)开始，比如我们要实现一个栈，首先要抽象出我们期望其包含的操作行为：
  - 以 *pushing* 的方式将新值压入堆栈
  - 以 *popping* 的方式取出最近被压入的值
  - 以 *peeking* 的方式，查看最后一个被压入的数值
  - 询问是否已满 *full*，是否为空*empty*，以及stack内的元素个数 *size*

类的具体实现如下：
```c++
//// Stack.h file
#include<vector>
#include<string>
using namespace std;

class Stack; // 1. class 前置声明：关键字class + 类名

// 2. class 定义：声明 + 主体
class Stack{
public: 
    bool push(const string&);
    bool pop(string &elem);
    bool peek(string &elem);

    bool empty();
    bool full();

    int size() {return _stack.size();} // 成员函数定义

private:
    vector<string> _stack;
};

//// 3. inline member function
inline bool Stack::empty() { return _stack.empty();}

inline bool Stack::full() { return _stack.size() == _stack.max_size();}

// Stack.cpp file
#include "Stack.h"

// 5. non-inline member funtion
bool Stack::pop(string &elem){
    if (empty()) return false; // 因为已经进行了类作用域解析，成员函数可直接使用

    elem = _stack.back();
    _stack.pop_back();
    return true;
}

bool Stack::peek(string &elem){
    if (empty()) return false;

    elem = _stack.back();
    return true;
}

bool Stack::push(const string &elem){
    if (full()) return false;

    _stack.push_back(elem);
    return true;
}
```

1. 类的前置声明只是用来将类的名称告诉编译器，并未提供关于此类的任何其他信息，如成员函数及数据成员等，但前置声明使得我们得以进行类指针的定义，或以此class作为数据类型：
   ```c++
   // 以下两种写法，必须先有类的前置声明才行
   Stack *pt = 0;
   void process(const Stack&)
   ```
2. class定义由声明及紧接之后的主体组成，主体由一对括号括住，并以分号结尾
   - 主体内的两个关键字`public` 和 `private`标示每个块内成员的访问权限：public member 可以在程序的任何地方被访问； private member只能在 member function 和 class friend内被访问
   - 类的所有成员函数都必须在类的主体内进行声明，但是否同时进行定义，可自由决定
   - 如果要在类主体内定义，该成员函数会被自动视为 inline 函数，如本例中的 size()
  
3. 类的成员函数也可主体外进行定义，需要使用类作用域解析运算符`::`，用来编译器分辨该函数属于哪一个类
   - 如果希望该函数为inline，在最前面加上关键字inline即可
   - 对于inline函数，定义与类的主体内或主体外没有分别，但同其他 non-member inline function一样，要把它放在头文件中

4. 通常，类的定义和其 inline member function 需要放在与该class同名的.h头文件中,用户想要使用该class时，包含该头文件即可
   
5. non-inline member function 在程序代码中定义，通常放在和class同名，扩展名为`.cpp`的文件中


### 1.4.2 构造函数与析构函数
上一小节中我们主要介绍了class的基本构成和定义方法，特别是member function 的定义，但忽略了一个重要问题，class中的data member如何初始化呢？这就需要我们事先提供一个或多个特别的初始化函数，编译器会在每次class object 被定义出来时，调用适当的函数加以处理，这些特别的函便是构造函数(constructor)。

**构造函数**
  - 构造函数的名称必须与class名称相同，且不用指定返回类型，因此也没有返回值
  - 构造函数可以被重载，因此我们可以一次定义多个构造函数，当类对象被实例化后，编译器便自动根据获的参数，挑选出应被调用的constructor
  - 具体例子见 [Triangular class](./src/Triangular.h) 定义
  ```c++
  // 1. 类对象调用构造函数
  Triangular t1; // 调用无任何参数的默认构造函数
  Triangular t2=8; // 调用包含一个参数的构造函数，等价于 Triangular t2(8)
  Triangular t3(10, 3); // 调用包含两个参数的构造函数
  Triangular t4(); // 错误！这样会把t4定义成参数列表为空，一个返回值类型为Triangular的函数！
  ```

除了按照上述方法在构造函数体内对数据成员采用默认值或指定参数进行初始化，我们还可以通过成员初始化列表进行初始化：
  - 成员初始化列表紧接在参数列表最后的冒号后面，各参数之间用逗号分隔
  - 欲赋值给数据成员的数值放在成员名称后面的小括号内
  - 成员初始化列表主要用于将参数传给 member class object的构造函数
  ```c++
  Triangular::Triangular(const Triangualr &rhs): _length(rhs._length), _beg_pos(rhs._beg_pos), _next(rhs._beg_pos-1) { }
  ```

**析构函数**  
和构造函数对应的是析构函数(destructor)。所谓析构函数是用户自定义的一个类成员，一旦某个类提供有析构函数，当其object结束生命时，便会自动调用destructor处理善后：主要是释放constructor中或对象生命周期中分配的资源
  - 析构函数的名称有严格的规定，类名称再加上`~`前缀，它不仅没有返回值，也没有任何参数
  - 因为参数列表为空，因此析构函数也没法被重载
  - 具体例子见[Matrix class](./src/Matrix.h)的定义，构造函数使用new表达式从heap中分配double数组所需的空间，而destructor则负责释放这些内存

但析构并非绝对必要的，比如我们上面的Triangular的例子，三个数据成员均是以储值(by value)的方式来存放，这些数据成员在类对象定义之后便已存在，当对象结束其声明周期时被释放，因此，并不需要我们定义析构函数。实际上，c++最难得部分之一便是了解何时需要定义析构函数何时不需要。

**成员逐一初始化与拷贝构造函数**  
除了在构建对象时通过构造函数将初值传入进行数据成员的初始化，我们也可使用某个已经实例化的类对象作为另一个类对象的初值: `Triangular tri1(8); Triangular tri2 = tri1;`, 类内的数据成员会被依次复制，即执行默认的成员逐一初始化操作
  - 上述操作对Triangular类是没有问题的，但对于Matrix类则会出现问题，因为执行成员的逐一拷贝时，两个类对象的_pmat指针会指向同一个位置，而依次执行析构函数时，前面的析构函数已经将该内存空间释放，后面的析构函数就会引发错误

为了解决这个问题，我们为Matrix提供一个拷贝构造函数(Copy Constructor):
  - 拷贝构造函数的唯一参数是一个 const reference, 指向一个Matrix的 对象，然后在函数内部改变成员逐一初始化的默认行为模式
  - 具体来讲，我们通过产生一个独立的数组复本，使某个对象的析构操作不至于影响另一个对象

  ```c++
  Matrix::Matrix(const Matrix &rhs): _row(rhs.row), _col(rhs.col)
  {
    int n = _row*_col;
    _pmat = new double[n]; // 产生一份复本
    for (int i=0; i<n; i++) _pmat[i] = rhs._pat[i];
  }
  ```

因此，当我们设计class时，必须思考在此class之上进行“成员逐一初始化”的行为模式是否适当，如果可以，则不必提供拷贝构造函数；否则，则必须重新定义拷贝构造函数。当然，如果我们定义了拷贝构造函数，也需要重新定义拷贝赋值运算符，这个我们后面再介绍。

### 1.4.3 定常成员函数与可变数据成员
首先我们先来看一个小函数：
  ```c++
  int sum(const Triangular &train){
    int beg_pos = train.beg_pos(), length = train.length(), sum = 0;
    for (int i=0; i<lenght; i++>) sum += train.elem(beg_pos+ix);
    return sum; 
  }
  ```
上面的train是个const reference, 即编译器必须保证train在sum()中不会被修改，但sum()中调用的任何一个member function都有可能更改train的值。编译器要保证sum中调用的成员函数，如begin_pos, length(), elem都不会更改其调用者，那么编译器怎么知道他们不会更改呢？我们就需要将这个成员函数标注为const,来告诉编译器：这个成员函数不会更改对象的内容。
  - 要实现const对成员函数的修饰，需要将const置于参数列表之后，函数体花括号之前
  - 如果成员函数在class主体之外定义，就必须在声明和定义中都指定const
  - 虽然编译器不会对每个函数进行分析，决定它究竟是const还是non-const，但它会检查每个声明为const的成员函数，看他们是否真的没有更改类对象的内容

我们再来看上述sum()的另一个版本：
  ```c++
  int sum(const Triangular &train){
    if (!train.length()) return 0;
    int val, sum = 0; 
    train.next_reset();
    while(train.next(val)) sum += val;
    return sum;
  }
  ```
上述函数确无法通过编译，因为我们train声明为了一个const object，但我们调用next_reset()和next()时确对train的数据成员`_next`进行了修改，或者说next_reset()，next()都不是const member function, 确被const object调用，于是必然造成错误

但我们换种思维方式，数据成员`_length`和`_beg_pos`提供了数列的抽象属性，如果我们改变对其进行改变，就相当与改变了数列的长度和起始位置，即对对象train的状态进行了改变。但数据成员`_next`只是我们用来对train的数据元素进行迭代的，改变`_next`其实并没有对class object状态造成影响，即并没有破坏对象的常量性！
  - 因此，关键字`mutable`就是为了让我们做出这种声明：对_next所做的更改并不会破坏class object的常量性

最后，通过将`_next`声明为`mutable`，next()和next_reset()便既可以修改_next的值，又可以被声明为 const member function, 第二个版本的sum()实现便没有问题了！

### 1.4.4 this指针
当我们希望用一个对象复制出另一个对象，这时就需要我们定义一个copy()成员函数，用于将一个对象数据成员的值作为另一个对象的初值：
  ```c++
  Triangular tr1(8);
  Triangular tr2(8,9);
  tr1.copy(tr2);

  Triangular& Triangular::copy(const Triangular &rhs)
  {
    if (this != &rhs){
      _length = rhs._length;
      _beg_pos = rhs._beg_pos;
      _next = rhs._beg_pos-1;
    }
    return *this; // 想要返回tr1,只需要提领this指针
  }
  ```
在copy()函数的实现中，我们涉及到了一个新的概念，this 指针：this指针在成员函数内用来指向其调用者(对象)，在本例中，便是tr1。为什么我们可以直接使用呢？这是因为编译器会自动将this指针加到每一个成员函数的参数列表，在参数列表内声明`Triangular *this`

### 1.4.5 静态类成员
**Static Data Member**  
在第二章中我们曾定义了一个局部静态 vector 用来存储Fibonnacci数列元素，以避免函数运行时数列元素的重复运算。现在我们设计的类内也需要一个唯一的容器来存储数列元素，我们同样使用static关键字来实现
  - static data member 用来表示唯一的，可共享的数据成员，它可以在同一类的所有对象中被访问
  - 对于class而言，静态数据成员只有唯一的一份实体，因此我们同样需要在程序代码文件中提供其清楚的定义，类似于全局对象的定义，但这里需要加上class scope 运算符：`vector<int> Triangular::_elems;`, 除了定义，我们也可以直接指定初值：`int Triangluar::_initial_size=8`;
  - 如果要在类成员函数内访问静态数据成员，其访问方式和普通的非静态数据成员一致

**Static Member Function**  
  - 通常情况下，我们都是通过类的某个对象来对其成员函数进行调用，这个对象会被绑定至该成员函数的this指针，通过存储与每个对象中的this指针，成员函数才能够访问存储于每个对象中的 non-static data member;
  - 但我们如果我们的成员函数并没有访问任何 non-static data member, 他的工作和任何对象都没有关联，比如只是访问static data member,如我们Triangular 类中的 is_elem()，我们还要将他与对象绑定吗？
  - 当然不用，我们只需要将此成员函数声明为static，在函数的声明前加上关键字static，后续使用时就可以直接使用，而不是通过对象调用
  - 调用方式为 `Triangular::is_elem(8);` 当然 class scope 运算符是必不可少的，不然不知道是哪一个类的is_elem();
  - 和static data member 一样，当我们在class主体外部进行成员函数的定义时，无需重复加上关键字static

### 1.4.6 Iterator Class
本节我们来亲自实现一个Iterator class，通过对其实现来了解如何对class进行运算符的重载操作。首选，我们希望能够实现如下操作：
  ```c++
  Triangular trian(1, 8);
  Triangualr::iterator it = trian.begin(), end_it = trian.end();
  while(it!=end_it)
  {
    cout << *it << ' ';
    ++it;
  }
  ```

为了让上述代码能够工作，我们必须为此iterator class 定义 `!=, *, ++` 等运算符:
  - 实际实现见[Triangual_iterator class 实现](./src/Triangular_iterator.h)
  - 我们可以像定义成员函数那样来定义运算符：运算符函数和普通函数类似，但他们不需要指定函数名，只需要在运算符前面加上`operator`关键字即可
  - 具体来讲，我们定义Triangular_iterator class用来维护一个索引值，用以索引Triangular中用来存储数列元素的那个 static data member, 即 _elems
  - 为了能够索引Triangular的数据成员，Triangular必须赋予Triangualr_iterator成员函数特殊的访问权限（即通过friend机制实现）
  - 具体运算符函数的实现，以`==` 运算符为例：如果两个Triangular_iterator对象的 _index相等，我们便认为这两个对象相等

  ```c++
  // 通过运算符重载，我们就可以将运算符直接作用于我们新定义的类对象
  if (trian1 == trian2) ...
  // 如果我们希望将运算符作用于指针所指的对象，就得先提领该指针，取出所指对象：
  if (*ptril == *ptril) ...
  ```

运算符重载主要包含以下几个规则：
  - 不可以引入新的运算符，除了`., .*, ::, ?:`四个运算符，其他的运算符皆可被重载
  - 运算符的操作数个数不可被改变，每个二元运算符都需要两个操作数，一元运算符都需要恰好一个操作数
  - 运算符的优先级不可改变，例如除法的运算符优先级永远高于加法
  - 运算符函数的参数列表中，必须至少有一个参数为class类型，也就是是说，我们无法为诸如指针之类的non-class类型，重新定义其原已存在的运算符，当然更无法为它引入新的运算符

到此为止，我们仅仅对运算符进行了重载，我们还需要为Triangular提供一组begin()/end()成员函数，并支持上述iterator的定义，这需要用到 嵌套类型 (nested type)的概念。具体实现参见[Triangual class 实现](./src/Triangular.h)

**嵌套类型**  
typedef 可以为某个类型设定另一个不同的名称，其通用形式为：`typedef existing_type new_name`:
  - 其中`existing_type`可以是任何一个内置类型、符合类型或class类型
  - 在我们的例子中，我们用iterator等同于Triangular_iterator，以简化其形式
  - 使用时通过`Triangular::iterator it = trian.begin();` class scope运算符来指引编译器，让他看到iterator这个字眼时，查看Triangular内提供的定义，如果我们直接 `iterator it = trian.begin()`，则必然出现错误

这样我们将iterator嵌套放在每个“提供iterator抽象概念”的class内，我们就可以提供有着相同名称的多个定义：
  - `Fibonacci::iterator fit = fib.begin();`
  - `Pell::iterator pit = pell.begin();`
  - `string::iterator sit = file_name.begin();`


### 1.4.7 Friend
在上一节中，我们定义的non-member function operator*()竟然直接访问了Triangular的私有数据成员_elems, 也访问了Triangular_iterator 的私有成员函数 check_integrity()！这是因为任何class都可以将其他function或class指定为朋友(friend):
  - 所谓friend，便具备了与 class member function 相同的访问权限，可以访问class的私有成员
  - 因此，为了让operator*()通过编译，不论Triangular 还是 Triangular_iterator 都必须将operator*()声明为“朋友”
  - 也就是说，只要在某个函数原型前加上关键字friend，就可以将它声明为某个class的friend，这份声明可以出现在class定义的任意位置上，不受private或public的影响
  - 如果你需要将数个重载函数都声明为某个class的friend，必须明确的为每个函数都加上friend,比如我们实现的operator*() 的两个版本

除了将函数声明为friend，我们也可以令class A 与 class B 建立friend关系，借此让class A的所有member function 都称为class B的friend，例如
  ```c++
  class Triangular {
    friend class Triangular_iterator; // 这样Triangular_iterator的所有member function都是 Triangular 的friend
  }
  ```

注意，友谊的建立通常是为了效率考虑，例如在某个non-member运算符函数中进行Point和Matrix的乘法运算，如果我们只是希望进行某个data member的读取和写入，那么为他提供具有public访问权限的inline 函数，就是建立友谊之外的一个替代方案。


### 1.4.8 拷贝赋值运算符(copy assignment operator)
默认情况下，当我们将某个class object 赋值给另一个，比如 `Triangular tri1(8), tri2(8,9); tri1 = tri2;`：
  - 对象tri2的数据成员会被依次复制给tri1，即默认的成员逐一复制操作
  - 对于Triangular这个类，使用默认的成员逐一复制即可，我们不需要做其他事情，但对于之前提到的Matrix class,使用这种复制方式便会出现问题（两个指针指向同一个位置）

因此我们需要一个拷贝构造函数和一个拷贝赋值运算符，前者在1.4.2节已经介绍过，这里我们来看Matrix的copy assignment operator的定义，详见 [Matrix.cpp](./src/Matrix.cpp)

只要class设计这明确提供了拷贝赋值运算符，他就会被用来取代"默认的成员逐一复制操作"，当然，对于类的使用者来说，他们在使用时没有任何区别，只需要重新编译即可。


### 1.4.9 Function Object
在3.6节中，我们直接使用了一些标注库事先定义好的function object，本节我们来自己实现一个function object。所谓function object,是一种“提供有function call运算符”的类，当编译器在编译过程中遇到`lt(ival);` lt 其实有三种可能：
  - lt是函数名称
  - lt是函数指针
  - lt是一个提供了function call 运算符的 函数对象，即编译器会将其转化为`lt.operator(ival);`

Funciton call 运算符可以接受任意个数的参数：零个，一个，两个或更多。比如可以用来支持Matrix的多维度下标操作，因为正常的下标运算符只能接受一个参数。

接下来我们定义一个LessThan class，用来提供一个function object, 来测试传入值是否小于某个指定值。该类包含一个基值，每个类对象初始化时都必须设定为基值。具体的例子参见 [LessThan.h](./src/LessThan.h)

### 1.4.10 重载 iostream 运算符
我们可以很自然的使用输出运算符 `cout << "hello world";`来对字符串对象进行输出，但如果使我们自己新定义的class object，还可以直接用输入输出运算符进行读取和写入操作吗？当然不行，需要我们另外提供一份重载的output运算符，从而实现`cout << trian << endl;` 以及 `cin >> trian;`
  - 在实现中，我们传入ostream的对象又被原封不动的返回，这样就可以串接多个输出运算符
  - 虽然参数列表中两个对象皆是以传址的形式传入，但ostream对象并未声明为const，因为每个output操作都会更改ostream 的内部状态
  - 另一个疑问是我们为何没有把output运算符设计成Triangular的成员函数呢？因为如果是成员函数，他的左操作数就必须是隶属于同一个class的对象，这样我们调用时就必须是`tri<<cout;`的形式

  ```c++
   ostream& operator<< (ostream &os, const Triangular &rhs)
   {
       os << "( " << rhs.beg_pos() << ", " << rhs.length() << " )";
       rhs.display(rhs.length(), rhs.beg_pos(), os);
       return os;
   }

   istream& operator>>(istream &is, Triangular &rhs)
   {
       char ch1, ch2;
       int bp, len;
       // 假设输入 （3，6） 6 10 
       is >> ch1 >> bp >> ch2 >> len;
       //rhs.beg_pos(bp); // 待实现
       //rhs.length(len);
       rhs.next_reset();
       return is;
   }
   // 测试
   Triangular tri(20);
    Triangular_iterator it = tri.begin();
    Triangular_iterator end_it = tri.end();
    cout << tri.length() << endl;
    while(it !=end_it)
    {
        cout << *it << ' ';
        ++it;
    }

    cout << tri<<endl;
  ```

### 1.4.11 指向类成员函数的指针
在之前的章节中，我们通过完整了的实现了Triangular类，了解了类的实现所涉及的知识点。通过此例子，我们便可以很快地实现其他数列，区别仅仅在于数列的产生算法不同。本节我们希望能够实现一个通用的数列类 num_sequence，使其对象能够同时支持6种数列：
  ```c++
  int main()
  {
    num_sequence ns;
    const int pos = 8;
    for (int x = 1; i<num_sequence::num_of_sequence(); ++i)
    {
      ns.set_sequence(num_sequence::ns_type[ix]);
      int elem_val = ns.elem(pos);
      display(cout, ns, pos, elem_val);
    }
  }
  ```
num_sequence 的设计关键在于，运用一个指向成员函数的指针，这种指针和我们之前介绍的指向非成员函数的指针比较相似：
  - 二者都需要指定其返回类型和参数列表，不过，指向成员函数的指针还需要表明它所指的是哪一个class：`void (num_sequence::*pm)(int) = 0`
  - 声明一个指向num_sequnce 成员函数的指针，且该成员函数的返回值必须为void，且参数列表必须是单个int，初始值为0代表暂时不指向任何一个成员函数
  - 上述指针的定义方式过于复杂，我们可以用嵌套类型加以简化 `typedef void (num_sequence::*PtrType)(int);`
  - 这样我们对函数名称进行取址（同样也需要加上类名），就可以定义并初始化一个指向具体的成员函数的指针：`PtrType pm = &num_sequence::fibonacci;`

```c++
#include<vector>
using namespace std;

class num_sequence{
public:
    typedef void (num_sequence::*PtrType)(int);
    
    // _pmf 可以指向下列任何一个函数
    void fibonacci(int);
    void pell(int);
    void lucas(int);
    void triangular(int);
    void sequare(int);
    void pentagonal(int);

private:
    PtrType _pmf;
    vector<int>* _elem; // 指向目前所用的vector
    static const int num_seq = 7;
    static PtrType func_tbl[num_seq]; // 存放成员函数地址
    static vector<vector<int>> seq; // 存放数列

};
```

## 1.5 面向对象编程
第四章我们介绍了基于对象的编程，即通过自己设计class，引入一个崭新的数据类型，从而更直接的在我们所设计的程序系统中表现我们想表现的实体：
  - 比如一个图书馆的借阅系统，我们通过设计Book, Borrower, DueData等类，然后基于这些类进行程序设计，肯定要比基于基本的数据类型，比如字符、算数、布尔等类型要轻松得多。

但当我们的系统逐步复杂，添加的类越来越多，且类之有着 “is a kind of”的关系时，基于类的编程反而会让我们的编程越来越麻烦：
  - 比如一段时间后图书馆借阅系统需要进一步的对之前的Book类进行划分，如 RentalBook, AudioBook, InterativeBook等，按照基于对象编程的思想，我们需要在重新逐个定义这些类吗？
  - 但明显每个类之间可能会共享一些 data member 以及 member function; 但也有可能会增加其自身特有的特殊数据，以及特有的借还程序、罚款计算方式等
  - 因此，第四章介绍的基于对象的编程中介绍的类机制无法针对这四个隶属同类的Book类的共通性质进行系统化的划分，因为这种模型无法让我们指出类间的关系

类间的关系就需要面向对象的编程模型加以设定

### 1.5.1 面向对象的基本概念
面向对象编程的概念两项最主要的特征是 "继承" 和 "多态"：
  - 继承让我们得以将一群相关的类组织起来，并让我们可以分享其间的共通数据和操作行为
  - 多态让我们在这些类上进行编程时，可以如同操控的单个个体，而非相互独立的类，并赋予我们更多弹性来加入或移除任何特定的类

**继承**  
首先，继承机制定义了 “父子” 关系：父亲被称为基类(base class)，子类被称为派生类(derived class)，父类和子类之间的关系则称为继承体系：
  - 父类定义了所有子类共通的 公有接口 和 私有实现
  - 而每个子类都可以增加或覆盖继承而来的东西，以实现其自身独特的行为

**抽象基类**  
还是以图书馆借阅管理系统为例，最上层是一个libMat类，它下面包括Book，childToys, Manazines, Films等子类，而Book又可以进一步细分为RentalBook, AudioBook, CDIBook等。从名字也可以看出，LibMat并不代表图书馆中实际存在的任何一个馆藏，它仅仅是为了我们设计上的需要而抽象出来的，但这个抽象十分关键，我们称之为“抽象基类”
  - 在面向对象的程序设计中，我们会间接利用“指向抽象基类的指针或引用”来操作系统中的各个对象，而不是直接操作各个实际对象
  - 以下面的例子为例，我们的例子并不存在LibMat对象，只有Book, RentalBook等类的对象，因此当我们执行loan_check_in()时，mat必定要指向我们程序中某个实际的对象，进而通过mat调用的check_in()函数也势必被解析为mat所代表的实际对象所拥有的那个check_in()函数
  - 因此问题的关键在于，这到底是怎么实现的呢？
  ```c++
  void loan_check_in(LibMat &mat)
  {
    // mat 实际代表的是某个派生类的对象，如Book, RentalBook, Magazines等
    mat.check_in();
    if (mat.is_late()) mat.assess_fine();
    if (mat.waiting_list()) mat.notify_available();
  }
  ```

**多态与动态绑定**  
多态让基类的指针或引用得以十分透明的指向其中任何一个派生类的对象，比如刚才提到的loan_check_in()，其参数mat总是指向LibMat的某个派生对象，但究竟是哪一个呢？答案是只有在程序实际执行时才能确定，而且每次执行时情况都有可能不同：
  - 在传统的非面向对象的编程中，我们写下`mat.check_in()`，编译器在编译时就依据mat所属的类决定究竟执行哪一个check_in()函数，因此我们把这种方式称为 “静态绑定”
  - 但在面向对象的编程方法中，找出实际被调用的究竟是哪一个派生类的check_in()函数，这一解析过程会延迟至运行时才进行，我们称其为 “动态绑定”

总的来讲，继承特性让我们得以定义一群互有关联的类，并共享共通的接口，比如各种图书馆藏，而多态则让我们以一种与类型无关的方式来操作这类对象。我们通过抽象基类的指针或引用类操控其共通接口，而实际执行起来的操作则需要等到运行时，根据指针或引用所指的实际对象的类型进行决定
  - 在此基础上，如果图书馆决定不再借出交互式书籍，我们仅需要将此类从原有的继承体系统移除即可，而loan_check_in()无需进行任何改动
  - 同样，如果图书馆需要为有声书收取费用，我们只需要再添加一个AudioRentalBook类即可，loan_check_in()依然不用更改
  - 因此，抽象基类配合多态，我们可以在不更改现有程序的前提下，加入或移除任何一个派生类

**具体实现**  
接下来我们具体来实现一个三层的类体系，借此来介绍与面向对象编程方法相关的语法元素：
  - 默认情况下，member function 的解析是在编译时静态的进行，若要令其在运行时动态的运行，我们就得在他的声明前加上关键字 `virtual`， 将其声明为一个虚函数
  - 然后在实际执行时，会根据我们传入具体的对象，是抽象基类对象还是某个派生类对象，来调用对应对象的虚函数
  - 当程序定义出一个派生对象时，基类和派生类的构造函数会被依次执行，而当派生对象销毁时，按照派生类和基类的顺序，依次调用析构函数进行销毁; (如果是基类A的派生类B的派生类C, 构造函数调用顺序为A->B->C)
  - 正常我们定义一个类，只需要关键字class加上类名，然后直接大括号；而我们定义一个派生类时，必须要指定它从哪一个已经存在的类中继承而来，因此要在类名后面加上 `: public 基类名称`, 其中public代表继承方式，总共有public, protected, private三种方式可供选择
  - 在派生类中，我们可以对基类中已经定义的函数进行重新定义，实现覆盖
  - 并且，我们还可以将类内成员的访问权限设定为 protected：被声明为protected的所有成员都可以被派生类直接访问，但除派生类之外，其他类都不得访问protected成员
  - 对于Book类所提供的各项数据和操作函数，均可被AudioBook直接使用，仿佛他们本来便是由AudioBook定义似的

### 1.5.2 定义抽象基类
本节我们将采用面向对象的方法，重新设计前一节的num_sequence class。总的思路是先为所有数列类设计出共享的抽象基类，然后继承它：
  - 定义抽象基类的第一个步骤就是找出所有子类共通的操作行为，这些操作行为便是基类的共有接口
  - 第二步便是找出哪些操作行为与类型相关，即哪些操作行为必须根据不同的派生类而有不同的实现方式：这些操作行为应该成为整个类继承体系中的虚函数
    - 注意，static member function 无法被声明为虚函数
  - 第三步便是找出每个操作行为的访问层级：
    - 最普通的public ：所有程序都能访问
    - 其次是protected：派生类可以访问，但不允许一般的程序使用
    - 限制性最强的private: 在基类之外都不需要被用到，即使派生类也无法访问

**注意事项：**  
1. 对于每个虚函数，我们要么明确给出其定义，要么可以将他设定为纯虚函数，主要针对没有实际意义的虚函数，比如gen_elems()对于num_sequence class, 定义为纯虚函数的方式是直接将虚函数赋值为0：
   ```c++
   virtual void gen_elems(int pos) = 0;
   ```
任何类如果声明有一个或多个纯虚函数，那么，由于其接口的不完整性（因为纯虚函数没有函数定义，所以不完整），程序无法为他产生任何对象，因此这种类只能作为派生类的子对象使用，而且前提是这些派生类必须为所有虚函数提供确切的定义。

2. 因为我们的基类并没有声明任何data member, 所以构造函数也没有任何可以进行初始化的non-static data member，我们便不需要定义构造函数
   
3. 但一般情况下，凡是基类定义有一个或多个虚函数，就应该将其析构函数声明为virtual，因此我们需要定义析构函数，具体原因如下：
  - 考虑如下程序片段`num_sequence *ps=Fibonacci(12); delete ps;` ps是基类的指针，但它在使用时实际上是指向派生类Fibonacci的对象，当delete应用于该指针时，析构函数会先应用于指针所指的对象上，即释放该对象
  - 如果是non-virtual函数，它在编译时便会完成解析，但这里我希望根据实际对象的类型选择调用哪一个destructor,即Fibonacci的，而不是num_sequence的，也就是解析应该在运行时进行，因此我们必须将destructor声明为virtual
  - 但并不建议在基类中将destructor声明为pure virtual，虽然它不具有实质意义的实现内容，通常的做法是直接提供空白的定义`inline num_sequence::~num_sequence(){}`


至此我们便完成了抽象基类的定义，但是类本身并不完全，它仅仅是为派生类提供一个接口，每个派生类还必须提供对应的实现细节，以补足基类的不足。

### 1.5.3 定义派生类
派生类由两部分组成：一是基类构成的子对象，由基类的non-static data member组成 (如果有的话)，二是派生类的部分，由派生类的non-static data member 组成。

1. 首先，派生类必须为从基类继承而来的每个纯虚函数提供对应的实现，除此之外，他还必须声明派生类专属的成员
   - 如果我们在派生类中新定义了两个non-virtual function length()和beg_pos()，因为他们并无基类所提供的实体可供覆盖。但也正是因为他们并非基类提供的接口的一员，所以当我们通过基类的在指针或引用进行操作时，就无法访问他们。比如`ps->what_am_i();` 通过虚函数机制，是可以访问Fibonacci::what_am_i()的，但对于 `ps->length()`却无法访问
   - 解决方案之一是重新回到基类，去修改基类的接口：加上两个纯虚函数length()和beg_pos(),这样便会自动造成派生类的beg_pos和length都成为虚函数，而不需要再指定关键字virtual。如果我们加上了virtual，那么修改基类的虚函数就得大费周章：每个派生类都必须对他重新声明

2. 派生类的虚函数必须精确吻合基类中的函数原型，在类外对虚函数进行定义时，不必指明关键字virtual
   - 在具体实现时，elem()可以直接调用继承而来的check_integrity()，就和使用自身成员一样。因为对于继承而来的public成员和protected成员，不论在继承体系中的深度如何，都可以视为派生类的自身成员
   - 基类的public成员在派生类中同样是public，可以开放给派生类的用户使用；基类的protected成员在派生类中同样是protected，因此只能给后续的派生类使用，不能给该派生类的用户使用
   - 我们在elem()调用gen_elems()时，明确指出了我们想调用哪个gen_elems()，使用class scope运算符，跳过虚函数机制，在编译时就完成解析，不再等到运行时解析。因此我们这里已经足够确定我们想使用的那个gen_elems()

3. 当派生类有某个member与其基类的member同名（并未声明为虚函数），便会覆盖基类的那份member，也就是说，在派生类内对该名称的任何使用，都会被解析为该该派生类自身的那份member，而非继承来的那份member
   - 在这种情况下，如果要在派生类内使用继承来的那份member，必须利用class scope运算符加以下限定
   - 但这种方案带来的问题是，因为基类中的那份member function 并未限定为虚函数，因此当我们用基类的指针或引用来调用该成员函数时，解析出来的都是基类的那一份成员函数，并不会考虑指针所指向的实际对象
   - 因此，在基类和派生类中提供同名的non-virtual函数，并不是一个较好的解决办法；针对此问题的一个粗暴的解决方案是在基类中将所有的函数都声明为虚函数

4. 当我们定义派生类时，我们必须决定，究竟是要将基类中的虚函数覆盖掉，还是原封不动的加以继承
   - 如果我们继承了纯虚函数，那么这个派生类也会被视为抽象类，也就无法为其定义任何对象
   - 如果我们决定覆盖基类所提供的虚函数，那么派生类提供的新定义，其函数原型必须**完全符合**基类所声明的函数原型，包括：参数列表、返回类型、常量性，否则就不会实现覆盖！
   - 当我们在派生类中，为了覆盖基类的某个虚函数而进行声明操作时，不一定非要加上关键字virtual，编译器会根据两个函数的原型声明，决定某个函数是否会覆盖其基类中的同名函数


**关于数据成员使用引用还是指针：**
  - 引用永远无法代表空对象，而指针却有可能是空，使用引用，可以省去检查其是否为空的步骤
  - 但数据成员如果是个引用，就必须在构造函数的成员初始化列表中进行初始化，一旦初始化，就再也无法指向另一个对象
  - 而指针却无此限制，我们可以在构造函数内加以初始化，也可以先将它初始化为空，后续再令他指向某个有效的内存地址

### 1.5.4 初始化、析构、复制
当基类拥有实际的data member时，我们就必须为他提供初始化行为，虽然我们可以将初始化留给每个派生类，但这么做会有潜在的危及，最好还是为基类提供构造函数：
   - 因为我们并无法为抽象基类定义任何对象，因此抽象基类扮演的角色是每个派生类对象的子对象，因此我们将基类的构造函数声明为protected而非public
   - 派生类对象的初始化行为，包含调用其基类的构造函数，然后再调用派生类自己的构造函数。这个过程有助于我们了解派生类对象之中其实包含多个子对象：由基类构造函数初始化的基类子对象、以及由派生类构造函数初始化的派生类子对象
   - 对于派生类的构造函数，我们不仅必须为派生类的数据成员进行初始化操作，还需要为其基类的数据成员提供适当的值，因为在调用基类的构造函数时，基类要求我们必须明确我们具体调用哪一个构造函数（根据指定的参数确定）
   - 如果派生类的构造函数未能明确指出调用基类的哪一个构造函数，编译器便会自动调用基类的默认构造函数，这时就需要我们事先为基类提供默认构造函数

如果我们为派生类定义了拷贝构造函数，我们就可以以某个派生类的对象作为另一个派生类对象的初值，如下例所示：
  - rhs代表等号右边的派生类对象，它在成员初始化列表中传给基类的拷贝构造函数
  - 如果基类没有定义拷贝构造函数，问题也不大，因为默认会使用 “成员逐一初始化”的方式进行初始化
  
  ```c++
     Fibonacci::Fibonacci(const Fibonacci &rhs):num_sequence(rhs){}
     // 使用方式
     Fibonacci fib1(10);
     Fibonacci fib2 = fib1;
  ```

拷贝赋值运算符的情况也一样，如果我们将某个派生类的对象赋值给另一个派生类对象，而且该派生类对象拥有明确定义的拷贝赋值运算符，他便会在复制时发生调用：
  ```c++
  Fibonacci& Fibonacci::operator=(const Fibonacci &rhs)
  {
    if (this != &rhs)
        num_sequence::operator=(rhs); // 必须明确调用基类的拷贝赋值运算符
    return *this;
  }

  ```

基类的析构函数会在派生类的析构函数结束之后被自动调用，我们无需在派生类中对它做明确而调用操作。


## 1.6 基于模板编程
模板又称为参数化的类型：
  - 称其为参数化：是因为类型相关的信息可以自模板定义中剥离
  - 称其为类型：是因为每一个类模板或函数模板基本上都随着它所作用或它所内含的类型而有性质上的变化，因此这些类模板或函数模板本身就像是某种类型。模板所接受（或作用于其上的类型），系由模板用户使用时指定

总的来讲，模板定义扮演的乃是处方的角色，能根据用户指定的特定值或特定类型，自动产生一个函数或类。之前我们已经大量的使用了vector,string等类模板，本章我们来手动实现一个二叉树类模板。

二叉树的定义包含两个class:
  - 一个是BinaryTree, 应以存储一个指针，指向根节点
  - 另一个是BTnode, 用来存储节点实值，以及连接至左右两个子节点的链接。而此处节点实值的类型 正是我们希望参数化的部分

### 1.6.1 模板类实现
**Class Template 定义**  
首先，模板类的定义方式和模板函数类型，class关键字前添加 `template<typename elemType>`，用来指明这是一个模板类，并且定义稍微用来指定的参数化类型。
  - 在使用时，通过 `BinaryTree<string> st` 指定二叉树节点类型即可

对于成员函数的定义，模板类内inline函数的定义，其方式和非模板类的方式相同，但在类外，模板类成员函数的定义和普通类成员函数的定义却大不相同：
  - 成员函数的定义始于关键字template和一个参数列表，之后便是函数定义本身，包括class scope运算符
  - 注意，当class scope运算符出现之后，其后所有的东西都被视为class定义范围内，因此对于构造函数析构函数等，我们再调用::BinaryTree(),就不用限定参数列表

**Template 类型参数处理**  
处理一个 模板类型参数 要比处理 明确类型的参数 复杂一些：
  - 如果我们要为函数声明一个明确的int参数，我们通常以传值的方式进行参数传递 `bool find(int val)`;
  - 如果声明 Matrix class为函数的参数，我们通常以传址的方式进行参数传递 `bool find(Matrix& val)`; 避免因Matrix对象的复制而造成的不必要的开销
  - 但当我们要处理template类型参数时，我们却无法得知用户实际要用的类型是否为语言内置类型，还是class类型。为了提高效率，我们把所有的template类型参数视为 class类型来处理，把他声明为 const reference

在构造函数的定义中，我们通常在成员初始化列表内为每个类型参数进行初始化操作（特别是依靠模板参数类型定义的对象），而不是全部在构造函数函数体内初始化，这样可以保证效率最佳：
  - 因为构造函数体内 对 _val 的赋值操作可以分解为两个步骤：(1). 函数体执行前，Matrix的 默认构造函数会先作用于_val身上; (2) 函数体内 copy assignment operator将val复制给_val
  - 而如果我们采用成员初始化列表进行初始化，只需要第二个步骤就可以直接完成

**reference to pointer 参数传递**
之前我们要么传递指针`*`,要么传递引用`&`，但还有传指针引用的方式`*&`:
  - 以指针传递，我们能够更改的是该指针所指之物，而不是指针本身
  - 为了改变指针本身，我们必须再加一层间接性，将参数声明为对指针的引用，这样我们不仅可以改变指针本身，也可以改变由此指针指向的对象

**使用函数模板重载output运算符**  
正常我们重载output运算符时，需要明确指明每个class的名称，但如果针对模板类，我们该如何重载输出运算符呢？
```c++
template <typename elemType>
inline ostream& operator<<(ostream &os, const BinaryTree<elemType> &bt)
{
  os << "Tree: "<<endl;
  bt.print(os);
  return os;
}
```

**常量表达式与默认参数值**  
模板参数并不是非得某种类型不可，我们也可以用常量表达式作为模板的参数。比如对于先前的数列继承体系，我们可以重新以类模板设计，将“对象所含的元素个数”进行参数化：
   ```c++
   // 基类
   template<int len>
   class num_sequence{
   public:
     num_sequence(int beg_pos=1);
     // ...
   };
   // 派生类
   template <int len>
   class Fibonacci::public num_sequence<len>{
   public:
     Fibonacci(int beg_pos=1) : num_sequence<len>(beg_pos){}
     // ...
   };
   // 实例化对象
   Fibonacci<16> fib1;
   ```

## 7. 异常处理
### 7.1 抛出异常
异常处理机制有两个主要成分：异常的鉴定与发出，以及异常的处理方式
  - 通常，不论是member function还是non-member function，都有可能产生异常以及处理异常。异常出现以后，正常程序的执行便被暂停(suspended)
  - 与此同时，异常处理机制开始搜索程序中有能力处理这一异常的地点，异常处理完成之后，程序便会继续（resume）,从异常点接着执行下去

C++ 通过throw表达式产生异常：`throw iterator_overflow(_index, _max_elems);`,那么何谓抛出一个异常？
  - 异常是某种对象，最简单的异常对象可以是普通的整数对象或字符串对象：`throw 42; throw "Error!";`
  - 但大部分时候，被抛出的异常都属于特定的异常类（也许形成一个继承体系），比如刚刚的iterator_overflow class

### 7.2 捕获异常
我们可以用单条或一连串的catch子句来捕获被抛出的异常对象：catch 子句由三部分组成：关键字 catch、小括号内的一个类型或对象、大括号内的一组语句（用于处理异常）
  - 异常对象的类型会逐一的被拿来和每个catch子句比对，如果类型符合，那么该catch子句的内容便会被执行
  - 在通过所有catch子句之后，由正常的程序重新接手
  - 有时候我们可能无法完成异常的完整处理，在记录信息之外，我们或许需要重新抛出异常，以寻求其他catch子句的协助，做进一步的处理。重新抛出时，只需要写下关键字`throw`即可，不再需要指明异常对象，它会将之前捕获的异常对象再一次抛出，并由另一个类型吻合的catch子句接手处理
  ```c++
  bool some_function()
  {
    bool statue = true;
    // ...
    catch (int erridx)
    {
      log_message(err_msg[erridx]);
      status = false;
    }
    catch (const char* str)
    {
      log_message(str);
      status = false;
    }
    // ..
    return status;
  }
  ```
如果我们想要捕获任何类型的异常，可以使用一网打尽的方式，catch all，在异常声明部分指定省略号(...)即可：
```c++
catch(...)
{
  log_message("xxx");
}
```

### 7.3 提炼异常
catch子句应该和try块相应而生：
  - try块是以关键字try作为开始，然后是大括号内的一连串程序语句
  - catch子句放在try块的末尾，这表示如果try块内有任何异常发生额，便由接下来的catch子句加以处理

当函数抛出异常时，异常处理机制开始查看：异常由何处抛出？并判断是否位于try块内？
  - 如果是，就检验相应的catch子句，看他是否具备处理此异常的能力，如果有，这个异常便被处理，而程序也就正常的执行下去
  - 如果不在try语句块内，会根据函数调用顺序不断的向上层查找，如果一直回到了main()还是找不到合适的catch子句，便会调用标准库提供的terminate()，其默认行为是中断整个程序的执行。因为c++规定，每个异常都应该被处理

### 7.4 局部资源管理
按照正常的处理逻辑，我们分配相关资源，在进行某些处理操作后，会希望在函数结束之前释放之前分配的资源。我们可能会这么写：
  ```c++
  extern Mutex m;
  void f()
  { 
    // 请求资源
    int *p = new int;
    m.acquire();

    process(p);
    // 释放资源
    m.release();
    delete p;
  }
  ```
但上述写法面临的问题是我们无法保证函数在最开始分配的资源最终一定会被释放掉。如果process()本身或process()内调用的函数抛出异常，那么process()调用操作之后的两条用于释放资源的语句便不会被执行。

所谓资源管理：是指对对象而言，初始化操作发生在构造函数之内，因此资源的请求亦应该在构造函数内完成，而资源的释放则应该在析构函数内完成：
  ```c++
  #include<memory>
  void f()
  {
    auto_ptr<int> p(new int);
    MutexLock m1(m);
    process(p);
    // p和m1的析构函数会在此处悄悄的调用
  }
  ```
  - p 和 m1都是局部对象 ，如果process执行无误，那么相应的析构函数便会在函数结束前自动作用于p和m1身上
  - 如果在process()执行过程中有任何异常被抛出，在异常处理机制终结某个函数之前，c++保证函数中所有局部对象的析构函数都会被调用
  - auto_ptr是标准库提供的类模板，他会自动删除通过new表达式分配的对象

auto_ptr将提领运算符和arrow运算符予以重载，这使得我们可以像使用一般指针一样的使用auto_ptr对象：
```c++
  auto_ptr<string> aps(new string("vermeer"));
  string *ps = new string("vermeer");

  if ((aps->size()==ps->size()) && (*aps==*ps)) ...
```

