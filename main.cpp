#include"basic_level.h"
#include <string>

char* name_table[10];
int numoftable;
const char* instructions[10];
level_hash* t[10];
int main()
{
    int op = 1;
    instructions[1] = "HINI";
    printf("请输入命令，");
    while(1)
    {
        char *temp_s = (char *)malloc(sizeof(char) * 10); 
        printf("请输入你要进行的操作\n");
        scanf("%s",temp_s);
        for(int i = 1; i <= 10; i++)
        {
            if(strcmp(temp_s,instructions[1]))
            {
                printf("请输入哈希表的名字和规模\n");
                uint64_t temp;
                char *temp_ss = (char *)malloc(sizeof(char) * 10);  
                scanf("%lu%s",&temp,temp_ss);
                t[++numoftable] = level_init(temp,temp_ss);
            }
        }
        break;
    }
    return 0;
}