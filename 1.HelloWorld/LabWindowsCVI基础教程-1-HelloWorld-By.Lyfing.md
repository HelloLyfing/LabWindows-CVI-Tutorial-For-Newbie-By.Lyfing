*前言：LabWindows/CVI是一款功能强大的集成了图形化界面编辑器以及对各种硬件通信协议支持的集成开发环境，它使用ANSI标准的C语言作为主要的编程语言。*  

编写该系列教程的原因：自己大学的毕设题目选的就是[基于LabWindows/CVI的信号监测系统开发][my_design]，自己当时的状态是：   

+ 对C语言基本不了解，不会用  
+ 对LabWindows/CVI完全不了解  

当时很想看一看中文的博客有没有相关的基础教程，这样一来自己也好尽快上手系统开发工作，谷歌百度后发现这些内容寥寥无几，无奈自己只好从看官方的英文帮助文档开始，一路摸索着完成了毕设项目的开发。但在查阅官方帮助文档的过程中我才发现，**对学习、使用LabWindows/CVI真正有帮助的**其实就是**阅读帮助文档**。虽然它是英文写成，却实在丰富全面，很多函数的使用方法说明下方都会附有样例工程，让你可以进一步了解如何使用这些函数，所以英文基础好的童鞋还是多看看官方帮助文档吧。
***** 
好了，闲话少说，我们今天就开始LabWindows/CVI的第一个工程：  
**1.Hello World.**  
具体内容：  
创建一个主面板（在LabWindows/CVI内部，Panel和Windows系统的窗口概念相当），在主面板上放置一个按钮，点击按钮，弹出消息"Hello world".
*****
1. 在LabWindows/CVI的开始界面，选择 Project >> New project，创建一个新工程
![](http://img.blog.csdn.net/20130620094251656)

2. 通过File >> New >> User Interface(*.uir)... 新建用户界面源文件文件
![](http://img.blog.csdn.net/20130620094312921)

3. 系统会自动创建一个"Untitled Panel",在该Panel(面板)的任意位置双击，打开**面板属性设置**窗口
4. 如图所示操作，把**Panel Title**改成**Hello World**. 然后_回车_或_点击确定_回到主Panel
![](http://img.blog.csdn.net/20130620094326671)

5. 在主Panel任意位置右击，在弹出的**控件列表**里选择 Command Button >> Square Command Button.  
![](http://img.blog.csdn.net/20130620094338281)

6. 主Panel上会出现一个**OK**按钮，双击该按钮打开**按钮属性设置**窗口。在**Callback function：**一栏填写"OK\_Btn\_Callback"(即Ok按钮的回调函数)。然后_回车_或_点击确定_回到主Panel  
![](http://img.blog.csdn.net/20130620093039000)

7. 用同样的方法再创建一个按钮(按钮可以通过Windows的"复制-粘贴"快捷键快速创建)，双击该按钮打开**按钮属性设置**窗口，按顺序依次设置"Label"及"Callback function"的值。然后_回车_或_点击确定_回到主Panel  
![](http://img.blog.csdn.net/20130620094426234)

8. 在系统菜单栏，依次选择Code >> Generate >> All Code...来创建**控件对应的执行代码文件(.c)**。之后，在弹出的窗口依次点击"Yes""Ok"  
![](http://img.blog.csdn.net/20130620094436953)  
![](http://img.blog.csdn.net/20130620094409890)  
![](http://img.blog.csdn.net/20130620094418312)

9. 按图示内容设置配置目标C文件的内容  
![](http://img.blog.csdn.net/20130620094452156)  

10. 在弹出的**New Project Option**菜单点击**OK**.  
![](http://img.blog.csdn.net/20130620094459453)

11. 之后会弹出**HelloWorld.c**文件的编辑界面。**将光标定位到**OK\_Btn\_Callback()函数,在**switch(event)**语句的**case EVENT_COMMIT**和**break;**之间添加如下的代码


    switch (event) {  
        case EVENT_COMMIT:  
            char title[30] = "I'm the title!";  
            char msg[100] = "Hello World !";  
            MessagePopup(title, msg);  
        	break;  
    }
![](http://img.blog.csdn.net/20130620094512031)

12. 好了，一切准备工作都已就绪，我们试运行一下这个程序，点击如图所示的**Debug Project**按钮，运行程序吧！
![](http://img.blog.csdn.net/20130620094358046)
![](http://img.blog.csdn.net/20130620094523406)
*****
程序源码[托管在Github][github]上，请自行前往查看。

[my_design]:https://github.com/HelloLyfing/Signal_Monitor_System_Based_On_LabWindows-CVI
[github]:https://github.com/HelloLyfing/LabWindows-CVI-Tutorial-For-Newbie-By.Lyfing