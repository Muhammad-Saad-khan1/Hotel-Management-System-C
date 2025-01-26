#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Guest_Information();
void Edit_Guest_Details();
void Delete_Guest_Detail();
void Book_Room();
void Update_Room();
void Cancel_Booking();
void Generate_Bill();
void Services();
void Save_Data();
void Load_Data();


struct information {

	char name[100];
	char address[100];
	char Mobile_number[20];
	char CNIC[20];
	int Room_Id[30];
	char RoomStatus[30][12];
	int Bill;
	int days;

} info,guest[100];
int guestcount = 0;

FILE *HMS;
int main() {
	int choice = 0;

	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t*                      *\n");
	printf("\t\t\t\t\t*        Welcome       *\n");
	printf("\t\t\t\t\t*           To         *\n");
	printf("\t\t\t\t\t*       \"MSK Hotel\"    *\n");
	printf("\t\t\t\t\t*                      *\n");
	printf("\t\t\t\t\t************************\n\n\n");

	Load_Data();

	while(choice != 9) {
		printf("\n\nEnter 1 -> Add Customer Details\nEnter 2 -> Edit Customer Details\nEnter 3 -> Delete Customer Details\nEnter 4 -> Reserve Room\n");
		printf("Enter 5 -> Update Room Reservation\nEnter 6 -> Cancel Room Reservation\nEnter 7 -> Services\nEnter 8 -> Bill\n");
		printf("Enter 9 -> Exit()\n");
		printf("\nEnter Your choice: ");
		scanf("%d",&choice);
		getchar();
		switch(choice) {
			case 1:
				Guest_Information();
				break;

			case 2:
				Edit_Guest_Details();
				break;
			case 3:
				Delete_Guest_Detail();
				break;
			case 4:
				Book_Room();
				break;
			case 5:
				Update_Room();
				break;
			case 6:
				Cancel_Booking();
				break;
			case 7:
				Services();
				break;
			case 8:
				Generate_Bill();
				break;
			case 9:
				Save_Data();
				break;

			default:
				printf("Invalid Choice Please Enter Again! ");
				break;
		}
	}


	return 0;
}

void Guest_Information() {

	struct information Newguest;
	int found = 0;

	printf("Enter Your Name: ");
	gets(Newguest.name);
	Newguest.name[strcspn(Newguest.name, "\n")] = 0;
	printf("Enter your Address: ");
	gets(Newguest.address);
	Newguest.address[strcspn(Newguest.address, "\n")] = 0;

	while(found == 0) {
		int check = 0;
		printf("Enter your CNIC: ");
		gets(Newguest.CNIC);
		Newguest.CNIC[strcspn(Newguest.CNIC, "\n")] = 0;

		while(strlen(Newguest.CNIC) != 15 || Newguest.CNIC[5] != '-' || Newguest.CNIC[13] != '-') {
			printf("Invalid CNIC\nEnter your CNIC Again: ");
			gets(Newguest.CNIC);
			Newguest.CNIC[strcspn(Newguest.CNIC, "\n")] = 0;
		}

		for(int i=0; i<guestcount; i++) {
			if(strcmp(guest[i].CNIC, Newguest.CNIC) == 0) {
				check = 1;
				break;
			}
		}

		if(check == 1) {
			printf("CNIC already exists!\n");
			found = 0;
		}
		else {
			found = 1;
		}
	}

	printf("Enter your Mobile Number: ");
	gets(Newguest.Mobile_number);
	Newguest.Mobile_number[strcspn(Newguest.Mobile_number, "\n")] = 0;

	Newguest.Bill = 0;
	Newguest.days = 0;

	guest[guestcount++] = Newguest;

	printf("\n\t\t\t\t\tDetail Added SuccessFully!\n");
	Save_Data();
}

