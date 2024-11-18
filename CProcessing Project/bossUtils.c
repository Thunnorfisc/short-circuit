#include "bossUtils.h"
#include <string.h>


/*
Function   : BossParts_Initialize
Description: Used to initialize the bodypart array in the Boss Struct
Parameters : BossPart bp[], int initiative, int healthbar, CP_Image image, CP_Vector pos, ElementType weakness, ElementType resistance, int number_of_parts
Return	   : void
*/
void BossParts_Initialize(BossPart bp[], int initiative, float healthbar, CP_Image image, CP_Vector pos, ElementType weakness, ElementType resistance, int index) {
    bp[index].initiative = initiative;
    bp[index].healthbar = healthbar;
    bp[index].image = image;
    bp[index].pos = pos;
    bp[index].weakness = weakness;
    bp[index].resistance = resistance;
}

/*
Function   : Boss_Initialize
Description: Used to initialize the boss struct
Parameters : BossPart bp[], int initiative, int healthbar, CP_Image image, CP_Vector pos, ElementType weakness, ElementType resistance, int number_of_parts
Return	   : int (true/false on if the boss was properly initialized)
*/
int Boss_Initialize(Boss* boss, int boss_id, CP_Vector grid_location[GRID_DIMENSIONS][GRID_DIMENSIONS]) {

    Boss temp_boss = { 0 };
    FILE* boss_file = fopen(BOSS_DATA_ADDR, "r");
    
    if (NULL == boss_file)
    {
        printf("Failed to open bosses_data.txt: %s", BOSS_DATA_ADDR);
        return (0);
    }

    while (EOF != fscanf_s(boss_file, "%d,%d,%d,%[^\n]",
        &temp_boss.boss_id,&temp_boss.enrage_time, &temp_boss.num_of_bp, boss->boss_name, (unsigned int)sizeof(boss->boss_name)))
    {
        if (temp_boss.boss_id == boss_id) {
            boss->boss_id = temp_boss.boss_id;
            boss->enrage_time = temp_boss.enrage_time;
            boss->num_of_bp = temp_boss.num_of_bp;
            break;
        }
    }

    CP_Image bp_image_arr[25];
    char asset_dir[100] = "Assets/Enemy_Files/", filepath[154] = {'\0'}, filepath_img[154] = { '\0' };

    if (boss->boss_name != NULL){
        //Concatenates the asset_dir
        sprintf_s(filepath, (unsigned int)sizeof(filepath), "%s%s%s", asset_dir, boss->boss_name, ".txt");

        for (int i = 0; i < boss->num_of_bp; ++i) {
            //Set path for each image file
            sprintf_s(filepath_img, (unsigned int)sizeof(filepath_img), "%s%s_part%01d%s", asset_dir, boss->boss_name, i, ".png");
            bp_image_arr[i] = CP_Image_Load(filepath_img);
        }
    }
    else {
        printf("Boss failed to initialize");
        return 0;
    }
    fclose(boss_file);

    //Reading Body Part File
    FILE* bp_file = fopen(filepath, "r");

    if (bp_file == NULL) {
        printf("Failed to open body part data: %s", filepath);
        return (0);
    }
    for (int i = 0; i < boss->num_of_bp; ++i) {
        BossPart temp_bp = { 0 };

        fscanf_s(bp_file, "%f,%d,%f,%f,%d,%d",
            &temp_bp.healthbar, &temp_bp.initiative, &temp_bp.pos.x, &temp_bp.pos.y, &temp_bp.resistance, &temp_bp.weakness);

        BossParts_Initialize(boss->parts, temp_bp.initiative, temp_bp.healthbar, bp_image_arr[i], grid_location[(int)temp_bp.pos.y-1][(int)temp_bp.pos.x-1], temp_bp.weakness, temp_bp.resistance, i);
    }

    fclose(bp_file);
    return 1;

}

/*
Function   : Check_Enemy_Hit
Description: Used to check which enemy was attacked
Parameters : Enemy enemy_arr[3], CP_Vector index_used[], CircuitPiece selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS], Player player
Return	   : void
*/
void Check_Boss_Hit(BossPart bp_arr[3], CP_Vector index_used[], CircuitPiece selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS], Player player) {
    int i = 0;
    int attack_count = 0;
    //Check which enemy was hit
    BossPart enemy_hit_arr[3] = { 0 };
    //CircuitPieces that hit
    CircuitPiece circuit_pieces_hit[3] = { 0 };
    int total_num_of_pieces = 0;

    //Count how many enemies were hit, how many pieces were used and which pieces hit
    while (CP_Vector_Length(index_used[i])) {
        for (int j = 0; j < 3; j++) {
            if (CP_Vector_Distance(bp_arr[j].pos, selected_pieces[(int)index_used[i].x - 1][(int)index_used[i].y - 1].position) == 0) {
                //Calculate the damage on the enemies
                circuit_pieces_hit[attack_count] = selected_pieces[(int)index_used[i].x - 1][(int)index_used[i].y - 1];
                enemy_hit_arr[attack_count] = bp_arr[j];
                attack_count++;
                continue;
            }
        }
        i++;
    }
    total_num_of_pieces = i;

    //Calculate the damage
    int index = 0;
    while (CP_Vector_Length(enemy_hit_arr[index].pos)) {
        Boss_Calculate_Damage(&(bp_arr[index]), player, circuit_pieces_hit[index], total_num_of_pieces, attack_count);
        index++;
    }
}

/*
Function   : Enemy_Calculate_Damage
Description: Used to calculate the amount of damage that is dealt to the enemy
Parameters : Enemy* enemy, Player const player, CircuitPiece piece_that_hit, int number_of_pipes, int num_of_enemies_hit
Return	   : void
*/
void Boss_Calculate_Damage(BossPart* enemy, Player const player, CircuitPiece piece_that_hit, int number_of_pipes, int num_of_enemies_hit) {
    //Varibales to calculate damage
    double damage_dealt = 0;
    double damage_multiplier = 1;

    //Check if the piece is a damage_multiplier hit
    if (enemy->weakness == piece_that_hit.element) {
        switch (piece_that_hit.element)
        {
        case Element_Fire:
            damage_multiplier *= player.fire_crit;
            break;
        case Element_Grass:
            damage_multiplier *= player.grass_crit;
            break;
        case Element_Water:
            damage_multiplier *= player.water_crit;
            break;
        default:
            damage_multiplier = 1;
            break;
        }
    }
    //Check if there is resistance
    else if (enemy->resistance == piece_that_hit.element) {
        switch (piece_that_hit.element)
        {
        case Element_Fire:
        case Element_Grass:
        case Element_Water:
            damage_multiplier = enemy->resistance;
            break;
        default:
            damage_multiplier = 1;
            break;
        }
    }

    damage_dealt = (double)player.attack * (double)number_of_pipes / (double)num_of_enemies_hit * damage_multiplier;

    enemy->healthbar -= (int)damage_dealt;
}