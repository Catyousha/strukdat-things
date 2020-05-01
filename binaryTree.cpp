#include <iostream>
#include <iomanip> //buat setprecision doang di rata-rata langkah
using namespace std;

/*--------          BATANG TUBUH BINARY TREE          --------*/
    /*--------------------------------------------------------------------+
    | template digunakan agar lebih fleksibel menggunakan tipedata        |
    | jadi buat deklarasinya bisa menggunakan tipedata apapun             |
    | contohnya kalau tipedata int, dideklarasikan jadi Tree<int>variabel |
    | kalau tipedata char, jadi Tree<char>variabel                        |
    +---------------------------------------------------------------------*/
    template <class T>
    struct Tree{

    /*-----------------------------+
    |          [pangkal]           |
    |              |               |
    |           [Tree]             |
    |          /      \            |
    |       [kiri]  [kanan]        |
    +-----------------------------*/
        T data;
        struct Tree *kiri;
        struct Tree *kanan;
        struct Tree *pangkal;
        
        //constructor dalam inisialisasi binarytree.
        //nilai pada parameter d akan digunakan sebagai pangkal
        //  Ex: Tree<int>*pohon = new Tree<int>(8) <-- 8 sebagai pangkal
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
            //NULL dikatakan sebagai 'jalan buntu'
            //nilai x akan dikembalikan
            if(tr == NULL){
                return x; //x juga dapat diartikan sebagai 'kedalaman'
            }

            /*---------------------------------------------------------------+
            |  Binary tree akan disusuri menurun melewati persimpangan       |
            |  cabang kiri (var a) dan cabang kanan (var b)                  |
            |  setiap menurun 'satu level' nilai x akan bertambah satu       |
            |  dan barulah ketika bertemu 'jalan buntu' / NULL, nilai x      |
            |  akan dikembalikan setelah mengalami penambahan berkali-kali   |
            +---------------------------------------------------------------*/
            int a = tinggiBT(tr->kiri, x+1);
            int b = tinggiBT(tr->kanan, x+1);
            
            // nilai a dan b dibandingkan, mana yang lebih besar / lebih dalam akan ditetapkan sebagai tinggi binary tree
            return (a>b)?a: b;
        }
    //-------- ./TINGGI BINARY TREE --------//

    //-------- LEVEL BINARY TREE --------//
        /*---------------------------------------------------------+
        | Level dapat juga berarti kedalaman                       |
        | fungsi ini mengembalikan nilai pada kedalaman berapa     |
        | data yang dicari (key) dihitung dari puncak binary tree  |
        +---------------------------------------------------------*/
        template <class T>
        int levelBT(Tree<T>* tr, T key){
            // node key akan didapatkan dalam bentuk node keyNode
            Tree<T>* keyNode = searchNode(tr,key);

            //periksa dulu apakah key ada dalam bintree atau kagak
            if(keyNode == NULL){
                cout<<"Key tidak ditemukan!"<<endl;
                return 0;
            }

            int level = 1;

            /*--------------------------------------------------------------------------------------------------------+
            |  bintree akan 'dipanjat' menggunakan looping while sampai ke puncaknya                                  |
            |  dimana puncaknya ditandai dengan tidak memiliki pangkal (tree->pangkal == NULL)                        |
            |  setiap memanjat ke pangkalnya, level akan bertambah 1.                                                 |
            |  jadi menghitung level / kedalaman binary tree ialah dari bawah (node key / keyNode) ke atas (puncak).  |
            +--------------------------------------------------------------------------------------------------------*/
            while(keyNode->pangkal != NULL){
                keyNode = keyNode->pangkal; //panjat
                level++;
            }
            return level;
        }
    //-------- ./LEVEL BINARY TREE --------//

    //-------- BANYAK NODE BINARY TREE --------//
        template <class T>
        int banyakNode(Tree<T>*tr){
            //NULL dikatakan sebagai 'jalan buntu'
            //apabila tembus sampai ke null, kembalikan nilai 0
            if(tr == NULL){
                return 0;
            }

            //posisi node 'mentok', langsung saja kembalikan nilai 1
            if(tr->kanan == NULL && tr->kiri == NULL){
                return 1;
            }
            else{
                //fungsi ini memencar ke cabang kiri dan cabang kanan
                //sementara di node ini bernilai 1 buah node (+1)
                /*-------------------------------------------------------------+
                |                            [pangkal]                         |
                |                               |                              |
                |                              [1]                             |
                |                   /                   \                      |
                |       [banyakNode(tr->kiri)]  [banyakNode(tr->kanan)]        |
                +-------------------------------------------------------------*/
                return banyakNode(tr->kanan) + banyakNode(tr->kiri) + 1;
                //banyakNode(tr->kanan) dapat juga diartikan sebagai jumlah node di cabang kanan
                //begitu pula dengan banyakNode(tr->kiri)
            }
        }
    //-------- ./BANYAK NODE BINARY TREE --------//
    
