// Initializing shared variables and arrays.
*x = 5;
unsigned ElementNo;
for(ElementNo=0; ElementNo< arr_array_size ; ElementNo++)
arr[ElementNo] = 0;
arr[0] = 10;
arr[1] = 11;
arr[2] = 12;
arr[3] = 13;


#ifdef ENABLE_TRACE_CODE
if ( EnableTrace )
{
printf("Address of x : %p\n",x );
for(ElementNo=0; ElementNo< arr_array_size ; ElementNo++)
printf("Address of arr[%u] : %p\n",ElementNo, &(arr[ElementNo]) );

}
#endif
