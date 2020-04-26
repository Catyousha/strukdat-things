#include <iostream>
#include <iomanip>
#include <sstream>
#define MAX_SIZE 10
using namespace std;

template <class tipedata>
class Stack{
    int top;
    
public:
    tipedata data[MAX_SIZE];
    Stack() { top = -1;}
    bool push(tipedata x);
    tipedata pop();
    tipedata peek();
    bool cekPenuh();
    void showStack();
};

template <class tipedata>
bool Stack<tipedata>::cekPenuh(){
    return (top == MAX_SIZE-1)?1:0;
}

template <class tipedata>
void Stack<tipedata>::showStack(){
    int show = top;
    int emptyVoid = MAX_SIZE-1;

        cout<<setfill('-')<<"+"<<setw(10)<<"+"<<endl;
        cout<<"|"<<"  Stack  "<<"|"<<endl;
        cout<<setfill('-')<<"+"<<setw(10)<<"+"<<endl;
    while(emptyVoid > top){
        cout<<setfill(' ')<<"|"<<setw(10)<<"|"<<endl;
        emptyVoid--;
    }
    while(show != -1){
        cout<<setfill(' ')<<"|    "<<data[show]<<setw(5)<<"|"<<endl;
        show--;
    }
    cout<<setfill('-')<<"+"<<setw(10)<<"+"<<endl;
}

template <class tipedata>
bool Stack<tipedata>::push(tipedata x){
    if(top>= (MAX_SIZE-1)){
        cout<<"Stack sudah penuh"<<endl;
        return false;
    }
    else{
        data[++top] = x;
        return true;
    }
}

template <class tipedata>
tipedata Stack<tipedata>::pop(){
    if(top < 0){
        cout<<"Stack ini tidak memiliki isi!"<<endl;
        exit(EXIT_FAILURE);
    }
    else{
        return data[top--];
    }
}

template <class tipedata>
tipedata Stack<tipedata>::peek(){
    if(top>-1){
        return data[top];
    }
    else{
        exit(EXIT_FAILURE);
    }
    
}

//scientific calc
int strToInt(string x){
    stringstream num(x);
    int n = 0;
    num >> n;
    return n;
}

int tier(char x){
    if(x == '^'){
        return 4;
    }
    else if(x == '*' || x == '/'){
        return 3;
    }
    else if(x == '+' || x=='-'){
        return 2;
    }
    else{
        return 1;
    }
}

string infixToPostfix(string x){
    Stack<char>op; op.push('X');
    string exp;

    for(int i=0; i<x.length(); i++){
        //kalau angka, langsung masuk
        if(x[i]>='0' && x[i]<='9'){
            exp+=x[i];
        }

        //kalau (, tampung di stack
        else if(x[i] == '('){
            op.push('(');
        }

        //kalau ketemu ), masuk ke operasi
        else if(x[i] == ')'){

            //cari di tumpukan sampai ketemu ( atau X
            while(op.peek() != 'X' && op.peek() !='('){
                //satu persatu operator ditelusuri sampai kebawah
                //operator tsb dimasukkan kedalam output postfix
                //sambil dihapus dari stack op
                char c = op.peek();
                op.pop();
                exp+=' ';
                exp+=c;
            }
            if(op.peek() == '('){
                //kalau malah langsung ketemu ), hapus langsung
                //ga guna kalau ekspresinya cuma ()
                char c = op.peek();
                op.pop();
            }
            exp+=' ';
        }

        else{
            //telusuri juga sampai ketemu X atau yang tiernya lebih besar dari op yang discan
            /*---------
            |    +    |    misalkan operator yang discan ialah *
            |    ^    |    maka + akan masuk kedalam notasi dan dihapus dari stack
            ---------*/
            while(op.peek() != 'X' && tier(x[i]) <= tier(op.peek())){
                char c = op.peek();
                op.pop();
                exp+=' ';
                exp+=c;
            }
            op.push(x[i]);
            /*---------
            |    *    |    dan * akan dipush kedalam stack
            |    ^    |    sehingga stack akan menjadi sebagai berikut
            ---------*/
            exp+=' ';
        }
    }

    //operator yang masih ada di stack akan di hapus dan dimasukkan kedalam postfix satu persatu
    while(op.peek() != 'X'){
        char c= op.peek();
        op.pop();
        exp+=' ';
        exp+=c;
    }

    return exp;
    
}

void doTheMath(string x){
    Stack<int>num;
    string temp;
    int outp = 0;

    for(int i = 0; i < x.length(); i++){
        
        if(x[i+1] != ' ' && x[i]>='0' && x[i]<='9'){
            temp+=x[i];
        }
        else if(x[i+1] == ' ' && x[i]>='0' && x[i]<='9'){
            temp+=x[i];
            int n = strToInt(temp);
            num.push(n);
            temp ="";
        }

        else if(x[i] == '+' ||
                x[i] == '-' ||
                x[i] == '*' ||
                x[i] == '/')
                
        {   int a = num.pop();
            int b = num.pop();

            switch(x[i]){
                case '+': num.push(a+b); break;
                case '-': num.push(b-a); break;
                case '*': num.push(a*b); break;
                case '/': num.push(b/a); break;
            }
        }
    }

    cout<<"Hasil: "<<num.pop()<<endl;
}

int main(){
    string exp; cin>>exp;
    cout<<"Infix: "<<exp<<endl;
    exp = infixToPostfix(exp);
    cout<<"Postfix: "<<exp<<endl;
    doTheMath(exp);
}
