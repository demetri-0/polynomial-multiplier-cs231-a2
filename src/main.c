#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	LinkedList* list = initList();
	insertFirst(list, 3, 2);
	insertFirst(list, 7, 3);
	insertLast(list, 4, 4);
	insertLast(list, 4, 4);
	insertLast(list, 4, 4);
	insertAfter(list, 5, 8, 3, 2);
	replaceElement(list, 4, 4, 10, 10);
	printf("%s\n", toString(list));

	deleteFirst(list);
	deleteLast(list);
	printf("%s\n", toString(list));

	printf("contains 3x^2? %d ||| contains 1x^1? %d\n", containsElement(list, 3, 2), containsElement(list, 1, 1));

	LinkedList* sortedList = initList();
	insertSorted(sortedList, 4, 5);
	insertSorted(sortedList, 2, 6);
	insertSorted(sortedList, 7, 1);
	insertSorted(sortedList, 12, 11);
	insertSorted(sortedList, 1, 3);
	deleteElement(sortedList, 2, 6);
	printf("%s\n", toString(sortedList));

	return 0;
}