void Edit_Guest_Details() {

	char CNIC[20];
	printf("Enter Your CNIC: ");
	gets(CNIC);
	CNIC[strcspn(CNIC, "\n")] = 0;
	while(strlen(CNIC) != 15 || CNIC[5] != '-' || CNIC[13] != '-') {
		printf("Invalid CNIC\nEnter your CNIC Again: ");
		gets(CNIC);
		CNIC[strcspn(CNIC, "\n")] = 0;
	}

	int Index = -1;
	for (int i = 0; i < guestcount; i++) {
		if (strcmp(guest[i].CNIC, CNIC) == 0) {
			Index = i;
			break;
		}
	}
	if (Index == -1) {
		printf("Guest not found!\n");
		return;
	}

	printf("Enter Your Name: ");
	gets(guest[Index].name);
	guest[Index].name[strcspn(guest[Index].name, "\n")] = 0;
	printf("Enter your Address: ");
	gets(guest[Index].address);
	guest[Index].address[strcspn(guest[Index].address, "\n")] = 0;
	printf("Enter your CNIC: ");
	gets(guest[Index].CNIC);
	guest[Index].CNIC[strcspn(guest[Index].CNIC, "\n")] = 0;
	while(strlen(guest[Index].CNIC) != 15 || guest[Index].CNIC[5] != '-' || guest[Index].CNIC[13] != '-') {
		printf("Invalid CNIC\nEnter your CNIC Again: ");
		gets(guest[Index].CNIC);
		guest[Index].CNIC[strcspn(guest[Index].CNIC, "\n")] = 0;
	}

	printf("Enter your Mobile Number: ");
	gets(guest[Index].Mobile_number);
	guest[Index].Mobile_number[strcspn(guest[Index].Mobile_number, "\n")] = 0;

	printf("\n\t\t\t\t\tDetail Updated SuccessFully!\n");
	Save_Data();


}

void Delete_Guest_Detail() {

	char CNIC[20];
	printf("Enter Your CNIC: ");
	gets(CNIC);
	CNIC[strcspn(CNIC, "\n")] = 0;
	while(strlen(CNIC) != 15 || CNIC[5] != '-' || CNIC[13] != '-') {
		printf("Invalid CNIC\nEnter your CNIC Again: ");
		gets(CNIC);
		CNIC[strcspn(CNIC, "\n")] = 0;
	}

	int Index = -1;
	for (int i = 0; i < guestcount; i++) {
		if (strcmp(guest[i].CNIC, CNIC) == 0) {
			Index = i;
			break;
		}
	}
	if (Index == -1) {
		printf("Guest not found!\n");
		return;
	}

	for(int i=Index; i < guestcount - 1; i++) {
		guest[i] = guest[i+1];
	}
	guestcount--;

	printf("\n\t\t\t\t\tDetails Deleted SuccessFully!\n");
	Save_Data();

}

