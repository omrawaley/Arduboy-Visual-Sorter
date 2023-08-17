#include <Arduboy2.h>

#include "sorting.h"
#include "bar.h"
#include "sprites.h"

Arduboy2 arduboy;
Sorting sorting;

enum class State : uint8_t
{
	SplashScreen,
	TitleScreen,
	Settings,
	UnsortedBars,
	SortedBars,
};

State state = State::SplashScreen;

constexpr size_t arraySize = 26;

uint8_t array[arraySize] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

uint8_t number = 1;
uint8_t index;

bool isRandom;

uint8_t sortMethod = 1;

String sortMethodName;

void setup()
{
	arduboy.begin();
	arduboy.initRandomSeed();
}

void loop()
{
	if(!arduboy.nextFrame())
		return;

	arduboy.pollButtons();

	arduboy.clear();

	updateState();

	arduboy.display();
}

void updateState()
{
	switch(state)
	{
		case State::SplashScreen:
			updateSplashScreen();
			drawSplashScreen();
			break;

		case State::TitleScreen:
			updateTitleScreen();
			drawTitleScreen();
			break;

		case State::Settings:
			updateSettings();
			drawSettings();
			break;

		case State::UnsortedBars:
			updateUnsortedBars();
			drawBars();
			break;

		case State::SortedBars:
			updateSortedBars();
			drawBars();
			break;
	}
}

void updateSplashScreen()
{
	static unsigned long currentTime = millis();

	unsigned long target = millis();

	target -= currentTime;
	
	if(target >= 3000)
		state = State::TitleScreen;
}

void drawSplashScreen()
{
	Sprites::drawOverwrite(39, 7, splashScreenLogo, 0);
}

void updateTitleScreen()
{
	if(arduboy.justPressed(B_BUTTON))
	{
		state = State::Settings;
	}
}

void drawTitleScreen()
{
	Sprites::drawOverwrite(0, 0, titleScreen, 0);
}

void updateSettings()
{
	if(arduboy.pressed(UP_BUTTON) && number < 52)
	{
		++number;
	}

	else if(arduboy.pressed(DOWN_BUTTON) && number > 1)
	{
		--number;
	}

	if(arduboy.justPressed(A_BUTTON) && index < arraySize - 1)
	{
		array[index] = number;

		++index;
	}

	if(arduboy.justPressed(LEFT_BUTTON))
	{
		if(!isRandom)
		{
			for(uint8_t i = 0; i < arraySize; ++i)
			{
				array[i] = random(1, 53);

				isRandom = true;
			}
		}

		else
		{
			for(uint8_t i = 0; i < arraySize; ++i)
			{
				array[i] = 1;

				isRandom = false;
			}
		}
	}

	if(arduboy.justPressed(B_BUTTON))
	{
		state = State::UnsortedBars;
	}
}

void drawSettings()
{
	arduboy.println("Number: " + String(number));
	arduboy.println("Index: " + String(index));

	if(isRandom)
	{
		arduboy.println("\nRandom: Yes");
	}
	else
	{
		arduboy.println("\nRandom: No");
	}

	arduboy.println("\nSorting Method:");
	arduboy.println(sortMethodName);

	sortMethodName = sorting.sortingNames[sortMethod - 1];

	if(arduboy.justPressed(RIGHT_BUTTON))
	{
		if(sortMethod < Sorting::totalSortingMethods)
		{
			++sortMethod;
		}
		else
		{
			--sortMethod;
		}
	}
}

void updateUnsortedBars()
{
	if(arduboy.justPressed(B_BUTTON))
	{
		state = State::SortedBars;
	}
}

void updateSortedBars()
{
	switch(sortMethod)
	{
		case 1:
			sorting.bubbleSort(array, arraySize);
			break;

		case 2:
			sorting.insertionSort(array, arraySize);
			break;
	}

	if(arduboy.justPressed(B_BUTTON))
	{
		state = State::Settings;

		number = 1;
		index = 0;

		for(uint8_t i = 0; i < arraySize; ++i)
		{
			array[i] = 1;
		}

		isRandom = false;

		sortMethod = 1;
	}
}

void drawBars()
{
	printCentered(sortMethodName);

	for(uint8_t i = 0; i < arraySize; ++i)
	{
		Bar bar(i * barGap, barWidth, array[i]);

		arduboy.fillRect(bar.x, bar.y, bar.width, bar.height);
	}
}

void printCentered(String text)
{
	uint8_t textLength = text.length();

	uint8_t totalCharacterWidth = textLength * 5;

	uint8_t totalGapWidth = (textLength - 1);

	uint8_t totalTextWidth = totalCharacterWidth + totalGapWidth;

	uint8_t x = (arduboy.width() / 2) - (totalTextWidth / 2);

	arduboy.setCursor(x, 0);
	arduboy.print(text);
}
