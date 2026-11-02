# ============================================================
#  C 语言练习仓库 —— GCC + GNU Make
#
#  本目录下每个 .c 文件都是一个独立的练习小程序（各自带 main），
#  所以编译规则是「一个 .c -> 一个同名的 .exe」，而不是链接成一个程序。
#
#  常用命令：
#    make                 编译当前目录下所有 .c 文件
#    make strlen          只编译 strlen.c  ->  strlen.exe
#    make run-strlen      编译并立即运行   ->  make run-strlen
#    make list            列出所有可编译的程序名
#    make clean           删除所有生成的 .exe 和 .o
#    make rebuild         先清理再全量编译
#    make help            显示帮助
#
#  注意：make 会把 <目标> 当成文件名，所以要编译 reverse.c
#        写 `make reverse` 即可，Makefile 会自动补上 .exe。
# ============================================================

CC       := gcc
# -std=c11：使用 C11 标准；-Wall -Wextra：打开常用警告；
# -g：保留调试信息，方便 VS Code / gdb 单步调试；-O2：二级优化。
# 注意 -O2 会把数组越界等问题用 -Warray-bounds 报出来，是件好事。
CFLAGS   := -std=c11 -Wall -Wextra -g -O2
# -lm 链接数学库（square_root.c 用到 fabs）。
# MinGW 下数学库通常已内置，加上也无害；Linux 下则必须加。
LDFLAGS  := -lm

# ------------------------------------------------------------
#  平台差异：Windows 下可执行文件带 .exe 后缀
# ------------------------------------------------------------
# 注意：这些变量必须写在所有规则之前。make 会立即展开规则行里的
# 变量（$(PROGS) 等），如果 EXE 定义在后面，规则就会退化成
# 不带 .exe 的 <名字>: <名字>.c，并报 "Circular ... dependency"。
# OS 环境变量并非所有 make（尤其 MSYS2 / Cygwin 的 make）都会设置，
# 所以这里再用 uname 兜底判断一次。
IS_WINDOWS := $(if $(filter Windows_NT,$(OS)),1,$(if $(findstring MINGW,$(shell uname -s 2>/dev/null)),1,$(if $(findstring MSYS,$(shell uname -s 2>/dev/null)),1,$(if $(findstring CYGWIN,$(shell uname -s 2>/dev/null)),1,))))
ifeq ($(IS_WINDOWS),1)
EXE := .exe
endif

# 当前目录下所有 .c 源文件 -> 对应的可执行文件名
SRCS  := $(wildcard *.c)
NAMES := $(SRCS:.c=)
PROGS := $(addsuffix $(EXE),$(NAMES))

# ------------------------------------------------------------
#  Windows 下 MinGW gcc 的临时目录问题
# ------------------------------------------------------------
# 在 Windows + MSYS2/MinGW 环境里，gcc 可能报：
#   Cannot create temporary file in C:\WINDOWS\: Permission denied
# 原因是 make 启动的子 shell 里 TMPDIR / TMP / TEMP 都是空的，
# gcc 只好退回到不可写的 C:\WINDOWS\。
#
# 解决方式：在每条编译命令前把三个临时目录变量一起显式设好。
# 必须「三个都设」——只设 TMPDIR 时 gcc 仍会去读 TMP 而失败。
#
# 用相对路径 .tmp，不要用绝对路径：本仓库目录名含中文（c语言），
# make 在把相对路径转成绝对路径时会把中文编码搞乱。
ifeq ($(IS_WINDOWS),1)
TMPDIR_ENV := TMPDIR=.tmp TMP=.tmp TEMP=.tmp
else
TMPDIR_ENV :=
endif

# ------------------------------------------------------------
#  默认目标：编译全部程序
# ------------------------------------------------------------
.DEFAULT_GOAL := all
.PHONY: all
all: $(PROGS)

# 一个 .c -> 一个同名可执行文件，只依赖自己的源文件
# 用静态模式规则，把每个 <名字>.c 明确映射到 <名字>.exe，
# 避免不同程序之间互相串依赖。
$(PROGS): %$(EXE): %.c
	@mkdir -p .tmp
	@echo "  CC  $<"
	@$(TMPDIR_ENV) $(CC) $(CFLAGS) $< $(LDFLAGS) -o $@
	@echo "  OK  $@"

# 允许 `make strlen`（不带后缀）直接编译 strlen.c
.PHONY: $(NAMES)
$(NAMES): %: %$(EXE)

# 编译并运行：make run-strlen
.PHONY: run-%
run-%: %$(EXE)
	@echo "  RUN $<"
	@./$<

# ------------------------------------------------------------
#  辅助目标
# ------------------------------------------------------------
.PHONY: list
list:
	@echo "可编译的程序："
	@for n in $(NAMES); do echo "  - $$n"; done

.PHONY: clean
clean:
	@echo "  CLEAN 删除所有 .exe / .o 和 .tmp 里的临时文件"
	@rm -f *.exe *.o
	@rm -rf .tmp

.PHONY: rebuild
rebuild: clean all

.PHONY: help
help:
	@echo "目标              说明"
	@echo "----------------  ----------------------------------------"
	@echo "make              编译全部 .c -> .exe"
	@echo "make <名字>       编译单个文件，如 make strlen"
	@echo "make run-<名字>   编译并运行，如 make run-strlen"
	@echo "make list         列出所有可编译的程序名"
	@echo "make clean        删除所有 .exe 和 .o"
	@echo "make rebuild      先 clean 再全量编译"
	@echo "make help         显示本帮助"
	@echo ""
	@echo "当前源文件："
	@for f in $(SRCS); do echo "  - $$f"; done
