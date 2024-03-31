#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//1200540

typedef struct information{

    int CreditHours;
    char CourseCode[100];
    char Course[200];
    char topics[200][100];
    char department[20];
    int num_topics;


};


struct information s1[100];// CREATE ARRAY TO READ FROM THE FILE
char *trim(char *str);// TO REMOVE WITHE SPACES
struct information** courses1 = NULL;//CREATE EMPTY QUADRATIC HASHTABLE
struct information** courses2 = NULL;//CREATE EMPTY DOUBLE HASHTABLE
int QH=0;// # number of collision occur in quadratic hash  method
int DH=0;// # number of collision occur in double hash method

int length=0;// the length of the array
int TableSize=0;// the length of the hash table size





int main()
{
    char file_couses[10000];
    length= readdata(file_couses,s1);// TO INSERT TO THE ARRAY FROM FILE AND GET THE NUMBER OF ELEMENTS
printf("the length is %d \n" , length);
       createHashTable();// TO CREATE TWO HASH TABLES(DOUBLE AND QUADRATIC )


  Display();

      return 0;
}


void DisplayC(){
    printf("Choose from the menu below:\n");
    printf("1) Print hashed tables (including empty spots) . \n");
    printf("2) Print out table size and the load factor. \n");
    printf("3) Print out the used hash functions. \n");
    printf("4) Insert a new record to hash table (insertion will be done on both hash tables). \n");
    printf("5) Search for a specific word (specify which table to search in). .\n");
    printf("6) Delete a specific record (from both tables). \n");
    printf("7) Compare between the two methods in terms of number of collisions occurred. \n");
    printf("8) Save hash table back to a file named saved_courses.txt (of the double hashing).\n");
    printf("9) exit.\n");

}
 // display menu
void Display(){
    int choice;
    DisplayC();

    while(1)
    {
        scanf("%d", &choice);
        if(choice == 9)
        {
            printf("Goodbye");
            break;
        }

        switch(choice)
        {
            case 1:

          printhash();

            break;
            case 2:
                printf(" The Table Size Is : %d \n" , TableSize);

                printf(" THE DEAULT LOAD FACTOR IS 0.75  THEN  ( # of keys /table size   ) MUST BE LESS THAN 0.75 \n  ");

                if(length/(float)TableSize  < 0.75)
                    printf("THE  VALUE IS %.2f  < 0.75 \n" ,length/(float)TableSize );

                else
                printf("THE  VALUE IS %.2f > 0.75 \n" ,length/(float)TableSize );


            break;

            case 3:

        printf("Table 1  : (QUADRATIC HASING) for  Strings (shifting by 5 ) \n   ( ((hash value << 5 ) + *key++) %% Table Size) + i*i) % TableSize Where 0 <i< hash table size    \n");

        printf("Table 2  : (DOUBLE HASING) for  Strings(shifting by 5 ) \n  ((hash value << 5 ) + *key++) %% Table Size ) + (i*(hash((hash value << 5 ) + *key++)) %% TableSize where 0 <i< hash table size    ");

                break;

            case 4:
            insert();

                break;


            case 5:
                search();

                break;

            case 6:
            deletecourse();
                break;

            case 7:
            collisionscmp();
                break;

            case 8:
                saveHashTable();
                break;


            default:
                printf("Please number from 1 to 8\n");
        }

        printf("\n\n");
        DisplayC();
    }
}
// to read file course and fill into array of struct(information)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int readdata( char file_c[10000]){

     FILE *couses_file;

   couses_file = fopen("courses.txt","r");//open the file and read from it

    if (couses_file == NULL){
        printf("File does not exist");
        return (-1);
    }

int length=0;

    while ( (fgets(file_c,10000,couses_file))!= NULL && couses_file !=EOF){
fillcourses(file_c ,length);
length++;
    }

    fclose(couses_file);
return length;
}


void fillcourses ( char line[] , int i){



    char *token = strtok(line,":");
    strcpy(s1[i].Course,token);
    token = strtok(NULL,"#");
        s1[i].CreditHours = atoi(token);
       token = strtok(NULL,"#");

         strcpy(s1[i].CourseCode,token);

             token = strtok(NULL,"/");
    strcpy(s1[i].department,token);

////     Read the topics
    int counter = 0;
        token = strtok(NULL,",");
    while(token != NULL){
        token=trim(token);
        strcpy(s1[i].topics[counter],(token));
        counter++;
        token = strtok(NULL,",");
            }
    s1[i].num_topics=counter;// to know the number of topics



}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int hash (char *key){

int hashvalue = 0;

  // shift by  5 -->  mult by 2^5 = 32

while ( *key != '\0' )
hashvalue = (hashvalue << 5 ) + *key++;
if( hashvalue < 0 )
hashvalue += TableSize;
return ( hashvalue % TableSize);


}


int guadratichashing(char name[100] ){

int coll=0;
int i=0;
while (i < TableSize){
 int index=(hash(name) + i*i) % TableSize; // get index from shifting string method then use quadratic hash menthod
if (courses1[index]!= NULL){ // to check if the spot is empty or not
    i++;
    QH++;//# OF COLLISIONS
}
else
return index;

}
}

