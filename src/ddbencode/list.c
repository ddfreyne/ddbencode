#include <ddbencode/ddbencode.h>
#include <ddbencode/private.h>

#include <stdarg.h>
#include <stdio.h>

BEList *BEListCreate(size_t aSize, ...)
{
	va_list ap;

	// Create list
	// FIXME check malloc return value
	BEList *list = malloc(sizeof (BEList));
	list->entries = malloc(aSize * (sizeof (struct _BEListEntry)));
	list->size = aSize;

	va_start(ap, aSize);
	for(size_t i = 0; i < aSize; ++i)
	{
		switch(va_arg(ap, int))
		{
			case BE_STRING:
				// TODO decide whether the string should be retained (dup'ed) or not
				list->entries[i].type = BE_STRING;
				list->entries[i].data.string = va_arg(ap, char *);
				break;

			case BE_INTEGER:
				list->entries[i].type = BE_INTEGER;
				list->entries[i].data.integer = va_arg(ap, int);
				break;

			case BE_LIST:
				list->entries[i].type = BE_LIST;
				list->entries[i].data.list = va_arg(ap, BEList *);
				break;

			case BE_DICTIONARY:
				list->entries[i].type = BE_DICTIONARY;
				list->entries[i].data.dictionary = va_arg(ap, BEDictionary *);
				break;

			default:
				free(list->entries);
				free(list);
				return NULL;
		}
	}
	va_end(ap);

	// Done
	return list;
}

void BEListDelete(BEList *aList)
{
	free(aList->entries);
	free(aList);
}

void BEListEncode(BEList *aList, void **aData, size_t *aDataLength)
{
	// Lists are encoded as an 'l' followed by their elements (also bencoded)
	// followed by an 'e'. For example l4:spam4:eggse corresponds to ['spam',
	// 'eggs'].

	// TODO implement
}

