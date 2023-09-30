#include "sort-harness.h"
#include "student_sort.h"
#include <stdio.h>
#include <pmmintrin.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include <x86intrin.h>

void student_sort(float a[], int size) {
  david_sort(a, size);
  sample_sort(a, size);
  CocktailSort(a, size);

}

void sample_sort(float a[], int size) {
  int i, j; 
  int n = 40;
  float array1[size], array2[size], array3[size], array4[size], array5[size];
  int count1 = 0; int count2 = 0; int count3 = 0; int count4 = 0; int count5 = 0;
  float array[40];
  for (i=0; i < n; i++) {
      array[i] = a[i];
  }

for (i = 0; i < n-1; i++)       
for (j = 0; j < n-i-1; j++) if (array[j] > array[j+1]) 
swap(&array[j], &array[j+1]); 
  
  __m128 number = _mm_setr_ps(array[0], array[10], array[20], array[30]);
  
  float arrayVal[4];
  for ( i = 0; i < size; i++ ) {
    __m128 value = _mm_set1_ps(a[i]);
    __m128 comp = _mm_cmpgt_ps(value, number);
    _mm_storeu_ps(arrayVal, comp);
    
    if (arrayVal[3] != 0) {
        array5[count5] = a[i];
        count5++;
    }
    else if (arrayVal[2] != 0) {
        array4[count4] = a[i];
        count4++;
    }
    else if (arrayVal[1] != 0) {
        array3[count3] = a[i];
        count3++;
    }
    else if (arrayVal[0] != 0) {
        array2[count2] = a[i];
        count2++;
    }
    else {
        array1[count1] = a[i];
        count1++;
    }
  }
  for (i = 0; i < count1-1; i++) {      
  for (j = 0; j < count1-i-1; j++) {
      __m128 value1 = _mm_set1_ps(array1[j]);
      __m128 value2 = _mm_set1_ps(array1[j+1]);
      __m128 comp1 = _mm_cmpgt_ps(value1, value2);
      _mm_storeu_ps(arrayVal, comp1);
      if (arrayVal[0] != 0) {
          swap(&array1[j], &array1[j+1]); 
      }
  }
  }
  for (i = 0; i < count2-1; i++) {      
  for (j = 0; j < count2-i-1; j++) {
      __m128 value1 = _mm_set1_ps(array2[j]);
      __m128 value2 = _mm_set1_ps(array2[j+1]);
      __m128 comp1 = _mm_cmpgt_ps(value1, value2);
      _mm_storeu_ps(arrayVal, comp1);
      if (arrayVal[0] != 0) {
          swap(&array2[j], &array2[j+1]); 
      }
  }
  }
  for (i = 0; i < count3-1; i++) {      
  for (j = 0; j < count3-i-1; j++) {
      __m128 value1 = _mm_set1_ps(array3[j]);
      __m128 value2 = _mm_set1_ps(array3[j+1]);
      __m128 comp1 = _mm_cmpgt_ps(value1, value2);
      _mm_storeu_ps(arrayVal, comp1);
      if (arrayVal[0] != 0) {
          swap(&array3[j], &array3[j+1]); 
      }
  }
  }
  for (i = 0; i < count4-1; i++) {      
  for (j = 0; j < count4-i-1; j++) {
      __m128 value1 = _mm_set1_ps(array4[j]);
      __m128 value2 = _mm_set1_ps(array4[j+1]);
      __m128 comp1 = _mm_cmpgt_ps(value1, value2);
      _mm_storeu_ps(arrayVal, comp1);
      if (arrayVal[0] != 0) {
          swap(&array4[j], &array4[j+1]); 
      }
  }
  }
  for (i = 0; i < count5-1; i++) {      
  for (j = 0; j < count5-i-1; j++) {
      __m128 value1 = _mm_set1_ps(array5[j]);
      __m128 value2 = _mm_set1_ps(array5[j+1]);
      __m128 comp1 = _mm_cmpgt_ps(value1, value2);
      _mm_storeu_ps(arrayVal, comp1);
      if (arrayVal[0] != 0) {
          swap(&array5[j], &array5[j+1]); 
      }
  }
  }
  
  for (i = 0; i<count1; i++) {
       a[i] = array1[i];
  }
  for (i = count1; i<count1+count2; i++) {
       a[i] = array2[i-count1];
  }
  for (i = count1+count2; i<count1+count2+count3; i++) {
       a[i] = array3[i-count1-count2];
  }
  for (i = count1+count2+count3; i<count1+count2+count3+count4; i++) {
       a[i] = array4[i-count1-count2-count3];
  }
  for (i = count1+count2+count3+count4; i<count1+count2+count3+count4+count5; i++) {
       a[i] = array5[i-count1-count2-count3-count4];
  }
}

void swap(float *a, float *b) 
{ 
float temp = *a; 
*a = *b; 
*b = temp; 
}  


//Cocktail Shaker Sort
void CocktailSort(float data[], int count)
{
	while (1)
	{
		char flag;
		int start[2] = { 1, count - 1 };
		int end[2] = { count, 0 };
		int inc[2] = { 1, -1 };
    float arrayCock[4];

		for (int it = 0; it < 2; ++it)
		{
			flag = 1;

			for (int i = start[it]; i != end[it]; i += inc[it])
			{    
          __m128 data1= _mm_set1_ps(data[i - 1]);
          __m128 data2= _mm_set1_ps(data[i]);
          __m128 compare = _mm_cmpgt_ps(data1, data2);
          _mm_storeu_ps(arrayCock, compare);
          if (arrayCock[0] != 0) {
          swap(data + i - 1, data + i);
					flag = 0;
      }
			}
			if (flag)
				return;
		}
	}
}

