#include "enemyStructs.h"
#include <stdlib.h>
#include <time.h>

//Change this to read from file and add int initiative code
Enemy Enemy_Arr_Initialize(EnemyTypes type, CP_Vector v) {
    Enemy enemy = {.enemy_type = type, .position = v };
    
    switch (type) {

    case E_Wizard:
        enemy.attack = 10;
        enemy.weakness = Element_Water;
        enemy.healthbar = 100;
        enemy.resistance = Element_Fire;
        enemy.resist_multiplier = 0.5;
        
        break;

    case E_Plant:
        enemy.attack = 8;
        enemy.weakness = Element_Fire;
        enemy.healthbar = 80;
        enemy.resistance = Element_Grass;
        enemy.resist_multiplier = 0.5;
        break;

    case E_Vulture:
        enemy.attack = 12;
        enemy.weakness = Element_Grass;
        enemy.healthbar = 90;
        enemy.resistance = Element_Water;
        enemy.resist_multiplier = 0.5;
        break;

    default:
        break;
    }

    return enemy;
}

void Enemy_Initialize_Array(Enemy enemies[ENEMY_COUNT], CP_Vector gridLocation[GRID_DIMENSIONS][GRID_DIMENSIONS], int num_to_generate, int do_randomise_enemies) {
    
    CP_Vector generated_vectors[ENEMY_COUNT] = { 0 };  // Array to store positions that are already generated
    CP_Vector new_vector = { 0 };
    int generated_i, generated_j;

    for (int i = 0; i < num_to_generate;) {
        // Generating new positions of the enemies using Grid System
        srand((unsigned int)time(NULL));
        generated_i = CP_Random_RangeInt(0, GRID_DIMENSIONS - 1);  // Random index for grid
        generated_j = CP_Random_RangeInt(0, GRID_DIMENSIONS - 1);
        new_vector = gridLocation[generated_i][generated_j];  // Get the position from grid

        if (!CP_Vector_Length(generated_vectors[0]) || !Exist_In_Array(&new_vector, &generated_vectors, A_CP_VECTOR, 3)) {
            // Store the enemies in an array
            EnemyTypes enemy_type_arr[3] = { E_Wizard, E_Plant, E_Vulture };
            // Randomise the different type of enemies that will appear
            if (do_randomise_enemies) enemies[i] = Enemy_Arr_Initialize(enemy_type_arr[CP_Random_RangeInt(0, 2)], new_vector);
            else enemies[i].position = new_vector;
            generated_vectors[i] = new_vector;
            ++i;    		
        }
    }
}

/*
Function   : Check_Enemy_Hit
Description: Used to check which enemy was attacked
Parameters : Enemy enemy_arr[3], CP_Vector index_used[], CircuitPiece selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS], Player player
Return	   : void
*/
void Check_Enemy_Hit(Enemy enemy_arr[3], CP_Vector index_used[], CircuitPiece selected_pieces[GRID_DIMENSIONS][GRID_DIMENSIONS], Player player) {
    int i = 0;
    int attack_count = 0;
    //Check which enemy was hit
    Enemy enemy_hit_arr[3] = { 0 };
    //CircuitPieces that hit
    CircuitPiece circuit_pieces_hit[3] = { 0 };
    int total_num_of_pieces = 0;

    //Count how many enemies were hit, how many pieces were used and which pieces hit
    while (CP_Vector_Length(index_used[i])) {
        for (int j = 0; j < 3; j++) {  
            if (CP_Vector_Distance(enemy_arr[j].position, selected_pieces[(int)index_used[i].x - 1][(int)index_used[i].y - 1].position) == 0) {
                //Calculate the damage on the enemies
                circuit_pieces_hit[attack_count] = selected_pieces[(int)index_used[i].x - 1][(int)index_used[i].y - 1];
                enemy_hit_arr[attack_count] = enemy_arr[j];
                attack_count++;
                continue;
            }
        }
        i++;
    }
    total_num_of_pieces = i;

    //Calculate the damage
    int index = 0;
    while (CP_Vector_Length(enemy_hit_arr[index].position)){
        Enemy_Calculate_Damage(&(enemy_arr[index]), player, circuit_pieces_hit[index], total_num_of_pieces, attack_count);
        index++;
    }
}

/*
Function   : Enemy_Calculate_Damage
Description: Used to calculate the amount of damage that is dealt to the enemy
Parameters : Enemy* enemy, Player const player, CircuitPiece piece_that_hit, int number_of_pipes, int num_of_enemies_hit
Return	   : void
*/
void Enemy_Calculate_Damage(Enemy* enemy, Player const player, CircuitPiece piece_that_hit, int number_of_pipes, int num_of_enemies_hit) {
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
    else if(enemy->resistance == piece_that_hit.element) {
        switch (piece_that_hit.element)
        {
        case Element_Fire:
        case Element_Grass:
        case Element_Water:
            damage_multiplier = enemy->resist_multiplier;
            break;
        default:
            damage_multiplier = 1;
            break;
        }
    }

    damage_dealt = (double)player.attack * (double)number_of_pipes/ (double)num_of_enemies_hit * damage_multiplier;

    enemy->healthbar -= (int)damage_dealt;
}

/*
Function   : Enemy_Damage_Player
Description: Used to calculate the amount of damage the enemy will do
Parameters : Enemy enemy, Player* player
Return	   : void
*/
void Enemy_Damage_Player(Enemy enemy[ENEMY_COUNT], Player* player) {
    float enemy_damage = 0;
    for (int i = 0; i < ENEMY_COUNT; ++i) {
        enemy_damage += CP_Random_RangeFloat((float)enemy[i].attack - 5.f, (float)enemy[i].attack);
    }
    player->health -= enemy_damage * (float)player->defense;
}