#####上接[第一节][the-1st-part]的内容，我们继续本章内容的下半部分。  

#### 5. 编写 `createGUI_Mine()` 函数的具体实现
`createGUI_Mine()`要完成的工作有：

 - 创建一个主面板(即主窗口)
 - 在主面板右侧创建一个Graph控件，用以显示Sine波形
 - 在主面板上创建两个按钮，并分别为他们编写回调函数以实现：

    - "Show"按钮：点击后Graph控件上显示出Sine波形，点击后按钮名称变为"Clear"；再次点击该按钮，Graph控件上的Sine波形被清空，按钮名称变回"Show"
    - "Quit"按钮：点击后退出程序

##### 1) 创建主面板  
LabWindows/CVI提供了一系列可创建各种可视化界面的函数和API，创建面板(Panel)的函数当然也包含其中，但它具体是什么，又应该怎么用呢？我们试着从帮助文档中找寻答案。  
打开帮助文档(在LabWindows/CVI的任意界面**按F1快捷键**，或者从菜单栏 **Help** >> **Contents F1**打开)，在**索引**标签栏下的搜索框中输入*Panel*，在列出的一堆搜索结果中寻找 `panels (User Interface Editor)` 项，再接着找它的子项 `programming with`，双击打开它(**如下图所示**)：  

