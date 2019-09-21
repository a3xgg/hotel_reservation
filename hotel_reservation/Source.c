/*
PROGRAMMED BY: ANDERSON FEBRIAN TP053792
FOR: ICP ASSIGNMENT
PROJECT TITLE: HOTEL RESERVATION SYSTEM
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100

//global variables
FILE* fp, * fp1, *fp2;
int option;
int i;
int* ptr;
int nday, nmonth, nyear; //USED IN FUNCTION CID(); COD();
char id[10];
//structures
struct moderator
{
	char username[10];
	char password[25];
	char nameof_employee[25];
};
//struct for guest
struct guest
{
	int num;
	char id[10];
	char fname[25];
	char lname[25];
	int contact_number;
	int guests;
	struct check_in
	{
		int day;
		int month;
		int year;
	}check_in_date;
	struct check_out
	{
		int day;
		int month;
		int year;
	}check_out_date;
	char rtype[15];
	int room_number;
}customer;
//struct for room
struct room
{
	char room_type[15];
	char room_capacity[10];
	int room_available;
	int price;
}info;

//SHOWS THE START MENU WHEN PROGRAM STARTS
int start_menu(void)
{
	do
	{
		printf("Welcome to the Hotel booking system\n");
		printf("Login to get started\n\n");
		printf("1. Admin login\n");
		printf("2. Customer login\n\n");
		printf("0. Exit\n");
		printf("Menu: ");
		scanf("%d", &option); //gets user input
		switch (option)
		{
		case 1: //if option is 1 then it will clear the screen and call the login function
			system("cls");
			login();
			break;
		case 2: //if option is 2 then it will clear the screen and call the login function
			system("cls");
			login();
			break;
		case 0:
			exit(1);
			break;
		default: //if user enters a wrong option then it will print invalid and clears the screen, then returns the user back to start menu
			printf("Enter a valid option\n");
			getch();
			system("cls");
			start_menu();
			break;
		}
	} while (option != 0);
}
//FUNCTION TO LOGIN
int login(void)
{
	int compare_username; //variable to be used in strcmp() to compare username
	int compare_password; //variable to be used in strcmp() to compare password
	ptr = &option;
	if (*ptr == 1)
	{
		struct moderator store_admin_info[MAX];//specify struct array to store data that was stored in file.
		struct moderator adminu; //defining a struct variable to be used for user input
		login:
		fp = fopen("users.txt", "r");
		if (fp == NULL)
		{
			printf("users.txt failed to open\n");
			printf("make sure the file exist..\n");
			printf("Press ENTER to return.");
			getch();
			system("cls");
			start_menu();
		}


		while (fread(&store_admin_info[i], sizeof(struct moderator), 1, fp)) //reads the file and stores the data into the moderator structure
		{
			i++;
		}
		
		printf("Enter login credentials\n");
		printf("Username: ");
		scanf("%s", adminu.username);
		printf("Password: ");
		scanf("%s", adminu.password);

		/*use to loop through the stored information in the array and passes the information to compare with user input*/
		for (i = 0; i < MAX; i++)
		{
			compare_username = strcmp(adminu.username, store_admin_info[i].username); //compares user input with the data stored in the array
			compare_password = strcmp(adminu.password, store_admin_info[i].password); //compares user input with the data stored in the array
			if (compare_username == 0 && compare_password == 0) //strcmp() returns 0 if string is equal
			{
				printf("Login Success. Redirecting..."); //if user input and information stored in array is equal then it will redirect when the user press enter
				getch();
				fclose(fp);
				system("cls"); // clears the screen
				menu(); //redirects to the admin menu
				break;
			}
		}
		printf("Username or Password Incorrect.");
		getch();
		system("cls");
		goto login;
		fclose(fp);
	}
	else
	{
		if (*ptr == 2)
		{
			
			struct guest store_customer[MAX];
			
			fp = fopen("customer.txt", "r+");
			if (fp == NULL)
			{
				printf("customer.txt failed to open");
				printf("\nmake sure the file exist..\n");
				printf("Press ENTER to return.");
				getch();
				system("cls");
				start_menu();
			}
			while (fread(&store_customer[i], sizeof(store_customer), 1, fp))
			{
				i++;
			}
			loginuser:
			printf("Enter your customer ID: ");
			scanf("%s", &id);
			for (i = 0; i < MAX; i++)
			{
				compare_username = strcmp(id, store_customer[i].id);
				if (compare_username == 0)
				{
					printf("Login Success!");
					getch();
					
					system("cls");
					menu();
					break;
				}
			}
			printf("Incorrect ID");
			getch();
			system("cls");
			goto loginuser;
			fclose(fp);
		}
	}
}
//FUNCTION  - REGISTER USER/ADMIN
int register_user(void)
{
	struct moderator adminu;
	struct moderator adminarray[MAX];
	char retypepass[25];
	int cmpuser;
	fp = fopen("users.txt", "a+");
	if (fp == NULL)
	{
		printf("users.txt file failed to open");
	}

	while (fread(&adminarray[i], sizeof(struct moderator), 1, fp))
	{
		i++;
	}
	
	printf("Register an account\n");
	printf("Enter name of employee: ");
	scanf("%s", adminu.nameof_employee);
	printf("Username: ");
	scanf("%s", adminu.username);
	//this loop is to make sure that there is no duplicate username in the file
	for (i = 0; i < MAX; i++)
	{
		cmpuser = strcmp(adminu.username, adminarray[i].username); //compares the input username and username in file
		if (cmpuser == 0) 
		{
			printf("Username has been taken\n");//if input username is equal to username in file then it will print username is taken
			getch();
			system("cls");
			continue;
		}
		else
		{
			break;
		}
	}
	printf("Password: ");
	scanf("%s", adminu.password);
	printf("Re-type password: ");
	scanf("%s", retypepass);
	int compare_password = strcmp(adminu.password, retypepass);
	while (compare_password != 0)
	{
		printf("Password does not match. Please try again.\n");
		printf("Username: %s\n", adminu.username);
		printf("Password: ");
		scanf("%s", adminu.password);
		printf("Re-type password: ");
		scanf("%s", retypepass);
		compare_password = strcmp(adminu.password, retypepass);
		system("cls");
	}
	fwrite(&adminu, sizeof(struct moderator), 1, fp);
	fclose(fp);
	printf("Account created successfully! \nPress ENTER to continue.");
	getch();
	system("cls");
	option = 1;
	menu();
}
//THIS FUNCTION CHECKS IF THE CHECK IN DATE IS VALID OR NOT
int check_cid(void)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	while (customer.check_in_date.day < tm.tm_mday || customer.check_in_date.day > 31 || customer.check_in_date.day < 0 || customer.check_in_date.month > 12 || customer.check_in_date.month < 0 || customer.check_in_date.month < (tm.tm_mon + 1) || customer.check_in_date.year < (tm.tm_year + 1900))
	{
		if (customer.check_in_date.day < tm.tm_mday && customer.check_in_date.month >(tm.tm_mon + 1))
		{
			if (customer.check_in_date.month > 12)
			{
				printf("Invalid date has been detected\n");
				printf("Check in date (dd-mm-yyyy): ");
				scanf("%d-%d-%d", &customer.check_in_date.day, &customer.check_in_date.month, &customer.check_in_date.year); // gets check in date
			}
			else
			{
				break;
			}
		}
		else
		{
			printf("Invalid date has been detected\n");
			printf("Check in date (dd-mm-yyyy): ");
			scanf("%d-%d-%d", &customer.check_in_date.day, &customer.check_in_date.month, &customer.check_in_date.year); // gets check in date
		}

	}
}
//THIS FUNCTION CHECKS WHETHER THE CHECK OUT DATE IS VALID OR NOT
int check_cod(void)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	while (customer.check_out_date.day < tm.tm_mday || customer.check_out_date.day > 31 || customer.check_out_date.day < 0 || customer.check_out_date.month > 12 || customer.check_out_date.month < 0 || customer.check_out_date.month < (tm.tm_mon + 1) || customer.check_out_date.year < (tm.tm_year + 1900))
	{
		if (customer.check_out_date.day < tm.tm_mday && customer.check_out_date.month >(tm.tm_mon + 1))
		{
			if (customer.check_out_date.month > 12)
			{
				printf("Invalid date has been detected\n");
				printf("Check in date (dd-mm-yyyy): ");
				scanf("%d-%d-%d", &customer.check_out_date.day, &customer.check_out_date.month, &customer.check_out_date.year); // gets check out date
			}
			else
			{
				break;
			}
		}
		else
		{
			printf("Invalid date has been detected\n");
			printf("Check in date (dd-mm-yyyy): ");
			scanf("%d-%d-%d", &customer.check_out_date.day, &customer.check_out_date.month, &customer.check_out_date.year); // gets check out date
		}
	}
}

