
// Taleed Hamadneh || #1220006 || Section 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TownNode
{
    char town_name[50];
    struct TownNode *next_town;
    struct TownNode *prev_town;
    struct DistrictNode *prev_district;
    int population;
};

struct DistrictNode
{
    char district_name[50];
    struct TownNode *next_town;
    struct TownNode *tail;  //refer to the last town in each district
};

void Rfile(struct DistrictNode *d[20]); // max number of district in ps =16
struct DistrictNode *MakeDEmpty(struct DistrictNode *L); ///create district
struct TownNode *NewTown(int popul, char TownName[50]); //create town
struct DistrictNode *FindDistrict(struct DistrictNode *d[20], char names[50]);
void menu();
void PrintBeforeSorting(struct DistrictNode *d[20]);
int NumOfDistricts(struct DistrictNode *d[20]);
int NumOfTowns(struct DistrictNode *L);
void SortTowns(struct DistrictNode *d[20]); //radix sort for populations
void InsertDistrict(struct DistrictNode *d[20], char name[50]); //insert district with this name
void InsertTown(struct DistrictNode *d[20], char town[50], char district[50], int popul); //insert town with name,popul,district name
void DeleteTown(struct DistrictNode *d[20], char town[50], char district[50]); // Delete town with this name
struct TownNode *FindTown(struct DistrictNode *d[20], char town[50], char district[50]);
void DeleteList(struct DistrictNode *L); // delete a district linked list 
void DeleteDistrict(struct DistrictNode *d[20], char district[50]); //delete district with this name
void changepopulation(struct DistrictNode *d[20], char district[50], char town[50], int popul);
int DistrictPopulation(struct DistrictNode *d);
int TotalPopulation(struct DistrictNode *d[20]); //of Palestine
void PrintDistrictsPopulation(struct DistrictNode *d[20]);
int MaxTownPop(struct DistrictNode *d[20]);
int MinTownPop(struct DistrictNode *d[20]);
void DeleteTownNode(struct TownNode *p); // Delete town with this position
void RadixSort(struct DistrictNode *d[20]); //sort the districts
int MaxSize(struct DistrictNode *d[20]); //max length size of district names
void Insertnode(char str[50], struct DistrictNode *L, struct TownNode *p); //insert node (special for districts radix sort)
struct TownNode *FindLastNodeRadix(struct DistrictNode *L); //used for insert last
void printAfterSorting(struct DistrictNode *d[20]);
void Wfile(struct DistrictNode *d[20]); //write the ouput in the file
void Insertnode2(int popul, char name[50], struct DistrictNode *L, struct TownNode *p); //insert node (special for population radix sort)
struct DistrictNode *RadixNumbers(struct DistrictNode *d); //used for sorting towns
int maxTowninD(struct DistrictNode *d);
int NumofTownsInPs(struct DistrictNode *d[20]);
void Makecopy(struct DistrictNode *d[20], struct DistrictNode *copy[20]); //to copy the loaded informations

