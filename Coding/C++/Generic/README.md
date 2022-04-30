<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-04-18 10:25:45
 * @LastEditTime: 2022-04-25 15:31:44
-->
- [3 泛型编程](#3-泛型编程)
  - [3.1 泛型程序基本概念](#31-泛型程序基本概念)
  - [3.2 容器](#32-容器)
  - [3.3 泛型算法](#33-泛型算法)
    - [3.3.1 泛型指针](#331-泛型指针)
    - [3.3.2 常用泛型算法](#332-常用泛型算法)
    - [3.3.3 设计泛型算法](#333-设计泛型算法)
  - [3.4 典型迭代器](#34-典型迭代器)

## 3 泛型编程
### 3.1 泛型程序基本概念
泛型程序设计是程序设计语言的一种风格或范式。泛型允许程序员在*强类型设计语言*中编写代码时使用一些以后才指定的类型，在实例化时作为参数指明这些类型。各种程序设计语言和其编译器、运行环境对泛型的支持均不一样，*C++中的泛型称之为模板*

在上一章节中便介绍了模板的概念，模板是c++程序设计语言中的一个重要特征，而标准模板库正是基于此特征集成的大型软件库，其大量影响了c++标准程序库，但并非是其中的一部分，使得c++编程语言在有了同java一样强大的类库的同时，保有了更大的可扩展性。

**C++标准模板库**  
C++ STL（标准模板库）是一套功能强大的 C++ 模板类，提供了通用的模板类和函数，这些模板类和函数可以实现多种流行和常用的算法和数据结构，如向量、链表、队列、栈。C++ 标准模板库的核心包括以下三个组件：
  - 容器（Containers）：容器是用来管理某一类对象的集合。C++ 提供了各种不同类型的容器，比如 deque、list、vector、map 等。
  - 算法（Algorithms）：算法作用于容器。它们提供了执行各种操作的方式，包括对容器内容执行初始化、排序、搜索和转换等操作。
  - 迭代器（iterators）：迭代器用于遍历对象集合的元素。这些集合可能是容器，也可能是容器的子集。
  
这三个组件都带有丰富的预定义函数，帮助我们通过简单的方式处理复杂的任务。通过上述概念，STL将“在数据上执行的操作” 与 “要执行操作的数据” 分开。详见[STL_Collections](./src/STL_Collections.h)

**[C++ 标准库](https://www.apiref.com/cpp-zh/cpp/header.html)**  
C++ 标准库可以分为两部分：
  - 标准函数库： 这个库是由通用的、独立的、不属于任何类的函数组成的。函数库继承自 C 语言。包括输入/输出 I/O，字符串和字符处理，数学，时间、日期和本地化，动态分配，其他，宽字符函数等
  - 面向对象类库： 这个库是类及其相关函数的集合。C++ 标准库包含了所有的 C 标准库，为了支持类型安全，做了一定的添加和修改。包括标准的 C++ I/O 类，String 类，数值类，STL 容器类，STL 算法，STL 函数对象，STL 迭代器，STL 分配器，本地化库，异常处理类，杂项支持库等


### 3.2 容器
容器从数据组织方式上可以分为两类：
  - 顺序性容器：依次维护第一个、第二个 ...直到最后一个元素，我们在顺序性容器上主要进行所谓的迭代操作，主要有：`vector, list, forward_list, deque, array`
  - 关联容器：用于快速查找容器中的元素值，主要有：`set, multiset, map, multimap, unordered_set, unordered_multiset, unordered_map, unordered_multimap`

其他类型容器：`bitset, valarray`

**顺序性容器**    
顺序性容器用来维护一组排列有序、类型相同的元素，其典型代表是vector，list以及deque
  - vector用一块连续内存来存放元素，vector内的每个元素都被存储在距离起始点的固定偏移位置上，因此对随机访问效率很高，但插入和删除由于需要移动其他元素，效率较低
  - list以双向链接而非连续内存来存储内容，每个元素都包含三个字段：value, back和front指针，在任意位置插入删除效率较高，但随机访问需要遍历，效率较低
  - deque(双端队列)其行为和vector颇为相似，都是以连续内存存储元素，但和vector不同的是，该队列的每一端都可以添加元素或删除元素，对于前后端元素的插入和删除操作，效率更高 (标准库的queue便是以deque实现)
  

**关联性容器**  
关联性容器主要包括map和set:
  - map是一对对的key-value组合，key用于查找，value用来表示我们要存储或取出的数据；注意任何一个key值在map内最多只有一份
  - set仅含有key，通过对key查询，判断该值是否存在于容器中


**容器类操作函数**  
下列为所有容器类（以及string类）共通的操作函数：
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


### 3.3 泛型算法
为更好的理解泛型算法的实现机理和使用方法，首先需要明确泛型指针的概念，然后给出常用常用的泛型算法，最后介绍如何设计泛型算法。

#### 3.3.1 泛型指针
**泛型指针的需求动机**  
1. 首先假定当前任务是需要实现一个find函数，给定一个存储整数的vector以及一个整数值，如果此值存在，则返回一个指向该值的指针，否则返回0，则很容易通过元素遍历比较直接写出。

2. 接下来如果又要求find函数不仅可以处理整数，也可以处理浮点数等其他任何类型，该怎么做呢？显然，结合之前的知识，可以使用函数模板进行实现，前提只需要保证该类型定义有equality(相等)运算符即可。

3. 更进一步，如果再要求不仅可以处理vector,也能处理array呢？当然可以使用函数重载进行分别定义，但可以仅定义一份函数吗？首先从两份函数的不同之处出发，二者的区别就在于传入的参数不同，其内部处理逻辑都是一致的，如何将容器类型进一步剥离，使得传入同样的参数呢？解决方案就是使用指针作为参数，传入vector或array的首地址，然后通过该指针不断的在内存中迭代寻找剩余元素，这样就实现了操作对象和具体容器类型的剥离。
   - 注意在使用指针作为参数时传入容器首地址时，很容易忽略例外情况，那就是vector为空时的情况，这时如果再传入其首地址，就会导致运行错误。（array可以直接传入首地址）
   - 因此在传入前需要执行非空检查`if (!vec.empty()`。
    
4. 为了进一步提升执行指针非空检查的通用性，进一步将其进行封装
    ```c++
     template <typename elemType>
     inline elemType* begin(const vector<elemType> vec) {return vec.empty()? 0 : &vec[0];}
    ```
    同样也可以封装一个end()函数，用来返回vector最后一个元素的下一个地址。最后便得到了一个可以应用于任意vector的find函数：`find(begin(vec), end(vec), search_value);`

5. 但由于begin(), end()的限制，当前find只能处理array和vector，如何进一步泛化到能够处理标准库中所有的容器类呢？比如list
   - list也是一个容器，不同的是，list的元素不是存在一段地址连续的内存空间中，而是以一组指针相互链接(linked)，分别通过forward和backward指针分别指向下一个和上一个元素
   - 因此，指针的算数运算并不适用于list，因此之前我们假设元素都存在连续内存空间中，我们便可以根据当前指针，加上元素大小，指向下一个元素

6. 解决方案就是在底层指针的行为之上再提供一层抽象，取代程序原本的“指针直接操作”的方式，把底层指针的处理通通放在此抽象层中，这样用户就无需直接面对指针操作！这就是泛型指针iterator.

7. 具体来讲，需要定义一组迭代对象，其提供和内置运算符(++, *, ==, !=)相同的运算符，这样就可以使用和指针相同的语法来进行迭代检索
   - 比如first和last都是list的iterator，希望它能够像指针一样`while (first!=last){cout << *first; ++first;}`
   - 但实际上它的提领(*)运算符，不等(!=)运算符，自增(++)运算符都是由iterator class内相关的inline函数提供的

8. 虽然内部实现和指针的算数运算不同，但外在表现都是相同的，这就是“底层指针行为之上的抽象”： 
   - 如果他是一个list的iterator，递增函数会沿着list的指针前进到下一个元素；
   - 如果是一个vector的iterator，递增函数就是根据当前地址加上元素大小到达下一个元素；
   - 外在表现上，我们的操作都是和之前操作指针一样直接使用 `++first`!


**泛型指针的基本概念**  
在后续章节中，会讲解如何实现这个iterator class，这里先关注如何定义并使用标准容器的iterator：
   - 每个标准容器都提供一个begin()操作函数，可以返回一个指向第一个元素的iterator，以及一个名为end()的操作函数，指向最后一个元素的下一个位置

对于iterator的定义我们需要考虑两个方面：
   - (1). 首先这份定义应该提供迭代对象(某个容器)的类型，用来决定如何访问下一元素; 
   - (2). 其次也要指明iterator所指的元素类型，决定了iterator提领操作的返回值

因此iterator定义的标准语法为`vector<string>::iterator iter = vec.begin()`
  - 表示iter被定义为一个iterator，指向一个vector，其内部元素类型为string,初值指向第一个元素
    - 双冒号表示此iterator是位于string vector定义内的嵌套类型

明确了定义和获取方式，后续使用比如赋值、比较、递增、提领等操作和指针并无二致
  - 比如要通过iter调用底部string元素所提供的操作，可以使用arrow运算符：`iter->size()`
  

**其他注意事项**  
至此已经让find()有了极大地通用性，可以不用关注元素类型，也不用关注容器类型。但还有一个小细节是find在实现过程中用到了底部元素的equality运算符，如果底部元素是我们自定义的其他类型，并没有提供这个运算符，或者用户希望赋予equality 运算符不同的意义，此find元素又不行了：
  - 解决方案之一是传入一个函数指针，取代原本固定使用的equality 运算符
  - 或者运用所谓的 function object (一种特殊的class，第四章会进行介绍)
  - 因此我们下一阶段的目标便是将find变成真正的泛型算法（如标准库中的find_if(),能够介绍函数指针或function object，取代底部元素的equality运算符）


#### 3.3.2 常用泛型算法
泛型算法提供了许多可用于容器类即数组类型上的操作，这些算法之所以被称为泛型，是因为它们和要操作的元素类型无关，比如元素类型无论是int,double,还是string,都不影响算法的实现，同样也和容器类彼此独立（不论容器是vector、list或array）
  - 前一章节已经介绍过，要达到“与操作对象的类型相互独立”的目的，可以使用 函数模板 技术
  - 进一步要实现“与容器无关”，那就不要直接在容器身上进行操作，通过借由一对iterator(first 和 last),表示我们要进行迭代的元素范围：
    - `first==last`: 只作用于first所指元素
    - `first!=last`: 首先作用于first所指元素，然后将first递增，指向下一个位置，然后比较二者是否相等，如此持续进行，直到first等于last为止
  
**常用泛型算法**  
本节介绍一些典型的泛型算法的应用，欲使用泛型算法，首先得包含对应的头文件：`#include<algorithm>`，其中常用的泛型函数包括：
  - `find()`: 用于搜索无序集合中是否存在某值，搜索范围由iterator [first, last) 标出，如果找到目标，返回一个iterator指向该值，否则指向last
  - `binary_search()`: 用于有序集合的搜索，找到返回true,否则false
  - `count()`: 返回数值相符的元素数目
  - `search()`: 对比某个容器内是否存在某个子序列，找到返回iteartor指向子序列起始处，否则指向末尾
  - `max_element()`: 返回范围内的最大值
  - `copy()`: 复制容器，两个iterator参数标识出复制范围，第三个iterator指向复制行为的目的地的第一个元素

**典型泛型算法**  
C++标准库中总共有超过60个泛型算法，一些典型的为
  - 搜索算法 (search algorithm): `find(), count(), adjacent_find(), find_if(), count_if(), binary_search(), find_first_of()`
  - 排序(sort)及次序整理(ordering)算法: `sort(), merge(), partial_sort(), partition(), random_shuffle(), reverse(), ratate()`
  - 复制(copy)、删除(delete)、替换(substitution)算法: ` copy(), remove(), remove_if(), replace(), replace_if(), swap(), unique() `
  - 关系(relational)算法: `equal(), include(), mismatch()`
  - 生成(generation)与质变(mutation)算法:` fill(), for_each(), generate(), transform() `
  - 数值(numeric)算法: ` accmulate(), adjacent_difference(), partial_sum(), inner_product() `
  - 集合(set)算法: ` set_union(), set_difference() `


#### 3.3.3 设计泛型算法
考虑一个新任务，给定一个整数vector，返回一个新的vector，仅包含原vector中小于10的所有数值。

1. 通过遍历比较，很容易便可以写出一个普通的filter函数。
  
2. 接下来增加函数的弹性，希望允许用户指定不同比较操作，如大于、小于，那么如何才能将 “比较操作” 参数化呢？可以用函数调用来取代less-than运算符：加入第三个参数pred,用它来指定一个函数指针，其参数列表有两个整数，返回值为bool。

3. 在继续优化filter()之前先来了解 function object 以及 function object adapter的概念。

**Function Object**  
所谓function object，是某种class的实例对象，这类class对function call运算符`()`做了重载操作，如此一来，可使function object被当做一般函数来使用（仿函数）。标准库事先定义了一组function object, 分为算数运算、关系运算、逻辑运算三大类：
  - 六个算术运算：`plus<type>()`, `minus<type>()`, `negate<type>()`, `multiplies<type>()`, `divides<type>()`, `modulus<type>()`
  - 六个关系运算：`less<type>()`, `less_equal<type>()`, `greater<type>()`, `greater_equal<type>()`, `equal_to<type>()`, `not_equal_to<type>()`
  - 三个逻辑运算：`logical_and<type>()`, `logical_or<type>()`, `logical_not<type>()`

function object 实现了我们原本用独立函数进行定义的事物，这样做的原因主要是为了效率。利用call运算符，将function object当做普通函数调用，可以消除 “通过函数指针来调用函数”时需要付出的额外的代价

**Function Object Adapter**  
一般来讲，function object 期望外界传入两个值，有时我们希望他是一个一元运算符，比如每个元素和指定元素进行比较，这就需要我们把其第二个参数绑定至用户指定的数值，这时便需要标准库所提供的adapter：
  - 标准库提供了两个binder adapter: `bind1st`会将指定值绑定至第一操作数；`bind2nd`会将指定值绑定至第二操作数
    - 如 `bind2nd(less<int>, val)`: 将val绑定于less<int>的第二个参数上，于是，less<int>会将每个元素拿来和val比较
  - 另一种adapter是所谓的negator，他会对function object的真伪值取反
    - not1 可对unary function object的真伪值取反：比如找出大于等于10的元素`not1(bind2nd(less<int>,10))`
    - not2 可对binary function object的真伪值取反

funtion object adapter 会对function object进行修改操作：所谓binder adapter (绑定适配器)会将function object的参数绑定至某特定值，使binary function object 转化为 unary function object


4. 重新回到之前的例子，用泛型算法find_if()来代替实现过程中的for循环，将find_if反复作用于数列，找出符合条件的每一个元素，所谓“条件”则由我们刚才提到的function object确定。

5. 最后，采用上节介绍的套路，可以进一步消除filter 与 vector元素类型、vector容器类型之间的依赖关系：
  - 使用函数模板来消除元素间的依赖性
  - 传入一对iterator[first, last)来消除容器类型的依赖性
  - 额外传入一个ieterator，指向结果容器，用于复制筛选出的元素


### 3.4 典型迭代器
迭代器是泛化的指针，通过使用迭代器，开发者可以操作数据结构而无需关心其内部的实现。根据迭代器操作方式的不同，迭代器分为五种：
  - 输入迭代器
  - 输出迭代器
  - 前向迭代器
  - 双向迭代器
  - 随机访问迭代器

**Iterator Inserter**  
先前我们通过两个iterator进行值拷贝，`*at++=*first++`,这种情况下，目的端的容器必须足够大，用于存储被赋值进来的每个元素，但filter()无法知道每次对at递增之后，at是否仍然指向一个有效的容器位置。为了解决整个问题，标准库提供了三个所谓的insertion adapter，这些adapter让我们得以避免使用容器的assignment运算符：
  - back_inserter() 会以容器的push_back()函数取代assignment运算符：`unique_copy(ivec.begin(), ivec.end(), back_inserter(res_vec));`
  - inserter() 会以容器的insert()函数取代assignment运算符，inserter()接受两个参数，一个是容器，另一个是iterator，指向容器的插入操作起点：` unique_copy(ivec.begin(), ivec.end(), inserter(res_vec, res_vec.end() )); `
  - front_inserter() 会以容器的push_front()函数取代assignment运算符，这个inserter只适用于list和deque: ` copy(ilist.begin(), ilist.end(), front_inserter(res_list)); `
  - 注意这些adapter并不能用于array上，array并不支持元素插入操作

6. 回到之前的filter的例子，我们调用filter时不再传入目标容器的iterator，而是采用vector的back_inserter，这样目标容器就可以是一个空的容器，然后不断在容器末端执行插入：
   - `filter(ivec.begin(), ivec.end(), back_inserter(ivec2), value, greater<int>());`

**iostream Iterator**  
标准库定义有供输入输出使用的iostream iterator类，称为 istream_iterator 和 ostream_iterator，分别支持单一类型的元素读取和写入
  - 首先为了使用这两个类，我们要包含其头文件 `#include<iterator>`
  - 其次，就像所有的iterator一样，我们需要一对first和last iterator，用来标识元素范围
  - 对于first，我们定义为 "绑定至标准输入设备" 的 istream_iterator：`istream_iterator<string> is(cin)`
  - 对于last， 我们希望它表示 "要读取的最后一个元素的下一位置"，对标准输入设备而言，就是 end-of-file, 我们只需要在定义时不为他指定istream对象即可： `istream_iterator<string> eof`
  - 对于ostream_iterator,我们需要用它表示字符串元素的输出位置，我们用ostream_iterator绑定标准输出设备：`ostream_iterator<string> os(cout, " ");`,第二个从参数表示输出各元素之间的分隔符

  
