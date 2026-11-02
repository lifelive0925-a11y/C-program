# C-Program 学习仓库

用来练习 C 语言基础语法、以及手写实现核心库函数的个人仓库。
每个 `.c` 文件都是一个可以独立编译、独立运行的练习小程序。

## 项目结构

| 文件 | 说明 |
| --- | --- |
| `strlen.c` | 手写实现字符串长度计算（`my_strlen`） |
| `strcpy.c` | 手写实现字符串拷贝（`my_strcpy`） |
| `memcpy.c` | 手写实现内存块拷贝（`my_memcpy`） |
| `my_copy.c` | 手写实现 `strncpy` 风格的定长拷贝（`my_copy`） |
| `reverse.c` | 把一个 32 位无符号整数的二进制位倒序（`reverse_bits`） |
| `square_root.c` | 用牛顿迭代法求平方根 |
| `Makefile` | 自动化编译脚本 |
| `.vscode/tasks.json` | VS Code 一键编译任务（使用 gcc） |
| `.gitignore` | Git 忽略文件配置 |
| `.gitattributes` | 统一换行符为 LF |

> 每个 `.c` 里都有自己的 `main()`，所以它们是**六个互相独立的小程序**，
> 不能链接成一个可执行文件。`Makefile` 会为每个 `.c` 单独生成一个同名的 `.exe`。

## 环境依赖

- **编译器**：GCC（Windows 下推荐 [MSYS2](https://www.msys2.org/) 自带的 `gcc`；Linux/macOS 用系统自带的 GCC/Clang）
- **构建工具**：GNU Make
- **编辑器**：VS Code（可选）

Windows 下安装 MSYS2 后，把 `C:\msys64\ucrt64\bin` 和 `C:\msys64\usr\bin` 加入 `PATH`，
这样 `gcc` 和 `make` 都能直接在终端里使用。

## 如何编译和运行

所有命令都在项目根目录下的终端里执行。

### 1. 编译全部程序

```bash
make
```

等价于对目录下每个 `.c` 调用一次 `gcc`，产物是同名的 `.exe`（Linux/macOS 下没有后缀）。

### 2. 只编译某一个程序

```bash
make strlen        # 只编译 strlen.c  ->  strlen.exe
make reverse       # 只编译 reverse.c ->  reverse.exe
```

`make list` 可以列出当前所有可编译的程序名，新增 `.c` 文件后会自动识别，不需要改 Makefile。

### 3. 编译并立即运行

```bash
make run-strlen
make run-reverse
```

### 4. 直接运行生成的可执行文件

```bash
./strlen.exe
./square_root.exe      # 这个程序需要从键盘输入一个数
```

`square_root.exe` 是交互式程序，运行时请输入一个非负数，例如：

```text
Enter a number: 2
The square root of 2.000000 is 1.414214
```

### 5. 清理编译产物

```bash
make clean
```

删除所有生成的 `.exe`、`.o` 以及编译时使用的临时目录 `.tmp`。

### 6. 查看全部可用命令

```bash
make help
```

### 常用命令速查

| 命令 | 作用 |
| --- | --- |
| `make` | 编译全部 `.c` |
| `make <名字>` | 编译单个文件，如 `make strlen` |
| `make run-<名字>` | 编译并运行，如 `make run-strlen` |
| `make list` | 列出所有程序名 |
| `make clean` | 删除所有编译产物 |
| `make rebuild` | 先 `clean` 再全量编译 |
| `make help` | 显示帮助 |

## 在 VS Code 中使用

1. 打开本文件夹（`File > Open Folder`）。
2. 按 `Ctrl + Shift + B` 可以直接编译**当前打开的** `.c` 文件，生成同名的 `.exe`。
3. 也可以直接使用终端里的 `make` 命令（推荐，见上一节）。

`tasks.json` 已配置为使用 `gcc`，请确保 `gcc` 在 `PATH` 中，否则 VS Code 会提示找不到命令。

## 编译选项说明

`Makefile` 中使用的是：

```make
CFLAGS  := -std=c11 -Wall -Wextra -g -O2
LDFLAGS := -lm
```

- `-std=c11`：使用 C11 标准
- `-Wall -Wextra`：打开常用警告，便于发现潜在问题
- `-g`：保留调试信息，方便用 gdb 或 VS Code 调试
- `-O2`：二级优化
- `-lm`：链接数学库（`square_root.c` 用到 `fabs`）

当前所有源文件编译时均为**零警告**。

## 备注

- 自定义函数统一加 `my_` 前缀（`my_strlen`、`my_strcpy`、`my_memcpy`），
  避免与标准库 `<string.h>` 中的同名函数冲突。
- Windows 下如果 `make` 报 `Cannot create temporary file in C:\WINDOWS\: Permission denied`，
  这是因为子进程拿不到可写的临时目录；本仓库的 `Makefile` 已通过 `.tmp` 目录做了处理，正常不需要手动干预。
- 仓库路径如果包含中文（例如 `C:\Users\xxx\Desktop\c语言`），建议保持使用相对路径，
  不要给 `TMPDIR` 传绝对路径，否则可能出现编码问题。