int main()
{
    int isRead = 0; //to know if the file was read or not
    int TisSorted = 0; //to know if the towns were sorted or not
    int DisSorted = 0; // to know if the districts were sorted or not

    struct DistrictNode *Districts[20];
    struct DistrictNode *copy[20];
    char town[50];
    char district[50];
    int popul;
    menu();
    int t = 0;
    scanf("%d", &t);
    while (t != 14)
    {
        if (t > 0 && t < 15)
        {
            switch (t)
            {
            case 1:
                if (isRead == 1)
                {
                    printf("You have already loaded it !!!\n\n");
                }

                else
                {
                    Rfile(Districts);
                    Makecopy(Districts, copy);
                    printf("File has been loaded successfully\n\n");
                    isRead = 1;
                }
                break;
            case 2:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else
                {
                    PrintBeforeSorting(copy);
                }
                break;
            case 3:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else
                {
                    RadixSort(Districts);
                    DisSorted = 1;
                    printf("Districts have been sorted successfully\n\n");
                }
                break;
            case 4:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else
                {
                    SortTowns(Districts);
                    TisSorted = 1;
                    printf("Towns have been sorted successfully\n\n");
                }
                break;
            case 5:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (TisSorted == 0)
                {
                    printf("Towns are not sorted!! Sort them first\n\n");
                }
                else if (DisSorted == 0)
                {
                    printf("Districts are not sorted!! Sort them first\n\n");
                }
                else
                {
                    printAfterSorting(Districts);
                }
                break;
            case 6:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (TisSorted == 0)
                {
                    printf("Towns are not sorted!! Sort them first\n\n");
                }
                else if (DisSorted == 0)
                {
                    printf("Districts are not sorted!! Sort them first\n\n");
                }
                else
                {
                    printf("Please enter the district name\n");
                    gets(district);
                    if (FindDistrict(Districts, district) != NULL)
                    {
                        printf("This District is already inserted!!\n\n");
                    }
                    else
                    {
                        InsertDistrict(Districts, district);
                        RadixSort(Districts);
                        printf("District has been added successfully\n\n");
                    }
                }
                break;
            case 7:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else
                {
                    printf("Please enter the Town name\n");
                    gets(town);
                    printf("Please enter the District name\n");
                    gets(district);
                    printf("Enter the town's Population\n");
                    scanf("%d", &popul);
                    getchar();
                    if (FindDistrict(Districts, district) == NULL)
                    {
                        printf("Couldn't add the town because this District is not inserted yet\n\n");
                    }
                    else if (FindTown(Districts, town, district) != NULL)
                    {
                        printf("Sorry.. This town is already inserted\n\n");
                    }

                    else
                    {
                        InsertTown(Districts, town, district, popul);
                        SortTowns(Districts);
                        printf("Town has been added successfully\n\n");
                    }
                }
                break;
            case 8:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }

                else
                {
                    printf("Please enter the town's name you want to delete\n");
                    gets(town);
                    printf("Please enter the District name\n");
                    gets(district);

                    if (FindDistrict(Districts, district) == NULL)
                    {
                        printf("This district is not inserted yet\n\n");
                    }
                    else if (FindTown(Districts, town, district) == NULL)
                    {
                        printf("This town is not inserted yet!\n\n");
                    }
                    else
                    {
                        DeleteTown(Districts, town, district);
                        printf("Town has been deleted successfully\n\n");
                    }
                }

                break;
            case 9:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }

                else
                {
                    printf("Please enter the district's name you want to delete..\n");
                    gets(district);
                    if (FindDistrict(Districts, district) != NULL)
                    {
                        DeleteDistrict(Districts, district);
                        printf("District has been deleted successfully\n\n");
                    }
                    else
                    {
                        printf("This district is not inserted yet\n\n");
                    }
                }
                break;
            case 10:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else
                {
                    printf("Total population of Palestine= %d\n\n", TotalPopulation(Districts));
                    printf("%d\n", MaxTownPop(Districts));
                    printf("%d\n\n", MinTownPop(Districts));
                }
                break;
            case 11:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (TisSorted == 0)
                {
                    printf("Towns are not sorted!! Sort them first\n\n");
                }
                else if (DisSorted == 0)
                {
                    printf("Districts are not sorted!! Sort them first\n\n");
                }
                else
                {
                    PrintDistrictsPopulation(Districts);
                }
                break;
            case 12:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else
                {
                    printf("Please enter the town you want to change\n");
                    gets(town);
                    printf("Please enter the district name \n");
                    gets(district);
                    printf("Please enter the new population\n");
                    scanf("%d", &popul);
                    getchar();
                    if (FindDistrict(Districts, district) == NULL)
                    {
                        printf("Sorry..The District of this town is not inserted yet\n\n");
                    }

                    else if (FindTown(Districts, town, district) == NULL)
                    {
                        printf("Sorry...This town is not inserted yet\n\n");
                    }
                    else if (popul < 0)
                    {
                        printf("Population cant be negative !! try again\n\n");
                    }
                    else
                    {
                        changepopulation(Districts, district, town, popul);
                        SortTowns(Districts);
                        printf("Population has been changed successfully\n\n");
                    }
                }
                break;
            case 13:
                if (isRead == 0)
                {
                    printf("File is not uploaded !! please load it first\n\n");
                }
                else if (TisSorted == 0)
                {
                    printf("Towns are not sorted!! Sort them first\n\n");
                }
                else if (DisSorted == 0)
                {
                    printf("Districts are not sorted!! Sort them first\n\n");
                }
                else
                {
                    Wfile(Districts);
                    printf("Output has been saved Successfully\n\n");
                }
                break;
            default:
                break;
            }

            menu();
            scanf("%d", &t);
            getchar();
        }
        else
        {
            printf("!!! Please enter number between 1 and 14 !!!\n\n");
            menu();
            scanf("%d", &t);
            getchar();
        }
    }
    printf("Bye Bye");
    Wfile(Districts); // auto save to the last edit the user has done..
    for (int i = 0; i < 20; i++) // Free The memory after exiting..
    { 
        DeleteList(Districts[i]);
    }

    for(int i=0;i<20;i++) { //free the copy memory
        DeleteList(copy[i]);
    }
}

