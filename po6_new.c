#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

static int id=1;//for users while registering

typedef struct admninfo{
	long long int phone;
	char adminId[100],fname[100],lname[100],email[100],password[100];
}adminInfo;

typedef struct userinfo{
	long long int phone,passportno;
	char fname[100],lname[100],email[100],password[100],userId[100];

}userInfo;

typedef struct logincred{
	char id[100],password[100];
}loginCred;

typedef struct dat{
    int dd,mm,yyyy;
}dateData;

typedef struct tim{
    int hh,mm,ss;
}timeData;

typedef struct flightinfo{
    char flightNo[100],source[100],destn[100],stop[100],category[100],meal[100],type[100];
    int amount,seat;//seats avaial
    timeData time;
    dateData date;
    bool stp;//is there a stop for this flight
}flightInfo;

typedef struct quer{
    char source[100],dest[100];
    dateData date;
    timeData timeAfter;
    timeData timeBefore;
}query;

typedef struct creddata{//used to check if id is matching or passwd or both
    bool id;
    bool password;
}credData;
// ####################### administrator functions
// verify the credentials
credData verifyCredAdmin(loginCred cred){
    FILE *infile;
    infile = fopen ("adminData2.txt","r");
    if(infile==NULL){
        printf("ERROR 404.....\nFile Not Found\n");
    }
    credData tmp;
    tmp.id=false;
    tmp.password=false;
    adminInfo data;
    while (fread (&data, sizeof(adminInfo), 1, infile)){
        //printf ("Name = %s   id = %s   email = %s  pass=%s",
        //      data.name, data.adminId,data.email,data.password);      debug line
        if(strcmp(data.adminId,cred.id)==0){
            tmp.id=true;
            if(strcmp(data.password,cred.password)==0){
                //printf("found user \n");
                 tmp.password=true;//credentials match
                 fclose(infile);
                 return tmp;
            }
        }
    }
    fclose(infile);
    return tmp;
}
// manage passenger
void managePass(){

}
// update passenger reservation
void updatePass(){

}
// update Profile
void updateAdminProfile(loginCred data){

}
//verify existance pf id
bool verifyAdminId(char *id){

}
//new admin signup
bool signUpAdmin(){
    printf("########################### \nSign Up");
    FILE *outfile,*infile;
    outfile=fopen("adminData2.txt","a");
    if(outfile==NULL){
        outfile=fopen("adminData2.txt","w");
    }
    adminInfo data;
    char pass[100]="#",pass2[100]="0",tmpid[100];
    bool flag=true;
    credData verifyid;
    while(1){
        printf("1).AdminId : ");
        scanf("%s",tmpid);
        loginCred tmpData;
        strcpy(tmpData.id,tmpid);
        strcpy(tmpData.password,"");
        verifyid=verifyCredAdmin(tmpData);
        //verifyid=false;
        if(verifyid.id==false){
            strcpy(data.adminId,tmpid);
            printf("id %s \n",data.adminId);
            break;
        }
        else{
            printf("Error... This Id is already taken...Reenter Id\n");
        }
    }
    printf("2).First Name : ");
    scanf("%s",data.fname);
    printf("3).Last Name : ");
    scanf("%s",data.lname);
    while(strcmp(pass,pass2)!=0){
        if(flag==false){
            printf("Error.. the passwords do not match... \n");
        }
        printf("4).password : ");
        scanf("%s",pass);
        printf("Reenter password : ");
        scanf("%s",pass2);
        if(strcmp(pass,pass2)!=0){
            flag=false;

        }
    }
    strcpy(data.password,pass);
    printf("5).email : ");
    scanf("%s",data.email);
    printf("6).Phone number : ");
    scanf("%lld",&data.phone);
    /*
        the file handling part


    */
    fwrite(&data,sizeof(adminInfo),1,outfile);//writing in file
    printf("Updated Information Succesfully......\n");
    fclose(outfile);
    return true;
    /*infile = fopen ("adminData1.txt","r");
    if(infile==NULL){
        printf("no infile present\n");
    }                                                                       // debuugging code
    while (fread (&data, sizeof(adminInfo), 1, infile))
      printf ("Name = %s   id = %s   email = %s  pass=%s",
              data.name, data.adminId,data.email,data.password);
    fclose(infile);
`   */
}
//add/update flight information
void editFlightInfo(){
    printf("########################### \nEdit Flight Information\n");
    flightInfo data;
    FILE *outfile;
    outfile=fopen("flightInfo.txt","a");
    if(outfile==NULL){
        outfile=fopen("flightInfo.txt","w");
    }
    bool flag=false;
    char tmp[100];
    printf("1).Type of flight Intl/Domestic :");
    scanf("%s",data.type);
    printf("2).Enter Flight Number :");
    scanf("%s",data.flightNo);
    printf("3).Source of Flight :");
    scanf("%s",data.source);
    printf("4).Destination of Flight :");
    scanf("%s",data.destn);
    printf("5).Is there a stop of this flight enter yes/no :");
    scanf("%s",tmp);
    if(strcmp(tmp,"yes")==0){
        printf("Enter the stop name :");
        scanf("%s",data.stop);
        data.stp=true;
    }
    else{
        data.stp=false;//no stop flight
    }
    printf("6).Enter date : \nEnter DD(date date): ");
    scanf("%d",&data.date.dd);
    printf("Enter MM(month month : ");
    scanf("%d",&data.date.mm);
    printf("Enter YYYY(year) : ");
    scanf("%d",&data.date.yyyy);
    printf("7).Enter Time : \nEnter HH(hour 24 hr format) : ");
    scanf("%d",&data.time.hh);
    printf("Enter mm(minutes) : ");
    scanf("%d",&data.time.mm);
    printf("Enter ss(seconds) : ");
    scanf("%d",&data.time.ss);
    printf("8).Type of Class :");
    scanf("%s",data.category);
    printf("9).Meal : ");
    scanf("%s",data.meal);
    printf("10).Enter amount : ");
    scanf("%d",&data.amount);
    printf("11).Seats Avaialabe : ");
    scanf("%d",&data.seat);
    /*
        file handling part
    */
    fwrite(&data,sizeof(flightInfo),1,outfile);//writing in file
    printf("Flight Information Updated Succefully...\n");
}
//admin SignIn
bool signInAdmin(){
            loginCred data;
            int tmp,tmp2;
			credData verify;
			printf("########################### \nSign In");
			printf("\nEnter the id for Sign in : ");
			scanf("%s",data.id);
			printf("Enter the password for Sign in : ");
			scanf("%s",data.password);
			//                     printf("%s sca  %s",data.id,data.password);
			verify=verifyCredAdmin(data);//verifying the credentials
			if(verify.password==false){
                 printf("###########################\n");
				printf("\nIncorrest id / password");
			}
			else{
			    printf("###########################\n");
                printf("\nLogin Credentials correct , succesful Administrator Login\n");
                printf("Select From the menu:\n1).Manage Passengers\n2).Update passenger Status\n3).edit Profile\n4).Edit Flight Information\n");
                scanf("%d",&tmp);
                if(tmp==1){
                    managePass();//manage the passengers
                }
                else{
                    if(tmp==2){
                        updatePass();//update the passengers
                    }
                    else{
                        if(tmp==3)
                            updateAdminProfile(data);// update admin prfoile data
                        else{
                            editFlightInfo();//updating flight Information
                        }
                    }
                }
			}
}




