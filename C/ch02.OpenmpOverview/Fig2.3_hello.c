/*

NAME:   Hello

Description: print "hello world" from multiple threads using OpenMP

History: Written by Tim Mattson March 2023.

License: Creative Commons with Attribution (CC BY).  See the file ../../License for details

*/
#include <stdio.h>
#include <omp.h>
int main()
{
    #pragma omp parallel 
    {
       int id = omp_get_thread_num ();  
       printf("hello %d ",id); 
       printf("world %d\n",id);
    } 
}
