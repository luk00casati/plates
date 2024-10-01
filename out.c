#include <cpiatti.h> 
 #include <stdio.h> 
 #include <stdlib.h> 
 #include <signal.h> 
 
 void transpiledcode(struct Stack* s){ 
 init_stack( s);

//stanspiledcode

push( s, 1  );
push(  s, 2  );
for (unsigned int i = 0; i <  20 ; i++) {
copy(  s );
rot(  s );
sum(  s );
 }
put(  s );
}

//end

//void handle_signal(int signal){ 
 //deinit_stack( s); 
 //fprintf(stderr, SIGERRS); 
 //exit(0); 
 //} 
 
 int main(){ 
    struct Stack s;
     //signal(SIGINT, handle_signal); 
     transpiledcode(&s); 
     deinit_stack( &s);  
     return 0; 
 }