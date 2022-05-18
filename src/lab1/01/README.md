# 实验一 多线程同步实验

## 实验目的

1. 掌握线程的概念及创建方法
2. 掌握线程互斥锁及条件变量同步机制
3. 掌握 POSIX 信号量机制
4. 掌握生产者消费者原理
5. 设计程序, 两种方法实现多线程生产者消费者同步问题

(备注: 至少包括两个生产者线程, 两个消费者线程. 各生产者线程放的数据需要不同, 例如: 生产者 1 放 1, 2, 3, 4, 生产者 2 放 -2, -4, -6, 或者 3, 6, 9, 12. 备注不写入实验报告)


## 实验原理

### 线程的概念

线程 ([thread][thread]) 是操作系统能够进行运算调度的最小单位. 它被包含在进程之中, 是进程中的实际运作单位. 一个线程指的是进程中一个单一顺序的控制流, 一个进程中可以并发多个线程, 每条线程并行执行不同的任务. 

线程是独立调度和分派的基本单位. 同一进程中的多个线程将共享该进程中的全部系统资源, 如虚拟地址空间, 文件描述符和信号处理等等. 但同一进程中的多个线程有各自的调用栈 (call stack), 自己的寄存器环境 (register context), 自己的线程本地存储 (thread-local storage).

一个进程可以有很多线程, 每个线程并行执行不同的任务. 在多核或多 CPU, 或支持 Hyper-threading 的 CPU 上使用多线程程序设计的好处是显而易见, 即提高了程序的执行吞吐率. 在单 CPU 单核的计算机上, 使用多线程技术, 也可以把进程中负责 I/O 处理, 人机交互而常被阻塞的部分与密集计算的部分分开来执行, 编写专门的线程执行密集计算, 从而提高了程序的执行效率. 

### pthreads 和 libpthread

[POSIX threads][pthreads], 通常以 **pthreads** 为人所知, 是一种独立于编程语言的线程执行模型 (或者称 "并发模型"). 它使得程序可以在同一时间控制多个不同的工作流. 每个工作流就是一个 "线程 ([thread][thread])", 而程序对于这些工作流的创建和控制, 则是通过对 [POSIX][posix] Threads API 的调用来实现. 通常, POSIX 兼容的类 Unix 系统都会提供这些 API, 这些系统通常会包含一个 **libpthread** 库. [^pthreads-wikipedia]

**pthreads** 定义了一系列 C 语言的类型, 函数和常量, 在 `pthread.h` 和对应的线程库中实现. 有大约 100 中线程相关的过程 (procedure), 均以 `pthred_` 开头, 并且可以分为以下几组:

- 线程管理 -- 线程的创建, 收集 (join) 等等.
- 互斥量
- 条件变量
- 使用读写锁实现的线程同步

POSIX 信号量 (semaphore) 的 API 可以与 POSIX threads 协同使用, 但并不在线程的标准之中. 这些和信号量相关的函数通常以 `sem_` 开头, 而非 `pthread_`.

下面是一些关于线程的概念 [^pthread-programming]:

- 线程并不会保存自己已经创建的线程, 也不知道创建自己的线程;
- 同一进程内的线程共享相同的地址空间;
- 每个线程都有独立的线程 ID, 寄存器环境, 调用栈, 优先级等等;
- pthread 库函数返回 0 表示成功.


[^pthreads-wikipedia]: 翻译自 [Wikipedia 上的 "pthreads" 词条][pthreads]

[^pthread-programming]: 翻译自 [Linux Tutorial: POSIX Threads](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html)


[pthreads 入门教程](https://hanbingyan.github.io/2016/03/07/pthread_on_linux/)

## 实验程序


程序代码

## 实验截图及结果分析




## 实验心得




[thread]: https://en.wikipedia.org/wiki/Thread_(computing) "Thread (computing) - Wikipedia"

[pthreads]: https://en.wikipedia.org/wiki/Pthreads "pthreads - Wikipedia"

[posix]: https://en.wikipedia.org/wiki/POSIX "POSIX - Wikipedia"
