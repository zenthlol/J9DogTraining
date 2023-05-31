#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Dog{
	char name[100];
	char breed[100];
	char size[100];
	char day[100];
	char id[100];
	
	int height;
	int bf;
	Dog *left;
	Dog *right;
};

int id_counter = 1;

Dog *Create(char name[], char breed[], char size[], char day[], char id[]){
	Dog *newNode = (Dog*)malloc(sizeof(Dog));
	strcpy(newNode->name, name);
	strcpy(newNode->breed, breed);
	strcpy(newNode->size, size);
	strcpy(newNode->day, day);
	strcpy(newNode->id, id);
	
	//declaration
	newNode->height = 1;
	newNode->bf = 0;
	newNode->left = newNode->right = NULL;
	return newNode;
}

int getHeight(Dog *curr){
	if(curr == NULL){
		return 0;
	}
	return curr->height;
}

int max(int a, int b){
	if(a>b){
		return a;
	}
	return b;
}

int balanceFactor(Dog *curr){
	if(curr == NULL){
	return 0;
	}
	return getHeight(curr->right) - getHeight(curr->left);
}

Dog *leftRotate(Dog *curr){
	Dog *newCurr = curr->right;
	Dog *newChild = newCurr->left;
	
	newCurr->left = curr;
	curr->right = newChild;
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
	newCurr->height = max(getHeight(newCurr->left), getHeight(newCurr->right)) + 1;
	
	return newCurr;
}


Dog *rightRotate(Dog *curr){
	Dog *newCurr = curr->left;
	Dog *newChild = newCurr->right;
	
	newCurr->right = curr;
	curr->left = newChild;
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
	newCurr->height = max(getHeight(newCurr->left), getHeight(newCurr->right)) + 1;
	
	return newCurr;
}



Dog *rebalance(Dog *curr){
	if(curr == NULL){
		return NULL;
	}
	
	curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;
	
	int bf = balanceFactor(curr);
	
	//berat kanan
	if(bf > 1){
		// anak kanan berat kiri
		if(balanceFactor(curr->right)<0){
			curr->right = rightRotate(curr->right);
		}
		// left rotate
		return leftRotate(curr);
	}
	
	//jika berat kiri
	else if(bf < -1){
		// jika anak kiri bearat kanan
		if(balanceFactor(curr->left) > 0){
			curr->left = leftRotate(curr->left);
		}
		//right rotate
		return rightRotate(curr);
	}
	return curr;
}

Dog *insert(Dog *curr, Dog *newNode){
	if(curr == NULL){
		return newNode;
	}
	else if(strcmp(newNode->id, curr->id) < 0 ){
		curr->left = insert(curr->left, newNode);
	}
	
	else if(strcmp(newNode->id, curr->id) > 0){
		curr->right = insert(curr->right, newNode);
	}
	return rebalance(curr);
}

//untuk deletion searching

Dog *search(Dog *curr, char id[]){
	if(curr== NULL){
		return NULL;
	}
	
	else if(strcmp(id, curr->id) < 0){
		return search(curr->left, id);
	}
	
	else if(strcmp(id, curr->id) > 0){
		return search(curr->right, id);
	}
	return curr;
}


Dog *predecessor(Dog *curr){
	Dog *temp = curr->left;
	while(temp->right != NULL){
		temp = temp->right;
	}
	return temp;
}


Dog *deletion(Dog *curr, char id[]){
	if(curr == NULL){
		return NULL;
	}
	else if(strcmp(id, curr->id) < 0){
		curr->left = deletion(curr->left, id);
	}
	
	else if(strcmp(id, curr->id) > 0){
		curr->right = deletion(curr->right, id);
	}
	else{
		if(curr->left == NULL && curr->right == NULL){
			free(curr);
			return NULL;
		}
		
		else if(curr->left = NULL){
			Dog *temp = curr;
			curr = curr->right;
			free(temp);
			return curr;
		}
		
		else if(curr->right == NULL){
			Dog *temp = curr;
			curr = curr->left;
			free(temp);
			return curr;
		}
		else{
			Dog *temp = predecessor(curr);
			strcpy(curr->name, temp->name);
			strcpy(curr->breed, temp->breed);
			strcpy(curr->size, temp->size);
			strcpy(curr->day, temp->day);
			strcpy(curr->id, temp->id);
			
			curr->left = deletion(curr->left, temp->id);
		}
	}
	return rebalance(curr);
}

