#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;
template <class H> class Coda {
		private:
			H* v;
			int size;
			int head;
			int tail;
			int len;
		protected:
		public:
			Coda () {
				len=5;
				v=new H (len);
				size=0;
				head=tail=0;
			}
			Coda (int l) {
				len=l;
				v=new H (len);
				size=0;
				head=tail=0;
			}
			Coda<H>* enqueue (H x) {
				if (!isFull()) {
					v[tail]=x;
					tail++;
					size++;
					if (tail==len) tail=0;
					return this;
				}else{
					return NULL;
				}
			}
			H* dequeue () {
				if (!isEmpty ()) {
					int k=head;
					head++;
					size--;
					if (head==len) head=0;
					return &v[k];
				}else{
					return NULL;
				}
			}
			int get_size (){
				return size;
			}
			int isEmpty () {
				return (size==0);
			}
			int isFull () {
				return (size==len);
			}
			void print () {
				int k=head;
				int i=head;
				int c=0;
				do{
					cout<<v[i]<<" "<<endl;
					i++;
					c++;
					if (i==len) i=0;
				}while (i!=k&&c!=size);
			}
};

int main (){
}