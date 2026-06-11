# ACM 笔试输入输出模板

笔试机考（牛客/赛码等）大多是 **ACM 模式**：没有给定函数签名，输入输出全部自己处理。
输入处理不熟练 = 算法再好也 0 分，**这是性价比最高的复习内容**。

**仓库例子**：`acm_template/`（8 个输入模式模板）、`29IO_template/`（加速 + 文件重定向 + 计时）。

`acm_template` 的使用方式：改 `CMakeLists.txt` 里 `add_executable(<target> <source_file>)` 的源文件名，
然后 `cd build && cmake .. && make && ./<target>`。

---

## 1. 八种输入模式（对应 acm_template/1~8）

### ① 多行输入，行数未知，每行两个数（`1a+b.cpp`）

```cpp
int a, b;
while (cin >> a >> b) {        // cin 返回流状态，EOF 时为 false，自动结束
    cout << a + b << endl;
}
```

**这是最核心的一招**：`while (cin >> x)` 读到 EOF 自动停，本地测试用 Ctrl+D 模拟 EOF。

### ② 第一行组数 n，后接 n 行（`2a+b2.cpp`）

```cpp
int n, a, b;
while (cin >> n) {
    while (n--) { cin >> a >> b; cout << a + b << endl; }
}
```

### ③ 特殊值终止（`3a+b3.cpp`）

```cpp
while (cin >> a >> b) {
    if (a == 0 && b == 0) break;   // 题目约定 0 0 结束
    cout << a + b << endl;
}
```

### ④ 每行先 n 再 n 个数，n=0 终止（`4a+b4.cpp`）

```cpp
while (cin >> n) {
    if (n == 0) return 0;
    while (n--) { cin >> a; /* 累加... */ }
}
```

### ⑤ 每组输出后接空行（`5a+b5.cpp`）

```cpp
cout << a + b << endl << endl;     // 注意题面"每组输出之间空一行"的要求
```

### ⑥ 多组多行嵌套（`6a+b6.cpp`）

```cpp
int n, m, a, sum = 0;
while (cin >> n) {                 // 每组 n 行
    while (n--) {
        cin >> m;                  // 每行先 m 再 m 个数
        while (m--) { cin >> a; sum += a; }
    }
    cout << sum << endl << endl;
    sum = 0;                       // ⚠️ 别忘了清零
}
```

### ⑦ 整行读取（`7getline.cpp`）

```cpp
string s;
while (getline(cin, s)) {          // 读一整行（含空格）
    // 配合 stringstream 切分：
    // stringstream ss(s); string word;
    // while (ss >> word) {...}
}
```

⚠️ 经典坑：`cin >> n` 之后接 `getline` 会先读到残留的换行符，中间要 `cin.ignore()` 或 `getline` 一次吃掉。

### ⑧ 先 n 再读 n 个数进 vector（`8vector.cpp`）

```cpp
while (cin >> n) {
    if (n == 0) break;
    vector<int> nums(n, 0);
    for (int i = 0; i < n; i++) cin >> nums[i];
    // ...处理...
}
```

---

## 2. IO 加速与本地调试（`29IO_template/main.cpp`）

百万级输入用 cin 默认配置会超时，开场三件套：

```cpp
ios::sync_with_stdio(0);   // 关闭与 C stdio 的同步（之后不可混用 scanf/printf）
cin.tie(0);                // 解除 cin 与 cout 的绑定（cin 前不再 flush cout）
cout.tie(0);
```

### 本地文件重定向（不用每次手敲测试数据）

```cpp
#define LOCAL                       // 提交前注释掉这行即可
#ifdef LOCAL
    ifstream infile("../in.txt");
    ofstream outfile("../out.txt");
    #define cin infile
    #define cout outfile
#endif
```

`28graph` 用的是另一种写法 `freopen("in.txt", "r", stdin)`，效果相同。
调试信息走 `cerr`（不受重定向影响，也不算输出）——`31dijkstra/main.cpp` 中
`cerr << ...` 打印松弛过程就是范例。

### 计时

```cpp
auto start = chrono::high_resolution_clock::now();
// ...被测代码...
auto end = chrono::high_resolution_clock::now();
chrono::duration<double> elapsed = end - start;
cerr << "Time taken: " << elapsed.count() << " seconds" << endl;
```

---

## 3. 笔试开场模板（直接背）

```cpp
#include <bits/stdc++.h>           // 比赛环境通用万能头
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    while (cin >> n) {             // 按题意选上面 8 种模式之一
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        // ---- 算法部分 ----
        // ---- 输出，注意行末空格/空行要求 ----
    }
    return 0;
}
```

检查清单：
- [ ] 多组输入是否每组都**重置了全局状态**（sum、visited、dp 数组）？
- [ ] 输出格式：行末有无多余空格？组间要不要空行？
- [ ] 数据范围要不要 `long long`？
- [ ] 提交前删掉 `#define LOCAL` / freopen / cerr 调试（cerr 可留，但别拖慢）。
