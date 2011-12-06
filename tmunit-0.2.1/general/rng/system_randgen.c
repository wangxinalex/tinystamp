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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "system_rng_interface.h"

typedef enum DistributionTypeEnum {UNIFORM,PERCENTAGE,INVALID} DistributionType;
DistributionType Distribution;


unsigned UniformDistNext(unsigned RandomValue,unsigned RangeSize);
unsigned  PercentageDistNext(unsigned RandomValue,unsigned RangeSize, float *Percentage);


int main(int argc, char* argv[])
{
    if(argc < 5  )
    {
	printf("The program has at least 5 arguments:\n"
	       "    Distribution type (uniform/percentage)\n"
	       "    InitialSeed\n"
	       "    ElementNumInRange\n"
	       "    RangeStartOffset\n"
	       "    [(if percentage distribution): percentages for each element]\n"
	       "    NumberOfNumbersToGenerate\n");
    }
    else
    {
      if( strcmp(argv[1],"uniform")== 0 )
	Distribution = UNIFORM;
      else if ( strcmp(argv[1],"percentage")== 0 )
	Distribution = PERCENTAGE;
      else
      {
	Distribution = INVALID;
	printf("UNKNOWN DISTRIBUTION. Terminating...");
	exit(1);
      }

      unsigned InitialSeed = atoi(argv[2]);
      unsigned ElementNumInRange = atoi(argv[3]);
      unsigned RangeStartOffset = atoi(argv[4]);
      unsigned NumberOfNumbersToGenerate;
      float Percentages[ElementNumInRange];


      unsigned CurrentArgNo = 5;


      if( Distribution == PERCENTAGE )
      {
	unsigned PercentageNo;
	for(PercentageNo=0; PercentageNo< ElementNumInRange; PercentageNo++, CurrentArgNo++)
	  Percentages[PercentageNo] = atof(argv[CurrentArgNo]);
      }

      NumberOfNumbersToGenerate = atoi(argv[CurrentArgNo]);
      
      //      printf("InitialSeed=%u\n",InitialSeed);
      	printf("RAND_MAX_VAL=%u\n",RAND_MAX_VAL);
      

      unsigned Histogram[ElementNumInRange];
      unsigned ElementNo;
      for(ElementNo=0; ElementNo< ElementNumInRange ; ElementNo++)
	{
	  Histogram[ElementNo]=0;
	}      


      printf("Numbers are ( in \"[index]: generated number\" format):\n");
      unsigned NumberNo=0;
      for(NumberNo=0; NumberNo< NumberOfNumbersToGenerate ; NumberNo++)
	{
	  //	  printf("(%u,", InitialSeed );
	  //	  printf("%u) ", RAND_R(&InitialSeed));
	  unsigned RandomValue = RAND_R(&InitialSeed);
	  unsigned ValueCorrespondingToDist;
	  if( Distribution == UNIFORM  )
	  {
	    ValueCorrespondingToDist = UniformDistNext(RandomValue,ElementNumInRange);
	  }
	  if( Distribution == PERCENTAGE  )
	  {
	    ValueCorrespondingToDist = PercentageDistNext(RandomValue,ElementNumInRange,Percentages);
	  }
	  Histogram[ValueCorrespondingToDist] ++;
	  ValueCorrespondingToDist +=  RangeStartOffset;
	  printf("[%u]: %u\n",NumberNo, ValueCorrespondingToDist);
	  
	}
      printf("\n");
      
      printf("Histogram:\n(");
      for(ElementNo=0; ElementNo< ElementNumInRange ; ElementNo++)
	{
	  if( ElementNo < ElementNumInRange-1)
	      printf("%u:%u, ", ElementNo+RangeStartOffset, Histogram[ElementNo]);
	  else
	    printf("%u:%u)", ElementNo+RangeStartOffset, Histogram[ElementNo]);
	}      
      printf("\n");
       
    }
    return 0;
} 



unsigned UniformDistNext(unsigned RandomValue,unsigned RangeSize)
{
    unsigned  ChosenElementNo =  (unsigned)((double)RangeSize * (double)((double)RandomValue/(double)(RAND_MAX_VAL + 1.0))) ;
    return ChosenElementNo;
}


unsigned  PercentageDistNext(unsigned RandomValue,unsigned RangeSize, float *Percentage)
{
    double SelectedPosInHundredScale = (double)100 * (double)((double)RandomValue/(double)(RAND_MAX_VAL + 1.0));

    unsigned CandidateNo;
    unsigned SelectedCandidate = RangeSize;
    double   CurrentRegionUpperLimit = 0 ;
    for(CandidateNo=0; CandidateNo< RangeSize; CandidateNo++)
    {
	double CurrentPercentageValue = (double)Percentage[CandidateNo];
	CurrentRegionUpperLimit += CurrentPercentageValue;
	if( CandidateNo == RangeSize-1)
	    CurrentRegionUpperLimit = 100.0;
	int SelectedPosInCurrentRegion = (SelectedPosInHundredScale < CurrentRegionUpperLimit );
	if( SelectedPosInCurrentRegion )
	{
	    SelectedCandidate = CandidateNo;
	    break;
	}
    }
    assert( SelectedCandidate < RangeSize);
    return SelectedCandidate;
}
