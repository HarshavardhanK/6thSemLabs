__kernel void cat(__global char * S, __global char * res,int len) {
	//Get the index of the current work item
	int i = get_global_id(0);
	i = i * len;
	for (int j = 0; j < len; j++)
		res[i+j]=S[j];
}