# Windows に インストールしてみよう

C言語の開発環境をインストールしてみましょう。

http://emscripten.org で配布されている、インストーラーを実行して開発環境を作ります。

emscriptenのサイトに記載されている通りで良いのですが、軽く解説します。

1. [http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html) に移動

2. emsdk-portable-64bit.zip をクリックしてダウンロード

3. ダウンロードした ファイルを解答する。

4. command line を開く

5. 3で回答したemsdk-portable-64bit 配下に移動する

6. emsdk.bat update

7. emsdk.bat install latest

8. emsdk.bat activate latest

9. emsdk_env.bat

で、emsdが使えるようになります。
試しに、where emcc と打ち込んでみましょう。

```
>where emcc
C:¥../emsdk-portable/emscripten/1.37.21/emcc
```
などと、表示されれば、多分OKです。
