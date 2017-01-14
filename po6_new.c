#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
/*
    author :aman
*/

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

typedef struct dat{//date
    int dd,mm,yyyy;
}dateData;

typedef struct tim{//time
    int hh,mm,ss;
}timeData;

typedef struct flightinfo{
    char flightNo[100],source[100],destn[100],stop[100],category[100],meal[100],type[100];
    int amount,seat;//seats avaial
    timeData time;
    dateData date;
    bool stp;//is there a stop for this flight
}flightInfo;

typedef struct quer{//query
    char source[100],dest[100],flightNo[100];
    dateData date;
    timeData timeAfter;
    timeData timeBefore;
    userInfo userData;
}query;

typedef struct creddata{//used to check if id is matching or passwd or both and also contains  //amanpurwar
    bool id;
    bool password;
    userInfo userData;
    adminInfo adminData;
}credData;

typedef struct reservationRequestData{// for storing reservation request data
    char userId[100],flightNo[100],passfname[100],passlname[100],source[100],dest[100],status[100];
    dateData date;
    int cost,seat,available,age,passport;

}reserve;

typedef struct cancl{
    dateData date;
    char flightNo[100],userId[100];
}cancel;
/*typdef struct updateStatus{
    char userId[100],flightNo[100],passfname[100],passlname[100],source[100],dest[100],status[100];
    dateData date;//author :amanpurwar
    int cost,seats,available,age,passport;
}status;*/

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
                 tmp.adminData=data;
                 fclose(infile);
                 return tmp;
            }
        }
    }
    fclose(infile);
    return tmp;
}

// update passenger reservation
void updatePassStatus(){
    FILE *infileRequest,*infileFlight,*outfile;
    flightInfo flightData;
    reserve resData;
    printf("########################### \nPassenger Status Update Started.....\n");
    infileRequest=fopen("reserveRequest1.txt","r");
    infileFlight=fopen("flightInfo1.txt","r");
    outfile=fopen("success.txt","a");
    if(outfile==NULL){
        outfile=fopen("success.txt","w");
    }
    while(fread (&resData, sizeof(reserve), 1, infileRequest)){
        printf("%s %s \n",resData.flightNo,resData.passfname);        //debuging code
        while(fread (&flightData, sizeof(flightInfo), 1, infileFlight)){
            if(strcmp(flightData.flightNo,resData.flightNo)==0){
                if(flightData.seat>=resData.seat||true){
                    strcpy(resData.status,"Success");
                    //printf("sfvsfg\n");
                    fwrite(&resData,sizeof(reserve),1,outfile);//writing in file
                }
            }
        }
    }
    fclose(outfile);
    fclose(infileRequest);
    fclose(infileFlight);
}
// manage passenger
void managePass(){
    printf("###########################\nManage Passengers\n1).Update passenger Status\n2).Exit\n");
    int tmp;
    scanf("%d",&tmp);
    if(tmp==1){
        updatePassStatus();//update the passengers status
    }
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
    while (fread (&data, sizeof(adminInfo), 1, infile))//amanpurwar
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
    outfile=fopen("flightInfo1.txt","a");
    if(outfile==NULL){
        outfile=fopen("flightInfo1.txt","w");
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
    fclose(outfile);
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

                while(1){
                    printf("###########################\n");
                    printf("Select From the menu:\n1).Manage Passengers\n2).edit Profile\n3).Edit Flight Information\n4).Exit\n");
                    scanf("%d",&tmp);
                    if(tmp==1){
                        managePass();//manage the passengers
                    }
                    else{
                        if(tmp==2&&false){
                            updatePassStatus();//update the passengers
                        }
                        else{
                            if(tmp==2)
                                updateAdminProfile(data);// update admin prfoile data
                            else{
                                if(tmp==3)
                                    editFlightInfo();//updating flight Information
                                else{
                                    break;
                                }
                            }
                        }
                    }
                }
			}
}




