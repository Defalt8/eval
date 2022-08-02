# eval

eval is a commandline tool used to evaluate mathematical expressions quick.  
\[Alpha\]

## features

- PODMAS operators including %-modulo and ^-power.
- Assignable variables and built-in variables and functions. Identifiers are case sensitive.
- Chainable expressions separated by `;`
- \*to be implemented in the future\*
  - dynamic function and variable registering using modules and config files
  - interactive mode
  - plotter

### Default variables

e, log2e, ln10, ln2, log10e, pi, 2pi, 3pi, 4pi

### Default functions

sqrt, sin, cos, tan, asin, acos, atan, sign, abs, deg2rad, rad2deg, norm2rad, rad2norm

## examples

- `eval "pi" -> 3.14...`
- `eval "2^3" -> 8`
- `eval "2^3*2" -> 16`
- `eval "sqrt(4)" -> 2`
- `eval "a=5" -> 5.00` sets `a` to `5`
- `eval "x=pi;x=x*2" -> 6.28...`
- `eval "x=pi;y=3;x*y" -> 9.42...`
