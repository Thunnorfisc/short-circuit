#include "cprocessing.h"
#include "mainMenuSystem.h"

/*
* ---------------------------------
     ! NOT TO BE TOUCHED !
Inform the team if need to change
-----------------------------------
*/
int main(void)
{
	CP_System_SetWindowSize(1280, 720);
	CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	CP_Engine_Run(0);
	return 0;
}