// ####################### User functions
// verify the credentials
credData verifyCredUser(loginCred cred){
    FILE *infile;
    infile = fopen ("userData2.txt","r");
    if(infile==NULL){
        printf("ERROR 404.....\nFile Not Found\n");
    }
    credData tmp;
    tmp.id=false;
    tmp.password=false;
    userInfo data;
    while (fread (&data, sizeof(adminInfo), 1, infile)){
        //printf ("Name = %s   id = %s   email = %s  pass=%s",
        //      data.name, data.userId,data.email,data.password);           // debug line
        if(strcmp(data.userId,cred.id)==0){
            tmp.id=true;
            if(strcmp(data.password,cred.password)==0){
                tmp.password=true;
                printf("found user \n");
                fclose(infile);
                return tmp;//credentials match
            }
        }
    }
    fclose(infile);
    return tmp;

}
// view flght deatails
void viewFlight(){

}
//
void ticketStatus(loginCred data){

}
//
void updateUserFile(loginCred data){

}
//user SignIn
bool signInUser(){
    loginCred data;
    int tmp,tmp2;
    credData verify;
    printf("########################### \nSign In\n");
    printf("\nEnter the id for Sign in : ");
    scanf("%s",data.id);
    printf("\nEnter the password for Sign in : ");
    scanf("%s",data.password);
    verify=verifyCredUser(data);//verifying the credentials
    if(verify.password==false){
        printf("###########################\n");
        printf("\nIncorrect id / password entered\n");
    }
    else{
        printf("###########################\n");
        printf("\nLogin Credentials correct , succesful Passenger Login");
        printf("Select From the menu:\n1).Request to view the available flights as per requirement\n2).Ticket Status\n3).Edit Profile");
        scanf("%d",&tmp);
        if(tmp==1){
            printf("###########################\n");
            printf("Enter the following details to view flight : \n");
            viewFlight();
        }
        else{
            if(tmp==2){
                printf("###########################\n");
                printf("The ticket status\n");
                ticketStatus(data);
            }
            else{
                updateUserFile(data);
            }
        }
    }
}
//check wether the ID is available or not
bool verifyUserId(char *userId){
}
//sign up of new iser
bool signUpUser(){
    FILE *infile,*outfile;
    outfile=fopen("userData2.txt","a");
    if(outfile==NULL){
        outfile=fopen("userData2.txt","w");
    }
    userInfo data;
    char pass[100]="#",pass2[100]="0",tmpid[100];
    bool flag=true;
    credData verifyid;
    loginCred tmpData;
    while(1){
        printf("1).userId : ");
        scanf("%s",tmpid);
        strcpy(tmpData.id,tmpid);
        strcpy(tmpData.password,"");
        verifyid=verifyCredUser(tmpData);
        if(verifyid.id==false){
            strcpy(data.userId,tmpid);
            break;
        }
        else{
            printf("Error... This Id is already taken...Reenter Id\n");
        }
    }
    printf("2).First Name : ");
    scanf("%s",data.fname);
    printf("3).Last Name : ");
    scanf("%s",data.lname);
    while(strcmp(pass,pass2)!=0){
        if(flag==false){
            printf("Error.. the passwords do not match... \n");
        }
        printf("4).password : ");
        scanf("%s",pass);
        printf("Reenter password : ");
        scanf("%s",pass2);
        if(strcmp(pass,pass2)!=0){
            flag=false;

        }
    }
    strcpy(data.password,pass);
    printf("5).email : ");
    scanf("%s",data.email);
    printf("6).Passport Number : ");
    scanf("%d",&data.passportno);
    printf("7).Phone Number : ");
    scanf("%lld",&data.phone);
    /*
        the file handling part

    */
    fwrite(&data,sizeof(userInfo),1,outfile);
    printf("Updated Information Succesfully......\n");
    fclose(outfile);
    return true;
}





