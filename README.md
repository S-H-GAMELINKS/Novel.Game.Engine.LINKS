# Novel.Game.Engine.LINKS
元々は、サークル内で使用する予定だったものをexe形式で配布していました。

ver2.60より、オープンソースソフトウェアとしてリリース開始。


・基本的な使用方法。

まず、書き上げた小説などを「LINKS.txt」内にコピー&ペーストする。
次に、タグ一覧に記載されているタグを「LINKS.txt」内の任意の場所に入力していく。
このとき注意されたいのはABなどの半角かつ大文字のアルファベットと、01などの半角の数字をタグとして
「LINKS」は認識することである。
そのため半角大文字のアルファベットなどを小説内で使用している場合、そのアルファベットをタグとして
認識してしまうので注意すること。
また半角スペースは読み込まず、次の文字を表示してしまうのでこちらも注意すること。
ただし、全角文字（例：ＬＩＮＫＳ等）はタグとして認識しない。
スペースも同様に全角であれば問題ない。

・操作方法

選択肢やタイトルメニュー等の項目選択は上下の十字キー、またはマウスポインタ。
決定はENTERキー。メニューはBACKSPACEキー、又は右クリック。ゲームの終了はESCAPEキーとなっています。

・メニュー画面について

　・基本操作
　　
　　基本的に上下の十字キー（またはマウスポインタ）でカーソルを動かし、項目を選択します。
　　またカーソルを合わせた状態でENTERキー（左クリック）を押すことでセーブ画面などに移ります。

以下、各項目で利用できる機能について

　・セーブ
　　
　　セーブを行います。セーブデータは1から3まであります。
　　メニューに戻るを押すことでメニュー画面に戻れます。


　・ロード
　　
　　ロードを行います。セーブデータは同様に3つありますので、そこからロードしてください。
　　また、メニューに戻るを押すことでメニュー画面に戻れます。


　・セーブデータ削除

　　セーブデータを削除します。セーブされたものの中から削除したいものを選んで削除してください。
　　メニューへ戻るには、メニューに戻るを押してください。


　・既読スキップ

　　既読スキップ機能を実行します。


　・スキップ

　　スキップを実行します。


　・オート

　　オートモードを実行します。


　・オート/スキップ停止

　　オート/スキップ機能を停止します。


　・バックログ参照

　　バックログ参照中は上下の十字キーで参照するログを変更できます。
　　（マウスの場合、左クリックでより以前のログを、右クリックでより最新のログを参照できます）
　　ENTERキー（又はマウスの左右を同時クリック）でバックログを終了します。
　　バックログ1が最新のログ、バックログ10が最も古いログとなります。

　・設定

　　左右の十字キーを押すことで音量や速度を調整できます。
　　（マウスの場合、左クリックで数値を増やし、右クリックで減らします）
　　なお、音量は数値が多いほど大きくなり、少ないほど小さくなります。

　　また、文字描画速度・オート・スキップの速度は数値が少ないほど速くなり、多いほど遅くなります。

　　左右の十字キーを押すことで、ウインドウ風の描画とサウンドノベル風の描画を切り替えることができます。
　　（マウスの場合、左クリックでサウンドノベル風の描画、右クリックでウインドウ風の描画へと切り替わります）

　　左右の十字キーを押すことで、ウインドウが非アクティブ時のゲーム進行を切り替えることができます。
　　処理の場合、非アクティブ時にもゲームが進行します。未処理の場合は、進行しません。
　　（マウスの場合、左クリックで未処理、右クリックで処理へと切り替わります）

　　左右の十字キーを押すことで、マウス操作/キーボード操作を切り替えることができます。
　　（マウスの場合、左クリックでマウス操作、右クリックでキーボード操作へと切り替わります）

　　メニュー/タイトル画面に戻る場合は、「メニューに戻る」または「タイトルに戻る」へカーソルを移動してから
　　ENTERキー(又は左クリック)を押してください。

　・タイトルに戻る

　　タイトル画面に戻ります。


　・ゲームに戻る

　　ゲームに戻ります。


　・そのほか

　　ESCAPEキーを押すとゲームを終了します。

　　F12キーを押すことで、最大10枚のスクリーンショットが取れます。


・ファイルの配置等に関して

また、各キャラクターデータなどを格納するフォルダに入れるファイル形式は以下の通りである。

DATA/STR:TXT形式のファイルを使用する。メインスクリプトは「LINKS.txt」であり、選択肢の分岐により
　　最大A～Fまでのサブスクリプトを使用することができる。
    注意：仕様により一行500文字程度までしか読み込めません。
	　また、各スクリプトファイルごとに50万行までしか読み込みません
	　(恐らく、一つのスクリプトファイルにそこまで書く人はいないと思いますが…。一応念のため。)

DATA/STR/CHOICE:選択肢として出てくる文章を編集することができる。250文字程度まで読み込める。

