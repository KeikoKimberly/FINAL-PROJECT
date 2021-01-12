#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char PantryIngredientGroup[7][255]={"Beans", "Dairy", "Fruits", "Meats", "Others","Spices", "Vegetables" };

struct PantryIngredient{
	char group[255];
	char name[255];
	int qty;
	PantryIngredient *next, *prev;
} *PantryHead, *PantryTail;

PantryIngredient *createPantryIngredient(char *group, char *name, int qty){
	PantryIngredient *temp = (PantryIngredient*)malloc(sizeof(PantryIngredient));
	strcpy(temp->group, group);
	strcpy(temp->name, name);
	temp->qty = qty;
	temp->next = temp->prev = NULL;
	return temp;
}

void PantryIngredientPushHead(char *group, char *name, int qty){
	PantryIngredient *temp = createPantryIngredient(group, name, qty);
	if(!PantryHead){
		PantryHead = PantryTail = temp;
	} else {
		PantryHead->prev = temp;
		temp->next = PantryHead;
		PantryHead = temp;
	}
}

void PantryIngredientPushTail(char *group, char *name, int qty){
	PantryIngredient *temp = createPantryIngredient(group, name, qty);
	if(PantryHead){
		PantryHead = PantryTail = temp;
	} else {
		PantryTail->next = temp;
		temp->prev = PantryTail;
		PantryTail = temp;
	}
}

void PantryIngredientPushMid(char *group, char *name, int qty){
	if(!PantryHead){
		PantryIngredient *temp = createPantryIngredient(group, name, qty);
		PantryHead = PantryTail = temp;
	} else if(strcmp(PantryHead->name, name) >= 0){
		PantryIngredientPushHead(group, name, qty);
		
	} else if(strcmp(PantryTail->name, name) <= 0){
		PantryIngredientPushTail(group, name, qty);
		
	} else {
		PantryIngredient *temp = createPantryIngredient(group, name, qty);
		
		struct PantryIngredient *curr = PantryHead;
		
		while(strcmp(curr->name, name) < 0){
			curr = curr->next;
		}
		
		temp->prev = curr->prev;
		temp->next = curr;
		curr->prev->next = temp;
		curr->prev = temp;
	}	
}

void PrintChar(int banyak, const char *karakter){
	for(int i = 0; i < banyak ;i++){
		printf("%s", karakter);
	}
}

void PrintNameAsc() {
	//Judul
	PrintChar(55, "=");
	puts("");
	printf("%*s", 32, "Ingredients");
	PrintChar(22, " ");
	printf("|\n");
	PrintChar(55, "=");
	puts("");
	printf("%*s", 10, "Group");
	printf("%*s", 19, "Name");
	printf("%*s", 22, "Quantity");
	PrintChar(3, " ");
	printf("|\n");
	PrintChar(55, "-");
	puts("");
	
	PantryIngredient *curr = PantryHead;

	while(curr) {
		
		//Print Group
		int flag = 0;
		int len = 15-strlen(curr->group); 
		if(len%2 == 1){
			len--;
			flag = 1;
		}
		len/=2;
		PrintChar(len, " ");
		
		printf("%s", curr->group);
		
		if(flag == 0){
			len--;
		}
		PrintChar(len, " ");
		printf("|");
		
		//Print Name
		flag = 0;
		len = 25 - strlen(curr->name);
		if(len%2 == 1){
			len--;
			flag = 1;
		}
		len/=2;
		PrintChar(len, " ");
		printf("%s", curr->name);
		if(flag == 0){
			len--;
		}
		PrintChar(len, " ");
		printf("|");
		
//		Print Quantity
		flag = 0;
		int qtyTemp = curr->qty;
		int ctr = 0;
		while(qtyTemp > 0){
			ctr++;
			qtyTemp /= 10;
		}
		
		len = 15 - ctr;
		if(len%2 == 1){
			flag = 1;
			len--;
		}
		len /= 2;
		PrintChar(len, " ");
		printf("%d", curr->qty);
		
		if(flag == 0){
			len--;
		}
		PrintChar(len, " ");
		printf("|\n");
		
		curr = curr->next;
	}
	PrintChar(55, "=");
	puts("");
}

void PrintNameDesc() {
	//Judul
	PrintChar(55, "=");
	puts("");
	printf("%*s", 32, "Ingredients");
	PrintChar(22, " ");
	printf("|\n");
	PrintChar(55, "=");
	puts("");
	printf("%*s", 10, "Group");
	printf("%*s", 19, "Name");
	printf("%*s", 22, "Quantity");
	PrintChar(3, " ");
	printf("|\n");
	PrintChar(55, "-");
	puts("");
	
	PantryIngredient *curr = PantryTail;

	while(curr) {
		
		//Print Group
		int flag = 0;
		int len = 15-strlen(curr->group); 
		if(len%2 == 1){
			len--;
			flag = 1;
		}
		len/=2;
		PrintChar(len, " ");
		
		printf("%s", curr->group);
		
		if(flag == 0){
			len--;
		}
		PrintChar(len, " ");
		printf("|");
		
		//Print Name
		flag = 0;
		len = 25 - strlen(curr->name);
		if(len%2 == 1){
			len--;
			flag = 1;
		}
		len/=2;
		PrintChar(len, " ");
		printf("%s", curr->name);
		if(flag == 0){
			len--;
		}
		PrintChar(len, " ");
		printf("|");
		
//		Print Quantity
		flag = 0;
		int qtyTemp = curr->qty;
		int ctr = 0;
		while(qtyTemp > 0){
			ctr++;
			qtyTemp /= 10;
		}
		
		len = 15 - ctr;
		if(len%2 == 1){
			flag = 1;
			len--;
		}
		len /= 2;
		PrintChar(len, " ");
		printf("%d", curr->qty);
		
		if(flag == 0){
			len--;
		}
		PrintChar(len, " ");
		printf("|\n");
		
		curr = curr->prev;
	}
	PrintChar(55, "=");
	puts("");
}


