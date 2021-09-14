// GPointerList.cpp: implementation of the GPointerList class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "GPointerList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPointerList::GPointerList()
{
	first = last = curr = NULL;
}

GPointerList::~GPointerList()
{
	Clear();
}

void GPointerList::Add(void* data)
{
	LPLIST_NODE q;
	q       = (LPLIST_NODE)malloc(sizeof(LIST_NODE));
	q->info = data;
	q->next = (curr) != NULL ? curr->next : NULL;
	q->prev = (curr) != NULL ? curr : NULL;
	if (curr != NULL)
	{
		curr->next = q;
	}
	curr = q;
	if ((q->prev) == NULL)
	{
		first = curr;
	}
	if ((q->next) == NULL)
	{
		last = curr;
	}
}

void GPointerList::Clear()
{
	LPLIST_NODE q;
	while (first != NULL)
	{
		q = first->next;
		free(first);
		first = q;
	}
	first = last = curr = NULL;
}

void GPointerList::GotoFirst()
{
	curr = first;
}

void GPointerList::GotoNext()
{
	curr = curr->next;
}

void* GPointerList::CurrData()
{
	return (curr) != NULL ? curr->info : NULL;
}

void GPointerList::GotoLast()
{
	curr = last;
}

void GPointerList::GotoPrev()
{
	curr = curr->prev;
}
