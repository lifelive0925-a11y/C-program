# ============================================================
#  C 语言练习目录 —— GCC + GNU Make
#
#  常用命令：
#    make              编译当前目录下所有 .c 文件
#    make strlen       只编译 strlen.c  ->  strlen.exe
#    make reverse      只编译 reverse.c ->  reverse.exe
#    make run-<名字>   编译并立即运行，如 make run-strlen
#    make clean        删除所有生成的 .exe / .o
#    make help         显示帮助
#
#  注意：make 会把 <目标> 当作要生成的文件名，
#        所以要编译 reverse.c，用 `make reverse`（会自动补 .exe）。
#
#  本 Makefile 已设为「每次强制重编」，不会因为 exe 比 c 新而跳过。
# ============================================================

CC      := gcc
CFLAGS  := -Wall -Wextra -g -std=c11
LDFLAGS :=

# 当前目录下所有 .c 源文件 -> 对应的 .exe
SRCS  := $(wildcard *.c)
PROGS := $(SRCS:.c=.exe)

# 默认目标
.PHONY: all
all: $(PROGS)

# 编译 .c -> .exe
# 依赖里加了 FORCE，保证每次都重新编译，不受时间戳影响
%.exe: %.c FORCE
	@echo "  CC  $<"
	@$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@
	@echo "  OK  $@"

# 强制重编用的空目标：没有命令，永远被当作"过期"
.PHONY: FORCE
FORCE:

# 支持 `make strlen` 而不写 .exe 后缀
.PHONY: $(SRCS:.c=)
$(SRCS:.c=): %: %.exe

# 编译并运行：make run-strlen
.PHONY: run-%
run-%: %.exe
	@echo "  RUN $<"
	@./$<

# 清理产物
.PHONY: clean
clean:
	@rm -f *.exe *.o
	@echo "  已清理 .exe 和 .o 文件"

# 帮助
.PHONY: help
help:
	@echo "目标       说明"
	@echo "---------- ----------------------------------------"
	@echo "make       编译全部 .c -> .exe"
	@echo "make <名>  编译单个文件，如 make strlen"
	@echo "make run-<名>  编译并运行，如 make run-strlen"
	@echo "make clean 删除所有 .exe 和 .o"
	@echo ""
	@echo "当前源文件："
	@for f in $(SRCS); do echo "  - $$f"; done