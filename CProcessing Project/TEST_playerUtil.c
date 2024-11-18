#include "TEST_playerUtil.h"
#include "itemSystem.h"

#define PLAYER_STAT_TEMP_ADDR "Assets/temp_player_data.txt"
/*
Function   : PlayerStats_Calculate
Description: Takes in the inventory of the player and copies the current player stats to calculate the stats for battle
Parameters : Item inventory[], Player player
Return	   : void
*/
void PlayerStats_Calculate(Item inventory[], Player player) {
	int index = 0;

	while (inventory[index].id != 0) {
		switch (inventory[index].type)
		{
		case HEALTH:
			//calculate new player health stat
			player.health += (int)inventory[index].modifier;
			break;
		case MANA:
			//calculate new player s_mana stat
			player.s_mana += (int)inventory[index].modifier;
			break;
		case ATTACK:
			//calculate new player Attack stat
			player.attack += (int)inventory[index].modifier;
			break;
		case DEFENSE:
			//calculate new player Defense stat
			player.defense += inventory[index].modifier;
			break;
		case FIRE:
			//calculate new player Fire stat
			player.fire_crit += inventory[index].modifier;
			break;
		case WATER:
			//calculate new player Water stat
			player.water_crit += inventory[index].modifier;
			break;
		case GRASS:
			//calculate new player Grass stat
			player.grass_crit += inventory[index].modifier;
			break;
		default:
			break;
		}
		index++;
	}

	//Plug calculated player stats into function to write to temp file
	PlayerStats_Create_Temp(player);
}

/*
Function   : PlayerStats_Create_Temp
Description: Takes the calculated player stats and writes to a temp file that will be read in battle system to calculate damage
Parameters : Player modified_player
Return	   : void
*/
int PlayerStats_Create_Temp(Player modified_player) {

	FILE* const temp_player_stats_path = fopen(PLAYER_STAT_TEMP_ADDR, "w");

	if (temp_player_stats_path == NULL) {
		printf("Failed to read Temp Player Stat File: %s", PLAYER_STAT_TEMP_ADDR);
		return 0;
	}

	//check if data was read properly
	if (fprintf(temp_player_stats_path, "%f,%d,%d,%lf,%lf,%lf,%lf",
		modified_player.health, modified_player.s_mana, modified_player.attack, modified_player.defense, modified_player.fire_crit, modified_player.water_crit, modified_player.grass_crit) < 0) {
		return 0;
	}
	//Test print
	printf("Player Stats: %f, %d, %d, %lf, %lf, %lf, %lf", modified_player.health, modified_player.s_mana, modified_player.attack, modified_player.defense, modified_player.fire_crit, modified_player.water_crit, modified_player.grass_crit);
	
	fclose(temp_player_stats_path);
	return 1;
}

/*
Function   : PlayerStats_ReadFile
Description: Takes the calculated player stats in a temp file and set the player in battle system to be used for damage calculation
Parameters : Player modified_player
Return	   : int (if the function successfully ran)
*/
int PlayerStats_ReadFile(Player* player) {
	FILE* const temp_player_stats_path = fopen(PLAYER_STAT_TEMP_ADDR, "r");

	if (temp_player_stats_path == NULL) {
		printf("Failed to read Temp Player Stat File: %s", PLAYER_STAT_TEMP_ADDR);
		return 0;
	}

	//Try to read the file containing the player stats. If fail, return 0 and inform developer
	if (fscanf_s(temp_player_stats_path, "%f,%d,%d,%lf,%lf,%lf,%lf",
		&(player->health), &(player->s_mana), &(player->attack), &(player->defense), &(player->fire_crit), &(player->water_crit), &(player->grass_crit)) != 7)
	{
		return 0;
	}

	//Test print
	printf("Player Stats: %f, %d, %d, %lf, %lf, %lf, %lf", player->health, player->s_mana, player->attack, player->defense, player->fire_crit, player->water_crit, player->grass_crit);

	fclose(temp_player_stats_path);

	//Return 1 if stats were successfully read
	return 1;
}