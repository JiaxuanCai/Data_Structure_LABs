#include "iostream"
#include "stdio.h"
#include "algorithm"
using namespace std;

class Rational{   //a class denoting a rational number
friend bool operator<(const Rational& r1, const Rational& r2) //overload operators
   {
      return(r1.N*r2.D<r2.N*r1.D);
   }
friend bool operator<=(const Rational& r1, const Rational& r2) 
   {
      return(r1.N*r2.D<=r2.N*r1.D);
   }
friend bool operator>(const Rational& r1, const Rational& r2)
   {
      return(r1.N*r2.D>r2.N*r1.D);
   }
friend bool operator>=(const Rational& r1, const Rational& r2) 
   {
      return(r1.N*r2.D>=r2.N*r1.D);
   }
friend bool operator==(const Rational& r1, const Rational& r2)
   {
      return(r1.N*r2.D==r2.N*r1.D);
   }
friend bool operator!=(const Rational& r1, const Rational& r2) 
   {
      return(r1.N*r2.D!=r2.N*r1.D);
   }

public:
   int N; //Numerator , required to be positive value
   int D; //Denominator , required to be positive value
   
   Rational() 
   {
      N=0;
      D=1;
   }  //default constructor
   Rational(int n)
   {
      N=n;
      D=1;
   } //constructor for integer value
   Rational(int n, int d) 
   {
      N=n;
      D=d;
   } //normal constructor
   Rational(const Rational& r)
   {
      D=r.D;
      N=r.N;
   } //copy constructor
   Rational& operator=(const Rational& r)
   {
      N=r.N;
      D=r.D;
      return *this;
   } // assignment override
};


class heap{
   private:
      Rational* Heap; //Physical place to store the rationals
      int maxsize; //the maxinum number of rationals the heap can hold
      int n; //current number of elements in the heap

      void siftdown(int pos) // to sift down a rational to the place it deserves and form a heap structure
      {
         while(!isLeaf(pos))//if the rational reaches the leaf, then put it in this place
         {
            int j=leftchild(pos); 
            int rc=rightchild(pos); //assume the rightchild to be smaller
            if((rc<n) && Heap[rc]<Heap[j]) //to justify whether the leftchild is smaller
               j=rc;
            if(Heap[pos]<Heap[j]) //satisfy the structure of a heap , return.
               return;
            swap(Heap[pos],Heap[j]); //else, change the place of pos and its smaller child
            pos=j;
         }
      }

      void siftup(int pos) // to sift up a rational to the place it deserves adn form a heap structure
      {
         while((pos!=0) && Heap[pos]<Heap[parent(pos)]) //to satisfy the basic needs
         {
            swap(Heap[pos],Heap[parent(pos)]); //change the pos and its parent
            pos=parent(pos); //also change the index
         }
      }

   public:
      heap(Rational* h, int num, int max) //constructor
      {
         Heap=h; 
         n=num; 
         maxsize=max;
         buildHeap(); //call buildheap to initialize the heap structure
      }

      int size() const //return the number of elements of the heap
      {
         return n;
      }

      bool isLeaf(int pos) const // to justify whether the node is a leafnode
      {
         return ((pos>=n/2) && (pos<n));
      }

      int leftchild(int pos) const //return the index of leftchild
      {
         return 2*pos+1;
      }

      int rightchild(int pos) const //return the index of rightchild
      {
         return 2*pos+2;
      }
   
      int parent(int pos) const // return the index of parent
      {
         return (pos-1)/2;
      }

      void buildHeap() //initializing heap
      {
         for(int i=n/2-1; i>=0; i--)
         {
            siftdown(i); //sift down all the way
         }
      }

      void insert(const Rational& it) //insert a rational to the heap, maintaining the heap structure
      {
         if(n>=maxsize){cout<<"The heap is full!"; return;} //whether heap is full
         int curr=n++; //set the index to be the last rational
         Heap[curr]=it; //put the rational to be inserted into the last place
         siftup(curr); //sift the rational all the way up to its deserved place
      }

      Rational removefirst() // remove the rational form the top of the heap
      {
         if(n<=0){cout<<"The heap is empty"; return NULL;} //whether heap is empty
         swap(Heap[0], Heap[--n]); //put the first rational into the last place and let n decrease
         if(n!=0) siftdown(0); // sift down the first element
         return Heap[n];
      }

      void printarray() // print the physical order of the heap
      {
         for(int i=0;i<n;i++) //iterate through the physical place of heap
         {
            if(Heap[i].N%Heap[i].D==0) // if the dinominator can divide the numerator, print the result of an integer
            {
               cout<<Heap[i].N/Heap[i].D;
               if(i!=n-1) cout<<' '<<' '; // print two spaces
            }
            else // if the rational is a fraction
            {
               if(__gcd(Heap[i].N,Heap[i].D)==1) //if the fraction can't be simplified , print it out
                  {
                     cout<<Heap[i].N<<'/'<<Heap[i].D;
                     if(i!=n-1) cout<<' '<<' ';
                  }
               else
                  { // if the fraction can be simplified, simplify it and then print it out.
                     int N1=Heap[i].N/__gcd(Heap[i].N,Heap[i].D); 
                     int D1=Heap[i].D/__gcd(Heap[i].N,Heap[i].D); 
                     cout<<N1<<'/'<<D1; 
                     if(i!=n-1) cout<<' '<<' ';
                  }
            }
         }
      }



      void printsort() //print out the sorted order of the heap
      {
         Rational rs[n]; //this array of Rational is to store the rational removed from the heap top
         int number=n; //store the current number of rationals in the heap
         for(int i=0;i<number ;i++)//iterate through the heap
         {
            Rational temp; //to store the deleted top value 
            temp=removefirst(); 
            rs[i]=temp; // store this rational into the array
            if(temp.N%temp.D==0) // if the dinominator can divide the numerator, print the result of an integer
            {
               cout<<temp.N/temp.D;
               if(i!=number -1) cout<<' '<<' ';
            }
            else// if the rational is a fraction
            {
               if(__gcd(temp.N,temp.D)==1) //if the fraction can't be simplified , print it out
                  {
                     cout<<temp.N<<'/'<<temp.D;
                     if(i!= number-1) cout<<' '<<' ';
                  }
               else // if the fraction can be simplified, simplify it and then print it out.
                  {
                     int N1=temp.N/__gcd(temp.N,temp.D);
                     int D1=temp.D/__gcd(temp.N,temp.D);
                     cout<<N1<<'/'<<D1;
                     if(i!=number -1) cout<<' '<<' ';
                  }
            }
         }
         for(int i=0;i<number ;i++) insert(rs[i]); //put the rationals back into the heap
      }
};



int main()
{

   int n;
   scanf("%d",&n); // the number of elements in the test case
   Rational h[n]; // the array holding the elements

   for(int i=0;i<n;i++) // read the input elements
   {
      int temp1,temp2;
      scanf("%d %d",&temp1,&temp2);
      Rational temp(temp1,temp2);
      h[i]=temp;
   }

   heap heap(h,n,n); //construct a heap called 'heap'

   heap.printarray(); // print the physical order of the heap
   cout<<' '<<' '<<endl;
   heap.printsort(); //print the sorted order of the heap

   getchar();
   getchar();
   return 0;

}