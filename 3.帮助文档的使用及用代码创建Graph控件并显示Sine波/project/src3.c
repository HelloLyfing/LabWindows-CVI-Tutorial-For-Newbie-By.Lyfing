#include <ansi_c.h>
#include <analysis.h>
#include <utility.h>
#include <cvirte.h>     
#include <userint.h>

/* 全局变量声明 */
static int panelHandle;
int graphHdl, showBtn, quitBtn; 

/* 函数原型声明 */
int createGUI_Mine(void);
int CVICALLBACK ButtonsResponse(int handle, int control, int event, void *callbackdata, int eventdata1, int eventdata2);

/* main()函数 */
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
	int pHandle = NewPanel(0, "用代码创建的图形界面", VAL_AUTO_CENTER, VAL_AUTO_CENTER, 300, 600);
	graphHdl = NewCtrl(pHandle, CTRL_GRAPH, "Created-Graph", 30, 250);
	showBtn = NewCtrl(pHandle, CTRL_SQUARE_COMMAND_BUTTON, "Show", 80, 50);
	quitBtn = NewCtrl(pHandle, CTRL_SQUARE_COMMAND_BUTTON, "Quit", 140, 50);
	InstallCtrlCallback(pHandle, showBtn, ButtonsResponse, 0);
	InstallCtrlCallback(pHandle, quitBtn, ButtonsResponse, 0);
	return pHandle;
}

int CVICALLBACK ButtonsResponse(int handle, int control, int event, 
				void *callbackdata, int eventdata1, int eventdata2){
	if (control == showBtn) { //如果事件发生在show按钮上
		switch (event) {
			case EVENT_COMMIT:
				char temp[8]="" ; GetCtrlAttribute(panelHandle, showBtn, ATTR_LABEL_TEXT, temp);
				DeleteGraphPlot(panelHandle, graphHdl, -1, VAL_IMMEDIATE_DRAW);
				if (strcmp(temp, "Show") == 0 ){
					//单击按钮时作出的响应
					double waveData[100], amp, phase, cycles;
					int n;
					n = 100;
					amp = 90.0;
					phase = 0.0;
					cycles = 1.5;
					SinePattern(n, amp, phase, cycles, waveData);
					PlotY(panelHandle, graphHdl, waveData, n, VAL_DOUBLE, VAL_THIN_LINE, 
						  VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS , VAL_YELLOW);
					SetCtrlAttribute(panelHandle, showBtn, ATTR_LABEL_TEXT, "Clear");
				}
				else{
					SetCtrlAttribute(panelHandle, showBtn, ATTR_LABEL_TEXT, "Show");
				}
				break;
		}
	}
	
	if (control == quitBtn) { //如果事件发生在quit按钮上
		switch (event) {
			case EVENT_COMMIT :
				//单击按钮时作出的响应
				QuitUserInterface(0);
				break;
		}
	}
	return(0);
}
