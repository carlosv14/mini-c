void printArray(int a[], int size)
{
    int i = 0;
    while(i<size) {
        printf(a[i]);
        printf("\t");
        i = i + 1;
    }
    printf("\n");
}

void main ()
{
   int i, j,temp,pass=0;
   int a[10] = {10,2,0,14,43,25,18,1,5,45};
   printf("Input list ...\n");
   printArray(a, 10);
   i = 0;
    while(i<10) {
        j = i + 1;
        while(j<10)
        {
            if(a[j] < a[i]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
            j = j + 1;
        }
        i = i+1;
        pass = pass + 1;
    }
    printf("Sorted Element List ...\n");
    printArray(a, 10);

    printf("\nNumber of passes taken to sort the list:");
    printf(pass);
    printf("\n");
}