struct TownNode *NewTown(int popul, char TownName[50]) //create a town with specific name and population
{
    struct TownNode *p = NULL;
    p = (struct TownNode *)malloc(sizeof(struct TownNode));
    if (p != NULL)
    {
        p->next_town = NULL;
        p->prev_town = NULL;
        p->population = popul;
        strcpy(p->town_name, TownName);
    }
    return p;
}

void Rfile(struct DistrictNode *d[20]) //reading the input file and storing the information in the array of linked lists
{
    for (int i = 0; i < 20; i++) //creating the array
    {
        d[i] = MakeDEmpty(d[i]);
    }
    for (int i = 0; i < 20; i++) //initial names for the districts
    {
        strcpy(d[i]->district_name, "\0");
    }
    char test[150];
    char district[50];
    char town[50];
    char popul[50];
    struct TownNode *p = NULL;
    FILE *myfile;
    myfile = fopen("districts.txt", "r");
    int i = 0;
    while (fgets(test, sizeof(test), myfile) != NULL)
    {
        char *token = strtok(test, "|");
        if (token != NULL)
        {
            strcpy(district, token);
            token = strtok(NULL, "|");
            if (token != NULL)
            {
                strcpy(town, token);
                token = strtok(NULL, "|");
                if (token != NULL)
                {
                    strcpy(popul, token);
                }
            }
        }

        if (FindDistrict(d, district) == NULL) // avoid repetition in district
        {
            strcpy(d[i]->district_name, district);
            d[i]->next_town = (NewTown(atoi(popul), town)); 
            d[i]->tail = d[i]->next_town;
            d[i]->next_town->prev_district = d[i];
            p = d[i]->next_town;
            i++;
        }
        else        // it enter the else when it reads the same district more than one
        {
            p->next_town = (NewTown(atoi(popul), town));
            p->next_town->prev_town = p;
            p = p->next_town;
            d[i - 1]->tail = p;
            p->next_town = NULL;
            p->prev_district = NULL;
        }
    }
    fclose(myfile);
}

struct DistrictNode *FindDistrict(struct DistrictNode *d[20], char names[50])
{
    for (int i = 0; i < 20; i++)
    {
        if (strcmp(d[i]->district_name, names) == 0)
        {
            return d[i];
        }
    }
    return NULL;
}

void Makecopy(struct DistrictNode *d[20], struct DistrictNode *copy[20]) //making copy to save the loaded informations
{

    for (int i = 0; i < 20; i++)
    {
        copy[i] = NULL;
        copy[i] = MakeDEmpty(copy[i]);
    }
    for (int i = 0; i < 20; i++)
    {
        struct TownNode *p = d[i]->next_town;
        strcpy(copy[i]->district_name, d[i]->district_name);
        while (p != NULL)
        {
            InsertTown(copy, p->town_name, copy[i]->district_name, p->population);
            p = p->next_town;
        }
    }
}

void PrintBeforeSorting(struct DistrictNode *c[20]) //printing the loaded information as in the input file
{
    int s = NumOfDistricts(c);
    struct TownNode *p = NULL;
    for (int i = 0; i < s; i++)
    {
        p = c[i]->next_town;
        while (p != NULL)
        {
            printf("%s", c[i]->district_name);
            printf("|%s", p->town_name);
            printf("|%d\n", p->population);
            p = p->next_town;
        }
    }
    printf("\n");
}

