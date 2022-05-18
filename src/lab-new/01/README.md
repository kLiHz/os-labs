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



## 实验程序

### 创建线程

pthread.h头文件中包含的几个基本概念及函数：
(1)pthread_t：. 

线程ID数据类型, 线程ID只在它所属的进程环境中有效

`pthread_create` 函数用于创建一个进程, 函数原型如下 [^pthreads-tutorial]:

```cpp
int pthread_create(pthread_t *new_thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
```

- 若成功创建新的线程, 函数将返回 0;
- 参数1: 传出参数, 用于保存成功创建线程之后对应的线程id. 
- 参数2: 传入线程的属性, 通常传 NULL, 表示不修改线程的属性. 
- 参数3: 传入一个指向函数的指针, 即待创建线程所执行函数的入口地址, 函数执行完毕, 则线程结束. 
- 参数4: 传入调用线程所执行函数时所使用的参数. 

调用 `pthread_join` 的线程将被阻塞, 直到对应线程终止. 

```cpp
int pthread_join(pthread_t thread, void **rval_ptr);
```

- 返回值:成功返回 0, 失败返回错误号
- 参数1: 回收线程的tid
- 参数2: 接收退出线程传递出的返回值

线程以不同的方法终止时, 通过 `pthread_join` 得到的终止状态是不同的, 总结如下:

- 如果 thread 线程通过 return 返回, `rval_ptr` 所指向的单元里存放的是 thread 线程函数的返回值. 
- 如果 thread 线程被别的线程调用 `pthread_cancel` 异常终止掉, `rval_ptr` 所指向的单元里存放的是常量 `PTHREAD_CANCELED`. 
- 如果 thread 线程是自己调用 `pthread_exit` 终止的, `rval_ptr` 所指向的单元存放的是传给 `pthread_exit` 的参数. 

如果 thread 线程的终止状态不感兴趣, 可以传 `NULL` 给 `rval_ptr` 参数. 

简单的示例程序 [thread_creation.c](./thread_creation.c): 

```cpp
{{#include ./thread_creation.c}}
```

需要注意, 编译文件时需要使用链接选项 `-lpthread`:

```console
$ cc thread_creation.c -lpthread
$ ./a.out
Thread 1 
Thread 2 
```

进程的结束一般有以下几种情况.

- 线程的任务完成, 即线程所执行的函数正常 `return`;
- 线程调用了 `pthread_exit` 函数;
- 其他线程调用 `pthread_cancel` 结束这个线程;
- 进程调用 `exec()` 或 `exit()`; 
- `main` 函数先于线程执行结束, 且 `main` 没有等待线程完成任务.

需要注意, 一个线程结束, 并不意味着它的所有信息都已经消失.

### 线程互斥锁

## 实验截图及结果分析




## 实验心得




[thread]: https://en.wikipedia.org/wiki/Thread_(computing) "Thread (computing) - Wikipedia"

[pthreads]: https://en.wikipedia.org/wiki/Pthreads "pthreads - Wikipedia"

[posix]: https://en.wikipedia.org/wiki/POSIX "POSIX - Wikipedia"

[^pthreads-tutorial]: 摘自 [pthreads 入门教程](https://hanbingyan.github.io/2016/03/07/pthread_on_linux/)

[C 语言 pthread 多线程并行程序设计入门教学与范例 - G. T. Wang](https://blog.gtwang.org/programming/pthread-multithreading-programming-in-c-tutorial/)
