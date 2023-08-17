#pragma once

#include <stdint.h>
#include <Arduino.h>

class Sorting
{
	public:
		static constexpr uint8_t totalSortingMethods = 2;

		String sortingNames[totalSortingMethods] = {"Bubble Sort", "Insertion Sort"};

		bool bubbleSort(uint8_t array[], size_t arraySize);
		bool insertionSort(uint8_t array[], size_t arraySize);
};