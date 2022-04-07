[原文链接]<https://www.jianshu.com/p/de9c98bba332>

#基本符号：* - + >
基本上所有的markdown标记都是基于这四个符号或组合，需要注意的是，如果以基本符号开头的标记，注意基本符号后有一个用于分割标记符和内容的空格。


#标题（从大到小取决于#号的数量）
# 一级标题
## 二级标题
### 三级标题
#### 四级标题
##### 五级标题
###### 六级标题


#引用
这是一个引用样式：> 引用内容


#段落
段落以 回车 作为标记。


#分隔符
连续输入三个以上的 --- 添加横线分隔符，如下：
------


＃列表
使用 * - + 中的任何一个符号加空格就可以创建无序列表，但如我这样的完美主义者可以进一步使用+和-来表现层次关系。
* 这是一个无序列表
-  这是一个无序列表
+ 这是一个父无序列表
  - 这是一个子无序列表

##使用 数字+点+空格+内容 创建有序列表
1. 这是一个有序列表
2. 这是一个有序列表
  1. 这是一个嵌套有序列表
  2. 这是一个嵌套有序列表
列表可以嵌套，使用时在嵌套列表前按 tab 或 空格 来缩进。如您所见，这篇文章的排版就使用了嵌套列表的样式。


＃链接
用markdown写下你的第一个md文档 的文章链接是这样构成的
[用markdown写下你的第一个md文档](http://www.jianshu.com/p/de9c98bba332) 
也可以直接用尖括号包含网址的方式<http://www.jianshu.com>来直接构造一个可点击的链接


图片
像构造一个链接一样，只需要在前面加！
![图片名称](图片地址)
简书
代码段
markdown常用来编写代码文档，因此文档中引入代码必不可少。

使用
```
代码段
```
这样的方式来构建一个代码段
` 符号在左上角esc键下方，请在半角状态输入
print("这是一个代码段");
使用 `符号包裹代码构建一个代码块
console.log('这是一个代码块');
一些markdown工具支持更简单的按tab缩进方式

＃字体样式
*倾斜*
**加粗**
***倾斜并加粗***
~~文字删除线~~

表格
使用- |符号把内容分割为你认为合适的表格样式就好。
使用:符号标识对齐。

表头1|表头2|表头3
:----|:-----:|-----:
左对齐|居中对齐|右对齐
表头1	表头2	表头3
左对齐	居中对齐	右对齐
保存
最后将markdown编写的文档存为 .md 格式，就可以用对应的工具查看效果和编辑了。

添加图片

```
<center>
    <img style="border-radius: 0.5125em;
    box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);"
    src="这里输入图片地址">
    <br>
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;
    display: inline-block;
    color: #999;
    padding: 2px;">这里输入标题</div>
</center>
```

<center> <font size=7> 大字并居中 </font> </center>  

<font color=gray size=72>大字+灰色</font>



## 图文混排

图片居于文字左边

将图片的链接放置在段落文本的正上方，中间不加换行。

```text
![](https://blog.ikke.moe/img/miui7.png)
这里是段落内容，注意两行中间并没有任何的换行！
```

图片居于文字右边

将图片的链接放置在段落文本的正下方，中间不加换行。

```text
这里是段落内容，注意两行中间并没有任何的换行！
![](https://blog.ikke.moe/img/miui7.png)
```

图片与文字无关

只需要在文字与图片之间加上换行即可。

```text
![](https://blog.ikke.moe/img/miui7.png)

这里是段落内容，注意两行中间有换行！
```

图片并排

两张图片的链接并列，中间没有换行。

```text
![](https://blog.ikke.moe/img/miui7.png)
![](https://blog.ikke.moe/img/miui7.png)
```


如果你用Typora，可以用<img> 标签更改，支持设定宽度、高度。<img src="https://www.google.com/doodles/kamma-rahbeks-241st-birthday" width="200px" />
 <img src="https://www.google.com/doodles/kamma-rahbeks-241st-birthday" style="height:200px" />
也可以指定缩小比例：<img src="https://www.google.com/doodles/kamma-rahbeks-241st-birthday" style="zoom:50%" />
详细可以看官方说明：Resize Images推荐这个markdown app，非常好用，支持Mac、windows



typora 文档

https://www.jianshu.com/p/b30955885e6d



Markdown to Slides

https://www.the5fire.com/slide/markdown-to-slide/#1

https://blog.csdn.net/yyw794/article/details/73697810



VScode 

https://juejin.im/post/5c45b92751882525487c5c66

https://zhuanlan.zhihu.com/p/56699805

https://shd101wyy.github.io/markdown-preview-enhanced/#/zh-cn/usages?id=vs-code
