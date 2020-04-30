#include <iostream>
#include <iomanip> //buat setprecision doang di rata-rata langkah
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

    //-------- BANYAK NODE BINARY TREE --------//
        template <class T>
        int banyakNode(Tree<T>*tr){
            if(tr == NULL){
                return 0;
            }

            if(tr->kanan == NULL && tr->kiri == NULL){
                return 1;
            }
            else{
                return banyakNode(tr->kanan) + banyakNode(tr->kiri) + 1;
            }
        }
    //-------- ./BANYAK NODE BINARY TREE --------//
    
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

    //-------- RETURN JUMLAH LANGKAH PENCARIAN --------//
        /*anggapan yang dicari ada*/
        template <class T>
        int searchLangkah(Tree<T>*tr, T x){
            if(tr == NULL){
                return -9999;
            }

            if(tr->data == x){
                return 1;
            }

            int a = searchLangkah(tr->kanan,x) + 1;
            int b = searchLangkah(tr->kiri,x) + 1;

            return (a>b)?a: b;
        }
        /*mirip fungsi nyari level sih tapi versi rekursif wkwkwk...*/
    //-------- ./RETURN JUMLAH LANGKAH PENCARIAN --------//

    //-------- RETURN TOTAL LANGKAH PENCARIAN --------//
        template <class T>
        int totalLangkah(Tree<T>*tr, int langkah = 1){
            if(tr == NULL){
                return 0;
            }
            int a = totalLangkah(tr->kanan, langkah+1);
            int b = totalLangkah(tr->kiri, langkah+1);

            return langkah + a + b;
        }
    //-------- ./RETURN TOTAL LANGKAH PENCARIAN --------//

    //-------- RETURN RATA-RATA LANGKAH PENCARIAN --------//
        template <class T>
        float rataLangkah(Tree<T>*tr){
            float total = totalLangkah(tr);
            float banyak = banyakNode(tr);

            return total/banyak;
        }
    //-------- ./RETURN RATA-RATA LANGKAH PENCARIAN --------//

/*--------          ./PENCARIAN BINARY TREE          --------*/


/*--------          TAMPILKAN BINARY TREE          --------*/

    //-------- PREORDER TRAVERSAL --------//
        template <class T>
        void preorder(Tree<T>* temp){

            if(temp == NULL)
            return;

            cout<<temp->data<<" ";
            preorder(temp->kiri);    
            preorder(temp->kanan);
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

    //-------- KESELURUHAN LANGKAH PENCARIAN --------//
        //trStart = trCheck ketika di fungsi main!
        //ditampilin sama kayak preorder transversal
        template <class T>
        void tampilLangkah(Tree<T>*tr, int langkah = 1){
            if(tr == NULL){
                return;
            }
            cout<<tr->data<<" = "<<langkah<<" langkah"<<endl;
            tampilLangkah(tr->kiri, langkah+1);
            tampilLangkah(tr->kanan, langkah+1);
        }
    //-------- ./KESELURUHAN LANGKAH PENCARIAN --------//

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
            /*
            //periksa nilainya ada apa kaga, biar ga ngebug pas di fungsi insertOfKey
            Tree<T> *check = searchNode(tr, x);
            if(check !=NULL){
                cout<<"Nilai sudah ada dalam binary tree!"<<endl;
                return;
            }
            */
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
    
    //-------- INSERT SESUAI PERBANDINGAN --------//
        /*yang lebih gede dari pangkal taruh di sebelah kanan
        yang lebih kecil dari pangkal taruh di sebelah kiri */
        template <class T>
        void insertBanding(Tree<T>* tr, T x){
            /*
            //periksa nilainya ada apa kaga, biar ga ngebug pas di fungsi insertOfKey
            Tree<T> *check = searchNode(tr, x);
            if(check !=NULL){
                cout<<"Nilai sudah ada dalam binary tree!"<<endl;
                return;
            }*/

            if(x < tr->data){
                if(tr->kiri != NULL){
                    insertBanding(tr->kiri, x);
                }
                else{
                    tr->kiri = new Tree<T>(x);
                    tr->kiri->pangkal = tr;
                }
            }
            else{
                if(tr->kanan != NULL){
                    insertBanding(tr->kanan, x);
                }
                else{
                    tr->kanan = new Tree<T>(x);
                    tr->kanan->pangkal = tr;
                }
            }
        }
    //-------- ./INSERT SESUAI PERBANDINGAN --------//

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
    cout<<"Masukkan nilai pangkal: ";
    int x; cin>>x;
    Tree<int> *a = new Tree<int>(x);

    cout<<"Masukkan banyak nilai: ";
    int n; cin>>n;

    while(n--){
        int i; cin>>i;
        insertBanding(a,i);
    }

    cout<<"Banyak Node: "<<banyakNode(a)<<endl;
    //cout<<"Preorder: "; preorder(a); cout<<endl;
    //cout<<"Inorder: "; inorder(a); cout<<endl;
    //cout<<"Postorder: "; postorder(a); cout<<endl;
    cout<<"Tinggi BT: "<<tinggiBT(a)<<endl;
    tampilLangkah(a);
    cout<<"Rata-Rata Langkah Pencarian: "<<setprecision(3)<<rataLangkah(a)<<endl;
}
