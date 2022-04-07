# Markdown to slides

<https://www.npmjs.com/package/markdown-to-slides>

> A command line interface to convert markdown documents to an HTML slideshow

## Firstly, a markdown to slides converter, using remark

Basically, Markdown to slides uses [remark](https://github.com/gnab/remark) to convert your markdown documents to HTML slideshows, i.e. that can be viewed in your favorite modern Web browser.

The **produced HTML file is standalone** and can be copied, send by mail, ...

If you want to have an idea of what remark does, take a look at the [demo page](http://remarkjs.com/#1).

The **presenter mode** is a great feature, have you tried to press 'P' on the demo page ?

Moreover, writing markdown documents for slideshows is easy:

```markdown
#Main title
 
---
## First chapter
 
---
### Chapter 1.1
 
Some content
 
---
### Chapter 1.2
 
Some content
 
---
## And so on...
```

Each slide must be separated with '---'. Take a look at the [remark wiki](https://github.com/gnab/remark/wiki) for further details.

## The document mode: convert markdown documents not aimed to slides

Sometimes, when you write a document with markdown, you may want to transform it as slides, even if it was not the aim.

An obvious document structure is:

```
# Main document title
 
## First chapter
 
### Chapter 1.1
 
Some content
 
### Chapter 1.2
 
Some content
 
## Second chapter
 
This chapter does not have sub sections
 
## And so on...
```

Usually, remark needs slides to be separated with `---`.

**This is where the document mode comes: enable the `--document-mode flag` (or `-d`), and slides are splitted automatically, based on the heading structure.**

With the previous example:

- the document title (`#`) is decorated as the main title
- chapter titles of the second level (`##`) without direct content (here: the 'First chapter') are on their own slides
- sub chapter titles (`###`) have their own slide.

Headings with level 4 (`####`) or above can be splitted on new slides thanks to the `--level`parameter.

This is not as extensible as the remark syntax, with slides properties (e.g. `class: middle` or `name:`), but it prevent from thinking to the slideshow when writing a document.

## Installation

First, you should follow this link https://www.kancloud.cn/shellway/npm-doc/199984 install node, npm and setup the working directory (2&3).

```
npm install markdown-to-slides -g
```

Then you will be able to generate slides from your markdown files from command line.

## Usage

### Basic usage

```
$ markdown-to-slides my-file.md -o slideshow.html
```

Write `my-file.md`, correctly formated to be converted as slides, as `slideshow.html`.

```
$ markdown-to-slides -d my-file.md -o slideshow.html
```

The same, enabling the document mode.

### Options

```
--title, -t          Generated page title
--style, -s          Path to custom stylesheet
--script, -j         Path to custom javascript
--template, -l       Path to custom mustache template
--help, -h           This screen
--output-file, -o    Path to output file (stdout if not specified)
--document-mode, -d  Generate slides from a document without slide separators (---) or annotations
--watch, -w          Watch mode
--level              Heading level to use as new slides (for example 3 is ###)
--include-remark -i  Include Remark sources (around 850kB) into the generated document
```





## Notes

### Inspiration

markdown-to-slides is very inspired from [markdown-html](https://github.com/fragphace/markdown-html/), it is a great tool to convert markdown to HTML.

### Related project

[Vegetables](http://partageit.github.io/vegetables/) is a static Web site generator, turning Markdown documents into HTML pages.

It can produce many versions of the same document, especially a slideshow version, using remark.

In other words, it is like markdown-to-slides, but for many documents at once, with a serve mode, a menu to navigate between documents and auto reload when a document is updated.

## Todo

- validate that md file exists
- split big slides
- handle foot notes (from additional file?)

## Changelog

### Version 1.0.5

- `index.js` changed to `LF` instead of `CRLF` to prevent from `env: node\r: No such file or directory` on mac os X (#12 and #13).

### Version 1.0.4

- Remark source protocol changed from HTTP to HTTPS thanks to [Kotaro Yoshimatsu](https://github.com/ktrysmt)

### Version 1.0.3

- Include remark script statically in compiled HTML. Thank you [Matt Kantor](https://github.com/mkantor)
- As the generated file grows (around takes 850kB) when including the remark script, this enhancement must be enabled with the `--include-remark` parameter

### Version 1.0.2

- It is possible to choose the heading level (default was 3, i.e. `###`) to split slides (#2)
- write() deprecation message removed, migrating mustache renderer from mu2 to mustache (#3)

### Version 1.0.1

- One line code CSS enhanced
- marked-to-md used: tables and list are now correctly handled

## [License](https://github.com/partageit/markdown-to-slides/blob/HEAD/LICENSE)









1. remark 是基于 Markdown 的幻灯片框架，这听起来没什么新奇的，这世界上已经处处 Markdown 了，但它又做对了几件至关重要的事情：
   - 它有元素对齐的语法！这特么实在太重要了。无数个日夜我都想居中一些元素，可是只能写丑陋的 HTML 语法 `<div style="text-align: center;"> </div>`。在 Markdown 中混入这些东西会严重触发我的代码洁癖，导致我时时想掀桌。
   - 不仅是对齐，它支持自定义任何元素的 CSS 类，这样让一些 Markdown 本来不支持的元素也可以通过 CSS 魔法实现了，比如脚注。它敞开了 CSS 大门，也就让幻灯片的任意元素有无穷的可定制性，前提是你要懂 CSS。通过 `.foo[]` 的 Markdown 语法对应 CSS 类名 `foo` 这件事打通了 Markdown 的任督二脉。Markdown 最大的问题就是没有语法定制单个元素的特殊格式，它只能通过全局 CSS 规则定义所有同类元素的样式。虽然我反对花里胡哨的格式（我尤其反对对单个词句着色），但有时候实在是希望能自定义一下。传统 Markdown 关死了这扇门，remark 以很简单的方式把它打开了。
2. 除了对齐单个的元素，它还支持每一张片子的全局对齐方式，比如片子所有内容居中、底端对齐。更重要的是，每一张片子都可以有自己的 CSS 类，换句话说，只要懂 CSS，你想上天就可以上天。
3. 一张片子里的内容可以以任意方式分割（语法是两短横线），分割过的片子在播放的时候会按次序一段段显示在屏幕上。比如你的爆笑 GIF 动图或者什么梗可以先藏在下面，等你讲完前两点之后再显示出来。这个“任意分割”又是一大亮点，因为传统 HTML5 框架往往只能做到对一个列表里的列表项一项一项依次出来，而 remark 可以非常放肆，你可以先一口气显示前两点，再显示第三点，再显示第四五六点。你想怎么安排你的片子内容怎么出场就怎么安排。
4. 每张幻灯片底下可以写注释。要解释这个注释有什么用，先得说一下 remark 的最强忍术的结印手势：播放幻灯片时，可以按一些快捷键，比如 `?` 或 `h` 显示帮助、`b` 让屏幕变黑、`m` 把一张片子上下左右颠倒（这特么简直太好玩了）、`c` 克隆一份当前窗口的片子到新窗口、`p` 进入演讲者模式。所谓演讲者模式，就是左右分栏格式，左栏上下分别显示当前片子和下一页片子（即：你讲当前页的时候可以预览下一页），右栏显示当前页上的注释，这些注释也可以用 Markdown 语法写，用来提醒自己一些幻灯片上没有展示给观众看的内容（比如冷笑话），这个模式只是给演讲者自己看的；前面我们说了克隆，实际演讲中，你可以克隆一份片子，以正常模式拖到投影仪上给观众看，而自己的电脑上则用演讲者模式。这样麻麻再也不怕我作报告的时候忘了讲冷笑话啦。这么说有些抽象，自己[戳开一个例子](https://slides.yihui.name/xaringan/)体验一下就知道了。
5. 一张片子可以设置背景图片！我为什么喜欢我的第一份 HTML5 幻灯片？一个最重要的原因就是图片可以占满全屏。这个功能在我用过的其它框架中几乎都没有，而我又是坚定的[图片党](https://slides.yihui.name/2017-rstudio-conf-rmarkdown-Yihui-Xie.html)（没有师姐那样的气场，只好靠大图来硬撑了）。
   - 之前有好事者在推特上给我提了一个功能请求，就是添加一个参数以便在随机的一页片子上显示 [Karl Broman 的胡子照](https://github.com/yihui/xaringan/issues/1)。这张照片背后的故事略有点长，这里就不展开了。总之呢，我觉得这个很好玩，某种程度上 Karl 就是我眼中的蒙娜丽莎，谜の微笑。
6. 其它功能如模板和代码高亮就不说了。

总之它几乎做对了每一件事情，极大解放了忍者的生产力，让我感到非常满意。别的幻灯片框架通常有天花板，你有能力也翻不过去，这是很窝心的。

那还有我什么事呢？当然有。它支持 Markdown，我自然得需要它支持 R Markdown 啊。当时我正在忙 blogdown 的事情，也很有趣，于是等等等，等到感恩节放假，在去另外一个城市的路上我用手机一边看 remark.js 的文档一边琢磨如何把它引进到 R 里面来，关键问题就是 remark 不支持 Pandoc，而是有自己的基于 JS 的 Markdown 渲染工具，所以问题就是如何绕开 Pandoc。思来想去想到一个绝妙的办法，回来集中三整天时间把它码出来。在现有的 R Markdown 扩展中，估计还没有这么黑的手段，而在我写过的 R 包中，也很少有一个我能指出[最关键一行代码](https://github.com/yihui/xaringan/blob/6a2ea5d232/R/render.R#L124)的包。这个包的代码量不大，包括注释和空行才 350 行代码，但包含了一些惊人的查克拉，我要是不说估计也很少有人能意识到。R Markdown 自身那些功能没什么惊人的，想必各位客官已经了如指掌了。先说一个普通的，就是数学公式支持，这是费了我一点脑子的事情，主要问题是 remark 不支持 Pandoc 的 Markdown 语法，所以数学公式得作特殊处理，至于怎么处理，看源代码应该是最好的理解方式，总之你可以在幻灯片中自由使用数学公式。

最厉害的其实是无限月读。

还是先说一下包的名字为啥叫 [xaringan](https://github.com/yihui/xaringan/) 吧。它是写轮眼 sharingan 的变体，把 sh 换成了 x，好让歪果仁知道我的姓 Xie 大概怎么念（而不要[念“鸡”](https://github.com/rbind/yihui/blob/master/cn/2015/10/interview)），当然更重要的是搜起来好搜，虽然读起来不那么好读。写轮眼是火影中的血继限界，有催眠眼和洞察眼的功能。演讲无非也就是催眠观众以及提供洞见，所以我提供这么个写轮眼的工具。xaringan 包中的 R Markdown 输出格式名称为月读（`moon_reader`），月读是写轮眼发动的幻术，对对手进行灵魂拷问。无限月读是一种大规模幻术，让施术者的轮回写轮眼借助月亮的反射使整个世界都陷入无限的幻觉中。“无限”在 xaringan 包中的意思其实是 基于 [servr](https://github.com/yihui/servr) 包的一个本地网页服务器，这个服务器可以无限预览幻灯片：一旦启动这个术，你只需要编辑、保存你的 R Markdown 源文档，其输出可以持续更新，所以你一直都可以在旁边看到重新编译过的新片子页面，而不需要在 RStudio 中重复点击 Knit 按钮。刷新过的页面会保持你刚刚浏览的位置，比如刚刚你在第 10 页，自动刷新后还会留在那一页，而不会变成从头开始。

其实无限月读的功能并不局限在这个包支持的幻灯片上，它可以支持任意 Rmd 文档的持续编译、刷新、预览，条件是输出格式是 HTML（否则没法在浏览器中打开）。这就是 xaringan 的最大秘密：少年，你可以不必点击 Knit 按钮。

servr 包我几年前就写了，我之所以没有在公开场合正式宣传，只是因为我一直在等一个脚底板有三颗痣的人^[我比较耐等，等一样东西经常能等上两三年。]，就是 R Markdown Notebooks，而它终于来了，现在我说出 servr 包，也不会有压力了，因为多数人都不会用它，他们应该会用 Rmd 笔记本的预览功能。这样我肩上就不必背负太多维护 servr 包的压力，我早知道很多用户迫切需要更方便的预览功能，要是我早早宣传，恐怕这两年得鸡飞狗跳了。