//prints

void inorder(Dog *curr){
	if(curr == NULL){
		return;
	}
	inorder(curr->left);
	printf("%s %s %s %s %s\n",curr->id, curr->name, curr->breed, curr->size, curr->day);
	inorder(curr->right);
}

void preorder(Dog *curr){
	if(curr == NULL){
		return;
	}
	printf("%s %s %s %s %s\n",curr->id, curr->name, curr->breed, curr->size, curr->day);
	preorder(curr->left);
	preorder(curr->right);
}

void postorder(Dog *curr){
	if(curr == NULL){
		return;
	}
	postorder(curr->left);
	postorder(curr->right);
	printf("%s %s %s %s %s\n",curr->id, curr->name, curr->breed, curr->size, curr->day);
}



// INPUT MENUS

Dog *menuInsert(Dog *curr){
	char dname[100];
	char dbreed[100];
	char dsize[100];
	char dday[100];
	char did[100];
	
	//input validations
	do{
		printf("Input Dog Name (5-15 chracters) : ");
		scanf("%[^\n]", dname); getchar();
	}while(strlen(dname) <5 || strlen(dname) > 15);
	
	do{
		printf("Input Dog Breed (3-25 characters) (only alphabets, spaces, all in CAPITAL): ");
		scanf("%[^\n]", dbreed); getchar();
	}while(strlen(dbreed) < 3 || strlen(dbreed) > 25); // kurang validasi only letters, and all capital
	
	do{
		printf("Input Dog Size (caseInsensitive)(Small || Medium || Large) : ");
		scanf("%[^\n]", dsize); getchar();
	} while(strcmp(dsize, "Small")!=0 && strcmp(dsize, "Medium")!=0 && strcmp(dsize, "Large")!=0 ); // kurang validasi insensitive
	
	do{
		printf("Input Training Day (caseSensitive)(MOn||Tue||Wed||Thu||Fri) : ");
		scanf("%[^\n]", dday); getchar();
	} while(strcmp(dday, "Mon")!=0 && strcmp(dday, "Tue")!=0 && strcmp(dday, "Wed")!=0 && strcmp(dday, "Thu")!=0 && strcmp(dday, "Fri")!=0);
	
	snprintf(did, sizeof(did), "%c%c%03d%c", toupper(dsize[0]), toupper(dsize[1]), id_counter++, toupper(dbreed[0])); // generate id belum benar
	printf("");
	Dog *newNode = Create(dname, dbreed, dsize, dday, did);
	curr = insert(curr, newNode);
	return curr;
}


Dog *removeMenu(Dog *curr){
	// no data
	if(curr == NULL){
		printf("There are no dogs to train yet!\n");
		return curr;
	}
	
	char id[100];
	// ask for input id for delete
	do{
		printf("Input dog ID to delete : ");
		scanf("%[^\n]", id); getchar();
	}while(search(curr, id) == NULL);
	
	curr = deletion(curr,id);
	printf("Dog with the ID %s removed!", id);
	return curr;
	
	
}



int main(){
	Dog *curr = NULL;
	
	int choice = 0;
	
	while(true){
		printf("THE J9 DOG TRAINING \n");
		printf("1. Add Dog To Train\n");
		printf("2. View All Dog\n");
		printf("3. Remove Dog\n");
		printf("4. Exit\n");
		printf("Choose >> ");
		scanf("%d", &choice); getchar();
		
		switch(choice){
			case 1:
				curr = menuInsert(curr);
				break;
			case 2:
				printf("Preorder : \n");
				preorder(curr);
				printf("\nInorder : \n");
				inorder(curr);
				printf("\nPostorder : \n");
				postorder(curr);
				break;
			case 3:
				curr = removeMenu(curr);
				break;
			case 4:
				break;
			
			default:
				printf("Choice invalid\n");
		}
	}
	
	
	return 0;
}