/*--------          ./SERBA-SERBI BINARY TREE          --------*/


/*--------          PENCARIAN BINARY TREE          --------*/

    //-------- RETURN BOOLEAN  --------//
        template <class T>
        bool searchBool(Tree<T>* tr, T x){
            //kalau bertemu NULL / jalan buntu, kembalikan nilai false
            if( tr == NULL){
                return false;
            }
            //kalau ketemu nilai x, jelas kembalikan nilai true
            if(tr->data == x){
                return true;
            }

            //kembalikan hasil pencarian di cabang kanan dan kiri
            //jika salah satunya bernilai true, kembalikan nilai true (boolean OR)
            return (searchBool(tr->kanan, x) || searchBool(tr->kiri, x));
        }

    //-------- ./RETURN BOOLEAN  --------//

    //-------- RETURN NODE  --------//
        template <class T>
        Tree<T>* searchNode(Tree<T>* tr, T x){
            //kalau bertemu NULL / jalan buntu, kembalikan nilai NULL
            if( tr == NULL){
                return NULL;
            }
            //kalau ketemu nilai x, kembalikan node yang mengandung nilai x
            if(tr->data == x){
                return tr;
            }

            //variabel a dan b menampung hasil pencarian di cabang kanan dan kiri
            Tree<T>* a = searchNode(tr->kanan,x);
            Tree<T>* b = searchNode(tr->kiri,x);
            
            //keduanya dibandingkan, jika mengandung node bernilai x (tidak NULL), kembalikan node tersebut
            //kalau keduanya bernilai NULL, yasudah kembalikan saja nilai NULL
            if(a != NULL){ return a; }
            else if(b != NULL){ return b; }
            else{ return NULL; }

        }

    //-------- ./RETURN NODE  --------//

    //-------- RETURN NODE TERAKHIR  --------//
        template <class T>
        Tree<T>* LastNode(Tree<T>* tr, int level, int tinggi){
            //kalau bertemu NULL / jalan buntu, kembalikan nilai NULL
            if(tr == NULL){
                return NULL;
            }

            //kalau level sudah sampai kedalaman maksimal / level = tinggi
            //kembalikan saja node saat ini, tidak peduli bernilai apa.
            if( level == tinggi){
                return tr;
            }

            //variabel a dan b menampung node 'galian' di cabang kanan dan kiri.
            //tiap 'menuruni' cabang, level bertambah 1
            Tree<T>* a = LastNode(tr->kanan, level+1, tinggi);
            Tree<T>* b = LastNode(tr->kiri, level+1, tinggi);
            
            //kalau dari cabang kanan maupun kiri sudah pada kedalaman maksimal dan tidak NULL,
            //prioritaskan kembalikan node sebelah kanan (variabel a)
            if(a != NULL){ return a; }
            else if(b != NULL){ return b; }
            else{ return NULL; }

        }
    //-------- ./RETURN NODE TERAKHIR --------//

    //-------- RETURN JUMLAH LANGKAH PENCARIAN --------//
        /*anggapan yang dicari ada dan bersifat tunggal*/
        template <class T>
        int searchLangkah(Tree<T>*tr, T x){
            //kalau tembus ke NULL / jalan buntu, kembalikan nilai -9999
            //-9999 digunakan untuk mengurangi jumlah langkah yang telah didapatkan melalui jalur hingga sampai kesini
            //   atau bisa disebut juga buat hapus jejak.
            if(tr == NULL){
                return -9999;
            }

            //kalau ketemu node yang mengandung nilai x, kembalikan nilai 1
            if(tr->data == x){
                return 1;
            }

            //variabel a dan b menampung jumlah langkah yang dilalui untuk mencari nilai x
            //tiap 'menuruni' cabang, jumlah langkah akan bertambah 1
            int a = searchLangkah(tr->kanan,x) + 1; //turun ke cabang kanan
            int b = searchLangkah(tr->kiri,x) + 1; //turun ke cabang kiri

            //kembalikan jumlah langkah terbesar untuk menemukan x
            //salah satu dari a atau b pasti bernilai negatif karena jalur yang salah akan mengembalikan nilai -9999
            return (a>b)?a: b;
        }
        /*mirip fungsi nyari level sih tapi versi rekursif wkwkwk...*/
    //-------- ./RETURN JUMLAH LANGKAH PENCARIAN --------//

    //-------- RETURN TOTAL LANGKAH PENCARIAN --------//
        template <class T>
        int totalLangkah(Tree<T>*tr, int langkah = 1){
            //kalau tembus ke NULL / jalan buntu, kembalikan nilai 0
            if(tr == NULL){
                return 0;
            }

            //variabel a dan b menyimpan nilai total langkah yang ditempuh menuju cabang kanan dan kiri
            int a = totalLangkah(tr->kanan, langkah+1);
            int b = totalLangkah(tr->kiri, langkah+1);

            //kembalikan nilai:
            // (jumlah langkah untuk mencapai node ini) + (jumlah langkah pada cabang kanan) + (jumlah langkah pada cabang kiri)
            return langkah + a + b;
        }
    //-------- ./RETURN TOTAL LANGKAH PENCARIAN --------//

    //-------- RETURN RATA-RATA LANGKAH PENCARIAN --------//
        template <class T>
        float rataLangkah(Tree<T>*tr){
            //menggunakan tipe data float agar bernilai desimal
            float total = totalLangkah(tr);
            float banyak = banyakNode(tr);
            
            //rumus rata-rata: total/banyak (yaiyalah)
            return total/banyak;
        }
    //-------- ./RETURN RATA-RATA LANGKAH PENCARIAN --------//

