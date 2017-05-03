#include "global.h"



Backpatchlist *makelist(int location)
{
	return new Backpatchlist(location);
}


void backpatchlist(Backpatchlist* list, int location)
{
	while (list != NULL)
	{
		backpatch(list->location, location - list->location);
		list = list->next;
	}
	
}

Backpatchlist *mergelist(Backpatchlist* list1, Backpatchlist* list2)
{
	Backpatchlist* current = list1;
	while (current->next != NULL) current = current->next;
	current->next = list2;
	return list1;
}