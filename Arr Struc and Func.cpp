#include <iostream>
#include <iomanip>

using namespace std;

//Structures for Data Housing Corp
//-------------------------------------------------------------------------------

//Name Information 
struct emp_info
{
    typedef string name;
    name first_name;
    name mid_in;
    name last_name;
};

//Deductions
struct pay_deduc
{
    double
        state_tax_final,
        fed_tax_final,
        union_fees_final;

};

//Payroll Information --- Previous Structures are initialized (last two)
struct payroll
{
    double
        rate,
        hours,
        overtime_hours,
        overtime_pay,
        gross_pay,
        net_pay;
    emp_info emp_data; //name info
    pay_deduc pay_deduc_data; //deductions 

};

//----------------------------------------------------------------------------------

//Function Prototypes
//----------------------------------------------------------------------------------
void welcome();
void input(payroll[], const int&);
double input_val_one();
double input_val_two();
void overtime_hours_calc(payroll[], const int&);
void overtime_pay_calc(payroll[], const int&);
void gross_pay_calc(payroll[], const int&);
void state_tax_calc(payroll[], const double, const int&);
void fed_tax_calc(payroll[], const double, const int&);
void union_fees_calc(payroll[], const double, const int&);
void net_pay_calc(payroll[], const int&);
double gross_total_calc(double, payroll[], const int&);
double gross_avg_all_calc(double, double, const int&);
void output_gross_all(double, double);
void output(payroll[], const int&);
void goodbye_statement();


//Main
//----------------------------------------------------------------------------------

int main() {

    //Number of Employees and initializing array
    const int size = 5;
    payroll employee[size];

    //Constant values for State, Federal, and Union Tax/Fees 
    const double state_tax = 0.06;
    const double federal_tax = 0.12;
    const double union_fees = 0.02;

    //Initilizing for Total and Average Gross Pay
    double gross_income_all = 0;
    double gross_income_avg = 0;


    //Functions Calls
    welcome();
    input(employee, size);
    overtime_hours_calc(employee, size);
    overtime_pay_calc(employee, size);
    gross_pay_calc(employee, size);
    state_tax_calc(employee, state_tax, size);
    fed_tax_calc(employee, federal_tax, size);
    union_fees_calc(employee, union_fees, size);
    net_pay_calc(employee, size);
    output(employee, size);

    gross_income_all = gross_total_calc(gross_income_all, employee, size);
    gross_income_avg = gross_avg_all_calc(gross_income_avg, gross_income_all, size);

    output_gross_all(gross_income_all, gross_income_avg);

    goodbye_statement();

}


//Functions
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------------------------------

// As 'payroll' is a new data type that housed the employee information and payroll data, I could list it as the only argument in the functions below
// Employee Size Array Address is still called as a Reference

//---------------------------------------------------------------------------------------------------------------------------------------------------

//Welcome Function
void welcome() {
    cout << "Welcome to Data Housing Corp. Payroll Calculator" << endl;
    cout << "================================================" << endl;
    cout << endl;
}

//Input Function for Full Name, Salary, and Hours Worked
void input(payroll a[], const int& s) {

    for (int i = 0; i < s; i++) {
        cout << "Please enter your First Name: ";
        cin >> a[i].emp_data.first_name;
        cout << endl;
        cout << "Please enter your Middle Initial: ";
        cin >> a[i].emp_data.mid_in;
        cout << endl;
        cout << "Please enter your Last Name: ";
        cin >> a[i].emp_data.last_name;
        cout << endl;
        cout << "Please enter your Salary: $";
        cin >> a[i].rate;
        cout << endl;
        //-------------Input Validation for Salary
        if (a[i].rate <= 0 || a[i].rate > 60) {
            a[i].rate = input_val_one();
        }
        //----------------------------------------
        cout << "Please enter the amount of Hours worked this Week: ";
        cin >> a[i].hours;
        cout << endl;
        //--------Input Validation for Hours Worked
        if (a[i].hours <= 0 || a[i].hours > 50) {
            a[i].hours = input_val_two();
        }
        //-----------------------------------------
        cout << endl;
    }
}

//Input Validator for Hours 
double input_val_one() {

    double in_val_one;

    do {
        cout << "Invalid...Please enter again: ";
        cin >> in_val_one;
        cout << endl;
    } while (in_val_one <= 0 || in_val_one > 60);

    return in_val_one;
}

//Input Validator for Salary
double input_val_two() {

    double in_val_two;

    do {
        cout << "Invalid...Please enter again: ";
        cin >> in_val_two;
        cout << endl;
    } while (in_val_two <= 0 || in_val_two > 50);

    return in_val_two;

}

