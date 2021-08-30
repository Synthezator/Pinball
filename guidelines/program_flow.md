# Do Not Default If Test to Non-Zero

* Do not default the test for non-zero, i.e.
```c
  if (FAIL != f()) 
```
is better than

```c
  if (f()) 
```

# Usually Avoid Embedded Assignments

* There is a time and a place for embedded assignment statements. In some constructs there is no better way to accomplish the results without making the code bulkier and less readable.

```c
    while (EOF != (c = getchar())) {
      process the character
    }
```

# _If Then Else_ Formatting
_If you have else if statements then it is usually a good idea to always have an else block for finding unhandled cases. Maybe put a log message in the else even if there is no corrective action taken._
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

## Continue and Break

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