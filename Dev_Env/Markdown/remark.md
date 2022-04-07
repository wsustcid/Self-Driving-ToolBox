class: middle, center

#Remark Usage Guides

###Shuai Wang

###USTC, May 1, 2019

# 1. Alignment

## 1.1 Whole slide text alignment 

```
class: middle, center

#Centered vertically and horizontally
```

The classes available for *vertically* aligning text are:

- `top` (default)
- `middle`
- `bottom`

The classes available for *horizontally* aligning text are:

- `left` (default)
- `center`
- `right`

## 1.2 Text block alignment

[Content classes](https://github.com/gnab/remark/wiki/Markdown#content-classes) let you assign CSS classes to a text block, and remark comes with a set of classes for setting horizontal text alignment:

```
.left[Left-aligned text]

.center[Centered text]

.right[Right-aligned text]

.footnote[.red.bold[**Ref.*] Encyclopedia of Machine Learning]
```



---

## 1.3 Images

This is a beautiful picture!.right[<img src=lena.jpg height=400px />]



### 1.3.1 Regular images

Regular images are inserted using normal Markdown [image syntax](http://daringfireball.net/projects/markdown/syntax#img), and are treated like regular content that can be placed inside [content classes](https://github.com/gnab/remark/wiki/Markdown#content-classes), e.g. to be [aligned](https://github.com/gnab/remark/wiki/Formatting#text-block-alignment):

```markdown
# Images

.right[![Right-aligned image](https://images-na.ssl-images-amazon.com/images/G/01/img15/pet-products/small-tiles/23695_pets_vertical_store_dogs_small_tile_8._CB312176604_.jpg)]
```

### 1.3.2 Background images

The [background-image](https://github.com/gnab/remark/wiki/Markdown#background-image) slide property lets you set the [background-image](http://www.w3schools.com/cssref/pr_background-image.asp) CSS property for the slide:

```markdown
background-image: url(image.jpg)

# Slide with background image
```

The background image will by default be centered both horizontally and vertically on the slide, and scaled down to fit if it is larger than the slide.



## 1.4 Video

There are multiple ways to include embedded video within a Remark presentation. Embed code from YouTube or others sites work as is:

```markdown
class: middle, center

<iframe width="560" height="315" src="https://www.youtube.com/embed/5eLcHJLDlI8" frameborder="0" allow="encrypted-media" allowfullscreen></iframe>

### Video example from YouTube
```

https://support.brightcove.com/available-options-standard-iframe-embed-code

HTML5 code also works as a way to embed files from the `assets`folder (or elsewhere).

```html
class: middle, center

<video width="560" height="420" controls>
    <source src="{{ site.baseurl }}/assets/video_example.mp4" type="video/mp4">
</video>

### iframe video test
```

Use the `autoplay` function within the video tag to enable autoplay: `<video width="560" height="420" controls autoplay>`.

---

class: middle, center

<iframe src="video2.mp4" frameborder="0" allow="encrypted-media" allowfullscreen></iframe>



# 2. Markdown

## 2.1 Slide Separators

A line containing three dashes, represents a slide separator (not a horizontal rule, `<hr />`, like in regular Markdown). Thus, a simple Markdown text like the one below represents a slideshow with two slides:

```
# Slide 1
This is slide 1
---
# Slide 2
This is slide 2
```



## 2.2 分栏显示



|                                                              |                                   |
| :----------------------------------------------------------: | :-------------------------------: |
| 利用表格实现分栏显示 <br> 使用br 换行显示 <br> <img src=real-time-face-tracking.gif /> | <img src=lena.jpg height=200px /> |



## 2.3 Incremental Slides

To avoid having to duplicate content if a slide is going to add to the previous one, using only two dashes to separate slides will make a slide inherit the content of the previous one:

```
# Slide

- bullet 1
--

- bullet 2
```

The above text expands into the following:

```
# Slide

- bullet 1
---

# Slide

- bullet 1
- bullet 2
```

---

Empty lines before and after the two dashes are of significance as the preceding newline character is omitted to enable adding to the last line of the previous slide. Thus, as the extra bullet point in the above example needs to go on a separate line, an extra line is added after the two dashes to force a newline. Without the extra line, the resulting text would have been `- bullet 1- bullet 2`.

By default, incremental slides are counted just like ordinary slides. By using the [count](https://github.com/gnab/remark/wiki/Markdown#count) slide property or [countIncrementalSlides](https://github.com/gnab/remark/wiki/Configuration#general)configuration option, excluding either single slides or all incremental slides from the slide count is possible.

## 2.4 Slide Notes

A line containing three question marks, represents a separator of content and note of the slide:

```
# Slide

Some content.

???
Some note.
```

## 2.5 Comments

If you want to leave a comment in your markdown, but not render it in the Slide Notes, you can use either of the two following methods. The HTML style comment will be available in the page's source in the browser, while the empty link will not be (I test result is that it will also be).

**HTML**

```
<!---
I'm a comment.
--->
```

**Empty Link**

```
[//]: # (I'm a comment)
```



## 2.6 Slide Properties

Initial lines of a slide on a key-value format will be extracted as slide properties.

### 2.6.1 name

The `name` property accepts a name used to identify the current slide:

```
name: agenda

# Agenda
```

A slide name may be used to:

- Link to a slide using URL fragment, i.e. `slideshow.html#agenda`, or in Markdown; `[the agenda](#agenda)`

- Navigate to a slide using the [API](https://github.com/gnab/remark/wiki/Configuration#api), i.e. `slideshow.gotoSlide('agenda')`

- Identify slide DOM element, either for scripting or styling purposes:

  ```
  <div class="remark-slide-container">
    <div class="remark-slide-scaler">
      <div class="remark-slide">
        <div id="slide-agenda" class="remark-slide-content">
          <h1>Agenda</h1>
  ```

- Reference slide when using the [template](https://github.com/gnab/remark/wiki/Markdown#template) slide property.

### 2.6.2 class

The `class` property accepts a comma-separated list of class names, which are applied to the current slide:

```
class: center, middle

# Slide with content centered in both dimensions
```

Resulting HTML extract:

```
<div class="remark-slideshow">
  <div class="remark-slide">
    <div class="remark-slide-content center middle">
      <h1>Slide with content centered in both dimensions</h1>
```

Built-in slide classes include `left`, `center`, `right`, `top`, `middle` and `bottom`, which may be used to [align entire slides](https://github.com/gnab/remark/wiki/Formatting#whole-slide-text-alignment).

### 2.6.3 background-image

The `background-image` property maps directly to the [background-image](http://www.w3schools.com/cssref/pr_background-image.asp) CSS property, which are applied to the current slide:

```
background-image: url(image.jpg)

# Slide with background image
```

Other slide background CSS properties defined in the default [remark styles](https://github.com/gnab/remark/blob/master/src/remark.less):

```
background-position: center;
background-repeat: no-repeat;
background-size: contain;      /* applied using JavaScript only if background-image is larger than slide */
```

---

background-image: url(lena.jpg)

The background-image property will create a new slide, so the headings of this slide can not be created by #

### 2.6.4 count

The `count` property allows for specific slides not to be included in the slide count, which is by default displayed in the lower right corner of the slideshow:

```
count: false

This slide will not be counted.
```

When the [countIncrementalSlides](https://github.com/gnab/remark/wiki/Configuration#general) configuration option is enabled, all [incremental slides](https://github.com/gnab/remark/wiki/Markdown#incremental-slides) will automatically have the `count: false`slide property set.

### 2.6.5 template

The `template` property names another slide to be used as a template for the current slide:

```
name: other-slide

Some content.

---
template: other-slide

Content appended to other-slide's content.
```

The final content of the current slide will then be this:

```
Some content.

Content appended to other-slide's content.
```

---

Both template slide content and properties are prepended to the current slide, with the following exceptions:

- `name` and `layout` properties are not inherited
- `class` properties are merged, preserving class order

The `template` property may be used to (apparently) add content to a slide incrementally, like bullet lists appearing a bullet at a time.

Using only two dashes (--) to separate slides implicitly uses the preceding slide as a template:

```
# Agenda

--
1. Introduction

--
2. Markdown formatting
```

Template slides may also contain a special `{{content}}`expression to explicitly position the content of derived slides, instead of having it implicitly appended.

### 2.6.6 layout

The `layout` property either makes the current slide a layout slide, which is omitted from the slideshow and serves as the default template used for all subsequent slides:

```
layout: true

# Section

---

## Sub section 1

---

## Sub section 2
```

Or, when set to false, reverts to using no default template.

Multiple layout slides may be defined throughout the slideshow to define a common template for a series of slides.

### 2.6.7 exclude

The `exclude` property, when set to `true`, hides a slide. It is a way to filter that slide out so that it is not used at all in rendering.

## 2.7 Content Classes

Any occurrences of one or more dotted CSS class names followed by square brackets are replaced with the contents of the brackets with the specified classes, as `<span>` tags, applied:

```
.footnote[.red.bold[*] Important footnote]
```

Resulting HTML extract:

```
<span class="footnote">
  <span class="red bold">*</span> Important footnote
</span>
```

Content classes available include `left`, `center` and `right`, which may be used to [align text blocks](https://github.com/gnab/remark/wiki/Formatting#text-block-alignment).

---

If you wish to have `<div>` tags instead, separate your content on new lines a follows:

```
.footnote[.red.bold[*]
Important footnote]

.footnote[
.red.bold[
*]Important footnote]
```

Resulting HTML:

```
<div class="footnote">
  <span class="red bold">*</span>
  Important footnote
</div>

<div class="footnote">
  <div class="red bold">*</div>
  Important footnote
</div>
```

---

In case of nested brackets, you can use [HTML codes](http://www.ascii.cl/htmlcodes.htm):

```
.footnote[.red.bold[*] Opening bracket: &amp;#91;]
```

Resulting HTML extract:

```
<span class="footnote">
  <span class="red bold">*</span> Opening bracket: [
</span>
```

## 2.8 Syntax Highlighting

Github Flavored Markdown ([GFM](https://guides.github.com/features/mastering-markdown/#GitHub-flavored-markdown)) fenced code blocks are the preferred way of creating code blocks, easily letting you specify the highlighting language:

```ruby
def add(a,b)
*  a + b
end

# Notice how there is no return statement.
```

### 2.8.1 Line Highlighting

With the [highlightLines](https://github.com/gnab/remark/wiki/Configuration#highlighting) configuration option enabled, lines prefixed with `*` will get highlighted with a yellow background, which can be handy for bringing attention to specific parts of code snippets, i.e.:

```
Implicit return statement:

​```ruby
def add(a,b)
*  a + b
end

# Notice how there is no return statement.
​```
```

This functionality is disabled by default.



## 2.9 Presentation mode

Presentation mode can be activated/deactivated by pressing the **P**key on your keyboard while having the window focused.

You will be presented with your current slide, a preview of the next slide, your current and next slide notes as well as a timer.

Additionally you can press **C** to create a new window where the same presentation will be displayed. This window is linked to the main window. Changing slides on one will cause the slide to change on the other.



## 2.10 Keyboard shortcuts

All of these shortcuts can also be seen during a presentation by pressing **H** or **?**

- **h** or **?**: Toggle the help window
- **j**: Jump to next slide
- **k**: Jump to previous slide
- **b**: Toggle blackout mode
- **m**: Toggle mirrored mode.
- **c**: Create a clone presentation on a new window
- **p**: Toggle PresenterMode
- **f**: Toggle Fullscreen
- **t**: Reset presentation timer
- **<number>** + **<Return>**: Jump to slide <number>



# 3. Mathjax