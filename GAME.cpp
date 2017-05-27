//ライブラリとヘッダの読み込み
#include "DxLib.h"
#include "DEF.h"
#include <cassert>
#include "GAME.h"

#if defined(_MSC_VER) && 1400 <= _MSC_VER
#	define LINKS_HAS_CRT_SECURE_FUNCTIONS 1
#endif
#if defined(__STDC_LIB_EXT1__) || defined(LINKS_HAS_CRT_SECURE_FUNCTIONS)
#	define LINKS_C11_CRT_BOTH_SECURE_FUNCTIONS 1
#	define LINKS_HAS_FOPEN_S 1
#endif
#ifdef _countof
#	define countof _countof
#else
#	define countof( arr ) ( sizeof(arr) / sizeof(*arr) )
#endif
// 文字列描画の位置
int DrawPointX = 0, DrawPointY = 0;

// 参照する文字列番号と文字列中の文字ポインタ
int SP = 0, CP = 0;

//キャラクター画像読込変数
long CHARACTER_LOAD[100];
int CHARACTER, CHARACTER_DUMMY;

//背景画像読込変数
long BACKGROUND_LOAD[100];
int BACKGROUND;

//背景音楽読込変数
long BACKGROUNDMUSIC_LOAD[100];
int BACKGROUNDMUSIC;

//効果音変数
long SOUNDEFFECT_LOAD[100];
int SOUNDEFFECT;

//スクリプト読込変数
int ScriptFile;

//スクリプト用読込配列
char String[GYOU][RETU];

//タイトル関連
int TITLE;
unsigned int Cr;

//ゲームオーバー
int GAMEOVER;

//選択肢読込変数
char ChoiceA[RETU], ChoiceB[RETU];
int Choice1, Choice2;

//エンドフラグ
int EndFlag = 99;

//ゲームメニュー変数
int GAMEMENU_COUNT;

//既読スキップ変数
int LINKS = 0;
int A = 0;
int B = 0;
int C = 0;
int D = 0;
int E = 0;
int F = 0;
int G = 0;
int H = 0;
int I = 0;
int J = 0;
int K = 0;
int L = 0;
int M = 0;
int N = 0;

//バックログ変数
int BACKLOG_CHOICE = 0;
int BACKLOG_HANDLE, BACKLOG[11], BACKLOG_BACKGROUND;
int LOG = 1, BACKLOG_COUNT = 1;
char *BACKLOG_DELETE;

//セーブ用変数
int SAVE, SAVE_CHOICE = 0;
int SAVESNAP1, SAVESNAP2, SAVESNAP3, SAVETITLE;
int SAVESNAP_HANDLE1 = 0, SAVESNAP_HANDLE2 = 0, SAVESNAP_HANDLE3 = 0, SAVESNAP_CHOICE = 0;
char *SAVE_DATA_DELETE;
char *SAVESNAP_CHOICE_DELETE;

//スキップ・オートモード用変数
int skip_auto = 0;
int SKIP_SPEED = 100;
int SKIP_SPEED_COUNT = 10;
int AUTO_SPEED = 100;
int AUTO_SPEED_COUNT = 10;

//非アクティブ用変数
char WindowActive = TRUE;

// １文字分一時記憶配列
char OneMojiBuf[3];

//キャラクター名配列
char CHARACTER_NAME[10];

//文字描画速度用変数
int STRING_SPEED = 100;
int STRING_SPEED_COUNT = 10;

//サウンドノベル風とウインドウ風の切り替え変数
int soundnovel_winownovel = 0;

//マウス操作とキー操作の切り替え変数
int mouse_key_move = 1;

//キー操作
int Key[256];
int y = MENUY;
int SAVE_y = SAVE_Y;
int GAME_y = GAMEMENU_y;

//設定用変数
int BGM_VOL_COUNT = 10;
int SE_VOL_COUNT = 10;
int BGM_VOL = 100;
int SE_VOL = 100;
int Config = 0;

//スクリーンショット用変数
int SCREENSHOT_COUNT = 0;

//ショートカットキー用変数
short SHORTCUT_KEY_FLAG = 0;

//セーブ・ロード関連
//通常セーブデータ
typedef struct {
	int ENDFLAG;    //ENDFLAG
	int SP;			//行数
	int CP;			//文字位置
	int CHAR;		//立ち絵情報
	int BG;			//背景画像情報
	int BGM;		//BGM情報
	int SAVE_CHOICE;//選択肢画面でのセーブ情報
}SaveData_t;

//クイックセーブデータ
typedef struct {
	int ENDFLAG;    //ENDFLAG
	int SP;			//行数
	int CP;			//文字位置
	int CHAR;		//立ち絵情報
	int BG;			//背景画像情報
	int BGM;		//BGM情報
	int SAVE_CHOICE;//選択肢画面でのセーブ情報
}QuickSaveData_t;

//コンティニューセーブデータ
typedef struct {
	int ENDFLAG;    //ENDFLAG
	int SP;			//行数
	int CP;			//文字位置
	int CHAR;		//立ち絵情報
	int BG;			//背景画像情報
	int BGM;		//BGM情報
	int SAVE_CHOICE;//選択肢画面でのセーブ情報
}ContinueSaveData_t;

//既読スキップ
typedef struct {
	int LINKS;		//メインルートの既読情報
	int A;			//Aルートの既読情報
	int B;			//Bルートの既読情報
	int C;			//Cルートの既読情報
	int D;			//Dルートの既読情報
	int E;			//Eルートの既読情報
	int F;			//Fルートの既読情報
	int G;			//Gルートの既読情報
	int H;			//Hルートの既読情報
	int I;			//Iルートの既読情報
	int J;			//Jルートの既読情報
	int K;			//Kルートの既読情報
	int L;			//Lルートの既読情報
	int M;			//Mルートの既読情報
	int N;			//Nルートの既読情報
}SkipData_t;

//設定データ
typedef struct {
	int BGM_VOL;				//BGM音量情報
	int BGM_VOL_COUNT;			//BGM音量メーター情報
	int SE_VOL;					//SE音量情報
	int SE_VOL_COUNT;			//SE音量メーター情報
	int SKIP_SPEED;				//スキップ速度情報
	int SKIP_SPEED_COUNT;		//スキップ速度メーター情報
	int AUTO_SPEED;				//オート速度情報
	int AUTO_SPEED_COUNT;		//オート速度メーター情報
	int STRING_SPEED;			//文字列描画速度
	int STRING_SPEED_COUNT;		//文字列描画速度メーター情報
	int soundnovel_winownovel;	//サウンドノベル風とウインドウ風描画の情報
	int mouse_key_move;			//マウス操作とキー操作の情報
}ConfigData_t;

int LINKS_MessageBox_YESNO(LPCTSTR lpText)
{
	return MessageBox(
		GetMainWindowHandle(),
		lpText,
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);
}
static int LINKS_MessageBox_OK(LPCTSTR lpText)
{
	return MessageBox(
		GetMainWindowHandle(),
		lpText,
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_OK
	);
}


static bool SerialNumberFileLoader(long* dest_arr, size_t dest_arr_num, const char* format) {
	assert(dest_arr_num <= 40);
	for (unsigned int i = 0; i < dest_arr_num; ++i) {
		char FilePathString[40] = {};
#ifdef LINKS_C11_CRT_BOTH_SECURE_FUNCTIONS
		if(-1 == sprintf_s(FilePathString, dest_arr_num, format, i)) return false;
#else
		if(0 > snprintf(FilePathString, format, i) return false;
#endif
		dest_arr[i] = LoadGraph(FilePathString);
	}
	return true;
}

//立ち絵素材読込
void MATERIAL_LOAD_CHARACTER() {
	assert(SerialNumberFileLoader(CHARACTER_LOAD, countof(CHARACTER_LOAD), "DATA/CHARACTER/CHAR%02u.png"));
}

//背景画像読込
void MATERIAL_LOAD_BACKGROUND() {
	assert(SerialNumberFileLoader(BACKGROUND_LOAD, countof(BACKGROUND_LOAD), "DATA/BACKGROUND/BG%02u.png"));
}

//ＢＧＭ読込
void MATERIAL_LOAD_BACKGROUNDMUSIC() {
	assert(SerialNumberFileLoader(BACKGROUNDMUSIC_LOAD, countof(BACKGROUNDMUSIC_LOAD), "DATA/BACKGROUNDMUSIC/BGM%02u.ogg"));
}

//ＳＥ読込
void MATERIAL_LOAD_SOUNDEFFECT(){
	assert(SerialNumberFileLoader(SOUNDEFFECT_LOAD, countof(SOUNDEFFECT_LOAD), "DATA/SOUNDEFFECT/SE%02u.ogg"));
}

//各素材データ読込関数
void MATERIAL_LOAD() {

	//サウンドデータの読み込み形式
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);

	//キャラクター画像読込
	MATERIAL_LOAD_CHARACTER();

	//背景画像読込
	MATERIAL_LOAD_BACKGROUND();

	//ＢＧＭ読込
	MATERIAL_LOAD_BACKGROUNDMUSIC();

	//ＳＥ読込
	MATERIAL_LOAD_SOUNDEFFECT();

	//ゲームオーバー画面
	GAMEOVER = LoadGraph("DATA/BACKGROUND/GAMEOVER.png");

	// 白色の値を取得
	Cr = GetColor(255, 255, 255);

	//タイトルメニュー背景画像読込
	TITLE = LoadGraph("DATA/BACKGROUND/TITLE.png");
}

//スクリプト配列流しこみ関数
int SCRIPT_TO_ARRAY() {

	//スクリプトファイルを配列へ流し込む
	for (int i = 0; i < GYOU; i++) {
		FileRead_scanf(ScriptFile, "%s", String[i]);
	}

	return 0;
}

//スクリプト読込関数
int SCRIPT_READ() {
	const char* ScriptFileNames[] = {
		"DATA/STR/LINKS.txt",
		"DATA/STR/A.txt",
		"DATA/STR/B.txt",
		"DATA/STR/C.txt",
		"DATA/STR/D.txt",
		"DATA/STR/E.txt",
		"DATA/STR/F.txt",
		"DATA/STR/G.txt",
		"DATA/STR/H.txt",
		"DATA/STR/I.txt",
		"DATA/STR/J.txt",
		"DATA/STR/K.txt",
		"DATA/STR/L.txt",
		"DATA/STR/M.txt",
		"DATA/STR/N.txt"
	};
	if (0 < EndFlag && EndFlag <= countof(ScriptFileNames)) {
		// スクリプトファイルを開く
		ScriptFile = FileRead_open(ScriptFileNames[EndFlag]);
		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
	}
	return 0;
}

//画面クリア処理関数
void SCREEN_CLEAR() {

	//画面処理
	SetDrawScreen(DX_SCREEN_BACK);

	ClearDrawScreen();

	SetDrawScreen(DX_SCREEN_FRONT);
}

//各処理後のゲーム画面の描画(サウンドノベル風)
void SOUNDNOVEL() {

	if (soundnovel_winownovel == 0) {

		SCREEN_CLEAR();

		//背景の表示
		if (BACKGROUND != 0) {
			DrawGraph(0, 0, BACKGROUND, TRUE);
		}

		//立ち絵の表示
		if (CHARACTER != 0) {
			DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
		}

		//ＢＧＭの再生
		if (BACKGROUNDMUSIC != 0) {
			PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		}

		DrawPointY = 0;
		DrawPointX = 0;

		if (SP != 0) {
			SP = SP - 1;
			CP = EOF;
		}

		if (SP == 0) {
			SP = 0;
			CP = 0;
		}

		//選択肢ループの場合
		if (SAVE_CHOICE == 1) {
			SP = SP + 1;
			CP = 0;
		}
	}
}

//各処理後のゲーム画面の描画(ウインドウ風)
void WINDOWNOVEL() {

	//ウインドウ風描画時の処理
	if (soundnovel_winownovel == 1) {

		SCREEN_CLEAR();

		//背景の表示
		if (BACKGROUND != 0) {
			DrawGraph(0, 0, BACKGROUND, TRUE);
		}

		int	Window_Color = GetColor(0, 0, 0);

		DrawBox(0, 400, 640, 480, Window_Color, TRUE);

		//立ち絵の表示
		if (CHARACTER != 0) {
			DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
		}

		//ＢＧＭの再生
		if (BACKGROUNDMUSIC != 0) {
			PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		}

		DrawPointY = 400;
		DrawPointX = 0;

		if (SP != 0) {
			SP = SP - 1;
			CP = EOF;
		}

		if (SP == 0) {
			SP = 0;
			CP = 0;
		}

		//選択肢ループの場合
		if (SAVE_CHOICE == 1) {
			SP = SP + 1;
			CP = 0;
		}
	}
}

//矢印キー操作関数
int MoveKey(int KeyStateBuf[]) {

	//キー操作が有効な場合
	if (mouse_key_move == 0) {

		//キー入力用変数
		char GetHitKeyStateAll_Key[256];

		//キーの情報を変数へ
		GetHitKeyStateAll(GetHitKeyStateAll_Key);

		//キー入力の状況
		for (int i = 0; i < 256; i++) {
			KeyStateBuf[i] = (GetHitKeyStateAll_Key[i] == 1) ? KeyStateBuf[i] + 1 : 0;
		}
	}
	return 0;
}

//ショートカットキー処理後の描画
void SHORTCUT_KEY_DRAW() {

	if (SHORTCUT_KEY_FLAG == 1) {

		//サウンドノベル風時の処理
		SOUNDNOVEL();

		//ウインドウ風時の処理
		WINDOWNOVEL();

		SHORTCUT_KEY_FLAG = 0;
	}
}

//タイトルメニューカーソル関数
void title(int Cr, int y) {

	//カーソル
	DrawString(MENUX, y, "■", Cr);

	//各メニュー項目
	DrawString(MENUX + CURSOR, GAMESTART, "START", Cr);
	DrawString(MENUX + CURSOR, GAMELOAD, "LOAD", Cr);
	DrawString(MENUX + CURSOR, GAMECONFIG, "CONFIG", Cr);
	DrawString(MENUX + CURSOR, QUICKLOAD, "QUICKLOAD", Cr);
	DrawString(MENUX + CURSOR, CONTINUE, "CONTINUE", Cr);
	DrawString(MENUX + CURSOR, GAMEQUIT, "QUIT", Cr);
}

//セーブロードメニューカーソル関数
void SAVE_LOAD_MENU(int Cr, int SAVE_y) {

	//カーソルの描画
	DrawString(SAVE_X, SAVE_y, "■", Cr);

	//カーソル操作
	if (Key[KEY_INPUT_DOWN] == 1) {
		ClearDrawScreen();
		SAVE_y += SAVE_MOVE;
		if (SAVE_y == (SAVE_Y_MAX + SAVE_MOVE + SAVE_MOVE))
			SAVE_y = SAVE_MOVE;
	}

	if (Key[KEY_INPUT_UP] == 1) {
		ClearDrawScreen();
		SAVE_y -= SAVE_MOVE;
		if (SAVE_y == (SAVE_Y - SAVE_MOVE))
			SAVE_y = SAVE_Y_MAX + SAVE_MOVE;
	}
}

//ゲームメニューカーソル関数
void GAME_MENU_CURSOR(int Cr, int GAME_y) {
	DrawString(SAVE_X - (CURSOR * 6), GAME_y, "■", Cr);
}

//マウス操作(タイトルメニュー)
void Mouse_Move_TITLE(int MouseY) {
	//タイトルメニュー
	if (EndFlag == 99) {
		y = (MouseY <= 329) ? 300
			: (MouseY <= 359) ? 330
			: (MouseY <= 389) ? 360
			: (MouseY <= 419) ? 390
			: (MouseY <= 449) ? 420
			: 450;
	}
}

//マウス操作(ゲームメニュー)
void Mouse_Move_GAME(int MouseY) {
	//ゲームメニュー
	if (EndFlag == 99 || EndFlag != 99 && GAMEMENU_COUNT == 0 && Config == 0) {
		GAME_y = (MouseY <= 59) ? 30
			: (MouseY <= 89) ? 60
			: (MouseY <= 119) ? 90
			: (MouseY <= 149) ? 120
			: (MouseY <= 179) ? 150
			: (MouseY <= 209) ? 180
			: (MouseY <= 239) ? 210
			: (MouseY <= 269) ? 240
			: (MouseY <= 299) ? 270
			: (MouseY <= 329) ? 300
			: (MouseY <= 359) ? 330
			: 360;
	}
}

//マウス操作(セーブ画面関連)
void Mouse_Move_SAVE(int MouseY) {

	if (GAMEMENU_COUNT == 0 && EndFlag != 99 || EndFlag == 99) {
		SAVE_y = (MouseY <= 199) ? 100
			: (MouseY <= 299) ? 200
			: (MouseY <= 399) ? 300
			: 400;
	}
}

//マウス操作(選択肢画面)
void Mouse_Move_CHOICE(int MouseY) {
	//選択肢画面
	if (EndFlag == 1 || EndFlag == 2 || EndFlag == 3 || EndFlag == 4 || EndFlag == 5 || EndFlag == 6 || EndFlag == 7) {
		y = (MouseY <= 229) ? 200 : 230;
	}
}

//マウス操作(コンフィグ)
void Mouse_Move_CONFIG(int MouseY) {

	//コンフィグ画面
	if (Config == 1) {
		GAME_y = (MouseY <= 59) ? 30
			: (MouseY <= 89) ? 60
			: (MouseY <= 119) ? 90
			: (MouseY <= 149) ? 120
			: (MouseY <= 179) ? 150
			: (MouseY <= 209) ? 180
			: (MouseY <= 239) ? 210
			: (MouseY <= 269) ? 240
			: 270;
	}
}

//マウス操作
int Mouse_Move() {

	//マウスの位置情報変数
	int MouseX, MouseY;

	//マウスの位置を取得
	GetMousePoint(&MouseX, &MouseY);

	if (mouse_key_move == 1) {

		//タイトルメニュー
		Mouse_Move_TITLE(MouseY);

		//ゲームメニュー
		Mouse_Move_GAME(MouseY);

		//セーブ画面関連
		Mouse_Move_SAVE(MouseY);

		//選択肢画面
		Mouse_Move_CHOICE(MouseY);

		//コンフィグ画面
		Mouse_Move_CONFIG(MouseY);
	}
	return 0;
}

//SKIP_READ LOAD関数
int SKIP_READ_LOAD()
{
	//既読データを読み込んで、各変数に代入
	SkipData_t Data;
	FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
	const errno_t er = fopen_s(&fp, "DATA/SAVE/SKIP_READ.dat", "rb");
	if (0 != er) {
		return 0;
	}
#else
	fp = fopen("DATA/SAVE/SKIP_READ.dat", "rb");
	if (fp == NULL) {
		return 0;
	}
#endif
	fread(&Data, sizeof(Data), 1, fp);
	LINKS = Data.LINKS;
	A = Data.A;
	B = Data.B;
	C = Data.C;
	D = Data.D;
	E = Data.E;
	F = Data.F;
	G = Data.G;
	H = Data.H;
	I = Data.I;
	J = Data.J;
	K = Data.K;
	L = Data.L;
	M = Data.M;
	N = Data.N;
	return 0;
}