void AddPantryIngredient(){
	char NameTemp[255];
	char GroupTemp[255];
	int flag = 0;
	do{
		flag = 0;
		printf("Name (lowercase): ");
		scanf("%[^\n]", NameTemp); getchar();
		for(int i = 0; i < strlen(NameTemp); i++){
			if(NameTemp[i] < 'a' || NameTemp[i] > 'z' ){
				flag = 1;
				break;
			}
		}
		
	} while(flag);


	do{
		flag = 0;
		printf("Group [Beans/Dairy/Fruits/Meats/Spices/Vegetables/Others]");
		scanf("%s", GroupTemp); getchar();
		for(int i = 0 ; i < 8; i++){
			if(strcmp(GroupTemp, PantryIngredientGroup[i]) == 0){
				flag = 0;
				break;
			}
			else {
				flag = 1;
			}
		}
	} while(flag);
	
	int QtyTemp;
	printf("Quantity: ");
	scanf("%d", &QtyTemp);getchar();
	PantryIngredientPushMid(GroupTemp, NameTemp, QtyTemp);
}

void PrintGroupAsc(){
	//judul
	PrintChar(55, "=");
	puts("");
	printf("%*s", 32, "Ingredients");
	PrintChar(22, " ");
	printf("|\n");
	PrintChar(55, "=");
	puts("");
	printf("%*s", 10, "Group");
	printf("%*s", 19, "Name");
	printf("%*s", 22, "Quantity");
	PrintChar(3, " ");
	printf("|\n");
	PrintChar(55, "-");
	puts("");
	
	for (int i = 0; i < 8 ; i++){
		
		PantryIngredient *curr = PantryHead;

	while(curr) {
		if(strcmp(curr->group, PantryIngredientGroup[i]) != 0){
			curr = curr->next;
			continue;
		}
		
		//Print Group
		int flag = 0;
		int len = 15-strlen(curr->group); 
		if(len%2 == 1){
			len--;
			flag = 1;
		}
		len/=2;
		PrintChar(len, " ");
		
		printf("%s", curr->group);
		
		if(flag == 0){
			len--;
		}
		PrintChar(len, " ");
		printf("|");
		
		//Print Name
		flag = 0;
		len = 25 - strlen(curr->name);
		if(len%2 == 1){
			len--;
			flag = 1;
		}
		len/=2;
		PrintChar(len, " ");
		printf("%s", curr->name);
		if(flag == 0){
			len--;
		}
		PrintChar(len, " ");
		printf("|");
		
//		Print Quantity
		flag = 0;
		int qtyTemp = curr->qty;
		int ctr = 0;
		while(qtyTemp > 0){
			ctr++;
			qtyTemp /= 10;
		}
		
		len = 15 - ctr;
		if(len%2 == 1){
			flag = 1;
			len--;
		}
		len /= 2;
		PrintChar(len, " ");
		printf("%d", curr->qty);
		
		if(flag == 0){
			len--;
		}
		PrintChar(len, " ");
		printf("|\n");
		
		curr = curr->next;
	}
		
	}
	PrintChar(55, "=");	
	puts("");
}

void PrintGroupDesc(){
	//judul
	PrintChar(55, "=");
	puts("");
	printf("%*s", 32, "Ingredients");
	PrintChar(22, " ");
	printf("|\n");
	PrintChar(55, "=");
	puts("");
	printf("%*s", 10, "Group");
	printf("%*s", 19, "Name");
	printf("%*s", 22, "Quantity");
	PrintChar(3, " ");
	printf("|\n");
	PrintChar(55, "-");
	puts("");
	
	for (int i = 7; i >=0 ; i--){
		
		PantryIngredient *curr = PantryHead;

		while(curr) {
			if(strcmp(curr->group, PantryIngredientGroup[i]) != 0){
				curr = curr->next;
				continue;
			}
			
			//Print Group
			int flag = 0;
			int len = 15-strlen(curr->group); 
			if(len%2 == 1){
				len--;
				flag = 1;
			}
			len/=2;
			PrintChar(len, " ");
			
			printf("%s", curr->group);
			
			if(flag == 0){
				len--;
			}
			PrintChar(len, " ");
			printf("|");
			
			//Print Name
			flag = 0;
			len = 25 - strlen(curr->name);
			if(len%2 == 1){
				len--;
				flag = 1;
			}
			len/=2;
			PrintChar(len, " ");
			printf("%s", curr->name);
			if(flag == 0){
				len--;
			}
			PrintChar(len, " ");
			printf("|");
			
	//		Print Quantity
			flag = 0;
			int qtyTemp = curr->qty;
			int ctr = 0;
			while(qtyTemp > 0){
				ctr++;
				qtyTemp /= 10;
			}
			
			len = 15 - ctr;
			if(len%2 == 1){
				flag = 1;
				len--;
			}
			len /= 2;
			PrintChar(len, " ");
			printf("%d", curr->qty);
			
			if(flag == 0){
				len--;
			}
			PrintChar(len, " ");
			printf("|\n");
			
			curr = curr->next;
		}
		
	}
	PrintChar(55, "=");
	puts("");
}

int main(){
	AddPantryIngredient();
	AddPantryIngredient();
	AddPantryIngredient();
	PrintNameAsc();
//	PrintNameDesc();
//	PrintGroupAsc();
//	PrintGroupDesc();
	return 0;
}
