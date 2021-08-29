# Stucture names
* Use underbars ('_') to separate name components

```c
typedef struct{
    
} struct_name_with_underbar;
```

* Declare variables in structures organized by use in a manner to attempt to minimize memory wastage because of compiler alignment issues, then by size, and then by alphabetical order
    _Bad Example_
```c
typedef struct{
    int a;
    char *b;
    int c;
    chr *d;
} foo;
```

    _Good example_

```c
typedef struct
{
    int a,
    int d,
    char *c,
    char *d;
} foo;
```

* Each variable gets its own type and line, although an exception can be made when declaring bitfields (to clarify that it's part of the one bitfield). Note that the use of bitfields in general is discouraged.

```c
typedef struct {
    int bar;
    unsigned int baz:1,
                 fuz:5,
                 zap:2;   
} foo;
```

*  Structures should be declared at the top of the file in which they are used, or in separate header files, if they are used in multiple source files.

# Variables naming

* use all lower case letters
* use '_' as the word separator.

```c
int handle_error (int error_number) {
      int            error= OsErr();
      Time           time_of_error;
      ErrorProcessor error_processor;
   }
```

# Pointers variables

* Place the * close to the variable name not pointer type

```c
    char *name= NULL;

    char *name, address; 
```

# Global variables

* Global variables should be prepended with a 'g_'.
* Global variables should be avoided whenever possible.

```c
    Logger  g_log;
    Logger* g_plog;
```

# Global constants

* Global constants should be all caps with '_' separators.

```c
const int A_GLOBAL_CONSTANT= 5;
```

# #define and macro names

* Put #defines and macros in all upper using '_' separators.
_Try to make your macro as clean as possible and avoid some hacks as 'do{} while(0)',parenthesis._
 ```c
#define MAX(a,b) blah
#define IS_ERR(err) blah
#define	MACRO(v, w, x, y)				\
do {									\
	v = (x) + (y);						\
	w = (y) + 2;						\
} while (0)
 ```

# Enum

* Labels All Upper Case with '_' Word Separators
_This is the standard rule for enum labels. No comma on the last element._

```c
enum PinStateType {
      PIN_OFF,
      PIN_ON
   };
```

* It's often useful to be able to say an enum is not in any of its valid states. Make a label for an uninitialized or error state. Make it the first label if possible.

```c
enum { STATE_ERR,  STATE_OPEN, STATE_RUNNING, STATE_DYING};
```




