#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
void Add_new_medicine();
void Purchase_Sales_medicine();
void Delete_medicine();
void Search_for_medicine();
void Display_all_medicine();
void Exit();
int main() {
    char pass[30];
    int ch, i;
    printf("\t\t\t\t\t WELCOME TO MEDICAL STORE MANAGEMENT SYSTEM\n\n\n");
    abc:
    printf("\t\t\t Enter Password:");
    i = 0;
    while ((pass[i] = getch()) != '\r') {
        printf("*");
        i++;
    }
    pass[i] = '\0';
    if (strcmp(pass, "lumbini") == 0){
    	printf("\n\nLogin successfully!!!");
    	getch();
		xyz:
		system("cls");
        printf("\t\t\t\tWELCOME TO MEDICAL STORE MANAGEMENT SYSTEM\n\n\n");
        printf("\t\t\t\tMENU\n\n");
        printf("\t\t\t1. Add new medicine\n");
        printf("\t\t\t2. Purchase/Sales medicine\n");
        printf("\t\t\t3. Delete medicine\n");
        printf("\t\t\t4. Search for medicine\n");
        printf("\t\t\t5. Display all medicine\n");
        printf("\t\t\t6. Exit\n\n");
        printf("\t\t\tEnter your choice:\t");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                Add_new_medicine();
                system("cls");
                goto xyz;
                break;
            case 2:
               Purchase_Sales_medicine();
                system("cls");
                goto xyz;
                break;
            case 3:
                Delete_medicine();
                system("cls");
                goto xyz;
                break;
            case 4:
                Search_for_medicine();
                system("cls");
                goto xyz;
                break;
            case 5:
                Display_all_medicine();
                getch();
                system("cls");
                goto xyz;
                break;
            case 6:
                Exit();
                break;
            default:
                printf("Invalid Input\n");
                getch();
                goto xyz;
        }
    } else {
        system("cls");
        printf("\t\t\tWrong Password\n");
        goto abc;
    }
    getch();
    return 0;
}
void Add_new_medicine() {
    char name[40];
    int id, quantity, rack, check_id;
    float price;
    FILE *ptr1, *ptr2;
    medicine_id:
    ptr1 = fopen("medicine.txt", "a+");
    ptr2 = fopen("new.txt", "w");
    system("cls");
    printf("\n Enter id:");
    scanf("%d", &check_id);
    while (fscanf(ptr1, "%d%s%d%f%d", &id, name, &quantity, &price, &rack) != EOF) {
        if (check_id == id) {
            printf("!!ID already exists!! You can't add the same ID!!\n\n");
            goto last;
        }
    }
    id = check_id;
    printf("\nEnter name:");
    scanf("%s", name);
    printf("\nEnter quantity:");
    scanf("%d", &quantity);
    printf("\nEnter price:");
    scanf("%f", &price);
    printf("\nEnter Rack Number:");
    scanf("%d", &rack);
    fprintf(ptr1, "%d\t%s\t%d\t%f\t%d\n", id, name, quantity, price, rack);
    fclose(ptr1);
    printf("!!Medicine added successfully!!\n");
    last:
    getch();
}
void Purchase_Sales_medicine() {
    char name[40];
    int choice, test = 0, check_id, id, quantity, newquantity, rack;
    float price, newprice;
    FILE *ptr1, *ptr2;
    ptr1 = fopen("medicine.txt", "r");
    ptr2 = fopen("newmedicine.txt", "w");
    printf("Enter ID to Purchase/Sales medicine\n");
    scanf("%d", &check_id);
    while (fscanf(ptr1, "%d%s%d%f%d", &id, name, &quantity, &price, &rack) != EOF)
	 {
        if (check_id == id)
		{
            test = 1;
            printf("Medicine found!\n");
            printf("1. Purchase\n");
            printf("2. Sales\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            system("cls");
            if (choice == 1) 
			{
                printf("Enter the quantity to purchase: ");
                scanf("%d", &newquantity);
                quantity=quantity+newquantity;
                fprintf(ptr2, "%d\t%s\t%d\t%f\t%d\n", id, name, quantity, price, rack);
                printf("!!Purchased successfully !!\n");
                getch();
            }
			 else if(choice==2) 
			{
                printf("Enter the quantity to sale: ");
                scanf("%d", &newquantity);
                if (newquantity<=quantity) 
				{
                    quantity=quantity-newquantity;
                    fprintf(ptr2, "%d\t%s\t%d\t%f\t%d\n", id, name, quantity, price, rack);
                    printf("!!Sold successfully !!\n", quantity, id);
                }
				else
				{
				fprintf(ptr2, "%d\t%s\t%d\t%f\t%d\n",id,name, quantity, price, rack);
                    printf("Not enough stock to sale.\n");	
				 }
			}
		}
				else
				{
                   fprintf(ptr2, "%d\t%s\t%d\t%f\t%d\n",id,name, quantity, price, rack); 
                }   
        } 	
        getch();
    fclose(ptr1);
    fclose(ptr2);
    remove("medicine.txt");
    rename("newmedicine.txt", "medicine.txt");
    if (test == 0) {
        system("cls");
        printf("!!Medicine ID %d not found!!\n", check_id);
    }
    getch();
}
void Delete_medicine() {
    char name[40];
    int id, check_id, quantity, rack, test = 0;
    float price;
    FILE *ptr1, *ptr2;

    ptr1 = fopen("medicine.txt", "r");
    if (ptr1 == NULL) {
        printf("File doesn't exist\n");
        getch();
        return;
    }
    
    ptr2 = fopen("newmedicine.txt", "w");

    printf("Enter id to delete medicine:\n");
    scanf("%d", &check_id);

    while (fscanf(ptr1, "%d%s%d%f%d", &id, name, &quantity, &price, &rack) != EOF) {
        if (check_id != id) {
            fprintf(ptr2, "%d\t%s\t%d\t%f\t%d\n", id, name, quantity, price, rack);
        } else {
            printf("!!Medicine Deleted Successfully!!\n");
            test = 1;
        }
    }

    fclose(ptr1);
    fclose(ptr2);
    remove("medicine.txt");
    rename("newmedicine.txt", "medicine.txt");

    if (test == 0) {
        printf("Medicine not found\n");
    }

    getch();
}

void Search_for_medicine() {
    char name[40];
    int id, check_id, quantity, rack, test = 0;
    float price;
    FILE *ptr1;
    ptr1 = fopen("medicine.txt", "r");
    printf("\n Enter ID to search for medicine: ");
    scanf("%d", &check_id);
    while (fscanf(ptr1, "%d%s%d%f%d", &id, name, &quantity, &price, &rack) != EOF) {
        if (check_id == id) {
            system("cls");
            test = 1;
            printf("\t\tMedicine Details\n");
            printf("\nName: %s", name);
            printf("\nQuantity: %d", quantity);
            printf("\nPrice: %f", price);
            printf("\nRack Number: %d", rack);
        }
    }
    if (test == 0) {
        system("cls");
        printf("\t\t\t!!Medicine ID %d Does not exist!!\n", check_id);
    }
    getch();
}
void Display_all_medicine() {
    int id, quantity, rack;
    char name[40];
    float price;
    FILE *ptr;
    ptr = fopen("medicine.txt", "r");
    if (ptr == NULL) {
        printf("File doesn't exist\n");
        getch();
        return;
    }
    system("cls");
    printf("=====================================================================================================\n");
    printf("| %-10s | %-25s | %-10s | %-10s | %-10s |\n", "ID", "Name of Medicine", "Quantity", "Price", "Rack");
    printf("=====================================================================================================\n");
    while (fscanf(ptr, "%d%s%d%f%d", &id, name, &quantity, &price, &rack) != EOF) {
        printf("| %-10d | %-25s | %-10d | %-10.2f | %-10d |\n", id, name, quantity, price, rack);
    }
    printf("=====================================================================================================\n");
    fclose(ptr);
    getch();
}
void Exit() {
    printf("............................ !!!Program is Terminating!!!.......................");
    getch();
}
