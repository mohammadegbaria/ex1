#include </home/mtm/public/2122b/ex1/RLEList.h>
#include "stdlib.h"
#include "assert.h"
#include "string.h"

struct RLEList_t{
    char character;
    int occur;
    RLEList next;
    RLEList prev;
};

//implement the functions here

RLEList RLEListCreate(){
    RLEList ptr = malloc(sizeof(*ptr));

    if(!ptr)
    {
        return NULL;
    }

    ptr->character = '\0';
    ptr->occur = 0;
    ptr->next = NULL;
    ptr->prev = NULL;

    return ptr;
}

void RLEListDestroy(RLEList list){
    while(list){
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

RLEList get_last_node(RLEList list){
    RLEList helper = list;
    while(helper->next != NULL){
        helper = helper->next;
    }
    return helper;
}

RLEListResult RLEListAppend(RLEList list, char value){
    if(!list || value == '\0'){
        return RLE_LIST_NULL_ARGUMENT;
    }

    if(list->character == '\0'){
        list->character = value;
        list->occur++;
        return RLE_LIST_SUCCESS;
    }

    RLEList last_node = get_last_node(list);

    if(last_node->character == value){
        last_node->occur++;
        return RLE_LIST_SUCCESS;
    }

    RLEList newList = RLEListCreate();
    if(!newList){
        return RLE_LIST_OUT_OF_MEMORY;
    }

    newList->character = value;
    newList->occur++;
    newList->prev = last_node;
    last_node->next = newList;
    return RLE_LIST_SUCCESS;
    }

int RLEListSize(RLEList list){
if(!list){
    return -1;
}
RLEList helper = list;
int size = 0;
while (helper)
{
    size += helper->occur;
    helper = helper->next;
}
return size;
}

RLEList my_remove(RLEList node){
       RLEList toDelete = node;
    if(node->prev == NULL){
        node = node->next;
        free(toDelete);
        return NULL;
    }
    if(node->next == NULL){
        node = node->prev;
        node->next = NULL;
        free(toDelete);
        return NULL;
    }

    RLEList _next_node = node->next;
    RLEList _prev_node = node->prev;
    _next_node->prev = _prev_node;
    _prev_node->next = _next_node;
    free(toDelete);
    return _prev_node;

}

void remove_node(RLEList node){
    RLEList help = my_remove(node);
    if(help == NULL)
    {
        return;
    }
    RLEList _next_node = help->next;
    if(_next_node->character == help->character)
    {
        help->occur += _next_node->occur;
        my_remove(_next_node);
    }
    //free(help);
    }

RLEList get_node(RLEList list, int index){
    assert(index >= 0);
    //printf("index:%d  list size:%d",index,RLEListSize(list));
    assert(index < RLEListSize(list));
    RLEList helper = list;
    int curr_size = helper->occur;
    while (index >= curr_size)
    {
        helper = helper->next;
        curr_size += helper->occur;
    }
    return helper;
}
RLEListResult RLEListRemove(RLEList list, int index){
    if(!list){
        //assert(list);
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index > RLEListSize(list) || index < 0){ 
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList node = get_node(list, index);

    if(node->occur == 1){
        if (index==0)
        {
            list=list->next;
            list->prev=NULL;
            free(node);
        }
        else{
        remove_node(node);
        }
        return RLE_LIST_SUCCESS;
    }
    node->occur-=1;
    return RLE_LIST_SUCCESS;
}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    if (!list)
    {
        if(result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    
    int size = RLEListSize(list);
    if(index < 0 || index >= size){
        if(result != NULL){
           *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }

    RLEList node = get_node(list, index);
    assert(node);
    char ch = node->character;
    if(result != NULL){
        *result = RLE_LIST_SUCCESS;
    }
    return ch;

}

int nodes_count(RLEList list){
    //assert(list);
    int count = 0;
    RLEList helper = list;
    while(helper){
        count++;
        helper = helper->next;
    }
    free(helper);
    return count;
}

void give_init_val(char *s, int len)
{
    int i = 0;
    while(i < len)
    {
        s[i++] = '\0';
    }
}
char* RLEListExportToString(RLEList list, RLEListResult* result){
    if(!list){
        if(result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int len = nodes_count(list);
    char *minimized = (char*)malloc(sizeof(*minimized)*sizeof(char)*len*3 + 1);
    if(minimized == NULL){
                if(result != NULL){
            *result = RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }
    char *helper2;
    helper2 = minimized;
    //give_init_val(minimized, len);
    char _occur, _character;
    RLEList helper = list;
    while(helper != NULL){
        _character = helper->character;
        _occur = helper->occur;
      //  if(strcmp("\\n", &_character) == 0){
           // sprintf(helper2, "%c%d%c", '\n', _occur, '\n');
        //}else{
            sprintf(helper2, "%c%d%c", _character, _occur, '\n');

       // }
        helper2+=3;
        helper = helper->next;
    }
            if(result != NULL){
            *result = RLE_LIST_SUCCESS;
        }
    return minimized;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if(!list || map_function == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList helper = list;
    char new_char;
    while(helper){
        new_char = map_function(helper->character);
        helper->character = new_char;
        helper = helper->next;
    }
    free(helper);
    return RLE_LIST_SUCCESS;
}

char get_char(RLEList node)
{
    return node->character;
}
