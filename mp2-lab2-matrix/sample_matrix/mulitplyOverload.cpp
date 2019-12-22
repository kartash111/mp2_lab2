#include<iostream>
#include<string>
#include<sstream>
#define SIZE 700
using namespace std;


class large{
    int no[SIZE];    
    /*
        array is used to store the large number. 
        Each digit of a the number is stored as an element..
        123 is stored as no[3]={1,2,3} 
    */
    
public:
    // overload the + operator
    large operator +(large& x){ 
        int carry=0;
        large ret;
        for(int i=SIZE-1;i>=0;i--){
            carry += no[i]+x.no[i];
            if(carry < 10){
                ret.no[i]=carry;
                carry=0;
            }
            else{
                ret.no[i]=carry%10;
                carry=carry/10;
            }
        }
        return ret;
    }
    large operator *(large& x){ // overload the * operator
        /*
            34 x 46
            -------
              204            // these values are stored in the
             136            // two dimensional array mat[][];
            -------
             1564   // this the value stored in "large ret"
        */                                
        large ret;                
        int carry=0;
        int mat[2*SIZE+1][2*SIZE]={0};
        for(int i=SIZE-1;i>=0;i--){
            for(int j=SIZE-1;j>=0;j--){
                carry += no[i]*x.no[j];
                if(carry < 10){
                    mat[i][j-(SIZE-1-i)]=carry;
                    carry=0;
                }
                else{
                    mat[i][j-(SIZE-1-i)]=carry%10;
                    carry=carry/10;
                }
            }
        }
        for(int i=1;i<SIZE+1;i++){
            for(int j=SIZE-1;j>=0;j--){
                carry += mat[i][j]+mat[i-1][j];
                if(carry < 10){
                    mat[i][j]=carry;
                    carry=0;
                }
                else{
                    mat[i][j]=carry%10;
                    carry=carry/10;
                }
            }
        }
        for(int i=0;i<SIZE;i++)
            ret.no[i]=mat[SIZE][i];
        return ret;
    }

    large (){
        for(int i=0;i<SIZE;i++)
            no[i]=0;
    }

    large (string _no){
        for(int i=0;i<SIZE;i++)
            no[i]=0;
        int index=SIZE-1;
        for(int i=_no.length()-1;i>=0;i--,index--){
            no[index]=_no[i]-'0';
        }
    }
    //print the large number
    void print(){        
        int start=0;
        // find the first non zero digit. store the index in start.
        for(int i=0;i<SIZE;i++)
        if(no[i]!=0){
            start=i;
            break;        
        }
        
        // print the number starting from start till the end of array.
        for(int i=start;i<SIZE;i++) 
            cout<<no[i];
        cout<<endl;
        return;
    }
};
int main(){
    large fact("1");
    for(int i=1;i<=300;i++){    
        stringstream io;
        
        // the input must be taken in the form of a string;
        string number;   
        io << i;
        io >> number;
        large ite(number);
        fact = fact * ite;
    }
    fact.print();
    return 0;
}