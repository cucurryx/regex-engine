# regex-engine

这是一个简单的正则引擎，支持大部分纯正则表达式的语法。主要功能就是解析一个正则表达式，来得到一个自动机，并优化。然后根据这个自动机来对字符串来进行匹配，判断是否符合正则表达式。实现方式采用了`regex -> nfa -> dfa -> minimal dfa`的经典实现方式。

## 编译环境
**gcc 7.2.0**

建议在Linux环境下使用，或者使用Clion。
在主目录下使用`make`来直接编译，然后运行`regex-engine`。或者使用IDE来 import project。 输入正则表达式，然后输入字符串判断是否匹配。

--- 

## 程序结构
```
Regex expression ===> NFA ===> DFA ===> Minimal DFA ===> Recognizer
```

使用递归下降的方法来parse正则表达式，用Thompson算法构造出NFA。然后，使用子集构造算法从NFA构造出DFA。最后，使用Hopcroft’s Algorithm来简化DFA。利用最后得到的自动机，来进行匹配。

parse部分参考了[这篇文章](http://www.cs.sfu.ca/~cameron/Teaching/384/99-3/regexp-plg.html)的正则表达式语法描述:
```
<RE>	::=	<union> | <simple-RE>
<union>	::=	<RE> "|" <simple-RE>
<simple-RE>	::=	<concatenation> | <basic-RE>
<concatenation>	::=	<simple-RE> <basic-RE>
<basic-RE>	::=	<star> | <plus> | <elementary-RE>
<star>	::=	<elementary-RE> "*"
<plus>	::=	<elementary-RE> "+"
<elementary-RE>	::=	<group> | <any> | <eos> | <char> | <set>
<group>	::=	"(" <RE> ")"
<any>	::=	"."
<eos>	::=	"$"
<char>	::=	any non metacharacter | "\" metacharacter
<set>	::=	<positive-set> | <negative-set>
<positive-set>	::=	"[" <set-items> "]"
<negative-set>	::=	"[^" <set-items> "]"
<set-items>	::=	<set-item> | <set-item> <set-items>
<set-items>	::=	<range> | <char>
<range>	::=	<char> "-" <char>
```

- NFA的数据结构和构造NFA相关函数在nfa.h和nfa.cc中声明和实现
- DFA在dfa.h和dfa.cc中实现。
- Regex的parser在parser.h和parser.cc中实现

另外，`test/`中包含了对各个部分的测试。

---

## 示例
```
xvvx-regex> (a|b)c
string to match: ac
match!
xvvx-regex> ([a-z])+\*
string to match: abcde*
match!
xvvx-regex> (a?\?)?
string to match: a?
match!
```
---

## TODO
- [ ] 用内存池来管理内存，NFA结点直接从内存池获取内存。
- [ ] 支持正向预查、反向预查、匿名捕获、命名捕获、边界和非贪婪重复等扩展正则表达式的功能。
- [ ] 生成表示NFA和DFA的图像。