DATA/SOUNDEFFECT:OGG形式のファイルを入れる。各タグに対応して、SE01～SE12まで番号が振れる。

DATA/SAVE:セーブデータの保存場所である。セーブデータは3つ保管できる。その他、セーブデータ用スクリーンショットも保存される。

DATA/MOVIE:WMV形式のMOVIE01～MOVIE04のファイルを入れる場所。なお、OP.wmvを置くことでオープニングを作ることもできる。
      その他、ENDING.wmvを入れることでエンディングムービーを流すこともできる。

DATA/CHARACTER:PNG形式のキャラクターの立ち絵を入れる場所。最大12枚使用可能。CHAR01～CHAR12まで番号を振れる。
	　なお、サイズは300×400のものを使用し、透過処理を行う必要がある。

DATA/BACKGROUNDMUSIC:OGG形式の音源を入れることでBGMを再生できる。最大12曲使用でき、BGM01～BGM12まで番号を振れる。

DATA/BACKGROUND:PNG形式の背景画像を入れる場所。640×480のサイズを使用する。BG01～BG12まで使用可能
		タイトル画像は"TITLE.png", ゲームオーバー画面は"GAMEOVER.png"となっている。
		セーブ・ロード画面は"SAVE.png"

――――――――――――――――――――――――――――――――――

更新履歴

2017/04/13	F1～F11の各種キーを押すことで、セーブ・ロードなどの機能を利用可能に。ver2.80

2017/04/05	マウス操作とキーボード操作の切り替え実装。また、キーボード操作時の挙動を修正。
			タイトル画面でESCAPEキーを押すことでゲーム終了可能に。
			そのほか、セーブデータロード時のスクリプト行管理を修正。ver2.75

2017/03/29	大幅なリファクタリングによりソースコードを短縮。
			また、設定関連の描画を数値に変更。ver2.70

2017/03/18  	オープンソースソフトウェアとしてリリース開始。
		「#」タグにて、キャラクター名を描画可能に(ウインドウ風のみ)。
		設定にて、ウインドウの非アクティブ時にゲームが進行するか切り替え可能に。
		セーブデータのロード時の画面のちらつきを修正。ver2.60

2017/02/17	コンフィグデータがない状況でのエラーメッセージの削除。
		ゲーム画面をサウンドノベル風とウインドウ風に切り替え可能に仕様変更。
		(※ウインドウ風での描画は4行程度しか文字列を描画できません)
		タイトル画面でコンフィグを開けるように変更。バックログの増設と修正。ver2.50

2017/01/15	マウス操作に対応（詳細は仕様にて）。セーブデータのロード関連のバグ修正。ver2.40

2016/12/27  	F12キーでスクリーンショットが撮れるように。既読スキップ関連での挙動など細かな修正。ver2.35

2016/12/06	細かな修正。クイックセーブ・クイックロード機能の実装。選択肢画面でのメニュー機能が使用可能。選択肢画面でのセーブを実装。ver2.30

2016/10/23	細かな修正。立ち絵削除タグ「@」の実装、設定データの保存。ver2.20

2016/8/26	細かなバグや不具合の修正。BGMやSEの音量調整とスキップ・オート速度調整機能の実装。ver2.15

2016/8/17	バックログ機能の改良。セーブデータ削除機能の追加。メニュー画面の実装。ver2.00

2016/8/05	簡易バックログ機能の追加。ver1.75

2016/7/25	セーブ・ロード画面の実装。またセーブデータ数を3個に増設。同時にスクリーンショットをセーブ・ロード画面に表示。ver1.70

2016/7/17	細かな修正。最大化ボタンの導入。ver1.52

2016/7/15	スキップなどのキー操作関連と、ウインドウの大きさを自由に変更できるように仕様変更。ver1.50

2016/7/10	選択肢の数を7個に増設。既読スキップ機能の追加ver1.45

2016/7/07	スキップ・オートモード機能の追加。ファイルパスの変更。ver1.25

2016/7/01	タグ処理なしで立ち絵画像を差し替えるように変更。
		それに付随して、文字列を7行描画した後に、自動改ページを行うよう変更。文字サイズの変更。ver1.10

2016/6/23	効果音再生時に処理が停止するバグを処置。ver1.02

2016/6/20	LINKS公開。ver1.00

――――――――――――――――――――――――――――――――――

以下、参考サイト

DXライブラリ置き場
URL:http://dxlib.o.oo7.jp/

DXライブラリ掲示板
URL:http://dxlib.o.oo7.jp/cgi/patiobbs/patio.cgi

ゲームプログラミングの館
URL:http://dixq.net/g/

C言語何でも質問掲示板
URL:http://dixq.net/forum/viewforum.php?f=3

「LINKS」開発にあたっては上記の素晴らしいサイトにて
公開されているソースコードを参考にさせていただきました。
この場を借りて感謝いたします。