![F1-Content-Programming-with-Panels.png](http://ww2.sinaimg.cn/large/6480dca9jw1e9w7ha8bigj20ke0gk458.jpg)  

<div id='how-to-find-useage'></div>*PS：想要查找**某个控件object的使用说明**，可以试着在帮助文档 >> **索引**标签下的搜索框输入它的名称，在搜索结果中找到它的使用介绍项 `object_name (User Interface)`及其子项，以查找相关帮助资料；想要查找**某个具体函数的使用说明**，方法同上，一般搜索结果第一项便是*  

在**Programming with Panels**的帮助文档页面，我们看它的第二段话 

 > *NewPanel* creates a new panel during program execution. NewPanel returns a handle that you use in subsequent User Interface Library functions to reference the panel. Use the first parameter of NewPanel to specify whether the panel is created as a top-level window or as a child of another (parent) window. You also specify the name, position, and size of the panel through parameters to NewPanel. Creating a new panel using NewPanel does not automatically display the panel. 

 这次请自行读完上面的关于 `NewPanel()` 函数的使用介绍，下面我们将直接使用它。如何使用？请在**索引**标签栏下的搜索框中输入 `NewPanel` 打开这个函数的帮助文档。  
 简单介绍一下，`NewPanel()` 函数可以创建一个主面板(*top-lever panel*)，或一个子面板(*child panel*)，这取决于你给它传入的参数。在这里我们要创建一个*主面板*，它的各项参数如下：  

 + 面板名称(panelTitle[])：用代码创建的图形界面
 + 面板的位置及大小(单位:像素)：距屏幕顶部**60**，距屏幕左边**300**，高度**300**,宽度**600**

现在，我们可以创建一个主面板了：
    
    # 为了使创建的主面板居中显示，距屏幕顶部和左边的距离都被换成了系统内部的整型变量VAL_AUTO_CENTER
    NewPanel(0, "用代码创建的图形界面", VAL_AUTO_CENTER, VAL_AUTO_CENTER, 300, 600)

好了，现在我们整个的代码看起来应该是这个样子：

    #include <utility.h>
    #include <cvirte.h>     
    #include <userint.h>

    static int panelHandle;

    int createGUI_Mine(void);

    int main (int argc, char *argv[]){
        if (InitCVIRTE (0, argv, 0) == 0)
            return -1;  /* out of memory */
        if ((panelHandle = createGUI_Mine()) < 0)
            return -1;
        DisplayPanel (panelHandle);
        RunUserInterface();
        DiscardPanel (panelHandle);
        return 0;
    }

    int createGUI_Mine(){
        int pHandle = NewPanel(0, "用代码创建的图形界面", VAL_AUTO_CENTER, VAL_AUTO_CENTER, 600, 800);
        return pHandle;
    }

<div id="how-to-debug"></div>**OK，到了这一步，先让我们试运行一下上面的程序吧**。运行程序(*Debug ***.exe*)的方法有三种：  

 1. 菜单栏 **Run** >> **Debug src.exe**
 2. 按快捷键组合 **Shift** + **F5**
 3. 鼠标点击如下按钮

![Button-Debug-Project.png](http://ww3.sinaimg.cn/large/6480dca9jw1e9w7i9m65sj20hb037mxp.jpg)

这时会弹出一个错误框，如下图所示：

![Error-Content-Missing.prototype.(Require.function....png](http://ww1.sinaimg.cn/large/6480dca9jw1e9w7irfl81j20fh0eemz2.jpg)

这是因为在LabWindows/CVI中，所有自定义的函数都是需要预定义，也就是得在 `main()` 函数之前声明原型(prototype)的。  
这好办，只需要把这两个**自定义函数的*原型声明*添加到 `main()` 函数之前**就可以了。**但问题是，如何声明原型？**这里最简单的方法是，随便到帮助文档中找一个工程样例(sample)，看看里面的自定义函数的原型声明的句式便可。

*PS：工程样例（sample）是LabWindows/CVI提供的用来演示如何使用某个控件或函数的可直接编译、运行的程序。**工程样例（sample）是快速入门LabWindows/CVI的编程格式及方法的大好捷径，一有机会就打开查看，有百利而无一害。**如何打开一个工程样例？以 `NewPanel()` 函数为例，当你在帮助文档中查找到 `NewPanel()` 函数的文档介绍页后，跳到这个页面的最底部，一般会附上若干工程样例，只需用鼠标单击"Open example"前的图标（如下图所示）便可打开这个叫做"userint\buildui.cws"的工程样例。* 

![NI_Help_How-To-Use-Project-Example.png](http://ww1.sinaimg.cn/large/6480dca9jw1e9w7j7i5p8j20jk0au0uh.jpg)  

在打开的"buildui.cws"工程样例中，我们点击**buildui.c**文件，找到

    /*------------------------------------------------*/
    /* Internal function prototypes                   */
    /*------------------------------------------------*/ 

区域，根据这个区域下方的自定义函数的原型声明的方法，我们可以看出，对自定义函数的原型声明其实很简单，只需要把这个函数在左大括号——**{**——之前的内容复制到这里，并在结尾添加行结束标志分号——**；**——即可。不过需要注意的一点是，无参数的函数，在原型声明时需要它在接收参数的括号**()**中加入 `void` 关键字。具体到本例中，对自定义函数的原型声明句子如下所示：
    
    int createGUI_Mine(void);

好了，把如上内容添加到main()函数的前面，然后再次试运行这个程序，这时会弹出我们刚刚用代码创建的那个图形界面，它目前还只是一个只有标题栏的空白面板(Panel)。效果图如下：

![Demo-用代码创建的图形界面.png](http://ww1.sinaimg.cn/large/6480dca9jw1e9w7jq97gjj20h409e3yo.jpg)  

<div id='how-to-exit-debug-forcely'></div>由于还没设置退出选项，所以这个程序无法正常退出。我们可以到启动它的LabWindows/CVI中关闭它：跳转到LabWindows/CVI界面，点击菜单栏 **Running** >> **Terminate Execution**即可（或点击工具栏的**stop**按钮）。

##### 2)在主面板右侧创建一个Graph控件，用以显示Sine波形
在创建Graph控件前，请先想一下这两个问题：  

 1. Graph控件是依附于哪个实体之上的，它的载体是什么？
 2. Graph控件的创建工作应该被放在哪个部分？**main()**函数中、**createGUI_Mine()**函数中，或者其他地方？

是不是这样的:

 - 问题1：像其他的应用软件一样，控制类、显示类的控件都应该至少依附于一个面板(窗口)之上，也就是说这些控件得有个**载体**。在本章中，Graph控件及其他两个按钮控件(有待创建)都是依附于我们上一步创建的主面板(主界面基本元素)之上的。  
 - 问题2：光从名字我们便可以看出，`createGUI_Mine()` 函数就是用来完成创建图形界面元素的工作的，所以Graph控件的创建应该被安排到这里。  

*PS：在这里讲**载体**的概念，是为了之后创建Graph控件时更易理解传入`pHandle`的原因，就是因为所有的控件都需要一个载体(如面板)*  

接下来的问题，Graph控件应该如何创建呢？不知道你发现没，这个问题跟我们上一小节的关于"如何创建一个面板(panel)"的问题非常相似，所以，请你首先试着自己花时间去帮助文档中查找答案(到帮助文档中查找答案的习惯对日后的独立开发有极大帮助，请务必亲试)。  

在帮助文档页，**索引**标签栏下的搜索框中输入*Graph*，如上一小节查找创建Panel时一样，在搜索结果中我们会找到如下部分的内容：

    graph controls (user interface)
       attribute
       events
       fuctions
       operating
       programming with  

我们尝试从*programming with*这个页面查找新建graph控件的方法，结果没什么收获。但你看到了，graph control(Graph控件)有一个*functions*页面，这里面列出了跟本控件有关的所有函数，我们点进去看看。  
我们要找到的是创建控件的函数，所以函数名应该会带有*New*字样，对函数列表逐一查找，便会发现 `NewCtrl()` 这个函数。对了！就是用它来创建Graph控件的。打开这个函数的帮助页(如何[打开?](#how-to-find-useage))，你会发现，这个函数不光能用来创建Graph控件，它还可以创建LabWindows/CVI提供的其他所有控件([点此查看][ctrls-list]控件支持列表)。  

关于`NewCtrl()`函数的用法请自信查看帮助文档。我们这里要创建一个Graph控件，进入 `NewCtrl()` 函数帮助页，把第二行的函数结构复制下来：  

    int NewCtrl (int panelHandle, int controlStyle, char controlLabel[], int controlTop, int controlLeft);

把它插入到 `createGUI_Mine()` 函数的第二行：

    int createGUI_Mine(){
        int pHandle = NewPanel(0, "用代码创建的图形界面", VAL_AUTO_CENTER, VAL_AUTO_CENTER, 600, 800);
        int NewCtrl (int panelHandle, int controlStyle, char controlLabel[], int controlTop, int controlLeft);        
        return pHandle;
    }
 
 - `NewCtrl()`创建好Graph控件后，会返回这个Graph控件的资源句柄(handle)，我们创建一个int型变量`graphHdl`来接收返回值；
 - 参数方面，int型的*panelHandle*就用上一步生成的面板资源句柄(pHandle)赋值，即用上一步创建的面板做它的"载体"；
 - int型的*controlStyle*：欲创建的控件类型，通过查函数的使用帮助可知，要想创建Graph控件，此处应填 *CTRL_GRAPH*；
 - char型的*controlLabel[]*：Graph的标签，相当于控件标题，此处使用"Created-Graph"；
 - int型的*controlTop*及*controlLeft*：该控件相对于它的**载体**的位置，*top*给个*30*，*left*给个*250*

 *PS：在编程领域，当需要确定一个矩形框的位置时，我们一般只需要指定它左上角那个点相对于它载体的位置即可，然后再分别给这个矩形框赋予长度和高度值。由于左上角位置已确定，长度、高度也已确定，这个矩形框的大小，及它相对于自身载体的位置便唯一确定了。这就好比在一面墙上画一个矩形，先确定它离墙的顶端和左端的距离（即它左上角点的位置），再已知长度、高度的话，从该点出发依次画出长和高，这个矩形在墙上的最终形状及位置便可以确定下来了。*

于是`createGUI_Mine()`函数修改为：

    int createGUI_Mine(){
        int pHandle = NewPanel(0, "用代码创建的图形界面", VAL_AUTO_CENTER, VAL_AUTO_CENTER, 600, 800);
        int graphHdl = NewCtrl(pHandle, CTRL_GRAPH, "Created-Graph", 30, 250);     
        return pHandle;
    }

试运行一下程序([how?](#how-to-debug))，我们可以看到之前空空如也的面板上已经多出来一个graph了：

![Demo-添加了graph控件后的图形界面.png](http://ww4.sinaimg.cn/large/6480dca9jw1e9w7k54b76j20h009ct9e.jpg)


##### 3) 在主面板上创建两个按钮：*show*、*quit*并分别为他们编写回调函数以发挥各自功能
a. 创建按钮  

请读者想一想，应该用什么函数来创建这两个按钮呢？我给你个提示：按钮属于控件范畴~  

没错，就是使用`NewCtrl()`函数来创建以上两个按钮！创建工作将被而且应该被安排到`createGUI_Mine()`函数中，我们把它安排到Graph控件的创建之后。  

**show**按钮的图形参数，即填入`NewCtrl()`函数的参数列表：

 - *panelHandle* = *pHandle*，即把本函数第一句创建好的面板作为按钮的"载体"；
 - *controlStyle* = *CTRL_SQUARE_COMMAND_BUTTON*，即方形命令按钮，这个值通过查函数的使用方法可得；
 - *controlLabel[]* = *"show"*，即按钮上显示的文字；
 - *controlTop* = *80* ， *controlLeft* = *50*，即按钮相对于自己"载体"的上端和左端的位置

**quit**按钮的图形参数：

 - *panelHandle* = *pHandle*，即把本函数第一句创建好的面板作为按钮的"载体"；
 - *controlStyle* = *CTRL_SQUARE_COMMAND_BUTTON*，即方形命令按钮，这个值通过查函数的使用方法可得；
 - *controlLabel[]* = *"quit"*，即按钮上显示的文字；
 - *controlTop* = *140* ， *controlLeft* = *50*，即按钮相对于自己"载体"的上端和左端的位置

我们分别用整形变量 *showBtn*及*quitBtn*来接收创建按钮后返回的资源句柄，于是`createGUI_Mine()`函数更新为：

    int createGUI_Mine(){
        int pHandle = NewPanel(0, "用代码创建的图形界面", VAL_AUTO_CENTER, VAL_AUTO_CENTER, 300, 600);
        int graphHdl = NewCtrl(pHandle, CTRL_GRAPH, "Created-Graph", 30, 250);
        int showBtn = NewCtrl(pHandle, CTRL_SQUARE_COMMAND_BUTTON, "Show", 80, 50);
        int quitBtn = NewCtrl(pHandle, CTRL_SQUARE_COMMAND_BUTTON, "Quit", 140, 50);
        return pHandle;
    }

试运行一下程序，添加了两个按钮的界面如下图所示：

![Demo-添加了show-quit-按钮后的图形界面.png](http://ww3.sinaimg.cn/large/6480dca9jw1e9w7kikah0j20h009ejs5.jpg)

到目前为止，我们已经完成了所有界面元素的创建工作。

b. 为两个按钮编写回调函数

*PS：请读者首先到 帮助文档 >> 索引 标签栏 下的搜索框中输入`callback functions`然后回车以打开关于回调函数的使用说明页面，请大致浏览一下该页面内容。我在这里简单说一下，回调函数(callback functions)是你绑定到某个特定用户界面元素(比如面板、按钮、Graph控件)上，用以响应发生在该元素上的所有用户事件的函数。例如，你可以给*按钮A*绑定一个回调函数，并在该回调函数中编写所有可能发生的事件的应对策略，如*按下按钮时做动作1*、*按钮抬起时做动作2*、*单击按钮时做动作3*、*双击按钮时...*一旦任意一个事件在该元素上发生，LabWindows/CVI便开始调用(执行)这个回调函数，预先设定好的动作便会被触发。*

如何编写回调函数？在上面提到的那个帮助文档页(即*Using Callback Functions to Respond to User Interface Events*页面)，我们可以看到三个回调函数的使用样例代码，他们分别是*面板*、*控件*以及*菜单栏*这三种用户界面元素的回调函数使用样例。请读者想一下，上述三种样例，哪一个可以为我们所用？  

当然还是*控件*的那个样例(*ControlResponse*)。我们把下面的样例完整地拷贝到我们的*src.c*主程序中，将其放到`createGUI_Mine()`函数的下面：

    int CVICALLBACK ControlResponse (int handle, int control, int event, void *callbackdata, int eventdata1, int eventdata2){
        ...
    }

现在要做的对这个样例进行DIY改造。

 1. 将函数名`ControlResponse`改为更具体的`ButtonsResponse`（此改动可有可无）；
 2. 去除一些无关内容

精简后，两个按钮的回调函数变为：

    int CVICALLBACK ButtonsResponse(int handle, int control, int event, 
                void *callbackdata, int eventdata1, int eventdata2){
        if (control == showBtn) { //如果事件发生在show按钮上
            switch (event) {
                case EVENT_RIGHT_CLICK :
                    //右击按钮时作出的响应
                    break;
                case EVENT_COMMIT :
                    //单击按钮时作出的响应
                    break;
            }
        }
        
        if (control == quitBtn) { //如果事件发生在quit按钮上
            switch (event) {
                case EVENT_COMMIT :
                    //单击按钮时作出的响应
                    break;
            }
        }
        return(0);
    }

当有[用户事件][user-interface-events]发生在按钮上，LabWindows/CVI便会调用上面的回调函数，并在调用时将该控件的载体(*handle*)、控件资源句柄(即资源id-*control*)、发生的事件id(*event*)等信息作为参数传入该回调函数。

我们看到上面的回调函数用到了变量*showBtn*和*quitBtn*，不过这两个变量是在`createGUI_Mine()`函数中创建的（局部变量）。为了能全局引用这两个变量，我们需要在*函数原型声明*部分的上方声明这两个全局变量。鉴于Graph控件也需要全局引用，所以我们在*函数原型声明*部分的上方添加这样的声明：

    ...
    /* 全局变量声明 */
    static int panelHandle;
    int graphHdl, showBtn, quitBtn; 

    /* 函数原型声明 */
    int createGUI_Mine(void);

    /* main()函数 */
    ...

然后在创建Graph控件以及两个Button按钮的地方(即`createGUI_Mine()`函数内)，去掉变量名*graphHdl*、*showBtn*和*quitBtn*前面的*int*即可。

我们来编写**当事件发生在***showBtn***按钮上时的事件响应**：  

    if (control == showBtn) { //如果事件发生在show按钮上
        switch (event) {
            case EVENT_COMMIT :
                //准备一个temp数组，用来存放按钮上要显示的"show"或"stop"字符串
                char temp[8]="" ; GetCtrlAttribute(panelHandle, showBtn, ATTR_LABEL_TEXT, temp);
                //清空graph上的内容，准备画图
                DeleteGraphPlot(panelHandle, graphHdl, -1, VAL_IMMEDIATE_DRAW);
                if (strcmp(temp, "Show") == 0 ){ //如果按钮显示的是"Show"的话
                    //准备波形数组
                    double waveData[100], amp, phase, cycles;
                    int n;
                    n = 100;
                    amp = 90.0;
                    phase = 0.0;
                    cycles = 1.5;
                    SinePattern(n, amp, phase, cycles, waveData);
                    //将波形数组填充到graph图表上
                    PlotY(panelHandle, graphHdl, waveData, n, VAL_DOUBLE, VAL_THIN_LINE, 
                          VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS , VAL_YELLOW);
                    SetCtrlAttribute(panelHandle, showBtn, ATTR_LABEL_TEXT, "Clear");
                }
                else{ //如果按钮显示的是"Clear"的话
                    SetCtrlAttribute(panelHandle, showBtn, ATTR_LABEL_TEXT, "Show");
                }
                break; 
        }
    }

接着编写**当事件发生在***quitBtn***按钮上时的事件响应**：

    if (control == quitBtn) { //如果事件发生在quit按钮上
        switch (event) {
            case EVENT_COMMIT :
                //单击按钮时作出的响应
                QuitUserInterface(0);
                break;
        }
    }

由于我们的回调函数`ButtonsResponse()`也是自定义函数，所以需要添加**函数原型声明**，读者还记得**在哪里**以及**如何添加**函数原型声明吗？

    ...
    /* 函数原型声明 */
    int createGUI_Mine(void);
    int CVICALLBACK ButtonsResponse(int, int, int, void, int, int);
    ...

最后一步，为按钮指派(安装)回调函数。

也许读者会有疑问：我们不是已经写好回调函数了吗？怎么还要指派(安装)回调函数？事实是：我们虽然已经写好了回调函数，但这个函数和具体控件之间仍是没有任何联系的。指派(安装)回调函数便是为两者建立关联的过程。

为某个控件指派(安装)回调函数用的是`InstallCtrlCallback()`这个函数，它的函数结构为：
    
    InstallCtrlCallback (int panelHandle, int controlID, CtrlCallbackPtr eventFunction, void *callbackData);

在使用时，你需要传入控件所属载体的资源句柄(*panelHandle*)、控件本身的资源句柄(*controlID*)、控件欲绑定的回调函数(*eventFunction*)以及在调用该回调函数时欲传给该函数的数据( **callbackData*)。特别注意的是，回调函数*eventFunction*的类型是*CtrlcallbackPtr*的，这一类型的函数，都必须遵循以下的函数声明结构：

    int CVICALLBACK CallbackFunctionName (int panelHandle, int controlID, int event, void *callbackData, int eventData1, int eventData2);

这也就是为什么我们的`ButtonsResponse()`函数的前面会有一个全大写的`CVICALLBACK`标志了。

为**show**、**quit**按钮指派(安装)回调函数将在`createGUI_Mine()`函数中完成：

    InstallCtrlCallback(pHandle, showBtn, ButtonsResponse, 0);
    InstallCtrlCallback(pHandle, quitBtn, ButtonsResponse, 0);

至此，所有工作已经完成，快快试运行一下你的程序吧！

*****
程序源码[托管在Github][github]上，请自行前往查看。

[the-1st-part]:http://lanfengming.com/?p=167
[ctrls-list]:http://zone.ni.com/reference/en-XX/help/370051V-01/cvi/uiref/cvioperating_controls/
[user-interface-events]:http://zone.ni.com/reference/en-XX/help/370051V-01/cvi/uiref/cvievents_overview/
[github]:https://github.com/HelloLyfing/LabWindows-CVI-Tutorial-For-Newbie-By.Lyfing
