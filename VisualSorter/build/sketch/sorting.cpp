#line 1 "/Users/om/Downloads/ARDUBOY/VisualSorter/sorting.cpp"
#include "sorting.h"

bool Sorting::bubbleSort(uint8_t array[], size_t arraySize)
{
	for(uint8_t i = 0; i < arraySize; ++i)
	{
		for(uint8_t j = i + 1; j < arraySize; ++j)
		{
			if(array[j] < array[i])
			{
				uint8_t temp = array[i];

				array[i] = array[j];
				array[j] = temp;
			}
		}
	}

	return true;
}

bool Sorting::insertionSort(uint8_t array[], size_t arraySize)
{
	for(uint8_t i = 1; i < arraySize; ++i)
	{
		uint8_t current = array[i];

		int8_t j = i - 1;

		while(j > -1 && current < array[j])
		{
			array[j + 1] = array[j];

			j--;
		}

		array[j + 1] = current;
	}

	return true;
}