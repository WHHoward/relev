#include"basic_level.h"
#include <string>
/* 
0->HINI
1->HDEL
2->HEXITS
3->HGET
4->HGETALL
5->HINCRBY X
5->HKEYS 
6->HLEN
7->HMGET
8->HMSET
9->HSET
10->HSETNX
11->HVALS

*/

char* order_table[12]={"HINIT","HDEL","HEXITS","HGET","HGETALL",
"HKEYS","HLEN","HMGET","HMSET","HSET","HSETNX","HVALS"};
int numoftable;
uint8_t t_key[KEY_LEN],t_value[VALUE_LEN];
char name[10];
level_hash* t[10];
int main()
{
    
    printf("请输入命令\n");
    int op;
    while(1)
    {
        char order[10];
        scanf("%s",order);
        for(int i=0;i<12;i++) 
            if(!strcmp(order,order_table[i])) op=i;
        switch (op)
        {
            case 0:
            {
                memset(name,0,sizeof(name));
                uint64_t size;
                scanf("%s%lu",name,&size);
                t[numoftable++]=level_init(size,name);
                break;   
            }
            case 1:
            {
                memset(t_key,0,sizeof(t_key));
                memset(name,0,sizeof(name));
                scanf("%s%s",name,t_key);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name))  printf("(intergar)%d\n",level_delete(t[i],t_key));
                }
            }
            case 2:
            {
                memset(name,0,sizeof(name));
                memset(t_key,0,sizeof(t_key));
                scanf("%s%s",name,t_key);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                        if(!level_dynamic_query(t[i],t_key))
                            printf("(intergar)1\n");
                }
            }
            case 3:
            {
                memset(name,0,sizeof(name));
                memset(t_key,0,sizeof(t_key));
                scanf("%s%s",name,t_key);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        
                        if(t_value!=NULL) printf("%s\n",t_value);
                        else printf("(nil)\n");
                    }          
                }
            }
            case 4:
            {
                memset(name,0,sizeof(name));
                scanf("%s",name);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        for(int j=0;i<t[i]->addr_capacity;j++)
                        {
                            for(int k=0;k<4;k++)
                            {
                                if(t[i]->buckets[j]->token[k])
                                    printf("%s %s\n",t[i]->buckets[j]->slot[k].key,t[i]->buckets[j]->slot[k].value);
                            }
                        }
                    }
                }
            }
            case 5:
            {
                memset(name,0,sizeof(name));
                scanf("%s",name);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        for(int j=0;i<t[i]->addr_capacity;j++)
                        {
                            for(int k=0;k<4;k++)
                            {
                                if(t[i]->buckets[j]->token[k])
                                    printf("%s\n",t[i]->buckets[j]->slot[k].key);
                            }
                        }
                    }
                }
            }
            case 6:
            {
                memset(name,0,sizeof(name));
                scanf("%s",name);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        printf("(intergar)%d\n",t[i]->level_item_num[0]+t[i]->level_item_num[1]);
                    }
                }
            }
            case 7:
            {
                memset(name,0,sizeof(name));
                memset(t_key,0,sizeof(t_key));
                scanf("%s",name);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        char temp[1000];
                        scanf("%[^\n]",temp);
                        while(sscanf(temp,"%s",t_key))
                        {
                            memset(t_value,0,sizeof(t_value));
                            strcpy((char *)t_value,(const char *)level_dynamic_query(t[i],t_key));
                            if(t_value!=NULL) printf("%s\n",t_value);
                            else printf("(nil)\n");
                        }
                    }
                }
            }
            case 8:
            {
                memset(name,0,sizeof(name));
                memset(t_key,0,sizeof(t_key));
                memset(t_value,0,sizeof(t_value));
                scanf("%s",name);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        char temp[1000];
                        scanf("%[^\n]",temp);
                        while(sscanf(temp,"%s%s",t_key,t_value))
                        {
                            level_insert(t[i],t_key,t_value);
                        }
                    }
                }
            }
            case 9:
            {
                memset(t_key,0,sizeof(t_key));
                memset(name,0,sizeof(name));
                memset(t_value,0,sizeof(t_value));
                uint8_t new_value[VALUE_LEN];
                scanf("%s%s%s",name,t_key,new_value);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        if(level_dynamic_query(t[i],t_key)==NULL) 
                        {
                            level_insert(t[i],t_key,new_value);
                            printf("(interger) 1\n");
                        }
                        else
                        {
                            level_update(t[i],t_key,new_value);
                            printf("(interger) 0\n");
                        }
                        
                    }
                }
            }
            case 10:
            {
                memset(t_key,0,sizeof(t_key));
                memset(name,0,sizeof(name));
                memset(t_value,0,sizeof(t_value));
                uint8_t new_value[VALUE_LEN];
                scanf("%s%s%s",name,t_key,t_value);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        if(level_dynamic_query(t[i],t_key)==NULL) 
                        {
                            level_insert(t[i],t_key,new_value);
                            printf("(interger) 1\n");
                        }
                        else
                        {
                            printf("(interger) 0\n");
                        }
                        
                    }
                }
            }
            case 11:
            {
                memset(name,0,sizeof(name));
                scanf("%s",name);
                for(int i=0;i<numoftable;i++)
                {
                    if(!strcmp(name,t[i]->name)) 
                    {
                        for(int j=0;i<t[i]->addr_capacity;j++)
                        {
                            for(int k=0;k<4;k++)
                            {
                                if(t[i]->buckets[j]->token[k])
                                    printf("%s\n",t[i]->buckets[j]->slot[k].value);
                            }
                        }
                    }
                }
            }
            case 12:
            {

            }
        }
    }
    return 0;
}