/*--------          ./PENCARIAN BINARY TREE          --------*/


/*--------          TAMPILKAN BINARY TREE          --------*/

    //-------- PREORDER TRAVERSAL --------//
        template <class T>
        void preorder(Tree<T>* temp){
            /*-----------------------------+
            |           [2]                |
            |          /   \               |
            |       [1]    [3]             |
            +-----------------------------*/
            //pangkal - kiri - kanan
            //2-1-3
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
            /*-----------------------------+
            |           [2]                |
            |          /   \               |
            |       [1]    [3]             |
            +-----------------------------*/
            //kiri - pangkal - kanan
            //1-2-3
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
            /*-----------------------------+
            |           [2]                |
            |          /   \               |
            |       [1]    [3]             |
            +-----------------------------*/
            //kiri-kanan-pangkal
            //1-3-2
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

            //tampilkan data pada node saat ini serta jumlah langkah yang sudah ditempuh
            cout<<tr->data<<" = "<<langkah<<" langkah"<<endl;
            
            //setiap menuruni cabang, langkah akan bertambah 1
            tampilLangkah(tr->kiri, langkah+1);
            tampilLangkah(tr->kanan, langkah+1);
        }
    //-------- ./KESELURUHAN LANGKAH PENCARIAN --------//

/*--------          ./TAMPILKAN BINARY TREE          --------*/