//FUNCTION  - ROOM BOOKING
int room_booking(void)
{
	
	//to input customer room booking
	fp = fopen("customer.txt", "a+");
	if (fp == NULL)
	{
		printf("customer.txt failed to open");
	}
	int compare_roomtype;

	printf("Room Booking\n");
	printf("Enter customer #: ");// enter number for example guest #1
	scanf("%d", &customer.num);
	printf("Enter customer's ID: ");
	scanf("%s", &customer.id); //gets customer id input example: ID25462
	printf("Customer Full Name: ");
	scanf("%s %s", customer.fname, customer.lname); //gets customer full name in fname and lname example: Anderson Febrian
	printf("Customer contact number: ");
	scanf("%d", &customer.contact_number); //gets customer contact number example: +60241231241
	printf("Number of guest: ");
	scanf("%d", &customer.guests); //gets the number of guest staying example: 2
	printf("Enter room type: ");
	scanf("%s", customer.rtype); //gets the prefered room type example: single

	//opening room_details 

	fp1 = fopen("room_details.txt", "r");
	fp2 = fopen("temp_room.txt", "w");
	if (fp1 == NULL)
	{
		printf("room_details.txt failed to open");
	}
	while (fread(&info, sizeof(info), 1, fp1))
	{
	
		compare_roomtype = strcmp(customer.rtype, info.room_type);
		if (compare_roomtype != 0)
		{
			fwrite(&info, sizeof(info), 1, fp2);
		}
		else
		{
			if (compare_roomtype == 0)
			{

				if (info.room_available != 0)
				{
					printf("you have chosen %s ", customer.rtype);
					info.room_available = info.room_available - 1;
					

					printf("Room number: ");
					scanf("%d", &customer.room_number); //gets room number

					time_t t = time(NULL);
					struct tm tm = *localtime(&t);
					repeat:
					printf("Check in date (dd-mm-yyyy): ");
					scanf("%d-%d-%d", &customer.check_in_date.day, &customer.check_in_date.month, &customer.check_in_date.year); // gets check in date

					check_cid();
					
					printf("Check out date (dd-mm-yyyy): ");
					scanf("%d-%d-%d", &customer.check_out_date.day, &customer.check_out_date.month, &customer.check_out_date.year); //gets check out date 

					check_cod();

					if (customer.check_in_date.day > customer.check_out_date.day)
					{
						nday = customer.check_in_date.day - customer.check_out_date.day;
					}
					else
					{
						nday = customer.check_out_date.day - customer.check_in_date.day;
					}

					nmonth = customer.check_out_date.month - customer.check_in_date.month;
					nyear = customer.check_out_date.year - customer.check_in_date.year;
					if (nday < 0 || nmonth < 0 || nyear < 0)
					{
						printf("sorry booking will not go through as date entered is invalid.\nPlease try again\n");
						goto repeat;
					}
					fwrite(&info, sizeof(info), 1, fp2);
				}

				else
				{
					printf("Room has been fully booked.. Redirecting to Availability..\n");
					printf("Press ENTER to continue..");
					getch();
					system("cls");
					check_availability_info();
					break;
				}
			}
		}
	}
	fclose(fp1);
	fclose(fp2);

	fp1 = fopen("room_details.txt", "w");
	fp2 = fopen("temp_room.txt", "r");
	while (fread(&info, sizeof(info), 1, fp2))
	{
		fwrite(&info, sizeof(info), 1, fp1);
	}
	fclose(fp1);
	fclose(fp2);

	fwrite(&customer, sizeof(customer), 1, fp); //writes the structure into the file called customer.txt
	if (fwrite != 0)
	{
		printf("\nRoom booked succesfully for %s %s for %dday %dmonth %dyear\n", customer.fname, customer.lname, nday, nmonth, nyear);
	}
	fclose(fp);
	printf("Press ENTER to return to menu...\n");
	getch();
	system("cls");
	option = 1;
	menu();
}
//PRINTS CURRENT BOOKING THAT CAN BE VIEWED BY THE CUSTOMER
int view_current_booking(void)
{
	int cmpid; //use for comparing customer id
	printf("Your current booking:\n\n");
	printf("Customer ID\tCustomer Name\tRoom Type\tRoom Number\tCheck in Date\tCheck out Date\n\n");
	fp = fopen("customer.txt", "r");
	fp1 = fopen("temp_cust_view.txt", "w+");
	if (fp1 == NULL)
	{
		printf("customer.txt file failed to open");
		start_menu();
	}
	while (fread(&customer, sizeof(customer), 1, fp))
	{
		cmpid = strcmp(id, customer.id);
		if (cmpid != 0)
		{
			fwrite(&customer, sizeof(customer), 1, fp1);
		}
		else
		{
			printf("%s\t%s %s\t%s\t%d\t%d-%d-%d\t%d-%d-%d\n\n",customer.id,customer.fname,customer.lname,customer.rtype,customer.room_number,customer.check_in_date.day,customer.check_in_date.month,customer.check_in_date.year,customer.check_out_date.day,customer.check_out_date.month,customer.check_out_date.year);
		}
	}
	fclose(fp);
	fclose(fp1);
	printf("\nPress ENTER to return.");
	getch();
	system("cls");
	option = 2;
	menu();
}

