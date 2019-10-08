# 附录B 解析参数

- 一个常见的Unix命令行程序使用如下：

  `command [options] arguments`

  一个***option***一般由`-`符号表示，后面可接参数。

  若`-`后面由多个参数，则最后一个参数后可以接参数。

  下面的3种调用方式效果相等：

```bash
$ grep -l -i -f patterns *.c
$ grep -lif patterns *.c
$ grep -lifpatterns *.c
```

​		`-l`、`-i` *option*没有参数，而`-f` *option* 带参数 `patterns`

- 解析参数，需要使用`getopt()`函数：

```c
#include <unistd.h>

extern int optind, opterr, optopt;
extern char *optarg;

/* See main text for description of return value */
int getopt(int argc, char *const argv[], const char *optstring);
```

1. 其中的`argc`与`argv`类似于`main()`方法中的参数
2. `optstring`参数指定了需要从`argv`中解析的参数列表。
   允许的字符为`[a-zA-Z0-9]`（*SUSv3*）。
   不允许的字符为`:?-`，因为在`getopt()`中有特殊意义。
   每个参数字符若带:，则表示这个参数后面可能带有参数。
3. `getopt()`方法需要反复调用，每次返回值表示不同的状态：
   - 若有`option`被找到了，则返回该`option`的字符值
   - 列表遍历完毕，返回-1
   - 若某个`option`带有参数，则将全局变量`optarg`指向该参数
4. `getopt()`返回`int`。不能直接将其赋值给`char`参数，否则`-1`有可能解析错误。
5. 每次调用`getopt()`方法后，`optind`变量会更新，以包含下一个未处理的`option`的位置。
   第一次调用`getopt()`前，`optind`为1

- 判断的思路如下：

  - 若`getopt()`返回`-1`，说明没有参数了，此时`optwind < argc`。
    则`argv[optind]`是下一个非参数的词的位置。
  - 若我们需要解析多个`option`向量，或者需要重新扫描`options`，则需要手动将optwind设置为1

- `getopt()`返回-1 的场景有：

  - 列表遍历完了。此时，`argv[optind]`为`NULL`。

  - 下一个未处理的单词不是以`-`开头。此时，`argv[optind][0]`不等于`'-'`。

  - 下一个未处理的单词就是`-`。此时，`argv[option]`等于`"="`。

  - 下一个未处理的单词包含`--`。此时，`optarg`被设置为`--`后面下一个单词的位置。
    这种场景一般用于将`-`开头的参数不作为`option`解析。例如：

    `grep -- -k myfile`

    会将`"-k"`作为搜索参数进行检索。

- `getopt()`报错的场景有：

  - `argv`中含有`optstring`中不支持的参数。
  - 某些`option`需要参数，但没有找到参数。

- 报错处理的方式：

  - 默认情况下，`getopt()`打印错误信息到`stderr`并返回`'?'`。
    此时，全局变量`optopt`返回导致错误的字符，它可能不在`optstring`列表中，或者缺少参数。
  - `opterr`默认为1。若设置为0，则不打印错误信息。
  - 可以在调用`getopt()`时，参数列表以`':'`开始，效果相当于设置`opterr`为0。
    此时，返回值若为`':'`，则表示**`option`缺乏参数**，从而与**不支持的`option`**区分开。

  | Error-reporting method    | *getopt()* displays error message? | Return for unrecognized option | Return for missing argument |
  | ------------------------- | ---------------------------------- | ------------------------------ | --------------------------- |
  | default (opterr==1)       | YES                                | ?                              | ?                           |
  | opterr == 0               | NO                                 | ?                              | ?                           |
  | : at start of `optstring` | NO                                 | ?                              | :                           |

  