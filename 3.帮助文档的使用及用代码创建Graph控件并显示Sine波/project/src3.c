#include <utility.h>
#include <cvirte.h>     
#include <userint.h>

static int panelHandle;

int createGUI_Mine(void);
int createMainPanel_Mine(void);

int main (int argc, char *argv[]){
    if (InitCVIRTE (0, argv, 0) == 0)
        return -1;  /* out of memory */
    panelHandle = createGUI_Mine();
    DisplayPanel (panelHandle);
    RunUserInterface();
	DiscardPanel (panelHandle);
    return 0;
}

int createGUI_Mine(){
	int pHandle = createMainPanel_Mine();
	
	return pHandle;
}

int createMainPanel_Mine(){
	int tempHandle = NewPanel(0, "用代码创建的图形界面", VAL_AUTO_CENTER, VAL_AUTO_CENTER, 600, 800);
	return tempHandle;
}