//////////////////////////////////////////////////////////////////
// for search
int serachq(char name[100]){
int i=0;
while (i < TableSize){
int index=(hash(name) + i*i) % TableSize; // get index from shifting string method then use double hash menthod
if (courses1[index]!= NULL){
    if(index >= 0 && index < TableSize){
   if(strcmp(courses1[index],name) == 0)// to check if the spot has the same course name
   return index;

    }
    i++;
}
else
return -1; // the index did not found
}

}
/////////////////////////////////////////////////////////////////////////////
int doublehashing(char name[100]){

int i=0;
while (i<TableSize){
int index=((hash(name)) + (i*fun(hash(name)))) % TableSize ; // get index from shifting string method then use double hash menthod
if (courses2[index]!= NULL){// to check if the spot is empty or not
    i++;
    DH++;// # OF COLLISIONS
}
else
return index;

}

}
////
int fun(int x){

int p=primeless(length);
return p -(x%p);


}
////
int primeless(){ // the first prime number < table size

int  size =(length*2);
    while(isPrime(size)==0)
    size--;

return size;
}

////////////////////////////////////////////////////////////////////////////////////
int serachd(char name[100]){

int i=0;
while (i < TableSize){
int index=(hash(name) % TableSize) + (i*fun(hash(name))) ;// to get the index
if (courses2[index]!= NULL){
    if(index >= 0 && index < TableSize){
   if(strcmp(courses2[index],name) == 0) // to check if the spot has the same course name
   return index;

    }
    i++;
}
else
return -1; // the index did not found
}


}
///////////////////////////////////////////////////////////////////////////////////
int tablesize(){ // the first prime number > number of element*2

int  size =(length*2)+1;
    while(isPrime(size)==0)
    size++;

return size;
}
///////////////////////////////////////////////////////////////////////////////////
void createHashTable( ){

    courses1 = (struct Node**) malloc((sizeof (struct Node*)) * 100);//FOR CREATE THE Quad  HASH TABLE
    courses2 = (struct Node**) malloc((sizeof (struct Node*)) * 100);//FOR CREATE THE Double  HASH TABLE

// set NULL to data
    for (int i = 0; i < 100; ++i)
        courses1[i] = NULL;

            for (int i = 0; i < 100; ++i)
        courses2[i] = NULL;

         TableSize=tablesize();// the first prime number > number of element*2

        for(int i=0;i<length ; i++){
        addtotable(s1[i].Course); //FOR ADD THE courses FROM THE array TO THE  HASH TABLES

        }


}

