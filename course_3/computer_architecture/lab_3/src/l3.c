#include <reg51.h>

char toLower(char letter) {
	if (letter >= 'A' && letter <= 'Z') {
		return letter - ('A' - 'a');
	} else { 
	  return letter;
	}
}

main() { 
	char testString[] = "This programmator";
	//char code testString[] = "This programmator";
  char testStringSize = 17;	
	char minChar; 
	int i, pivot = 0;
	
	// remove all spaces
	for (i = 0; i < testStringSize; i++) {
		if (testString[i] == ' ') {
			testString[i] = testString[testStringSize - 1];
			testString[testStringSize - 1] = 0;
			testStringSize--;
		}
	}
		 
	while(pivot != testStringSize) {
	  // search for a min
		minChar = testString[pivot];
		
		for (i = pivot + 1; i < testStringSize; i++) {		
			if (toLower(testString[i]) < toLower(minChar)) {
				minChar = testString[i];
			}
		}
		
		// swap min chars with chars at pivot index, increment pivot for each swap
		for (i = pivot; i < testStringSize; i++) {
			if (testString[i] == minChar) {
				// swap
				char buffer = testString[i];
				testString[i] = testString[pivot];
				testString[pivot] = buffer;
				pivot++;
			}				
		}
	}
}