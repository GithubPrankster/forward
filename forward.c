#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char name[64];
    char buf[128];
}expr;

expr funcs[16];
int funcnt = 0;

static int pop(int *stk, int *cnt){
    int res = stk[--(*cnt)];
    stk[*cnt] = 0;
    return res;
}

static inline void push(int *stk, int *cnt, const int val){
    stk[(*cnt)++] = val;
}

int stack[16];
int stkcnt = 0;

void eval(char *buf)
{
    while(*buf != '\0'){
        if(isdigit(*buf)){
            sscanf(buf, "%d", &stack[stkcnt]);

            int n = stack[stkcnt++];
            while(n != 0){
                n /= 10;
                ++buf;
            }
        }

        if(*buf == '+'){
            int a = pop(stack, &stkcnt);
            int b = pop(stack, &stkcnt);
            push(stack, &stkcnt, b + a);
        }

        if(*buf == '-'){
            int a = pop(stack, &stkcnt);
            int b = pop(stack, &stkcnt);
            push(stack, &stkcnt, b - a);
        }

        if(*buf == '*'){
            int a = pop(stack, &stkcnt);
            int b = pop(stack, &stkcnt);
            push(stack, &stkcnt, b * a);
        }

        if(*buf == '/'){
            int a = pop(stack, &stkcnt);

            if(a == 0){
                printf("Nice try. ");
                break;
            }

            int b = pop(stack, &stkcnt);
            push(stack, &stkcnt, b / a);
        }

        if(*buf == '.'){
            if(*(buf + 1) == '"'){
                buf += 3;
                char thing[128];
                int counterer = 0;
                while(*buf != '"'){
                    thing[counterer++] = *(buf++);
                }

                printf("%s ", thing);
                buf += strlen(thing);
            }else if(*(buf + 1) == 'S'){
                ++buf;
                for(unsigned int i = 0; i < stkcnt; i++){
                    printf("%d ", stack[i]);
                }
            }else{
                printf("%d ", pop(stack, &stkcnt));
            }
        }

        if(*buf == ':'){
            buf += 2;

            sscanf(buf, "%s", &funcs[funcnt].name);
            buf += strlen(funcs[funcnt].name) + 1;

            int cnt = 0;
            while(*buf != ';'){
                funcs[funcnt].buf[cnt++] = *(buf++);
            }

            funcs[funcnt].buf[cnt - 1] = '\0';

            buf += cnt;
            ++funcnt;
        }
        
        if(isalpha(*buf)){
            char thing[32];
            sscanf(buf, "%s", &thing);

            buf += strlen(thing);

            for (int i = 0; i < funcnt; i++){
                if(strstr(thing, funcs[i].name)){
                    eval(funcs[i].buf);
                }
            }
            
            if(strstr(thing, "DUP")){
                stack[stkcnt] = stack[stkcnt - 1];
                stkcnt++; // Put it here for sake of reading.
            }

            if(strstr(thing, "POP")){
                pop(stack, &stkcnt);
            }

            if(strstr(thing, "SPACES")){
                for(unsigned int i = 0; i < abs(pop(stack, &stkcnt)); i++){
                    printf(" ");
                } 
            }

            if(strstr(thing, "CR")){
                printf("\r\n");
            }

            if(strstr(thing, "EMIT")){
                printf("%c", pop(stack, &stkcnt));
            }

            if(strstr(thing, "SWAP")){
                int temp = stack[stkcnt];
                stack[stkcnt] = stack[stkcnt - 1];
                stack[stkcnt - 1] = temp;
            }
        }

        ++buf;
    }
}

int main(void)
{
    printf("FORWARD ver. 0.4, by Uneven Prankster @ 2020\n");
    char buf[256];
    while(fgets(buf, sizeof buf, stdin)){
        eval(buf);
        printf(" cool.\n");
    }
    return 0;
}