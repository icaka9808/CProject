#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef struct Graveyard
{

	char name[50];
	int row;
	int line;
	int dayOfDeath;
	int monthOfDeath;
	int yearOfDeath;
	int reservedFor;
}Graveyard;
typedef struct Node
{
    Graveyard graveyard;
	struct Node *next;
}t_Node;
t_Node *AddGrave(t_Node *head);
t_Node *GetInfo();
void ClearScreen();
void GetNewGrave(Graveyard *newGrave);
void calculateDays(t_Node *new_node);
void showAll(t_Node *new_node);
void Add();
int main()
{
	Add();
	int choice;
	t_Node *head = head = GetInfo();

	while (1)
	{
		printf("1.Add new grave.\r\n2.Calculate days.\r\n3.Show all graves.\r\n4.Exit.\r\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		if (choice == 1)
		{
			head = AddGrave(head);
		}
		else if (choice == 2)
		{
			calculateDays(head);
		}
		else if (choice == 3)
		{
			showAll(head);
		}
		else
		{
			return 0;
		}
		ClearScreen();
	}
}

void ClearScreen()
{
	system("pause");
	system("cls");
}


void GetNewGrave(Graveyard *newGrave)
{
	printf("Enter data for the grave:\r\n\r\n");
	printf("Enter grave owner: ");
	scanf(" %[^\n]%*c", newGrave->name, 50);

	printf("Enter grave row: ");
	scanf("%d", &newGrave->row);

	printf("Enter grave line: ");
	scanf("%d", &newGrave->line);

	printf("Enter day of death: ");
	scanf("%d", &newGrave->dayOfDeath);

	printf("Enter month of death: ");
	scanf("%d", &newGrave->monthOfDeath);

	printf("Enter year death: ");
	scanf("%d", &newGrave->yearOfDeath);

	printf("Enter years that the grave is reserved: ");
	scanf("%d", &newGrave->reservedFor);


}
t_Node *AddGrave(t_Node *head)
{
	t_Node *current = head;
	Graveyard grave;

	GetNewGrave(&grave);

	while (current->next != NULL)
	{
		current = current->next;
	}

	current->next = (t_Node*)malloc(sizeof(t_Node));
	current->next->graveyard = grave;
	current->next->next = NULL;

	FILE *fp = fopen("File.bin", "ab");

	if (fwrite(&grave, sizeof(Graveyard), 1, fp) != 1)
		printf("Error in file writing.\r\n");

	fclose(fp);

	return head;
}
t_Node *GetInfo()
{
	FILE *fp = fopen("File.bin", "rb");

	t_Node *head = (t_Node*)malloc(sizeof(t_Node));
	t_Node *current = head;
	t_Node *prev = head;

	Graveyard grave;

	while (fread(&grave, sizeof(Graveyard), 1, fp))
	{
		current->graveyard = grave;
		current->next = (t_Node*)malloc(sizeof(t_Node));
		prev = current;
		current = current->next;

	}

	prev->next = NULL;

	fclose(fp);

	return head;
}
void calculateDays(t_Node *new_node)
{
	printf("Insert current day:");
	int day;
	scanf("%d", &day);
	printf("Insert current month:");
	int month;
	scanf("%d", &month);
	printf("Insert current year:");
	int year;
	scanf("%d", &year);

	while (new_node != NULL)
	{
		if ((30 - new_node->graveyard.dayOfDeath + day == 40)
        && (month - new_node->graveyard.monthOfDeath <= 2)
        && year == new_node->graveyard.yearOfDeath)
		{
			printf("%s has made 40 days", new_node->graveyard.name);
		}
		else if ((day == new_node->graveyard.dayOfDeath
                && 12 - new_node->graveyard.monthOfDeath + month == 6
                && year - new_node->graveyard.yearOfDeath <= 2)
                || (day == new_node->graveyard.dayOfDeath
                && month - new_node->graveyard.monthOfDeath == 6
                && year == new_node->graveyard.yearOfDeath))
		{
			printf("%s has made 6 months", new_node->graveyard.name);
		}
		else if (day == new_node->graveyard.dayOfDeath&&month == new_node->graveyard.monthOfDeath&&year - new_node->graveyard.yearOfDeath == 1)
		{
			printf("%s has made 1 year", new_node->graveyard.name);
		}
		new_node = new_node->next;
	}

}
void showAll(t_Node *new_node)
{


	while (new_node != NULL)
	{
		printf("%s  ", new_node->graveyard.name);
		printf("%d  ", new_node->graveyard.row);
		printf("%d  ", new_node->graveyard.line);
		printf("%d  ", new_node->graveyard.dayOfDeath);
		printf("%d  ", new_node->graveyard.monthOfDeath);
		printf("%d  ", new_node->graveyard.yearOfDeath);
		printf("%d  \r\n", new_node->graveyard.reservedFor);
		new_node = new_node->next;
	}

}
void Add()
{
	FILE *fp = fopen("File.bin", "wb");

	t_Node *head = (t_Node*)malloc(sizeof(t_Node));
	t_Node *new_node = head;

	Graveyard grave1 = { "ivan  ", 1,1,5,3,2014,20 };
	Graveyard grave2 = { "georgi", 1,6,5,5,2000,20 };
	Graveyard grave3 = { "cvetan", 1,1,7,3,2018,20 };
	Graveyard grave4 = { "ivan  ", 1,1,7,4,1999,20 };
	Graveyard grave5 = { "boris ", 1,1,8,8,2008,20 };

	new_node->graveyard = grave4;
	new_node->next = (t_Node*)malloc(sizeof(t_Node));
	new_node = new_node->next;

	new_node->graveyard = grave3;
	new_node->next = (t_Node*)malloc(sizeof(t_Node));
	new_node = new_node->next;

	new_node->graveyard = grave1;
	new_node->next = (t_Node*)malloc(sizeof(t_Node));
	new_node = new_node->next;

	new_node->graveyard = grave2;
	new_node->next = (t_Node*)malloc(sizeof(t_Node));
	new_node = new_node->next;

	new_node->graveyard = grave5;
	new_node->next = NULL;

	new_node = head;

	while (new_node != NULL)
	{
		fwrite(&(new_node->graveyard), sizeof(Graveyard), 1, fp);

		new_node = new_node->next;
	}

	fclose(fp);
}