// ####################### User functions
// verify the credentials
credData verifyCredUser(loginCred cred){
    FILE *infile;
    infile = fopen ("userData3.txt","r");
    if(infile==NULL){
        printf("ERROR 404.....\nFile Not Found\n");
    }
    credData tmp;
    tmp.id=false;
    tmp.password=false;
    userInfo data,last;
    while (fread (&data, sizeof(userInfo), 1, infile)){
        //printf ("fName = %s  lname= %s id = %s   email = %s  pass=%s\n",
            //  data.fname,data.lname, data.userId,data.email,data.password);           // debug line
        if(strcmp(data.userId,cred.id)==0){
            tmp.id=true;
            last=data;
        }
    }
    if(strcmp(last.password,cred.password)==0){
                tmp.password=true;
                tmp.userData=last;
                //printf("found user \n");
                fclose(infile);
                return tmp;//credentials match
            }

    fclose(infile);
    return tmp;

}
//to check if the flight time is in between queried time
bool timeCheck(timeData flight,timeData after,timeData before){
    bool flag1=false,flag2=false;
    if(flight.hh>=after.hh){
        if(flight.mm>=after.mm){
            if(flight.ss>=after.ss){
                flag1=true;
            }
        }
    }
    if(flight.hh<=before.hh){
        if(flight.mm<=before.mm){
            if(flight.ss<=before.ss){
                flag2=true;
            }
        }
    }
    if(flag1==true&&flag2==true){
        return true;
    }
    else{
        return false;
    }
}
//
void reservation(query Query){
    printf("###########################\nSeat Reservation :\n Enter the details Below :\n");
    reserve data;
    FILE *outfile;
    outfile=fopen("reserveRequest1.txt","a");
    if(outfile==NULL){
        outfile=fopen("reserveRequest1.txt","w");
    }
    strcpy(data.userId,Query.userData.userId);
    strcpy(data.source,Query.source);
    strcpy(data.dest,Query.dest);
    strcpy(data.flightNo,Query.flightNo);
    strcpy(data.status,"pending");
    data.date=Query.date;
    //printf("Date %d:%d:%d",data.date.dd,data.date.mm,data.date.yyyy);     //debuging
    printf("1).Passenger First Name : ");
    scanf("%s",data.passfname);
    printf("2).Passenger Last Name : ");
    scanf("%s",data.passlname);
    printf("3).Passenger Age : ");
    scanf("%d",&data.age);
    printf("4).Passenger Passport Number : ");
    scanf("%d",&data.passport);
    data.seat=1;
    fwrite(&data,sizeof(reserve),1,outfile);
    printf("Reservation Request Done Succesfully......\n");
    fclose(outfile);
    FILE *infile = fopen ("reserveRequest1.txt","r");
    if(infile==NULL){
        printf("no infile present\n");
    }                                                                       // debuugging code
    while (fread (&data, sizeof(reserve), 1, infile))
      printf ("Name = %s   id = %s   email = %s  pass=%s\n",
              data.passfname, data.userId,data.passlname,data.flightNo);
    fclose(infile);

}
// view flght deatails
void viewFlight(loginCred loginData){
    query Query;
    flightInfo data;
    int tmp;
    bool flag=false;//to check if flight found or not
    FILE *infile;
    credData user=verifyCredUser(loginData);
    infile =fopen("flightInfo1.txt","r");
    if(infile==NULL){
        printf("no infile present\n");
    }
    printf("1).Enter Source :");
    scanf("%s",Query.source);
    printf("2).Enter Destination :");
    scanf("%s",Query.dest);
    printf("3).Enter Flight Date : \nEnter DD(date date): ");
    scanf("%d",&Query.date.dd);
    printf("Enter MM(month month : ");
    scanf("%d",&Query.date.mm);
    printf("Enter YYYY(year) : ");
    scanf("%d",&Query.date.yyyy);
    printf("4).Enter the time after which Flight is to seen : \nEnter HH(hour 24 hr format) : ");
    scanf("%d",&Query.timeAfter.hh);
    printf("Enter mm(minutes) : ");
    scanf("%d",&Query.timeAfter.mm);
    printf("Enter ss(seconds) : ");
    scanf("%d",&Query.timeAfter.ss);
    printf("5).Enter the time before which Flight is to seen : \nEnter HH(hour 24 hr format) : ");
    scanf("%d",&Query.timeBefore.hh);
    printf("Enter mm(minutes) : ");
    scanf("%d",&Query.timeBefore.mm);
    printf("Enter ss(seconds) : ");
    scanf("%d",&Query.timeBefore.ss);
    /*
        File handling part

    */
    printf("Query Search Completed.....\n");
    while (fread (&data, sizeof(flightInfo), 1, infile)){
        //printf("Flight No. : %s , Time(hh:mm:ss) : %d:%d:%d , Flight type : %s , Seats Available : %d , Amount : %d \n",data.flightNo,data.time.hh,data.time.mm,data.time.ss,data.type,data.seat,data.amount);
        if(strcmp(data.source,Query.source)==0){
            if(strcmp(data.destn,Query.dest)==0||strcmp(data.stop,Query.dest)==0){
                if(data.date.yyyy==Query.date.yyyy){
                    if(data.date.mm==Query.date.mm){
                        if(data.date.dd==Query.date.dd){
                            bool timecheck=timeCheck(data.time,Query.timeAfter,Query.timeBefore);
                            if(timecheck==true){
                                if(!flag){
                                    printf("###########################\n");
                                    printf("The follwing flights were Found : \n");
                                }
                                flag=true;
                                printf("Flight No. : %s , Time(hh:mm:ss) : %d:%d:%d , Flight type : %s , Seats Available : %d , Amount : Rs.%d \n",data.flightNo,data.time.hh,data.time.mm,data.time.ss,data.type,data.seat,data.amount);
                            }
                        }
                    }
                }
            }
        }
    }
    if(flag==false){
        printf("No Flight Found......\n");
    }
    fclose(infile);
    if(flag==true){
        printf("###########################\n");
        printf("Select From the Menu :\n");
        printf("1).Request For Reservation\n2).Exit\n");
        scanf("%d",&tmp);
        if(tmp==1){
            printf("Enter the flight Number : ");
            char flightNo[100];
            scanf("%s",flightNo);
            strcpy(Query.flightNo,flightNo);
            Query.userData=user.userData;
            reservation(Query);
        }
    }

}
//ticket cancellation
bool ticketCancel(loginCred data){
    printf("###########################\nTicket Cancellation\n");
    printf("Enter the details for ticket cancellation : \n1).FLight Number : ");
    FILE *outfile;
    outfile=fopen("cancelList.txt","w");
    cancel Cancel;
    char tmp[10];
    scanf("%s",Cancel.flightNo);
    printf("2).Enter Date : \n date(dd) : ");
    scanf("%d",&Cancel.date.dd);
    printf(" month(MM) : ");
    scanf("%d",&Cancel.date.mm);
    printf(" year(yyyy) : ");
    scanf("%d",&Cancel.date.yyyy);
    printf("Confimr Cancellation (yes/no) :");
    scanf("%s",tmp);
    if(strcmp(tmp,"yes")==0){
        fwrite(&Cancel,sizeof(cancel),1,outfile);
        printf("Cancelling the ticket......\n");
    }
    fclose(outfile);
}
//ticket status and cancelltaion
void ticketStatus(loginCred data){
    int tmp,tmp2;
    reserve ticket,latest;
    bool flag=false,flag2=false;
    printf("########################### \nPassenger Ticket Status and Cancellation\n");
    FILE *infile,*infile2;
    infile=fopen("success.txt","r");
    infile2=fopen("reserveRequest1.txt","r");
    printf("1).Display the confirmation of the latest reservation\n2).Ticket Cancellation\n3).Booked Ticket History\n4).Exit\n");
    scanf("%d",&tmp);

    if(tmp==1||tmp==2){
        while(fread (&ticket, sizeof(reserve), 1, infile2)){
        //printf("id : %s ,",ticket.userId);        //debugging
            if(strcmp(ticket.userId,data.id)==0){
                latest=ticket;
                flag2=true;
            }
        }
        if(flag2==true&&tmp==1){
            while(fread (&ticket, sizeof(reserve), 1, infile)){
                    //printf("id : %s ,",ticket.userId);        //debugging
                    if(strcmp(ticket.userId,data.id)==0){
                        latest=ticket;
                        flag=true;
                    }
            }
            printf("###########################\nConfirmation Status.....\n");
            if(!flag){
                printf("The ticket is not yet confirmed by admin..... \n");
            }
            else{

                printf("The ticket is Confirmed...\n1).Print ticket\n2).Exit\n");
                scanf("%d",&tmp);
                if(tmp==1){
                    char uid[100]="";
                    strcat(uid,latest.userId);
                    strcat(uid,latest.flightNo);
                    strcat(uid,latest.source);
                    printf("\tTicket Id : %s\tPass. name : %s %s\n\tFlight No. : %s\tSource : %s\tDest. : %s\n"
                        ,uid,latest.passfname,latest.passlname,latest.flightNo,latest.source,latest.dest);
                }
            }
        }
        else{
            if(flag2==true&&tmp==2){
                ticketCancel(data);
            }
            else
                printf("No Reservation made yet....\n");
        }
    }
    else{
        if(tmp==3){
            while(fread (&ticket, sizeof(reserve), 1, infile2)){
                        //printf("id : %s ,",ticket.userId);        //debugging
                        if(strcmp(ticket.userId,data.id)==0){
                            latest=ticket;
                            flag2=true;
                        }
            }
            if(flag2==true){

                    while(fread (&ticket, sizeof(reserve), 1, infile)){
                        //printf("id : %s ,",ticket.userId);        //debugging
                        if(strcmp(ticket.userId,data.id)==0){
                            printf("\tPass. name : %s %s Date: %d:%d:%d\n\tFlight No. : %s\tSource : %s\tDest. : %s\n"
                        ,ticket.passfname,ticket.passlname,ticket.date.dd,ticket.date.mm,ticket.date.yyyy,ticket.flightNo,ticket.source,ticket.dest);
                        }
                    }
            }
            else{
                printf("No ticket booked yet...\n");
            }
        }
    }
    fclose(infile);
    fclose(infile2);
}
//editing the user data
void updateUserFile(loginCred data){
    userInfo old,new;
    FILE *outfile;
    bool flag=true;;
    char tmp[10],pass[100]="0",pass2[100]="43";
    outfile=fopen("userData3.txt","a");
    credData user=verifyCredUser(data);
    old=user.userData;//old user data
    printf("###########################\nUpdate User Data :\n");
    printf("UserID : %s\n",old.userId);
    strcpy(new.userId,old.userId);
    strcpy(new.fname,old.fname);
    strcpy(new.lname,old.fname);
    new.passportno=old.passportno;
    printf("1).If you want to edit phone number (yes/no) : ");
    scanf("%s",tmp);
    if(strcmp(tmp,"yes")==0){
        printf("Enter the new Number :");
        scanf("%lld",&new.phone);
    }
    else{
        new.phone=old.phone;
    }
    printf("2).If you want to edit email (yes/no) : ");
    scanf("%s",&tmp);
    if(strcmp(tmp,"yes")==0){
        printf("Enter the new email :");
        scanf("%s",new.email);
    }
    else{
        strcpy(new.email,old.email);
    }
    printf("3).If you want to change the password (yes/no) : ");
    scanf("%s",&tmp);
    if(strcmp(tmp,"yes")==0){
        while(strcmp(pass,pass2)!=0){
            if(flag==false){
                printf("Error.. the passwords do not match... \n");
            }
            printf("Enter the new password :");
            scanf("%s",pass);
            printf("Reenter the password : ");
            scanf("%s",pass2);
            if(strcmp(pass,pass2)!=0){
                flag=false;

            }
        }
        strcpy(new.password,pass);

    }
    else{
        strcpy(new.password,old.password);
    }
    printf("Do you want to confrm to update the information ? (yes/no) : ");
    scanf("%s",tmp);
    if(strcmp(tmp,"yes")==0){
        printf("Updating Information.....\n");
        fwrite(&new,sizeof(userInfo),1,outfile);
    }
    else{
        printf("Cancelling update of information....\n");
    }
    fclose(outfile);

}

