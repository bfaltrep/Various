__kernel void reduction(__global float *vec,
		     int debut,
		     int fin)
{

  __local float tmp[TILE];

  tmp[get_local_id(0)] = vec[debut+get_local_id(0)];

  barrier(CLK_LOCAL_MEM_FENCE);

  for(int i = TILE/2 ; i > 0 ; i/=2 ){
  	if(get_local_id(0) <= i){
  		tmp[get_local_id(0)] = tmp[get_local_id(0)]+tmp[get_local_id(0)+i];
  	}
  	barrier(CLK_LOCAL_MEM_FENCE);
  }

  if(get_local_id(0) == 0){
		vec[fin+get_group_id(0)]= tmp[get_local_id(0)];
	}
}