//SKIP_READ SAVE関数
int SKIP_READ_SAVE()
{
		//既読スキップデータ保存
		SkipData_t Data = { LINKS, A, B, C, D, E, F, G, H, I, J, K, L, M, N };
		FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
		const errno_t er = fopen_s(&fp, "DATA/SAVE/SKIP_READ.dat", "wb");
		if (0 != er) {
			return 0;
		}
#else
		fp = fopen("DATA/SAVE/SKIP_READ.dat", "wb");//バイナリファイルを開く
		if (fp == NULL) {//エラーが起きたらNULLを返す
			return 0;
		}
#endif
		fwrite(&Data, sizeof(Data), 1, fp); // SkipData_t構造体の中身を出力
		fclose(fp);//ファイルを閉じる

	return 0;

}

//CONFIG_SAVE関数
int CONFIG_SAVE()
{
	//設定データ保存
	ConfigData_t Data = { BGM_VOL, BGM_VOL_COUNT, SE_VOL, SE_VOL_COUNT, SKIP_SPEED, SKIP_SPEED_COUNT, AUTO_SPEED, AUTO_SPEED_COUNT, STRING_SPEED, STRING_SPEED_COUNT, soundnovel_winownovel, mouse_key_move };
	FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
	const errno_t er = fopen_s(&fp, "DATA/SAVE/Config.dat", "wb");
	if (0 != er) {
		return 0;
	}
#else
	fp = fopen("DATA/SAVE/Config.dat", "wb");//バイナリファイルを開く
	if (fp == NULL) {//エラーが起きたらNULLを返す
		return 0;
	}
#endif
	fwrite(&Data, sizeof(Data), 1, fp); // ConfigData_t構造体の中身を出力
	fclose(fp);//ファイルを閉じる

	return 0;
}

//CONFIG_LOAD関数
int CONFIG_LOAD()
{
	//設定データの読み込み
	ConfigData_t Data;
	FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
	const errno_t er = fopen_s(&fp, "DATA/SAVE/Config.dat", "rb");
	if (0 != er) {
		return 0;
	}
#else
	fp = fopen("DATA/SAVE/Config.dat", "rb");
	if (fp == NULL) {
		return 0;
	}
#endif
	fread(&Data, sizeof(Data), 1, fp);

	//各種変数に代入
	BGM_VOL = Data.BGM_VOL;
	BGM_VOL_COUNT = Data.BGM_VOL_COUNT;
	SE_VOL = Data.SE_VOL;
	SE_VOL_COUNT = Data.SE_VOL_COUNT;
	SKIP_SPEED = Data.SKIP_SPEED;
	SKIP_SPEED_COUNT = Data.SKIP_SPEED_COUNT;
	AUTO_SPEED = Data.AUTO_SPEED;
	AUTO_SPEED_COUNT = Data.AUTO_SPEED_COUNT;
	STRING_SPEED = Data.STRING_SPEED;
	STRING_SPEED_COUNT = Data.STRING_SPEED_COUNT;
	soundnovel_winownovel = Data.soundnovel_winownovel;
	mouse_key_move = Data.mouse_key_move;

	return 0;

}

//クイックセーブ時のメッセージ
void QUICKSAVE_SAVE_MESSAGE() {
	SAVE = LINKS_MessageBox_YESNO("クイックセーブを実行しますか？");
}

//クイックセーブ
int QUICKSAVE_SAVE(){

	//クイックセーブ時のメッセージ
	QUICKSAVE_SAVE_MESSAGE();

	if (SAVE == IDYES) {

		//クイックセーブデータの作成
		QuickSaveData_t Data = { EndFlag, SP, 0, CHARACTER, BACKGROUND, BACKGROUNDMUSIC, SAVE_CHOICE };
		FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
		const errno_t er = fopen_s(&fp, "DATA/SAVE/QUICKSAVEDATA.dat", "wb");
		if (0 != er) {
			return 0;
		}
#else
		fp = fopen("DATA/SAVE/QUICKSAVEDATA.dat", "wb");//バイナリファイルを開く
		if (fp == NULL) {//エラーが起きたらNULLを返す
			return 0;
		}
#endif
		fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t構造体の中身を出力
		fclose(fp);//ファイルを閉じる
	}

	return 0;

}

//クイックロード時のメッセージ
void QUICKSAVE_LOAD_MESSAGE() {
	SAVE = LINKS_MessageBox_YESNO("クイックロードを実行しますか？");
}

//クイックロード
int QUICKSAVE_LOAD() {

	//クイックロード時のメッセージ
	QUICKSAVE_LOAD_MESSAGE();

	if (SAVE == IDYES) {

		//クイックセーブデータの読み込み
		QuickSaveData_t Data;
		FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
		const errno_t er = fopen_s(&fp, "DATA/SAVE/QUICKSAVEDATA.dat", "rb");
		if (0 != er) {
			return 0;
		}
#else
		fp = fopen("DATA/SAVE/QUICKSAVEDATA.dat", "rb");
		if (fp == NULL) {
			return 0;
		}
#endif
		fread(&Data, sizeof(Data), 1, fp);
		EndFlag = Data.ENDFLAG;
		SP = Data.SP;
		CP = Data.CP;
		CHARACTER = Data.CHAR;
		BACKGROUND = Data.BG;
		BACKGROUNDMUSIC = Data.BGM;
		SAVE_CHOICE = Data.SAVE_CHOICE;

		GAMEMENU_COUNT = 1;

		//サウンドノベル風描画時の処理
		SOUNDNOVEL();

		//ウインドウ風描画時の処理
		WINDOWNOVEL();

		LINKS_MessageBox_OK("ロードしました！");

		fclose(fp);
	}
	return 0;
}

//コンティニュー用セーブ
int CONTINUE_SAVE() {

	//クイックセーブデータの作成
	ContinueSaveData_t Data = { EndFlag, SP, 0, CHARACTER, BACKGROUND, BACKGROUNDMUSIC, SAVE_CHOICE };
	FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
	const errno_t er = fopen_s(&fp, "DATA/SAVE/CONTINUESAVEDATA.dat", "wb");
	if (0 != er) {
		return 0;
	}
#else
	fp = fopen("DATA/SAVE/CONTINUESAVEDATA.dat", "wb");//バイナリファイルを開く
	if (fp == NULL) {//エラーが起きたらNULLを返す
		return 0;
	}
#endif
	fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t構造体の中身を出力
	fclose(fp);//ファイルを閉じる

	return 0;
}

//コンティニュー用ロード時のメッセージ
void CONTINUE_LOAD_MESSAGE() {
	SAVE = LINKS_MessageBox_YESNO("前回遊んだところから再開しますか？");
}

//コンティニュー用ロード
int CONTINUE_LOAD() {

	//コンティニュー用ロード時のメッセージ
	CONTINUE_LOAD_MESSAGE();

	if (SAVE == IDYES) {

		//コンティニューセーブデータの読み込み
		ContinueSaveData_t Data;
		FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
		const errno_t er = fopen_s(&fp, "DATA/SAVE/CONTINUESAVEDATA.dat", "rb");
		if (0 != er) {
			return 0;
		}
#else
		fp = fopen("DATA/SAVE/CONTINUESAVEDATA.dat", "rb");
		if (fp == NULL) {
			return 0;
		}
#endif
		fread(&Data, sizeof(Data), 1, fp);
		EndFlag = Data.ENDFLAG;
		SP = Data.SP;
		CP = Data.CP;
		CHARACTER = Data.CHAR;
		BACKGROUND = Data.BG;
		BACKGROUNDMUSIC = Data.BGM;
		SAVE_CHOICE = Data.SAVE_CHOICE;

		GAMEMENU_COUNT = 1;

		//サウンドノベル風描画時の処理
		SOUNDNOVEL();

		//ウインドウ風描画時の処理
		WINDOWNOVEL();

		LINKS_MessageBox_OK("ロードしました！");

		fclose(fp);
	}
	return 0;
}

//コンフィグ(キー操作)
void CONFIG_KEY_MOVE() {

	//キー操作関連
	if (Key[KEY_INPUT_DOWN] == 1) {
		GAME_y += GAMEMENU_y;
		if (GAME_y == (GAMEMENU_y * 10))
			GAME_y = GAMEMENU_y;
	}

	if (Key[KEY_INPUT_UP] == 1) {
		GAME_y -= GAMEMENU_y;
		if (GAME_y == (GAMEMENU_y - GAMEMENU_y))
			GAME_y = (GAMEMENU_y * 9);
	}
}

//コンフィグ(BGM音量調節)
void BGM_VOL_CHANGE() {

	//ＢＧＭ音量調整
	if (GAME_y == GAMEMENU_y && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);

		BGM_VOL += 10;
		BGM_VOL_COUNT += 1;

		if (BGM_VOL_COUNT >= 10) {
			BGM_VOL = 100;
			BGM_VOL_COUNT = 10;
		}
	}

	if (GAME_y == GAMEMENU_y && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);

		BGM_VOL -= 10;
		BGM_VOL_COUNT -= 1;

		if (BGM_VOL_COUNT <= 0) {
			BGM_VOL = 0;
			BGM_VOL_COUNT = 0;
		}
	}

}

//コンフィグ(SE音量調整)
void SE_VOL_CHANGE() {

	//ＳＥ音量調整
	if (GAME_y == GAMEMENU_y * 2 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 2 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);

		SE_VOL += 10;
		SE_VOL_COUNT += 1;

		if (SE_VOL_COUNT >= 10) {
			SE_VOL = 100;
			SE_VOL_COUNT = 10;
		}
	}

	if (GAME_y == GAMEMENU_y * 2 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 2 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);

		SE_VOL -= 10;
		SE_VOL_COUNT -= 1;

		if (SE_VOL_COUNT <= 0) {
			SE_VOL = 0;
			SE_VOL_COUNT = 0;
		}
	}
}

//コンフィグ(オート速度調整)
void AUTO_SPEED_CHANGE() {

	//オート速度調整
	if (GAME_y == GAMEMENU_y * 3 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 3 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);

		AUTO_SPEED += 10;
		AUTO_SPEED_COUNT += 1;

		if (AUTO_SPEED_COUNT >= 10) {
			AUTO_SPEED = 100;
			AUTO_SPEED_COUNT = 10;
		}
	}

	if (GAME_y == GAMEMENU_y * 3 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 3 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);

		AUTO_SPEED -= 10;
		AUTO_SPEED_COUNT -= 1;

		if (AUTO_SPEED_COUNT <= 0) {
			AUTO_SPEED = 0;
			AUTO_SPEED_COUNT = 0;
		}
	}
}

//コンフィグ(スキップ速度調整)
void SKIP_SPEED_CHANGE() {

	//スキップ速度調整
	if (GAME_y == GAMEMENU_y * 4 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 4 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);

		SKIP_SPEED += 10;
		SKIP_SPEED_COUNT += 1;

		if (SKIP_SPEED_COUNT >= 10) {
			SKIP_SPEED = 100;
			SKIP_SPEED_COUNT = 10;
		}
	}

	if (GAME_y == GAMEMENU_y * 4 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 4 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);

		SKIP_SPEED -= 10;
		SKIP_SPEED_COUNT -= 1;

		if (SKIP_SPEED_COUNT <= 0) {
			SKIP_SPEED = 0;
			SKIP_SPEED_COUNT = 0;
		}

	}
}

//コンフィグ(文字描画)
void STRING_SPEED_CHANGE() {

	//文字描画速度調整
	if (GAME_y == GAMEMENU_y * 5 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 5 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);

		STRING_SPEED += 10;
		STRING_SPEED_COUNT += 1;

		if (STRING_SPEED_COUNT >= 10) {
			STRING_SPEED = 100;
			STRING_SPEED_COUNT = 10;
		}
	}

	if (GAME_y == GAMEMENU_y * 5 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 5 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);

		STRING_SPEED -= 10;
		STRING_SPEED_COUNT -= 1;

		if (STRING_SPEED_COUNT <= 0) {
			STRING_SPEED = 0;
			STRING_SPEED_COUNT = 0;
		}
	}
}

//コンフィグ(サウンドノベル風とウインドウ風)
void SOUNDNOVEL_WINDOWNOVEL_CHANGE() {

	//サウンドノベル風とウインドウ風の切り替え
	if (GAME_y == GAMEMENU_y * 6 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 6 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);
		soundnovel_winownovel = 0;
	}

	if (GAME_y == GAMEMENU_y * 6 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 6 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);
		soundnovel_winownovel = 1;
	}
}

//非アクティブ時の処理設定
void WINDOWACTIVE() {

	//非アクティブ時の処理の切り替え
	if (GAME_y == GAMEMENU_y * 7 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 7 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);
		WindowActive = FALSE;

		//非アクティブ状態ではゲームを実行しない
		SetAlwaysRunFlag(WindowActive);
	}

	if (GAME_y == GAMEMENU_y * 7 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 7 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);
		WindowActive = TRUE;

		//非アクティブ状態でもゲームを実行
		SetAlwaysRunFlag(WindowActive);
	}
}

//コンフィグ(マウス/キー操作)
void MOUSE_KEY_MOVE() {

	//マウス操作を有効に
	if (GAME_y == GAMEMENU_y * 8 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 8 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);

		mouse_key_move = 1;
	}

	//キー操作を有効に
	if (GAME_y == GAMEMENU_y * 8 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 8 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);

		mouse_key_move = 0;
	}
}

//各種設定情報描画
void CONFIG_MENU() {

	//セーブデータ名描画
	DrawString(SAVE_NAME_X, GAMEMENU_y, "ＢＧＭ音量", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 2, "ＳＥ音量", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 3, "オート速度", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 4, "スキップ速度", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 5, "文字描画速度", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 6, "描画方法", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 7, "非アクティブ時", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 8, "マウス/キー操作", Cr);

	DrawString(SAVE_NAME_X, GAMEMENU_y * 9, "戻る", Cr);

	//BGM音量目盛り描画
	DrawFormatString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, Cr, "%d", BGM_VOL);

	//SE音量目盛り描画
	DrawFormatString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, Cr, "%d", SE_VOL);

	//オート速度目盛り描画
	DrawFormatString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, Cr, "%d", AUTO_SPEED);

	//スキップ速度目盛り描画
	DrawFormatString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, Cr, "%d", SKIP_SPEED);

	//文字描画速度目盛り描画
	DrawFormatString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, Cr, "%d", STRING_SPEED);

	//サウンドノベル風
	if (soundnovel_winownovel == 0)
		DrawString(SAVE_NAME_X + CURSOR * 6, GAMEMENU_y * 6, "サウンドノベル風", Cr);

	//ウインドウ風
	if (soundnovel_winownovel == 1)
		DrawString(SAVE_NAME_X + CURSOR * 6, GAMEMENU_y * 6, "ウインドウ風", Cr);

	//非アクティブ時の処理
	if (WindowActive == TRUE)
		DrawString(SAVE_NAME_X + CURSOR * 7, GAMEMENU_y * 7, "処理", Cr);

	if (WindowActive == FALSE)
		DrawString(SAVE_NAME_X + CURSOR * 7, GAMEMENU_y * 7, "未処理", Cr);

	//マウス操作
	if (mouse_key_move == 1)
		DrawString(SAVE_NAME_X + CURSOR * 8, GAMEMENU_y * 8, "マウス操作", Cr);

	//キー操作
	if (mouse_key_move == 0)
		DrawString(SAVE_NAME_X + CURSOR * 8, GAMEMENU_y * 8, "キー操作", Cr);
}

//コンフィグ(タイトル/ゲームメニューへ戻る)
void CONFIG_TITLE_BACK() {

	//タイトルに戻る/ゲームメニューに戻る
	if (GAME_y == GAMEMENU_y * 9 && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == GAMEMENU_y * 9 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//戻る
		SAVE = LINKS_MessageBox_YESNO("戻りますか？");

		if (SAVE == IDYES) {

			ClearDrawScreen();
			GAME_y = GAMEMENU_y;
			Config = 0;
		}
	}
}

//コンフィグ(メッセージ)
void CONFIG_MESSAGE() {

	SAVE = LINKS_MessageBox_YESNO("設定を変更しますか？");
}

//コンフィグ
void CONFIG() {

	//コンフィグ(メッセージ)
	CONFIG_MESSAGE();

	if (SAVE == IDYES) {

		Config = 1;

		GAME_y = GAMEMENU_y;

		ClearDrawScreen();

		WaitTimer(300);

		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && Config == 1) {

			GAME_MENU_CURSOR(Cr, GAME_y);

			//各種設定情報描画
			CONFIG_MENU();

			//BGM音量調節
			BGM_VOL_CHANGE();

			//SE音量調整
			SE_VOL_CHANGE();

			//オート速度調整
			AUTO_SPEED_CHANGE();

			//スキップ速度調整
			SKIP_SPEED_CHANGE();

			//文字列描画速度
			STRING_SPEED_CHANGE();

			//サウンドノベル風とウインドウ風描画設定
			SOUNDNOVEL_WINDOWNOVEL_CHANGE();

			//非アクティブ時の処理設定
			WINDOWACTIVE();

			//マウス操作とキー操作設定
			MOUSE_KEY_MOVE();

			//タイトルに戻る
			CONFIG_TITLE_BACK();

			//マウス操作関連
			Mouse_Move();

			//コンフィグ(キー操作)
			CONFIG_KEY_MOVE();

			//画面クリア処理
			SCREEN_CLEAR();
		}

		//ショートカットキー時の事後処理
		SHORTCUT_KEY_DRAW();
	}
}

//ゲームメニュー項目描画関数
void GAMEMENU_DRAW() {

	//各メニュー描画
	DrawString(SAVE_NAME_X, GAMEMENU_y, "セーブ", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 2, "ロード", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 3, "セーブデータ削除", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 4, "既読スキップ", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 5, "スキップ", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 6, "オート", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 7, "オート/スキップ停止", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 8, "バックログ参照", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 9, "設定", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 10, "タイトルに戻る", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 11, "ゲームに戻る", Cr);
	DrawString(SAVE_NAME_X, GAMEMENU_y * 12, "ゲーム終了", Cr);

}

//ゲームメニュー(キー操作)
void GAMEMENU_KEY_MOVE() {

	if (Key[KEY_INPUT_DOWN] == 1) {
		GAME_y += GAMEMENU_y;
		if (GAME_y == (GAMEMENU_y * 13))
			GAME_y = GAMEMENU_y;
	}

	if (Key[KEY_INPUT_UP] == 1) {
		GAME_y -= GAMEMENU_y;
		if (GAME_y == (GAMEMENU_y - GAMEMENU_y))
			GAME_y = (GAMEMENU_y * 12);
	}
}

//セーブデータ一覧描画
void SAVEDATA_DRAW() {

	//スクリーンショット描画
	DrawRotaGraph(SAVE_SNAP_X, SAVE_Y, 0.2f, 0, SAVESNAP1, TRUE);
	DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 2, 0.2f, 0, SAVESNAP2, TRUE);
	DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 3, 0.2f, 0, SAVESNAP3, TRUE);

	//セーブデータ名描画
	DrawString(SAVE_NAME_X, SAVE_Y, "セーブデータ1", Cr);
	DrawString(SAVE_NAME_X, SAVE_Y * 2, "セーブデータ2", Cr);
	DrawString(SAVE_NAME_X, SAVE_Y * 3, "セーブデータ3", Cr);

	DrawString(SAVE_NAME_X - CURSOR, SAVE_Y * 4, "戻る", Cr);
}

