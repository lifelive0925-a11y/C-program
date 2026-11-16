# Key FSM

用状态机重写按键处理：非阻塞、带消抖，支持短按和长按。主循环每 10ms 调一次 `key_tick()`，不再用 `HAL_Delay` 卡住 CPU。

## 文件

```text
key.h        状态、事件、key_t 结构体、API
key.c        状态机实现
test_key.c   PC 端模拟按键的测试
```

## 状态图

```text
        stable == 1                 press_ms >= 1000ms
IDLE ───────────────► PRESSED ─────────────────────► LONG
  ▲                      │                             │
  │                      │ stable == 0                 │ stable == 0
  │                      ▼                             ▼
  └──────────────────  SHORT                        RELEASE
```

## 事件

| 事件 | 含义 |
|---|---|
| `KEY_EV_NONE` | 无事件 |
| `KEY_EV_SHORT` | 按下后 1 秒内释放 |
| `KEY_EV_LONG` | 按住满 1 秒 |
| `KEY_EV_RELEASE` | 长按结束、松手 |

## API

```c
void key_init(key_t *k, uint8_t raw);
key_event_t key_tick(key_t *k, uint8_t raw, uint32_t dt_ms);
```

- `raw`：当前按键电平，`1` 表示按下，`0` 表示松开（按硬件取反）
- `dt_ms`：距离上次调用的毫秒数，建议 10
- 返回值：本次产生的事件，一般情况是 `KEY_EV_NONE`

## 参数

| 参数 | 值 | 位置 |
|---|---|---|
| 消抖次数 | 连续 3 次采样一致 | `key.c` 中 `>= 3` |
| 长按阈值 | 1000 ms | `key.c` 中 `>= 1000` |
| tick 周期 | 10 ms | 调用方决定 |

## 构建与运行

```bash
gcc -std=c11 -Wall -Wextra key.c test_key.c -o test_key.exe
./test_key.exe
```

当前输出：

```text
short   : SHORT
long    : LONG
release : RELEASE
bounce  : NONE
```

## 测试说明

`test_key.c` 用固定 10ms tick 模拟输入：

1. **短按**：按下 3 tick 消抖，保持 50 tick，释放 3 tick → 期望 `SHORT`
2. **长按**：按下 3 tick，保持 120 tick（1.2s）→ 期望 `LONG`；再释放 3 tick → 期望 `RELEASE`
3. **抖动**：`1/0` 交替 2 次，不够 3 次 → 期望不触发任何事件

当前实际输出：

```text
short   : SHORT    ✅
long    : LONG     ✅
release : RELEASE  ✅
bounce  : NONE     ✅
```



## 踩坑记录（示例）

### 坑：长按永远不触发

- 现象：按住 3 秒也没有 `LONG`
- 原因：判断条件写成了 `dt_ms >= 1000`，`dt_ms` 是单次间隔，不是累计时间
- 解决：改成 `k->press_ms >= 1000`

### 坑：长按松手后没有 `RELEASE`

- 现象：进入 `KEY_LONG` 后松手，什么事件都没有
- 原因：释放判断写成 `!k->state`，枚举值非 0，条件永远为假
- 解决：改成 `!k->stable`，判断的是电平

## 验收

- `short` 输出 `SHORT`
- `long` 输出 `LONG`
- `release` 输出 `RELEASE`
- 抖动序列不产生事件
- 主循环里没有 `HAL_Delay` 做消抖
- README 里有状态图、事件表、参数、坑记录