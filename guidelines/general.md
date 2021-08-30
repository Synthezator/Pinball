# General advice

* Don't use floating-point variables where discrete values are needed. Using a float for a loop counter is a great way to shoot yourself in the foot. Always test floating-point numbers as <= or >=, never use an exact comparison (== or !=).


* Accidental omission of the second ``='' of the logical compare is a problem. The following is confusing and prone to error

```c
  if (abool= bbool) { ... }
```

_Use explicit tests and avoid assignment with an implicit test. The recommended form is to do the assignment before doing the test:_

```c
    abool= bbool;
    if (abool) { ... }
```
# Be Const Correct

* C provides the const key word to allow passing as parameters objects that cannot change to indicate when a method doesn't modify its object. Using const in all the right places is called "const correctness."