また、ノベルゲームエンジン「LINKS」はDXライブラリを使用して制作しています。
DX Library Copyright (C) 2001-2017 Takumi Yamada.


以下は、DXライブラリにて使用されている各ライブラリの著作権表記となります。

　libjpeg　Copyright (C) 1991-2013, Thomas G. Lane, Guido Vollbeding.


　　　libpng　Copyright (C) 2004, 2006-2012 Glenn Randers-Pehrson.
　　　zlib　Copyright (C) 1995-2012 Jean-loup Gailly and Mark Adler.


　　　libtiff　Copyright (c) 1988-1997 Sam Leffler
　　　libtiff　Copyright (c) 1991-1997 Silicon Graphics, Inc.

　　　Permission to use, copy, modify, distribute, and sell this software and
　　　its documentation for any purpose is hereby granted without fee, provided
　　　that (i) the above copyright notices and this permission notice appear in
　　　all copies of the software and related documentation, and (ii) the names of
　　　Sam Leffler and Silicon Graphics may not be used in any advertising or
　　　publicity relating to the software without the specific, prior written
　　　permission of Sam Leffler and Silicon Graphics.

　　　THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
　　　EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
　　　WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.

　　　IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
　　　ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
　　　OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
　　　WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
　　　LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
　　　OF THIS SOFTWARE.


　　　libogg　Copyright (C) 2002-2009 Xiph.org Foundation

　　　Redistribution and use in source and binary forms, with or without
　　　modification, are permitted provided that the following conditions
　　　are met:

　　　- Redistributions of source code must retain the above copyright
　　　notice, this list of conditions and the following disclaimer.

　　　- Redistributions in binary form must reproduce the above copyright
　　　notice, this list of conditions and the following disclaimer in the
　　　documentation and/or other materials provided with the distribution.

　　　- Neither the name of the Xiph.org Foundation nor the names of its
　　　contributors may be used to endorse or promote products derived from
　　　this software without specific prior written permission.

　　　THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
　　　``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
　　　LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
　　　A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION
　　　OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
　　　SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
　　　LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
　　　DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
　　　THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
　　　(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
　　　OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


　　　Opus audio codec
　　　Copyright 2001-2011 Xiph.Org, Skype Limited, Octasic,
　　　 Jean-Marc Valin, Timothy B. Terriberry,
　　　 CSIRO, Gregory Maxwell, Mark Borgerding,
　　　 Erik de Castro Lopo

　　　Redistribution and use in source and binary forms, with or without
　　　modification, are permitted provided that the following conditions
　　　are met:

　　　- Redistributions of source code must retain the above copyright
　　　notice, this list of conditions and the following disclaimer.

　　　- Redistributions in binary form must reproduce the above copyright
　　　notice, this list of conditions and the following disclaimer in the
　　　documentation and/or other materials provided with the distribution.

　　　- Neither the name of Internet Society, IETF or IETF Trust, nor the
　　　names of specific contributors, may be used to endorse or promote
　　　products derived from this software without specific prior written
　　　permission.

　　　THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
　　　``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
　　　LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
　　　A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
　　　OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
　　　EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
　　　PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
　　　PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
　　　LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
　　　NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
　　　SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


　　　Opusfile
　　　Copyright (c) 1994-2013 Xiph.Org Foundation and contributors

　　　Redistribution and use in source and binary forms, with or without
　　　modification, are permitted provided that the following conditions
　　　are met:

　　　- Redistributions of source code must retain the above copyright
　　　notice, this list of conditions and the following disclaimer.

　　　- Redistributions in binary form must reproduce the above copyright
　　　notice, this list of conditions and the following disclaimer in the
　　　documentation and/or other materials provided with the distribution.

　　　- Neither the name of the Xiph.Org Foundation nor the names of its
　　　contributors may be used to endorse or promote products derived from
　　　this software without specific prior written permission.

　　　THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
　　　``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
　　　LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
　　　A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FOUNDATION
　　　OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
　　　SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
　　　LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
　　　DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
　　　THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
　　　(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
　　　OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


　　　Mersenne Twister
　　　Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
　　　All rights reserved.

　　　Redistribution and use in source and binary forms, with or without
　　　modification, are permitted provided that the following conditions
　　　are met:

　　　1. Redistributions of source code must retain the above copyright
　　　notice, this list of conditions and the following disclaimer.

　　　2. Redistributions in binary form must reproduce the above copyright
　　　notice, this list of conditions and the following disclaimer in the
　　　documentation and/or other materials provided with the distribution.

　　　3. The name of the author may not be used to endorse or promote products
　　　derived from this software without specific prior written permission.

　　　THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
　　　IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
　　　OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
　　　IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
　　　INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
　　　NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
　　　DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
　　　THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
　　　(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
　　　THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


　　　Bullet　Copyright (c) 2003-2006 Erwin Coumans.

