# eval 1.3.7

eval is a commandline tool used to evaluate mathematical expressions quick.  
\[Alpha\]

## features

- PODMAS operators including %-modulo and ^-power.
- Assignable variables and built-in variables and functions. Identifiers are case sensitive.
- Chainable expressions separated by `;`
- Interactive mode
- \*to be implemented in the future\*
  - dynamic function and variable registering using modules and config files
  - plotter

### Default variables

e log2e ln10 ln2 log10e pi 2pi 3pi 4pi

### Default functions

sqrt sin cos tan asin acos atan exp log log10 log2 floor ceil round sign signp signn abs int frac deg2rad rad2deg norm2rad rad2norm

## examples

- `eval "pi" -> 3.14...`
- `eval "2^3" -> 8`
- `eval "2^3*2" -> 16`
- `eval "sqrt(4)" -> 2`
- `eval "a=5" -> 5.00` sets `a` to `5`
- `eval "x=pi;x=x*2" -> 6.28...`
- `eval "x=pi;y=3;x*y" -> 9.42...`
- interactive mode

  ```shell
    eval -i
    > x = cos(deg2rad(45))
    0.707106781186548
    > result * 2
    1.414213562373095
  ```