void Book_Room() {
	int choice,days;
	char Avail[12]="Available";
	char Reserve[12]="Reserved ";

	if(guestcount==1) {

		for (int i = 0; i < 30; i++) {
			info.Room_Id[i] = 101+i;
		}

		for (int i = 0; i < 30; i++) {
			if(strcmp(info.RoomStatus[i], Reserve) != 0) {
				strcpy(info.RoomStatus[i], Avail);
			}
		}
	}

	char CNIC[20];
	printf("Enter Your CNIC: ");
	gets(CNIC);
	CNIC[strcspn(CNIC, "\n")] = 0;
	while(strlen(CNIC) != 15 || CNIC[5] != '-' || CNIC[13] != '-') {
		printf("Invalid CNIC\nEnter your CNIC Again: ");
		gets(CNIC);
		CNIC[strcspn(CNIC, "\n")] = 0;
	}

	int Index = -1;
	for (int i = 0; i < guestcount; i++) {
		if (strcmp(guest[i].CNIC, CNIC) == 0) {
			Index = i;
			break;
		}
	}
	if (Index == -1) {
		printf("Guest not found!\n");
		return;
	}


	printf("\t\t\t\t\tRoom Status:\n");
	for (int i = 0; i < 30; i++) {
		printf("\t%d. %s ",info.Room_Id[i],info.RoomStatus[i]);
		if ((i + 1) % 5 == 0) {
			printf("\n");
		}
	}


	printf("\n\n\tEnter the Room Id to Reserve the Room: ");
	scanf("%d",&choice);
	printf("\n\tEnter the number of days for Booking: ");
	scanf("%d",&days);

	for (int i = 0; i < 30; i++) {
		if (info.Room_Id[i] == choice && strcmp(info.RoomStatus[i],Avail)==0) {
			strcpy(info.RoomStatus[i], Reserve);
			strcpy(guest[Index].RoomStatus[i],Reserve);
			guest[Index].Room_Id[i] = choice;
			printf("\nRoom Reserved Successfully!\n");
			guest[Index].days = days;
			guest[Index].Bill += 3500 * days;
		}
	}

	Save_Data();
}
void Update_Room() {
	int oldRoom, newRoom, days;
	char Avail[12] = "Available";
	char Reserve[12] = "Reserved ";
	char CNIC[20];
	int found = 0;

	printf("Enter Your CNIC: ");
	gets(CNIC);
	CNIC[strcspn(CNIC, "\n")] = 0;
	while(strlen(CNIC) != 15 || CNIC[5] != '-' || CNIC[13] != '-') {
		printf("Invalid CNIC\nEnter your CNIC Again: ");
		gets(CNIC);
		CNIC[strcspn(CNIC, "\n")] = 0;
	}

	int Index = -1;
	for (int i = 0; i < guestcount; i++) {
		if (strcmp(guest[i].CNIC, CNIC) == 0) {
			Index = i;
			break;
		}
	}
	if (Index == -1) {
		printf("Guest not found!\n");
		return;
	}

	printf("\nYour current room bookings:\n");
	for (int i = 0; i < 30; i++) {
		if (strcmp(guest[Index].RoomStatus[i], Reserve) == 0) {
			printf("Room %d is reserved under your name\n", guest[Index].Room_Id[i]);
			found = 1;
		}
	}

	if (!found) {
		printf("You don't have any room bookings!\n");
		return;
	}

	printf("\nEnter the Room number you want to change: ");
	scanf("%d", &oldRoom);
	
	found = 0;
	for (int i = 0; i < 30; i++) {
		if (guest[Index].Room_Id[i] == oldRoom && strcmp(guest[Index].RoomStatus[i], Reserve) == 0) {
			found = 1;
			break;
		}
	}
	
	if (!found) {
		printf("This room is not reserved under your name!\n");
		return;
	}

	printf("\nRooms Status:\n");
	for (int i = 0; i < 30; i++) {
			printf("\t%d. %s ", info.Room_Id[i], info.RoomStatus[i]);
			if ((i + 1) % 5 == 0) printf("\n");
		
	}

	printf("\n\nEnter the new Room Id you want to reserve: ");
	scanf("%d", &newRoom);
	
	found = 0;
	for (int i = 0; i < 30; i++) {
		if (info.Room_Id[i] == newRoom && strcmp(info.RoomStatus[i], Avail) == 0) {
			found = 1;
			break;
		}
	}
	
	if (!found) {
		printf("Selected room is not available!\n");
		return;
	}

	printf("\nEnter the number of days for Booking: ");
	scanf("%d", &days);

	printf("\nConfirm room change from %d to %d? (1 for Yes, 0 for No): ", oldRoom, newRoom);
	int confirm;
	scanf("%d", &confirm);

	if (confirm == 1) {
		for (int i = 0; i < 30; i++) {
			if (info.Room_Id[i] == oldRoom) {
				strcpy(info.RoomStatus[i], Avail);
				strcpy(guest[Index].RoomStatus[i], Avail);
			}
			if (info.Room_Id[i] == newRoom) {
				strcpy(info.RoomStatus[i], Reserve);
				strcpy(guest[Index].RoomStatus[i], Reserve);
				guest[Index].Room_Id[i] = newRoom;
				guest[Index].days = days;
				guest[Index].Bill = guest[Index].Bill - (3500 * guest[Index].days) + (3500 * days);
			}
		}
		printf("\nRoom Updated Successfully!\n");
	} else {
		printf("\nRoom change cancelled!\n");
	}

	Save_Data();
}

