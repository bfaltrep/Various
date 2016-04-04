// ./transpose

__kernel void transpose(__global float *in,
	  	     			__global float *out)
{

	// efficacité : 380 µs

	int x = get_global_id(0); //j
	int y = get_global_id(1); //i

	int X = get_group_id(0); //j
	int Y = get_group_id(1); //i

	int xl = get_local_id(0); 
	int yl = get_local_id(1);

	__local float tuile[TILE][TILE]; //instanciée qu'une seule fois par grp

	tuile[yl][xl]= in[y* get_global_size(1)+x];

	barrier(CLK_LOCAL_MEM_FENCE);
	
	out[X* TILE* get_global_size(0) + Y*TILE + xl + yl* get_global_size(1)] = tuile[xl][yl];

  
	  /*
	  //efficacité : 460 µs
	  int x = get_global_id(0); //j
	  int y = get_global_id(1); //i
	  out[x * get_global_size(0) + y] = in[y * get_global_size(0) + x];
	  */
}
