#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
  	char username[20];
	char password[20];
	
	int status;
	struct node *next;
}node;

node *head = NULL;
node *current = NULL;

void insert(char username[20], char password[20], int status){
	node *temp;
	temp=(node *)malloc(sizeof(node));
	strcpy(temp->username, username);
	strcpy(temp->password, password);
	temp->status = status;
	temp->next = head;
	head = temp;
}

node *find(char name[20]){

   
   node *current = head;

  
   if(head == NULL)
	{
      return NULL;
    }

   while(strcmp(current->username, name) != 0){
      if(current->next == NULL){
         return NULL;
      }else {
         current = current->next;
      }
   }      
   return current;
}
void update_passwd (char a[],char b[],char c[]){

    int pos = 0;
   
   if(head==NULL) {
      printf("Error!");
      return;
   } 

   current = head;
   while(current->next!=NULL) {
      if(strcmp(current->username,a)==0) {
        strcpy(current->password,c);
        printf("password changed!\n");
         return;
      }
      current = current->next;
      pos++;
   }
   printf(" khong ton tai trong list\n");
	
	
}

void update_data(char b[]) {
   int pos = 0;
   
   
   if(head==NULL) {
      printf("Danh sach lien ket chua duoc khoi tao");
      return;
   } 

   current = head;
   while(current->next!=NULL) {
      if(strcmp(current->username,b)==0) {
         current->status = 1;
         printf("\nTim thay  tai vi tri %d\n", pos);
         writeFile();
         return;
      }
      current = current->next;
      pos++;
   }
   printf("%d khong ton tai trong list\n");
}


void printAll()
{
    node *temp;
    temp = head;
    while(temp)
    {
    	printf("%20s %20s %d",temp->username, temp->password, temp->status);
        printf("\n");
        temp=temp->next;
    }
    printf("\n");
}

void openFile(){
	node *acc;
	char *username;
	char *password;
	int status;
	char c;
	int u = 0, p = 0, blank = 0;
	username = (char *)malloc(20);
	password = (char *)malloc(20);
    FILE *fptr;
	if((fptr=fopen("account.txt","r+"))==NULL){
		printf("Khong tim thay %s\n","account.txt");
		return;
	}
	while(1){
		fscanf(fptr,"%s",username);
		fscanf(fptr,"%s",password);
		fscanf(fptr,"%d",&status);
		if(feof(fptr)) break;
		insert(username, password, status);
	}
	free(username); free(password);
	fclose(fptr);
}

void writeFile(){
	FILE *fptr;
	node *temp;
    temp = head;
    fptr=fopen("account.txt","w+");
    while(temp){
    	fprintf(fptr, "%s %s %d", temp->username, temp->password, temp->status);
    	fprintf(fptr, "\n");
    	temp=temp->next;
    }
    fclose(fptr);
}

