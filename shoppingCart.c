#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
	int id;
	char name[20];
	int price;
	int qty;
};

struct Bill { //keeps the fields for calculating the bill
	int pid;
	char pname[20];
	int pprice;
	
};

char mygetch();

int getID();  //automaticall generates the id
int billFileNo();  //automatically generated

void manageProduct();
void purchaseProduct();
void generateBill();
void addProduct();
void displayAllProduct();

struct Product findProduct(int id);
void updateProduct(int id, int qty);

char fproduct[] = {"product.dat"};
char fbill[] ={"bill.dat"};
int total =0;

int main(){
	File *fp;
	int ch;
	system("clear"); 

	while (1) {

		system("clear");
		printf("=========================================================================\n\n");

		printf("\t\tWelcome Product Management System\n\n");

		printf("==========================================================================\n\n");

		printf("1. Manage Product\n\n");
		printf("2. Purchase Product\n\n");

		printf("3.  Generate Bill\n\n");
		printf("0. Exit\n\n");

		printf("==========================================================================\n");

		printf("\nPlease enter your Choice\n");
		scanf("%d", &ch);

		switch(ch){

			case 1: manageProduct();
					break;

			case 2: purchaseProduct();
					break;

			case 3: generateBill();
					break;

			case 0: exit(0);


		}

		mygetch();


	}

	return 0;

}


int getID(){
	
	File *fp;  //file pointer
	int value =0;
	fp = fopen("prodid.txt", "r");

	if(fp ==NULL){
		fp = fopen("prodid.txt", "w");
		fprintf(fp, "%d\n",0 );
		fclose(fp);
		fp=fopen("prodid.txt", "r");
	}

	fscanf(fp, "%d", &value);
	fclose(fp);

	fp =fopen("prodid.txt", "w");
	fprintf(fp, "%d\n", value+1 );  //increments the value of the prodid
	fclose(fp);

	return value + 1;

}

void manageProduct() {
	int ch;
	int back;

	while(1) {
		System("clear");

		printf("=============================================================\n\n");

		printf("\t\t Welcome Product Management System\n\n");

		printf("==============================================================\n\n");

		printf("1. Add New Product\n\n");
		printf("2.Display all Products\n\n");
		printf("0. Back\n\n");
		printf("===============================================================\n\n");

		printf("\nPlease enter your Choice\n");
		scanf("%d", &ch);

		switch(ch) {

			case 1: addProduct();
			        break;

			case 2: displayAllProduct();
			        break;

			case 0: back =1;
			        break;

		}

		if (back == 1){
			break;
		} else {
			mygetch();

		}

	}
}

void addProduct() {

	FILE *fp;
	struct Product t1;
	fp = fopen(fproduct, "ab");

	t1.id = getID();

	printf("\nEnter product name: \n");
	scanf("%s", t1.name);
	printf("\nEnter product price: \n");
	scanf("%d", &t1.price);
	printf("\nEnter product quantity: " );
	scanf("%d", &t1.qty);

	fwrite(&t1, sizeof(t1), 1, fp);

	fclose(fp);

}

void displayAllProduct(){

	FILE *fp;
	struct Product t; 
	int id, found = 0;

	system("clear");

	fp = fopen(fproduct, "rb");

	printf("\n=====================================================================\n\n");
	printf("\t\t Product Details \n\n");
	printf("========================================================================\n\n");

	printf("ID\tName\tQty.\tPrice\n\n");

	while(1) {
		frad(&t, sizeof(t), 1, fp);

		if(feof(fp)){
			break;
		}

		printf("%d\t", t.id );
		printf("%s\t", t.name );

		printf("%d\t", t.qty);
		printf("%d\t\t\n", t.price);
	}

	printf("==========================================================================\n\n");
	fclose(fp);

}

