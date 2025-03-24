#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Struct to store bread's data
struct data{
	int id;
	char name[51];
	double price;
	char type[31];
	struct data *prev, *next;
} *head = NULL, *tail = NULL;

// Function to create new node
struct data *create(int idN, char nameN[], double priceN, char typeN[]){
	struct data *temp = (struct data*)malloc(sizeof(struct data));
	temp->id = idN;
	strcpy(temp->name, nameN);
	temp->price = priceN;
	strcpy(temp->type, typeN);
	return temp;
}

// Function to push data

void push(int idN, char nameN[], double priceN, char typeN[]){
	struct data *newData = create(idN, nameN, priceN, typeN);
	
	// If data list is currently empty
	if(head == NULL && tail == NULL){
		head = tail = newData;
	}
	
	// if newData is smaller than current head
	else if(idN < head->id){
		newData->next = head;
		head->prev = newData;
		head = newData;
	}
	
	// if newData is bigger than current tail
	else if(idN > tail->id){
		tail->next = newData;
		newData->prev = tail;
		tail = newData;
	}
	
	// if newData is in the middle of head and tail
	else{
		struct data *curr = head;
		while(curr->next != NULL && idN > curr->next->id){
			curr = curr->next;
		}
		newData->prev = curr;
		newData->next = curr->next;
		curr->next = newData;	
		newData->next->prev = newData;
	}
	head->prev = tail->next = NULL;
	printf("Succesfull Push!\n");
}

void pop(char delName[]){
	
	struct data *temp;
	
	// If data is empty
	if(head == NULL && tail == NULL){
		printf("No Data!\n");
		return;
	}
	
	// If there' only one data
	else if(head == tail && strcmp(head->name, delName) == 0){
		printf("ID: %d\nName: %s\nPrice: $%.2lf\nType: %s\n", temp->id, temp->name, temp->price, temp->type);
		free(head);
		free(tail);
		head = tail = NULL;
	}
	
	// If head->name is == delName
	else if(strcmp(delName, head->name) == 0){
		temp = head;
		printf("ID: %d\nName: %s\nPrice: $%.2lf\nType: %s\n", temp->id, temp->name, temp->price, temp->type);
		head = head->next;
		free(temp);
	}
	
	// If tail->name is == delName
	else if(strcmp(delName, tail->name) == 0){
		temp = tail;
		printf("ID: %d\nName: %s\nPrice: $%.2lf\nType: %s\n", temp->id, temp->name, temp->price, temp->type);
		tail = tail->prev;
		free(temp);
	}
	
	// If delName is in the middle of head and tail
	else{
		struct data *curr = head;
		while(curr->next != NULL && strcmp(curr->next->name, delName) != 0){
			curr = curr->next;
		}
		if(curr->next == NULL){
			printf("%s does not exist!\n", delName);
			return;
		}
		else{
			temp = curr->next;
			printf("ID: %d\nName: %s\nPrice: $%.2lf\nType: %s\n", temp->id, temp->name, temp->price, temp->type);
			curr->next = temp->next;
			curr->next->prev = curr;
			free(temp);
		}
	}
	head->prev = tail->next = NULL;
	return;
}

void searchID(int findID){
	struct data *curr;
	
	// If data is empty
	if(head == NULL && tail == NULL){
		printf("No Data!\n");
		return;
	}
	
	// If there's only one data
	else if(head == tail && head->id == findID){
		curr = head;
	}
	
	// If findId == head
	else if(head->id == findID){
		curr = head;
	}
	
	// If findID == tail
	else if(tail->id == findID){
		curr = tail;
	}
	
	// If findId is in the middle of head and tail
	else{
		curr = head;
		while(curr != NULL && curr->id != findID){
			curr = curr->next;
		}
		if(curr == NULL){
			printf("No bread by ID: %d", findID);
			return;
		}
	}
	printf("Find It!\n");
	printf("ID: %d\nName: %s\nPrice: $%.2lf\nType: %s\n", curr->id, curr->name, curr->price, curr->type);
}

int searchName(char upName[]){
	struct data *curr;
	
	// If data is empty
	if(head == NULL && tail == NULL){
		printf("No Data!\n");
		return -1;
	}
	
	// If there's only one data
	else if(head == tail && strcmp(head->name, upName) == 0){
		curr = head;
	}
	
	// If findId == head
	else if(strcmp(head->name, upName) == 0){
		curr = head;
	}
	
	// If findID == tail
	else if(strcmp(tail->name, upName) == 0){
		curr = tail;
	}
	
	// If findId is in the middle of headn and tail
	else{
		curr = head;
		while(curr != NULL && strcmp(curr->name, upName) != 0){
			curr = curr->next;
		}
		if(curr == NULL){
			printf("No bread by name: %s", upName);
			return -1;
		}
	}
	printf("Find It!\n");
	printf("ID: %d\nName: %s\nPrice: $%.2lf\nType: %s\n", curr->id, curr->name, curr->price, curr->type);
	return curr->id;
}

