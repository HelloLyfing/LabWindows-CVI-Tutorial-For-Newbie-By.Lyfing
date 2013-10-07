[上一篇][previous-tutorial]中我们讲了如何**使用界面编辑器**创建一个Graph控件，并通过绑定代码在它上面显示Sine波和Cosine波。  

本篇虽然仍要创建Graph，不过所有的图形创建工作都将由**代码**完成。也就是说，从头到尾，你无需再借助界面编辑器来完成创建控件、设置属性、绑定回调函数等工作，上述内容都将在一个**.c**文件中由代码来实现。  

而且说实在的，授人以鱼不如授人以渔。这个系列教程不可能从零开始详尽介绍各个控件、内建函数的使用方法，一来确实内容太多，无力一一详述；二来这些东西本就在**官方文档**中有足够详尽的使用说明，自己再来赘述反倒没有意义。**此系列教程更多的意义在于**：在引导新手慢慢上手、熟悉Labwindows开发环境的同时，教会新手自己查阅帮助文档解决问题，最终达到新手可以自己查找帮助文档解决问题的目的。我想教会人用字典比每个字手把手教更有意义，对吧？因此从本篇开始会侧重介绍帮助文档的使用。

本篇任务：  

+ 用代码在主面板上创建一个Graph控件；
+ **显示波形按钮**、**清除波形按钮**；
+ 开始尝试从帮助文档中寻找解决问题的答案或方案

效果图：

------
#### 1. New Project(新建工程)  
如何新建工程？  

 + 打开LabWindows/CVI程序后，如果弹出如下页面(启动页)。则通过选择**New**版块的**Project**选项即可新建工程

 + ![Startup-page.png]()

 + 如果打开程序后直接看到的是程序主界面，则直接通过菜单栏 **File** >> **New** >> **Project(*.prj)** 即可新建工程  

在之后弹出的**New Project Options**对话框中，保留系统默认选项，直接点击**OK**即可  

#### 2. New Source File(新建.c代码源文件)

通过菜单栏依次选择 **File** >> **New** >> **Source(*.c)** 即可新建代码源文件  

此时需要保存一下我们新建的工程，通过菜单栏依次选择**File** >> **Add Untitled1.c to project**(添加代码源文件到工程中)，此时会弹出如下对话框(LabWindows/CVI Message)

![You-must-name-.c-file-name-before-using-it.png]()  

对话框内容为：代码源文件只有在命名后才可以被添加到Project中，所以你需要首先给代码源文件命名并选择其存储位置，我们把它保存在任意位置的**project3**文件夹下，并将其命名为 *src3.c*。 

此时新建工程及其系列文件(源代码文件、用户界面文件、配置文件等)都将被自动命名为 *src.后缀*

#### 3. 在.c代码文件中添加main()函数
我们知道LabWindows/CVI使用的c语言作为编程语言，而c语言中的 `main()` 函数则是整个程序的入口，所以我们首先为源代码文件添加 `main()` 函数*(下面的 `main()` 函数代码由系统根据用户界面文件(***.uir**)自动生成，算是LabWindows/CVI程序的 `main()` 函数的原始框架，最好把它复制到源代码文件中，不推荐手敲。下面会详细解释这个main()函数的默认运行机制)*

<code>代码片段1</code>

关于上面的`main()`函数：

<code>代码片段2</code>

