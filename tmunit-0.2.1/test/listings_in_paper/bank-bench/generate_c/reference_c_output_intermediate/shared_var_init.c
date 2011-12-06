// Initializing shared variables and arrays.
unsigned ElementNo;
for(ElementNo=0; ElementNo< a_array_size ; ElementNo++)
a[ElementNo] = 0;


#ifdef ENABLE_TRACE_CODE
if ( EnableTrace )
{
for(ElementNo=0; ElementNo< a_array_size ; ElementNo++)
printf("Address of a[%u] : %p\n",ElementNo, &(a[ElementNo]) );

}
#endif
