
> 建议用`ctrl`+`F`搜索


<table>
<tr>
<td bgcolor=#FDF5E6>
<font color=#6A5ACD size=2>
本文将采用jupyter notebook来书写Markdown相关语法，你可以使用`ctrl`+`enter`来运行Markdown，观察各语法符号的作用。
</font></td></tr></table>


# 一、字体、颜色、背景



> 首先说明，Markdown不具有字体、颜色、背景设置的功能，相关功能我们需要借助于HTML语法来实现


## 1.基本语法
**基本表达形式为：**
``` markdown
<table>
    <tr>
        <td bgcolor=#FDF5E6>
            <font color=#6A5ACD size=2>
本文将采用jupyter notebook来书写Markdown相关语法，你可以使用`ctrl`+`enter`来运行Markdown，观察各语法符号的作用。
            </font>
        </td>
    </tr>
</table>
```

*其中，标签 `<td>` 描述背景，标签`font`描述内容。我们来尝试一下：*



---
**`Ctrl`+`enter`测试一下：**
**********************
```html
<font face="STCAIYUN" color=#A52A2A size=4 >【内容】</font>
```
><font face="STCAIYUN" color=#A52A2A size=4 >字体：华文云彩；颜色：#A52A2A；字号：4号（通常系统默认3号字体，可自由设置字号1-7号）</font>


**再来加上背景试试：**
**********************
``` markdown
<table>
    <tr>
        <td bgcolor=#F5F5DC>
            <font face="STCAIYUN" color=#A52A2A size=4 >
            【内容】
</font></td></tr></table>
```
><table><tr><td bgcolor=#F5F5DC> <font face="STCAIYUN" color=#A52A2A size=4 >【内容】</font></td></tr></table>


## 2.色码表


是不是发现了有些颜色设置采用的是**十六进制码**！！

其实，颜色设置即可以采用**十六进制码**，也可以采用**名字**、也可以采用**rgb(,,)表达结构**。

接下来我们给出常用颜色对应的十六进制码表格，如下：

