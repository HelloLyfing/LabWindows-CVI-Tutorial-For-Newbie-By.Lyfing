/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2013. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_COMMANDBUTTON_3            2       /* control type: command, callback function: quitSystem */
#define  PANEL_COMMANDBUTTON_2            3       /* control type: command, callback function: showCosineWave */
#define  PANEL_COMMANDBUTTON              4       /* control type: command, callback function: showSineWave */
#define  PANEL_GRAPH                      5       /* control type: graph, callback function: (none) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK quitSystem(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK showCosineWave(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK showSineWave(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
