#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
	struct number{
	char value;
	struct number *nextPtr;
	struct number *backPtr;
};
typedef struct number number;
typedef number *numberPtr;

	void freeList(numberPtr head) {
    numberPtr current = head;
    numberPtr next;
    while (current != NULL) {
        next = current->backPtr;
        free(current);
        current = next;
    }
}

	//program use basic multiplying rules.
	numberPtr sum(numberPtr sum, numberPtr head){
	int carry=0;
	//sum is the result of multiplying one digit with the other linked list 
	//start is start of result
	numberPtr start = head;
	numberPtr temp=malloc(sizeof(number));
	//if there is no result it copies the first sum
	//else it sums two linked list.
	if(head==NULL){
		while(sum!=NULL){
			if(head==NULL){
			numberPtr added = malloc(sizeof(number));
			added->value=sum->value;
			added->nextPtr=NULL;
			added->backPtr=NULL;
			temp=added;
			head=added;
			}else{
			numberPtr added = malloc(sizeof(number));
			added->value=sum->value;
			added->nextPtr=NULL;
			added->backPtr=temp;
			temp->nextPtr=added;
			temp=added;
			}
			sum=sum->nextPtr;			
		}
		return head->nextPtr;
	}else{
		while(sum!=NULL){
			if(start!=NULL){
			int result = (start->value-'0')+(sum->value-'0')+carry;
			int remainder = result%10;
			carry=result/10;	
			start->value=remainder+'0';
			temp=start;
			start=start->nextPtr;
			}else{
				if(sum!=NULL&&carry!=0){
				numberPtr added = malloc(sizeof(number));
				int result = (sum->value-'0')+carry;
				int remainder = result%10;
				carry=result/10;
				added->value=remainder+'0';
				added->nextPtr=NULL;
				added->backPtr=temp;
				temp->nextPtr=added;
				temp=added;
				}else if(sum!=NULL){
				numberPtr added = malloc(sizeof(number));
				int result = (sum->value-'0');
				int remainder = result%10;
				carry=result/10;	
				added->value=remainder+'0';
				added->nextPtr=NULL;
				added->backPtr=temp;
				temp->nextPtr=added;
				temp=added;
				}else if(carry!=0){
				numberPtr added = malloc(sizeof(number));
				int result = carry;
				int remainder = result%10;
				carry=result/10;	
				added->value=remainder+'0';
				added->nextPtr=NULL;
				added->backPtr=temp;
				temp->nextPtr=added;
				temp=added;
				}
			}
			sum=sum->nextPtr;
			}
			//it returns next element of final result so it shifts the digit.
			return head->nextPtr;
		}
	}

	int main(){
	//starts the timer
	struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
	int change,carry,sumcheck=0;
	numberPtr startPtr1=NULL;
	numberPtr startPtr2=NULL;
	numberPtr endPtr1=NULL;
	numberPtr endPtr2=NULL;
	numberPtr currentPtr=NULL;
	FILE *cfPtr,*cPtr;
	cPtr = fopen("output.txt", "w");
	cfPtr = fopen("input.txt","r");
	char c;
	//take numbers and create linked lists.
	   while ((c = fgetc(cfPtr)) != EOF) {
		if (c == '\n') {
        change=1;	
        } else {
        	numberPtr newNumber = malloc(sizeof(number));
        	newNumber->value=c;
        	if(change==0){
        	if(startPtr1==NULL){
        	startPtr1=newNumber;
        	endPtr1=newNumber;
        	currentPtr=newNumber;
        	newNumber->backPtr=NULL;
        	newNumber->nextPtr=NULL;
			}
            else{
            currentPtr->nextPtr=newNumber;
            newNumber->backPtr=currentPtr;
            newNumber->nextPtr=NULL;
            endPtr1=newNumber;
            currentPtr=newNumber;
			}
			}else if(change==1){
			if(startPtr2==NULL){
        	startPtr2=newNumber;
        	currentPtr=newNumber;
        	newNumber->backPtr=NULL;
        	newNumber->nextPtr=NULL;
			}
            else{
            currentPtr->nextPtr=newNumber;
            newNumber->backPtr=currentPtr;
            newNumber->nextPtr=NULL;
            endPtr2=newNumber;
            currentPtr=newNumber;
			}
			}
        }
    }
    fclose(cfPtr);
	numberPtr temp=NULL;
    numberPtr sStartPtr1=NULL;	
    numberPtr startPtr=NULL;
	numberPtr sEndPtr1=NULL;
	numberPtr endPtr=NULL;
    numberPtr current1 = endPtr1;
    numberPtr current2 = endPtr2;
	int dot1,dot2,dot,dotcheck=0;
	dot2=0;
    numberPtr result1 = malloc(sizeof(number));
    numberPtr result = malloc(sizeof(number));
    result=NULL;
    int multiplication,more,remainder,counter1,counter2=0;
    //multiplies one digit with other linked list and calls sum function.
	while(current2!=NULL){
    	current1=endPtr1;
    	if(current2->value!='.'){
    	while(current1!=NULL){
    		numberPtr result1 = malloc(sizeof(number));
    		if(current1->value!='.'){	
    		multiplication=(current2->value-'0')*(current1->value-'0');
    		multiplication=multiplication+more;
    		more=multiplication/10;
			remainder = multiplication%10;
			result1->value=remainder+'0';
			if(sEndPtr1==NULL){
			sEndPtr1=result1;
			sStartPtr1=result1;
			result1->backPtr=NULL;
			result1->nextPtr=NULL;
			temp=result1;
			}else{
			result1->backPtr=temp;
			result1->nextPtr=NULL;
			temp->nextPtr=result1;
			temp=result1;
			sStartPtr1=result1;
			}
		}else{
			if(dotcheck==0)
			dot+=dot1;
			dotcheck++;
		}
		dot1++;
		current1=current1->backPtr;
		if((current1==NULL) && (more!=0)){
		numberPtr result2 = malloc(sizeof(number));
		result2->value=more+'0';
		result2->nextPtr=NULL;	
		result2->backPtr=sStartPtr1;
		sStartPtr1=result2;
		temp->nextPtr=result2;
		}
		numberPtr startPtr = sStartPtr1;
		}	
		more=0;
		result=sum(sEndPtr1, result);
	change++;
	//keeps the starting pointer of result.
	if(change==2){
	startPtr= result->backPtr;
	}
	freeList(sStartPtr1);	
	sStartPtr1=NULL;
	sEndPtr1=NULL;
	}else{
		dot+=dot2;
	}
	current2=current2->backPtr;
	dot2++;
	}
	numberPtr zerocheck=startPtr;
	int dotcounter=0;
	numberPtr dotptr=malloc(sizeof(number));
	dotptr->value='.';
	numberPtr last;
	//place the dot.
	while(startPtr!=NULL){
		dotcounter++;
		if(dot==dotcounter){
			numberPtr t = startPtr->nextPtr;
			startPtr->nextPtr=dotptr;
			dotptr->nextPtr=t;
			dotptr->backPtr=startPtr;
			t->backPtr=dotptr;
		}
		last=startPtr;
		startPtr=startPtr->nextPtr;
	}
	//deletes the last zeros after the dot and deletes the dot if there is no number after it
	while((zerocheck->value=='0'||zerocheck->value=='.')&&dot!=0){
		numberPtr del=zerocheck;
		zerocheck=zerocheck->nextPtr;
		zerocheck->backPtr=NULL;
		del->nextPtr=NULL;
		free(del);
	}
	while((last->value=='0'&&last->backPtr->value!='.')&&dot!=0){
		numberPtr del=last;
		last=last->backPtr;
		last->nextPtr=NULL;
		del->backPtr=NULL;
		free(del);
	}
	//prints the result
		fprintf(cPtr,"Multiplier: ");
	    while(startPtr1!=NULL){
    	fprintf(cPtr,"%c",startPtr1->value);
    	startPtr1=startPtr1->nextPtr;
	}
		fprintf(cPtr,"\nMultiplicand: ");
	    while(startPtr2!=NULL){
    	fprintf(cPtr,"%c",startPtr2->value);
    	startPtr2=startPtr2->nextPtr;
	}
		fprintf(cPtr,"\nResult: ");
		while(last!=NULL){
		fprintf(cPtr,"%c",last->value);
		last=last->backPtr;
	}
	freeList(last);
	freeList(endPtr1);
	freeList(endPtr2);
	clock_gettime(CLOCK_MONOTONIC, &end_time);
	double time_taken = (end_time.tv_sec - start_time.tv_sec) + 
                        (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    fprintf(cPtr,"\nElapsed time: %f seconds\n", time_taken);
    fclose(cPtr);
	return 0;
	}
