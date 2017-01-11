#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int i,j,k;
void input(int *,int *,int *,int *,char *,int *,int *,long long int *);
void sender(int *,char *, int *);
void receiver(int *,int *,int *,int *,char *,int *,int *,long long int *);

int main()
{
   int bits;
    char ch;
   long  long int m;
   printf("Enter the no. of bits for the sequence no. : ");
   scanf("%d",&bits);
   m=pow(2,bits); 
         int fr_send_at_instance;
         int *arr=(int *)malloc (m*sizeof (int));   //upper layers
         int *send=(int *)malloc (m*sizeof (int));  //sender side
	 int *rcvd=(int *)malloc (m*sizeof (int));  //receiver side
	 char *rcvd_ack=(char *)malloc (m*sizeof (char));  //recever side for ack
	 int sw;
	 int rw;       //tells expected frame
           input(&fr_send_at_instance,arr,send,rcvd,rcvd_ack,&sw,&rw,&m);   //for input
           while(1)
            {
              sender(&fr_send_at_instance,rcvd_ack,send); 
              receiver(&fr_send_at_instance,arr,send,rcvd,rcvd_ack,&sw,&rw,&m);
              printf("One whole window was sent Do You Want to continue for another Window:\n");
              scanf("%c",&ch);
               if(ch=='n')
                {
                  printf("**********Thanks Have a Nice Day**********");
                  break;
                  }
                }
          
           }

   void input(int *fr_send_at_instance,int *arr,int *send,int *rcvd,char *rcvd_ack, int *sw,int *rw,long long int *m )
    {
      int t=0;
      	*fr_send_at_instance=(*m/2);  //setting window size
      
	for( i=0;i<*m;i++)    
	{
		arr[i]=t;
		t=(t+1)% *m;
	}

	for(i=0;i<*fr_send_at_instance;i++)     //sender side aquiring first window data from upper layers
	{
		send[i]=arr[i];
		rcvd[i]=arr[i];
		rcvd_ack[i]='n';
	}

	*rw=*sw=*fr_send_at_instance;   //window size

	
       }

   void sender(int *fr_send_at_instance,char *rcvd_ack ,int *send)
     {
        for( i=0;i<*fr_send_at_instance;i++)     //sending a first window of frames
	{
		if(rcvd_ack[i]=='n')
			
			printf("SENDER:Frame %d is sent",send[i]);
                         printf("\n");
	}
	
     }

  void receiver(int *fr_send_at_instance,int *arr,int *send,int *rcvd,char *rcvd_ack, int *sw,int *rw, long long int *m )
    {
       
	int f;
	int j;
	int f1;
	int a1;
	char ch;
        int j1;
	

	for(i=0;i<*fr_send_at_instance;i++)
	{
		if(rcvd_ack[i]=='n')
		{
			f=rand()%10;  //if f=5 frame is discarded for some reason
				        //else frame is correctly recieved
			 if(f!=5)       //if frame is recived correctly
			{
				for(j=0;j<*fr_send_at_instance;j++)
				if(rcvd[j]==send[i])
				{
					
					printf("reciever:Frame %d recieved correctly",rcvd[j]);printf("\n");
					rcvd[j]=arr[*rw];
					*rw=(*rw+1)%*m;
                                        j1=j;
					break;
				}
 			       
				if(j1==*fr_send_at_instance)   //if exceeds window size
					
				printf("reciever:Dupliocate frame %d discarded",send[i]);printf("\n");
				a1=rand()%5;
				//if al==3 then ack is lost
				//else recieved
				if(a1==3)
				{
					
					printf("acknowledgement %d lost",send[i]);printf("\n");
				
					printf("(sender timeouts-->Resend the frame)");printf("\n");
					rcvd_ack[i]='n';
				}
				else    
				{
					
					printf("(acknoledgement %d recieved)",send[i]);printf("\n");
					rcvd_ack[i]='p';
				}
			}
			else   //here it's sure that frame is currupted 
			{
				int ld=rand()%2;
			 	//if =0 then frame damaged
				 //else frame lost

				if(ld==0)
				{
					
					printf("RECIEVER : Frame %d is damaged",send[i]);printf("\n");
				
					printf("RECIEVER : Negative Acknoledgement %d sent",send[i]);printf("\n");
				}
				else
				{
					
					printf("RECIEVER : Frame %d is lost",send[i]);printf("\n");
					
					printf("(SENDER TIMEOUTS-->RESEND THE FRAME)");printf("\n");
				}
				rcvd_ack[i]='n';
			}
	 	}
	}
	for(j=0;j<*fr_send_at_instance;j++)
	{
		if(rcvd_ack[j]=='n')
			break;
	}

	 i=0;
	for( k=j;k<*fr_send_at_instance;k++)
	{
		send[i]=send[k];
		
		if(rcvd_ack[k]=='n')
			rcvd_ack[i]='n';
		else
			rcvd_ack[i]='p';
		i++;
	}

	if(i!=*fr_send_at_instance)                     //loding next window on sender side according to sequence number from upper layer
	{
		for( k=i;k<*fr_send_at_instance;k++)
		{
			send[k]=arr[*sw];
			*sw=(*sw+1)%*m;
			rcvd_ack[k]='n';
		}
	}
	
    }  








 
    
