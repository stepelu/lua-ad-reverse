# Lua Reverse Mode Automatic Differentiation

## Resources

+ *Evaluating Derivatives: Principles and Techniques of Algorithmic Differentiation, Second Edition*: clear exposition of the thoery and practice of forward and reverse mode automatic diffentation
+ *David Gay's RAD library*: see dep/rad folder into this repository, 
+ [*Adept: A fast automatic differentiation library for C++*](http://www.met.reading.ac.uk/clouds/adept/): one of the fastes implementations of reverse mode AD in C++ via operator overloading and template metaprogramming
+ [*Stan*](http://mc-stan.org/): framework for frequentist and bayesian inference of statistical distribution-based models, includes reverse mode automatic differentiation engine (not explicitely documented)

## Plan

1. Understand reverse mode logic, convert/extend RAD library to Lua
2. Implement efficient Lua version of reverse mode differentiation based on Adept and Stan
3. Optimize implementation of point 2 for LuaJIT/FFI
