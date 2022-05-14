# Week 7 Assignment - Interview Questions

Q: Given an integer variable a, write two code fragments. The first should set bit 3 of a. The second should clear bit 3 of a. In both cases, the other bits should be unmodified.

```c
int a = 0x55; // 0b01010101
a = a & ~(1 << 3); // Clear bit 3
a = a | (1 << 3); // Set bit 3
```

The solution could be improved by using #define for the bit mask to improve the readability of the code.  

```c
#define BIT3 (0x1 << 3)
```

Q: On a certain project it is required to set an integer variable at the absolute address 0x67a9 to the value 0xaa55. Write code to accomplish this task.

```c
int* ptr = 0x67A9;
*ptr = 0xAA55;
```

This code returns a compiler warning.
```console
warning: initialization of ‘int *’ from ‘int’ makes pointer from integer without a cast [-Wint-conversion]
```
Although the code may still work, it is more correct to explicitly cast the address to an int *. 
```c
int* ptr = (int*) 0x67A9;
*ptr = 0xAA55;
```