//セーブ画面(キー操作)
void SAVEDATA_KEY_MOVE() {

	if (Key[KEY_INPUT_DOWN] == 1) {
		SAVE_y += SAVE_MOVE;
		if (SAVE_y == (SAVE_Y_MAX + SAVE_MOVE + SAVE_MOVE))
			SAVE_y = SAVE_MOVE;
	}

	if (Key[KEY_INPUT_UP] == 1) {
		SAVE_y -= SAVE_MOVE;
		if (SAVE_y == (SAVE_Y - SAVE_MOVE))
			SAVE_y = SAVE_Y_MAX + SAVE_MOVE;
	}
}

//セーブデータスクリーンショット読込
void SAVEDATA_SCREENSHOT_READ() {

	//セーブ時のスクリーンショット読込
	SAVESNAP1 = LoadGraph("DATA/SAVE/SAVESNAP1.png");
	SAVESNAP2 = LoadGraph("DATA/SAVE/SAVESNAP2.png");
	SAVESNAP3 = LoadGraph("DATA/SAVE/SAVESNAP3.png");
	SAVETITLE = LoadGraph("DATA/BACKGROUND/SAVE.png");

	WaitTimer(600);
}

//セーブ前のメッセージ
void SAVEDATA_SAVE_MESSAGE() {

	SAVE = LINKS_MessageBox_YESNO("セーブ画面に移行しますか？");
}

//セーブ後のメッセージ
void SAVE_MESSAGE() {

	LINKS_MessageBox_OK("セーブしました！");
}

//セーブ後の処理(サウンドノベル風)
void SAVE_SOUNDNOVEL() {

	//サウンドノベル風描画時の処理
	SOUNDNOVEL();

	SAVE_CHOICE = 0;

	GAMEMENU_COUNT = 1;
}

//セーブ後の処理(ウインドウ風)
void SAVE_WINDOWNOVEL() {

	//ウインドウ風描画時の処理
	WINDOWNOVEL();

	SAVE_CHOICE = 0;

	GAMEMENU_COUNT = 1;
}

static int CreateSaveData(int* SaveSnapHandle, const char* Message, const char* ImagePath, const char* SaveDataPath) {
	SAVE = LINKS_MessageBox_YESNO(Message);
	if (SAVE == IDYES) {
		//セーブデータ１用のスクリーンショット取得変数
		*SaveSnapHandle = 1;

		//選択肢画面でのセーブ処理
		if (SAVESNAP_CHOICE != 0) {
			SetDrawScreen(DX_SCREEN_BACK);
			DrawGraph(0, 0, SAVESNAP_CHOICE, TRUE);
			SaveDrawScreenToPNG(0, 0, 640, 480, ImagePath, 0);
			SAVESNAP_CHOICE = 0;
			*SaveSnapHandle = 0;
			SetDrawScreen(DX_SCREEN_FRONT);

		}

		//セーブデータの作成
		SaveData_t Data = { EndFlag, SP, 0, CHARACTER, BACKGROUND, BACKGROUNDMUSIC, SAVE_CHOICE };
		FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
		const errno_t er = fopen_s(&fp, SaveDataPath, "wb");
		if (0 != er) {
			return 0;
		}
#else
		fp = fopen(SaveDataPath, "wb");//バイナリファイルを開く
		if (fp == NULL) {//エラーが起きたらNULLを返す
			return 0;
		}
#endif
		fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t構造体の中身を出力
		fclose(fp);
		//セーブ後のメッセージ
		SAVE_MESSAGE();
		//サウンドノベル風描画時の処理
		SAVE_SOUNDNOVEL();
		//ウインドウ風描画時の処理
		SAVE_WINDOWNOVEL();
	}

	return 0;
}
//セーブデータ１にセーブ
int SAVEDATA_1_SAVE() {
	return CreateSaveData(
		&SAVESNAP_HANDLE1, 
		"セーブデータ1にセーブしますか？", 
		"DATA/SAVE/SAVESNAP1.png", 
		"DATA/SAVE/SAVEDATA1.dat"
	);
}

//セーブデータ2にセーブ
int SAVEDATA_2_SAVE() {
	return CreateSaveData(
		&SAVESNAP_HANDLE2,
		"セーブデータ2にセーブしますか？",
		"DATA/SAVE/SAVESNAP2.png",
		"DATA/SAVE/SAVEDATA2.dat"
	);
}

//セーブデータ3にセーブ
int SAVEDATA_3_SAVE() {
	return CreateSaveData(
		&SAVESNAP_HANDLE3,
		"セーブデータ3にセーブしますか？",
		"DATA/SAVE/SAVESNAP3.png",
		"DATA/SAVE/SAVEDATA3.dat"
	);
}

//セーブデータ・セーブ画面ループ
void SAVEDATA_SAVE_LOOP() {

	//セーブデータ・セーブ画面ループ
	while (ProcessMessage() == 0 && MoveKey(Key) == 0 && GAMEMENU_COUNT == 0) {

			//背景描画
			DrawGraph(0, 0, SAVETITLE, TRUE);

			//カーソル描画
			SAVE_LOAD_MENU(Cr, SAVE_y);

			//セーブ画面描画
			SAVEDATA_DRAW();

			//マウス操作
			Mouse_Move();

			//キー操作関連
			SAVEDATA_KEY_MOVE();

			//画面クリア処理
			SCREEN_CLEAR();

			//セーブデータ１にセーブ
			if (SAVE_y == SAVE_Y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == SAVE_Y && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				//セーブデータ１にセーブ
				SAVEDATA_1_SAVE();
			}

			//セーブデータ２にセーブ
			if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				//セーブデータ２にセーブ
				SAVEDATA_2_SAVE();
			}

			//セーブデータ３にセーブ
			if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				//セーブデータ３にセーブ
				SAVEDATA_3_SAVE();
			}

			//画面に戻る
			if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				SAVE = LINKS_MessageBox_YESNO("戻りますか？");

				if (SAVE == IDYES) {

					ClearDrawScreen();

					//ショートカットキー時の事後処理
					SHORTCUT_KEY_DRAW();
					break;
				}
			}
		}
}

//セーブデータセーブ関数
void SAVEDATA_SAVE() {

	//セーブ前のメッセージ
	SAVEDATA_SAVE_MESSAGE();

	if (SAVE == IDYES) {
		ClearDrawScreen();
		SAVE_y = SAVE_Y;

		//セーブデータのスクリーンショットの読み込み
		SAVEDATA_SCREENSHOT_READ();

		//セーブデータ・セーブ画面ループ
		SAVEDATA_SAVE_LOOP();
	}
}

//ロード前のメッセージ
void SAVEDATA_LOAD_MESSAGE() {

	SAVE = LINKS_MessageBox_YESNO("ロード画面に移行しますか？");
}

//ロード後のメッセージ
void LOAD_MESSAGE() {

	LINKS_MessageBox_OK("ロードしました！");
}

//ロード後の処理(サウンドノベル風)
void LOAD_SOUNDNOVEL() {

	//サウンドノベル風描画時の処理
	SOUNDNOVEL();

	GAMEMENU_COUNT = 1;
}

//ロード後の処理(ウインドウ風)
void LOAD_WINDOWNOVEL() {

	//ウインドウ風描画時の処理
	WINDOWNOVEL();

	GAMEMENU_COUNT = 1;
}

//セーブデータ1のロード
int SAVEDATA_1_LOAD() {

	SAVE = LINKS_MessageBox_YESNO("セーブデータ1をロードしますか？");

	if (SAVE == IDYES) {
		SaveData_t Data;
		FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
		const errno_t er = fopen_s(&fp, "DATA/SAVE/SAVEDATA1.dat", "rb");
		if (0 != er) {
			LINKS_MessageBox_OK("セーブデータ1がありません！");
			return 0;
		}
#else
		fp = fopen("DATA/SAVE/SAVEDATA1.dat", "rb");
		if (fp == NULL) {

			LINKS_MessageBox_OK("セーブデータ1がありません！");

			return 0;
		}
#endif
		fread(&Data, sizeof(Data), 1, fp);
		EndFlag = Data.ENDFLAG;
		SP = Data.SP;
		CP = Data.CP;
		CHARACTER = Data.CHAR;
		BACKGROUND = Data.BG;
		BACKGROUNDMUSIC = Data.BGM;
		SAVE_CHOICE = Data.SAVE_CHOICE;

		//ロード後のメッセージ
		LOAD_MESSAGE();

		//ロード後の処理(サウンドノベル風)
		LOAD_SOUNDNOVEL();

		//ロード後の処理(ウインドウ風)
		LOAD_WINDOWNOVEL();

		fclose(fp);
	}

	return 0;
}

//セーブデータ2のロード
int SAVEDATA_2_LOAD() {

	SAVE = LINKS_MessageBox_YESNO("セーブデータ2をロードしますか？");

	if (SAVE == IDYES) {
		SaveData_t Data;
		FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
		const errno_t er = fopen_s(&fp, "DATA/SAVE/SAVEDATA2.dat", "rb");
		if (0 != er) {
			LINKS_MessageBox_OK("セーブデータ2がありません！");
			return 0;
		}
#else
		fp = fopen("DATA/SAVE/SAVEDATA2.dat", "rb");
		if (fp == NULL) {

			LINKS_MessageBox_OK("セーブデータ2がありません！");

			return 0;
		}
#endif
		fread(&Data, sizeof(Data), 1, fp);
		EndFlag = Data.ENDFLAG;
		SP = Data.SP;
		CP = Data.CP;
		CHARACTER = Data.CHAR;
		BACKGROUND = Data.BG;
		BACKGROUNDMUSIC = Data.BGM;
		SAVE_CHOICE = Data.SAVE_CHOICE;

		//ロード後のメッセージ
		LOAD_MESSAGE();

		//ロード後の処理(サウンドノベル風)
		LOAD_SOUNDNOVEL();

		//ロード後の処理(ウインドウ風)
		LOAD_WINDOWNOVEL();

		fclose(fp);
	}

	return 0;
}

//セーブデータ3をロード
int SAVEDATA_3_LOAD() {

	SAVE = LINKS_MessageBox_YESNO("セーブデータ3をロードしますか？");

	if (SAVE == IDYES) {
		SaveData_t Data;
		FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
		const errno_t er = fopen_s(&fp, "DATA/SAVE/SAVEDATA3.dat", "wb");
		if (0 != er) {
			LINKS_MessageBox_OK("セーブデータ3がありません！");
			return 0;
		}
#else
		fp = fopen("DATA/SAVE/SAVEDATA3.dat", "rb");
		if (fp == NULL) {

			LINKS_MessageBox_OK("セーブデータ3がありません！");

			return 0;
		}
#endif
		fread(&Data, sizeof(Data), 1, fp);
		EndFlag = Data.ENDFLAG;
		SP = Data.SP;
		CP = Data.CP;
		CHARACTER = Data.CHAR;
		BACKGROUND = Data.BG;
		BACKGROUNDMUSIC = Data.BGM;
		SAVE_CHOICE = Data.SAVE_CHOICE;

		//ロード後のメッセージ
		LOAD_MESSAGE();

		//ロード後の処理(サウンドノベル風)
		LOAD_SOUNDNOVEL();

		//ロード後の処理(ウインドウ風)
		LOAD_WINDOWNOVEL();

		fclose(fp);
	}
	return 0;
}

//セーブデータ・ロード画面ループ
void SAVEDATA_LOAD_LOOP() {

	while (ProcessMessage() == 0 && MoveKey(Key) == 0 && GAMEMENU_COUNT == 0) {

			//背景描画
			DrawGraph(0, 0, SAVETITLE, TRUE);

			//カーソル描画
			SAVE_LOAD_MENU(Cr, SAVE_y);

			//セーブデータ一覧描画
			SAVEDATA_DRAW();

			//マウス操作
			Mouse_Move();

			//セーブ画面(キー操作)
			SAVEDATA_KEY_MOVE();

			//画面クリア処理
			SCREEN_CLEAR();

			//セーブデータ１のロード
			if (SAVE_y == SAVE_Y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == SAVE_Y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				//セーブデータ１をロード
				SAVEDATA_1_LOAD();
			}

			//セーブデータ２のロード
			if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				//セーブデータ2をロード
				SAVEDATA_2_LOAD();
			}

			//セーブデータ３のロード
			if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				//セーブデータ2をロード
				SAVEDATA_3_LOAD();
			}

			//戻る
			if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

					SAVE = LINKS_MessageBox_YESNO("戻りますか？");

					if (SAVE == IDYES) {

						ClearDrawScreen();

						//ショートカットキー時の事後処理
						SHORTCUT_KEY_DRAW();
						break;
					}
			}
		}
}

//セーブデータロード関数
int SAVEDATA_LOAD() {

	//ロード前のメッセージ
	SAVEDATA_LOAD_MESSAGE();

	if (SAVE == IDYES) {

		ClearDrawScreen();
		SAVE_y = SAVE_Y;

		//セーブデータのスクリーンショット読込
		SAVEDATA_SCREENSHOT_READ();

		//セーブデータ・ロード画面ループ
		SAVEDATA_LOAD_LOOP();
	}
	return 0;
}

//削除前のメッセージ
void SAVEDATA_DELETE_MESSAGE() {

	SAVE = LINKS_MessageBox_YESNO("セーブデータ削除画面に移行しますか？");
}

//削除後のメッセージ
void DELETE_MESSAGE() {

	LINKS_MessageBox_OK("削除しました！");
}

//削除後の処理(サウンドノベル風)
void DELETE_SOUNDNOVEL() {

	//サウンドノベル風描画時の処理
	SOUNDNOVEL();

	GAMEMENU_COUNT = 1;
}

//削除後の処理(ウインドウ風)
void DELETE_WINDOWNOVEL() {

	//削除後の処理(ウインドウ風)
	WINDOWNOVEL();

	GAMEMENU_COUNT = 1;
}

//セーブデータ1削除
void SAVEDATA_1_DELETE(){

	SAVE = LINKS_MessageBox_YESNO("セーブデータ1を削除しますか？");

	if (SAVE == IDYES) {

		SAVE_DATA_DELETE = "DATA/SAVE/SAVEDATA1.dat";
		remove(SAVE_DATA_DELETE);

		SAVE_DATA_DELETE = "DATA/SAVE/SAVESNAP1.png";
		remove(SAVE_DATA_DELETE);

		//削除後のメッセージ
		DELETE_MESSAGE();

		//削除後の処理(サウンドノベル風)
		DELETE_SOUNDNOVEL();

		//削除後の処理(ウインドウ風)
		DELETE_WINDOWNOVEL();
	}
}

//セーブデータ2削除
void SAVEDATA_2_DELETE() {

	SAVE = LINKS_MessageBox_YESNO("セーブデータ2を削除しますか？");

	if (SAVE == IDYES) {

		SAVE_DATA_DELETE = "DATA/SAVE/SAVEDATA2.dat";
		remove(SAVE_DATA_DELETE);

		SAVE_DATA_DELETE = "DATA/SAVE/SAVESNAP2.png";
		remove(SAVE_DATA_DELETE);

		//削除後のメッセージ
		DELETE_MESSAGE();

		//削除後の処理(サウンドノベル風)
		DELETE_SOUNDNOVEL();

		//削除後の処理(ウインドウ風)
		DELETE_WINDOWNOVEL();
	}

}

//セーブデータ3削除
void SAVEDATA_3_DELETE() {

	SAVE = LINKS_MessageBox_YESNO("セーブデータ3を削除しますか？");

	if (SAVE == IDYES) {

		SAVE_DATA_DELETE = "DATA/SAVE/SAVEDATA3.dat";
		remove(SAVE_DATA_DELETE);

		SAVE_DATA_DELETE = "DATA/SAVE/SAVESNAP3.png";
		remove(SAVE_DATA_DELETE);

		//削除後のメッセージ
		DELETE_MESSAGE();

		//削除後の処理(サウンドノベル風)
		DELETE_SOUNDNOVEL();

		//削除後の処理(ウインドウ風)
		DELETE_WINDOWNOVEL();
	}

}

//セーブデータ削除画面ループ
void SAVEDATA_DELETE_LOOP() {

	while (ProcessMessage() == 0 && MoveKey(Key) == 0 && GAMEMENU_COUNT == 0) {

		//背景描画
		DrawGraph(0, 0, SAVETITLE, TRUE);

		//カーソル描画
		SAVE_LOAD_MENU(Cr, SAVE_y);

		//セーブデータ一覧描画
		SAVEDATA_DRAW();

		//マウス操作
		Mouse_Move();

		//キー操作関連
		SAVEDATA_KEY_MOVE();

		//画面クリア処理
		SCREEN_CLEAR();

		if (SAVE_y == SAVE_Y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == SAVE_Y && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

			//セーブデータ1削除処理
			SAVEDATA_1_DELETE();
		}

		if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

			//セーブデータ2削除処理
			SAVEDATA_2_DELETE();
		}

		if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

			//セーブデータ3削除処理
			SAVEDATA_3_DELETE();
		}

		if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

			SAVE = LINKS_MessageBox_YESNO("戻りますか？");

			if (SAVE == IDYES) {

				ClearDrawScreen();

				//ショートカットキー時の事後処理
				SHORTCUT_KEY_DRAW();
				break;
			}
		}
	}
}

//セーブデータ削除処理
void SAVEDATA_DELETE() {

	//削除前のメッセージ
	SAVEDATA_DELETE_MESSAGE();

	if (SAVE == IDYES) {

		ClearDrawScreen();
		SAVE_y = SAVE_Y;

		//セーブ時のスクリーンショット読込
		SAVEDATA_SCREENSHOT_READ();

		//セーブデータ削除画面ループ
		SAVEDATA_DELETE_LOOP();
	}
}

//既読スキップメッセージ
void SKIP_READ_MESSAGE() {

	SAVE = LINKS_MessageBox_YESNO("既読スキップを実行しますか？");
}

//既読スキップ後の処理(サウンドノベル風)
void SKIP_READ_SOUNDNOVEL() {

	GAMEMENU_COUNT = 1;

	//サウンドノベル風描画時の処理
	SOUNDNOVEL();
}

//既読スキップ後の処理(ウインドウ風)
void SKIP_READ_WINDOWNOVEL() {

	GAMEMENU_COUNT = 1;

	//既読スキップ後の処理(ウインドウ風)
	WINDOWNOVEL();
}

