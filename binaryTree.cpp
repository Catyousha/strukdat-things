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
        pangkal = kiri = kanan = NULL;
    }
};
/*--------          ./BATANG TUBUH BINARY TREE          --------*/


/*--------          SERBA-SERBI BINARY TREE          --------*/

    //-------- TINGGI BINARY TREE --------//
        template <class T>
        int tinggiBT(Tree<T>* tr, int x=0){
            if(tr == NULL){
                return x;
            }
            int a = tinggiBT(tr->kiri, x+1);
            int b = tinggiBT(tr->kanan, x+1);
            
            return (a>b)?a: b;
        }
    //-------- ./TINGGI BINARY TREE --------//

    //-------- LEVEL BINARY TREE --------//
        template <class T>
        int levelBT(Tree<T>* tr, T key){
            Tree<T>* keyNode = searchNode(tr,key);
            if(keyNode == NULL){
                cout<<"Key tidak ditemukan!"<<endl;
                return 0;
            }
            int level = 1;
            while(keyNode->pangkal != NULL){
                keyNode = keyNode->pangkal;
                level++;
            }
            return level;
        }
    //-------- ./LEVEL BINARY TREE --------//

/*--------          ./SERBA-SERBI BINARY TREE          --------*/


/*--------          PENCARIAN BINARY TREE          --------*/

    //-------- RETURN BOOLEAN  --------//
        template <class T>
        bool searchBool(Tree<T>* tr, T x){
            if( tr == NULL){
                return false;
            }
            if(tr->data == x){
                return true;
            }


            return (searchBool(tr->kanan, x) || searchBool(tr->kiri, x));
        }

    //-------- ./RETURN BOOLEAN  --------//

    //-------- RETURN NODE  --------//
        template <class T>
        Tree<T>* searchNode(Tree<T>* tr, T x){
            if( tr == NULL){
                return NULL;
            }
            if(tr->data == x){
                return tr;
            }

            Tree<T>* a = searchNode(tr->kanan,x);
            Tree<T>* b = searchNode(tr->kiri,x);
            
            if(a != NULL){
                return a;
            }
            else if(b != NULL){
                return b;
            }
            else{
                return NULL;
            }

            
        }

    //-------- ./RETURN NODE  --------//

    //-------- RETURN NODE TERAKHIR  --------//
        template <class T>
        Tree<T>* LastNode(Tree<T>* tr, int level, int tinggi){
            if(tr == NULL){
                return NULL;
            }
            if( level == tinggi){
                return tr;
            }

            Tree<T>* a = LastNode(tr->kanan, level+1, tinggi);
            Tree<T>* b = LastNode(tr->kiri, level+1, tinggi);
            
            if(a != NULL){
                return a;
            }
            else if(b != NULL){
                return b;
            }
            else{
                return NULL;
            }

        }
    //-------- ./RETURN NODE TERAKHIR --------//

/*--------          ./PENCARIAN BINARY TREE          --------*/


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

    //-------- INSERT BERDASARKAN KEY --------//
        template <class T>
        void insertOfKey(Tree<T>* tr, T key, T x){
            Tree<T>* keyNode = searchNode(tr, key);
            if(keyNode == NULL){
                cout<<"Key tidak ditemukan!"<<endl;
                return;
            }

            if(keyNode->kiri != NULL){
                keyNode->kanan = new Tree<T>(x);
                keyNode->kanan->pangkal = keyNode;
            }
            else{
                keyNode->kiri = new Tree<T>(x);
                keyNode->kanan->pangkal = keyNode;
            }
        }
    //-------- ./INSERT BERDASARKAN KEY --------//
    
/*--------          ./TAMBAHKAN (INSERT) BINARY TREE          --------*/

/*--------          HAPUS (DELETE) BINARY TREE          --------*/

    //-------- HAPUS DARI POJOK KANAN BAWAH [default] --------//
        template <class T>
        void deleteDefault(Tree<T>* tr){
            Tree<T>* hapus = LastNode(tr, 1, tinggiBT(tr));
            if(hapus == NULL){
                cout<<"Tree kosong!"<<endl;
                return;
            }
            if(hapus->pangkal == NULL){
                tr = NULL; delete tr;
                return;
            }

            hapus = hapus->pangkal;
            if(hapus->kanan == NULL){
                hapus->kiri = NULL; delete hapus->kiri;
            }
            else{
                hapus->kanan = NULL; delete hapus->kanan;
            }
        }
    //-------- ./HAPUS DARI POJOK KANAN BAWAH [default] --------//

    //-------- HAPUS BERDASARKAN KEY --------//
        template <class T>
        void deleteOfKey(Tree<T>* tr, T key){
            Tree<T>* hapus = searchNode(tr, key);
            if(hapus == NULL){
                cout<<"Key tidak ditemukan!"<<endl;
                return;
            }
            if(hapus->pangkal == NULL){
                hapus = NULL; delete hapus;
            }
            else{
                hapus = hapus->pangkal;
                if(hapus->kanan->data == key){
                    hapus->kanan = NULL; delete hapus->kanan;
                }
                else{
                    hapus->kiri = NULL; delete hapus->kiri;
                }
            }

        }
    //-------- ./HAPUS BERDASARKAN KEY --------//


/*--------          ./HAPUS (DELETE) BINARY TREE          --------*/

int main(){
    Tree<int> *a = new Tree<int>(0);
    insertDefault(a, 1);
    insertDefault(a, 2);
    insertDefault(a,3);
    insertDefault(a,4);
    insertDefault(a,5);
    insertDefault(a,6);
    cout<<&a<<endl;
    cout<<&a+1<<endl;
    cout<<"Preorder: "; preorder(a); cout<<endl;
    cout<<"Inorder: "; inorder(a); cout<<endl;
    cout<<"Postorder: "; postorder(a); cout<<endl;
    cout<<"Tinggi BT: "<<tinggiBT(a)<<endl;
    
}
