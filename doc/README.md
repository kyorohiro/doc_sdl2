# 本書では、C言語 x Emscripten x SDL について書きます

Emscriptenを利用すると事で、C言語でブラウザー上で動作するアプリケーションを作成できます。

本書では、OpenGL と SDL と Enscripten を利用して
ブラウザー用、Window用、OSX用のゲームを作成していきます。


2017年9月の時点での時点で



### C言語はHacker必須の言語

本書では、C言語を利用します。※ C++ではなくて、純粋なC言語です。


C言語は最古の言語のひとつです。
[https://en.wikipedia.org/wiki/C_(programming_language)](https://en.wikipedia.org/wiki/C_(programming_language))
[http://www.bell-labs.com/usr/dmr/www/chist.html](http://www.bell-labs.com/usr/dmr/www/chist.html)
1973年にUNIXというOSを開発する中で生まれました。

C言語は、手続き型言語と関数型言語の特徴を持ちます。


C言語は、移植の容易性や、自由度の高さが売りです。

世界で持っても利用されているOSのひとつ、 LinuxはC言語で書かれています。

Hacker必須の言語ですね!!


## Emscriptenは、LLVMのバイトコードをJavaScriptに変換するツール
[http://kripken.github.io/emscripten-site/docs/index.html](http://kripken.github.io/emscripten-site/docs/index.html)
LLVMでコンパイルされたバイトコードをJavaScriptに変換することができます。

C言語ないし、C++言語で書いたアプリケーションやライブラリーをJavaScriptに変換するのが主な使い方でしょう。


C言語で書かれた様々なライブラリーが、EmscriptenによってJavaScript化されています。


以下を参照してみてください。
[https://github.com/kripken/emscripten/wiki/Porting-Examples-and-Demos](https://github.com/kripken/emscripten/wiki/Porting-Examples-and-Demos)

Lua や mRuby などの、プログラム言語や、ffmpegなどのVideoコンバーター
などなど、

様々なライブラリーのデモが用意されています。



## SDL は、マルチメディアライブラリー

[https://en.wikipedia.org/wiki/SDL](https://en.wikipedia.org/wiki/SDL)
SDL は、Simple Media Library の略語です。 C言語で書かれた、クロスプラットフォームのライブラリーです。
グラフィックやサウンドの再生すうアプリを作成できます。

基本的には、OSの違いを吸収する最低限のAPIが用意されています。それを元に、様々なライブラいーが公開されています。

Font、Networkなどなどです。
SDLをベースにしてゲームを作成できます。そして、SDLをベースにすれば、様々な環境で動作させる事ができます。


## OpenGL は、GPUを扱うグラフィックライブラリー
[https://en.wikipedia.org/wiki/OpenGL](https://en.wikipedia.org/wiki/OpenGL)

OpenGL は、GPUを2Dや3Dのグラフィック用途に利用するためのAPI群です。

GPUを使用する事で、高速に処理できます。CPUでは時間のかかる処理も、GPUならリアルタイムに処理することができます。

ゲームでは、このGPUを利用してプログラムを書きます。


## 関連

炎の型 With Scratch の C言語版の準備編みたいな位置づけ
- 火の型 with Scratch 2.0 プログラム入門　　https://www.gitbook.com/book/kyorohiro/firestyle/details
- 炎の型 With Scratch 2.0 (ゲームプログラム入門) https://www.gitbook.com/book/kyorohiro/doc_scratch/details
