__kernel void vector_to_octal(__global int *A, __global int *B){

	int i = get_global_id(0);
	int n = A[i];

	int octalNum = 0; 

    while (n != 0) { 
  
        octalNum = (octalNum * 10) + (n % 8); 
        n = n / 8;
    } 

    int sec = octalNum;
    octalNum = 0;

    while(sec!=0){
    	octalNum = (octalNum*10) + (sec%10);
    	sec/=10;
    }

    B[i] = octalNum;
}