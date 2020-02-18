#include <iostream>
#include <sstream>
#include "rational.h"
using namespace std;

/**
 * Your implementation of the Rational class must provide appropriate
 *  member and non-member functions such that the following program
 *	compiles and produces the correct output.
 */
int main()
{
    cout << "Constructor and insertion and extraction operators:" << endl;
    Rational r1;
    cout << r1 << endl;
    Rational r2(4, -20);
    cout << r2 << endl;
    Rational r3, r4, r5;
    int x = 2;
    std::stringstream ss("18 /-10 -14 / -6 2/4");
    ss >> r3 >> r4 >> r5;
    // Should yield 3 Rationals: r3=-9/5, r4=7/3, and r5=1/2
    cout << r3 << " " << r4 << " " << r5 << endl;

    cout << "Addition checks: " << endl;
    cout << (r2 + r3) << endl;
    cout << (x + r3) << endl;
    cout << (r3 + x) << endl;
    cout << "Multiplication checks: " << endl;
    cout << (r3 * r4) << endl;
    cout << (6 * r4) << endl;
    cout << (r4 * 6) << endl;
    cout << "Exponentiation checks: " << endl;
    cout << (r5 ^ 3) << endl;
    cout << (r5 ^ -2) << endl;
    cout << (r3 ^ 0) << endl;

    Rational req1(2, 4), req2(4, 8), rne3(-4, 8);
    cout << "Equal checks: " << endl;
    cout << (req1 == req2) << endl;
    cout << (req1 == rne3) << endl;
    cout << "Not Equal checks: " << endl;
    cout << (req1 != req2) << endl;
    cout << (req1 != rne3) << endl;
    cout << "Less-than checks: " << endl;
    cout << (r3 < r4) << endl;
    cout << (req1 < req2) << endl;
    cout << (rne3 < req1) << endl;

    Rational r5c1 = r5, r5c2 = r5, r5c3 = r5, r5c4 = r5;
    cout << "Assignment checks: " << endl;
    cout << (r5c1 += rne3) << endl;
    cout << (r5c2 += 5) << endl;
    cout << (r5c3 *= r2) << endl;
    cout << (r5c4 *= 3) << endl;

    Rational r6a(2,4), r6b(-4,8);
    cout << "Normalized 0 check: " << endl;
    cout << r6a + r6b << endl;
    
    /*
    cout << "Both num and denom are negative: " << endl;
    Rational r7a(-4, -8), r7b(1, -2);
        cout << r7a << "+" << r7b << "=\n";
    cout << r7a + r7b << endl; // 0/1

    cout << "Bad creation" << endl;
    Rational r10a(0, -8), r10b(0, 7);
    cout << r10a << endl;       // 0/1
    cout << r10b << endl;       // 0/1

    cout << "Multiplication by 0: " << endl;
    Rational r8a(5, 8), r8b;
    cout << (r8a * r8b) << endl; // 0/1
    cout << (0 * r8a) << endl;   // 0/1
    cout << (r8a * 0) << endl;   // 0/1

    cout << "Add 0" << endl;
    cout << (r8a + r8b) << endl; // 5/8
    cout << (0 + r8a) << endl;   // 5/8
    cout << (r8a + 0) << endl;   // 5/8

    cout << "Add + and - num" << endl;
    Rational r8c(-1, 3);
    cout << (r8a + r8c) << endl; // 7/24
    cout << (-2 + r8a) << endl; // -11/8
    cout << (r8a + -2) << endl; // -11/8
    cout << r7a << "+" << r8c << "=\n";
    cout << r7a + r8c << endl;  // 1/6

    cout << "Add - and - num" << endl;
    Rational r8d(-1, 5);
    cout << (r8c + r8d) << endl; // -8/15
    cout << (-2 + r8d) << endl;  // -11/5
    cout << (r8d + -2) << endl;  // -11/5

    cout << "Multiply + and - num" << endl;
    cout << (r8c * r8d) << endl; // 1/15
    cout << (-2 * r8d) << endl;  // 2/5
    cout << (r8d * 2) << endl;  // -2/5

    cout << "Exponentiation checks: " << endl;
        cout << (r8d ^ 3) << endl; // -1/125
        cout << (r8d ^ -2) << endl;// 25/1
        cout << (r8d ^ 0) << endl; // 1/1

    cout << "*= with 0:" << endl;
        cout << (r8b *= r8a) << endl; // 0/1 
        cout << (r8c *= 0) << endl; // 0/1
    cout << "+= with 0" << endl;
        cout << (r8b += r8a) <<endl; //0 + 5/8 = 5/8 
    cout << r8b <<endl; //5/8: r8b is now 5/8

    cout << "Bad extraction" << endl;
    std::stringstream ss2("");
    std::stringstream ss3(" ");
    std::stringstream ss4(" a ");
    std::stringstream ss5("18 4 2 3");
    std::stringstream ss6("18 / / -6");
    std::stringstream ss7("/ / /");
    std::stringstream ss8("/ 18 4");
    Rational r9(7,8), r10(7, 8), r11(7, 8), r12(7, 8), r13(7, 8), r14(7, 8), r15(7, 8), r16(7, 8), r17(7, 8);

    ss2 >> r9;
    ss3 >> r10;
    ss4 >> r11;
    ss5 >> r12 >> r13;
    ss6 >> r14 >> r15;
    ss7 >> r16;
    ss8 >> r17;
    // Should ALL yield 0/1 
    cout << r9 << " " << r10 << " " << r11 << " " << r12 << " " << 
            r13 << " " << r14 << " " << r15 << " " << r16 << " " << r17;
    */


    return 0;
}
