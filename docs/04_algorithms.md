# 笔试算法题分类复习（核心篇）

笔试算法题按解题套路分为以下 10 类。每类给出：**原理 → 通用模板 → 仓库内例子 → 推荐练习题**。
复习方法：先看原理，**遮住模板自己默写一遍**，跑通仓库例子，再刷推荐题巩固。

> 仓库例子均可 `cd <目录> && mkdir -p build && cd build && cmake .. && make` 编译运行。

## 分类总表

| # | 类型 | 识别信号 | 仓库例子 | 复杂度 |
|---|------|----------|----------|--------|
| 1 | 哈希表 | "是否存在/出现次数/两数之和" | `17test_map` `18test_hash` | O(n) |
| 2 | 双指针/滑动窗口 | "连续子数组/窗口最值/原地操作" | `10single_queue` `30nums` | O(n) |
| 3 | 链表 | "反转/环/合并/第 k 个节点" | `8link_list` | O(n) |
| 4 | 栈与队列 | "匹配/单调性/用 X 实现 Y" | `9queue_from_stack` `10single_queue` `13queue` | O(n) |
| 5 | 二叉树 | "遍历/深度/路径/公共祖先" | `11binary_tree` | O(n) |
| 6 | 字符串匹配 KMP | "子串首次出现位置/重复模式" | `7kmp_algorithm` | O(n+m) |
| 7 | 回溯 | "所有组合/排列/子集/棋盘" | `26backtracking` | 指数级 |
| 8 | 动态规划 | "最值/方案数/能否达成，有重叠子问题" | `27dnamicPramming` | O(n·m) |
| 9 | 图论 DFS/BFS/最短路 | "岛屿/连通块/最短路径" | `28graph` `31dijkstra` | O(V+E) / O(E log V) |
| 10 | 排序/快速选择/位运算 | "第 k 大/TopK/不用加号" | `30nums` `14heap_test` `24getsum` `34ninja_build` | O(n)~O(n log n) |

---

## 1. 哈希表

### 原理

用空间换时间：把"查找是否存在"从 O(n) 降到 O(1)。看到**"两个元素配对"、"统计频次"、"判重"**先想哈希。
- 元素判重 → `unordered_set`
- 键值映射（值→下标、词→频次）→ `unordered_map`
- 需要有序遍历 → `set`/`map`（红黑树，O(log n)，详见 [02_stl.md](./02_stl.md)）

### 模板：两数之和（LeetCode 1）

```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;              // 值 -> 下标
    for (int i = 0; i < nums.size(); i++) {
        auto it = seen.find(target - nums[i]); // 查"配对的另一半"
        if (it != seen.end()) return {it->second, i};
        seen[nums[i]] = i;                     // 边查边存，只扫一遍
    }
    return {};
}
```

**仓库例子**：`17test_map/testmap.cpp`（map 的 insert/find/operator[] 用法）。

**练习**：LC 1 两数之和、LC 242 有效字母异位词、LC 349 两数组交集、LC 454 四数相加 II、LC 128 最长连续序列。

---

## 2. 双指针 / 滑动窗口

### 原理

- **双指针**：两个下标按规则移动，把双重循环 O(n²) 压成 O(n)。三种形态：快慢指针（原地删除/链表找环）、左右对撞（有序数组两数之和/盛水）、滑动窗口（连续子区间）。
- **滑动窗口**：右指针扩张窗口，不满足条件时左指针收缩。**窗口内统计量必须能 O(1) 增量维护**。

### 模板：滑动窗口

```cpp
int left = 0;
for (int right = 0; right < n; right++) {
    addToWindow(nums[right]);            // 1. 右端进
    while (windowInvalid()) {            // 2. 失效则左端出
        removeFromWindow(nums[left]);
        left++;
    }
    ans = max(ans, right - left + 1);    // 3. 此刻窗口合法，更新答案
}
```

### 仓库例子：滑动窗口最大值（`10single_queue/single_queue.cpp`，LC 239）

窗口最大值不能 O(1) 维护，要借助**单调队列**（递减）：新元素入队前把队尾所有比它小的弹掉——它们再也不可能成为最大值：