void menu()
{

    printf("Please choose one \n");
    printf("1. Load the input file (Palestinian districts and their town with population)\n");
    printf("2. Print the loaded information before sorting.\n");
    printf("3. Sort the districts alphabetically using Radix sort.\n");
    printf("4. Sort the towns for each district based on population in ascending order.\n");
    printf("5. Print the sorted information.\n");
    printf("6. Add a new district to the list of sorted districts (and sort the list)\n");
    printf("7. Add a new town to a certain district.\n");
    printf("8. Delete a town from a specific district.\n");
    printf("9. Delete a complete district.\n");
    printf("10. Calculate the population of Palestine, the max and min town population.\n");
    printf("11. Print the districts and their total population (without towns details).\n");
    printf("12. Change the population of a town.\n");
    printf("13. Save to output file.\n");
    printf("14. Exit.\n");
}

int NumOfDistricts(struct DistrictNode *d[20])
{
    for (int i = 0; i < 20; i++)
    {
        if (strlen(d[i]->district_name) == 0)
        {
            return i;
        }
    }
    return 20;
}

int NumOfTowns(struct DistrictNode *L) //num of towns in a specific district
{
    int count = 0;
    struct TownNode *p = NULL;
    p = L->next_town;
    while (p != NULL)
    {
        count++;
        p = p->next_town;
    }

    return count;
}

void InsertDistrict(struct DistrictNode *d[20], char name[50]) //insert district with specific name 
{
    if (FindDistrict(d, name) != NULL)
    {
        return;
    }
    else
    {
        int size = NumOfDistricts(d);
        strcpy(d[size]->district_name, name);
        d[size]->next_town = NULL;
    }
}

void InsertTown(struct DistrictNode *d[20], char town[50], char district[50], int popul)
{
    struct TownNode *p = NULL;
    int s = NumOfDistricts(d);
    if (FindTown(d, town, district) != NULL)
    {
        return;
    }

    else
    {
        for (int i = 0; i < s; i++)
        {
            if (strcmp(d[i]->district_name, district) == 0)
            {
                Insertnode(town, d[i], FindLastNodeRadix(d[i]));
                FindLastNodeRadix(d[i])->population = popul;
            }
        }
    }
}

void DeleteTown(struct DistrictNode *d[20], char town[50], char district[50])//delete a specific town from a specific district
{

    struct TownNode *p = NULL;
    p = FindTown(d, town, district);
    if (p != NULL)
    {
        if (p->prev_district == NULL) // Not the first town
        {
            if (p->next_town != NULL) // not the last town (in the middle)
            {
                p->next_town->prev_town = p->prev_town;
                p->prev_town->next_town = p->next_town;
                p->next_town = NULL;
                p->prev_town = NULL;
                free(p);
            }

            else // the last town
            {
                p->prev_town->next_town = NULL;
                free(p);
            }
        }

        else // The first town
        {
            if (p->next_town != NULL) // Not the last town 
            {
                p->next_town->prev_district = p->prev_district;
                p->prev_district->next_town = p->next_town;
                p->next_town = NULL;
                p->prev_town = NULL;
                free(p);
            }

            else
            { // the last town (last and first = the only town)
                p->prev_district->next_town = NULL;
                free(p);
            }
        }
    }
}

struct TownNode *FindTown(struct DistrictNode *d[20], char town[50], char district[50])
{ //n/2 time search using two pointers (head and tail)
    struct TownNode *head = NULL;
    struct TownNode *tail = NULL;
    int s = NumOfDistricts(d);
    for (int i = 0; i < s; i++)
    {
        if (strcmp(d[i]->district_name, district) == 0)
        {
            head = d[i]->next_town;
            tail = d[i]->tail;
            while (tail != NULL && head != NULL && strcmp(head->town_name, town) != 0 && strcmp(tail->town_name, town) != 0 && head != tail && tail->next_town != head)
            {
                head = head->next_town;
                tail = tail->prev_town;
            }
            if (head != NULL && strcmp(head->town_name, town) == 0)
            {
                return head;
            }

            else if (tail != NULL && strcmp(tail->town_name, town) == 0)
            {
                return tail;
            }

            return NULL; //reducing time
        }
    }
    return NULL;
}

struct DistrictNode *MakeDEmpty(struct DistrictNode *L) //creating district
{

    L = (struct DistrictNode *)malloc(sizeof(struct DistrictNode));
    if (L == NULL)
        printf("Out of memory");

    else
    {
        strcpy(L->district_name, "\0");
        L->next_town = NULL;
    }
    return L;
}

