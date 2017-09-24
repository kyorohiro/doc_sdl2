# 四則演算(Four arithmetic operations)をしてみよう

## 足し算

```
// add.c
#include<stdio.h>
int main(int argc, char **argv) {
 printf("%d", 2+3);
}
```
emcc add.c -o add.html

## 引き算
```
// add.c
#include<stdio.h>
int main(int argc, char **argv) {
 printf("%d", 100-1);
}
```
emcc add.c -o add.html

## 掛け算
```
// add.c
#include<stdio.h>
int main(int argc, char **argv) {
 printf("%d", 2*3);
}
```
emcc add.c -o add.html


## 割り算
```
// add.c
#include<stdio.h>
int main(int argc, char **argv) {
 printf("%d", 100/10);
}
```
emcc add.c -o add.html
