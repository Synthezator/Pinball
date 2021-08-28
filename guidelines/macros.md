# Don't Turn C into Pascal

* Don't change syntax via macro substitution. It makes the program unintelligible to all but the perpetrator.

# Replace Macros with Inline Functions

* However, macros for small functions are ok.

```c
#define  MAX(x,y)	(((x) > (y) ? (x) : (y))
```
_The macro above can be replaced for integers with the following inline function with no loss of efficiency:_
```c
inline int 
   max(int x, int y) {
      return (x > y ? x : y);
   }
```

# Always Wrap the Expression in Parenthesis
* When putting expressions in macros always wrap the expression in parenthesis to avoid potential communitive operation abiguity
```c
#define ADD(x,y) x + y
```
must be written as 
```c
#define ADD(x,y) ((x) + (y))
```
# Make Macro Names Unique

Like global variables macros can conflict with macros from other packages.

* Prepend macro names with package names.
* Avoid simple and common names like MAX and MIN.