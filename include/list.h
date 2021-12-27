#ifndef LIST_H
#define LIST_H

#include <stdint.h>
#include <stddef.h>
#include "../include/portmacro.h"

struct xLIST_ITEM{
    TickType_t xItemValue;
    struct xLIST_ITEM *pxNext;
    struct xLIST_ITEM *pxPrevious;
    void* pvOwner;
    void* pvContainer;
};
typedef struct xLIST_ITEM ListItem_t;

//define mini node structer, as end of two ways list
struct xMINI_LIST_ITEM{
    TickType_t xItemValue;
    struct xLIST_ITEM *pxNext;
    struct xLIST_ITEM *pxPrevious;
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;

typedef struct xLIST{
    UBaseType_t uxNumberOfItems;//list node counter
    ListItem_t *pxIndex;//list node pointer
    MiniListItem_t xListEnd;//the last node of list
}List_t;

/*
***********************
*    global define    *
***********************
*/
#define listSET_LIST_ITEM_OWNER(pxListItem, pxOwner)\
                                ((pxListItem)->pvOwner = (void*) (pxOwner))

#define listGET_LIST_ITEM_OWNER(pxListItem)\
                                ((pxListItem)->pvOwner)

#define listSET_LIST_ITEM_VALUE(pxListItem, xValue)\
                                ((pxListItem)->xItemValue = (xValue))

#define listGET_LIST_ITEM_VALUE(pxListItem)\
                                ((pxListItem)->xItemValue)

#define listGET_ITEM_VALUE_OF_HEAD_ENTRY(pxList)\
                                        (((pxList)->xListEnd).pxNext->xItemValue)

#define listGET_HEAD_ENTRY(pxList)\
                            (((pxList)->xListEnd).pxNext)

#define listGET_NEXT(pxListItem)\
                    ((pxListItem)->pxNext)

#define listGET_END_MARKER(pxList)\
                            (ListItem_t const *) (&((pxList)->xListEnd))

#define listLIST_IS_EMPTY(pxList)\
                            ((BaseType_t) ((pxList)->uxNumberOfItems == (UBaseType_t) 0))

#define listCURRENT_LIST_LENGTH(pxList)\
                                ((pxList)->uxNumberOfItems)

#define listGET_OWNER_OF_NEXT_ENTRY(pxTCB,pxList)\
{\
    List_t * const pxConstList = pxList;\
    pxConstList->pxIndex = pxConstList->pxIndex->pxNext;\
    if( (void*) ( pxConstList->pxIndex == (void*) &(pxConstList->xListEnd) ) )\
    {\
        pxConstList->pxIndex = pxConstList->pxIndex->pxNext;\
    }\
    pxTCB = pxConstList->pxIndex->pvOwner;\
}\

#define listGET_OWNER_OF_HEAD_ENTRY( pxList )  ( (&( ( pxList )->xListEnd ))->pxNext->pvOwner )

void vListInitialise(List_t * const pxList);
void vListInitialiseItem(ListItem_t * const pxItem);
void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem);
void vListInsert(List_t * const pxList, ListItem_t * const pxNewListItem);
UBaseType_t uxListRemove(ListItem_t * const pxItemToRemove);

#endif