int main(){
	int tmp,tmp2,i,j;
	printf("Welcome To the Portal\n");
    while(1){
        printf("###########################\n");
        printf("Enter The Category of User :\n");
        printf("1).Enter as an Administrator \n2).Enter as an User\n3).Not much to do today\n");
        scanf("%d",&tmp);
        // 1 for admin 2 for user
        if(tmp==1){//*********Administrator
            printf("###########################\nAdministrative Area\n");
            printf("Select From the menu:\n1).SignIn\n2).Signup\n");
            scanf("%d",&tmp);
            if(tmp==1){
                signInAdmin();
            }
            else{// for new Admin User
                printf("###########################\n");
                printf("Fill the given below details : \n");
                bool signupVerify=signUpAdmin();//for new user Signup if signup is succeful take to the sign in page
                //signupVerify=true;
                if(signupVerify==true){
                    printf("Redeirecting to Sign In page.... \n");
                    signInAdmin();
                }
            }
        }
        else{//***************Passenger
            if(tmp==2){
                printf("###########################\nTicket Booking and Cancellation Area\n");
                printf("Select From the menu:\n1).SignIn\n2).Signup\n");
                scanf("%d",&tmp);
                if(tmp==1){
                    signInUser();
                }
                else{//for new User
                    printf("###########################\n");
                    printf("Fill the given below details : \n");
                    bool userVerify=signUpUser();
                    if(userVerify==true){
                        printf("Redirecting to Sign In Page.... \n");
                        signInUser();
                    }

                }
            }
            else{
                printf("Thank You for Your visit\n");
                break;
            }

        }
    }
}