话虽如此，还是简单介绍一下main()函数的运行流程吧：  

 1. 首先使用`InitCVIRTE (0, argv, 0)`函数进行系统初始化；
 2. 接着开始**选择**并**载入**图形界面(主面板)文件，准备显示图形。这一步的一种通用做法是：`panelHandle = LoadPanel (0, "src.uir", PANEL))` ，即用 `LoadPanel()` Lab自带函数载入你之前已经创建好的图形界面描述文件(**.uir**文件或**.tui**文件，看看本系列教程中上两章所创建的工程，其中都带有**.uir**图形界面描述文件)，并在载入后将该面板资源在系统内存中的**句柄**(handle)交给(赋值给)我们之前创建的全局变量 `panelHandle` 。但是本章教程中并没创建图形界面描述文件，因为我们是要用纯代码实现创建图形控件并使其发挥一定功用。
 3. `DisplayPanel (panelHandle)` | 上一步，我们载入图形界面描述文件，并获得了其在系统内存中的句柄(即 `panelHandle` )，这一步便是将这个图形界面显示出来。使用 `DisplayPanel()` 函数可以完成此项工作
 4. `RunUserInterface()` 将开始运行图形界面，并将捕获到的用户事件(events)分发给回调函数。我们来看看 `RunUserInterface` 的使用说明。在 `RunUserInterface` 上按F1(或在打开的**NI LabWindows/CVI Help**面板的左侧，点击**索引(N)**标签，然后在搜索框中输入 `RunUserInterface` 后回车。在**用途**(Purpose)部分，我们看到这样一段话：*RunUserInterface does not return until you call QuitUserInterface from within a callback function. RunUserInterface returns the value that you pass to QuitUserInterface.* 也就是说 `RunUserInterface()` 一旦执行，它不会立即返回(return)，所以跟在它后面的代码也就不会立即执行。那么这个函数何时才会返回呢？**直到你主动在某个`回调函数`中调用 `QuitUserInterface()` 函数**， `RunUserInterface()` 才会返回，而且它的返回值是你传入 `QuitUserInterface()` 的参数。PS：`QuitUserInterface()` 一般出现在**系统退出按钮**或**主面板右上角的"x"关闭按钮**的回调函数中。
 5. `DiscardPanel (panelHandle)` | 载入到系统内存中的图形界面资源，必须在系统退出前被清理掉，以防止程序给PC内存留下太多垃圾。`DiscardPanel (panelHandle)` 便是做此项工作的，按F1查看它的使用说明，它的用途(Purpose)部分写到：*Removes a panel and any of its child panels from memory and clears them from the screen if visible.You must call DiscardPanel from the thread in which you create the panel.* 即：*将一个面板(panel)及其所有的子面板(child panel,面板可以有父子关系)从内存中移除；如果它们正显示在屏幕上，则清除这些图像。而且你必须在创建面板的线程中(多线程范畴)调用`DiscardPanel()`*
 6. `return 0` 退出 `main()` 函数，程序运行结束。  

LabWindows/CVI程序的main()函数的运行机制基本如此。当然只要不颠倒上述几个部分的顺序的话，你可以在 `main()` 函数的任意位置添加任意有逻辑的代码。下一节我们将从修改上述 `main()` 函数着手，编写本章内容需要的 `main()` 函数。

#### 4. 开始编写main()函数
上一节我们只是从其他地方复制了一份LabWindows/CVI程序的 `main()` 函数框架，但它并不能满足我们的需求，我们需要在此基础上修改它。

1) 第一步不改动原框架，使用 `InitCVIRTE()` 函数进行系统初始化

    if ( InitCVIRTE(0, argv, 0) == 0 ) 
        return -1;  /* out of memory */

2) 原框架的第二步是：   

    panelHandle = LoadPanel (0, "src.uir", PANEL))

即*使用Lab自带函数 `LoadPanel()` 载入用户之前创建的图形界面描述文件(**.uir**/**.tui**)*，但我们要自己用代码创建图形界面的，**所以这一步的内容改为**：  

    panelHandle = createGUI_Mine() # GUI = Graphic User Interface

`createGUI_Mine()` 是我们自己编写的函数，它的作用是创建一个面板，并将创建好的面板资源的句柄(handle)返回(return)。为了与Lab系统自带函数区别开来，我们在函数名之后添加了 `_Mine` 标记（*其实这个标记可有可无*）。  

3) 剩余部分跟源框架保持一致：

    DisplayPanel (panelHandle);
    RunUserInterface ();
    DiscardPanel (panelHandle);
    return 0;


[previous-tutorial]:http://hellolyfing.sinaapp.com/labwindowscvi-tutorial-2-create-a-graph-show-sine-cosine-wave-on-it/
[the-2nd-part]:
