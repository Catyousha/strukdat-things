#include <iostream>
using namespace std;

/*--------          BATANG TUBUH BINARY TREE          --------*/
template <class T>
struct Tree{
    T data;
    struct Tree *kiri;
    struct Tree *kanan;
    struct Tree *pangkal;

    Tree (T d){
        data = d;
        kiri = kanan = NULL;
    }
    void tambahCabang(T d);
};
/*--------          ./BATANG TUBUH BINARY TREE          --------*/


/*--------          SERBA-SERBI BINARY TREE          --------*/

    //-------- TINGGI BINARY TREE --------//
    template <class T>
    int tinggiBT(Tree<T>* tr, int x){
        if(tr == NULL){
            return x;
        }
        int a = tinggiBT(tr->kiri, x+1);
        int b = tinggiBT(tr->kanan, x+1);
        
        return (a>b)?a: b;
    }
    //-------- ./TINGGI BINARY TREE --------//

    
/*--------          ./SERBA-SERBI BINARY TREE          --------*/


/*--------          TAMPILKAN BINARY TREE          --------*/

    //-------- PREORDER TRAVERSAL --------//
        template <class T>
        void preorder(Tree<T>* temp){

            if(temp == NULL)
            return;

            cout<<temp->data<<" ";
            preorder(temp->kiri);    
            inorder(temp->kanan);
        }
    //-------- ./PREORDER TRAVERSAL --------//

    //-------- INORDER TRAVERSAL --------//
        template <class T>
        void inorder(Tree<T>* temp){

            if(temp == NULL)
            return;

            inorder(temp->kiri);
            cout<<temp->data<<" ";
            inorder(temp->kanan);
        }
    //-------- ./INORDER TRAVERSAL --------//

    //-------- POSTORDER TRAVERSAL --------//
        template <class T>
        void postorder(Tree<T>* temp){

            if(temp == NULL)
            return;

            postorder(temp->kiri);
            postorder(temp->kanan);
            cout<<temp->data<<" ";
        }
    //-------- ./POSTORDER TRAVERSAL --------//

/*--------          ./TAMPILKAN BINARY TREE          --------*/


/*--------          TAMBAHKAN (INSERT) BINARY TREE          --------*/

    //-------- INSERT DARI KIRI KE KANAN (KAYAK NULIS) [default] --------//
        template <class T>
        void insertDefault(Tree<int>*tr,T d){
            if(tr->kiri == NULL && tr->kanan == NULL){
                tr->kiri = new Tree<int>(d);
                tr->kiri->pangkal = tr;
            }
            else if(tr->kiri != NULL && tr->kanan == NULL){
                tr->kanan = new Tree<int>(d);
                tr->kanan->pangkal = tr;
            }
            else{
                if(tr->kiri->kiri != NULL && tr->kiri->kanan != NULL){
                    insertDefault(tr->kanan,d);
                }
                else{
                    insertDefault(tr->kiri,d);
                }
            }
        }
        //-------- ./INSERT DARI KIRI KE KANAN (KAYAK NULIS) [default] --------//

/*--------          ./TAMBAHKAN (INSERT) BINARY TREE          --------*/



int main(){
    Tree<int> *a = new Tree<int>(0);
    insertDefault(a, 1);
    insertDefault(a, 2);
    insertDefault(a,3);
    insertDefault(a,4);
    insertDefault(a,5);
    
    cout<<"Preorder: "; preorder(a); cout<<endl;
    cout<<"Inorder: "; inorder(a); cout<<endl;
    cout<<"Postorder: "; postorder(a); cout<<endl;
    cout<<"Tinggi BT: "<<tinggiBT(a,0)<<endl;
}
