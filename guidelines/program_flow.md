# Do Not Default If Test to Non-Zero

Do not default the test for non-zero, i.e.
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
=====wt?====The ++ and -- operators count as assignment statements. So, for many purposes, do functions with side effects. Using embedded assignment statements to improve run-time performance is also possible. However, one should consider the tradeoff between increased speed and decreased maintainability that results when embedded assignments are used in artificial places. For example,


   a = b + c;
   d = a + r; 
should not be replaced by

   d = (a = b + c) + r; 
even though the latter may save one cycle. In the long run the time difference between the two will decrease as the optimizer gains maturity, while the difference in ease of maintenance will increase as the human memory of what's going on in the latter piece of code begins to fade.
==