void DeleteDistrict(struct DistrictNode *d[20], char district[50]) //delete a specific district with its towns
{
    int index = 0; // to know the place of tthe deleted one
    int s = NumOfDistricts(d);
    int size = s - 1;
    for (int i = 0; i < s; i++)
    {
        if (strcmp(d[i]->district_name, district) == 0)
        {
            index = i;
            DeleteList(d[i]);
        }
    }

    for (int i = index; i < s; i++) //shifting the districts after deleting one
    {
        d[i] = d[i + 1];
    }

    d[size] = MakeDEmpty(d[size]); // empty the last district after deletion
}

void SortTowns(struct DistrictNode *d[20]) //sorting towns based on populations using radix sort
{
    struct DistrictNode *p = NULL;
    for (int i = 0; i < 20; i++)
    {
        p = RadixNumbers(d[i]);
        d[i] = p;
    }
}

void DeleteList(struct DistrictNode *L) //delete the whole linked list (district) with its head
{

    struct TownNode *p = NULL;
    p = L->next_town;
    struct TownNode *temp = NULL;
    free(L);

    while (p != NULL)
    {

        temp = p->next_town;
        DeleteTownNode(p);
        p = temp;
    }
}

void changepopulation(struct DistrictNode *d[20], char district[50], char town[50], int popul)
{
    struct TownNode *p = NULL;
    p = FindTown(d, town, district);
    if (p != NULL)
    {
        p->population = popul;
    }
}

int TotalPopulation(struct DistrictNode *d[20]) //of Palestine
{
    int popul = 0;
    struct TownNode *p = NULL;
    int s = NumOfDistricts(d);
    for (int i = 0; i < s; i++)
    {
        popul += DistrictPopulation(d[i]);
    }
    return popul;
}

int DistrictPopulation(struct DistrictNode *d) //population for Specific district
{
    struct TownNode *p = NULL;
    int popul = 0;
    p = d->next_town;
    while (p != NULL)
    {
        popul += p->population;
        p = p->next_town;
    }
    return popul;
}

void PrintDistrictsPopulation(struct DistrictNode *d[20])
{
    int s = NumOfDistricts(d);
    if (s == 0)
    {
        printf("There are no Districts !!\n\n");
    }
    else
    {
        for (int i = 0; i < s; i++)
        {
            printf("%s = ", d[i]->district_name);
            printf("%d\n", DistrictPopulation(d[i]));
        }
        printf("\n");
    }
}

int MaxTownPop(struct DistrictNode *d[20])
{
    int max = 0;
    int s = NumOfDistricts(d);
    int z = NumofTownsInPs(d);
    if (z == 0)
    {
        printf("There are no Towns in your list, max=");
        return 0;
    }

    else
    {
        struct TownNode *p = NULL;
        struct TownNode *n = NULL;
        for (int i = 0; i < s; i++)
        {
            p = d[i]->next_town;
            while (p != NULL)
            {
                if (p->population > max)
                {
                    max = p->population;
                    n = p;
                }
                p = p->next_town;
            }
        }
        printf("Max town population is %s =", n->town_name);
        return max;
    }
}

int MinTownPop(struct DistrictNode *d[20])
{
    int min = 1000000; // initial value
    struct TownNode *p = NULL;
    struct TownNode *n = NULL;
    int s = NumOfDistricts(d);
    int z = NumofTownsInPs(d);
    if (z == 0)
    {
        printf("There are no Towns in your list, min=");
        return 0;
    }
    else
    {
        for (int i = 0; i < s; i++)
        {
            p = d[i]->next_town;
            while (p != NULL)
            {
                if (p->population < min)
                {
                    min = p->population;
                    n = p;
                }
                p = p->next_town;
            }
        }
        printf("Min town population is %s =", n->town_name);
        return min;
    }
}

void DeleteTownNode(struct TownNode *p) //delete a node in specific position
{
    if (p != NULL)
    {
        if (p->prev_district == NULL) // Not the first town
        {
            if (p->next_town != NULL) // not the last town
            {
                p->next_town->prev_town = p->prev_town;
                p->prev_town->next_town = p->next_town;
                p->next_town = NULL;
                p->prev_town = NULL;
                free(p);
            }

            else // the last town
            {
                p->prev_town->next_town = NULL;
                free(p);
            }
        }

        else // The first town
        {
            if (p->next_town != NULL) // Not the last town
            {
                p->next_town->prev_district = p->prev_district;
                p->prev_district->next_town = p->next_town;
                p->next_town = NULL;
                p->prev_town = NULL;
                free(p);
            }

            else
            { // the last town
                p->prev_district->next_town = NULL;
                free(p);
            }
        }
    }
}

