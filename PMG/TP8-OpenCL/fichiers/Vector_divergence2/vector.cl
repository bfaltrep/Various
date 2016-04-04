
__kernel void vecmul(__global float *vec,
		     __global float *res,
		     float k)
{
	//res[get_global_id(0)] = k * vec[get_global_id(0)];

	int id = (get_global_id(0)+16)%get_global_size(0);

	int grp = get_group_id(0);

	//ajouter une boucle de 10 pr que ce soit plus repérable
	if((grp&1) ==0)
		res[id] = 3.14 * vec[id];
	else
		res[id] = k * vec[id];
}
