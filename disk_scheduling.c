#include <stdio.h>  //for printf and scanf
#include <stdlib.h> //for malloc

#define LOW 0
#define HIGH 199
#define START 53

//compare function for qsort
//you might have to sort the request array
//use the qsort function 
// an argument to qsort function is a function that compares 2 quantities
//use this there.
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

//Prints the sequence and the performance metric
void printSeqNPerformance(int *request, int numRequest)
{
    int i, last, acc = 0;
    last = START;
    printf("\n");
    printf("%d", START);
    for (i = 0; i < numRequest; i++)
    {
        printf(" -> %d", request[i]);
        acc += abs(last - request[i]);
        last = request[i];
    }
    printf("\nPerformance : %d\n", acc);
    return;
}

//access the disk location in FCFS
void accessFCFS(int *request, int numRequest)
{
    //simplest part of assignment
    printf("\n----------------\n");
    printf("FCFS :");
    printSeqNPerformance(request, numRequest);
    printf("----------------\n");
    return;
}

//access the disk location in SSTF
void accessSSTF(int *request, int numRequest)
{
    //write your logic here
    //the position of the request that has the shortest distance
    int index;
    //our array containg the job sequence
    int newRequest[numRequest];
    
    //the head's position
    int last = START;
    //counter
    int count =0;
    while(count < numRequest){
        //the shortest difference between requests initialized to a big number
        int shortest = 100000000;

        for(int i=0;i<numRequest;i++){
            //if the difference between the current position and the request is smaller than the shortest
            if(abs(last - request[i]) < shortest){
                //update the shortest distance
                shortest = abs(last - request[i]);
                //save the index
                index = i;
            }
        }
        //the current position of the head
        last = request[index];
        //assigning the order of the 
        newRequest[count] = last;
        //setting the values of to be very large so that we dont go back to it
        request[index] = 1000000000;
        //increment the count
        count++;
    }
    printf("\n----------------\n");
    printf("SSTF :");
    printSeqNPerformance(newRequest, numRequest);
    printf("----------------\n");
    return;
}

//access the disk location in SCAN
void accessSCAN(int *request, int numRequest)
{
    //our array that will contain an extreme
    int *newExtraRequest;
    //an index
    int index=0;
    //midpoint of the high and lows
    int mid = (HIGH + LOW) / 2;
    //sort the array first
    qsort(request,numRequest,sizeof(int),cmpfunc);
    //our new array containing the final job sequence
    int newRequest[numRequest];
    //arrays the will contain elements that are < start and > start
    int firstHalf[numRequest];
    int secondHalf[numRequest];
    int newCnt;

    for(int i =0;i<numRequest;i++){
        //if the request is smaller than start, store it in the respective array
        //and set the other array's index to -1.
        if(request[i] < START){
            firstHalf[i] = request[i];
            secondHalf[i] = -1;
        }
        else{
            //request[i] > start
            secondHalf[i] = request[i];     
            firstHalf[i] = -1;
        }
    }
    if(START < mid){
        //move left
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(firstHalf[numRequest-1-i] == -1) continue;
            else {
                //add it to the new array
                newRequest[index] = firstHalf[numRequest-1-i];
                //increment index
                index++;
            }
        }
        //if the number of request doesnt match the index, it means that we are not done with all the requests
        if(index != numRequest){
            //allocate extra space for the extreme
            newExtraRequest = malloc(sizeof(int)*(numRequest+1));
            for(int i=0;i<numRequest;i++){
                //copy everything into the new array
                newExtraRequest[i] = newRequest[i];
            }
            //go to the extreme
            newExtraRequest[index] = LOW;
            //increment the position
            index++;
            //update the number of requests
            newCnt = numRequest + 1;
        }
        else{
            //otherwise we are done
            newExtraRequest = newRequest;
            newCnt = numRequest;
        }
        //dealing with the second half if we have any
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(secondHalf[i] == -1) continue;
            else {
                //add it to the new array
                newExtraRequest[index] = secondHalf[i];
                //increment index
                index++;
            }
        }

    }
    else{
        //move right
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(secondHalf[i] == -1) continue;
            else {
                //add it to the new array
                newRequest[index] = secondHalf[i];
                //increment index
                index++;
            }
        }        
        //if the number of request doesnt match the index, it means that we are not done with all the requests
        if(index != numRequest){
            //allocate extra space for the extreme
            newExtraRequest = malloc(sizeof(int)*(numRequest+1));
            for(int i=0;i<numRequest;i++){
                //copy everything into the new array
                newExtraRequest[i] = newRequest[i];
            }
            //go to the extreme
            newExtraRequest[index] = HIGH;
            //increment the position
            index++;
            //update the number of requests
            newCnt = numRequest + 1;
        }
        else{
            //otherwise we are done
            newExtraRequest = newRequest;
            newCnt = numRequest;
        }
        //dealing with the first half
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(firstHalf[numRequest-1-i] == -1) continue;
            else {
                //add it the new array
                newExtraRequest[index] = firstHalf[numRequest-1-i];
                //increment index
                index++;
            }
        }
    }
    //write your logic here
    printf("\n----------------\n");
    printf("SCAN :");
    printSeqNPerformance(newExtraRequest, newCnt);
    printf("----------------\n");
    return;
}