//user SignIn
bool signInUser(){
    loginCred data;
    int tmp,tmp2;
    credData verify;
    printf("########################### \nUser Sign In\n");
    printf("\nEnter the id for Sign in : ");
    scanf("%s",data.id);
    printf("Enter the password for Sign in : ");
    scanf("%s",data.password);
    verify=verifyCredUser(data);//verifying the credentials
    if(verify.password==false){
        printf("###########################\n");
        printf("\nIncorrect id / password entered\n");
    }
    else{
        printf("###########################\n");
        printf("\nLogin Credentials correct , succesful Passenger Login\n");
        while(1){
            printf("###########################\n");
            printf("Select From the menu:\n1).Request to view and book the available flights as per requirement\n2).Ticket Status,History And Cancellation \n3).Edit Profile\n4).Exit\n");
            scanf("%d",&tmp);
            if(tmp==1){
                printf("###########################\n");
                printf("Enter the following details to view flight : \n");
                viewFlight(data);
            }
            else{
                if(tmp==2){
                    //printf("###########################\n");
                    //printf("The ticket status\n");
                    ticketStatus(data);
                }
                else{
                     if(tmp==3)
                        updateUserFile(data);
                     else{
                        if(tmp==4&&false){
                            ticketCancel(data);
                        }
                        else
                            break;
                     }
                }
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
    outfile=fopen("userData3.txt","a");
    if(outfile==NULL){
        outfile=fopen("userData3.txt","w");
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
    /*infile = fopen ("userData3.txt","r");
    if(infile==NULL){
        printf("no infile present\n");
    }                                                                       // debuugging code
    while (fread (&data, sizeof(userInfo), 1, infile))
      printf ("Name = %s   id = %s   email = %s  pass=%s\n",
              data.fname, data.userId,data.email,data.password);
    fclose(infile);*/
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