void Services() {
	int choice = 0;

	char CNIC[20];
	printf("Enter Your CNIC: ");
	gets(CNIC);
	CNIC[strcspn(CNIC, "\n")] = 0;
	while(strlen(CNIC) != 15 || CNIC[5] != '-' || CNIC[13] != '-') {
		printf("Invalid CNIC\nEnter your CNIC Again: ");
		gets(CNIC);
		CNIC[strcspn(CNIC, "\n")] = 0;
		
	}

	int Index = -1;
	for (int i = 0; i < guestcount; i++) {
		if (strcmp(guest[i].CNIC, CNIC) == 0) {
			Index = i;
			break;
		}
	}
	if (Index == -1) {
		printf("Guest not found!\n");
		return;
	}

	while(choice != 6) {

		printf("\n\n1: laundry\n");
		printf("2: Cleaning\n");
		printf("3: Food\n");
		printf("4: Drinks\n");
		printf("5: Cancel Last Order\n");
		printf("6: Exit()\n");
		printf("Enter your Choice: ");
		scanf("%d",&choice);

		switch(choice) {
			case 1:
				int NoOfSuit;
				printf("Cost of 1 suit is: 120\n");
				printf("Enter the Number of Suits: ");
				scanf("%d",&NoOfSuit);
				printf("Thank You!");
				guest[Index].Bill += 120*NoOfSuit;
				break;
			case 2:
				printf("Cost per day: 150 \n");
				printf("Thank You!");
				guest[Index].Bill += 150;
				break;
			case 3:
				int choiceForItem;
				while(choiceForItem != 7) {

					printf("\n\n\t\t       Food Item Name  	    	:  Prices\n");
					printf("\t\t1: Burger (McDonald's)		:   250\n");
					printf("\t\t2: Chicken McNuggets(10 pieces) :   300\n");
					printf("\t\t3: French Fries (Medium)	:   150\n");
					printf("\t\t4: Pizza Slice (Pizza Hut)	:   200\n");
					printf("\t\t5: Shawarma (Medium)		:   180\n");
					printf("\t\t6: Cancel Last Order\n");
					printf("\t\t7: Exit()\n");

					printf("Enter Your Choice: ");
					scanf("%d",&choiceForItem);
					switch(choiceForItem) {
						case 1:
							printf("Order Confirm!!");
							guest[Index].Bill += 250;
							break;
						case 2:
							printf("Order Confirm!!");
							guest[Index].Bill += 300;
							break;
						case 3:
							printf("Order Confirm!!");
							guest[Index].Bill += 150;
							break;
						case 4:
							printf("Order Confirm!!");
							guest[Index].Bill += 200;
							break;
						case 5:
							printf("Order Confirm!!");
							guest[Index].Bill += 180;
							break;
						case 6:
							printf("\nEnter the item number to cancel (1-5): ");
							int cancelItem;
							scanf("%d", &cancelItem);
							switch(cancelItem) {
								case 1:
									guest[Index].Bill -= 250;
									printf("Burger order cancelled!\n");
									break;
								case 2:
									guest[Index].Bill -= 300;
									printf("Chicken McNuggets order cancelled!\n");
									break;
								case 3:
									guest[Index].Bill -= 150;
									printf("French Fries order cancelled!\n");
									break;
								case 4:
									guest[Index].Bill -= 200;
									printf("Pizza Slice order cancelled!\n");
									break;
								case 5:
									guest[Index].Bill -= 180;
									printf("Shawarma order cancelled!\n");
									break;
								default:
									printf("Invalid item number!\n");
							}
							break;
						case 7:
							printf("\nThank You !!");
							break;
						default:
							printf("Sorry Invalid Choice Please try again!");
							break;
					}
				}
				break;

			case 4:
				int choiceForDrink;
				while (choiceForDrink != 7) {

					printf("\n\n\t\t     Drink Items Name  	:  Prices\n");
					printf("\t\t1: Pepsi (1.5 liter)	:   200\n");
					printf("\t\t2: 7UP (1.5 liter)	:   200\n");
					printf("\t\t3: Red Bull (250 ml)	:   350\n");
					printf("\t\t4: Tea (1 cup)		:   70\n");
					printf("\t\t5: Lassi (500 ml)	:   80\n");
					printf("\t\t6: Cancel Last Order\n");
					printf("\t\t7: Exit()\n");

					printf("Enter Your Choice: ");
					scanf("%d",&choiceForDrink);

					switch(choiceForDrink) {
						case 1:
							printf("Order for Pepsi is Confirm!!!!");
							guest[Index].Bill += 200;
							break;
						case 2:
							printf("Order for 7UP is Confirm!!!!");
							guest[Index].Bill += 200;
							break;
						case 3:
							printf("Order for Red Bull is Confirm!!!!");
							guest[Index].Bill += 350;
							break;
						case 4:
							printf("Order for Tea is Confirm!!!!");
							guest[Index].Bill += 70;
							break;
						case 5:
							printf("Order for lassi is Confirm!!!!");
							guest[Index].Bill += 80;
							break;
						case 6:
							printf("\nEnter the drink number to cancel (1-5): ");
							int cancelDrink;
							scanf("%d", &cancelDrink);
							switch(cancelDrink) {
								case 1:
									guest[Index].Bill -= 200;
									printf("Order for Pepsi is cancelled!\n");
									break;
								case 2:
									guest[Index].Bill -= 200;
									printf("Order for 7UP is cancelled!\n");
									break;
								case 3:
									guest[Index].Bill -= 350;
									printf("Order for Red Bull is cancelled!\n");
									break;
								case 4:
									guest[Index].Bill -= 70;
									printf("Order for Tea is cancelled!\n");
									break;
								case 5:
									guest[Index].Bill -= 80;
									printf("Order for Lassi is cancelled!\n");
									break;
								default:
									printf("Invalid drink number!\n");
							}
							break;
						case 7:
							printf("\nThank You !!");
							break;
						default:
							printf("Sorry Invalid Choice Please try again!");
							break;
					}
				}
				break;

			case 5:
				if(guest[Index].Bill > 0) {
					int cancelChoice;
					printf("\nSelect service to cancel:\n");
					printf("1: Laundry (120 per suit)\n");
					printf("2: Cleaning (150)\n");
					printf("3: Food\n");
					printf("4: Drinks\n");
					printf("Enter your choice: ");
					scanf("%d", &cancelChoice);

					switch(cancelChoice) {
						case 1: {
							int suits;
							printf("Enter number of suits to cancel: ");
							scanf("%d", &suits);
							guest[Index].Bill -= 120 * suits;
							printf("Laundry order cancelled successfully!\n");
							break;
						}
						case 2:
							guest[Index].Bill -= 150;
							printf("Cleaning service cancelled successfully!\n");
							break;
						case 3: {
							int foodItem;
							printf("Enter food item to cancel (1-5): ");
							scanf("%d", &foodItem);
							switch(foodItem) {
								case 1: guest[Index].Bill -= 250; break;
								case 2: guest[Index].Bill -= 300; break;
								case 3: guest[Index].Bill -= 150; break;
								case 4: guest[Index].Bill -= 200; break;
								case 5: guest[Index].Bill -= 180; break;
								default: printf("Invalid food item!\n");
							}
							if(foodItem >= 1 && foodItem <= 5)
								printf("Food order cancelled successfully!\n");
							break;
						}
						case 4: {
							int drinkItem;
							printf("Enter drink item to cancel (1-5): ");
							scanf("%d", &drinkItem);
							switch(drinkItem) {
								case 1: case 2: guest[Index].Bill -= 200; break;
								case 3: guest[Index].Bill -= 350; break;
								case 4: guest[Index].Bill -= 70; break;
								case 5: guest[Index].Bill -= 80; break;
								default: printf("Invalid drink item!\n");
							}
							if(drinkItem >= 1 && drinkItem <= 5)
								printf("Drink order cancelled successfully!\n");
							break;
						}
						default:
							printf("Invalid choice!\n");
					}
				} else {
					printf("No orders to cancel!\n");
				}
				break;

			case 6:
				printf("Thank you for Using our services! ");
				break;

			default:
				printf("Invalid Choice Try Again! ");
				break;
		}
	}

	Save_Data();
}

