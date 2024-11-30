/* .--------------------------------------------------------------. */
/* |   _____ __               __     _______                 _ __ | */
/* |  / ___// /_  ____  _____/ /_   / ____(_)___________  __(_) /_| */
/* |  \__ \/ __ \/ __ \/ ___/ __/  / /   / / ___/ ___/ / / / / __/| */
/* | ___/ / / / / /_/ / /  / /_   / /___/ / /  / /__/ /_/ / / /_  | */
/* |/____/_/ /_/\____/_/   \__/   \____/_/_/   \___/\__,_/_/\__/  | */
/* '--------------------------------------------------------------' */
/*
File: main.c
Author: Jason Teo Jun Hao (jasonjunhao.teo)
Sub-Authors: 
Kelly Chiang Kar Yan (chiang.k)
William Wibisana Dumnanauw (williamwibisana.d)
Lim Yan De (l.yande)
Ong Wei Song (weisong.ong)

Description:
This file is the main file of the game

 * All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
*/

#include "cprocessing.h"
#include "mainMenuSystem.h"

/*
* ---------------------------------
*      ! NOT TO BE TOUCHED !
* Inform the team if need to change
* ---------------------------------
*/
int main(void)
{
	CP_System_SetWindowSize(1280, 720);
	CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	CP_System_SetFrameRate(144.0f);
	CP_Engine_Run(0);
	return 0;
}