//access the disk location in CSCAN
void accessCSCAN(int *request, int numRequest)
{
    //our array that will contain an extreme
    int *newExtraRequest;
    //an index
    int index=0;
    //midpoint of the high and lows
    int mid = (HIGH + LOW) / 2;
    //sort the array first
    qsort(request,numRequest,sizeof(int),cmpfunc);
    //our new array containing the final job sequence
    int newRequest[numRequest];
    //arrays the will contain elements that are < start and > start
    int firstHalf[numRequest];
    int secondHalf[numRequest];
    int newCnt;

    for(int i =0;i<numRequest;i++){
        //if the request is smaller than start, store it in the respective array
        //and set the other array's index to -1.
        if(request[i] < START){
            firstHalf[i] = request[i];
            secondHalf[i] = -1;
        }
        else{
            //request[i] > start
            secondHalf[i] = request[i];     
            firstHalf[i] = -1;
        }
    }
    if(START < mid){
        //move left
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(firstHalf[numRequest-1-i] == -1) continue;
            else {
                //add it to the new array
                newRequest[index] = firstHalf[numRequest-1-i];
                //increment position
                index++;
            }
        }
        //if the number of request doesnt match the index, it means that we are not done with all the requests
        if(index != numRequest){
            //allocate extra space for the extreme
            newExtraRequest = malloc(sizeof(int)*(numRequest+2));
            for(int i=0;i<numRequest;i++){
                //copy everything into the new array
                newExtraRequest[i] = newRequest[i];
            }
            //go to the extreme
            newExtraRequest[index] = LOW;
            //increment the position
            index++;
            //go to the extreme
            newExtraRequest[index] = HIGH;
            //increment the position
            index++;
            //update the number of requests
            newCnt = numRequest + 2;
        }
        else{
            //otherwise we are done
            newExtraRequest = newRequest;
            newCnt = numRequest;
        }
        //dealing with the second half if we have any
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(secondHalf[numRequest-1-i] == -1) continue;
            else {
                //add it to the new array
                newExtraRequest[index] = secondHalf[numRequest-1-i];
                //increment index
                index++;
            }
        }

    }
    else{
        //move right
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(secondHalf[i] == -1) continue;
            else {
                //add it to the new array 
                newRequest[index] = secondHalf[i];
                //increment index
                index++;
            }
        }
        //if the number of request doesnt match the index, it means that we are not done with all the requests
        if(index != numRequest){
            //allocate extra space for the extreme
            newExtraRequest = malloc(sizeof(int)*(numRequest+2));
            for(int i=0;i<numRequest;i++){
                //copy everything into the new array
                newExtraRequest[i] = newRequest[i];
            }
            //go to the extreme
            newExtraRequest[index] = HIGH;
            //increment the position
            index++;
            //go to the extreme
            newExtraRequest[index] = LOW;
            //increment the position
            index++;
            //update the number of requests
            newCnt = numRequest + 2;
        }
        else{
            //otherwise we are done
            newExtraRequest = newRequest;
            newCnt = numRequest;
        }
        //dealing with the first half
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(firstHalf[i] == -1) continue;
            else {
                //add it to the new array
                newExtraRequest[index] = firstHalf[i];
                //increment index
                index++;
            }
        }
    }
    //write your logic here
    printf("\n----------------\n");
    printf("CSCAN :");
    printSeqNPerformance(newExtraRequest, newCnt);
    printf("----------------\n");
    return;
}

//access the disk location in LOOK
void accessLOOK(int *request, int numRequest)
{
    //an index
    int index=0;
    //midpoint of the high and lows
    int mid = (HIGH + LOW) / 2;
    //sort the array first
    qsort(request,numRequest,sizeof(int),cmpfunc);
    //our new array containing the final job sequence
    int newRequest[numRequest];
    //arrays the will contain elements that are < start and > start
    int firstHalf[numRequest];
    int secondHalf[numRequest];
    int newCnt;

    for(int i =0;i<numRequest;i++){
        //if the request is smaller than start, store it in the respective array
        //and set the other array's index to -1.
        if(request[i] < START){
            firstHalf[i] = request[i];
            secondHalf[i] = -1;
        }
        else{
            //request[i] > start
            secondHalf[i] = request[i];     
            firstHalf[i] = -1;
        }
    }
    if(START < mid){
        //move left
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(firstHalf[numRequest-1-i] == -1) continue;
            else {
                //add it to the new array
                newRequest[index] = firstHalf[numRequest-1-i];
                //increment index
                index++;
            }
        }
        //dealing with the second half if we have any
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(secondHalf[i] == -1) continue;
            else {
                //add it to the new array
                newRequest[index] = secondHalf[i];
                //increment index
                index++;
            }
        }
    }
    else{
        //move right
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(secondHalf[i] == -1) continue;
            else {
                //add it to the new array
                newRequest[index] = secondHalf[i];
                //increment index
                index++;
            }
        }
        //dealing with the first half
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(firstHalf[numRequest-1-i] == -1) continue;
            else {
                //add it to the new array
                newRequest[index] = firstHalf[numRequest-1-i];
                //increment index
                index++;
            }
        }
    }
    //write your logic here
    printf("\n----------------\n");
    printf("LOOK :");
    printSeqNPerformance(newRequest, numRequest);
    printf("----------------\n");
    return;
}