void Cancel_Booking() {
	int choice;
	char Avail[12] = "Available";

	char CNIC[20];
	printf("Enter Your CNIC: ");
	gets(CNIC);
	CNIC[strcspn(CNIC, "\n")] = 0;
	while(strlen(CNIC) != 15 || CNIC[5] != '-' || CNIC[13] != '-') {
		printf("Invalid CNIC\nEnter your CNIC Again: ");
		gets(CNIC);
		CNIC[strcspn(CNIC, "\n")] = 0;
	}

	int Index = -1;
	for (int i = 0; i < guestcount; i++) {
		if (strcmp(guest[i].CNIC, CNIC) == 0) {
			Index = i;
			break;
		}
	}
	if (Index == -1) {
		printf("Guest not found!\n");
		return;
	}

	printf("\nEnter the Room Id to Cancel the Booking: ");
	scanf("%d", &choice);
	for (int i = 0; i < 30; i++) {
		if (info.Room_Id[i] == choice) {
			strcpy(info.RoomStatus[i], Avail);
			strcpy(guest[Index].RoomStatus[i],Avail);
			printf("\nBooking Cancelled Successfully!\n");
		}
	}


	guest[Index].Bill -= 3500 * guest[Index].days;
	guest[Index].days = 0;

	Save_Data();
}
void Generate_Bill() {

	char CNIC[20];
	printf("Enter Your CNIC: ");
	gets(CNIC);
	CNIC[strcspn(CNIC, "\n")] = 0;
	while(strlen(CNIC) != 15 || CNIC[5] != '-' || CNIC[13] != '-') {
		printf("Invalid CNIC\nEnter your CNIC Again: ");
		gets(CNIC);
		CNIC[strcspn(CNIC, "\n")] = 0;
	}
	int Index = -1;
	for (int i = 0; i < guestcount; i++) {
		if (strcmp(guest[i].CNIC, CNIC) == 0) {
			Index = i;
			break;
		}
	}
	if (Index == -1) {
		printf("Guest not found!\n");
		return;
	}

	printf("Total Bill of Guest %s is: %d\n\n",guest[Index].name,guest[Index].Bill);
}