int cancel_booking(void)
{
	int nums, custnum;

	fp = fopen("customer.txt", "r");
	printf("#\tCust_ID\t\tCust_Name\t\tCust_Contact\tNumber_of_Guests\tCheck_in_Date\tCheck_out_Date\tRoom_Type\tRoom_Number\n");
	printf("-\t-------\t\t---------\t\t------------\t----------------\t-------------\t--------------\t---------\t-----------\n");
	while (fread(&customer, sizeof(customer), 1, fp))
	{
		printf("%d %s\t%s %s\t%d\t\t%d\t\t%d-%d-%d\t%d-%d-%d\t%s %d\n", customer.num, customer.id, customer.fname, customer.lname, customer.contact_number, customer.guests, customer.check_in_date.day,customer.check_in_date.month,customer.check_in_date.year, customer.check_out_date.day,customer.check_out_date.month,customer.check_out_date.year, customer.rtype, customer.room_number);
	}
	fclose(fp);

	fp = fopen("customer.txt", "r");
	fp1 = fopen("temp_cust.txt", "w"); //temp file to store cust info which will be written back into the original file

	if (fp == NULL)
	{
		printf("customer.txt failed to open\n");
		printf("returning to menu...\n");
		printf("Press ENTER to continue.");
		getch();
		system("cls");
		option = 1;
		menu();
	}
	printf("\nEnter a number to Cancel booking: ");
	scanf("%d", &nums);

	while (fread(&customer, sizeof(customer), 1, fp))
	{
		custnum = customer.num;
		if (custnum != nums)
		{
			fwrite(&customer, sizeof(customer), 1, fp1);
		}
	}
	fclose(fp);
	fclose(fp1);

	fp = fopen("customer.txt", "w");
	fp1 = fopen("temp_cust.txt", "r");

	while (fread(&customer, sizeof(customer), 1, fp1))
	{
		fwrite(&customer, sizeof(customer), 1, fp);
	}

	fclose(fp);
	fclose(fp1);
	printf("\nBooking has been cancelled...\n");
	printf("All information regarding this user has been deleted..\n");
	printf("Redirecting to Availability menu.\nMake sure to edit the number of available rooms!\n\n");
	printf("Press ENTER to continue.");
	getch();
	system("cls");
	check_availability_info();
}
//FUNCTION - MODIFY BOOKING
modify_booking()
{
	int nums,custnum;

	fp = fopen("customer.txt", "r");
	printf("# Cust_ID\tCust_Name\tCust_Contact\tNumber_of_Guests\tCheck_in_Date\tCheck_out_Date\tRoom_Type\tRoom_Number\n");
	printf("# -------\t---------\t------------\t----------------\t-------------\t--------------\t---------\t-----------\n");
	while (fread(&customer, sizeof(customer), 1, fp))
	{
		printf("%d %s\t%s %s\t\t%d\t\t%d\t\t%d-%d-%d\t%d-%d-%d\t%s\t%d\n", customer.num, customer.id, customer.fname, customer.lname, customer.contact_number, customer.guests, customer.check_in_date.day, customer.check_in_date.month, customer.check_in_date.year, customer.check_out_date.day, customer.check_out_date.month, customer.check_out_date.year, customer.rtype, customer.room_number);
	}
	fclose(fp);

	fp = fopen("customer.txt", "r");
	fp1 = fopen("temp_cust.txt", "w"); //temp file to store cust info which will be written back into the original file

	if (fp == NULL)
	{
		printf("customer.txt failed to open");
	}
	printf("\nEnter a number to modify: ");
	scanf("%d", &nums);
	
	while (fread(&customer, sizeof(customer), 1, fp))
	{
		custnum = customer.num;
		
		if (custnum != nums)
		{
			fwrite(&customer, sizeof(customer), 1, fp1);
		}
		else
		{
			printf("\nWhat do you want to edit from %s\n" ,customer.id);
			printf("1. Number of Guest\n2. Room Type and Room Number\n3. Room Number\n4. Check in Date and Check out Date\n5. Cust #\n0. Cancel\n");
			scanf("%d", &option);
			switch (option)
			{
			case 1:
				printf("Enter new number of guest: ");
				scanf("%d", &customer.guests);
				break;
			case 2:
				printf("Enter new Room Type: ");
				scanf("%s", customer.rtype);
				printf("Enter new Room Number: ");
				scanf("%d", &customer.room_number);
				break;
			case 3:
				printf("Enter new Room Number: ");
				scanf("%d", &customer.room_number);
				break;
			case 4:
				repeat:
				printf("Enter new Check in Date (dd-mm-yyyy): ");
				scanf("%d-%d-%d", &customer.check_in_date.day,&customer.check_in_date.month,&customer.check_in_date.year);
				check_cid();
				printf("Enter new Check out Date (dd-mm-yyyy): ");
				scanf("%d-%d-%d", &customer.check_out_date.day,&customer.check_out_date.month,&customer.check_out_date.year);
				check_cod();
				if (customer.check_in_date.day > customer.check_out_date.day)
				{
					nday = customer.check_in_date.day - customer.check_out_date.day;
				}
				else
				{
					nday = customer.check_out_date.day - customer.check_out_date.day;
				}

				nmonth = customer.check_out_date.month - customer.check_in_date.month;
				nyear = customer.check_out_date.year - customer.check_in_date.year;
				if (nday < 0 || nmonth < 0 || nyear < 0)
				{
					printf("sorry booking will not go through as date entered is invalid.\nPlease try again\n");
					goto repeat;
				}
				break;
			case 5:
				printf("Enter new #: ");
				scanf("%d", &customer.num);
				break;
			case 0:
				option = 1;
				system("cls");
				menu();
				break;
			default:
				printf("Enter a valid option\n");
				break;
			}
			fwrite(&customer, sizeof(customer), 1, fp1);
		}
	}

	fclose(fp);
	fclose(fp1);

	fp = fopen("customer.txt", "w");
	fp1 = fopen("temp_cust.txt", "r");

	while (fread(&customer, sizeof(customer), 1, fp1))
	{
		fwrite(&customer, sizeof(customer), 1, fp);
	}

	fclose(fp);
	fclose(fp1);

	printf("Successfully updated..\nReturning to menu\n");
	getch();
	system("cls");
	option = 1;
	menu();
}

