//ゲームリンクス開発 簡易ノベルゲームエンジン「ＬＩＮＫＳ」ver3.00
#include "DxLib.h"
#include "stdio.h"
#include "GAME.h"
#include "DEF.h"
#include "resource.h"

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
	SetFontSize(font_size);

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
		y = (title_menu_game_quit_pos_y == y) ? title_menu_game_start_pos_y : y + cursor_move_unit;
	}

	if (Key[KEY_INPUT_UP] == 1) {
		y = (title_menu_game_start_pos_y == y) ? title_menu_game_quit_pos_y : y - cursor_move_unit;
	}
}

//タイトルメニュー終了処理
void TITLE_MENU_END() {

	SAVE = LINKS_MessageBox_YESNO("終了しますか？");

	if (SAVE == IDYES)
		EndFlag = 99999;

	WaitTimer(300);
}

//タイトルメニュー(選択処理)
void TITLE_MENU_CHOICE() {

	if (y == title_menu_game_start_pos_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == title_menu_game_start_pos_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		EndFlag = 1;

	if (y == title_menu_game_load_pos_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == title_menu_game_load_pos_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		SAVEDATA_LOAD();

	if (y == title_menu_game_config_pos_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == title_menu_game_config_pos_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		CONFIG();

	if (y == title_menu_quick_load_pos_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == title_menu_quick_load_pos_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		QUICKSAVE_LOAD();

	if (y == title_menu_continue_pos_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == title_menu_continue_pos_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
		CONTINUE_LOAD();

	if (y == title_menu_game_quit_pos_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == title_menu_game_quit_pos_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0))
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

static void GameLoopType1(const int RouteNumber, int32_t& TextIgnoredFlag){
	if (EndFlag == RouteNumber) {
		if (TextIgnoredFlag == 0) skip_auto = 0;
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
			if (EndFlag != RouteNumber && EndFlag != 99999) {
				if (SAVE_CHOICE == 0) FORMAT();
				TextIgnoredFlag = 1;
				SKIP_READ_SAVE();
				break;
			}
			if (EndFlag == 99999) break;
			//参照文字列処理
			WORD_FORMAT();
		}
	}
}

static void GameLoopType2(const int RouteNumber, const int32_t TextIgnoredFlag){
	if (EndFlag == RouteNumber) {
		if (TextIgnoredFlag == 0) skip_auto = 0;
		SCRIPT_READ();
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
			if (EndFlag != RouteNumber) {
				if (SAVE_CHOICE == 0) FORMAT();
				break;
			}
			//参照文字列処理
			WORD_FORMAT();
		}
	}
}
//ゲームのループ(LINKS)
void GAME_LOOP_LINKS() {
	//メインルート
	GameLoopType1(1, TextIgnoredFlag.LINKS);
}

//ゲームのループ(A)
void GAME_LOOP_A() {
	GameLoopType1(2, TextIgnoredFlag.A);
}

//ゲームのループ(B)
void GAME_LOOP_B() {
	GameLoopType1(3, TextIgnoredFlag.B);
}

//ゲームのループ(C)
void GAME_LOOP_C() {
	GameLoopType1(4, TextIgnoredFlag.C);
}

//ゲームのループ(D)
void GAME_LOOP_D() {
	GameLoopType1(5, TextIgnoredFlag.D);
}

//ゲームのループ(E)
void GAME_LOOP_E() {
	GameLoopType1(6, TextIgnoredFlag.E);
}

//ゲームのループ(F)
void GAME_LOOP_F() {
	GameLoopType1(7, TextIgnoredFlag.F);
}

//ゲームのループ(G)
void GAME_LOOP_G() {
	GameLoopType2(8, TextIgnoredFlag.G);
}

//ゲームのループ(H)
void GAME_LOOP_H() {
	GameLoopType2(9, TextIgnoredFlag.H);
}

//ゲームのループ(I)
void GAME_LOOP_I() {
	GameLoopType2(10, TextIgnoredFlag.I);
}

//ゲームのループ(J)
void GAME_LOOP_J() {
	GameLoopType2(11, TextIgnoredFlag.J);
}

//ゲームのループ(K)
void GAME_LOOP_K() {
	GameLoopType2(12, TextIgnoredFlag.K);
}

//ゲームのループ(L)
void GAME_LOOP_L() {
	GameLoopType2(13, TextIgnoredFlag.L);
}

//ゲームのループ(M)
void GAME_LOOP_M() {
	GameLoopType2(14, TextIgnoredFlag.M);
}

//ゲームのループ(N)
void GAME_LOOP_N() {
	GameLoopType2(15, TextIgnoredFlag.N);
}

//ゲームのループ
void GAME_LOOP() {
	GAME_LOOP_LINKS();
	GAME_LOOP_A();
	GAME_LOOP_B();
	GAME_LOOP_C();
	GAME_LOOP_D();
	GAME_LOOP_E();
	GAME_LOOP_F();
	GAME_LOOP_G();
	GAME_LOOP_H();
	GAME_LOOP_I();
	GAME_LOOP_J();
	GAME_LOOP_K();
	GAME_LOOP_L();
	GAME_LOOP_M();
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
