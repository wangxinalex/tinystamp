/*
 * 
 * Author(s):
 *   Derin Harmanci <derin.harmanci@unine.ch>
 *
 * Copyright (c) 2008.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "general.h"

char* dupstr(const char* InputString)
{
    unsigned NewStringLenght = strlen(InputString)+1;
    char* NewString = malloc(NewStringLenght*sizeof(char));
    strcpy(NewString,InputString);
    return NewString;
}


char* strext(char* ExtendedString, const char* AddedString)
{
    if( ExtendedString == NULL) 
	ExtendedString = dupstr(AddedString);
    else
    {
	char* DuplicateString = dupstr(ExtendedString);
	unsigned NewStringlength = strlen(ExtendedString) + strlen(AddedString) + 1; // 1 is added for terminating NULL character.
	free(ExtendedString);
	ExtendedString = malloc(NewStringlength*sizeof(char));
	sprintf(ExtendedString,"%s%s",DuplicateString,AddedString);
	
	free(DuplicateString);
    }
    return ExtendedString;
}	    





void GenereateUnsignedListOutput(const unsigned* ListPtr, unsigned ListSize, char** OutputString)
{

    if( ListSize >0)
    {
	char* QuasiInfiniteDummyString = malloc(100000*sizeof(char));
	
	sprintf(QuasiInfiniteDummyString,"{");
	unsigned ElementNo;
	for(ElementNo=0; ElementNo < ListSize; ElementNo++)
	{
	    if( ElementNo < ListSize -1)
		sprintf(QuasiInfiniteDummyString,"%s%u,",QuasiInfiniteDummyString,ListPtr[ElementNo]);
	    else
		sprintf(QuasiInfiniteDummyString,"%s%u}",QuasiInfiniteDummyString,ListPtr[ElementNo]);
	}
	*OutputString = dupstr(QuasiInfiniteDummyString);

	free(QuasiInfiniteDummyString);

    }
    else
    {
	*OutputString = strdup("EMPTY");
    }
    
}

void GenereateIntegerListOutput(int* ListPtr, unsigned ListSize, char** OutputString)
{


     if(ListSize > 0)
     {   
	 char* QuasiInfiniteDummyString = malloc(100000*sizeof(char));
	 
	 sprintf(QuasiInfiniteDummyString,"{");
	 unsigned ElementNo;
	 for(ElementNo=0; ElementNo < ListSize; ElementNo++)
	 {
	     if( ElementNo < ListSize -1)
		 sprintf(QuasiInfiniteDummyString,"%s%u,",QuasiInfiniteDummyString,ListPtr[ElementNo]);
	     else
		 sprintf(QuasiInfiniteDummyString,"%s%u}",QuasiInfiniteDummyString,ListPtr[ElementNo]);
	 }
	 *OutputString = strdup(QuasiInfiniteDummyString);

	free(QuasiInfiniteDummyString);

     }
     else
     {
	 *OutputString = strdup("EMPTY");
     }


}
