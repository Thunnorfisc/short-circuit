#include "enemyStructs.h"


//Initializing E_Mage enemy object
E_Mage E_Mage_Initialize(CP_Vector v) {
	E_Mage new_e_mage;
	new_e_mage.position = v;

	return new_e_mage;
}

void E_Mage_Initialize_Array(E_Mage e_mage_arr[3], CP_Vector gridLocation[GRID_DIMENSIONS][GRID_DIMENSIONS], int const num_to_generate) {
	CP_Vector generated_vectors[3] = {0};
	CP_Vector newVector = {0};
	int generated_i, generated_j;

	for (int i = 0; i < num_to_generate;) {
		//Generating new positions of the enemies using Grid System
		srand(time(NULL));
		generated_i = CP_Random_RangeInt(0, GRID_DIMENSIONS-1);
		generated_j = CP_Random_RangeInt(0, GRID_DIMENSIONS-1);
		newVector = CP_Vector_Set(gridLocation[generated_i][generated_j].x, gridLocation[generated_i][generated_j].y);

		if (!CP_Vector_Length(generated_vectors[0]) || !Exist_In_Array(&newVector, &generated_vectors, A_CP_VECTOR, 3)) {
			e_mage_arr[i].position = newVector;
			generated_vectors[i] = newVector;
			++i;
		}
	}
}
