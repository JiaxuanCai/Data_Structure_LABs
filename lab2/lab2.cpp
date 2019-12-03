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

        const E& frontvalue() const
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

        int length() const
        {
            return ((rear+maxsize)-front+1)%maxsize;
        }
};


template <typename E>
class QStack {
   private:
        int maxSize; 
        AQueue<E> QA;
        AQueue<E> QB;
   public:
     QStack(int size = defaultsize): QA(size), QB(size) //初始化队列
     {
        maxSize = size;
     }

     ~QStack() 
     {
         QA.~AQueue();
         QB.~AQueue();
     }
              
     void clear()
     {
        QA.clear();
        QB.clear();
     }

     void push(const E& it)
     {
        if(QA.length()!=0) QA.enqueue(it);
        else QB.enqueue(it);
     }

     E pop()
     {
		if (QA.length()!=0) {
			while (QA.length() >= 2) {
				E temp = QA.dequeue();
				QB.enqueue(temp);
			}
			E temp1 = QA.frontvalue();
			QA.dequeue();
			return temp1;
		}
		else {
			while (QB.length() >= 2) {
				E temp = QB.dequeue();
				QA.enqueue(temp);
			}
			E temp1 = QB.frontvalue();
			QB.dequeue();
			return temp1;
		}
     }

     const E& topValue() const
     {
         if(QA.length()==0 && QB.length()==0) {cout<<"The stack is empty"; return 2;}
         if(QA.length()!=0)
         {
            return QA.rearvalue();
         }
         else
         {
            return QB.rearvalue();
         }
     }

     int length() const 
     {
        if(QA.length()!=0)
            return QA.length();
        else
            return QB.length();
     }

    void printqstack()
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


int main()
{
    // int N,k,m;
    QStack<int> s;
    // scanf("%d%d%d",&N,&k,&m);
    int N=5,m=120,k=3;
    int push[N];
    int pop[N];

    for(int i=0;i<N;i++)
    {
            push[i]=i+1;
    }

    // while(m)
    // {
        pop[0]=1;
        pop[1]=2;
        pop[2]=3;
        pop[3]=4;
        pop[4]=5;
            // for(int i=0;i<N;i++)
            // {
            //     scanf("%d",&pop[i]);
            // }
        do{      
            for(int i=0; i<N ;i++)
            {
                cout<<pop[i]<<' ';
            }
          
            cout<<endl;
            for (int i = 0, j = 0; i <N; i++) {
                s.push(push[i]);
                 if(s.length()>3) break;
                while (j < N && s.length()!=0 && s.topValue() == pop[j]){
                    s.pop();
                    j++;
                }
            }
            if(s.length()==0) cout<<'T'<<endl;
            else cout<<'F'<<endl;
            s.clear();
            // if(m>1) cout<<endl;
        }while(next_permutation(pop,pop+N));
    //     m--;
    // }        

    getchar();
    getchar();
    return 0;
}
