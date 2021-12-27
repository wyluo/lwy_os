#include "../include/list.h"

struct xLIST List_Test;//define list origin node

struct xLIST_ITEM List_Item1;//define node1, node2, node3
struct xLIST_ITEM List_Item2;
struct xLIST_ITEM List_Item3;

int main(void)
{
    vListInitialise(&List_Test);//init list origin node
    
    vListInitialiseItem(&List_Item1);//init node1
    List_Item1.xItemValue = 1;

    vListInitialiseItem(&List_Item2);//init node2
    List_Item2.xItemValue = 2;

    vListInitialiseItem(&List_Item3);//init node3
    List_Item3.xItemValue = 3;

    vListInsert( &List_Test, &List_Item2);
    vListInsert( &List_Test, &List_Item1);
    vListInsert( &List_Test, &List_Item3);

    for(;;)
	{
		//nothine do
	}
}