*<font face="仿宋" size=4 >好多啊！！！算了，我还是给你们一个[链接](https://www.toodoo.com/db/color.html)吧，改天正则一下把表格改好看了！！！</font>*

颜色名|十六进制码|颜色rgb
:---:|:---:|:---:
<font color=#F0F8FF size=4 >AliceBlue</font>|#F0F8FF|rgb(240, 248, 255)
<font color=#FAEBD7 size=4 >AntiqueWhite</font>	|#FAEBD7	|rgb(250, 235, 215)
<font color=#00FFFF size=4 >Aqua</font>|#00FFFF	|rgb(0, 255, 255)
<font color=#7FFFD4 size=4 >Aquamarine</font>	|#7FFFD4	|rgb(127, 255, 212)
···|···|···


# 二、Markdown基本语法


## 1.标题
### 基本表达式：
***********
<font face="黑体" color=#A52A2A size=4 >
            In：
</font>
```
# 一级标题
## 二级标题
### 三级标题
#### 四级标题
##### 五级标题
###### 六级标题
```
***
<font face="黑体" color=#A52A2A size=4 >
            Out：
</font>
># 一级标题
## 二级标题
### 三级标题
#### 四级标题
##### 五级标题
###### 六级标题


## 2.文本样式


### ·基本符号表达式:
***********
|语法|效果|
|---|---|
|```*斜体*```|*斜体*|
|```_斜体_```|_斜体_|
|```**粗体** ```|**粗体** |
|```__粗体__```|__粗体__|
|````文字背景阴影````|`文字背景阴影`|
|```~~文字删除线~~```|~~文字删除线~~|
| | |
|```*~~斜体&删除线~~*```|*~~斜体&删除线~~*|
|```***粗体&斜体***```|***粗体&斜体***|
|```**~~加粗&删除线~~**```|**~~加粗&删除线~~**|
|```***~~倾斜&加粗&删除线~~***```|***~~倾斜&加粗&删除线~~***|
| | |
|特殊字符转义符|```\```|
|```\\```|\\|
|``` \` ```|\`|
|```\.```|\.|
|```\{```|\{|
|···|···|
<font face="仿宋" color=gray size=2 >
            注：组合体，可由前面的语法随意组合
</font>


---
### ·分割线:
``` markdown
分割粗实线：---
分割细实线：***
```


-------
### ·列表:
***
<font face="黑体" color=#A52A2A size=4 >
            In：
</font>

``` markdown
**无序列表样式1**
- 无序列表项目
- 无序列表项目
- 无序列表项目

**无序列表样式2**
* 无序列表项目
* 无序列表项目
* 无序列表项目

**有序列表样式**
1.  有序列表项目
2.  有序列表项目
3.  有序列表项目
2222.  有序列表中即使你写的序号顺序是乱的，只要第一个列表前的数字是1，实际显示时后面的列表都会自动排序

**嵌套列表样式**
- 外层列表项目
 + 内层列表项目
   * 再一层列表项目
 + 内层列表项目
 + 内层列表项目
- 外层列表项目
```

***
<font face="黑体" color=#A52A2A size=4 >
            Out：
</font>

>**无序列表样式1**
- 无序列表项目
- 无序列表项目
- 无序列表项目

>**无序列表样式2**
* 无序列表项目
* 无序列表项目
* 无序列表项目

>**有序列表样式**
1.  有序列表项目
2.  有序列表项目
3.  有序列表项目
2222.  有序列表中即使你写的序号顺序是乱的，只要第一个列表前的数字是1，实际显示时后面的列表都会自动排序

>**嵌套列表样式**
- 外层列表项目
 + 内层列表项目
   - 再一层列表项目
 + 内层列表项目
 + 内层列表项目
- 外层列表项目

---
### ·引用
在需要添加引用的内容之前加入符号 `>`
***
<font face="黑体" color=#A52A2A size=4 >
            In：
</font>

``` markdown
>引用内容
>>重引用
换行当做空格使
除非后面加上两个空格
>
>退出重引用

退出引用
```
***
<font face="黑体" color=#A52A2A size=4 >
            Out：
</font>

>引用内容
>>重引用
换行符当做空格
除非后面加上两个空格
>
>退出重引用

退出引用


---
### ·代码高亮
***
** ·行内式 **
<font face="黑体" color=#A52A2A size=4 >
            In：
</font>
```C语言里的函数 `scanf()` 怎么使用？```

<font face="黑体" color=#A52A2A size=4 >
            Out：
</font>
C语言里的函数 `scanf()` 怎么使用？

***
** ·多行代码 **
>\```[语法名]
内容
\```

***
如：
<font face="黑体" color=#A52A2A size=4 >
            In：
</font>
>\``` python
import numpy as np
\```

<font face="黑体" color=#A52A2A size=4 >
            Out：
</font>
```python
import numpy as np
```
***


---
### ·表格
***
<font face="黑体" color=#A52A2A size=4 >
            In：
</font>

```
|左对齐|左对齐|居中|右对齐|
|----|:----|:----:|----:|
|1|2|3|4|
```

<font face="黑体" color=#A52A2A size=4 >
            Out：
</font>

|左对齐|左对齐|居中|右对齐|
|:----|----|:----:|----:|
|1|2|3|4|
---


### ·超链接
___
**文字超链接：**
<font face="黑体" color=#A52A2A size=4 >
            In：
</font>
```markdown
1.行内式：[我的git主页](https://w407022008.github.io/sique.github.io/)
2.参考式：[usl]:https://w407022008.github.io/sique.github.io/
[我的git主页][usl]
```

___
<font face="黑体" color=#A52A2A size=4 >
            Out：
</font>

1.行内式：
[我的git主页](https://w407022008.github.io/sique.github.io/)
2.参考式：
[我的git主页][usl]
[usl]:https://w407022008.github.io/sique.github.io/

___
**注脚超链接：**  其实也就是采用了参考式
<font face="黑体" color=#A52A2A size=4 >
            In：
</font>
```
使用 Markdown[^1]可以效率的书写文档, 直接转换成 HTML, 你可以使用 Leanote[^Le] 编辑器进行书写。

[^1]: Markdown是一种纯文本标记语言

[^Le]: 开源笔记平台，支持Markdown和笔记直接发为博文
```
___
<font face="黑体" color=#A52A2A size=4 >
            Out：
</font>

使用 Markdown[^1]可以效率的书写文档, 直接转换成 HTML, 你可以使用 Leanote[^Le] 编辑器进行书写。

[^1]: Markdown是一种纯文本标记语言

[^Le]: 开源笔记平台，支持Markdown和笔记直接发为博文

___
** 自动链接、邮箱**
<font face="黑体" color=#A52A2A size=4 >
            In：
</font>
```
<https://w407022008.github.io/sique.github.io/>
<w407022008@gmail.com>
```

***
<font face="黑体" color=#A52A2A size=4 >
            Out：
</font>

<https://w407022008.github.io/sique.github.io/>
<w407022008@gmail.com>

___
**图片引入：**
<font face="黑体" color=#A52A2A size=4 >
            In：
</font>
```
1.行内式：
![图片的名字，不会显示](https://s-media-cache-ak0.pinimg.com/originals/3c/d5/67/3cd5679f54dc60811383649f9f6ea37d.png)
2.参考式：
[photo]:https://s-media-cache-ak0.pinimg.com/originals/3c/d5/67/3cd5679f54dc60811383649f9f6ea37d.png
![图片的名字，不会显示][photo]
```

***
<font face="黑体" color=#A52A2A size=4 >
            Out：
</font>

1.行内式：
![图片的名字，不会显示](https://s-media-cache-ak0.pinimg.com/originals/3c/d5/67/3cd5679f54dc60811383649f9f6ea37d.png)

2.参考式：
![图片的名字，不会显示][photo]
[photo]:https://s-media-cache-ak0.pinimg.com/originals/3c/d5/67/3cd5679f54dc60811383649f9f6ea37d.png

# 三、LaTeX数学编辑


## ·符号

|   符号   |   代码   |     |   符号    |   代码    |     |    符号    |    代码    |     |   符号   |   代码   |
| -------- | -------- | --- | --------- | --------- | --- | ---------- | ---------- | --- | -------- | -------- |
| $\alpha$ | `\alpha` |     | $\beta$   | `\beta`   |     | $\gamma$   | `\gmma`    |     | $\theta$ | `\theta` |
| $\Phi$   | `\Phi`   |     | $\Lambda$ | `\Lambda` |     | $\Omega$   | `\Omega`   |     | $\Delta$ | `\Delta` |
| $\infty$ | `\infty` |     | $\nabla$  | `\nabla`  |     | $\partial$ | `\partial` |     | $d$      | `d`      |
| $\times$ | `\times` |     | $\div$    | `\div`    |     | $\pm$      | `\pm`      |     | $\oplus$ | `\oplus` |
| $\leq$   | `\leq`   |     | $\geq$    | `\geq`    |     | $\approx$  | `\approx`  |     | $\neq$   | `\neq`   |
<font face='仿宋' color=gray size=2> 以上都是一些常用的符号，更多符号输入查看[这里](http://oeis.org/wiki/List_of_LaTeX_mathematical_symbols)
</font>


## ·一些简单的公式例子


* **分式：frac{}{}**
    **In**: `$P(A\mid B) = \frac{P(B\mid A)P(A)}{P(B)}$`
    **Out**:$$P(A\mid B) = \frac{P(B\mid A)P(A)}{P(B)}$$
* **开方：sqrt{}**:
    **In**: `$\sqrt{2\pi}$`
    **Out**: $$\sqrt{2\pi}$$
* **次方：{}^{}**
    **In**: `$e^{2x}\div e^{2}x$`
    **Out**: $$e^{2x}\div e^{2}x$$

* **微分量：\dot{}**
    **In**: `$\dot x, \ddot x, \dddot x$`
    **Out**: $$\dot x, \ddot x, \dddot x$$
* **矢量：\vec{};\overrightarrow{}**
    **In**: `$\vec{x}, \overrightarrow{xy}$`
    **Out**: $$\vec{x}, \overrightarrow{xy}$$
* **矩阵：\matrix{}**
    **In**: `$\left\lgroup \matrix{a & b & 1 \cr c & d & 2 \cr 3} \right\rgroup$`
    **Out**: $$\left\lgroup \matrix{a & b & 1 \cr c & d & 2 \cr 3} \right\rgroup$$
* **积分：\int_{}^{} **
    **In**: `$\int_0^1 f(x)dx - \int^1_0 g(x)dx$`
    **Out**：$$\int_0^1 f(x)dx - \int^1_0 g(x)dx$$

* **求和：\sum_{}^{} **
    **In**: `$\sum\nolimits_{i=1}^{n} i^2 = \sum\limits_{i=1}^{n} i^2$`
    **Out**: $$\sum\nolimits_{i=1}^{n} i^2 = \sum\limits_{i=1}^{n} i^2$$

<font face='仿宋' color=gray size=2>
更多内容查看于
</font><font face='仿宋' color=gray size=3>
[$\LaTeX$](http://www.onemathematicalcat.org/MathJaxDocumentation/TeXSyntax.htm)
</font>


# 四、幻灯片制作


<http://www.jianshu.com/p/86117613b7a6>
这里有一个示例，暂时不需要做。