/*--------          TAMBAHKAN (INSERT) BINARY TREE          --------*/

    //-------- INSERT DARI KIRI KE KANAN (KAYAK NULIS) [default] --------//
        template <class T>
        void insertDefault(Tree<int>*tr,T d){

            //kalau berada pada node mentok (tidak memiliki cabang lagi),
            //  isi cabang sebelah kiri dengan data baru
            if(tr->kiri == NULL && tr->kanan == NULL){
                tr->kiri = new Tree<int>(d);
                tr->kiri->pangkal = tr;
            }

            //tapi kalau yang sebelah kiri itu ada isinya, yasudah isi cabang sebelah kanan
            else if(tr->kiri != NULL && tr->kanan == NULL){
                tr->kanan = new Tree<int>(d);
                tr->kanan->pangkal = tr;
            }

            //kalau tidak berada pada node mentok
            else{
                //jika kondisi seperti ini:
                /*--------------------------------+
                |               [node skrg]       |
                |                  /              |
                |             [ada isi]           |
                |             /      \            |
                |       [ada isi]  [ada isi]      |
                +--------------------------------*/
                //maka telusuri ke cabang sebelah kanan dari node skrg
                if(tr->kiri->kiri != NULL && tr->kiri->kanan != NULL){
                    insertDefault(tr->kanan,d);
                }

                //tapi kalau kayak gini:
                /*--------------------------------+            /*--------------------------------+
                |               [node skrg]       |            |               [node skrg]       |
                |                  /              |            |                  /              |
                |             [ada isi]           |     atau   |             [ada isi]           |
                |             /      \            |            |             /        \          |
                |        [NULL]    [NULL]         |            |        [ada isi]    [NULL]      |
                +---------------------------------+            +--------------------------------*/
                                                            //dan sebaliknya
                //maka telusuri ke cabang sebelah kiri dari node skrg
                else{
                    insertDefault(tr->kiri,d);
                }
            }
        }
    //-------- ./INSERT DARI KIRI KE KANAN (KAYAK NULIS) [default] --------//

    //-------- INSERT BERDASARKAN KEY --------//
        //key dapat berarti acuan.
        template <class T>
        void insertOfKey(Tree<T>* tr, T key, T x){
            
            //periksa nilainya ada apa kaga, biar ga ngebug pas di fungsi insertOfKey
            Tree<T> *check = searchNode(tr, x);
            if(check !=NULL){
                cout<<"Nilai sudah ada dalam binary tree!"<<endl;
                return;
            }
            
            //kalau key / acuan tidak ditemukan, jelas tidak bisa dilakukan penambahan
            Tree<T>* keyNode = searchNode(tr, key);
            if(keyNode == NULL){
                cout<<"Key tidak ditemukan!"<<endl;
                return;
            }
            
            //data yang akan ditambahkan diprioritaskan untuk diletakkan pada cabang kiri dengan key sebagai pangkal
            //kalau cabang kiri pada key penuh, alihkan ke cabang kanan
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
            
            //nilai x dibandingkan dengan nilai pada node ini
            //kalau lebih kecil, alihkan ke cabang sebelah kiri
            if(x < tr->data){
                //kalau sebelah kiri penuh, telusuri node sebelah kiri tersebut
                //sehingga nilai yang akan ditambahkan akan menjadi anak dari tr->kiri
                if(tr->kiri != NULL){
                    insertBanding(tr->kiri, x);
                }
                else{
                    tr->kiri = new Tree<T>(x);
                    tr->kiri->pangkal = tr;
                }
            }
            //kalau lebih besar, alihkan ke cabang sebelah kanan
            else{
                if(tr->kanan != NULL){
                    //kalau sebelah kanan penuh, telusuri node sebelah kanan tersebut
                    //sehingga nilai yang akan ditambahkan akan menjadi anak dari tr->kanan
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
            //dapakan node terakhir dari fungsi LastNode
            Tree<T>* hapus = LastNode(tr, 1, tinggiBT(tr));

            //kalau node terakhir ga ada / binary treenya kosong
            if(hapus == NULL){
                cout<<"Tree kosong!"<<endl;
                return;
            }
            
            //kalau pangkal dari node terakhir bernilai NULL / puncak, langsung delete binary treenya
            if(hapus->pangkal == NULL){
                tr = new Tree<int>(NULL); delete tr;
                return;
            }

            //beralih ke pangkal dari node terakhir
            hapus = hapus->pangkal;

            //kalau yang disebelah kanan kosong / NULL, berarti yang disebelah kiri itu node terakhir
            //dan karena yang mau dihapus itu node terakhir, ya hapus cabang kiri
            if(hapus->kanan == NULL){
                hapus->kiri = NULL; delete hapus->kiri;
            }
            else{
                //sebaliknya, hapus cabang kanan yang merupakan node terakhir
                hapus->kanan = NULL; delete hapus->kanan;
            }
        }
    //-------- ./HAPUS DARI POJOK KANAN BAWAH [default] --------//

    //-------- HAPUS BERDASARKAN KEY --------//
        template <class T>
        void deleteOfKey(Tree<T>* tr, T key){
            //hampir sama seperti fungsi deleteDefault
            //hanya saja yang menjadi acuan adalah key yang ingin dihapus itu sendiri
            Tree<T>* hapus = searchNode(tr, key);

            if(hapus == NULL){
                cout<<"Key tidak ditemukan!"<<endl;
                return;
            }

            if(hapus->pangkal == NULL){
                tr = new Tree<int>(NULL); delete tr;
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

/*--------------------------------------------------------------------+
|   95% kodingan murni milik pribadi [jak]                            |
|   2.5% dari geeksforgeeks (konsep templates & bintree)              |
|   2.5% dari stackoverflow <3 (pengaplikasian templates pada bintree)|
+--------------------------------------------------------------------*/
