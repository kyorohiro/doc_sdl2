# Hello World を実行してみよう!!

コマンドプロンプトを開いて、C言語で、Hello Worldを実行してみましょう。


※ 初めてのプログラム
..
..

- [1]. コマンドプロンプトを起動する

- [2]. notepadで、hello.c ファイルを開く

```
C:\Users\Usr>mkdir work
C:\Users\Usr>cd work
C:\Users\Usr\work>mkdir helloworld
C:\Users\Usr\work\helloworld>cd helloworld
C:\Users\Usr\work\helloworld>notepad hello.c
```

- [3]. コードを書く

```
#include<stdio.h>
int main(int argc, char **argv) {
  printf("Hello, World!");
}

```

- [3]. 保存する
Ctrl+S　する。 ※ CtrlキーとSキーの同時押し。



- [4]. コンパイルして、Htmlファイルを生成する

```
C:\Users\Usr\work\helloworld>emcc hello.c -o hello.html

```

- [5]. 実行する

```
C:\Users\Usr\work\helloworld>start hello.html

```