void Load_Data() {
	HMS = fopen("Hotel_Management_System.txt", "r");
	if (HMS == NULL) {
		return;
	}

	while (fscanf(HMS, "Name: %[^\n]\n", guest[guestcount].name) == 1) {
		fscanf(HMS, "Address: %s\n", guest[guestcount].address);
		fscanf(HMS, "CNIC: %s\n", guest[guestcount].CNIC);
		fscanf(HMS, "Mobile Number: %s\n", guest[guestcount].Mobile_number);
		fscanf(HMS, "Room Id: %d Reserved for %d Days\n", &guest[guestcount].Room_Id[0], &guest[guestcount].days);
		fscanf(HMS, "Bill: %d\n",&guest[guestcount].Bill);
		for(int j=0; j<30; j++) {
			fscanf(HMS, "%d: %s\n", &info.Room_Id[j], info.RoomStatus[j]);
		}

		guestcount++;
	}

	fclose(HMS);
}

void Save_Data() {
	HMS = fopen("Hotel_Management_System.txt", "w");
	if(HMS == NULL) {
		printf("Error in opening file to save data.\n");
		return;
	}
	for (int i = 0; i < guestcount; i++) {
		fprintf(HMS, "Name: %s\n", guest[i].name);
		fprintf(HMS, "Address: %s\n", guest[i].address);
		fprintf(HMS, "CNIC: %s\n", guest[i].CNIC);
		fprintf(HMS, "Mobile Number: %s\n", guest[i].Mobile_number);
		fprintf(HMS, "Room Id: %d Reserved for %d Days\n", guest[i].Room_Id[i],guest[i].days);
		fprintf(HMS, "Bill: %d\n", guest[i].Bill);


	}

	for (int j = 0; j < 30; j++) {
		fprintf(HMS, "%d: %s\n", info.Room_Id[j], info.RoomStatus[j]);
	}

	fclose(HMS);
}
