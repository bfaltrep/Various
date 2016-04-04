
__kernel void vecmul(__global float *vec,
		     __global float *res,
		     float k)
{
	//res[get_global_id(0)] = k * vec[get_global_id(0)];

	int id = (get_global_id(0)+16)%get_global_size(0);

	if(((get_global_id(0)>> id)&1) == 0)
		res[id] = k * vec[id];
	else
		res[id] = 3.14 * vec[id];
}
