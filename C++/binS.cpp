#include<iostream>
using namespace std; // standard - thư viện chuẩn 

/*
 ngôn ngữ bậc cao -> bộ biên dịch -> mã máy 
 
*/
int main(){
    /*
        <kiểu dữ liệu> <tên biến>;
        số nguyên : int, long, long long
        số thực : float, double
        + - * / %
        
    */
       
    //cout << "So a + b la : ";
    /*
        if (<điều kiện>) {
            <code> 
        }
        else if(<điều kiện>){
            <code>
        }
        else {

        }
    */
   /*
    nhập 2 số
    tính tổng
    kiểm tra xem nếu là số âm thì in ra : tong la so am
    nếu tổng là số từ [0, 9] : tong la so hoan hao
    nếu tổng lớn hơn 9 : tong la so khong hoan hao 
 */
    int month, year;
    cin >> month;
    cin >> year;
    
    if(month == 2){
        if((year % 4 == 0 && year % 100 != 0) || (year % 100 == 0 || year % 400 == 0)){
            cout << 29;
        }else cout << 28;
    }
    else if(month < 8){
        if(month % 2 == 0){
            cout << 30;
        }
        else {
            cout << 31;
        }
    }else {
        if(month % 2 == 0){
            cout << 31;
        }else {
            cout << 30;
        }
    }
}