//FUNCTION - INSERT ROOM DETAILS
insert_room_details()
{
	fp = fopen("room_details.txt", "a+");
	if (fp == NULL)
	{
		printf("room_details.txt failed to open");
	}
	printf("Insert Room Details\n");
	printf("Room type: ");
	scanf("%s", info.room_type);
	printf("Room capacity: ");
	scanf("%s", &info.room_capacity);
	printf("Available Rooms: ");
	scanf("%d", &info.room_available);
	printf("Room Price: ");
	scanf("%d", &info.price);
	fwrite(&info, sizeof(info), 1, fp);
	fclose(fp);
}
//FUNCTION - UPDATE ROOM DETAILS
update_room_details()
{
	char rtype[15];

	printf("Which room type detail do you want to edit: ");
	scanf("%s", rtype);

	fp = fopen("room_details.txt", "r");
	fp1 = fopen("temp_room.txt", "w");

	while (fread(&info, sizeof(info), 1, fp))
	{
		int rmcmp;

		rmcmp = strcmp(rtype, info.room_type);

		if (rmcmp != 0)
		{
			fwrite(&info, sizeof(info), 1, fp1);
		}
		else
		{
			printf("What do you want to edit from %s\n", rtype);
			printf("1. Room Type\n2. Room Capacity\n3. Available Rooms\n4. Price\n5. All\n\n0. Exit\n");
			scanf("%d", &option);
			switch (option)
			{
			case 1:
				printf("Enter new Room Type: ");
				scanf("%s", info.room_type);
				break;
			case 2:
				printf("Enter new Room Capacity: ");
				scanf("%s", info.room_capacity);
				break;
			case 3:
				printf("Enter Available rooms: ");
				scanf("%d", &info.room_available);
				break;
			case 4:
				printf("Enter new room price: ");
				scanf("%d", &info.price);
				break;
			case 5:
				printf("Enter new Room Type: ");
				scanf("%s", info.room_type);
				printf("Enter new Room Capacity: ");
				scanf("%s", info.room_capacity);
				printf("Enter Available rooms: ");
				scanf("%d", &info.room_available);
				printf("Enter new room price: ");
				scanf("%d", &info.price);
				break;
			case 0:
				printf("Press ENTER to return.");
				getch();
				system("cls");
				check_availability_info();
			break;
			default:
				printf("\nenter a valid menu");
				break;
			}
			fwrite(&info, sizeof(info), 1, fp1);
		}
	}

	fclose(fp);
	fclose(fp1);

	fp = fopen("room_details.txt", "w");
	fp1 = fopen("temp_room.txt", "r");
	while (fread(&info, sizeof(info), 1, fp1))
	{
		fwrite(&info, sizeof(info), 1, fp);
	}
	fclose(fp);
	fclose(fp1);
	
	printf("Details has been updated.\n");
	printf("Press ENTER to return.\n");
	getch();
	system("cls");
	check_availability_info();
}