void purchaseProduct(){
	char ch1, ch2;

	int id;
	System("clear");
	printf("===========================================================================\n\n");

	printf("\t\t Welcome Product Management System\n\n");

	printf("===========================================================================\n\n");


	while (1) {
		displayAllProduct();  //displays all the product

		__fpurge(stdin); //displays all the products  //fflsush (stdin)

		printf("\n\n\nDo you want to purchase [Y/N]: ");
		scanf("%c", &ch1);

		if(ch1 =='Y'){
			FILE *fp;

			struct Bill t1;
			struct Product t2;
			

			fp = fopen(fbill, "ab");
			printf("\n\nEnter the Product ID to Purchase: ");
			scanf ("%d", &id);

			t2 = findProduct(id);

			t1.pid = t2.id;

			strcpy(t1.pname, t2.name);  //copies to the Bill method
			t1.pprice = t2.price;

			fwrite(&t1, sizeof(t1), 1, fp);

			fclose(fp);
		}
		__fpurge(stdin); //fflush (stdin)
		printf("\n\n\nDo you want to continue [Y/N]: ");
		scanf("%c", &ch2);

		if(ch2 =='N'){
			break;
		}

		mygetch();

	}
}


struct Product findProduct (int id){

	FILE *fp;

	struct Product t;
	fp = open(fproduct, "rb");

	while(1) {

		fread (&t, sizeof(t), 1, fp);

		if(feof(fp)){
			break;

		}

		if(t.id ==id){
			updateProduct(id, t.qty -1);  //
			break;
		}
	}
	fclose(fp);
	return t;

}

void updateProduct(int id, int qty) {

	FILE *fp, *fp1; 

	struct Product t, t1;
	int found =0;

	fp = fopen(fproduct, "rb");
	fp1 = fopen ("tem.dat", "wb");

	while(1) {
		fread (&t, sizeof(t), 1, fp);
		if(feof(fp)){
			break;
		}

		if(t.id == id){
			found = 1;
			t.qty = qty;
			fwrite(&t, sizeof(t), 1, fp1);
		}
		else {
			fwrite(&t, sizeof(t), 1, fp1);
		}
	}
	fclose(fp);
	fclose(fp1);


	if(found ==0){
		printf("Sorry No Record Found\n\n");

	}
	else {
		fp = fopen (fproduct, "wb");
		fp1 =fopen("temp.dat", "rb");

		while (1) {
			fread (&t, sizeof(t), 1, fp1);

			if(feof(fp1)){
				break;
			}
			fwrite(&t, sizeof(t), 1, fp);
		}

	}

	fclose(fp);
	fclose(fp1);

}



void generateBill(){

	FILE *fp, *fp1; 
	struct Bill t;
	int id, found =0;

	char ch1;
	int brel =0;
	char billname [20];

	system("clear");

	fp= fopen(fbill, "rb");

	printf("\n=======================================================\n\n");
	printf("\t\t Bill Details\n\n");
	printf("=========================================================\n\n");

	printf("Pro-ID\tPro-Name\tPro-Price\n\n");


	while(1) {
		fread(&t, sizeof(t), 1, fp);

			if(feof(fp)){
				break;
			}

			printf("%d\t\n", t.pid);
			printf("%s\t", t.pname);
			printf("%d\t\t\t\n", t.pprice);
			total =total + t.pprice;
	}

	printf("\n\n=============================>>>>Total Bill Amount [Rs. :%d ]\n\n", total);
	fclose(fp);

	if(total !=0) {
		 __fpurge(stdin);//fflush(stdin);
		printf("\n\n\nDo you want to generate Final Bill [Y/N]: ");
		scanf("%c", ch1);

		if(ch1 =='Y') {
			brel = billFileNo();
			sprintf(billname, "%s%d","", brel);
			strcat(billname, ".dat");

			fp =fopen (fbill, "rb");
			fp1 = fopen(billname, "wb");

			while(1) {
				fread (&t, sizeof(t), 1, fp);

				if(feof(fp)){
					break;
				}
				fwrite(&t, sizeof(t), 1, fp1);
			}

			fclose(fp);
			fclose(fp1);

			fp =fopen(fbill, "wb");
			fclose(fp);
			total= 0;
		}
	}
	else {
		printf("\n\n Sorry item selected \n\n");
	}


}

int billFileNo() {

	FILE *fp;
	int value = 0;
	fp =  fopen ("billno.txt", "r");

	if(fp ==NULL) {
		fp = fopen ("billno.txt", "w");
		fprintf(fp, "%d", 0);
		fclose(fp);
		fp=fopen("billno.txt", "r");
	}

	fscanf(fp, "%d", &value);
	fclose(fp);

	fp = fopen("billno.txt", "w");
	fprintf(fp, "%d", value + 1 );

	fclose(fp);

	return value +1;
}

