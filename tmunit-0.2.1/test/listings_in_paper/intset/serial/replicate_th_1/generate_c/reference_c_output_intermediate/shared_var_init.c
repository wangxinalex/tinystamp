// Initializing shared variables and arrays.
unsigned ElementNo;
for(ElementNo=0; ElementNo< m_array_size ; ElementNo++)
m[ElementNo] = 0;


#ifdef ENABLE_TRACE_CODE
if ( EnableTrace )
{
for(ElementNo=0; ElementNo< m_array_size ; ElementNo++)
printf("Address of m[%u] : %p\n",ElementNo, &(m[ElementNo]) );

}
#endif
