# Hello World を書き間違えてみよう

## 全角文字をつかう

```
#include<stdio.h>
int main(int argc, char **argv) {
  　printf("Hello, World!");
}
```

以下のような、エラーが表示されます。  
printfの左側、3行目:のあたりに  
想定外の文字があるようですね。

```
C:\Users\jiegu\work\helloworld>emcc hello.c -o hello.html
hello.c:3:3: error: source file is not valid UTF-8
  <81>@printf("Hello, World!");
  ^
hello.c:3:4: error: expected expression
  <81>@printf("Hello, World!");
      ^
2 errors generated.
ERROR:root:compiler frontend failed to generate LLVM bitcode, halting
```

# 「;」と「:」を書き間違える

```
#include<stdio.h>
int main(int argc, char **argv) {
  printf("Hello, World!"):
}
```

以下のような、エラーが表示されます。  
4行目のあたりで、「;」でなくて「:」と書かれてますよ。  
と指摘されます。

```
C:\Users\jiegu\work\helloworld>emcc hello.c -o hello.html
hello.c:4:25: error: expected ';' after expression
 printf("Hello, World!"):
                        ^
                        ;
1 error generated.
ERROR:root:compiler frontend failed to generate LLVM bitcode, halting
```
