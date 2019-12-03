#include"iostream"
#include"stdio.h"
#include"algorithm" 

using namespace std;
#define defaultsize 99

template <typename E> class AQueue
{
    private:
        void operator = (const AQueue&) {} //protect assign operator
        AQueue (const AQueue&) {} //protect copy constructor
        int maxsize; //maxinum number of elements
        int front; //the index of queue's front
        int rear; //the index of queue's rear
        E *listArray; // the array holding the elements

    public:
        AQueue(int size=defaultsize) //initialize the queue
        {
            maxsize=size+1;
            rear=0;
            front=1;
            listArray = new E[maxsize];
        }

        ~AQueue()  //delete iqueue
        {
            delete [] listArray;
        }

        void clear() //reinitialize queue
        {
            rear=0;
            front=1;
        }

        void enqueue (const E& it) //inque
        {
            if((rear+2)%maxsize==front) //circular queue
            {
                cout<<"Queue is full";
                return;
            }

            rear=(rear+1)%maxsize; //circular incresement
            listArray[rear]=it;
        }

        E dequeue () // get out of queue
        {
            if(length()==0) 
            {
                cout<<"Queue is empty";
                return 2;
            }
            E it= listArray[front];
            front=(front+1)%maxsize; //circular incresement
            return it;
        }

        const E& frontvalue() const //return the value of queue's front
        {
             if(length()==0)
            {
                cout<<"Queue is empty";
                return 2;
            }
            return listArray[front];
        }

        const E& rearvalue() const
        {
             if(length()==0)
            {
                cout<<"Queue is empty";
                return 2;
            }
            return listArray[rear];
        }

        int length() const //return the number of elements in the queue
        {
            return ((rear+maxsize)-front+1)%maxsize;  //circular count
        }
};


template <typename E> 
class QStack { //Queue based stack
   private:
        int maxSize;  //maxinum number of elements in the stack
        AQueue<E> QA;  //Queue A
        AQueue<E> QB;  //Queue B
   public:
     QStack(int size = defaultsize): QA(size), QB(size) //initialize the queues
     {
        maxSize = size;
     }

     ~QStack() //destructor: clear the stack
     {
         QA.~AQueue();
         QB.~AQueue();
     }
              
     void clear() //reinitialize the stack
     {
        QA.clear();
        QB.clear();
     }

     void push(const E& it) // push an element into the stack
     {
        if(QA.length()!=0) QA.enqueue(it); //choose A if A is not empty
        else QB.enqueue(it); //choose B if A is empty
     }

     E pop() //pop an element from the stack
     {
		if (QA.length()!=0) { //choose A if A is not empty
			while (QA.length() >= 2) {
				E temp = QA.dequeue();
				QB.enqueue(temp); //delete elements from A, and store them into B, to maintian the elements in the stack
			}
			E temp1 = QA.frontvalue();
			QA.dequeue();
			return temp1;
		}
		else {  //choose B if A is empty
			while (QB.length() >= 2) {
				E temp = QB.dequeue();
				QA.enqueue(temp);//delete elements from B, and store them into A, to maintian the elements in the stack
			}
			E temp1 = QB.frontvalue();
			QB.dequeue();
			return temp1;
		}
     }

     const E& topValue() const //return the element at the top of the stack
     {
         if(QA.length()==0 && QB.length()==0) {cout<<"The stack is empty"; return 2;} //error reporter
         if(QA.length()!=0) //choose A is A is not empty
         {
            return QA.rearvalue(); //return the value in the rear of the queue
         }
         else //choose B is A is empty
         {
            return QB.rearvalue(); //return the value in the rear of the queue
         }
     }

     int length() const  //return the length of the stack
     { 
        if(QA.length()!=0)
            return QA.length(); //directly return the length of the selected queue
        else
            return QB.length();
     }

    void printqstack() //print the elements in the stack (used to test the funcion of the stack)
    {
      if(QA.length()==0 && QB.length()==0) {cout<<"The stack is empty"; return;}
    	E temp;
        QStack s1;
        while(length()!=0)
        {
    	    temp=pop();
            cout<<temp<<endl;
            s1.push(temp);
        }
        while(s1.length()!=0)
        {
            temp=s1.pop();
            push(temp);
        }
    }
};


int main()  //to satisfy the demands of the problem
{  
    int N,k,m;  //the three inputs
    QStack<int> s;   //instantiation of the Qstack
    scanf("%d%d%d",&N,&k,&m);  
    int push[N];  //store the sequence of the elements pushed into the stack
    int pop[N];   //store the sequence of elements to be tested
    for(int i=0;i<N;i++)  
    {  
            push[i]=i+1;  //generate the sequence of the elements pushed into the stack
    }  
    while(m)  
    {  
        for(int i=0;i<N;i++)  
        {  
            scanf("%d",&pop[i]);  //read the sequence of elements to be tested
        }  
        for (int i = 0, j = 0; i <N; i++) {  
            s.push(push[i]);  
            if(s.length()>k) break;  //judge whether the length is overdue
            while (j < N && s.length()!=0 && s.topValue() == pop[j]){  //pop the element if it's same as the top element
                s.pop();  
                j++;  //index of  the sequence of elements to be tested
            }  
        }  
        if(s.length()==0) cout<<'T';  //if all the elements are poped ,then this sequence is valid
        else cout<<'F';  //otherwise it;s not valid
        if(m>1) cout<<endl;  
        m--;  
    }          
   
    getchar();  
    getchar();
    return 0;  
}  