//Overtime Hours Function
void overtime_hours_calc(payroll b[], const int& sze) {
    for (int i = 0; i < sze; i++) {
        if (b[i].hours > 40) {
            b[i].overtime_hours = b[i].hours - 40;
        }
        else b[i].overtime_hours = 0;
    }
}

//Overtime Pay Function
void overtime_pay_calc(payroll c[], const int& sze) {
    for (int i = 0; i < sze; i++) {
        c[i].overtime_pay = c[i].overtime_hours * c[i].rate * 1.50;
    }

}

//Gross Pay Function
void gross_pay_calc(payroll d[], const int& sze) {
    for (int i = 0; i < sze; i++) {
        d[i].gross_pay = (d[i].rate * d[i].hours) + d[i].overtime_pay;
    }
}

//State Tax Function
void state_tax_calc(payroll e[], const double val, const int& s) {
    for (int k = 0; k < s; k++) {
        e[k].pay_deduc_data.state_tax_final = e[k].gross_pay * val;
    }

}

//Federal Tax Function
void fed_tax_calc(payroll f[], const double val, const int& s) {
    for (int k = 0; k < s; k++) {
        f[k].pay_deduc_data.fed_tax_final = f[k].gross_pay * val;
    }
}


//Union Fees Function
void union_fees_calc(payroll h[], const double val, const int& s) {
    for (int k = 0; k < s; k++) {
        h[k].pay_deduc_data.union_fees_final = h[k].gross_pay * val;
    }
}

//Net Pay Function
void net_pay_calc(payroll m[], const int& ss) {
    for (int a = 0; a < ss; a++) {
        m[a].net_pay = m[a].gross_pay - (m[a].pay_deduc_data.state_tax_final + m[a].pay_deduc_data.fed_tax_final + m[a].pay_deduc_data.union_fees_final);
    }
}


//Output Function 
void output(payroll n[], const int& sz) {

    //Payroll Display Title
    cout.width(80);
    cout << "Data Housing Corp. Weekly Payroll" << endl;
    cout.width(80);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    cout << "First Name" << "\tMI" << "\tLast Name" << "\tRate per Hour" << "\tHours Worked" << "\tGross Income" << "\tState Tax" << "\tFederal Tax" << "\tUnion Fees" << "\tNet Income" << endl;
    cout << "==========" << "\t==" << "\t=========" << "\t=============" << "\t============" << "\t============" << "\t=========" << "\t===========" << "\t==========" << "\t==========" << endl;

    for (int i = 0; i < sz; i++) {
        cout << fixed << setprecision(2);

        cout << left << setw(16) << n[i].emp_data.first_name << setw(9) << n[i].emp_data.mid_in << setw(10) << n[i].emp_data.last_name; //First Name, Middle Initial, Last Name

        cout << right
            << setw(6) << "$" << n[i].rate //Salary
            << setw(10) << "" << n[i].hours //Hours Worked
            << setw(12) << "$" << n[i].gross_pay //Gross Pay
            << setw(10) << "$" << n[i].pay_deduc_data.state_tax_final //State Tax
            << setw(11) << "$" << n[i].pay_deduc_data.fed_tax_final //Federal Tax
            << setw(10) << "$" << n[i].pay_deduc_data.union_fees_final //Union Fees
            << setw(12) << "$" << n[i].net_pay; //Net Pay
        cout << endl; 

    }

    cout << endl;
}


//Gross Total Pay for all Employees Function
double gross_total_calc(double val_all, payroll x[], const int& sz) {
    val_all = 0;
    for (int n = 0; n < sz; n++) {
        val_all = val_all + x[n].gross_pay;
    } return val_all;                       
}

//Gross Average Pay for all Employees Function
double gross_avg_all_calc(double val_avg, double val_all, const int& sz) {
    val_avg = 0;
    for (int n = 0; n < sz; n++) {
        val_avg = val_all / sz;
    } return val_avg;                       
}

//Output for Gross Total and Gross Average
void output_gross_all(double val_all, double val_avg) {
    cout << endl;
    cout << "The Gross Total Pay of all Employees is: " << val_all << endl; //Gross Total
    cout << "The Gross Average Pay of all Employees is: " << val_avg << endl; //Gross Average 
    cout << endl;
}


//Goodbye Function 
void goodbye_statement() {
    cout << endl << "Thank you for using Data Housing Corp Payroll Calculator. Have a Great Day!" << endl;
    cout << endl << endl;
}