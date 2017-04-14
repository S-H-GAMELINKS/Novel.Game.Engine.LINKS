//ゲームリンクス開発 簡易ノベルゲームエンジン「ＬＩＮＫＳ」ver2.80
#include "DxLib.h"
#include "stdio.h"
#include "GAME.h"
#include "DEF.h"
#include "resource.h"

// 文字列描画の位置
extern int DrawPointX, DrawPointY;

// 参照する文字列番号と文字列中の文字ポインタ
extern int SP, CP;

//スクリプト読込変数
extern int ScriptFile;

//スクリプト用読込配列
extern char String[GYOU][RETU];

//タイトル関連
extern int TITLE;
extern unsigned int Cr;

//エンドフラグ
extern int EndFlag;

//既読スキップ変数
extern int LINKS;
extern int A;
extern int B;
extern int C;
extern int D;
extern int E;
extern int F;
extern int G;
extern int H;
extern int I;
extern int J;
extern int K;
extern int L;
extern int M;
extern int N;

//設定用変数
extern int BGM_VOL;
extern int SE_VOL;
extern int BGM_VOL_COUNT;
extern int SE_VOL_COUNT;

//バックログ変数
extern char *BACKLOG_DELETE;

//セーブ用変数
extern int SAVE, SAVE_CHOICE;
extern char *SAVESNAP_CHOICE_DELETE;

//スキップ・オートモード用変数
extern int skip_auto;
extern int SKIP_SPEED;
extern int SKIP_SPEED_COUNT;
extern int AUTO_SPEED;
extern int AUTO_SPEED_COUNT;

//キー操作
extern int Key[256];
extern int y;
extern int SAVE_y;
extern int GAME_y;

//DXライブラリ初期化前処理
void DXLib_PREP() {

	//ログの抽出
	SetOutApplicationLogValidFlag(FALSE);

	//アイコン
	SetWindowIconID(101);

	//ウインドウに表示されるゲームソフト名
	SetWindowText("ノベルゲームエンジン「LINKS」");

	//ウインドウを自由に変更できる
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);

	//ウインドウ描画の種類
	SetDrawMode(DX_DRAWMODE_NEAREST);

	//ウインドウの種類
	SetWindowStyleMode(7);

	//初期ウインドウサイズ
	SetWindowSize(640, 480);

	//ウインドウモードで起動
	ChangeWindowMode(TRUE);
}

