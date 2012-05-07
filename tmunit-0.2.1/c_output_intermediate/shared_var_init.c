// Initializing shared variables and arrays.
*W = 4;
unsigned ElementNo;
for(ElementNo=0; ElementNo< a_array_size ; ElementNo++)
a[ElementNo] = 0;


#ifdef ENABLE_TRACE_CODE
if ( EnableTrace )
{
printf("Address of W : %p\n",W );
for(ElementNo=0; ElementNo< a_array_size ; ElementNo++)
printf("Address of a[%u] : %p\n",ElementNo, &(a[ElementNo]) );

}
#endif
