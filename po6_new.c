#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	int tmp,tmp2,i,j;
	printf("Category of User :\n");
	printf("1).Administrator \n2)User");
	scanf("%d",&tmp);
	// 1 for admin 2 for user
	if(tmp==1){
		/*
		for admin fnctns are
			~login
			~Register
			~Manage PAssengers
			~Update the Pass Status
			~Edit Profile	
		*/
		printf("Select From the menu:\n1).Login\n2).Register\n3).Manage Passengers\n4).Update the Passenger Status\n5)Edit Profile");
	}	
}