//既読スキップ判定
void SKIP_READ_CHECK() {

	//既読スキップメッセージ
	SKIP_READ_MESSAGE();

	//以下、既読データ読み込み時の判定
	if (EndFlag == 1 && SAVE == IDYES && LINKS == 1)
		skip_auto = 2;

	if (EndFlag == 2 && SAVE == IDYES && A == 1)
		skip_auto = 2;

	if (EndFlag == 3 && SAVE == IDYES && B == 1)
		skip_auto = 2;

	if (EndFlag == 4 && SAVE == IDYES && C == 1)
		skip_auto = 2;

	if (EndFlag == 5 && SAVE == IDYES && D == 1)
		skip_auto = 2;

	if (EndFlag == 6 && SAVE == IDYES && E == 1)
		skip_auto = 2;

	if (EndFlag == 7 && SAVE == IDYES && F == 1)
		skip_auto = 2;

	if (EndFlag == 8 && SAVE == IDYES && G == 1)
		skip_auto = 2;

	if (EndFlag == 9 && SAVE == IDYES && H == 1)
		skip_auto = 2;

	if (EndFlag == 10 && SAVE == IDYES && I == 1)
		skip_auto = 2;

	if (EndFlag == 11 && SAVE == IDYES && J == 1)
		skip_auto = 2;

	if (EndFlag == 12 && SAVE == IDYES && K == 1)
		skip_auto = 2;

	if (EndFlag == 13 && SAVE == IDYES && L == 1)
		skip_auto = 2;

	if (EndFlag == 14 && SAVE == IDYES && M == 1)
		skip_auto = 2;

	if (EndFlag == 15 && SAVE == IDYES && N == 1)
		skip_auto = 2;

	//ショートカットキー時の事後処理
	SHORTCUT_KEY_DRAW();
}

//スキップ処理
void SKIP_START() {

	SAVE = LINKS_MessageBox_YESNO("スキップを実行しますか？");

	if (SAVE == IDYES) {

		skip_auto = 2;
		GAMEMENU_COUNT = 1;

		//サウンドノベル風描画時の処理
		SOUNDNOVEL();

		//ウインドウ風描画時の処理
		WINDOWNOVEL();
	}
}

//オート処理メッセージ
void AUTO_MESSAGE() {

	SAVE = LINKS_MessageBox_YESNO("オートモードを実行しますか？");
}

//オート処理
void AUTO_START() {

	//オート処理メッセージ
	AUTO_MESSAGE();

	if (SAVE == IDYES) {

		skip_auto = 1;
		GAMEMENU_COUNT = 1;

		//サウンドノベル風描画時の処理
		SOUNDNOVEL();

		//既読スキップ後の処理(ウインドウ風)
		WINDOWNOVEL();
	}
}

//オート/スキップ停止処理メッセージ
void AUTO_SKIP_MESSAGE() {

	SAVE = LINKS_MessageBox_YESNO("スキップ又はオートモードを終了しますか？");
}

//オート/スキップ停止処理
void AUTO_SKIP_STOP() {

	//オート/スキップ停止処理メッセージ
	AUTO_SKIP_MESSAGE();

	if (SAVE == IDYES) {

		skip_auto = 0;
		GAMEMENU_COUNT = 1;

		//サウンドノベル風描画時の処理
		SOUNDNOVEL();

		//ウインドウ風描画時の処理
		WINDOWNOVEL();
	}
}

//バックログ参照メッセージ
void BACKLOG_MESSAGE() {

	SAVE = LINKS_MessageBox_YESNO("バックログ画面に移行しますか？");
}

//バックログ(キー操作関連)
void BACKLOG_KEY_MOVE() {

	//バックログ（キー操作関連）
	if (LOG != 10 && CheckHitKey(KEY_INPUT_UP) == 1 || LOG != 10 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		LOG++;
		WaitTimer(300);
	}

	if (LOG != 1 && CheckHitKey(KEY_INPUT_DOWN) == 1 || LOG != 1 && (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
		LOG--;
		WaitTimer(300);
	}
}

//バックログの描画関数
void BACKLOG_SCREENSHOT_DRAW() {

	if (LOG == 1) {
		DrawGraph(0, 0, BACKLOG[0], TRUE);
		DrawString(0, 450, "バックログ1", Cr);
	}
	if (LOG == 2) {
		DrawGraph(0, 0, BACKLOG[1], TRUE);
		DrawString(0, 450, "バックログ2", Cr);
	}
	if (LOG == 3) {
		DrawGraph(0, 0, BACKLOG[2], TRUE);
		DrawString(0, 450, "バックログ3", Cr);
	}
	if (LOG == 4) {
		DrawGraph(0, 0, BACKLOG[3], TRUE);
		DrawString(0, 450, "バックログ4", Cr);
	}
	if (LOG == 5) {
		DrawGraph(0, 0, BACKLOG[4], TRUE);
		DrawString(0, 450, "バックログ5", Cr);
	}
	if (LOG == 6) {
		DrawGraph(0, 0, BACKLOG[5], TRUE);
		DrawString(0, 450, "バックログ6", Cr);
	}
	if (LOG == 7) {
		DrawGraph(0, 0, BACKLOG[6], TRUE);
		DrawString(0, 450, "バックログ7", Cr);
	}
	if (LOG == 8) {
		DrawGraph(0, 0, BACKLOG[7], TRUE);
		DrawString(0, 450, "バックログ8", Cr);
	}
	if (LOG == 9) {
		DrawGraph(0, 0, BACKLOG[8], TRUE);
		DrawString(0, 450, "バックログ9", Cr);
	}
	if (LOG == 10) {
		DrawGraph(0, 0, BACKLOG[9], TRUE);
		DrawString(0, 450, "バックログ10", Cr);
	}
}

//バックログ参照
void BACKLOG_DRAW() {

	//バックログ参照メッセージ
	BACKLOG_MESSAGE();

	if (SAVE == IDYES) {

		WaitTimer(600);

		LOG = 1;

		while (ProcessMessage() == 0) {

			//バックログ（キー操作関連）
			BACKLOG_KEY_MOVE();

			//バックログの描画関数
			BACKLOG_SCREENSHOT_DRAW();

			//画面クリア処理
			SCREEN_CLEAR();

			//終了処理
			if (CheckHitKey(KEY_INPUT_RETURN) == 1 || (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				ClearDrawScreen();

				DeleteGraph(BACKLOG[0]);

				WaitTimer(300);

				//ショートカットキー時の事後処理
				SHORTCUT_KEY_DRAW();
				break;
			}
		}
	}
}

//タイトルに戻る
void GAMEMENU_TITLE_BACK() {

	SAVE = LINKS_MessageBox_YESNO("タイトル画面に戻りますか？");

	if (SAVE == IDYES) {

		ClearDrawScreen();

		if (SHORTCUT_KEY_FLAG == 1)
			StopSoundMem(BACKGROUNDMUSIC);

		GAMEMENU_COUNT = 1;
		EndFlag = 99;
		y = MENUY;
		skip_auto = 0;
		CHARACTER = 0;
		BACKGROUND = 0;
		BACKGROUNDMUSIC = 0;
	}
}

//ゲームに戻る
void GAMEMENU_GAME_BACK() {

	SAVE = LINKS_MessageBox_YESNO("ゲームに戻りますか？");

	if (SAVE == IDYES) {

		GAMEMENU_COUNT = 1;

		//サウンドノベル風描画時の処理
		SOUNDNOVEL();

		//ウインドウ風描画時の処理
		WINDOWNOVEL();
	}
}

//ゲーム終了
void GAMEMENU_GAME_FINISH() {

	SAVE = LINKS_MessageBox_YESNO("終了しますか？");

	if (SAVE == IDYES) {

		//コンティニュー用セーブ
		CONTINUE_SAVE();

		EndFlag = 99999;

		GAMEMENU_COUNT = 1;
	}
}

//終了ウインドウ
int GAME_FINISH() {

	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {

		SAVE = LINKS_MessageBox_YESNO("終了しますか？");

		if (SAVE == IDYES) {

			//コンティニュー用セーブ
			CONTINUE_SAVE();

			EndFlag = 99999;

			if (GAMEMENU_COUNT == 0)
				GAMEMENU_COUNT = 1;
		}
	}

	return 0;
}

//各ゲームメニュー選択時処理
void GAMEMENU_CHOICE() {

	//セーブ
	if (GAME_y == GAMEMENU_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == GAMEMENU_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//セーブデータセーブ処理
		SAVEDATA_SAVE();
		WaitTimer(300);
	}

	//ロード
	if (GAME_y == (GAMEMENU_y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 2) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//セーブデータロード処理
		SAVEDATA_LOAD();
		WaitTimer(300);
	}

	//セーブデータ削除
	if (GAME_y == (GAMEMENU_y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 3) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//セーブデータ削除処理
		SAVEDATA_DELETE();
		WaitTimer(300);
	}

	//既読スキップ
	if (GAME_y == (GAMEMENU_y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 4) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//既読データの読み込み
		SKIP_READ_LOAD();

		//既読済みの部分を判定して、スキップ
		SKIP_READ_CHECK();
		WaitTimer(300);
	}

	//スキップ
	if (GAME_y == (GAMEMENU_y * 5) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 5) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//スキップ処理
		SKIP_START();
		WaitTimer(300);
	}

	//オート
	if (GAME_y == (GAMEMENU_y * 6) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 6) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//オート処理
		AUTO_START();
		WaitTimer(300);
	}

	//オート/スキップ停止
	if (GAME_y == (GAMEMENU_y * 7) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 7) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//オート/スキップ停止処理
		AUTO_SKIP_STOP();
		WaitTimer(300);
	}

	//バックログ参照
	if (GAME_y == (GAMEMENU_y * 8) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 8) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//バックログ参照
		BACKLOG_DRAW();
		WaitTimer(300);
	}

	//設定
	if (GAME_y == (GAMEMENU_y * 9) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 9) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//設定画面の呼び出し
		CONFIG();
		WaitTimer(300);
	}

	//タイトルに戻る
	if (GAME_y == (GAMEMENU_y * 10) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 10) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//タイトルに戻る
		GAMEMENU_TITLE_BACK();
		WaitTimer(300);
	}

	//ゲームに戻る
	if (GAME_y == (GAMEMENU_y * 11) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 11) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//ゲームに戻る
		GAMEMENU_GAME_BACK();
		WaitTimer(300);
	}

	//ゲーム終了
	if (GAME_y == (GAMEMENU_y * 12) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 12) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		//ゲーム終了
		GAMEMENU_GAME_FINISH();
		WaitTimer(300);
	}

	//エスケープでゲーム終了
	GAME_FINISH();
}

//ゲームメニュー
int GAMEMENU() {

	//ゲームメニューを開く
	if (CheckHitKey(KEY_INPUT_BACK) == 1 || (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {

		GAMEMENU_COUNT = 0;
		ClearDrawScreen();
		StopSoundMem(BACKGROUNDMUSIC);
		GAME_y = GAMEMENU_y;

		//ゲームメニューループ
		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && GAMEMENU_COUNT == 0) {

			//ゲームメニューの描画
			GAMEMENU_DRAW();

			//カーソル描画
			GAME_MENU_CURSOR(Cr, GAME_y);

			//マウス操作
			Mouse_Move();

			//ゲームメニュー(キー操作)
			GAMEMENU_KEY_MOVE();

			//画面クリア処理
			SCREEN_CLEAR();

			//各ゲームメニュー選択時処理
			GAMEMENU_CHOICE();
		}
	}

	return 0;
}

//選択肢機能
void sentakusi(int Cr, int y) {

	//カーソルの描画
	DrawString(SENTAKUSIX, y, "■", Cr);

	//選択肢の描画
	DrawString(SENTAKUSIX + CURSOR, SENTAKUSI1, ChoiceA, Cr);
	DrawString(SENTAKUSIX + CURSOR, SENTAKUSI2, ChoiceB, Cr);
}

// 改行関数
int Kaigyou(void)
{
	if (soundnovel_winownovel == 0) {

		int TempGraph;

		// 描画行位置を一つ下げる
		DrawPointY++;

		// 描画列を最初に戻す
		DrawPointX = 0;

		// もし画面からはみ出るなら画面をスクロールさせる
		if (DrawPointY * MOJI_SIZE + MOJI_SIZE > 480)
		{
			// テンポラリグラフィックの作成
			TempGraph = MakeGraph(640, 480);

			// 画面の内容を丸々コピーする
			GetDrawScreenGraph(0, 0, 640, 480, TempGraph);

			// 一行分上に貼り付ける
			DrawGraph(0, -MOJI_SIZE, TempGraph, FALSE);

			// 一番下の行の部分を黒で埋める
			DrawBox(0, 480 - MOJI_SIZE, 640, 480, 0, TRUE);

			// 描画行位置を一つあげる
			DrawPointY--;

			// グラフィックを削除する
			DeleteGraph(TempGraph);
		}
	}

	if (soundnovel_winownovel == 1) {

		// 描画行位置を一つ下げる
		DrawPointY += 20;

		// 描画列を最初に戻す
		DrawPointX = 0;
	}

	// 終了
	return 0;
}

//スクリプトタグ処理(立ち絵描画)
void SCRIPT_OUTPUT_CHARACTER_DRAW() {

	//サウンドノベル風時の処理
	if (soundnovel_winownovel == 0) {
		//背景画像を切り抜き、立ち絵の上にペースト
		CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
		DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);

	}

	//ウインドウ風時の処理
	if (soundnovel_winownovel == 1) {
		//背景画像を切り抜き、立ち絵の上にペースト
		CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
		DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
	}

	//文字を進める
	CP++;

}

//スクリプトタグ処理(背景描画)
void SCRIPT_OUTPUT_BACKGROUND() {

	// 読みこんだグラフィックを画面左上に描画
	DrawGraph(0, 0, BACKGROUND, TRUE);

	//ウインドウ風時の処理
	if (soundnovel_winownovel == 1) {

		//ウインドウの色選択
		int	Window_Color = GetColor(0, 0, 0);

		//ウインドウの描画
		DrawBox(0, 400, 640, 480, Window_Color, TRUE);
	}

	//文字を進める
	CP++;

}

//スクリプトタグ処理(BGM再生)
void SCRIPT_OUTPUT_BACKGROUNDMUSIC() {

	// 音量の設定
	ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

	//BGM再生
	PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);

	//文字を進める
	CP++;

}

//スクリプトタグ処理(SE再生)
void SCRIPT_OUTPUT_SOUNDEFFECT() {

	StopSoundMem(SOUNDEFFECT);

	// 音量の設定
	ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

	//SEの再生
	PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);

	//文字を進める
	CP++;

}

//セーブデータ用スクリーンショット保存
void SAVESNAP() {

	//セーブデータ用スクリーンショット保存
	if (SAVESNAP_HANDLE1 == 1) {
		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP1.png", 0);
		SAVESNAP_HANDLE1 = 0;
	}

	if (SAVESNAP_HANDLE2 == 1) {
		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP2.png", 0);
		SAVESNAP_HANDLE2 = 0;
	}

	if (SAVESNAP_HANDLE3 == 1) {
		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP3.png", 0);
		SAVESNAP_HANDLE3 = 0;
	}
}

