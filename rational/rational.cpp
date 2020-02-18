#include <stdexcept>
#include <math.h>
#include "rational.h"

Rational::Rational()
{
    n = 0;
    d = 1;
}
Rational::Rational(int num, int denom)
{
    if (denom == 0) throw std::invalid_argument("Can't have denom = 0");
    // Continue your implementation below.
    // You should likely call this->reduce() and this->normalize0()
    if(num == 0){
        this->normalize0();
    }else{
        n = num; 
        d = denom;
    }
    this->reduce();
}

void Rational::normalize0()
{
    if (n == 0 && d != 1) d = 1;
}

/**
 * Appropriate ostream (insertion) operator '<<'
 *
 * When outputting a Rational simply print the numerator (with the sign),
 * a '/' character, and the denominator.  Thus, if the ostream operator is
 * applied to Rational(2,-4), "-1/2" should be output.  If the ostream
 * operator is applied to Rational(-6,-4), "3/2" should be output.
 */
std::ostream& operator<<(std::ostream& ostr, const Rational& r)
{
    ostr << r.n << "/" << r.d;
    return ostr;
}

/**
 * Appropriate istream (extraction) operator '>>'
 *
 * When inputting a Rational, read a numerator, a '/', and a denominator
 * and set the Rational input reference with the appropriate value specified
 * by the values read.
 *
 * Any amount of whitespace may separate the three components
 * (numerator, '/', and denominator).  And the numerator and/or denominator
 * may be negative when read.
 */
std::istream& operator>>(std::istream& istr, Rational& r)
{
    int n,d;
    char x;
    istr >> n;
    if(istr.fail()){
        r = Rational();
        return istr;
    }
    istr >> x;
    if(istr.fail()){
        r = Rational();
        return istr;
    }
    istr >> d;
    if(istr.fail()){
        r = Rational();
        return istr;
    }else if(x != '/'){
        r = Rational();
        return istr;
    }
    r = Rational(n,d);
    return istr;
}

Rational Rational::operator+(Rational& r)
{
    Rational temp;
    temp.d = d * r.d;
    temp.n = n * r.d + d * r.n;
    temp.reduce();
    return temp;
}

Rational Rational::operator+(int num)
{
    Rational temp;
    temp.d = d;
    temp.n = n + d * num;
    temp.reduce();
    return temp;
}

Rational operator+(int num, Rational& r)
{
    Rational temp;
    temp.d = r.d;
    temp.n = r.n + num * r.d;
    temp.reduce();
    return temp;
}

Rational Rational::operator*(Rational& r)
{
    Rational temp;
    temp.d = d * r.d;
    temp.n = n * r.n;
    temp.reduce();
    return temp;
}

Rational Rational::operator*(int num)
{
    Rational temp;
    temp.d = d;
    temp.n = n*num;
    temp.reduce();
    return temp;
}

Rational operator*(int num, Rational& r)
{
    Rational temp;
    temp.d = r.d;
    temp.n = r.n * num;
    temp.reduce();
    return temp;
}

Rational Rational::operator^(int num)
{
    Rational temp;
    if(num>0){
        temp.d = pow(d, num);
        temp.n = pow(n, num);
    }else{
        temp.d = pow(n, num*-1);
        temp.n = pow(d, num*-1);
    }
    temp.reduce();
    return temp;

}

bool Rational::operator==(Rational& r)
{
    return (n==r.n && d==r.d);
}

bool Rational::operator!=(Rational& r)
{
    return !(n==r.n && d==r.d);
}

bool Rational::operator<(Rational& r)
{
    if(n<0 && r.n>=0){
        return true;
    }else if(n>=0 && r.n<0){
        return false;
    }

    int rhs = n * r.d; 
    int lhs = r.n * d;

    if(rhs < lhs){
        return true;
    }
    return false;
}

Rational Rational::operator+=(Rational& r)
{
    Rational temp;
    temp.d = d * r.d;
    temp.n = n * r.d + d * r.n;
    d = temp.d/ gcd(temp.d, temp.n);
    n = temp.n/ gcd(temp.d, temp.n);
    temp.reduce();
    return temp;
}

Rational Rational::operator+=(int num)
{
    Rational temp;
    temp.d = d;
    temp.n = n + d * num;
    d = temp.d/gcd(temp.d, temp.n);
    n = temp.n/gcd(temp.d, temp.n);
    temp.reduce();
    return temp;
}

Rational Rational::operator*=(Rational& r)
{
    Rational temp;
    temp.d = d * r.d;
    temp.n = n * r.n;
    d = temp.d/gcd(temp.d, temp.n);
    n = temp.n/gcd(temp.d, temp.n);
    temp.reduce();
    return temp;
}

Rational Rational::operator*=(int num)
{
    Rational temp;
    temp.d = d;
    temp.n = n*num;
    d = temp.d/gcd(temp.d, temp.n);
    n = temp.n/gcd(temp.d, temp.n);
    temp.reduce();
    return temp;
}

/**
 * Divides the numerator and denominator by the gcd
 * thus leaving it in reduced form.
 */
void Rational::reduce()
{
    int divide = gcd(n,d);
    n /= divide;
    d /= divide;

    if(d<0){
        n= n*-1;
        d= d*-1;
    }
    
}

// Note:  Static member functions are essentially global
//        functions (take no implicit 'this' parameter and thus
//        are not applied to any particular instance of the class).
//        However, unlike a global scope function, a static member
//        function is scoped within the class (e.g. Rational::gcd(2,4))
//        and can access private data members of any class objectjects
//        passed as input arguments.
//        They are often used for helper functions for a class which
//        do NOT require any access to the data members or that are
//        not specific to a paritcular object instance.
//        In fact, there can also be static data members.  For more
//        information refer to:
//    https://www.tutorialspoint.com/cplusplus/cpp_static_members.htm

/**     
 * Returns the greatest common divisor of a and b
 */
int Rational::gcd(int a, int b)
{
	if (b == 0){
        return a; 
    }
    return gcd(b, a % b); 
}

/**
 * Returns the least common multiple of a and b
 */
int Rational::lcm(int a, int b)
{
	return (a*b)/gcd(a,b);
}