void registerAccount(){
	char username[20];
	char password[20];
	//__fpurge(stdin);
	printf("---------Register\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	printf("Password: "); scanf("%s", password);
	printf("\n");
	if(find(username) != NULL){
	printf("Account already exists!");	
	} 
	else{
		insert(username, password, 2);
		printf("successfull registration!\n");
		writeFile();
		printAll();
	}
	printf("\n");
}

void activeAccount(){
	int count_code =0;
	char username[20];
	char password[20];
	char code[20] ;
	char i[] = "20184030";
	printf("---------Active\n");
	/*printf("Username: "); scanf("%s", username);
	printf("\n");
	printf("Password: "); scanf("%s", password);//gets(password); __fpurge(stdin);
	printf("\n");
	printf("Code: "); scanf("%s", code);
	printf("\n");
	if((find(username) != NULL) && strcmp(code,i)==0){
		update_data(username);
		writeFile();
		printf("account has been active ");
	}
	else if ((find(username) != NULL) && strcmp(code,i) !=0){
		printf("wrong code");
		
	}
	else{
		printf("account is not actived");
	}
	printf("\n");
	
}*/
    int code_count =0;
printf("Username: "); scanf("%s", username);
	printf("\n");
printf("Password: "); scanf("%s", password);
	printf("\n");
	node *acc = find(username);
	if(acc != NULL){
		
	    do{
		printf("Code: "); scanf("%s", code);
		printf("\n");
		if((strcmp(acc->password,password) == 0) && strcmp(code,i) == 0){
		
                        update_data(username);
		        writeFile();
		        printf("account has been active \n");
		        return acc;
}
		else {
			printf("Wrong code,account is not actived\n");
			code_count++;
			
			}
		}while(code_count < 4);
		if(code_count == 4) {
			printf("The account has been locked\n");
			acc->status = 0;
			writeFile();
			return NULL;
		}
	}
	else{
		printf("Account does not exist\n");
		return NULL; 
	} 
}
node *signin(){
	char username[20];
	char password[20];
	int login_count = 0;
	printf("---------Sign In\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	node *acc = find(username);
	if(acc != NULL){
		if(acc->status == 0){
			printf("Account has been blocked!\n");
			return NULL;
		}
		do{
		printf("Password: "); scanf("%s", password);
		printf("\n");
		if(strcmp(acc->password,password) == 0){
			printf("Success\n");
			return acc; 
			}
		else {
			printf("Wrong Password\n");
			login_count++;
			
			}
		}while(login_count < 3);
		if(login_count == 3) {
			printf("The account has been locked\n");
			acc->status = 0;
			writeFile();
			return NULL;
		}
	}
	else{
		printf("Account does not exist\n");
		return NULL; 
	} 
}

void search(){
	char username[20];
	printf("---------Search\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	node *acc = find(username);
	if(acc != NULL){
		printf("Username: %20s Status: %d\n", acc->username, acc->status);
	}
	else printf("Account does not exist\n");
}

node *signout(){
	char username[20];
	printf("---------Sign Out\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	node *acc = find(username);
	if(acc == NULL){
		printf("Account does not exist\n");
		return NULL;
	}
	else return acc;
}

int choice(){
	int c = 0;
	printf("USER MANAGEMENT PROGRAM\n");
	printf("-----------------------------------\n");
	printf("1. Register\n");
	printf("2. ActiveAccount\n");
	printf("3. Sign in\n");
	printf("4. Search\n");
	printf("5. Change Password\n");
	printf("6. Sign out\n");
	printf("Your choice (1-6, other to quit):\n"); scanf("%d", &c);
	return c;	
}

int main()
{
	openFile();
	printAll();
    char a[20];
    char b[20];
    char c[20];
	int ch;
	
	node *login_acc = NULL;
	node *signout_acc = NULL;
	do{
		ch = choice();
		
		switch(ch){
		case 1: registerAccount(); break;
		case 2 : activeAccount(); printAll();
			
			break;
		case 3: login_acc = signin(); break;
		case 4: {
			if(login_acc != NULL) {
				//printf("%s\n", login_acc->username);
				search();
			}
			else printf("Sign in first!\n");
		} break;
		case 5 : 
		if(login_acc == NULL) printf("Sign in first!\n"); 
		else{
		
	    
	    printf("---------Changepasswd\n");
	    printf("Username: "); scanf("%s", a);
	    printf("\n");
	    printf("Password: "); scanf("%s", b);
	    printf("\n");
	    
	    printf("New Password: "); scanf("%s", c); 
	    node *acc = find(a);
		//update_passwd (a,b,c);
		if(strcmp(acc->password,b) == 0){
		update_passwd(a,b,c);
		writeFile();
        
				
	} 
	else{
		printf("Current password is incorrec!");
	        printf("\n");
                }
		printAll();} break;
		case 6: {
			if(login_acc == NULL) printf("Sign in first!\n"); 
			else{
				signout_acc = signout();
				if(signout_acc)
				if(strcmp(signout_acc->username,login_acc->username) == 0){
					printf("Gudbike Hust\n");
					login_acc = NULL;
				}
				else printf("Wrong Username!\n");
			}			
		} break;
		
		
	}
	}
	while(ch > 0 && ch < 7);
	

	return 0;
}