//////////////////////////////////////////////////////////////////////////////////////////////////
void addtotable(char name[200] ){

if((int) (0.75 * TableSize) <= length){ // to check the tables is nearly full to rehash it
    rehash(TableSize, name);
}
else{
int index1 = guadratichashing(name); // get index from the quadratic hash method
int index2 = doublehashing(name); // get index from the double hash method
courses1[index1]=name; // add the course to the index
 courses2[index2]=name;//  add the course to the index of second table
}
}
/////////////////////////////////////////////////////////////
void  rehash(int oldtablesize,char name[200]){ // when the table is 0.75  full then reenter (re hash) the element to the tables

int newsize=(oldtablesize*2)+1;
    while(isPrime(newsize)==0)
    newsize++;

TableSize=newsize;//new size

////////////////////////////////////////////////////////////
//re initialize tables to re insert the elements
     courses1 = (struct Node**) malloc((sizeof (struct Node*)) * TableSize);//FOR CREATE THE Quad  HASH TABLE
    courses2 = (struct Node**) malloc((sizeof (struct Node*)) * TableSize);//FOR CREATE THE Double  HASH TABLE


    for (int i = 0; i < TableSize; ++i)
        courses1[i] = NULL;

            for (int i = 0; i < TableSize; ++i)
        courses2[i] = NULL;
////////////////////////////////////////////////////////////
//re insert the elements in the tables
        for(int i=0;i<length ; i++){
        addtotable(s1[i].Course);

        }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


void search(){

    char temp;
    int choice;
    char name[20];
    printf("enter course name : ");
        scanf("%c",&temp);
        gets(name);


    printf(" \n In which Table !!! \n 1 for Quad Table \n 2 for Double Table");
    scanf("%d",&choice);

    if(choice ==1){ // search in quadratic hash table


int index =serachq(name); // get the index from quadratic table method


if(index > tablesize(length) || index <0)
    printf("there is no course with this name in Quad Table %s \n " , name);


  else{

    printf(" INDEX : %d \n" , index );

   for(int i=0;i<length;i++){

    if(strcmp(s1[i].Course,name)==0){
printf(" \n Course Code : %s   Course Name: %s  CreditHours: %d  Department: %s\n"
                , s1[i].CourseCode,s1[i].Course, s1[i].CreditHours, s1[i].department);
                printf( " Topics : ");
              for(int j=0 ; j<s1[i].num_topics; j++)
                printf( " %s " , s1[i].topics[j]);
                printf("\n");

  }
    }

    }}

   else if( choice ==2){ // search in double hash table
int index =serachd(name); // get the index form double hash method


if(index > tablesize(length) || index <0)
    printf("there is no course with this name in Quad Table %s \n " , name);


  else{

    printf(" INDEX : %d \n" , index );

   for(int i=0;i<length;i++){

    if(strcmp(s1[i].Course,name)==0){
printf(" \n Course Code : %s   Course Name: %s  CreditHours: %d  Department: %s\n"
                , s1[i].CourseCode,s1[i].Course, s1[i].CreditHours, s1[i].department);
                printf( " Topics : ");
              for(int j=0 ; j<s1[i].num_topics; j++)
                printf( " %s " , s1[i].topics[j]);
                printf("\n");

  }
    }

    }
}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void insert(){
char name[100]; char temp; int chours;   char dep[100];  char ccode[100]; char topics[100];
printf("%d",length);

length=length+1;// the # of element increse
            printf("Enter The course code : ");
            scanf("%s", &ccode);
            strcpy(s1[length-1].CourseCode,ccode);


           printf("Enter The New Name : ");
             scanf("%c",&temp);//temprorary character
             gets(name);
             strcpy(s1[length-1].Course,name) ;

            printf("Enter The New credit hours : ");
            scanf("%d", &chours);
            s1[length-1].CreditHours = chours;


       printf("Enter The New department : ");
            scanf("%c",&temp);
            gets(dep);
           strcpy(s1[length-1].department,dep);


int num;
        printf("enter number of topics you want to insert");
        scanf("%d",&num);
        s1[length-1].num_topics=num;

        for(int i=0;i<num;i++){
                printf("Enter The New topics : ");
            scanf("%c",&temp);
                gets(topics);
                strcpy(s1[length-1].topics[i],topics);
}
addtotable(s1[length-1].Course);// to add record to the table


}
/////////////////////////////////////////////////////////////////////////////

void deletecourse (){

    char temp;
    char name[20];
    printf("enter course name : ");
        scanf("%c",&temp);
        gets(name);

            int index1 =serachq(name);// get the index from quadratic hash table method
            int index2 =serachd(name);// get the index from double hash table method



            if(index1 <0 || index1>TableSize && index2 <0 || index2>TableSize) // if the index not between 0 and table size
                printf("there is no course with this name");

             else {
            courses1[index1] = NULL;
            courses2[index2] = NULL;
         //   length--;//decrease # of element
             }


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////

void saveHashTable(){

     FILE *hash;

   hash = fopen("saved_courses.txt","w");//open the file and write on it

           fprintf(hash, "     DOUBLE HASH TABLE      \n");

    for (int i = 0; i < TableSize; ++i)
        fprintf(hash, "Index : %d\t Name: %s\n", i, courses2[i]);


    fclose(hash);//FOR CLOSE THE OUTPUT FILE



}


///////////////////////////////////////////////////////////////////////////////////////////////////////
void collisionscmp(){

printf("THE NUMBER OF COLLISIONS OCCURED IN QUADRTIC HASH TABLE IS : %d \n",QH);

printf("THE NUMBER OF COLLISIONS OCCURED IN DOULE HASH TABLE IS : %d \n ",DH);


if(QH<DH)
        printf("THE METHOD OF USING QUADRTIC HASINH IS BETTER BECUSE THE NUMBER"
                "OF COLLISIONS OCCURED  LESS THAN DOUBLE TABLE");


else if(DH<QH)
  printf("THE METHOD OF USING DOUBLE HASINH IS BETTER BECUSE THE NUMBER"
                "OF COLLISIONS OCCURED  LESS THAN QUADRTIC TABLE");




 else
        printf("THE TWO METHODS ARE EQUIVELENT");
}



//////////////////////////////////////////////////////////////////////////////
void printhash() {

                printf("         Quad HASH TABLE 1 \n");
                printf("_____________________________________________________________\n\n");
    for (int i = 0; i < TableSize; i++) {
        printf("Index : %d\t Name: %s\n", i, courses1[i]);
    }
                printf(" \n     Double HASH TABLE 2 \n");
                printf("_____________________________________________________________\n\n");

    for (int i = 0; i < TableSize; i++) {
        printf("Index : %d\t Name: %s\n", i, courses2[i]);
    }


}
/////////////////////////////////////////////////////////////////////////////////
int isPrime(int n)
{
    // base case
    if (n <= 1)
        return 0;

    // Check from 2 to (n-1) / 2
    for (int i = 2; i <= n/2; i++)
        if (n % i == 0)
            return 0;

    return 1;
}


/////////////////////////////////////////////////////////////////
// this function to trim white spaces from the string
char *trim(char *str)
{
    int i;

    while (isspace (*str)) str++;   // skip left side white spaces
    for (i = strlen (str) - 1; (isspace (str[i])); i--) ;   // skip right side white spaces
    str[i + 1] = '\0';
    return str;
}
