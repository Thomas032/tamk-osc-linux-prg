#include <iostream>
using namespace std;

int main(){
    cout << "Enter two numbers: ";
    int a, b;
    cin >> a >> b;
    int sum = a + b;
    int sub = a - b;
    int prod = a * b;
    int quot = a / b;
    cout << "Addition: " <<sum << endl;
    cout << "Subtraction: " <<sub << endl;
    cout << "Multiplication: " <<prod << endl;
    cout << "Division: " <<quot << endl;
    return 0;
}