//スクリプトタグ処理(クリック待ち)
void SCRIPT_UTPUT_KEYWAIT() {

	//スキップ・オート変数がＯＦＦの場合
	if (skip_auto == 0) {

		//セーブデータ用スクリーンショット保存
		SAVESNAP();

		// ボタン押し待ちおよび参照文字位置を一つ進める
		WaitKey();

		//エンターキーで次へ
		if (CheckHitKey(KEY_INPUT_RETURN) == 1 || (GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
			CP++;
	}

	//スキップ・オート変数がＯＮの場合（オートモード）
	if (skip_auto == 1) {

		//セーブデータ用スクリーンショット保存
		SAVESNAP();

		//少し待って、次の文字列を描画
		WaitTimer(1800 * AUTO_SPEED / 100);
		CP++;
	}

	//スキップ・オート変数がＯＮの場合(スキップ)
	if (skip_auto == 2) {

		//セーブデータ用スクリーンショット保存
		SAVESNAP();

		CP++;
	}

}

//バックログ取得関数1
void BACKLOG_GET_1() {

	if (BACKLOG_COUNT == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

		BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		BACKLOG[0] = BACKLOG_HANDLE;
	}
}

//バックログ取得関数2
void BACKLOG_GET_2() {

	if (BACKLOG_COUNT == 2) {

		BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

		BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		BACKLOG[0] = BACKLOG_HANDLE;
	}
}

//バックログ取得関数3
void BACKLOG_GET_3() {

	if (BACKLOG_COUNT == 3) {

		BACKLOG_BACKGROUND = BACKLOG[1];

		BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

		BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		BACKLOG[0] = BACKLOG_HANDLE;
	}
}

//バックログ取得関数4
void BACKLOG_GET_4() {

	if (BACKLOG_COUNT == 4) {

		BACKLOG_BACKGROUND = BACKLOG[2];

		BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[1];

		BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

		BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		BACKLOG[0] = BACKLOG_HANDLE;
	}
}

//バックログ取得関数5
void BACKLOG_GET_5() {

	if (BACKLOG_COUNT == 5) {

		BACKLOG_BACKGROUND = BACKLOG[3];

		BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[2];

		BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[1];

		BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

		BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		BACKLOG[0] = BACKLOG_HANDLE;
	}
}

//バックログ取得関数6
void BACKLOG_GET_6() {

	if (BACKLOG_COUNT == 6) {

		BACKLOG_BACKGROUND = BACKLOG[4];

		BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[3];

		BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[2];

		BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[1];

		BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

		BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		BACKLOG[0] = BACKLOG_HANDLE;
	}
}

//バックログ取得関数7
void BACKLOG_GET_7() {

	if (BACKLOG_COUNT == 7) {

		BACKLOG_BACKGROUND = BACKLOG[5];

		BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[4];

		BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[3];

		BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[2];

		BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[1];

		BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

		BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		BACKLOG[0] = BACKLOG_HANDLE;
	}
}

//バックログ取得関数8
void BACKLOG_GET_8() {

	if (BACKLOG_COUNT == 8) {

		BACKLOG_BACKGROUND = BACKLOG[6];

		BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[5];

		BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[4];

		BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[3];

		BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[2];

		BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[1];

		BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

		BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		BACKLOG[0] = BACKLOG_HANDLE;
	}
}

//バックログ取得関数9
void BACKLOG_GET_9() {

	if (BACKLOG_COUNT == 9) {

		BACKLOG_BACKGROUND = BACKLOG[7];

		BACKLOG[8] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[6];

		BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[5];

		BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[4];

		BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[3];

		BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[2];

		BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[1];

		BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

		BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		BACKLOG[0] = BACKLOG_HANDLE;
	}
}

//バックログ取得関数10
void BACKLOG_GET_10() {

	if (BACKLOG_COUNT >= 10) {

		BACKLOG_BACKGROUND = BACKLOG[8];

		BACKLOG[9] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[7];

		BACKLOG[8] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[6];

		BACKLOG[7] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[5];

		BACKLOG[6] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[4];

		BACKLOG[5] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[3];

		BACKLOG[4] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[2];

		BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG_BACKGROUND = BACKLOG[1];

		BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

		BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

		BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

		BACKLOG[0] = BACKLOG_HANDLE;
	}
}

//バックログ取得関数(メイン)
void BACKLOG_GET() {

	//バックログ取得関数1
	BACKLOG_GET_1();

	//バックログ取得関数2
	BACKLOG_GET_2();

	//バックログ取得関数3
	BACKLOG_GET_3();

	//バックログ取得関数4
	BACKLOG_GET_4();

	//バックログ取得関数5
	BACKLOG_GET_5();

	//バックログ取得関数6
	BACKLOG_GET_6();

	//バックログ取得関数7
	BACKLOG_GET_7();

	//バックログ取得関数8
	BACKLOG_GET_8();

	//バックログ取得関数9
	BACKLOG_GET_9();

	//バックログ取得関数10
	BACKLOG_GET_10();
}

//スクリプトタグ処理(ゲーム画面のクリア処理)
void SCRIPT_OUTPUT_SCREENCLEAR() {

	SetDrawScreen(DX_SCREEN_BACK);

	BACKLOG_COUNT++;

	//バックログ取得関数
	BACKLOG_GET();

	// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
	ClearDrawScreen();
	DrawPointY = 0;
	DrawPointX = 0;
	CHARACTER = 0;
	BACKGROUND = 0;
	CP++;

	SetDrawScreen(DX_SCREEN_FRONT);

}

//スクリプトタグ処理(少し待つ)
void SCRIPT_OUTPUT_WAIT() {

	//オート又は通常時、3秒待つ
	if (skip_auto != 2) {
		WaitTimer(1800);
		CP++;
	}

	//スキップ時、3秒待たずに次へ
	if (skip_auto == 2)
		CP++;
}

//スクリプトタグ処理(ゲームオーバー)
void SCRIPT_OUTPUT_GAMEOVER() {

	BACKGROUND = GAMEOVER;
	DrawGraph(0, 0, BACKGROUND, TRUE);

	if (soundnovel_winownovel == 1) {

		int	Window_Color = GetColor(0, 0, 0);

		DrawBox(0, 400, 640, 480, Window_Color, TRUE);
	}

	CP++;
}

//スクリプトタグ処理(エンディング)
void SCRIPT_OUTPUT_ENDING() {

	PlayMovie("DATA/MOVIE/ENDING.wmv", 1, DX_MOVIEPLAYTYPE_NORMAL);
	CP++;
}

//スクリプトタグ処理(BGM再生終了)
void SCRIPT_OUTPUT_BGMSTOP() {

	StopSoundMem(BACKGROUNDMUSIC);
	BACKGROUNDMUSIC = 0;
	CP++;
}

//スクリプトタグ処理(SE再生終了)
void SCRIPT_OUTPUT_SESTOP() {

	StopSoundMem(SOUNDEFFECT);
	CP++;
}

//選択肢ループ用描画処理(サウンドノベル風)
void SCRIPT_OUTPUT_CHOICE_LOOP_SOUNDNOVEL() {

	if (soundnovel_winownovel == 0 && SAVE_CHOICE == 1) {

		DrawGraph(0, 0, BACKGROUND, TRUE);

		DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
	}
}

//選択肢ループ用描画処理(ウインドウ風)
void SCRIPT_OUTPUT_CHOICE_LOOP_WINDOWNOVEL() {

	if (soundnovel_winownovel == 1 && SAVE_CHOICE == 1) {

		int	Window_Color = GetColor(0, 0, 0);

		DrawGraph(0, 0, BACKGROUND, TRUE);

		DrawBox(0, 400, 640, 480, Window_Color, TRUE);

		DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
	}
}

//選択肢ループ用描画処理
void SCRIPT_OUTPUT_CHOICE_LOOP_DRAW() {

	//選択肢ループ用描画処理(サウンドノベル風)
	SCRIPT_OUTPUT_CHOICE_LOOP_SOUNDNOVEL();

	//選択肢ループ用描画処理(ウインドウノベル風)
	SCRIPT_OUTPUT_CHOICE_LOOP_WINDOWNOVEL();
}

//選択肢ファイルの読み込み(描画用)
void SCRIPT_OUTPUT_CHOICE_READ() {

	if (EndFlag == 1) {
		//選択肢Aを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/A.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Bを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/B.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}

	if (EndFlag == 2) {
		//選択肢Cを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/C.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Dを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/D.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}

	if (EndFlag == 3) {
		//選択肢Eを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/E.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Fを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/F.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}

	if (EndFlag == 4) {
		//選択肢Gを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/G.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Hを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/H.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}

	if (EndFlag == 5) {
		//選択肢Iを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/I.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Jを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/J.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}

	if (EndFlag == 6) {
		//選択肢Kを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/K.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Lを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/L.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}

	if (EndFlag == 7) {
		//選択肢Mを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/M.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Nを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/N.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}
}

//セーブデータ用スクリーンショット取得(選択肢画面)
void SCRIPT_OUTPUT_CHOICE_LOOP_SAVESNAP() {

	if (SAVESNAP_CHOICE == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP_CHOICE.png", 0);

		SAVESNAP_CHOICE = LoadGraph("DATA/SAVE/SAVESNAP_CHOICE.png", 0);
	}
}

//キー操作(選択肢画面用)
void SCRIPT_OUTPUT_CHOICE_LOOP_KEY_MOVE() {

	if (Key[KEY_INPUT_DOWN] == 1) {
		y += CURSOR;
		if (y == (SENTAKUSI2 + CURSOR))                         // y座標が260なら(選択が一番下なら)
			y = SENTAKUSI1;                        // 選択座標を一番上に
	}
	if (Key[KEY_INPUT_UP] == 1) {
		y -= CURSOR;
		if (y == (SENTAKUSI1 - CURSOR))
			y = SENTAKUSI2;
	}
}

//選択後の分岐処理(選択肢↑)
void SCRIPT_OUTPUT_CHOICE_BRANCH_UP() {

	switch (EndFlag) {

	case 1:

			EndFlag = 2;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;

	case 2:
			EndFlag = 4;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;

	case 3:
			EndFlag = 6;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;

	case 4:
			EndFlag = 8;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;

	case 5:
			EndFlag = 10;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;

	case 6:
			EndFlag = 12;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;

	case 7:
			EndFlag = 14;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;
	}
}

//選択後の分岐処理(選択肢↓)
void SCRIPT_OUTPUT_CHOICE_BRANCH_DOWN() {

	switch (EndFlag) {

	case 1:
			EndFlag = 3;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;

	case 2:
			EndFlag = 5;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;

	case 3:
			EndFlag = 7;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;

	case 4:
			EndFlag = 9;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;

	case 5:
			EndFlag = 11;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;

	case 6:
			EndFlag = 13;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;

	case 7:
			EndFlag = 15;
			SAVE_CHOICE = 0;
			SAVESNAP_CHOICE = 0;
			break;
	}
}

//選択肢時のバックログ取得(選択肢の読み込み)
void SCRIPT_OUTPUT_CHOICE_BACKLOG_CHOICE_READ() {

	if (EndFlag == 2 || EndFlag == 3) {
		//選択肢Aを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/A.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Bを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/B.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}

	if (EndFlag == 4 || EndFlag == 5) {
		//選択肢Cを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/C.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Dを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/D.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}

	if (EndFlag == 6 || EndFlag == 7) {
		//選択肢Eを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/E.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Fを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/F.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}

	if (EndFlag == 8 || EndFlag == 9) {
		//選択肢Gを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/G.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Hを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/H.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}

	if (EndFlag == 10 || EndFlag == 11) {
		//選択肢Iを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/I.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Jを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/J.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}

	if (EndFlag == 12 || EndFlag == 13) {
		//選択肢Kを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/K.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Lを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/L.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}

	if (EndFlag == 14 || EndFlag == 15) {
		//選択肢Mを開く
		Choice1 = FileRead_open("DATA/STR/CHOICE/M.txt");
		FileRead_gets(ChoiceA, RETU, Choice1);

		//選択肢Nを開く
		Choice2 = FileRead_open("DATA/STR/CHOICE/N.txt");
		FileRead_gets(ChoiceB, RETU, Choice2);
	}
}

//選択肢時のバックログ取得
void SCRIPT_OUTPUT_CHOICE_BACKLOG() {

	SetDrawScreen(DX_SCREEN_BACK);

	//選択肢ループ用描画処理(サウンドノベル風)
	SCRIPT_OUTPUT_CHOICE_LOOP_SOUNDNOVEL();

	//選択肢ループ用描画処理(サウンドノベル風)
	SCRIPT_OUTPUT_CHOICE_LOOP_WINDOWNOVEL();

	//選択肢時のバックログ取得(選択肢の読み込み)
	SCRIPT_OUTPUT_CHOICE_BACKLOG_CHOICE_READ();

	//選択肢の描画
	sentakusi(Cr, y);

	//バックログ取得
	BACKLOG_GET();

	ClearDrawScreen();
	DrawPointY = 0;
	DrawPointX = 0;
	BACKGROUND = 0;
	CHARACTER = 0;

	SetDrawScreen(DX_SCREEN_FRONT);
}

//選択肢ループ
void SCRIPT_OUTPUT_CHOICE_LOOP() {

	//選択肢ファイルの読み込み(描画用
	SCRIPT_OUTPUT_CHOICE_READ();

	while (ProcessMessage() == 0 && MoveKey(Key) == 0 && EndFlag != 99 && EndFlag != 99999 && SAVE_CHOICE != 0) {

		//選択肢ループ用描画処理
		SCRIPT_OUTPUT_CHOICE_LOOP_DRAW();

		//選択肢の描画
		sentakusi(Cr, y);

		//ゲームメニュー
		GAMEMENU();

		//ゲーム終了
		GAME_FINISH();

		//セーブデータ用スクリーンショット取得
		SCRIPT_OUTPUT_CHOICE_LOOP_SAVESNAP();

		//マウス操作
		Mouse_Move();

		//キー操作関連
		SCRIPT_OUTPUT_CHOICE_LOOP_KEY_MOVE();

		//画面クリア処理
		SCREEN_CLEAR();

		if (y == SENTAKUSI1 && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == SENTAKUSI1 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			BACKLOG_COUNT++;

			//選択肢時のバックログ取得
			SCRIPT_OUTPUT_CHOICE_BACKLOG();

			//選択後の分岐処理(選択肢↑)
			SCRIPT_OUTPUT_CHOICE_BRANCH_UP();
			CP++;
			break;
		}

		if (y == SENTAKUSI2 && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == SENTAKUSI2 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//選択後の分岐処理(選択肢↑)
			SCRIPT_OUTPUT_CHOICE_BRANCH_DOWN();
			CP++;
			break;
		}

	}
}

//スクリプトタグ処理(選択肢処理)
void SCRIPT_OUTPUT_CHOICE() {

	int temp_CHARACTER = CHARACTER;
	int temp_BACKGROUND = BACKGROUND;

	y = SENTAKUSIY;

	if (EndFlag == 1 || EndFlag == 2 || EndFlag == 3 || EndFlag == 4 || EndFlag == 5 || EndFlag == 6 || EndFlag == 7) {

		SAVE_CHOICE = 1;
		SAVESNAP_CHOICE = 1;

		//選択肢ループ
		SCRIPT_OUTPUT_CHOICE_LOOP();
	}

	if (EndFlag == 8 || EndFlag == 9 || EndFlag == 10 || EndFlag == 11 || EndFlag == 12 || EndFlag == 13 || EndFlag == 14 || EndFlag == 15)
		CP++;
}

//スクリプトタグ処理(終了文字)
void SCRIPT_OUTPUT_END() {

	if (EndFlag == 1)
		LINKS = 1;

	if (EndFlag == 2)
		A = 1;

	if (EndFlag == 3)
		B = 1;

	if (EndFlag == 4)
		C = 1;

	if (EndFlag == 5)
		D = 1;

	if (EndFlag == 6)
		E = 1;

	if (EndFlag == 7)
		F = 1;

	if (EndFlag == 8)
		G = 1;

	if (EndFlag == 9)
		H = 1;

	if (EndFlag == 10)
		I = 1;

	if (EndFlag == 11)
		J = 1;

	if (EndFlag == 12)
		K = 1;

	if (EndFlag == 13)
		L = 1;

	if (EndFlag == 14)
		M = 1;

	if (EndFlag == 15)
		N = 1;

	SKIP_READ_SAVE();

	// 終了フラグを立てるおよび参照文字位置を一つ進める
	EndFlag = 99999;
	CP++;
}

//立ち絵クリア処理
void SCRIPT_OUTPUT_CHARACTER_REMOVE() {

	//サウンドノベル風時の処理
	if (soundnovel_winownovel == 0) {
		CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
		DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);
		CP++;
	}

	//ウインドウ風時の処理
	if (soundnovel_winownovel == 1) {
		CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
		DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);
		CP++;
	}
}

//キャラクター名描画処理
void SCRIPT_OUTPUT_CHARACTER_NAME() {

	//サウンドノベル風時の処理
	if (soundnovel_winownovel == 0) {
		SP++;
		CP++;
	}

	//ウインドウ風時の処理
	if (soundnovel_winownovel == 1) {

		//キャラクター名を読み込む
		CHARACTER_NAME[0] = String[SP][CP + 1];
		CHARACTER_NAME[1] = String[SP][CP + 2];
		CHARACTER_NAME[2] = String[SP][CP + 3];
		CHARACTER_NAME[3] = String[SP][CP + 4];
		CHARACTER_NAME[4] = String[SP][CP + 5];
		CHARACTER_NAME[5] = String[SP][CP + 6];
		CHARACTER_NAME[6] = String[SP][CP + 7];
		CHARACTER_NAME[7] = String[SP][CP + 8];
		CHARACTER_NAME[8] = String[SP][CP + 9];
		CHARACTER_NAME[9] = '\0';

		//キャラクター名の背景
		int	Window_Color = GetColor(0, 0, 0);

		DrawBox(30, 360, 150, 385, Window_Color, TRUE);

		// １文字描画
		DrawString(30, 360, CHARACTER_NAME, GetColor(255, 255, 255));

		SP++;
		CP++;
	}
}

//文字列の描画
void SCRIPT_OUTPUT_STRING_DRAW() {

	// １文字分抜き出す
	OneMojiBuf[0] = String[SP][CP];
	OneMojiBuf[1] = String[SP][CP + 1];
	OneMojiBuf[2] = '\0';

	if (soundnovel_winownovel == 1 && DrawPointY <= 399)
		DrawPointY = 400;

	if (soundnovel_winownovel == 0) {
		// １文字描画
		DrawString(DrawPointX * MOJI_SIZE, DrawPointY * MOJI_SIZE, OneMojiBuf, GetColor(255, 255, 255));
	}

	if (soundnovel_winownovel == 1) {
		// １文字描画
		DrawString(DrawPointX * MOJI_SIZE, DrawPointY, OneMojiBuf, GetColor(255, 255, 255));
	}

	// 参照文字位置を２バイト勧める
	CP += 2;

	// カーソルを一文字文進める
	DrawPointX++;
}

//文字列の描画速度
void SCRIPT_OUTPUT_STRING_DRAW_SPEED() {

	//スキップ・オート変数がＯＦＦの場合
	if (skip_auto == 0) {
		// 少し待つ
		WaitTimer(30 * STRING_SPEED / 100);
	}

	//スキップ・オート変数がＯＮの場合(オートモード)
	if (skip_auto == 1) {
		// 少し待つ
		WaitTimer(30 * AUTO_SPEED / 100);
	}

	//スキップ・オート変数がＯＮの場合（スキップ）
	if (skip_auto == 2) {
		//速く処理
		WaitTimer(10 * SKIP_SPEED / 100);
	}
}

//文字列の改行
void SCRIPT_OUTPUT_STRING_KAIGYO() {

	// 画面からはみ出たら改行する
	if (DrawPointX * MOJI_SIZE + MOJI_SIZE > 640)
		Kaigyou();
}

//サウンドノベル風時の改ページ処理
void SCRIPT_OUTPUT_STRING_PAGE_CLEAR_SOUNDNOVEL() {

	//サウンドノベル風時の改ページ処理
	if (soundnovel_winownovel == 0) {

		if (DrawPointY * MOJI_SIZE + MOJI_SIZE > CHARACTERY + MOJI_SIZE) {

			SetDrawScreen(DX_SCREEN_BACK);

			BACKLOG_COUNT++;

			//バックログ取得
			BACKLOG_GET();

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

			SetDrawScreen(DX_SCREEN_FRONT);

			WaitTimer(300);
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;

			if (BACKGROUND != 0)
				DrawGraph(0, 0, BACKGROUND, TRUE);

			if (CHARACTER != 0)
				DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
		}
	}
}

//ウインドウ風時の改ページ処理
void SCRIPT_OUTPUT_STRING_PAGE_CLEAR_WINODWNOVEL() {

	//ウインドウ風時の改ページ処理
	if (soundnovel_winownovel == 1) {

		if (DrawPointY > 480) {

			SetDrawScreen(DX_SCREEN_BACK);

			BACKLOG_COUNT++;

			//バックログ取得
			BACKLOG_GET();

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

			SetDrawScreen(DX_SCREEN_FRONT);

			WaitTimer(300);
			ClearDrawScreen();
			DrawPointY = 400;
			DrawPointX = 0;

			if (BACKGROUND != 0)
				DrawGraph(0, 0, BACKGROUND, TRUE);

			if (soundnovel_winownovel == 1) {

				int	Window_Color = GetColor(0, 0, 0);

				DrawBox(0, 400, 640, 480, Window_Color, TRUE);
			}

			if (CHARACTER != 0)
				DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
		}
	}
}

//キャラクター描画処理1～9
void CHARACTER_DRAW_0() {

	switch (String[SP][CP])
	{
	case '1':

		//キャラ01読込
		CHARACTER = CHARACTER_LOAD[0];
		break;

	case '2':

		//キャラ02読込
		CHARACTER = CHARACTER_LOAD[1];
		break;

	case '3':

		//キャラ03読込
		CHARACTER = CHARACTER_LOAD[2];
		break;

	case '4':

		//キャラ04読込
		CHARACTER = CHARACTER_LOAD[3];
		break;

	case '5':

		//キャラ05読込
		CHARACTER = CHARACTER_LOAD[4];
		break;

	case '6':

		//キャラ06読込
		CHARACTER = CHARACTER_LOAD[5];
		break;

	case '7':

		//キャラ07読込
		CHARACTER = CHARACTER_LOAD[6];
		break;

	case '8':

		//キャラ08読込
		CHARACTER = CHARACTER_LOAD[7];
		break;

	case '9':

		//キャラ09読込
		CHARACTER = CHARACTER_LOAD[8];
		break;
	}
}

//キャラクター描画処理10～19
void CHARACTER_DRAW_1() {

	switch (String[SP][CP])
	{
	case '0':

		//キャラ10読込
		CHARACTER = CHARACTER_LOAD[9];
		break;

	case '1':

		//キャラ11読込
		CHARACTER = CHARACTER_LOAD[10];
		break;

	case '2':

		//キャラ12読込
		CHARACTER = CHARACTER_LOAD[11];
		break;

	case '3':

		//キャラ13読込
		CHARACTER = CHARACTER_LOAD[12];
		break;

	case '4':

		//キャラ14読込
		CHARACTER = CHARACTER_LOAD[13];
		break;

	case '5':

		//キャラ15読込
		CHARACTER = CHARACTER_LOAD[14];
		break;

	case '6':

		//キャラ16読込
		CHARACTER = CHARACTER_LOAD[15];
		break;

	case '7':

		//キャラ17読込
		CHARACTER = CHARACTER_LOAD[16];
		break;

	case '8':

		//キャラ18読込
		CHARACTER = CHARACTER_LOAD[17];
		break;

	case '9':

		//キャラ19読込
		CHARACTER = CHARACTER_LOAD[18];
		break;
	}
}

//キャラクター描画処理20～29
void CHARACTER_DRAW_2() {

	switch (String[SP][CP])
	{
	case '0':

		//キャラ20読込
		CHARACTER = CHARACTER_LOAD[19];
		break;

	case '1':

		//キャラ21読込
		CHARACTER = CHARACTER_LOAD[20];
		break;

	case '2':

		//キャラ22読込
		CHARACTER = CHARACTER_LOAD[21];
		break;

	case '3':

		//キャラ23読込
		CHARACTER = CHARACTER_LOAD[22];
		break;

	case '4':

		//キャラ24読込
		CHARACTER = CHARACTER_LOAD[23];
		break;

	case '5':

		//キャラ25読込
		CHARACTER = CHARACTER_LOAD[24];
		break;

	case '6':

		//キャラ26読込
		CHARACTER = CHARACTER_LOAD[25];
		break;

	case '7':

		//キャラ27読込
		CHARACTER = CHARACTER_LOAD[26];
		break;

	case '8':

		//キャラ28読込
		CHARACTER = CHARACTER_LOAD[27];
		break;

	case '9':

		//キャラ29読込
		CHARACTER = CHARACTER_LOAD[28];
		break;
	}
}

//キャラクター描画処理30～39
void CHARACTER_DRAW_3() {

	switch (String[SP][CP])
	{
	case '0':

		//キャラ30読込
		CHARACTER = CHARACTER_LOAD[29];
		break;

	case '1':

		//キャラ31読込
		CHARACTER = CHARACTER_LOAD[30];
		break;

	case '2':

		//キャラ32読込
		CHARACTER = CHARACTER_LOAD[31];
		break;

	case '3':

		//キャラ33読込
		CHARACTER = CHARACTER_LOAD[32];
		break;

	case '4':

		//キャラ34読込
		CHARACTER = CHARACTER_LOAD[33];
		break;

	case '5':

		//キャラ35読込
		CHARACTER = CHARACTER_LOAD[34];
		break;

	case '6':

		//キャラ36読込
		CHARACTER = CHARACTER_LOAD[35];
		break;

	case '7':

		//キャラ37読込
		CHARACTER = CHARACTER_LOAD[36];
		break;

	case '8':

		//キャラ38読込
		CHARACTER = CHARACTER_LOAD[37];
		break;

	case '9':

		//キャラ39読込
		CHARACTER = CHARACTER_LOAD[38];
		break;
	}
}

//キャラクター描画処理40～49
void CHARACTER_DRAW_4() {

	switch (String[SP][CP])
	{
	case '0':

		//キャラ40読込
		CHARACTER = CHARACTER_LOAD[39];
		break;

	case '1':

		//キャラ41読込
		CHARACTER = CHARACTER_LOAD[40];
		break;

	case '2':

		//キャラ42読込
		CHARACTER = CHARACTER_LOAD[41];
		break;

	case '3':

		//キャラ43読込
		CHARACTER = CHARACTER_LOAD[42];
		break;

	case '4':

		//キャラ44読込
		CHARACTER = CHARACTER_LOAD[43];
		break;

	case '5':

		//キャラ45読込
		CHARACTER = CHARACTER_LOAD[44];
		break;

	case '6':

		//キャラ46読込
		CHARACTER = CHARACTER_LOAD[45];
		break;

	case '7':

		//キャラ47読込
		CHARACTER = CHARACTER_LOAD[46];
		break;

	case '8':

		//キャラ48読込
		CHARACTER = CHARACTER_LOAD[47];
		break;

	case '9':

		//キャラ49読込
		CHARACTER = CHARACTER_LOAD[48];
		break;
	}
}

//キャラクター描画処理50～59
void CHARACTER_DRAW_5() {

	switch (String[SP][CP])
	{
	case '0':

		//キャラ50読込
		CHARACTER = CHARACTER_LOAD[49];
		break;

	case '1':

		//キャラ51読込
		CHARACTER = CHARACTER_LOAD[50];
		break;

	case '2':

		//キャラ52読込
		CHARACTER = CHARACTER_LOAD[51];
		break;

	case '3':

		//キャラ53読込
		CHARACTER = CHARACTER_LOAD[52];
		break;

	case '4':

		//キャラ54読込
		CHARACTER = CHARACTER_LOAD[53];
		break;

	case '5':

		//キャラ55読込
		CHARACTER = CHARACTER_LOAD[54];
		break;

	case '6':

		//キャラ56読込
		CHARACTER = CHARACTER_LOAD[55];
		break;

	case '7':

		//キャラ57読込
		CHARACTER = CHARACTER_LOAD[56];
		break;

	case '8':

		//キャラ58読込
		CHARACTER = CHARACTER_LOAD[57];
		break;

	case '9':

		//キャラ59読込
		CHARACTER = CHARACTER_LOAD[58];
		break;
	}
}

//キャラクター描画処理60～69
void CHARACTER_DRAW_6() {

	switch (String[SP][CP])
	{
	case '0':

		//キャラ60読込
		CHARACTER = CHARACTER_LOAD[59];
		break;

	case '1':

		//キャラ61読込
		CHARACTER = CHARACTER_LOAD[60];
		break;

	case '2':

		//キャラ62読込
		CHARACTER = CHARACTER_LOAD[61];
		break;

	case '3':

		//キャラ63読込
		CHARACTER = CHARACTER_LOAD[62];
		break;

	case '4':

		//キャラ64読込
		CHARACTER = CHARACTER_LOAD[63];
		break;

	case '5':

		//キャラ65読込
		CHARACTER = CHARACTER_LOAD[64];
		break;

	case '6':

		//キャラ66読込
		CHARACTER = CHARACTER_LOAD[65];
		break;

	case '7':

		//キャラ67読込
		CHARACTER = CHARACTER_LOAD[66];
		break;

	case '8':

		//キャラ68読込
		CHARACTER = CHARACTER_LOAD[67];
		break;

	case '9':

		//キャラ69読込
		CHARACTER = CHARACTER_LOAD[68];
		break;
	}
}

//キャラクター描画処理70～79
void CHARACTER_DRAW_7() {

	switch (String[SP][CP])
	{
	case '0':

		//キャラ70読込
		CHARACTER = CHARACTER_LOAD[70];
		break;

	case '1':

		//キャラ71読込
		CHARACTER = CHARACTER_LOAD[70];
		break;

	case '2':

		//キャラ72読込
		CHARACTER = CHARACTER_LOAD[71];
		break;

	case '3':

		//キャラ73読込
		CHARACTER = CHARACTER_LOAD[72];
		break;

	case '4':

		//キャラ74読込
		CHARACTER = CHARACTER_LOAD[73];
		break;

	case '5':

		//キャラ75読込
		CHARACTER = CHARACTER_LOAD[74];
		break;

	case '6':

		//キャラ76読込
		CHARACTER = CHARACTER_LOAD[75];
		break;

	case '7':

		//キャラ77読込
		CHARACTER = CHARACTER_LOAD[76];
		break;

	case '8':

		//キャラ78読込
		CHARACTER = CHARACTER_LOAD[77];
		break;

	case '9':

		//キャラ79読込
		CHARACTER = CHARACTER_LOAD[78];
		break;
	}
}

//キャラクター描画処理80～89
void CHARACTER_DRAW_8() {

	switch (String[SP][CP])
	{
	case '0':

		//キャラ80読込
		CHARACTER = CHARACTER_LOAD[79];
		break;

	case '1':

		//キャラ81読込
		CHARACTER = CHARACTER_LOAD[80];
		break;

	case '2':

		//キャラ82読込
		CHARACTER = CHARACTER_LOAD[81];
		break;

	case '3':

		//キャラ83読込
		CHARACTER = CHARACTER_LOAD[82];
		break;

	case '4':

		//キャラ84読込
		CHARACTER = CHARACTER_LOAD[83];
		break;

	case '5':

		//キャラ85読込
		CHARACTER = CHARACTER_LOAD[84];
		break;

	case '6':
		//キャラ86読込
		CHARACTER = CHARACTER_LOAD[85];
		break;

	case '7':

		//キャラ87読込
		CHARACTER = CHARACTER_LOAD[86];
		break;

	case '8':

		//キャラ88読込
		CHARACTER = CHARACTER_LOAD[87];
		break;

	case '9':

		//キャラ89読込
		CHARACTER = CHARACTER_LOAD[88];
		break;
	}
}

//キャラクター描画処理90～99
void CHARACTER_DRAW_9() {

	switch (String[SP][CP])
	{
	case '0':

		//キャラ90読込
		CHARACTER = CHARACTER_LOAD[89];
		break;

	case '1':

		//キャラ91読込
		CHARACTER = CHARACTER_LOAD[90];
		break;

	case '2':

		//キャラ92読込
		CHARACTER = CHARACTER_LOAD[91];
		break;

	case '3':

		//キャラ93読込
		CHARACTER = CHARACTER_LOAD[92];
		break;

	case '4':

		//キャラ94読込
		CHARACTER = CHARACTER_LOAD[93];
		break;

	case '5':

		//キャラ95読込
		CHARACTER = CHARACTER_LOAD[94];
		break;

	case '6':

		//キャラ96読込
		CHARACTER = CHARACTER_LOAD[95];
		break;

	case '7':

		//キャラ97読込
		CHARACTER = CHARACTER_LOAD[96];
		break;

	case '8':

		//キャラ98読込
		CHARACTER = CHARACTER_LOAD[97];
		break;

	case '9':

		//キャラ99読込
		CHARACTER = CHARACTER_LOAD[98];
		break;
	}
}

//キャラクター描画処理
void CHARACTER_DRAW() {

	switch (String[SP][CP]) {

	case '0':

		CP++;

		CHARACTER_DRAW_0();
		break;

	case '1':

		CP++;

		CHARACTER_DRAW_1();
		break;

	case '2':

		CP++;

		CHARACTER_DRAW_2();
		break;

	case '3':

		CP++;

		CHARACTER_DRAW_3();
		break;

	case '4':

		CP++;

		CHARACTER_DRAW_4();
		break;

	case '5':

		CP++;

		CHARACTER_DRAW_5();
		break;

	case '6':

		CP++;

		CHARACTER_DRAW_6();
		break;

	case '7':

		CP++;

		CHARACTER_DRAW_7();
		break;

	case '8':

		CP++;

		CHARACTER_DRAW_8();
		break;

	case '9':

		CP++;

		CHARACTER_DRAW_9();
		break;
	}
}

//背景描画処理1～9
void BACKGROUND_DRAW_0() {

	switch (String[SP][CP])
	{
	case '1':

		//背景01読込
		BACKGROUND = BACKGROUND_LOAD[0];
		break;

	case '2':

		//背景02読込
		BACKGROUND = BACKGROUND_LOAD[1];
		break;

	case '3':

		//背景03読込
		BACKGROUND = BACKGROUND_LOAD[2];
		break;

	case '4':

		//背景04読込
		BACKGROUND = BACKGROUND_LOAD[3];
		break;

	case '5':

		//背景05読込
		BACKGROUND = BACKGROUND_LOAD[4];

		break;

	case '6':

		//背景06読込
		BACKGROUND = BACKGROUND_LOAD[5];
		break;

	case '7':

		//背景07読込
		BACKGROUND = BACKGROUND_LOAD[6];
		break;

	case '8':

		//背景08読込
		BACKGROUND = BACKGROUND_LOAD[7];
		break;

	case '9':

		//背景09読込
		BACKGROUND = BACKGROUND_LOAD[8];
		break;
	}
}

//背景描画処理10～19
void BACKGROUND_DRAW_1() {

	switch (String[SP][CP])
	{
	case '0':

		//背景10読込
		BACKGROUND = BACKGROUND_LOAD[9];
		break;

	case '1':

		//背景11読込
		BACKGROUND = BACKGROUND_LOAD[10];
		break;

	case '2':

		//背景12読込
		BACKGROUND = BACKGROUND_LOAD[11];
		break;

	case '3':

		//背景13読込
		BACKGROUND = BACKGROUND_LOAD[12];
		break;

	case '4':

		//背景14読込
		BACKGROUND = BACKGROUND_LOAD[13];
		break;

	case '5':

		//背景15読込
		BACKGROUND = BACKGROUND_LOAD[14];
		break;

	case '6':

		//背景16読込
		BACKGROUND = BACKGROUND_LOAD[15];
		break;

	case '7':

		//背景17読込
		BACKGROUND = BACKGROUND_LOAD[16];
		break;

	case '8':

		//背景18読込
		BACKGROUND = BACKGROUND_LOAD[17];
		break;

	case '9':

		//背景19読込
		BACKGROUND = BACKGROUND_LOAD[18];
		break;
	}
}

//背景描画処理20～29
void BACKGROUND_DRAW_2() {

	switch (String[SP][CP])
	{
	case '0':

		//背景20読込
		BACKGROUND = BACKGROUND_LOAD[19];
		break;

	case '1':

		//背景21読込
		BACKGROUND = BACKGROUND_LOAD[20];
		break;

	case '2':

		//背景22読込
		BACKGROUND = BACKGROUND_LOAD[21];
		break;

	case '3':

		//背景23読込
		BACKGROUND = BACKGROUND_LOAD[22];
		break;

	case '4':

		//背景24読込
		BACKGROUND = BACKGROUND_LOAD[23];
		break;

	case '5':

		//背景25読込
		BACKGROUND = BACKGROUND_LOAD[24];
		break;

	case '6':

		//背景26読込
		BACKGROUND = BACKGROUND_LOAD[25];
		break;

	case '7':

		//背景27読込
		BACKGROUND = BACKGROUND_LOAD[26];
		break;

	case '8':

		//背景28読込
		BACKGROUND = BACKGROUND_LOAD[27];
		break;

	case '9':

		//背景29読込
		BACKGROUND = BACKGROUND_LOAD[28];
		break;
	}
}

//背景描画処理30～39
void BACKGROUND_DRAW_3() {

	switch (String[SP][CP])
	{
	case '0':

		//背景30読込
		BACKGROUND = BACKGROUND_LOAD[29];
		break;

	case '1':

		//背景31読込
		BACKGROUND = BACKGROUND_LOAD[30];
		break;

	case '2':

		//背景32読込
		BACKGROUND = BACKGROUND_LOAD[31];
		break;

	case '3':

		//背景33読込
		BACKGROUND = BACKGROUND_LOAD[32];
		break;

	case '4':

		//背景34読込
		BACKGROUND = BACKGROUND_LOAD[33];
		break;

	case '5':

		//背景35読込
		BACKGROUND = BACKGROUND_LOAD[34];
		break;

	case '6':

		//背景36読込
		BACKGROUND = BACKGROUND_LOAD[35];
		break;

	case '7':

		//背景37読込
		BACKGROUND = BACKGROUND_LOAD[36];
		break;

	case '8':

		//背景38読込
		BACKGROUND = BACKGROUND_LOAD[37];
		break;

	case '9':

		//背景39読込
		BACKGROUND = BACKGROUND_LOAD[38];
		break;
	}
}

//背景描画処理40～49
void BACKGROUND_DRAW_4() {

	switch (String[SP][CP])
	{
	case '0':

		//背景40読込
		BACKGROUND = BACKGROUND_LOAD[39];
		break;

	case '1':

		//背景41読込
		BACKGROUND = BACKGROUND_LOAD[40];
		break;

	case '2':

		//背景42読込
		BACKGROUND = BACKGROUND_LOAD[41];
		break;

	case '3':

		//背景43読込
		BACKGROUND = BACKGROUND_LOAD[42];
		break;

	case '4':

		//背景44読込
		BACKGROUND = BACKGROUND_LOAD[43];
		break;

	case '5':

		//背景45読込
		BACKGROUND = BACKGROUND_LOAD[44];
		break;

	case '6':

		//背景46読込
		BACKGROUND = BACKGROUND_LOAD[45];
		break;

	case '7':

		//背景47読込
		BACKGROUND = BACKGROUND_LOAD[46];
		break;

	case '8':

		//背景48読込
		BACKGROUND = BACKGROUND_LOAD[47];
		break;

	case '9':

		//背景49読込
		BACKGROUND = BACKGROUND_LOAD[48];
		break;
	}
}

//背景描画処理50～59
void BACKGROUND_DRAW_5() {

	switch (String[SP][CP])
	{
	case '0':

		//背景50読込
		BACKGROUND = BACKGROUND_LOAD[49];
		break;

	case '1':

		//背景51読込
		BACKGROUND = BACKGROUND_LOAD[50];
		break;

	case '2':

		//背景52読込
		BACKGROUND = BACKGROUND_LOAD[51];
		break;

	case '3':

		//背景53読込
		BACKGROUND = BACKGROUND_LOAD[52];
		break;

	case '4':

		//背景54読込
		BACKGROUND = BACKGROUND_LOAD[53];
		break;

	case '5':

		//背景55読込
		BACKGROUND = BACKGROUND_LOAD[54];
		break;

	case '6':

		//背景56読込
		BACKGROUND = BACKGROUND_LOAD[55];
		break;

	case '7':

		//背景57読込
		BACKGROUND = BACKGROUND_LOAD[56];
		break;

	case '8':

		//背景58読込
		BACKGROUND = BACKGROUND_LOAD[57];
		break;

	case '9':

		//背景59読込
		BACKGROUND = BACKGROUND_LOAD[58];
		break;
	}
}

//背景描画処理60～69
void BACKGROUND_DRAW_6() {

	switch (String[SP][CP])
	{
	case '0':

		//背景60読込
		BACKGROUND = BACKGROUND_LOAD[59];
		break;

	case '1':

		//背景61読込
		BACKGROUND = BACKGROUND_LOAD[60];
		break;

	case '2':

		//背景62読込
		BACKGROUND = BACKGROUND_LOAD[61];
		break;

	case '3':

		//背景63読込
		BACKGROUND = BACKGROUND_LOAD[62];
		break;

	case '4':

		//背景64読込
		BACKGROUND = BACKGROUND_LOAD[63];
		break;

	case '5':

		//背景65読込
		BACKGROUND = BACKGROUND_LOAD[64];
		break;

	case '6':

		//背景66読込
		BACKGROUND = BACKGROUND_LOAD[65];
		break;

	case '7':

		//背景67読込
		BACKGROUND = BACKGROUND_LOAD[66];
		break;

	case '8':

		//背景68読込
		BACKGROUND = BACKGROUND_LOAD[67];
		break;

	case '9':

		//背景69読込
		BACKGROUND = BACKGROUND_LOAD[68];
		break;
	}
}

//背景描画処理70～79
void BACKGROUND_DRAW_7() {

	switch (String[SP][CP])
	{
	case '0':

		//背景70読込
		BACKGROUND = BACKGROUND_LOAD[70];
		break;

	case '1':

		//背景71読込
		BACKGROUND = BACKGROUND_LOAD[70];
		break;

	case '2':

		//背景72読込
		BACKGROUND = BACKGROUND_LOAD[71];
		break;

	case '3':

		//背景73読込
		BACKGROUND = BACKGROUND_LOAD[72];
		break;

	case '4':

		//背景74読込
		BACKGROUND = BACKGROUND_LOAD[73];
		break;

	case '5':

		//背景75読込
		BACKGROUND = BACKGROUND_LOAD[74];
		break;

	case '6':

		//背景76読込
		BACKGROUND = BACKGROUND_LOAD[75];
		break;

	case '7':

		//背景77読込
		BACKGROUND = BACKGROUND_LOAD[76];

		break;

	case '8':

		//背景78読込
		BACKGROUND = BACKGROUND_LOAD[77];
		break;

	case '9':

		//背景79読込
		BACKGROUND = BACKGROUND_LOAD[78];
		break;
	}
}

//背景描画処理80～89
void BACKGROUND_DRAW_8() {

	switch (String[SP][CP])
	{
	case '0':

		//背景80読込
		BACKGROUND = BACKGROUND_LOAD[79];
		break;

	case '1':

		//背景81読込
		BACKGROUND = BACKGROUND_LOAD[80];
		break;

	case '2':

		//背景82読込
		BACKGROUND = BACKGROUND_LOAD[81];
		break;

	case '3':

		//背景83読込
		BACKGROUND = BACKGROUND_LOAD[82];
		break;

	case '4':

		//背景84読込
		BACKGROUND = BACKGROUND_LOAD[83];

		break;

	case '5':

		//背景85読込
		BACKGROUND = BACKGROUND_LOAD[84];
		break;

	case '6':

		//背景86読込
		BACKGROUND = BACKGROUND_LOAD[85];
		break;

	case '7':

		//背景87読込
		BACKGROUND = BACKGROUND_LOAD[86];
		break;

	case '8':

		//背景88読込
		BACKGROUND = BACKGROUND_LOAD[87];
		break;

	case '9':

		//背景89読込
		BACKGROUND = BACKGROUND_LOAD[88];
		break;
	}
}

//背景描画処理90～99
void BACKGROUND_DRAW_9() {

	switch (String[SP][CP])
	{
	case '0':

		//背景90読込
		BACKGROUND = BACKGROUND_LOAD[89];
		break;

	case '1':

		//背景91読込
		BACKGROUND = BACKGROUND_LOAD[90];
		break;

	case '2':

		//背景92読込
		BACKGROUND = BACKGROUND_LOAD[91];
		break;

	case '3':

		//背景93読込
		BACKGROUND = BACKGROUND_LOAD[92];
		break;

	case '4':

		//背景94読込
		BACKGROUND = BACKGROUND_LOAD[93];
		break;

	case '5':

		//背景95読込
		BACKGROUND = BACKGROUND_LOAD[94];
		break;

	case '6':

		//背景96読込
		BACKGROUND = BACKGROUND_LOAD[95];
		break;

	case '7':

		//背景97読込
		BACKGROUND = BACKGROUND_LOAD[96];
		break;

	case '8':

		//背景98読込
		BACKGROUND = BACKGROUND_LOAD[97];
		break;

	case '9':

		//背景99読込
		BACKGROUND = BACKGROUND_LOAD[98];
		break;
	}
}

//背景描画処理
void BACKGROUND_DRAW() {

	switch (String[SP][CP]) {

	case '0':

		CP++;

		BACKGROUND_DRAW_0();
		break;

	case '1':

		CP++;

		BACKGROUND_DRAW_1();
		break;

	case '2':

		CP++;

		BACKGROUND_DRAW_2();
		break;

	case '3':

		CP++;

		BACKGROUND_DRAW_3();
		break;

	case '4':

		CP++;

		BACKGROUND_DRAW_4();
		break;

	case '5':

		CP++;

		BACKGROUND_DRAW_5();
		break;

	case '6':

		CP++;

		BACKGROUND_DRAW_6();
		break;

	case '7':

		CP++;

		BACKGROUND_DRAW_7();
		break;

	case '8':

		CP++;

		BACKGROUND_DRAW_8();
		break;

	case '9':

		CP++;

		BACKGROUND_DRAW_9();
		break;
	}
}

//BGM再生処理1～9
void BACKGROUNDMUSIC_START_0() {

	switch (String[SP][CP])
	{
	case '1':

		//BGM01読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[0];
		break;

	case '2':

		//BGM02読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[1];
		break;

	case '3':

		//BGM03読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[2];
		break;

	case '4':

		//BGM04読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[3];
		break;

	case '5':

		//BGM05読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[4];
		break;

	case '6':

		//BGM06読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[5];
		break;

	case '7':

		//BGM07読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[6];
		break;

	case '8':

		//BGM08読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[7];
		break;

	case '9':

		//BGM09読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[8];
		break;
	}
}

//BGM再生処理10～19
void BACKGROUNDMUSIC_START_1() {

	switch (String[SP][CP])
	{
	case '0':

		//BGM10読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[9];
		break;

	case '1':

		//BGM11読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[10];
		break;

	case '2':

		//BGM12読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[11];
		break;

	case '3':

		//BGM13読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[12];
		break;

	case '4':

		//BGM14読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[13];
		break;

	case '5':

		//BGM15読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[14];
		break;

	case '6':

		//BGM16読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[15];
		break;

	case '7':

		//BGM17読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[16];
		break;

	case '8':

		//BGM18読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[17];
		break;

	case '9':

		//BGM19読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[18];
		break;
	}
}

//BGM再生処理20～29
void BACKGROUNDMUSIC_START_2() {

	switch (String[SP][CP])
	{
	case '0':

		//BGM20読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[19];
		break;

	case '1':

		//BGM21読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[20];
		break;

	case '2':

		//BGM22読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[21];
		break;

	case '3':

		//BGM23読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[22];
		break;

	case '4':

		//BGM24読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[23];
		break;

	case '5':

		//BGM25読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[24];
		break;

	case '6':

		//BGM26読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[25];
		break;

	case '7':

		//BGM27読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[26];
		break;

	case '8':

		//BGM28読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[27];
		break;

	case '9':

		//BGM29読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[28];
		break;
	}
}

//BGM再生処理30～39
void BACKGROUNDMUSIC_START_3() {

	switch (String[SP][CP])
	{
	case '0':

		//BGM30読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[29];
		break;

	case '1':

		//BGM31読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[30];
		break;

	case '2':

		//BGM32読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[31];
		break;

	case '3':

		//BGM33読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[32];
		break;

	case '4':

		//BGM34読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[33];
		break;

	case '5':

		//BGM35読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[34];
		break;

	case '6':

		//BGM36読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[35];
		break;

	case '7':

		//BGM37読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[36];
		break;

	case '8':

		//BGM38読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[37];
		break;

	case '9':

		//BGM39読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[38];
		break;
	}
}

//BGM再生処理40～49
void BACKGROUNDMUSIC_START_4() {

	switch (String[SP][CP])
	{
	case '0':

		//BGM40読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[39];
		break;

	case '1':

		//BGM41読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[40];
		break;

	case '2':

		//BGM42読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[41];
		break;

	case '3':

		//BGM43読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[42];
		break;

	case '4':

		//BGM44読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[43];
		break;

	case '5':

		//BGM45読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[44];
		break;

	case '6':

		//BGM46読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[45];
		break;

	case '7':

		//BGM47読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[46];
		break;

	case '8':

		//BGM48読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[47];
		break;

	case '9':

		//BGM49読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[48];
		break;
	}
}

//BGM再生処理50～59
void BACKGROUNDMUSIC_START_5() {

	switch (String[SP][CP])
	{
	case '0':

		//BGM50読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[49];
		break;

	case '1':

		//BGM51読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[50];
		break;

	case '2':

		//BGM52読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[51];
		break;

	case '3':

		//BGM53読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[52];
		break;

	case '4':

		//BGM54読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[53];
		break;

	case '5':

		//BGM55読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[54];
		break;

	case '6':

		//BGM56読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[55];
		break;

	case '7':

		//BGM57読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[56];
		break;

	case '8':

		//BGM58読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[57];
		break;

	case '9':

		//BGM59読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[58];
		break;
	}
}

//BGM再生処理60～69
void BACKGROUNDMUSIC_START_6() {

	switch (String[SP][CP])
	{
	case '0':

		//BGM60読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[59];
		break;

	case '1':

		//BGM61読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[60];
		break;

	case '2':

		//BGM62読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[61];
		break;

	case '3':

		//BGM63読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[62];
		break;

	case '4':

		//BGM64読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[63];
		break;

	case '5':

		//BGM65読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[64];
		break;

	case '6':

		//BGM66読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[65];
		break;

	case '7':

		//BGM67読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[66];
		break;

	case '8':

		//BGM68読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[67];
		break;

	case '9':

		//BGM69読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[68];
		break;
	}
}

//BGM再生処理70～79
void BACKGROUNDMUSIC_START_7() {

	switch (String[SP][CP])
	{
	case '0':

		//BGM70読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[70];
		break;

	case '1':

		//BGM71読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[70];
		break;

	case '2':

		//BGM72読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[71];
		break;

	case '3':

		//BGM73読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[72];
		break;

	case '4':

		//BGM74読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[73];
		break;

	case '5':

		//BGM75読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[74];
		break;

	case '6':

		//BGM76読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[75];
		break;

	case '7':

		//BGM77読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[76];
		break;

	case '8':

		//BGM78読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[77];
		break;

	case '9':

		//BGM79読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[78];
		break;
	}
}

//BGM再生処理80～89
void BACKGROUNDMUSIC_START_8() {

	switch (String[SP][CP])
	{
	case '0':

		//BGM80読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[79];

		break;

	case '1':

		//BGM81読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[80];
		break;

	case '2':

		//BGM82読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[81];
		break;

	case '3':

		//BGM83読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[82];
		break;

	case '4':

		//BGM84読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[83];

		break;

	case '5':

		//BGM85読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[84];
		break;

	case '6':

		//BGM86読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[85];
		break;

	case '7':

		//BGM87読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[86];
		break;

	case '8':

		//BGM88読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[87];
		break;

	case '9':

		//BGM89読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[88];
		break;
	}
}

//BGM再生処理90～99
void BACKGROUNDMUSIC_START_9() {

	switch (String[SP][CP])
	{
	case '0':

		//BGM90読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[89];
		break;

	case '1':

		//BGM91読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[90];
		break;

	case '2':

		//BGM92読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[91];
		break;

	case '3':

		//BGM93読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[92];
		break;

	case '4':

		//BGM94読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[93];
		break;

	case '5':

		//BGM95読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[94];
		break;

	case '6':

		//BGM96読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[95];
		break;

	case '7':

		//BGM97読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[96];
		break;

	case '8':

		//BGM98読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[97];
		break;

	case '9':

		//BGM99読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[98];
		break;
	}
}

//BGM再生処理
void BACKGROUNDMUSIC_START() {

	switch (String[SP][CP]) {

	case '0':

		CP++;

		BACKGROUNDMUSIC_START_0();
		break;

	case '1':

		CP++;

		BACKGROUNDMUSIC_START_1();
		break;

	case '2':

		CP++;

		BACKGROUNDMUSIC_START_2();
		break;

	case '3':

		CP++;

		BACKGROUNDMUSIC_START_3();
		break;

	case '4':

		CP++;

		BACKGROUNDMUSIC_START_4();
		break;

	case '5':

		CP++;

		BACKGROUNDMUSIC_START_5();
		break;

	case '6':

		CP++;

		BACKGROUNDMUSIC_START_6();
		break;

	case '7':

		CP++;

		BACKGROUNDMUSIC_START_7();
		break;

	case '8':

		CP++;

		BACKGROUNDMUSIC_START_8();
		break;

	case '9':

		CP++;

		BACKGROUNDMUSIC_START_9();
		break;

	}
}

//SE再生処理1～9
void SOUNDEFFECT_START_0() {

	switch (String[SP][CP])
	{
	case '1':

		//SE01読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[0];
		break;

	case '2':

		//SE02読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[1];
		break;

	case '3':

		//SE03読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[2];
		break;

	case '4':

		//SE04読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[3];

		break;

	case '5':

		//SE05読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[4];
		break;

	case '6':

		//SE06読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[5];
		break;

	case '7':

		//SE07読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[6];
		break;

	case '8':

		//SE08読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[7];
		break;

	case '9':

		//SE09読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[8];
		break;
	}
}

//SE再生処理10～19
void SOUNDEFFECT_START_1() {

	switch (String[SP][CP])
	{
	case '0':

		//SE10読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[9];
		break;

	case '1':

		//SE11読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[10];
		break;

	case '2':

		//SE12読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[11];
		break;

	case '3':

		//SE13読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[12];
		break;

	case '4':

		//SE14読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[13];
		break;

	case '5':

		//SE15読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[14];
		break;

	case '6':

		//SE16読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[15];
		break;

	case '7':

		//SE17読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[16];
		break;

	case '8':

		//SE18読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[17];
		break;

	case '9':

		//SE19読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[18];
		break;
	}
}

//SE再生処理20～29
void SOUNDEFFECT_START_2() {

	switch (String[SP][CP])
	{
	case '0':

		//SE20読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[19];
		break;

	case '1':

		//SE21読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[20];
		break;

	case '2':

		//SE22読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[21];
		break;

	case '3':

		//SE23読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[22];
		break;

	case '4':

		//SE24読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[23];
		break;

	case '5':

		//SE25読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[24];
		break;

	case '6':

		//SE26読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[25];
		break;

	case '7':

		//SE27読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[26];
		break;

	case '8':

		//SE28読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[27];
		break;

	case '9':

		//SE29読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[28];
		break;
	}
}

//SE再生処理30～39
void SOUNDEFFECT_START_3() {

	switch (String[SP][CP])
	{
	case '0':

		//SE30読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[29];
		break;

	case '1':

		//SE31読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[30];
		break;

	case '2':

		//SE32読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[31];
		break;

	case '3':

		//SE33読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[32];
		break;

	case '4':

		//SE34読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[33];
		break;

	case '5':

		//SE35読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[34];
		break;

	case '6':

		//SE36読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[35];
		break;

	case '7':

		//SE37読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[36];
		break;

	case '8':

		//SE38読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[37];
		break;

	case '9':

		//SE39読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[38];
		break;
	}
}

//SE再生処理4～49
void SOUNDEFFECT_START_4() {

	switch (String[SP][CP])
	{
	case '0':

		//SE40読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[39];
		break;

	case '1':

		//SE41読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[40];
		break;

	case '2':

		//SE42読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[41];
		break;

	case '3':

		//SE43読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[42];
		break;

	case '4':

		//SE44読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[43];
		break;

	case '5':

		//SE45読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[44];
		break;

	case '6':

		//SE46読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[45];
		break;

	case '7':

		//SE47読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[46];
		break;

	case '8':

		//SE48読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[47];
		break;

	case '9':

		//SE49読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[48];
		break;
	}
}

//SE再生処理50～59
void SOUNDEFFECT_START_5() {

	switch (String[SP][CP])
	{
	case '0':

		//SE50読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[49];
		break;

	case '1':

		//SE51読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[50];
		break;

	case '2':

		//SE52読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[51];
		break;

	case '3':

		//SE53読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[52];
		break;

	case '4':

		//SE54読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[53];

		break;

	case '5':

		//SE55読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[54];
		break;

	case '6':

		//SE56読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[55];
		break;

	case '7':

		//SE57読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[56];
		break;

	case '8':

		//SE58読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[57];
		break;

	case '9':

		//SE59読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[58];
		break;
	}
}

//SE再生処理60～69
void SOUNDEFFECT_START_6() {

	switch (String[SP][CP])
	{
	case '0':

		//SE60読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[59];
		break;

	case '1':

		//SE61読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[60];
		break;

	case '2':

		//SE62読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[61];
		break;

	case '3':

		//SE63読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[62];
		break;

	case '4':

		//SE64読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[63];
		break;

	case '5':

		//SE65読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[64];
		break;

	case '6':

		//SE66読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[65];
		break;

	case '7':

		//SE67読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[66];
		break;

	case '8':

		//SE68読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[67];
		break;

	case '9':

		//SE69読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[68];
		break;
	}
}

//SE再生処理70～79
void SOUNDEFFECT_START_7() {

	switch (String[SP][CP])
	{
	case '0':

		//SE70読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[70];
		break;

	case '1':

		//SE71読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[70];
		break;

	case '2':

		//SE72読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[71];
		break;

	case '3':

		//SE73読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[72];
		break;

	case '4':

		//SE74読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[73];
		break;

	case '5':

		//SE75読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[74];
		break;

	case '6':

		//SE76読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[75];
		break;

	case '7':

		//SE77読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[76];
		break;

	case '8':

		//SE78読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[77];
		break;

	case '9':

		//SE79読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[78];
		break;
	}
}

//SE再生処理80～89
void SOUNDEFFECT_START_8() {

	switch (String[SP][CP])
	{
	case '0':

		//SE80読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[79];
		break;

	case '1':

		//SE81読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[80];
		break;

	case '2':

		//SE82読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[81];
		break;

	case '3':

		//SE83読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[82];
		break;

	case '4':

		//SE84読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[83];
		break;

	case '5':

		//SE85読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[84];
		break;

	case '6':

		//SE86読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[85];
		break;

	case '7':

		//SE87読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[86];
		break;

	case '8':

		//SE88読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[87];
		break;

	case '9':

		//SE89読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[88];
		break;
	}
}

//SE再生処理90～99
void SOUNDEFFECT_START_9() {

	switch (String[SP][CP])
	{
	case '0':

		//SE90読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[89];
		break;

	case '1':

		//SE91読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[90];
		break;

	case '2':

		//SE92読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[91];
		break;

	case '3':

		//SE93読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[92];
		break;

	case '4':

		//SE94読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[93];
		break;

	case '5':

		//SE95読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[94];
		break;

	case '6':

		//SE96読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[95];
		break;

	case '7':

		//SE97読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[96];
		break;

	case '8':

		//SE98読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[97];
		break;

	case '9':

		//SE99読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[98];
		break;
	}
}

//SE再生処理
void SOUNDEFFECT_START() {

	switch (String[SP][CP]) {

	case '0':

		CP++;

		SOUNDEFFECT_START_0();
		break;

	case '1':

		CP++;

		SOUNDEFFECT_START_1();
		break;

	case '2':

		CP++;

		SOUNDEFFECT_START_2();
		break;

	case '3':

		CP++;

		SOUNDEFFECT_START_3();
		break;

	case '4':

		CP++;

		SOUNDEFFECT_START_4();
		break;

	case '5':

		CP++;

		SOUNDEFFECT_START_5();
		break;

	case '6':

		CP++;

		SOUNDEFFECT_START_6();
		break;

	case '7':

		CP++;

		SOUNDEFFECT_START_7();
		break;

	case '8':

		CP++;

		SOUNDEFFECT_START_8();
		break;

	case '9':

		CP++;

		SOUNDEFFECT_START_9();
		break;
	}
}

//動画再生1～9
void MOVIE_START_0() {

	switch (String[SP][CP])
	{
	case '1':

		//動画01読込
		PlayMovie("DATA/MOVIE/MOVIE01.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '2':

		//動画02読込
		PlayMovie("DATA/MOVIE/MOVIE02.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '3':

		//動画03読込
		PlayMovie("DATA/MOVIE/MOVIE03.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '4':

		//動画04読込
		PlayMovie("DATA/MOVIE/MOVIE04.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '5':

		//動画05読込
		PlayMovie("DATA/MOVIE/MOVIE05.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '6':

		//動画06読込
		PlayMovie("DATA/MOVIE/MOVIE06.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '7':

		//動画07読込
		PlayMovie("DATA/MOVIE/MOVIE07.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '8':

		//動画08読込
		PlayMovie("DATA/MOVIE/MOVIE08.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '9':

		//動画09読込
		PlayMovie("DATA/MOVIE/MOVIE09.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;
	}
}

//動画再生10～19
void MOVIE_START_1() {

	switch (String[SP][CP])
	{
	case '0':

		//動画10読込
		PlayMovie("DATA/MOVIE/MOVIE10.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '1':

		//動画11読込
		PlayMovie("DATA/MOVIE/MOVIE11.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '2':

		//動画12読込
		PlayMovie("DATA/MOVIE/MOVIE12.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '3':

		//動画13読込
		PlayMovie("DATA/MOVIE/MOVIE13.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '4':

		//動画14読込
		PlayMovie("DATA/MOVIE/MOVIE14.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '5':

		//動画15読込
		PlayMovie("DATA/MOVIE/MOVIE15.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '6':

		//動画16読込
		PlayMovie("DATA/MOVIE/MOVIE16.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '7':

		//動画17読込
		PlayMovie("DATA/MOVIE/MOVIE17.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '8':

		//動画18読込
		PlayMovie("DATA/MOVIE/MOVIE18.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '9':

		//動画19読込
		PlayMovie("DATA/MOVIE/MOVIE19.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;
	}
}

//動画再生20～29
void MOVIE_START_2() {

	switch (String[SP][CP])
	{
	case '0':

		//動画20読込
		PlayMovie("DATA/MOVIE/MOVIE20.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '1':

		//動画21読込
		PlayMovie("DATA/MOVIE/MOVIE21.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '2':

		//動画22読込
		PlayMovie("DATA/MOVIE/MOVIE22.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '3':

		//動画23読込
		PlayMovie("DATA/MOVIE/MOVIE23.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '4':

		//動画24読込
		PlayMovie("DATA/MOVIE/MOVIE24.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '5':

		//動画25読込
		PlayMovie("DATA/MOVIE/MOVIE25.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);

		break;

	case '6':

		//動画26読込
		PlayMovie("DATA/MOVIE/MOVIE26.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '7':

		//動画27読込
		PlayMovie("DATA/MOVIE/MOVIE27.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '8':

		//動画28読込
		PlayMovie("DATA/MOVIE/MOVIE28.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '9':

		//動画29読込
		PlayMovie("DATA/MOVIE/MOVIE29.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;
	}
}

//動画再生30～39
void MOVIE_START_3() {

	switch (String[SP][CP])
	{
	case '0':

		//動画30読込
		PlayMovie("DATA/MOVIE/MOVIE30.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '1':

		//動画31読込
		PlayMovie("DATA/MOVIE/MOVIE31.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '2':

		//動画32読込
		PlayMovie("DATA/MOVIE/MOVIE32.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '3':

		//動画33読込
		PlayMovie("DATA/MOVIE/MOVIE33.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '4':

		//動画34読込
		PlayMovie("DATA/MOVIE/MOVIE34.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '5':

		//動画35読込
		PlayMovie("DATA/MOVIE/MOVIE35.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '6':

		//動画36読込
		PlayMovie("DATA/MOVIE/MOVIE36.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '7':

		//動画37読込
		PlayMovie("DATA/MOVIE/MOVIE37.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '8':

		//動画38読込
		PlayMovie("DATA/MOVIE/MOVIE38.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '9':

		//動画39読込
		PlayMovie("DATA/MOVIE/MOVIE39.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;
	}
}

//動画再生40～49
void MOVIE_START_4() {

	switch (String[SP][CP])
	{
	case '0':

		//動画40読込
		PlayMovie("DATA/MOVIE/MOVIE40.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '1':

		//動画41読込
		PlayMovie("DATA/MOVIE/MOVIE41.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '2':

		//動画42読込
		PlayMovie("DATA/MOVIE/MOVIE42.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);

		break;

	case '3':

		//動画43読込
		PlayMovie("DATA/MOVIE/MOVIE43.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '4':

		//動画44読込
		PlayMovie("DATA/MOVIE/MOVIE44.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '5':

		//動画45読込
		PlayMovie("DATA/MOVIE/MOVIE45.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '6':

		//動画46読込
		PlayMovie("DATA/MOVIE/MOVIE46.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '7':

		//動画47読込
		PlayMovie("DATA/MOVIE/MOVIE47.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '8':

		//動画48読込
		PlayMovie("DATA/MOVIE/MOVIE48.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '9':

		//動画49読込
		PlayMovie("DATA/MOVIE/MOVIE49.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;
	}
}

//動画再生50～59
void MOVIE_START_5() {

	switch (String[SP][CP])
	{
	case '0':

		//動画50読込
		PlayMovie("DATA/MOVIE/MOVIE50.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '1':

		//動画51読込
		PlayMovie("DATA/MOVIE/MOVIE51.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '2':

		//動画52読込
		PlayMovie("DATA/MOVIE/MOVIE52.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '3':

		//動画53読込
		PlayMovie("DATA/MOVIE/MOVIE53.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '4':

		//動画54読込
		PlayMovie("DATA/MOVIE/MOVIE54.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '5':

		//動画55読込
		PlayMovie("DATA/MOVIE/MOVIE55.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '6':

		//動画56読込
		PlayMovie("DATA/MOVIE/MOVIE56.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '7':

		//動画57読込
		PlayMovie("DATA/MOVIE/MOVIE57.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '8':

		//動画58読込
		PlayMovie("DATA/MOVIE/MOVIE58.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '9':

		//動画59読込
		PlayMovie("DATA/MOVIE/MOVIE59.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;
	}
}

//動画再生60～69
void MOVIE_START_6() {

	switch (String[SP][CP])
	{
	case '0':

		//動画60読込
		PlayMovie("DATA/MOVIE/MOVIE60.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '1':

		//動画61読込
		PlayMovie("DATA/MOVIE/MOVIE61.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '2':

		//動画62読込
		PlayMovie("DATA/MOVIE/MOVIE62.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '3':

		//動画63読込
		PlayMovie("DATA/MOVIE/MOVIE63.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '4':

		//動画64読込
		PlayMovie("DATA/MOVIE/MOVIE64.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '5':

		//動画65読込
		PlayMovie("DATA/MOVIE/MOVIE65.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '6':

		//動画66読込
		PlayMovie("DATA/MOVIE/MOVIE66.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '7':

		//動画67読込
		PlayMovie("DATA/MOVIE/MOVIE67.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '8':

		//動画68読込
		PlayMovie("DATA/MOVIE/MOVIE68.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '9':

		//動画69読込
		PlayMovie("DATA/MOVIE/MOVIE69.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;
	}
}

//動画再生70～79
void MOVIE_START_7() {

	switch (String[SP][CP])
	{
	case '0':

		//動画70読込
		PlayMovie("DATA/MOVIE/MOVIE70.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '1':

		//動画71読込
		PlayMovie("DATA/MOVIE/MOVIE71.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '2':

		//動画72読込
		PlayMovie("DATA/MOVIE/MOVIE72.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '3':

		//動画73読込
		PlayMovie("DATA/MOVIE/MOVIE73.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '4':

		//動画74読込
		PlayMovie("DATA/MOVIE/MOVIE74.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '5':

		//動画75読込
		PlayMovie("DATA/MOVIE/MOVIE75.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '6':

		//動画76読込
		PlayMovie("DATA/MOVIE/MOVIE76.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '7':

		//動画77読込
		PlayMovie("DATA/MOVIE/MOVIE77.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '8':

		//動画78読込
		PlayMovie("DATA/MOVIE/MOVIE78.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '9':

		//動画79読込
		PlayMovie("DATA/MOVIE/MOVIE79.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;
	}
}

//動画再生80～89
void MOVIE_START_8() {

	switch (String[SP][CP])
	{
	case '0':

		//動画80読込
		PlayMovie("DATA/MOVIE/MOVIE80.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '1':

		//動画81読込
		PlayMovie("DATA/MOVIE/MOVIE81.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '2':

		//動画82読込
		PlayMovie("DATA/MOVIE/MOVIE82.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '3':

		//動画83読込
		PlayMovie("DATA/MOVIE/MOVIE83.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '4':

		//動画84読込
		PlayMovie("DATA/MOVIE/MOVIE84.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);

		break;

	case '5':

		//動画85読込
		PlayMovie("DATA/MOVIE/MOVIE85.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '6':

		//動画86読込
		PlayMovie("DATA/MOVIE/MOVIE86.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '7':

		//動画87読込
		PlayMovie("DATA/MOVIE/MOVIE87.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '8':

		//動画88読込
		PlayMovie("DATA/MOVIE/MOVIE88.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '9':

		//動画89読込
		PlayMovie("DATA/MOVIE/MOVIE89.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;
	}
}

//動画再生90～99
void MOVIE_START_9() {

	switch (String[SP][CP])
	{
	case '0':

		//動画90読込
		PlayMovie("DATA/MOVIE/MOVIE90.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '1':

		//動画91読込
		PlayMovie("DATA/MOVIE/MOVIE91.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '2':

		//動画92読込
		PlayMovie("DATA/MOVIE/MOVIE92.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '3':

		//動画93読込
		PlayMovie("DATA/MOVIE/MOVIE93.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '4':

		//動画94読込
		PlayMovie("DATA/MOVIE/MOVIE94.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '5':

		//動画95読込
		PlayMovie("DATA/MOVIE/MOVIE95.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '6':

		//動画96読込
		PlayMovie("DATA/MOVIE/MOVIE96.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '7':

		//動画97読込
		PlayMovie("DATA/MOVIE/MOVIE97.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '8':

		//動画98読込
		PlayMovie("DATA/MOVIE/MOVIE98.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

	case '9':

		//動画99読込
		PlayMovie("DATA/MOVIE/MOVIE99.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;
	}
}

//動画再生処理
void MOVIE_START() {

	switch (String[SP][CP]) {

	case '0':

		CP++;

		MOVIE_START_0();
		break;

	case '1':

		CP++;

		MOVIE_START_1();
		break;

	case '2':

		CP++;

		MOVIE_START_2();
		break;

	case '3':

		CP++;

		MOVIE_START_3();
		break;

	case '4':

		CP++;

		MOVIE_START_4();
		break;

	case '5':

		CP++;

		MOVIE_START_5();
		break;

	case '6':

		CP++;

		MOVIE_START_6();
		break;

	case '7':

		CP++;

		MOVIE_START_7();
		break;

	case '8':

		CP++;

		MOVIE_START_8();
		break;

	case '9':

		CP++;

		MOVIE_START_9();
		break;
	}
}

//コメント処理
void COMMENT() {

	switch (String[SP][CP]) {

		case '/':

			SP++;
			CP = 0;
			break;
	}
}

//スクリプトタグ処理(メイン)関数
int SCRIPT_OUTPUT() {

	char  Moji;

	// 文字の描画
	Moji = String[SP][CP];

	switch (Moji)
	{

		//キャラクター描画処理
	case 'C':

		CP++;

		CHARACTER_DRAW();

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//背景描画処理
	case 'B':

		CP++;

		BACKGROUND_DRAW();

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//BGM再生処理
	case 'M':

		CP++;

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC_START();

		//BGM再生処理
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//SE再生処理
	case 'S':

		CP++;

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT_START();

		//SE再生処理
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//ムービー再生処理
	case 'V':

		CP++;

		MOVIE_START();
		break;

		// 改行文字
	case 'L':

		// 改行処理および参照文字位置を一つ進める
		Kaigyou();
		CP++;
		break;

		// ボタン押し待ち文字
	case 'P':

		//クリック待ち処理
		SCRIPT_UTPUT_KEYWAIT();
		break;

		// クリア文字
	case 'R':

		//ゲーム画面のクリア処理
		SCRIPT_OUTPUT_SCREENCLEAR();
		break;

		//少し待つ
	case 'W':

		//スクリプトタグ処理(少し待つ)
		SCRIPT_OUTPUT_WAIT();
		break;

		//ゲームオーバー
	case 'G':

		//ゲームオーバー画面処理
		SCRIPT_OUTPUT_GAMEOVER();
		break;

		//エンディング
	case 'F':

		//エンディング再生
		SCRIPT_OUTPUT_ENDING();
		break;

		//BGMの再生を止める
	case 'O':

		//BGMの再生を止める
		SCRIPT_OUTPUT_BGMSTOP();
		break;

		//SEの再生を止める
	case 'Q':

		//SEの再生を止める
		SCRIPT_OUTPUT_SESTOP();
		break;

		//選択肢の表示
	case 'D':

		//選択肢描画処理
		SCRIPT_OUTPUT_CHOICE();
		break;

		// 終了文字
	case 'E':

		//スクリプトタグ処理(終了文字)
		SCRIPT_OUTPUT_END();
		break;

		//立ち絵消しタグ
	case '@':

		//立ち絵クリア処理
		SCRIPT_OUTPUT_CHARACTER_REMOVE();
		break;

		//ウインドウ風キャラクター名描画タグ
	case '#':

		//キャラクター名描画処理
		SCRIPT_OUTPUT_CHARACTER_NAME();
		break;

		//コメントタグ
	case '/' :

		CP++;

		//コメントタグ処理
		COMMENT();
		break;

	case ' ':
		CP++;
		break;

	default:	// その他の文字

				//文字列の描画処理
		SCRIPT_OUTPUT_STRING_DRAW();

		//文字列の描画速度
		SCRIPT_OUTPUT_STRING_DRAW_SPEED();

		//文字列の描画速度
		SCRIPT_OUTPUT_STRING_KAIGYO();

		//サウンドノベル風時の改ページ処理
		SCRIPT_OUTPUT_STRING_PAGE_CLEAR_SOUNDNOVEL();

		//ウインドウ風時の改ページ処理
		SCRIPT_OUTPUT_STRING_PAGE_CLEAR_WINODWNOVEL();
		break;
	}
	return 0;
}

//初期化
int FORMAT() {

	// 描画位置の初期位置セット（横）
	DrawPointX = 0;
	DrawPointY = 0;

	// 参照文字位置をセット
	SP = 0;	// １行目の
	CP = 0;	// ０文字

	FileRead_close(ScriptFile);
	FileRead_close(Choice1);
	FileRead_close(Choice2);

	return 0;
}

//スクリーンショット取得後の処理
void SCREEN_SHOT_COUNT() {

	WaitTimer(300);
	SCREENSHOT_COUNT++;
}

//スクリーンショット01取得機能
void SCREENSHOT_01() {

	//スクリーンショット０１取得
	if (SCREENSHOT_COUNT == 0 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT01.png", 0);

		LINKS_MessageBox_OK("スクリーンショット０１を取得しました！");

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット02取得機能
void SCREENSHOT_02() {

	//スクリーンショット０２取得
	if (SCREENSHOT_COUNT == 1 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT02.png", 0);

		LINKS_MessageBox_OK("スクリーンショット０２を取得しました！");

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット03取得機能
void SCREENSHOT_03() {

	//スクリーンショット０３取得
	if (SCREENSHOT_COUNT == 2 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT03.png", 0);

		LINKS_MessageBox_OK("スクリーンショット０３を取得しました！");

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット04取得機能
void SCREENSHOT_04() {

	//スクリーンショット０４取得
	if (SCREENSHOT_COUNT == 3 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT04.png", 0);

		LINKS_MessageBox_OK("スクリーンショット０４を取得しました！");

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット05取得機能
void SCREENSHOT_05() {

	//スクリーンショット０５取得
	if (SCREENSHOT_COUNT == 4 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT05.png", 0);

		LINKS_MessageBox_OK("スクリーンショット０５を取得しました！");

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット06取得機能
void SCREENSHOT_06() {

	//スクリーンショット０６取得
	if (SCREENSHOT_COUNT == 5 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT06.png", 0);

		LINKS_MessageBox_OK("スクリーンショット０６を取得しました！");

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット07取得機能
void SCREENSHOT_07() {

	//スクリーンショット０７取得
	if (SCREENSHOT_COUNT == 6 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT07.png", 0);

		LINKS_MessageBox_OK("スクリーンショット０７を取得しました！");

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット08取得機能
void SCREENSHOT_08() {

	//スクリーンショット０８取得
	if (SCREENSHOT_COUNT == 7 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT08.png", 0);

		LINKS_MessageBox_OK("スクリーンショット０８を取得しました！");

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット09取得機能
void SCREENSHOT_09() {

	//スクリーンショット０９取得
	if (SCREENSHOT_COUNT == 8 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT09.png", 0);

		LINKS_MessageBox_OK("スクリーンショット０９を取得しました！");

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット10取得機能
void SCREENSHOT_10() {

	//スクリーンショット１０取得
	if (SCREENSHOT_COUNT == 9 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT10.png", 0);

		LINKS_MessageBox_OK("スクリーンショット１０を取得しました！");

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット機能
int SCREENSHOT() {

	//スクリーンショット01取得機能
	SCREENSHOT_01();

	//スクリーンショット02取得機能
	SCREENSHOT_02();

	//スクリーンショット03取得機能
	SCREENSHOT_03();

	//スクリーンショット04取得機能
	SCREENSHOT_04();

	//スクリーンショット05取得機能
	SCREENSHOT_05();

	//スクリーンショット06取得機能
	SCREENSHOT_06();

	//スクリーンショット07取得機能
	SCREENSHOT_07();

	//スクリーンショット08取得機能
	SCREENSHOT_08();

	//スクリーンショット09取得機能
	SCREENSHOT_09();

	//スクリーンショット10取得機能
	SCREENSHOT_10();

	//スクリーンショット取得限界メッセージ
	if (SCREENSHOT_COUNT >= 10 && CheckHitKey(KEY_INPUT_F12) == 1) {

		LINKS_MessageBox_OK("これ以上スクリーンショットを取得できません");

		WaitTimer(300);
	}

	return 0;
}

//各種F1～F11キー
void SHORTCUT_KEY() {

	//セーブ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F1) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = 0;
		SAVEDATA_SAVE();
	}

	//ロード
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F2) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = 0;
		SAVEDATA_LOAD();
	}

	//セーブデータ削除
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F3) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = 0;
		SAVEDATA_DELETE();
	}

	//既読スキップ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F4) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = 0;
		SKIP_READ_CHECK();
	}

	//スキップ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F5) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = 0;
		SKIP_START();
	}

	//オート
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F6) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = 0;
		AUTO_START();
	}

	//スキップ&オート停止
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F7) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = 0;
		AUTO_SKIP_STOP();
	}

	//バックログ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F8) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = 0;
		BACKLOG_DRAW();
	}

	//設定
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F9) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = 0;
		CONFIG();
	}

	//クイックセーブ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F10) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = 0;
		QUICKSAVE_SAVE();
	}
}