int MaxSize(struct DistrictNode *d[20]) //max length of districts names
{
    int max = 0;
    if (d[0] != NULL)
    {
        max = strlen(d[0]->district_name);
    }
    for (int i = 1; i < 20; i++)
    {
        if (strlen(d[i]->district_name) > max)
        {
            max = strlen(d[i]->district_name);
        }
    }

    return max;
}
void Insertnode(char str[50], struct DistrictNode *L, struct TownNode *p) //insert node in radix sort for districts
{

    struct TownNode *temp = (struct TownNode *)malloc(sizeof(struct TownNode));
    if (p != NULL)
    {
        if (temp != NULL)
        {
            strcpy(temp->town_name, str);
            temp->next_town = NULL;
            p->next_town = temp;
            temp->prev_town = p;
        }
    }
    else
    {
        if (temp != NULL)
        {
            strcpy(temp->town_name, str);
            temp->next_town = NULL;
            L->next_town = temp;
            temp->prev_district = L;
        }
    }
}

void Insertnode2(int popul, char name[50], struct DistrictNode *L, struct TownNode *p) //insert node for radixt sort for populations
{

    struct TownNode *temp = (struct TownNode *)malloc(sizeof(struct TownNode));
    if (p != NULL)
    {
        if (temp != NULL)
        {
            strcpy(temp->town_name, name);
            temp->population = popul;
            temp->next_town = NULL;
            p->next_town = temp;
            temp->prev_town = p;
        }
    }
    else
    {
        if (temp != NULL)
        {
            strcpy(temp->town_name, name);
            temp->population = popul;
            temp->next_town = NULL;
            L->next_town = temp;
            temp->prev_district = L;
        }
    }
    L->tail = temp;
}
struct TownNode *FindLastNodeRadix(struct DistrictNode *L)
{

    struct TownNode *p = L->next_town;
    if (p != NULL)
    {
        while (p->next_town != NULL)
        {
            p = p->next_town;
        }
    }
    return p;
}

void RadixSort(struct DistrictNode *d[20])
{
    int s = NumOfDistricts(d);
    struct DistrictNode *r[55]; //( 26 lower, 26 upper, 1 space , 1 dash , 1 for short strings)
    char x;
    for (int i = 0; i < 55; i++) //array of structs
    {
        r[i] = NULL;
        r[i] = MakeDEmpty(r[i]);
    }
    struct DistrictNode *copy[20]; // to copy the towns after sorting
    Makecopy(d, copy);
    int size = MaxSize(d);
    while (size != 0)
    {

        for (int i = 0; i < s; i++)
        {
            char str[20];
            strcpy(str, d[i]->district_name);
            if (strlen(str) >= size) //this condition for sorting the tall strings first
            {
                x = str[size - 1];
                if (x == 32)
                { // Space
                    Insertnode(str, r[53], FindLastNodeRadix(r[53]));
                }
                else if (x == 45)
                { // Dash
                    Insertnode(str, r[54], FindLastNodeRadix(r[54]));
                }
                else if (x >= 97 && x <= 122) //small letters
                {
                    Insertnode(str, r[2 * (x - 'a') + 1], FindLastNodeRadix(r[2 * (x - 'a') + 1]));
                }
                else if (x >= 65 && x <= 90) ///capital letters
                {
                    Insertnode(str, r[2 * (x - 'A') + 2], FindLastNodeRadix(r[2 * (x - 'A') + 2]));
                }
            }
            else
            {
                Insertnode(str, r[0], FindLastNodeRadix(r[0]));//insert the short strings at the first index until the size decrease
            }
        }

        for (int i = 0; i < 20; i++) //empty the main list to insert in it new order districts later
        {
            d[i] = MakeDEmpty(d[i]);
        }

        for (int j = 0; j < 55; j++) //inserting the new order of districts in the main list
        {
            struct TownNode *t = NULL;
            t = r[j]->next_town;
            while (t != NULL)
            {
                InsertDistrict(d, t->town_name);
                t = t->next_town;
            }
        }

        for (int i = 0; i < 55; i++) //empty the array of structs in each round
        {
            r[i] = NULL;
            r[i] = MakeDEmpty(r[i]);
        }
        size--;
    }

    for (int i = 0; i < 20; i++) //copying the towns from the copy to the main list 
    {
        struct DistrictNode *p = NULL;
        p = FindDistrict(copy, d[i]->district_name);
        d[i]->next_town = p->next_town;
    }
}