```cpp
void push(T x) {                         // 入队：维持队列递减
    while (!sq.empty() && x > sq.back()) sq.pop_back();
    sq.push_back(x);
}
void pop(T x) {                          // 出窗：仅当队首正是离开的元素才弹
    if (!sq.empty() && sq.front() == x) sq.pop_front();
}
T front() { return sq.front(); }         // 队首即窗口最大值
```

**练习**：LC 27 移除元素、LC 15 三数之和、LC 209 长度最小的子数组、LC 3 无重复字符的最长子串、LC 239 滑动窗口最大值。

---

## 3. 链表

### 原理

链表题九成靠两个技巧：
1. **虚拟头节点 dummyHead**：把"删头节点"和"删中间节点"统一成一种情况，不用单独判空（`8link_list` 的 `Linklist` 类就内置了 `_dummyHead`）。
2. **画图移指针**：先存 next 再断链，顺序错一步就丢链。

### 模板：反转链表（LC 206）

```cpp
ListNode* reverseList(ListNode* head) {
    ListNode *pre = nullptr, *cur = head;
    while (cur) {
        ListNode* nxt = cur->next;   // 先保存
        cur->next = pre;             // 再反转
        pre = cur; cur = nxt;        // 双指针前移
    }
    return pre;
}
```

### 模板：删除节点（带 dummy，对应 `8link_list` 的 `deleteAtIndex`）

```cpp
ListNode* dummy = new ListNode(0); dummy->next = head;
ListNode* cur = dummy;
while (cur->next && /*未到目标*/) cur = cur->next;
ListNode* tmp = cur->next;
cur->next = cur->next->next;
delete tmp;
```

**仓库例子**：`8link_list/linkList.cpp` 完整实现了 LC 707 设计链表（get / addAtHead / addAtTail / addAtIndex / deleteAtIndex）。

**练习**：LC 206 反转链表、LC 19 删除倒数第 N 个节点、LC 142 环形链表 II（快慢指针，相遇后从头同速再走）、LC 21 合并有序链表、LC 160 相交链表。

---

## 4. 栈与队列

### 原理

- 栈：后进先出 → **匹配类问题**（括号、消消乐）、**单调栈**（下一个更大元素）。
- 队列：先进先出 → BFS 的载体。
- "用栈实现队列"类题考的是**摊还分析**：每个元素最多进出两个栈各一次，均摊 O(1)。

### 仓库例子 1：两个栈实现队列（`9queue_from_stack/queue_from_stack.cpp`，LC 232）

```cpp
stack<int> stack_in, stack_out;
void push(int x) { stack_in.push(x); }
int pop() {
    if (stack_out.empty())              // 只有出栈空了才倒一次
        while (!stack_in.empty()) { stack_out.push(stack_in.top()); stack_in.pop(); }
    int x = stack_out.top(); stack_out.pop();
    return x;
}
```

同文件还有反向题：**单队列实现栈**（LC 225）——push 后把前面 n-1 个元素出队再入队，队首即栈顶。

### 仓库例子 2：单调队列（见上文滑动窗口）；`13queue/queue.cpp` 是 STL queue 适配器的 mini 实现（面试问"queue 底层"直接背它）。

### 单调栈模板（下一个更大元素，LC 739）

```cpp
stack<int> st;                            // 存下标，栈内对应值单调递减
for (int i = 0; i < n; i++) {
    while (!st.empty() && nums[i] > nums[st.top()]) {
        ans[st.top()] = i - st.top();     // nums[i] 就是栈顶的"下一个更大"
        st.pop();
    }
    st.push(i);
}
```

**练习**：LC 20 有效括号、LC 232/225 栈队列互实现、LC 739 每日温度、LC 84 柱状图最大矩形、LC 347 前 K 个高频元素（堆）。

---

## 5. 二叉树

### 原理

二叉树 = **递归三要素**：参数返回值、终止条件（`root == nullptr`）、单层逻辑（按前/中/后序安排"处理当前节点"的位置）。
层序遍历用队列（BFS），一圈 `while + for(size)` 处理一层。

### 仓库例子：四种遍历（`11binary_tree/binary_tree.cpp`）

