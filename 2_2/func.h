#pragma once // Include guard

#include "Test.h"  // Include the definition of the Test class
#include <utility> // Needed for std::move

// f1: Takes by value (triggers copy constructor), returns by value (triggers move constructors without elision)
Test f1(Test param)
{
    // The print call happens after the copy construction of 'param'.
    // The name "a" is just a placeholder label matching the output pattern.
    param.print("a");
    return param; // Move semantics used for return value when elision is off
}

// f2: Takes by reference, returns by reference (no copies or moves)
Test &f2(Test &param)
{
    // The print call happens inside f2, operating on the original object 'b'.
    // The name "b" is just a placeholder label matching the output pattern.
    param.print("b");
    return param; // Return a reference to the same object
}

// f3: Takes by reference, performs a move-based swap
void f3(Test &p1, Test &p2)
{
    // Standard swap implementation using move semantics
    Test temp = std::move(p1); // Calls move constructor: Test(Test&&)
                               // p1's buffer is now nullptr
    p1 = std::move(p2);        // Calls move assignment: operator=(Test&&)
                               // p2's buffer is now nullptr
    p2 = std::move(temp);      // Calls move assignment: operator=(Test&&)
                               // temp's buffer is now nullptr

} // temp goes out of scope here, calling ~Test() on an object with buf == nullptr