void printAfterSorting(struct DistrictNode *d[20])
{
    int s = NumOfDistricts(d);
    if (s == 0)
    {
        printf("There are no Districts in your list!!\n\n");
    }

    else
    {
        struct TownNode *p = NULL;
        for (int i = 0; i < s; i++)
        {
            printf("%s District, Population= %d\n", d[i]->district_name, DistrictPopulation(d[i]));
            p = d[i]->next_town;
            while (p != NULL)
            {
                printf("%s, %d\n", p->town_name, p->population);
                p = p->next_town;
            }
            printf("\n");
        }
    }
}

void Wfile(struct DistrictNode *d[20]) //write in the output file
{
    FILE *myfile;
    myfile = fopen("sorted_districts.txt", "w");
    int s = NumOfDistricts(d);
    struct TownNode *p = NULL;
    for (int i = 0; i < s; i++)
    {
        fprintf(myfile, "%s District, Population= %d\n", d[i]->district_name, DistrictPopulation(d[i]));
        p = d[i]->next_town;
        while (p != NULL)
        {
            fprintf(myfile, "%s, %d\n", p->town_name, p->population);
            p = p->next_town;
        }
    }
    fclose(myfile);
}

int maxTowninD(struct DistrictNode *d) //max town population in specific district, used for population radix sort
{
    int max = 0;
    int s = NumOfTowns(d);
    struct TownNode *p = d->next_town;
    for (int i = 0; i < s; i++)
    { // Note: there is no need to check if p!=NULL because the number of towns can do that
        if (p->population > max)
        {
            max = p->population;
        }

        p = p->next_town;
    }
    return max;
}

struct DistrictNode *RadixNumbers(struct DistrictNode *d) //sorting the populations in radix sort
{
    int s = NumOfTowns(d);
    int m, n = 1, Maxdigit = 0, temp = 0;
    char districtname[50];
    strcpy(districtname, d->district_name); // to store the district name
    struct DistrictNode *r[10]; // 10 digits
    for (int i = 0; i < 10; i++) // array of struct for radix sort
    {
        r[i] = NULL;
        r[i] = MakeDEmpty(r[i]);
    }

    int largest = maxTowninD(d); //the max population in the district

    while (largest != 0) //to know the digits of the max population number
    {
        largest /= 10;
        Maxdigit++;
    }
    char townname[50];
    while (Maxdigit != 0) //the rounds of he radix sort is based on the max digits number
    {
        struct TownNode *p = d->next_town;
        for (int i = 0; i < s; i++)
        {
            strcpy(townname, p->town_name);
            m = p->population;
            temp = m / n; //to take the least sig number , to the most sig in each round
            Insertnode2(m, townname, r[temp % 10], FindLastNodeRadix(r[temp % 10])); //inserting the population in the appropriate index
            p = p->next_town;
        }

        d = MakeDEmpty(d); //empty the main list
        for (int i = 0; i < 10; i++)
        {
            struct TownNode *t = NULL;
            t = r[i]->next_town;
            while (t != NULL) //inserting the new order of towns in the main disrict
            {

                Insertnode2(t->population, t->town_name, d, FindLastNodeRadix(d));
                t = t->next_town; 
            }
        }

        for (int i = 0; i < 10; i++) //empty the array of struct in each round
        {
            r[i] = NULL;
            r[i] = MakeDEmpty(r[i]);
        }

        n *= 10; //the digits
        Maxdigit--;
    }
    strcpy(d->district_name, districtname); //copy the district name to the new list
    return d;
}

int NumofTownsInPs(struct DistrictNode *d[20]) //used to check if there are towns to display the min and max population
{
    int count = 0;
    int s = NumOfDistricts(d);

    for (int i = 0; i < s; i++)
    {
        count += NumOfTowns(d[i]);
    }

    return count;
}    
