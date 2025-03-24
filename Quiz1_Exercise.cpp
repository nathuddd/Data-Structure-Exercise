#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Struct to store data
struct data{
	int dl;
	char name[21];
	int id;
	struct data *prev, *next;
} *head = NULL, *tail = NULL;

// Funtion to create new node
struct data *create(int dlN, char nameN[], int idN){
	struct data *temp = (struct data*)malloc(sizeof(struct data));
	temp->dl = dlN;
	strcpy(temp->name, nameN);
	temp->id = idN;
	return temp;
}

// Function to push data
void push(int dlN, char nameN[], int idN){
	struct data *newData = create(dlN, nameN, idN);
	
	// If list is empty
	if(head == NULL && tail == NULL){
		head = tail = newData;
	}
	
	// If newData's deadline is smaller than head
	else if(dlN < head->dl || dlN == head->dl){
		head->prev = newData;
		newData->next = head;
		head = newData;
	}
	
	// If newData's deadline is bigger than tail
	else if(dlN > tail->dl || dlN == tail->dl){
		tail->next = newData;
		newData->prev = tail;
		tail = newData;
	}
	
	// If newData's deadline is in between head and tail
	else{
		struct data *curr = head;
		while(curr->next != NULL && dlN > curr->next->dl){
			curr = curr->next;
		}
		newData->next = curr->next;
		newData->prev = curr;
		curr->next = newData;
		newData->next->prev = curr;
	}
	
	head->prev = tail->next = NULL;
	printf("Push Done!\n");
}

// Function to complete finishTask operation
void finishTask(){
	struct data *temp = head;
	// If list is empty
	if(head == NULL && tail == NULL){
		printf("No Data!\n");
	}
	
	// If there's only one data
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	
	// Delete head
	else{
		head = head->next;
		free(temp);
	}
	
	head->prev = tail->prev = NULL;
	printf("finishTask Done!\n");
	return;
}

// Function to complete removeId operation
void removeId(int delId){
	struct data *temp;
	
	// If list is emoy
	if(head == NULL && tail == NULL){
		printf("No Data!\n");
	}
	
	// If there's only one data
	else if(head == tail && head->id == delId){
		free(head);
		head = tail = NULL;
	}
	
	// If removeId == head->id
	else if(delId == head->id){
		temp = head;
		head = head->next;
		free(temp);
	}
	
	// If removeId == tail->id
	else if(delId == tail->id){
		temp = tail;
		tail = tail->prev;
		free(temp);
	}
	
	// If removeId is in between tail and head
	else{
		struct data *curr = head;
		while(curr->next != NULL && delId != curr->next->id){
			curr = curr->next;
		}
		if(curr->next == NULL){
			printf("id %d does not exist!\n", delId);
			return;
		}
		else{
			temp = curr->next;
			curr->next = temp->next;
			temp->next->prev = curr;
			free(temp);
		}
	}
	
	head->prev = tail->next = NULL;
	return;
}

// Function to display data
void display(){
	struct data *curr = head;
	if(head == NULL && tail == NULL){
		printf("No Data!\n");
		return;
	}
	while(curr != NULL){
		printf("deadline: %d\ntask name: %s\nid: %d\n\n", curr->dl, curr->name, curr->id);
		curr = curr->next;
	}
	printf("Display Done!\n");
	return;
}

int main(){
	
	int task, op;
	scanf("%d %d", &task, &op); getchar();
	
	int dlN;
	char nameN[21];
	int idN = 1;
	for(int i = 0; i < task; i++){
		scanf("%d %[^\n]", &dlN, &nameN); getchar();
		push(dlN, nameN, idN);
		idN++;
	}
	printf("\n");
	
	char act[11];
	int delId;
	for(int i = 0; i <op; i++){
		scanf("%s", &act); getchar();
		if(strcmp(act, "finishTask") == 0){
			finishTask();
		} else if(strcmp(act, "removeId") == 0){
			scanf("%d", &delId); getchar();
			removeId(delId);
		} else{
			printf("Invalid Action!\n");
		}
	}
	printf("\n");
	
	display();
	
	return 0;
}