```cpp
// 递归（前序为例；中序/后序只是调换 push_back 位置）
void pre_order(TreeNode* node, vector<int>& res) {
    if (!node) return;
    res.push_back(node->val);   // 根（中序放中间，后序放最后）
    pre_order(node->left, res);
    pre_order(node->right, res);
}

// 层序：队列 BFS
vector<int> levelOrder(TreeNode* root) {
    vector<int> res; if (!root) return res;
    queue<TreeNode*> q; q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        res.push_back(node->val);
        if (node->left)  q.push(node->left);
        if (node->right) q.push(node->right);
    }
    return res;
}
```

按层分组的变体：内层加 `int size = q.size(); for (int i = 0; i < size; i++) {...}`。

记忆锚点：
- 前序 = 根左右（拷贝/构造树用）、中序 = 左根右（BST 中序有序！）、后序 = 左右根（求子树信息汇总，如高度、删除树）。
- BST 的题先想"中序遍历是升序数组"。

**练习**：LC 144/94/145/102 四种遍历、LC 104 最大深度、LC 101 对称二叉树、LC 236 最近公共祖先、LC 98 验证 BST、LC 105 前序+中序构造树。

---

## 6. 字符串匹配（KMP）

### 原理

暴力匹配失配时文本指针回退，O(n·m)。KMP 的洞察：失配时**模式串里已匹配的前缀自带信息**。
`next[i]` = `s[0..i]` 的**最长相等前后缀**长度。失配时模式指针 `j` 跳到 `next[j-1]`（利用"前缀==后缀"跳过重复比较），文本指针 `i` 永不回退 → O(n+m)。

### 仓库例子：`7kmp_algorithm/kmp.cpp`（LC 28）

```cpp
void getNext(vector<int>& next, const string& s) {
    int j = 0; next[0] = 0;
    for (int i = 1; i < s.size(); i++) {
        while (j > 0 && s[i] != s[j]) j = next[j-1];  // 失配回退（可能连续回退）
        if (s[i] == s[j]) j++;
        next[i] = j;
    }
}
int strStr(const string& haystack, const string& needle) {
    vector<int> next(needle.size(), 0);
    getNext(next, needle);
    int j = 0;
    for (int i = 0; i < haystack.size(); i++) {
        while (j > 0 && haystack[i] != needle[j]) j = next[j-1];
        if (haystack[i] == needle[j]) j++;
        if (j == needle.size()) return i - needle.size() + 1;
    }
    return -1;
}
```

记忆锚点：求 next 的过程**就是模式串和自己做 KMP**，两段代码结构完全一样。

**练习**：LC 28 找出字符串第一个匹配项、LC 459 重复的子字符串（`n % (n - next[n-1]) == 0`）。

---

## 7. 回溯

### 原理

回溯 = 在**决策树**上 DFS：每层一个 for 循环（横向选哪个），递归进入下一层（纵向），返回时**撤销选择**。
能解四类题：组合、切割、子集、排列 + 棋盘类（N 皇后、解数独）。

通用骨架（背下来）：

```cpp
void backtracking(参数) {
    if (终止条件) { result.push_back(path); return; }
    for (int i = startIndex; i < n; i++) {   // 本层候选
        path.push_back(选择);                 // 处理
        backtracking(i + 1);                  // 递归（组合用 i+1，排列从 0 开始+used）
        path.pop_back();                      // 回溯撤销
    }
}
```

### 仓库例子：`26backtracking/main.cpp` 包含三道递进的题

1. **组合（LC 77）**：`backtracking(n, k, i+1)`，附剪枝 `i <= n - (k - path.size()) + 1`（剩余元素不够凑 k 个就别进了）。
2. **子集 II 去重（LC 90）**：先 `sort`，同层去重 `if (i > 0 && nums[i]==nums[i-1] && !used[i-1]) continue;`
   —— `used[i-1]==false` 说明前一个相同元素是**本层**用过又撤销的，跳过；`==true` 则是树枝上用的，允许。
3. **递增子序列（LC 491）**：不能排序，改用本层 `unordered_set` 去重。

