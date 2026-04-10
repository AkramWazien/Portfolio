/*To be fixed later*/
#include <iostream>
#include <climits>

char operation(){
    char op;
    std::cout << "Enter your desired operation (+ - * /): ";
    std::cin >> op;
    return op;
}

int main(){
    using std::cout;
    using std::endl;
    using std::cin;
    using string_t = std::string;

    char input_op;
    double num1;
    double num2;
    double result = 0;

    input_op = operation();
    cout << "Enter the first number: ";
    while (!(cin >> num1)){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    cout << "Enter the second number: ";
    cin >> num2;

    switch(input_op){
        case '+':
            result = num1 + num2;
            cout << "The result is " << result;
            break;
        case '-':
            result = num1 - num2;
            cout << "The result is " << result;
            break;
        case '*':
            result = num1 * num2;
            cout << "The result is " << result;
            break;
        case '/':
            result = num1 / num2;
            cout << "The result is " << result;
            break;
        default:
            cout << "Enter a correct operation" << endl;
            main();
            break;
    }
    return 0;
}