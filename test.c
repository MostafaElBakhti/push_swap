#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


int main(){

	typedef struct test
	{
		char *name;
		int age;
		struct test *next;
	}test1 ;


	typedef struct test2
	{
		char *name;
		int age;
		struct test2 *next;
	}t1337 ;

	t1337 *p1337  = malloc (sizeof (t1337)) ;
	p1337->name = malloc (20) ;
	strcpy (p1337->name , "1337") ;
	p1337->age = 20 ;


	printf("%zu\n" , sizeof(test1)) ;
	test1 *person = malloc(sizeof(test1)) ; 
	test1 *person2 = malloc(sizeof(test1)) ; 
	person->name = malloc(20) ;
	person2->name = malloc(20) ;
	strcpy(person->name, "Mel-Bakh") ;
	strcpy(person2->name, "Mel-Bakh2") ;
	person->age = 25 ;
	person2->age = 25 ;
	person->next = p1337 ;
	p1337->next = person2 ;
	person2->next = NULL ;
	printf("Name: %s, Age: %d , Adress %p", (*person).name, person->age , person->next) ;
	printf("\nName: %s, Age: %d , Adress %p", person->next->name, person->next->age , person2->next) ;

}