记忆锚点：
- 组合/子集：用 `startIndex` 防止回头；排列：用 `used[]` 数组，每层从 0 扫。
- "树层去重"（结果不能重复）vs"树枝去重"（同一路径不能重复用元素）是所有去重题的分水岭。

**练习**：LC 77 组合、LC 39/40 组合总和、LC 78/90 子集、LC 46/47 全排列、LC 131 分割回文串、LC 51 N 皇后。

---

## 8. 动态规划

### 原理

DP 适用条件：**最优子结构 + 重叠子问题**。固定解题五步（代码随想录套路）：
1. 确定 `dp[i][j]` 的**含义**（最重要，想清楚这一步题就解了一半）
2. 递推公式
3. 初始化
4. 遍历顺序
5. 打印 dp 数组调试

### 仓库例子：01 背包（`27dnamicPramming/main.cpp`）

**二维版**：`dp[i][j]` = 背包容量 j、从前 i 件物品中任取的最大价值。

```cpp
// 不放 i：dp[i-1][j]；放 i：dp[i-1][j-weight[i]] + value[i]
if (j < weight[i]) dp[i][j] = dp[i-1][j];
else dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]] + value[i]);
```

**一维滚动数组版**（必须掌握，笔试写这个）：

```cpp
vector<int> dp(bagweight + 1, 0);
for (int i = 0; i < weight.size(); i++)           // 先物品
    for (int j = bagweight; j >= weight[i]; j--)  // 后容量，⚠️ 倒序
        dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
```

**为什么倒序**：一维 `dp[j]` 复用的是"上一行"的值；正序遍历时 `dp[j-weight[i]]` 已被本行更新过，
等于同一件物品放了两次——那是**完全背包**（完全背包正是把这层改成正序）。

### DP 题型地图

| 题型 | 状态定义套路 | 代表题 |
|------|--------------|--------|
| 线性 DP | dp[i] = 以 i 结尾/前 i 个的最值 | LC 70 爬楼梯、LC 198 打家劫舍、LC 53 最大子数组和 |
| 01 背包 | 选或不选，容量倒序 | LC 416 分割等和子集、LC 494 目标和 |
| 完全背包 | 可重复选，容量正序 | LC 322 零钱兑换、LC 518 零钱兑换 II |
| 子序列 | dp[i][j] = s1 前 i 与 s2 前 j | LC 1143 最长公共子序列、LC 72 编辑距离 |
| 区间/其他 | dp[i][j] = 区间 [i,j] | LC 516 最长回文子序列、LC 300 LIS |

**练习**：上表全部 + LC 121 买卖股票、LC 62 不同路径。

---

## 9. 图论：DFS / BFS / 最短路

### 原理

- **连通块类**（岛屿）：遍历每个格子，遇到未访问的陆地就 DFS/BFS 把整个连通块染色，计数 +1。
- **层数/最短步数类**（无权图）：必须 BFS，队列天然按距离分层。
- **带权最短路**：Dijkstra（非负权），贪心 + 堆：每次取当前距离最小的未访问点，松弛其出边。

### 仓库例子 1：岛屿数量（`28graph/main.cpp`，LC 200 / 卡码网 99）

```cpp
int dir[4][2] = {0,1, 1,0, -1,0, 0,-1};          // 四方向数组

void dfs(grid, visited, x, y) {
    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][0], ny = y + dir[i][1];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;   // 越界
        if (!visited[nx][ny] && grid[nx][ny] == 1) {
            visited[nx][ny] = true;               // 入口处标记
            dfs(grid, visited, nx, ny);
        }
    }
}
// BFS 版同文件：⚠️ 入队时立刻标记 visited，而不是出队时，否则重复入队超时
```

### 仓库例子 2：堆优化 Dijkstra（`31dijkstra/main.cpp`，卡码网 47）