//DXライブラリ初期化後処理
void DXLib_POST_PREP() {

	//マウス描画設定
	SetMouseDispFlag(TRUE);

	//DXアーカイブ機能の使用
	SetUseDXArchiveFlag(TRUE);

	//各素材データ読込
	MATERIAL_LOAD();

	// フォントのサイズセット
	SetFontSize(MOJI_SIZE);

	//フォントの設定
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//ゲームリンクスロゴ表示
	PlayMovie("DATA/MOVIE/OP.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);

	//OP画面の削除
	ClearDrawScreen();
	WaitTimer(600);

	//設定の読込
	CONFIG_LOAD();
}

//タイトルメニュー(キー操作)
void TITLE_MENU_KEY_MOVE() {

	if (Key[KEY_INPUT_DOWN] == 1) {
		y += CURSOR;
		if (y == (GAMEQUIT + CURSOR))
			y = GAMESTART;
	}

	if (Key[KEY_INPUT_UP] == 1) {
		y -= CURSOR;
		if (y == (GAMESTART - CURSOR))
			y = GAMEQUIT;
	}
}

//タイトルメニュー終了処理
void TITLE_MENU_END() {

	SAVE = MessageBox(
		NULL,
		"終了しますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

	if (SAVE == IDYES)
		EndFlag = 99999;

	WaitTimer(300);
}

//タイトルメニュー(選択処理)
void TITLE_MENU_CHOICE() {

	if (y == GAMESTART && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == GAMESTART && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		EndFlag = 1;

	if (y == GAMELOAD && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == GAMELOAD && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		SAVEDATA_LOAD();

	if (y == GAMECONFIG && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == GAMECONFIG && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		CONFIG();

	if (y == QUICKLOAD && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == QUICKLOAD && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		QUICKSAVE_LOAD();

	if (y == GAMEQUIT && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == GAMEQUIT && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		TITLE_MENU_END();
}

//タイトルメニュー関数
void TITLE_MENU() {

	//タイトルメニュー
	if (EndFlag == 99) {

		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && EndFlag == 99) {

			//タイトル表示
			DrawGraph(0, 0, TITLE, TRUE);

			//タイトルメニュー表示
			title(Cr, y);

			//スクリーンショット機能
			SCREENSHOT();

			//マウス操作
			Mouse_Move();

			//キー操作関連
			TITLE_MENU_KEY_MOVE();

			//画面クリア処理
			SCREEN_CLEAR();

			//タイトルメニュー(選択処理)
			TITLE_MENU_CHOICE();

			//終了ウインドウ
			GAME_FINISH();
		}
	}
}

//参照文字列処理
void WORD_FORMAT() {

	// 参照文字列の終端まで行っていたら参照文字列を進める
	if (String[SP][CP] == '\0')
	{
		SP++;
		CP = 0;
	}
}

//ゲームのループ(LINKS)
void GAME_LOOP_LINKS() {

	//メインルート
	if (EndFlag == 1) {

		if (LINKS == 0)
			skip_auto = 0;

		//メインスクリプト読込
		SCRIPT_READ();

		//メインループ(LINKS)
		while (EndFlag != 99 && ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが1でなかったら終了する。
			if (EndFlag != 1 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				LINKS = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(A)
void GAME_LOOP_A() {

	//Aルート
	if (EndFlag == 2) {

		if (A == 0)
			skip_auto = 0;

		//Aルートスクリプト読込
		SCRIPT_READ();

		//Ａルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが2でなかったら終了する
			if (EndFlag != 2 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				A = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(B)
void GAME_LOOP_B() {

	//Bルート
	if (EndFlag == 3) {

		if (B == 0)
			skip_auto = 0;

		//Bルートスクリプト読込
		SCRIPT_READ();

		//Bルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが3でなかったら終了する
			if (EndFlag != 3 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				B = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(C)
void GAME_LOOP_C() {

	//Cルート
	if (EndFlag == 4) {

		if (C == 0)
			skip_auto = 0;

		//Cルートスクリプト読込
		SCRIPT_READ();

		//Cルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが4でなかったら終了する
			if (EndFlag != 4 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				C = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(D)
void GAME_LOOP_D() {

	//Dルート
	if (EndFlag == 5) {

		if (D == 0)
			skip_auto = 0;

		//Dルートスクリプト読込
		SCRIPT_READ();

		//Dルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが5でなかったら終了する
			if (EndFlag != 5 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				D = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(E)
void GAME_LOOP_E() {

	//Eルート
	if (EndFlag == 6) {

		if (E == 0)
			skip_auto = 0;

		//Eルートスクリプト読込
		SCRIPT_READ();

		//Eルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが2でなかったら終了する
			if (EndFlag != 6 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				E = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(F)
void GAME_LOOP_F() {

	//Fルート
	if (EndFlag == 7) {

		if (F == 0)
			skip_auto = 0;

		//Fルートスクリプト読込
		SCRIPT_READ();

		//Fルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが7でなかったら終了する
			if (EndFlag != 7 && EndFlag != 99999) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				F = 1;
				SKIP_READ_SAVE();
				break;
			}

			if (EndFlag == 99999)
				break;

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(G)
void GAME_LOOP_G() {

	//Gルート
	if (EndFlag == 8) {

		if (G == 0)
			skip_auto = 0;

		//Gルートスクリプト読込
		SCRIPT_READ();

		//Gルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが7でなかったら終了する
			if (EndFlag != 8) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(H)
void GAME_LOOP_H() {

	//Hルート
	if (EndFlag == 9) {

		if (H == 0)
			skip_auto = 0;

		//Hルートスクリプト読込
		SCRIPT_READ();

		//Hルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが7でなかったら終了する
			if (EndFlag != 9) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(I)
void GAME_LOOP_I() {

	//Iルート
	if (EndFlag == 10) {

		if (I == 0)
			skip_auto = 0;

		//Iルートスクリプト読込
		SCRIPT_READ();

		//Iルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが7でなかったら終了する
			if (EndFlag != 10) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(J)
void GAME_LOOP_J() {

	//Jルート
	if (EndFlag == 11) {

		if (J == 0)
			skip_auto = 0;

		//Jルートスクリプト読込
		SCRIPT_READ();

		//Jルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが7でなかったら終了する
			if (EndFlag != 11) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(K)
void GAME_LOOP_K() {

	//Kルート
	if (EndFlag == 12) {

		if (K == 0)
			skip_auto = 0;

		//Kルートスクリプト読込
		SCRIPT_READ();

		//Kルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが7でなかったら終了する
			if (EndFlag != 12) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(L)
void GAME_LOOP_L() {

	//Lルート
	if (EndFlag == 13) {

		if (L == 0)
			skip_auto = 0;

		//Lルートスクリプト読込
		SCRIPT_READ();

		//Lルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが7でなかったら終了する
			if (EndFlag != 13) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(M)
void GAME_LOOP_M() {

	//Mルート
	if (EndFlag == 14) {

		if (M == 0)
			skip_auto = 0;

		//Mルートスクリプト読込
		SCRIPT_READ();

		//Mルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが7でなかったら終了する
			if (EndFlag != 14) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ(N)
void GAME_LOOP_N() {

	//Nルート
	if (EndFlag == 15) {

		if (N == 0)
			skip_auto = 0;

		//Nルートスクリプト読込
		SCRIPT_READ();

		//Nルートループ
		while (ProcessMessage() == 0)
		{
			//タグ処理
			SCRIPT_OUTPUT();

			//ゲームメニュー
			GAMEMENU();

			//スクリーンショット取得
			SCREENSHOT();

			//ショートカットキー
			SHORTCUT_KEY();

			//終了
			GAME_FINISH();

			// 終了フラグが7でなかったら終了する
			if (EndFlag != 15) {

				if (SAVE_CHOICE == 0)
					FORMAT();

				break;
			}

			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

//ゲームのループ
void GAME_LOOP() {

	//ゲームのループ(LINKS)
	GAME_LOOP_LINKS();
	
	//ゲームのループ(A)
	GAME_LOOP_A();

	//ゲームのループ(B)
	GAME_LOOP_B();

	//ゲームのループ(C)
	GAME_LOOP_C();

	//ゲームのループ(D)
	GAME_LOOP_D();

	//ゲームのループ(E)
	GAME_LOOP_E();

	//ゲームのループ(F)
	GAME_LOOP_F();

	//ゲームのループ(G)
	GAME_LOOP_G();

	//ゲームのループ(H)
	GAME_LOOP_H();

	//ゲームのループ(I)
	GAME_LOOP_I();

	//ゲームのループ(J)
	GAME_LOOP_J();

	//ゲームのループ(K)
	GAME_LOOP_K();

	//ゲームのループ(L)
	GAME_LOOP_L();

	//ゲームのループ(M)
	GAME_LOOP_M();

	//ゲームのループ(N)
	GAME_LOOP_N();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//DXライブラリ初期化前処理
	DXLib_PREP();

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)	
	{
		// エラーが起きたら直ちに終了
		return -1;
	}

	//DXライブラリ初期化後処理
	DXLib_POST_PREP();

	while (ProcessMessage() == 0 && EndFlag != 99999) {

		//タイトルメニュー
		TITLE_MENU();

		//各種ゲームループ
		GAME_LOOP();
	}

	//設定の保存
	CONFIG_SAVE();

	//バックログ画像の削除
	BACKLOG_DELETE = "DATA/BACKLOG/BACKLOG1.png";
	remove(BACKLOG_DELETE);

	//選択肢セーブスナップ削除
	SAVESNAP_CHOICE_DELETE = "DATA/SAVE/SAVESNAP_CHOICE.png";
	remove(SAVESNAP_CHOICE_DELETE);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}