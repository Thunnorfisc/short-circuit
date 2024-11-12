#include "enemyStructs.h"

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
