#include <stdio.h>
#include <string.h>
typedef struct{
int i_val;
double f_val;
char s_val[100];
int b_val;
}Stack;
Stack st[100000];
Stack s;
int i;
int counter = 0;
Stack pop(){
counter--;
Stack t = st[counter];
return t;
}
void push(Stack stk)
{
st[counter]=stk;
counter++;
}
void main(){
s.i_val =2;
push(s);
s.i_val =3;
push(s);
i = pop().i_val + pop().i_val;
s.i_val = i;
push(s);
s.b_val=1;
push(s);
s.f_val =2.300000;
push(s);
strcpy(s.s_val,"Hello\n");
push(s);
s = pop();
printf("%s",s.s_val);
}