//FUNCTION TO CHECK ROOM AVAILABILITY AND INFO
check_availability_info()
{
	int num = 1;
	fp = fopen("room_details.txt", "r+");
	if (fp == NULL)
	{
		printf("room_details.txt file failed to open");
	}


	printf("Room Availability and Info\n\n");
	printf("Room Type\tRoom Capacity\tAvailable Rooms\tPrice (MYR)\n");
	printf("---------\t--------------\t--------------\t-----------\n");
	//PRINTS OUT ALL THE ROOM INFORMATION
	while (fread(&info, sizeof(info), 1, fp))
	{
		printf("%d. %s    \t       %s     \t       %d     \t     %d    \n", num, info.room_type, info.room_capacity, info.room_available, info.price);
		num++;
	}
	printf("\nDo you wish to view a room?\n\n");
	printf("1. Yes\n2. No\n\n0. Edit\n");
	printf("Menu: ");
	scanf("%d", &option); //GETS THE USER CHOICE
	switch (option)
	{
	case 1: 
		printf("Which room do you want to view?");
		room_info(); //PRINTS OUT ROOM INFO CHOICES
		getch(); 
		system("cls");
		check_availability_info(); //RETURNS BACK TO CHECK_AVAILABILITY_INFO
		break;
	case 2:
		printf("\nReturning to main menu...");
		printf("\nPress ENTER to continue.");
		getch();
		system("cls");
		option = 1;
		menu();
		break;
	case 0:
		update_room_details();
		break;
	default:
		printf("enter a valid option...");
		getch();
		system("cls");
		check_availability_info();
		break;
	}
	fclose(fp);
}
//check room for user
int check_room(void)
{
	int num = 1;
	fp = fopen("room_details.txt", "r+");
	if (fp == NULL)
	{
		printf("room_details.txt file failed to open");
	}


	printf("Room Availability and Info\n\n");
	printf("Room Type\tAvailable Rooms\tPrice (MYR)\n");
	printf("---------\t--------------\t------------\n");
	//PRINTS OUT ALL THE ROOM INFORMATION
	while (fread(&info, sizeof(info), 1, fp))
	{
		printf("%d. %s    \t        %d\t%d    \n", num, info.room_type, info.room_available, info.price);
		num++;
	}
	printf("\nDo you wish to view a room?\n");
	printf("1. Yes\n2. No\n");
	printf("Menu: ");
	scanf("%d", &option); //GETS THE USER CHOICE
	switch (option)
	{
	case 1:
		printf("Which room do you want to view?");
		room_info(); //PRINTS OUT ROOM INFO CHOICES
		getch();
		system("cls");
		check_room();
		break;
	case 2:
		printf("\nReturning to main menu...\n");
		printf("Press ENTER to continue.");
		getch();
		system("cls");
		option = 2;
		menu();
		break;
	default:
		printf("enter a valid option...");
		getch();
		system("cls");
		check_room();
		break;
	}
}
//FUNCTION TO BE USED IN check_availability_info
int room_info(void)
{
	scanf("%d", &option);
	if (option == 1)
	{
		system("cls");
		printf("Room Info: Single\n\n");
		printf("Room Details\n");
		printf("Max occupant: 1 person\n");
		printf("Facilities:\n");
		printf("- 1 Single Bed\n");
		common_facilities();
		printf("\nPress Enter to continue");
	}
	else
	{
		if (option == 2)
		{
			system("cls");
			printf("Room Info: Double\n\n");
			printf("Room Details\n");
			printf("Max occupant: 2 - 3 people\n");
			printf("Facilities:\n");
			printf("- 2 Single Bed OR 1 Queen bed\n");
			common_facilities();
			printf("\nPress Enter to continue");
		}
		else
		{
			if (option == 3)
			{
				system("cls");
				printf("Room Info: Triple\n\n");
				printf("Room Details\n");
				printf("Max occupant: 2 people\n");
				printf("Facilities:\n");
				printf("- 3 Single Bed OR 1 Queen bed and 1 Single bed OR 1 King bed\n");
				common_facilities();
				printf("\nPress Enter to continue");
			}
		}
	}
}