//access the disk location in CLOOK
void accessCLOOK(int *request, int numRequest)
{
    //our array that will contain an extreme
    int *newExtraRequest;
    //an index
    int index=0;
    //midpoint of the high and lows
    int mid = (HIGH + LOW) / 2;
    //sort the array first
    qsort(request,numRequest,sizeof(int),cmpfunc);
    //our new array containing the final job sequence
    int newRequest[numRequest];
    //arrays the will contain elements that are < start and > start
    int firstHalf[numRequest];
    int secondHalf[numRequest];
    int newCnt;

    for(int i =0;i<numRequest;i++){
        //if the request is smaller than start, store it in the respective array
        //and set the other array's index to -1.
        if(request[i] < START){
            firstHalf[i] = request[i];
            secondHalf[i] = -1;
        }
        else{
            //request[i] > start
            secondHalf[i] = request[i];     
            firstHalf[i] = -1;
        }
    }
    if(START < mid){
        //move left
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(firstHalf[numRequest-1-i] == -1) continue;
            else {
                //add it to the new array
                newRequest[index] = firstHalf[numRequest-1-i];
                //increment index
                index++;
            }
        }
        //if the number of request doesnt match the index, it means that we are not done with all the requests
        if(index != numRequest){
            //allocate extra space for the extreme
            newExtraRequest = malloc(sizeof(int)*(numRequest+1));
            for(int i=0;i<numRequest;i++){
                //copy everything into the new array
                newExtraRequest[i] = newRequest[i];
            }
            //go to the extreme
            newExtraRequest[index] = HIGH;
            //increment the position
            index++;
            //update the number of requests
            newCnt = numRequest + 1;
        }
        else{
            //otherwise we are done
            newExtraRequest = newRequest;
            newCnt = numRequest;
        }
        //dealing with the second half if we have any
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(secondHalf[numRequest-1-i] == -1) continue;
            else {
                //add it to the new array
                newExtraRequest[index] = secondHalf[numRequest-1-i];
                //increment index
                index++;
            }
        }

    }
    else{
        //move right
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(secondHalf[i] == -1) continue;
            else {
                //add it to the new array
                newRequest[index] = secondHalf[i];
                //increment index
                index++;
            }
        }
        //if the number of request doesnt match the index, it means that we are not done with all the requests
        if(index != numRequest){
            //allocate extra space for the extreme
            newExtraRequest = malloc(sizeof(int)*(numRequest+1));
            for(int i=0;i<numRequest;i++){
                //copy everything into the new array
                newExtraRequest[i] = newRequest[i];
            }
            //go to the extreme
            newExtraRequest[index] = LOW;
            //increment the position
            index++;
            //update the number of requests
            newCnt = numRequest + 1;
        }
        else{
            //otherwise we are done
            newExtraRequest = newRequest;
            newCnt = numRequest;
        }
        //dealing with the first half
        for(int i=0;i<numRequest;i++){
            //if the content is -1 move on to the next position
            if(firstHalf[i] == -1) continue;
            else {
                //add it to the new array
                newExtraRequest[index] = firstHalf[i];
                //increment index
                index++;
            }
        }
    }
    //write your logic here
    printf("\n----------------\n");
    printf("CLOOK :");
    printSeqNPerformance(newExtraRequest,newCnt);
    printf("----------------\n");
    return;
}

int main()
{
    int *request, numRequest, i,ans;

    //allocate memory to store requests
    printf("Enter the number of disk access requests : ");
    scanf("%d", &numRequest);
    request = malloc(numRequest * sizeof(int));

    printf("Enter the requests ranging between %d and %d\n", LOW, HIGH);
    for (i = 0; i < numRequest; i++)
    {
        scanf("%d", &request[i]);
    }

    printf("\nSelect the policy : \n");
    printf("----------------\n");
    printf("1\t FCFS\n");
    printf("2\t SSTF\n");
    printf("3\t SCAN\n");
    printf("4\t CSCAN\n");
    printf("5\t LOOK\n");
    printf("6\t CLOOK\n");
    printf("----------------\n");
    scanf("%d",&ans);

    switch (ans)
    {
    //access the disk location in FCFS
    case 1: accessFCFS(request, numRequest);
        break;

    //access the disk location in SSTF
    case 2: accessSSTF(request, numRequest);
        break;

        //access the disk location in SCAN
     case 3: accessSCAN(request, numRequest);
        break;

        //access the disk location in CSCAN
    case 4: accessCSCAN(request,numRequest);
        break;

    //access the disk location in LOOK
    case 5: accessLOOK(request,numRequest);
        break;

    //access the disk location in CLOOK
    case 6: accessCLOOK(request,numRequest);
        break;

    default:
        break;
    }
    return 0;
}
