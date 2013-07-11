#include <analysis.h>
#include <cvirte.h>		
#include <userint.h>
#include "2-Using-Graph-Demo.h"

static int panelHandle;

int main (int argc, char *argv[]) {
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "2-Using-Graph-Demo.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK showSineWave (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch(event){
		case EVENT_COMMIT:
			DeleteGraphPlot(panelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			
			double waveData[100], amp, phase, cycles;
			int n;
			n = 100;
			amp = 90.0;
			phase = 0.0;
			cycles = 1.5;
			SinePattern(n, amp, phase, cycles, waveData);
			
			PlotY(panelHandle, PANEL_GRAPH, waveData, n, VAL_DOUBLE, VAL_THIN_LINE, 
				  VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS , VAL_YELLOW);
			break;
	}
	return 0;
}

int CVICALLBACK showCosineWave (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event){
		case EVENT_COMMIT:
			DeleteGraphPlot(panelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			
			double waveData[100], amp, phase, cycles;
			int n;
			n = 100;
			amp = 90.0;
			phase = 90.0;
			cycles = 1.5;
			SinePattern(n, amp, phase, cycles, waveData);
			
			PlotY(panelHandle, PANEL_GRAPH, waveData, n, VAL_DOUBLE, VAL_THIN_LINE, 
				  VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS , VAL_YELLOW);
			break;
	}
	return 0;
}

int CVICALLBACK quitSystem (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2) {
	switch (event) {
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