//FUNCTION TO PRINT OUT COMMON FACILITIES - TO BE USED IN room_info
int common_facilities(void)
{
	printf("- 30\" TV\n");
	printf("- Free WiFi\n");
	printf("- Aircondition\n");
	printf("- Telephone\n");
	printf("- Desk and Chair\n");
	printf("- Coffee and tea facilities\n");
	printf("- Water heater\n");
	printf("- Safe box\n");
	printf("- Hair Dryer\n");
	printf("- Bathtub or Shower\n");
	printf("- Wardrobe\n");
}

//FUNCTION AFTER LOGIN SUCCESFUL
int menu(void)
{
	switch(option) //checks the option
	{
	case 1: //if 1 it will print the admin interface
		
		printf("Welcome to the admin interface\n\n");

		printf("1. Register user\n");
		printf("2. Room Booking\n");
		printf("3. Cancel Booking\n");
		printf("4. Check availability/View Room info\n");
		printf("5. Modify Booking\n");
		printf("6. Insert Room Details\n\n");

		printf("0. Logout\n");
		printf("Menu: ");
		scanf("%d", &option);
		switch (option) //gets option
		{
		case 1: //if 1 goes to register user
			system("cls");
			option = 0;
			register_user();
			break;
		case 2: //if 2 goes to room booking
			system("cls");
			room_booking();
			break;
		case 3: //if 3 goes to cancel booking
			cancel_booking();
			break;
		case 4: //if 4 goes to check availability
			system("cls");
			check_availability_info();
			break;
		case 5: //if 5 goes to modify booking
			system("cls");
			modify_booking();
			break;
		case 6:
			system("cls");
			insert_room_details();
			option = 1;
			menu();
			break;
		case 0:
			system("cls");
			start_menu();
			break;
		default:
			printf("enter a valid menu");
			getch();
			system("cls");
			menu();
			break;
		}
		break;
	case 2: //if option is 2 it will go to the customer interface
		printf("Welcome to the Customer interface\n");
		printf("1. View existing booking\n");
		printf("2. Check availability/Room info\n");
		printf("0. Logout\n");
		printf("Menu: ");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			system("cls");
			view_current_booking();
		case 2:
			system("cls");
			check_room();
			getch();
			break;
		case 0:
			system("cls");
			start_menu();
			break;
		default:
			printf("enter a valid menu");
			getch();
			system("cls");
			option = 2;
			menu();
			break;
		}
		break;
	}
}

//MAIN FUNCTION WHERE EVERYTHING BEGINS
int main(void)
{
	start_menu();
}