```cpp
vector<list<Edge>> grid(N+1);                     // 邻接表
vector<int> minidst(N+1, INT_MAX);                // 源点到各点最短距离
vector<bool> visited(N+1, false);
priority_queue<pair<int,int>, vector<pair<int,int>>, edge_greater> pq;  // 小顶堆<节点,距离>

minidst[start] = 0;
pq.push({start, 0});
while (!pq.empty()) {
    auto cur = pq.top(); pq.pop();
    if (visited[cur.first]) continue;             // 懒删除：过期堆项直接跳过
    visited[cur.first] = true;                    // 1 选最近未访问点 2 标记
    for (Edge e : grid[cur.first])                // 3 松弛出边
        if (!visited[e.to] && minidst[e.to] > minidst[cur.first] + e.val) {
            minidst[e.to] = minidst[cur.first] + e.val;
            pq.push({e.to, minidst[e.to]});
        }
}
```

记忆锚点：Dijkstra 三部曲 = 选最小、标访问、松弛邻边；堆优化把"选最小"从 O(V) 降到 O(log V)，总复杂度 O(E log V)。
负权边用 Bellman-Ford，多源最短路用 Floyd。

**练习**：LC 200 岛屿数量、LC 695 岛屿最大面积、LC 994 腐烂的橘子（多源 BFS）、LC 207 课程表（拓扑排序）、LC 743 网络延迟时间（Dijkstra）。

---

## 10. 排序、快速选择与位运算

### 快速排序 & 快速选择

**仓库例子**：`30nums/main.cpp`（quickSelect 求第 k 小）、`34ninja_build/test.cpp`（并行快排，见 [03_concurrency.md](./03_concurrency.md)）

partition 是核心：选 `nums[right]` 为 pivot，把小于 pivot 的换到前面，最后 pivot 归位，**返回的下标就是 pivot 的最终位置**：

```cpp
int partition(vector<int>& nums, int left, int right) {
    int pivot = nums[right], i = left;
    for (int j = left; j < right; j++)
        if (nums[j] < pivot) swap(nums[i++], nums[j]);
    swap(nums[i], nums[right]);
    return i;
}
// 快速选择：第 k 小 = 只递归 pivot 所在的一侧，平均 O(n)
int quickSelect(vector<int>& nums, int l, int r, int k) {
    if (l == r) return nums[l];
    int p = partition(nums, l, r);
    if (p == k) return nums[p];
    return p < k ? quickSelect(nums, p+1, r, k) : quickSelect(nums, l, p-1, k);
}
```

### 堆排序 / TopK

**仓库例子**：`14heap_test/heap_test.cpp`（make_heap / push_heap / pop_heap / sort_heap 全流程，见 [02_stl.md](./02_stl.md)）。
TopK 套路：**求前 k 大用小顶堆**（堆中维持 k 个最大值，新元素 > 堆顶则替换），O(n log k)。

### 排序面试速查

| 算法 | 平均 | 最坏 | 稳定 | 备注 |
|------|------|------|------|------|
| 快排 | O(n log n) | O(n²) | ✗ | 最坏出现在有序输入 + 固定 pivot |
| 归并 | O(n log n) | O(n log n) | ✓ | 额外 O(n) 空间；链表排序首选 |
| 堆排 | O(n log n) | O(n log n) | ✗ | 原地，TopK |
| 冒泡/插入 | O(n²) | O(n²) | ✓ | 插入排序对近乎有序数据 O(n) |

### 位运算

**仓库例子**：`24getsum/main.cpp`（不用 + 求和，见 [01_cpp_core.md](./01_cpp_core.md) 第 7 节）。

常用恒等式：`x & (x-1)` 去掉最低位 1（数 1 的个数/判 2 的幂）、`x & (-x)` 取最低位 1、
异或自反 `a^a=0, a^0=a`（找只出现一次的数）。

**练习**：LC 215 数组中第 K 个最大元素（快速选择）、LC 912 排序数组、LC 136 只出现一次的数字、LC 191 位 1 的个数、LC 371 两整数之和。

---

## 附：笔试通用注意事项

1. **数据范围决定算法**：n ≤ 20 回溯/状压；n ≤ 10³ 可 O(n²)；n ≤ 10⁵ 需 O(n log n)；n ≥ 10⁷ 只能 O(n)。
2. **整型溢出**：累加、相乘先想 `long long`；负数取模、`(unsigned)` 左移（`24getsum` 的写法）。
3. **输入输出**：ACM 模式见 [05_acm_io.md](./05_acm_io.md)，比赛前务必过一遍。
