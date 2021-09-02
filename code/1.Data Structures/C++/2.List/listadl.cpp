#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;

template <class T> class Node {
		private:
			T* key;
			Node<T>* prev;
			Node<T>* next;
		protected:
		public:
			Node (T* key) {
				this->key=NULL;
				if (key) this->key=new T (*key);
				prev=next=NULL;
			}
			Node (T* key,Node<T>* next) {
				this->key=NULL;
				if (key) this->key=new T (*key);
				this->next=next;
				prev=NULL;
			}
			Node (T* key,Node<T>* next,Node<T>* prev) {
				this->key=NULL;
				if (key) this->key=new T (*key);
				this->next=next;
				this->prev=prev;
			}
			T getKey () {
				return *key;
			}
			T* getK () {
				return new T (*key);
			}
			Node<T>* getNext () {
				return next;
			}
			Node<T>* getPrev () {
				return prev;
			}
			void setKey (T key) {
				this->key=key;
			}
			void setNext (Node<T>* next) {
				this->next=next;
			}
			void setPrev (Node<T>* prev) {
				this->prev=prev;
			}
};

template <class T> class Listadl {
	private:
		int n;
		Node<T>* header;
		Node<T>* trailer;
		Node<T>* current;
		void insertAfter (Node<T>* tmp,T x) {
				Node<T>* f=new Node<T> (&x,tmp->getNext(),tmp);
				f->getNext()->setPrev (f);
				tmp->setNext (f);
				n++;
		}
		Node<T>* search (T x) {
			Node<T>* a=header->getNext ();
			while (a!=trailer) {
				if (a->getKey()==x) return a;
				a=a->getNext();
			}
			return NULL;
		}
		Node<T>* search_max (T x) {
			Node<T>* d=header->getNext();
			while (d!= trailer) {
				if (d->getKey()>=x) return d;
				d=d->getNext();
			}
			return NULL;
		}
		void ord (T x) {
			Node<T>* m=search_max (x);
			if (m) {
				Node<T>* nd=new Node<T> (&x,m,m->getPrev());
				m->setPrev (nd);
				nd->getPrev()->setNext (nd);
			}else{
				insertAfter (trailer->getPrev(),x);
			}
			n++;
		}
	protected:
	public:
		Listadl () {
			n=0;
			trailer=new Node<T> (NULL);
			header=new Node<T> (NULL,trailer);
			trailer->setPrev (header);
			current=trailer;
		}
		Listadl<T>* ins_in_testa (T x) {
			insertAfter (header,x);
			return this;
		}
		Listadl<T>* ins_in_coda (T x) {
			insertAfter (trailer->getPrev(),x);
			return this;
		}
		Listadl<T>* ins (T x) {
			return ins_in_testa (x);
		}
		Listadl<T>* ins_ord (T x) {
			ord (x);
			return this;
		}
		Listadl<T>* canc (T x) {
			Node<T>* tmp=search (x);
			if (!tmp) return this;
			tmp->getPrev()->setNext (tmp->getNext());
			tmp->getNext()->setPrev (tmp->getPrev());
			delete tmp;
			n--;
			return this;
		}
		int find (T x) {
			return ((search (x))!=NULL);
		}
		int get_Size () {
			return n;
		}
		int isEmpty () {
			return (n==0);
		}
		void print () {
			Node<T>* d=header->getNext();
			cout<<endl;
			cout<<endl;
			while (d!=trailer) {
				if (d->getNext ()==trailer) {
					cout<<d->getKey();
				}else{
					cout<<d->getKey()<<"-";
				}
				d=d->getNext();
			}
			cout<<endl;
			cout<<endl;
		}
		T* begin () {
			current=header->getNext();
			if (current!=trailer) return current->getK();
			return NULL;
		}
		int hasNext () {
			return (current!=trailer && current->getNext ()!=trailer);
		}	
		T* next () {
			if (hasNext ()) {
				current=current->getNext();
				return current->getK();
			}
			return NULL;
		}
};	

int main (){
}
