#####上接[第一节][the-1st-part]的内容，我们继续本节内容的下半部分。  

#### 5. 编写 `createPanel_Mine()` 函数的具体实现
`createPanel_Mine()`要完成的工作有：

 + 创建一个主面板(即窗口)
 + 在主面板右侧创建一个Graph控件，用以显示Sine波形
 + 在主面板上创建两个按钮，并分别为他们编写回调函数以实现：

    + "Show"按钮：点击后Graph控件上显示出Sine波形，点击后按钮名称变为"Stop"；再次点击该按钮，Graph控件上的Sine波形被清空，按钮名称变回"Show"
    + "Quit"按钮：点击后退出程序

1) 创建主面板  
LabWindows/CVI提供了一系列可创建各种可视化界面的函数和API，创建面板(Panel)的函数当然也包含其中，但它具体是什么，又应该怎么用呢？我们试着从帮助文档中找寻答案。  
打开帮助文档(在LabWindows/CVI的任意界面**按F1快捷键**，或者从菜单栏 **Help** >> **Contents F1**打开)，在**索引**标签栏下的搜索框中输入*Panel*，在列出的一堆搜索结果中寻找 `panels (User Interface Editor)` 项，再接着找它的子项 `programming with`，双击打开它(**如下图所示**)：  

![F1-Content-Programming-with-Panels.png]()  

PS : *想要查找某个控件的创建或相关的操作函数的话，可以试着在**索引**标签下输入它的名称，找到它的使用介绍项 `object name (User Interface Editor)`以寻找相关帮助资料*  

在**Programming with Panels**的帮助文档页面，我们看它的第二段话 

 > *NewPanel* creates a new panel during program execution. NewPanel returns a handle that you use in subsequent User Interface Library functions to reference the panel. Use the first parameter of NewPanel to specify whether the panel is created as a top-level window or as a child of another (parent) window. You also specify the name, position, and size of the panel through parameters to NewPanel. Creating a new panel using NewPanel does not automatically display the panel. 

 这次请自行读完上面的关于 `NewPanel()` 函数的使用介绍，下面我们将直接使用它。如何使用？请在**索引**标签栏下的搜索框中输入 `NewPanel` 打开这个函数的帮助文档。  
 简单介绍一下，`NewPanel()` 函数可以创建一个主面板(*top-lever panel*)，或一个子面板(*child panel*)，这取决于你给它传入的参数。在这里我们要创建一个*主面板*，它的各项参数如下：  

 + 面板名称(panelTitle[])：用代码创建的图形界面
 + 面板的位置及大小(单位:像素)：距屏幕顶部**60**，距屏幕左边**300**，高度**500**,宽度**600**

好了，我们现在可以创建一个主面板了：
    
    # 为了使创建的主面板居中显示，距屏幕顶部和左边的距离都被换成了系统内部的整型变量VAL_AUTO_CENTER
    NewPanel(0, "用代码创建的图形界面", VAL_AUTO_CENTER, VAL_AUTO_CENTER, 500, 600)

好了，现在我们整个的代码看起来应该是这个样子：

    代码片段-3

**好了，到了这一步，先让我们试运行一下上面的程序吧**。运行程序(*Debug ***.exe*)的方法有三种：  

 1. 菜单栏 **Run** >> **Debug src.exe**
 2. 按快捷键组合 **Shift** + **F5**
 3. 鼠标点击如下按钮

![Button-Debug-Project.png]()

这时会弹出一个错误框，如下图所示：

![Error-Content-Missing.prototype.(Require.function....png]()

这是因为在LabWindows/CVI中，所有自定义的函数都是需要预定义，也就是得在 `main()` 函数之前声明原型(prototype)的。  
这好办，只需要把这两个**自定义函数的*原型声明*添加到 `main()` 函数之前**就可以了。**但问题是，如何声明原型？**这里最简单的方法是，随便到帮助文档中找一个工程样例(sample)，看看里面的自定义函数的原型声明的句式便可。

PS：*工程样例（sample）是LabWindows/CVI提供的用来演示如何使用某个控件或函数的可直接编译、运行的程序。**工程样例（sample）是快速入门LabWindows/CVI的编程格式及方法的大好捷径，一有机会就打开查看，有百利而无一害。**如何打开一个工程样例？以 `NewPanel()` 函数为例，当你在帮助文档中查找到 `NewPanel()` 函数的文档介绍页后，跳到这个页面的最底端，一般会附上若干工程样例，只需用鼠标单击"Open example"前的图标便可打开，下图所示：*  

![NI_Help_How-To-Use-Project-Example.png]()  



    


[the-1st-part]:









