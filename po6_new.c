#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static int id=1;//for users while registering 

typedef struct admninfo{
	int phone;
	char id[100],name[100],email[100],password[100];	
}adminInfo;

typedef struct userinfo{
	int phone,passportno;
	char name[100],email[100],password[100],id[100],date[100],time[100];
	
}userData;

typedef struct logincred{
	char id,password;
}loginCred;

bool verifyCred(loginCred data){
	
}


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
		scanf("%d",&tmp);
		if(tmp==1){
			loginCred data;
			printf("Enter the id: ");
			scanf("%s",data.id);
			printf("\nEnter the passwd: ");
			scanf("%s",data.password);
			
		}	
	}	
}
