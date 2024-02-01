#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global declarations
struct student
{
    int marks;
    int id;
    char name[10];
};
int sizeOfArray, totalNoOfRecords;
struct student s[100];


// Function declarations
void insert();
void display();
void seek();
void modify();
void deleteRecord();
void totalRecords();





int main()
{
    int choice;
    FILE *f;

    f = fopen("global.txt", "r+");
    
    fscanf(f, "%d", &totalNoOfRecords); // Storing previous value
    if(!totalNoOfRecords)
    {
        totalNoOfRecords = 0;
    }
    fclose(f);
    do
    {
        puts("-------------------");
        printf("Enter your choice\n");
        printf("1. Insert student record\n");
        printf("2. Seek a student's record\n");
        printf("3. Display all records\n");
        printf("4. Modify a record\n");
        printf("5. Delete a record\n");
        printf("6. Total number of records in file\n");
        printf("7. Exit\n");
        
        
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insert();
            break;
        case 2:
            seek();
        case 3:
            display();
            break;
        case 4:
           modify();
           break;
         case 5:
            deleteRecord();
            break;
        case 6:
            totalRecords();
            break;
        default:
            break;
        
        }


    } while (choice != 7);
    
    f = fopen("global.txt", "w+"); //Write current value
    fprintf(f, "%d", totalNoOfRecords);
    fclose(f);
  return 0;
}


void insert()
{
   
    FILE *fp;
    
    int n, i;
    printf("Enter size of array\n");
    scanf("%d", &sizeOfArray);

    

    fp = fopen("record.dat", "ab+");

   

    for (i = 0; i < sizeOfArray; i++)
    {
        puts("-------------------");
        printf("\t\t\t\tStudent %d's record\n", i+1);
        printf("Enter student %d's marks\n", i+1);
        scanf("%d", &s[i].marks);
        

        printf("Enter student %d's id\n", i+1);
        scanf("%d", &s[i].id);

        printf("Enter student %d's name\n", i+1);
        scanf("%s", s[i].name);
       

        
        fwrite(&s[i],  sizeof(struct student), 1,fp);
     
    }
     totalNoOfRecords += sizeOfArray;
   // printf("No%d\n", totalNoOfRecords);

    

 

   
    fclose(fp);


}
void seek()
{
        int i, srNo;
        FILE *fp;
        struct student t;
        

        fp = fopen("record.dat", "rb+");

        printf("Enter sr no of student you wanna search\n");
        scanf("%d", &srNo);
        srNo--;
       
        if (srNo <= 0)
        {
            fseek(fp, sizeof(t) , SEEK_SET);

        }
        
        fseek(fp, srNo * sizeof(t) , SEEK_SET);

        fread(&t, sizeof(t), 1, fp);
        

     
        
        fclose(fp);
}
    
void display()
 {
        FILE *fp;
        int i;
        struct student temp;

        fp = fopen("record.dat", "rb");
        
        if(totalNoOfRecords == 0) puts("No records are there");
        for(i=0; i< totalNoOfRecords; i++)
        {   
            fread(&s[i], sizeof(struct student), 1, fp);
            puts("-------------------");
            fprintf(stdout, "Student's marks: %d\n", s[i].marks);
        
            printf("Student's id: %d\n", s[i].id);
       
            printf("Student's name: %s\n", s[i].name);
         
        }
        
        fclose(fp); 
}
void modify()
{   
        int i, id;
        FILE *f1, *f2;
        struct student t;
        

        f1 = fopen("record.dat", "rb");
        f2 = fopen("temp.dat", "wb");

        printf("Enter id of student you wanna modify\n");
        scanf("%d", &id);
        
           while (fread(&t, sizeof(t), 1, f1))
        {
            if(id == t.id) // Modify if id is found
            {
              printf("Enter student's marks\n");
              scanf("%d", &t.marks);
        

              printf("Enter student's id\n");
              scanf("%d", &t.id);
 
              printf("Enter student's name\n");
              scanf("%s", t.name);
            }
            else
            {
             fwrite(&t, sizeof(t), 1, f2);
            }
        } 
        fclose(f1);
        fclose(f2);
        remove("record.dat");
        if(rename("temp.dat", "record.dat"))
        {
            puts("Record modified succesfully");
        }
}
void deleteRecord()
{   
        int i, id;
        FILE *f1, * f2;
        struct student t;
        

        f1 = fopen("record.dat", "rb");
        f2 = fopen("temp.dat", "wb");

        printf("Enter id of student you wanna delete\n");
        scanf("%d", &id);
        
        while (fread(&t, sizeof(t), 1, f1))
        {
            if(id == t.id)
            {
                totalNoOfRecords--;
              continue;
            }
            fwrite(&t, sizeof(t), 1, f2);
        } 
        fclose(f1);
        fclose(f2);
        remove("record.dat"); // Delete file and rename temp one
        if(rename("temp.dat", "record.dat"))
        {
            puts("Record deleted succesfully");
        }
        
         
          
       
        
}

void totalRecords()
{   
    printf("Total number of records %d\n", totalNoOfRecords);
}
