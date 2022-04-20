#include "RLEList.h"
#include <stdio.h>
#include <string.h>


 struct RLEList_t{
    char character;
    int occur;
    RLEList next;
    RLEList prev;
    //TODO: implement
};
RLEList RLEListCreate()
{   RLEList new_node=malloc(sizeof(*new_node));
    if(!new_node)
    {
      return NULL ;
      }
    new_node->character='\0';
    new_node->next=NULL;
    new_node->prev=NULL;
    new_node->occur=0;
    return new_node;

}
void RLEListDestroy(RLEList list)
{ 
    while(list)
    { 
        RLEList helper= list ;
        list = list->next;
        free(helper);
    }
}
RLEListResult RLEListAppend(RLEList list, char value)
{  
     RLEList helper=list;
     if (list==NULL||value=='\0')
     {
         return RLE_LIST_NULL_ARGUMENT;
     }
     
     while (helper->next!=NULL)
     {
         helper=helper->next;
     }
     
     if (helper->character=='\0')
     {
         helper->character=value;
         helper->occur++;
         free(helper);
         return RLE_LIST_SUCCESS;
     }
     

     if(helper->character==value)
          helper->occur++;
     else
     {
         RLEList new_node = RLEListCreate();
         if (new_node==NULL)
         {
             return RLE_LIST_OUT_OF_MEMORY;
         }
         new_node->character=value;
         new_node->occur=1;
         new_node->prev=helper;
         helper->next=new_node;
         free(new_node);
     }
     free(helper);
    return RLE_LIST_SUCCESS ;
    
}
int RLEListSize(RLEList list)
{
    int count = 0 ;
    if(!list)
      {
           return -1 ;
      } 
    count+= list->occur;
    RLEList helper=list->next;
    while (helper!=NULL)
    {
        count+= helper->occur;
        helper=helper->next;
    }
    free(helper);
    return count ;  

    
}
RLEListResult RLEListRemove(RLEList list, int index)
{
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    int current_index = 0;
    if( index > RLEListSize(list) || index<0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList helper = list ;
    while ( index > current_index )
    {
        current_index += helper->occur;
        if (current_index >= index)
        {
            break;
        }
        
        helper=helper->next;

    }
    if (helper->occur>1)
    {
        helper->occur-=1;
    }
    if (helper->occur==1)
    {
        
        if (helper->prev!=NULL)
        {
             RLEList prev_node = helper->prev ;
             RLEList next_node = helper->next ;
             prev_node->next=next_node;
             helper->prev=NULL;
             helper->next=NULL;
             free(next_node);
             free(prev_node);
        }
        else 
        { 
         RLEList next_helper = helper->next ;   
         if(next_helper==NULL)
            {
               RLEListDestroy(list);  
            }
         else
            {
                list=helper->next;
                
            }    
         free(next_helper);
        }
    }    
    free(helper);
    return RLE_LIST_SUCCESS;
}
char RLEListGet(RLEList list, int index, RLEListResult *result)
{ 
    if (!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT ;
        return 0;
    }
    if (RLEListSize(list)<index||index<0)
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS ;
        return 0;
    }
    int current_index = 0;
    RLEList helper = list ;
    while ( index > current_index )
    {
        current_index += helper->occur;
        if (current_index >= index)
        {
            break;
        }
        
        helper=helper->next;
    }
    result = RLE_LIST_SUCCESS ;
    char wanted_index = helper->character;
    free(helper);
    return wanted_index;
}
int count_nodes(RLEList list)
{
    int count= 0;
    if(!list)
    { 
        return 0;
    }
    RLEList helper= list;
    while (helper!=NULL)
    {
        count++;
    }
    free(helper);
    return count;
}
char* RLEListExportToString(RLEList list, RLEListResult* result)
{  
  char *string=(char*)malloc(sizeof(char)*((count_nodes(list)*3+1)));
  if (!list||string==NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT ;
        return NULL;
    }
   *string ="/0";
   RLEList helper = list ;
   char clean="/0";
   char *extract_ch=(char*)malloc(sizeof(char)*3);
   while (helper!=NULL)
   {    
       char occur_char =(char)helper->occur;
       char jumping [3]={'\','\','n''};
       strcat(extract_ch,&helper->character);
       strcat(extract_ch,&occur_char);
       strcat(extract_ch,jumping);
       strcat(string,extract_ch);
       strcpy(extract_ch,&clean);
       helper=helper->next;

   }
    free(helper);
    return string;
}
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList helper=list;
    while (helper)
    {
        helper->character=map_function(helper->character);
        helper = helper->next;
    }
    return RLE_LIST_SUCCESS;
}








//implement the functions here