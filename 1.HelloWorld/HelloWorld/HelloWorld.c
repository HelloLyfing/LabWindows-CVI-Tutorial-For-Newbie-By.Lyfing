#include <cvirte.h>		
#include <userint.h>
#include "HelloWorld.h"

static int panelHandle;

int main (int argc, char *argv[]) {
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "HelloWorld.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK OK_Btn_Callback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_COMMIT:
			char title[30] = "I'm the title!";
			char msg[100] = "Hello World !";
			MessagePopup(title, msg);
			break;
	}
	return 0;
}

int CVICALLBACK Quit_Btn_Callback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}