void updatePrice(double upPrice, int upID){
	struct data *curr = head;
	while(curr != NULL && curr->id != upID){
		curr = curr->next;
	}
	curr->price = upPrice;
	printf("Updated Succesfully!\n");
	printf("ID: %d\nName: %s\nPrice: $%.2lf\nType: %s\n", curr->id, curr->name, curr->price, curr->type);
}

void displayType(char findType[]){
	if(head == NULL && tail == NULL){
		printf("No Data!\n");
		return;	
	}
	struct data *curr = head;
	int no = 1;
	int found = 0;
	printf("%-2s || %-3s | %-20s | %-6s | %-20s\n", "No", "ID", "Name", "Price", "Type");
	while(curr != NULL){
		if(strcmp(curr->type, findType) == 0){
			printf("%.2d || %.3d | %-20s | $%.2lf | %-20s\n", no, curr->id, curr->name, curr->price, curr->type);	
			no++;
			found = 1;
		}
		curr = curr->next;
	}
}

void display(){
	if(head == NULL && tail == NULL){
		printf("No Data!\n");
		return;	
	}
	struct data *curr = head;
	int no = 1;
	printf("%-2s || %-3s | %-20s | %-6s | %-20s\n", "No", "ID", "Name", "Price", "Type");
	
	while(curr != NULL){
		printf("%.2d || %.3d | %-20s | $%.2lf | %-20s\n", no, curr->id, curr->name, curr->price, curr->type);
		curr = curr->next;
		no++;
	}
}

int main(){

	int choose;
	int idN;
	char nameN[51];
	double priceN;
	char typeN[31];
	
	while(true){
		printf("Menu:\n1. Add New Bread\n2. View All Bread\n3. Search for Bread by ID\n4. Update Bread Information\n5. Remove Discontinued Bread\n6. Show Bread by Type\n7. Exit\n=> ");
		scanf("%d", &choose); getchar();
		while(choose < 0 || choose > 7){
			printf("Invalid menu, choose again:\n=> ");
			scanf("%d", &choose); getchar();
		}
		printf("\n");
		
		switch(choose){	
			// Add New Bread
			case 1:
				int totalAdd;
				
				printf("How many bread would you like to add? ");
				scanf("%d", &totalAdd); getchar();
				printf("\n");
				
				for(int i = 0; i < totalAdd; i++){
					printf("ID: ");
					scanf("%d", &idN); getchar();
					printf("Name: ");
					scanf("%[^\n]", &nameN); getchar();
					printf("Price: $");
					scanf("%lf", &priceN); getchar();
					printf("Type: ");
					scanf("%[^\n]", &typeN); getchar();
					
					push(idN, nameN, priceN, typeN);
					printf("\n");
				}
				
				break;
				
			// View All Bread	
			case 2:
				display();
				printf("\n");
				break;
			
			// Search for Bread by ID	
			case 3:
				int findID;
				
				printf("ID to Find: ");
				scanf("%d", &findID); getchar();
				printf("\n");
				searchID(findID);
				printf("\n");
				break;
				
			// Update Bread Information
			case 4:
				char upName[51];
				double upPrice;
				int upID;
				
				printf("Name of Bread to be Updated: ");
				scanf("%[^\n]", &upName); getchar();
				upID = searchName(upName); 
				printf("\n");
				
				if(upID == -1) {
					break;
				}
				else{
					printf("Change price to: $");
					scanf("%lf", &upPrice); getchar();
					printf("\n");
					updatePrice(upPrice, upID);	
					printf("\n");
				}
				
				break;
				
			// Remove Discontinued Bread
			case 5:
				char delName[51];
				
				printf("Name of Bread to be Removed: ");
				scanf("%[^\n]", &delName); getchar();
				pop(delName);
				printf("Data Deleted Succsfully!\n");
				printf("\n");
				break;
				
			// Find Bread by Type (Display by Type)
			case 6:
				char findType[31];
				
				printf("Type of Bread to Show: ");
				scanf("%[^\n]", &findType); getchar();
				
				displayType(findType);
				
				break;
				
			// Exit
			case 7:
				printf("Exiting!");
				return 0;
		}
		printf("Press enter to continue to menu selection!");
		getchar();
		system("cls");
	}
	
return 0;
}
