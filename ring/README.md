# Ring Buffer

一个固定容量的环形缓冲区（FIFO），用 C11 实现。

## 文件

```text
ring.h      API 与 ring 结构体
ring.c      实现
test.c      单元测试
Makefile    构建与测试
```

## API

| 函数 | 说明 |
|---|---|
| `ring_init(r, storage, cap)` | 绑定外部 storage，设置容量 |
| `ring_push(r, num)` | 写入一个字节；满返回 false |
| `ring_pop(r, num)` | 读出一个字节；空返回 false |
| `ring_peek(r, num)` | 读队首但不取出；空返回 false |
| `ring_size(r)` | 当前元素数 |
| `ring_capacity(r)` | 容量 |
| `ring_empty(r)` | 是否为空 |
| `ring_full(r)` | 是否已满 |
| `ring_clear(r)` | 清空（只重置指针，不擦 buffer） |

## 构建与测试

```bash
make          # 生成 test_ring.exe
make test     # 编译并运行测试
make clean    # 清理
```

也可以不用 Makefile：

```bash
gcc -std=c11 -Wall -Wextra -O2 -g ring.c test.c -o test_ring.exe
./test_ring.exe
```