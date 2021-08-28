# Brace placement

* Always Uses Braces Form

```c
   if (condition) {    
      ...                   
   }   
   while (condition) {
      ...                  
   }                     
```

* All if, while and do statements require braces even if there is only a single statement within the braces. 
```c
if (1 == somevalue) {
   somevalue = 2;
}
```
# Add Comments to Closing Braces

* Adding a comment to closing braces can help when you are reading code because you don't have to find the begin brace to know what is going on.

```c
while(1) {
   if (valid) {
  
   } /* if valid */
   else {
   } /* not valid */

} /* end forever */
```

# Parens () with Key Words and Functions Policy

* Do _not_ put parens next to keywords. Put a space between.
* Do put parens next to function names.
* Do not use parens in return statements when it's not necessary.
_Keywords are not functions. By putting parens next to keywords keywords and function names are made to look alike_
```c
    if (condition) {
    }

    while (condition) {
    }

    strcpy(s, s1);

    return 1;
```

# A Line Should Not Exceed 78 Characters =)

# If _Then_ _Else_ Formatting

* Common approach
```c
if (condition) {
   } else if (condition) {
   } else {
   }
```

## Condition format

* Always put the constant on the left hand side of an equality/inequality comparison.

```c
if ( 6 == errorNum ) ...
```

_One reason is that if you leave out one of the = signs, the compiler will find the error for you. A second reason is that it puts the value you are looking for right up front where you can find it instead of buried at the end of your expression._

# switch formatting

* Falling through a case statement into the next case statement shall be permitted as long as a comment is included.

* The default case should always be present and trigger an error if it should not be reached, yet is reached.

* If you need to create variables put all the code in a block.

```c
   switch (...)
   {
      case 1:
         ...
      /* comments */

      case 2:
      {        
         int v;
         ...
      }
      break;

      default:
   }

```

# Use of goto,continue,break and ?:

## Goto

* Try to avoid using this keyword. The main place where they can be usefully employed is to break out of several levels of switch, for, and while nesting._The need to do such a thing may indicate that the inner constructs should be broken out into a separate function, with a success/failure return code._

```c
   for (...) {
      while (...) {
      ...
         if (disaster) {
            goto error;
         } 
      }
   }
```

# Continue and Break

Problems with continue : 
* It may bypass the test condition
* It may bypass the increment/decrement expression

```c
while (TRUE) {
   ...
   /* A lot of code */
   ...
   if (/* some condition */) {
      continue;
   }
   ...
   /* A lot of code */
   ...
   if ( i++ > STOP_VALUE) break;
}
```

* *Mixing continue with break in the same loop is a sure way to disaster.*

# ?:

* The trouble is people usually try and stuff too much code in between the ? and :

* Put the condition in parens so as to set it off from other code
* If possible, the actions for the test should be simple functions.
* Put the action for the then and else statement on a separate line unless it can be clearly put on one line.

```c
(condition) ? funct1() : func2();

(condition)
    ? long statement
    : another long statement;
```

or 

```c
 (condition)
      ? long statement
      : another long statement;
```

# One Statement Per Line
* There should be only one statement per line unless the statements are very closely related.

*  One Variable Per Line. 
```c
char **a = 0;  /* add doc */
char  *x = 0;  /* add doc */
```

# Use Header File Guards

* Include files should protect against multiple inclusion through the use of macros that "guard" the files. Do *not* use underscores '_' as the first or last character of a header guard.(For C++ compatibility)

```c
#ifndef sys_socket_h
  #define sys_socket_h  /* NOT _sys_socket_h_ */
  #endif 
```
