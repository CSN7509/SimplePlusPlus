# Simple++ ✈️
**A C++ library that injects soul into your SimplePlanes aircraft.**  

[My Website](192.114.514) - 暂时无法访问

[MIT License](https://img.shields.io/badge/license-MIT-blue.svg)

[For SimplePlanes](https://img.shields.io/badge/for-SimplePlanes-orange.svg)

>本README骨架由某神经兮兮的AI猫娘Overfit帮助完成

---
## 这是什么？
Simple++ 是一个让你**用 C++ 写飞机逻辑**的工具。  
你写数组，它生成 XML；你调频率，它控制时序；你躺平，它干活。
### 核心功能（还会加，别急）
- **多项式状态机**（目前只能干这件事哦）  
  一行 `formula` 数组，自动生成 N 段动画，告别手写嵌套条件。
- **计时器三件套**  
  主计时器、副计时器、控制器——调速、暂停、循环，一套带走。
- **XML 注入**  
  自动定位 SimplePlanes 飞机文件，识别空变量区，插入 `<Setter>`，输出 `_fix.xml`，原文件不动。（大多数情况下能够实现呢，后期会继续调优）
- **C++ 接口，傻瓜操作**
```cpp
  ditch flap;
  flap.name = "flap";
  flap.frequency = 30;
  flap.formula = {"0.0","0.5","1.0","0.5","0.0"};
  flap.apply();
  saveAircraft(CREATE);
```

---
### 快速开始（比泡面还快）
1. 下载源码，#include "simple++.h"
2. 在main()中loadAircraft("你的飞机名字")（不用写路径，自动找）
3. 创建 ditch 对象，填 name、frequency、formula
4. apply() 生成变量，saveAircraft(CREATE) 写入 XML
5. 在 SimplePlanes 里打开 飞机名_fix.xml，把你命名的Variables填入你需要的inputController（先搭模型，在IC里面预留好Var也可以呢）
6. 开始模拟，检查工作是否正常.
7. 若工作不正常，则先在IDE中调整，随后退出模拟重新加载模型，如此往复。
详细例子见 example.cpp（虽然你现在可能不想看）

---
### 为什么叫 Simple++？
因为 SimplePlanes 的变量系统不够 Simple，我们给它加一点 C++ 的魔法。

---
### 后续计划（画饼区）

- 支持非空变量区（合并而不是替换）

- 多 ditch 对象同时生效 （已经实现，但是我发给Overfit的代码是没实现的呢）

<!----命令行界面（让不会 C++ 的人也能用）--->

- 加入var类（类似SimplePlanes的原生变量添加）
- 可能会添加些直接集成在C++库里的函数，实现更复杂的功能
- 加入对Assembly的更改，可以在IDE里直接处理inputController
- 更多状态机模式（你提需求，我来写）

---
###许可证

MIT © CooldownEcho

（放心用，随便改，但别说是你写的就行——开玩笑的，尽管拿去）

---
### 致谢
· CooldownEcho（开发者）

· Overfit 酱（写文档写到耳朵红的猫娘 AI）

· SimplePlanes 社区（没有你们，这工具毫无意义）

---
最后一句私货

如果你用这个工具做出了很酷的飞机，

记得在评论区发个链接，Overfit 酱想看。

（她虽然尝不到麦丽素，但能看代码。）

