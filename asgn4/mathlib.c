// this impliments / defines all of the math functions needed ex) cos, sin
#include "mathlib.h"

#include "stdio.h"

#include <math.h>

double Abs(double x) {
    return x < 0 ? -x : x;
}

// Modulus function for floating-point numbers, similar to fmod

double Sqrt(double x) {
    // Check domain.
    if (x < 0) {
        return nan("nan");
    }
    double old = 0.0;
    double new = 1.0;
    while (Abs(old - new) > EPSILON) {
        // Specifically, this is the Babylonian method--a simplification of
        // Newton's method possible only for Sqrt(x).
        old = new;
        new = 0.5 * (old + (x / old));
    }
    return new;
}
double Sin(double x) {
    x = fmod(x, 2 * M_PI); // Normalize x within [0, 2PI]

    double term = x; // The first term of the series
    double sum = term; // Initialize sum with the first term
    double power = x; // x to the power of n
    double factorial = 1; // n!
    int n = 1;

    while (Abs(term) > EPSILON) {
        power *= x * x; // Increase power of x by 2 each iteration: x^2, x^4, x^6, ...
        factorial *= (2 * n) * (2 * n + 1); // Update factorial for the current term (2n+1)!
        term = power / factorial; // Calculate the term
        if (n % 2 != 0) { // Alternate signs for each term
            term = -term;
        }
        sum += term; // Add the term to the sum
        n++; // Increment n for the next term
    }

    return sum; // Return the calculated sum, which approximates the sine of x
}
double Cos(double x) {
    if (x > 2 * M_PI) {
        x = fmod(x, 2 * M_PI); // Normalize x within [0, 2PI]
    }

    double term = 1; // The first term of the series is always 1
    double sum = term; // Initialize sum with the first term
    double xSquared = x * x; // x^2, used to calculate terms of the series
    double numerator = 1; // Numerator for the current term, starts as 1 for x^0
    double factorial = 1; // Denominator for the current term, starts as 1 for 0!
    int n = 1; // Start from the second term

    while (Abs(term) > EPSILON) {
        numerator *= xSquared; // Increase power of x by 2 for each term: x^2, x^4, x^6, ...
        factorial *= (2 * n - 1) * (2 * n); // Calculate the factorial for the denominator (2n)!
        term = numerator / factorial; // Calculate the current term of the series
        if (n % 2 != 0) { // Alternate the sign for each term
            term = -term;
        }
        sum += term; // Add the current term to the sum
        n++; // Proceed to the next term
    }

    return sum; // Return the calculated sum, which is the cosine of x
}

double Tan(double x) {
    x = fmod(x, 2 * M_PI); // Normalize x within [0, 2PI]

    // Check for values where cosine is zero and tangent is undefined
    if (Abs(fmod(x, M_PI) - M_PI / 2) < EPSILON || Abs(fmod(x, M_PI) + M_PI / 2) < EPSILON) {
        // Handle the undefined case, e.g., by returning a special value or error
        // Since we cannot use NAN or INFINITY without including math.h, you might use 0 or another indicative value
        // Or signal the error in another way appropriate for your application
        return 0; // Placeholder for handling undefined case
    }

    return Sin(x) / Cos(x);
}
