#include "enemyStructs.h"
#include <stdlib.h>
#include <time.h>
Enemy initializeEnemy(EnemyTypes type, CP_Vector v) {
    Enemy enemy = {.enemy_type = type, .position = v };

    switch (type) {

    case E_Wizard:
        enemy.attack = 10;
        enemy.weakness = Element_Water;
        enemy.healthbar = 100;
        enemy.resistance = Element_Fire;
        enemy.criticaldmg = 15;
        break;

    case E_Plant:
        enemy.attack = 8;
        enemy.weakness = Element_Fire;
        enemy.healthbar = 80;
        enemy.resistance = Element_Grass;
        enemy.criticaldmg = 12;
        break;

    case E_Vulture:
        enemy.attack = 12;
        enemy.weakness = Element_Grass;
        enemy.healthbar = 90;
        enemy.resistance = Element_Water;
        enemy.criticaldmg = 18;
        break;

    default:
        break;
    }

    return enemy;
}


void Enemy_Initialize_Array(Enemy enemies[3], CP_Vector gridLocation[GRID_DIMENSIONS][GRID_DIMENSIONS], int num_to_generate) {
    
    CP_Vector generated_vectors[3] = { 0 };  // Array to store positions that are already generated
    CP_Vector new_vector = { 0 };
    int generated_i, generated_j;

    for (int i = 0; i < num_to_generate;) {
        // Generating new positions of the enemies using Grid System
        srand(time(NULL));
        generated_i = CP_Random_RangeInt(0, GRID_DIMENSIONS - 1);  // Random index for grid
        generated_j = CP_Random_RangeInt(0, GRID_DIMENSIONS - 1);
        new_vector = gridLocation[generated_i][generated_j];  // Get the position from grid

        if (!CP_Vector_Length(generated_vectors[0]) || !Exist_In_Array(&new_vector, &generated_vectors, A_CP_VECTOR, 3)) {
            // Store the enemies in an array
            EnemyTypes enemy_type_arr[3] = { E_Wizard, E_Plant, E_Vulture };
            // Randomise the different type of enemies that will appear
            enemies[i] = initializeEnemy(enemy_type_arr[CP_Random_RangeInt(0, 2)],new_vector );
            generated_vectors[i] = new_vector;
            ++i;    		
        }
    }
}
/*
Function   : Check_Enemy_Hit
Description: Used to check which enemy was attacked
Parameters : Enemy enemy_attacked[3] (May not be needed), Enemy enemy_arr[3], CP_Vector index_used[], CircuitPiece selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS]
Return	   : int number of attacked enemies
*/
int Check_Enemy_Hit(Enemy enemy_attacked[3], Enemy enemy_arr[3], CP_Vector index_used[], CircuitPiece selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS]) {
    int i = 0;
    int attack_count = 0;

    //Check to see which enemy was attacked. By right here also can do damage. If Damage to be done here, then remove the first array parameter
    while (CP_Vector_Length(index_used[i++])) {
        for (int j = 0; j < 3; j++) {   
            if (CP_Vector_Distance(enemy_arr[j].position, selected_pieces[(int)index_used[i].x - 1][(int)index_used[i].y - 1].position) == 0) {
                enemy_attacked[attack_count++] = enemy_arr[j];
                continue;
            }
        }
    }
    return attack_count;
}

/*
Function   : BossParts_Initialize
Description: Used to initialize the bodypart array in the Boss Struct
Parameters : BossPart bp[], int initiative, int healthbar, CP_Image image, CP_Vector pos, ElementType weakness, ElementType resistance, int number_of_parts
Return	   : void
*/
void BossParts_Initialize(BossPart bp[], int initiative, int healthbar, CP_Image image, CP_Vector pos, ElementType weakness, ElementType resistance, int number_of_parts) {
    for (int i = 0; i < number_of_parts; ++i) {
        bp[i].initiative = initiative;
        bp[i].healthbar = healthbar;
        bp[i].image = image;
        bp[i].pos = pos;
        bp[i].weakness = weakness;
        bp[i].resistance = resistance;
    }
}

/*
Function   : Boss_Initialize
Description: Used to initialize the boss struct
Parameters : BossPart bp[], int initiative, int healthbar, CP_Image image, CP_Vector pos, ElementType weakness, ElementType resistance, int number_of_parts
Return	   : int (true/false on if the boss was properly initialized)
*/
//int Boss_Initialize(Boss* boss, FILE* const boss_file, int boss_id) {
//
//    int boss_data_exist = 0;
//    //Read from the text file of bosses and choose based on the ID
//    while (fscanf_s(boss_file, "Boss_ID: %d EnrageTimer: %d BossName: %[^\n]", &((*boss).boss_id), &((*boss).enrage_time), (*boss).boss_name) == "3") {
//        if (boss_id == boss->boss_id) {
//            boss_data_exist = 1;
//            break;
//        }
//    }
//
//    //Check if the boss was able to successfully load
//    if (!boss_data_exist) {
//        printf("Boss object failed to load\n");
//        return 0;
//    }
//    char filename[32] = { 0 };
//    //Concat_FilePath(filename, "Asset/", boss->boss_name, ".txt");
//
//    ////Use the boss name to read from the file containing the boss parts data
//    //FILE* boss_parts_data = fopen(filename, "r");
//
//    //if (boss_parts_data == NULL) {
//    //    printf("(%s) Boss part data failed to load:\n%s may be invalid\n", boss->boss_name, filename);
//    //    return 0;
//    //}
//
//    //Read the data
//
//}