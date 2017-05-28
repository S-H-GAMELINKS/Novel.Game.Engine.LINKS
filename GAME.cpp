//ライブラリとヘッダの読み込み
#include "GAME.h"
#include "DxLib.h"
#include "DEF.h"
#include <initializer_list>
#include <cassert>

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
static int CHARACTER_LOAD[99];
static int CHARACTER, CHARACTER_DUMMY;

//背景画像読込変数
static int BACKGROUND_LOAD[99];
static int BACKGROUND;

//背景音楽読込変数
static int BACKGROUNDMUSIC_LOAD[99];
static int BACKGROUNDMUSIC;

//効果音変数
static int SOUNDEFFECT_LOAD[99];
static int SOUNDEFFECT;

//スクリプト用読込配列
char String[GYOU][RETU];

//タイトル関連
int TITLE;
unsigned int Cr;

//ゲームオーバー
static int GAMEOVER;

//選択肢読込変数
static char ChoiceStrings[2][RETU];
static int Choices[2];
static const char* const ChoiceFiles[][2] = {
	{ "DATA/STR/CHOICE/A.txt", "DATA/STR/CHOICE/B.txt" },
	{ "DATA/STR/CHOICE/C.txt", "DATA/STR/CHOICE/D.txt" },
	{ "DATA/STR/CHOICE/E.txt", "DATA/STR/CHOICE/F.txt" },
	{ "DATA/STR/CHOICE/G.txt", "DATA/STR/CHOICE/H.txt" },
	{ "DATA/STR/CHOICE/I.txt", "DATA/STR/CHOICE/J.txt" },
	{ "DATA/STR/CHOICE/K.txt", "DATA/STR/CHOICE/L.txt" },
	{ "DATA/STR/CHOICE/M.txt", "DATA/STR/CHOICE/N.txt" }
};


//エンドフラグ
int EndFlag = 99;

//ゲームメニュー変数
static int GAMEMENU_COUNT;

//既読スキップ変数
SkipData_t TextIgnoredFlag = {};

//バックログ変数
static int BACKLOG_CHOICE = 0;
static int BACKLOG_HANDLE, BACKLOG[11], BACKLOG_BACKGROUND;
static int LOG = 1, BACKLOG_COUNT = 1;
char *BACKLOG_DELETE;

//セーブ用変数
int SAVE, SAVE_CHOICE = 0;
static int SAVESNAP1, SAVESNAP2, SAVESNAP3, SAVETITLE;
static int SAVESNAP_HANDLE1 = 0, SAVESNAP_HANDLE2 = 0, SAVESNAP_HANDLE3 = 0, SAVESNAP_CHOICE = 0;
char *SAVESNAP_CHOICE_DELETE;


//非アクティブ用変数
static char WindowActive = TRUE;

// １文字分一時記憶配列
static char OneMojiBuf[3];

//キャラクター名配列
static char CHARACTER_NAME[10];

//キー操作
int Key[256];
int y = MENUY;
int SAVE_y = SAVE_Y;
int GAME_y = GAMEMENU_y;

//スキップ・オートモード用変数
int skip_auto = 0;

//設定用変数
ConfigData_t ConfigData = {
	/*BGM_VOL               :*/100,
	/*BGM_VOL_COUNT         :*/10,
	/*SE_VOL                :*/100,
	/*SE_VOL_COUNT          :*/10,
	/*SKIP_SPEED            :*/100,
	/*SKIP_SPEED_COUNT      :*/10,
	/*AUTO_SPEED            :*/100,
	/*AUTO_SPEED_COUNT      :*/10,
	/*STRING_SPEED          :*/100,
	/*STRING_SPEED_COUNT    :*/10,
	/*soundnovel_winownovel :*/0,
	/*mouse_key_move        :*/1
};
static int Config = 0;

//スクリーンショット用変数
static int SCREENSHOT_COUNT = 0;

//ショートカットキー用変数
static short SHORTCUT_KEY_FLAG = 0;

//セーブ・ロード関連
//通常セーブデータ
struct alignas(4) SaveData_t {
	std::int32_t ENDFLAG;    //ENDFLAG
	std::int32_t SP;			//行数
	std::int32_t CP;			//文字位置
	std::int32_t CHAR;		//立ち絵情報
	std::int32_t BG;			//背景画像情報
	std::int32_t BGM;		//BGM情報
	std::int32_t SAVE_CHOICE;//選択肢画面でのセーブ情報
};

//クイックセーブデータ
struct alignas(4) QuickSaveData_t {
	std::int32_t ENDFLAG;    //ENDFLAG
	std::int32_t SP;			//行数
	std::int32_t CP;			//文字位置
	std::int32_t CHAR;		//立ち絵情報
	std::int32_t BG;			//背景画像情報
	std::int32_t BGM;		//BGM情報
	std::int32_t SAVE_CHOICE;//選択肢画面でのセーブ情報
};

//コンティニューセーブデータ
struct alignas(4) ContinueSaveData_t {
	std::int32_t ENDFLAG;    //ENDFLAG
	std::int32_t SP;			//行数
	std::int32_t CP;			//文字位置
	std::int32_t CHAR;		//立ち絵情報
	std::int32_t BG;			//背景画像情報
	std::int32_t BGM;		//BGM情報
	std::int32_t SAVE_CHOICE;//選択肢画面でのセーブ情報
};

union SkipDataConv {
	alignas(4) SkipData_t flag;
	alignas(4) std::int32_t arr[15];
};
static_assert(alignof(std::int32_t) == 4, "err");
static_assert(alignof(SkipData_t) == alignof(std::int32_t[15]), "err");
static_assert(sizeof(SkipData_t) == sizeof(std::int32_t[15]), "err");

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

template<typename Func>
static bool SerialNumberFileLoader(int* dest_arr, size_t dest_arr_num, const char* format, Func&& LoadFunc) {
	if (NULL == dest_arr) return false;
	assert(dest_arr_num <= 40);
	for (unsigned int i = 0; i < dest_arr_num; ++i) {
		char FilePathString[40] = {};
#ifdef LINKS_C11_CRT_BOTH_SECURE_FUNCTIONS
		if(-1 == sprintf_s(FilePathString, dest_arr_num, format, i + 1)) return false;
#else
		if(0 > snprintf(FilePathString, dest_arr_num, format, i) return false;
#endif
		dest_arr[i] = LoadFunc(FilePathString);
	}
	return true;
}

//立ち絵素材読込
void MATERIAL_LOAD_CHARACTER() {
	assert(SerialNumberFileLoader(CHARACTER_LOAD, countof(CHARACTER_LOAD), "DATA/CHARACTER/CHAR%02u.png", [](const TCHAR* FileName) {
		return LoadGraph(FileName);
	}));
}

//背景画像読込
void MATERIAL_LOAD_BACKGROUND() {
	assert(SerialNumberFileLoader(BACKGROUND_LOAD, countof(BACKGROUND_LOAD), "DATA/BACKGROUND/BG%02u.png", [](const TCHAR* FileName) {
		return LoadGraph(FileName);
	}));
}

//ＢＧＭ読込
void MATERIAL_LOAD_BACKGROUNDMUSIC() {
	assert(SerialNumberFileLoader(BACKGROUNDMUSIC_LOAD, countof(BACKGROUNDMUSIC_LOAD), "DATA/BACKGROUNDMUSIC/BGM%02u.ogg", [](const TCHAR* FileName) {
		return LoadSoundMem(FileName);
	}));
}

//ＳＥ読込
void MATERIAL_LOAD_SOUNDEFFECT(){
	assert(SerialNumberFileLoader(SOUNDEFFECT_LOAD, countof(SOUNDEFFECT_LOAD), "DATA/SOUNDEFFECT/SE%02u.ogg", [](const TCHAR* FileName) {
		return LoadSoundMem(FileName);
	}));
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
int SCRIPT_TO_ARRAY(int ScriptFile) {

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
		const int ScriptFile = FileRead_open(ScriptFileNames[EndFlag - 1]);
		SCRIPT_TO_ARRAY(ScriptFile);
		FileRead_close(ScriptFile);
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

	if (ConfigData.soundnovel_winownovel == 0) {

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
	if (ConfigData.soundnovel_winownovel == 1) {

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
	if (ConfigData.mouse_key_move == 0) {

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

	if (ConfigData.mouse_key_move == 1) {

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
	fread(&TextIgnoredFlag, sizeof(SkipData_t), 1, fp);
	return 0;
}

//SKIP_READ SAVE関数
int SKIP_READ_SAVE()
{
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
		fwrite(&TextIgnoredFlag, sizeof(SkipData_t), 1, fp); // SkipData_t構造体の中身を出力
		fclose(fp);//ファイルを閉じる

	return 0;

}

//CONFIG_SAVE関数
int CONFIG_SAVE()
{
	//設定データ保存
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
	fwrite(&ConfigData, sizeof(ConfigData_t), 1, fp); // ConfigData_t構造体の中身を出力
	fclose(fp);//ファイルを閉じる

	return 0;
}

//CONFIG_LOAD関数
int CONFIG_LOAD()
{
	//設定データの読み込み
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
	fread(&ConfigData, sizeof(ConfigData_t), 1, fp);
	fclose(fp);//ファイルを閉じる

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

		ConfigData.BGM_VOL += 10;
		ConfigData.BGM_VOL_COUNT += 1;

		if (ConfigData.BGM_VOL_COUNT >= 10) {
			ConfigData.BGM_VOL = 100;
			ConfigData.BGM_VOL_COUNT = 10;
		}
	}

	if (GAME_y == GAMEMENU_y && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);

		ConfigData.BGM_VOL -= 10;
		ConfigData.BGM_VOL_COUNT -= 1;

		if (ConfigData.BGM_VOL_COUNT <= 0) {
			ConfigData.BGM_VOL = 0;
			ConfigData.BGM_VOL_COUNT = 0;
		}
	}

}

//コンフィグ(SE音量調整)
void SE_VOL_CHANGE() {

	//ＳＥ音量調整
	if (GAME_y == GAMEMENU_y * 2 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 2 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);

		ConfigData.SE_VOL += 10;
		ConfigData.SE_VOL_COUNT += 1;

		if (ConfigData.SE_VOL_COUNT >= 10) {
			ConfigData.SE_VOL = 100;
			ConfigData.SE_VOL_COUNT = 10;
		}
	}

	if (GAME_y == GAMEMENU_y * 2 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 2 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);

		ConfigData.SE_VOL -= 10;
		ConfigData.SE_VOL_COUNT -= 1;

		if (ConfigData.SE_VOL_COUNT <= 0) {
			ConfigData.SE_VOL = 0;
			ConfigData.SE_VOL_COUNT = 0;
		}
	}
}

//コンフィグ(オート速度調整)
void AUTO_SPEED_CHANGE() {

	//オート速度調整
	if (GAME_y == GAMEMENU_y * 3 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 3 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);

		ConfigData.AUTO_SPEED += 10;
		ConfigData.AUTO_SPEED_COUNT += 1;

		if (ConfigData.AUTO_SPEED_COUNT >= 10) {
			ConfigData.AUTO_SPEED = 100;
			ConfigData.AUTO_SPEED_COUNT = 10;
		}
	}

	if (GAME_y == GAMEMENU_y * 3 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 3 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);

		ConfigData.AUTO_SPEED -= 10;
		ConfigData.AUTO_SPEED_COUNT -= 1;

		if (ConfigData.AUTO_SPEED_COUNT <= 0) {
			ConfigData.AUTO_SPEED = 0;
			ConfigData.AUTO_SPEED_COUNT = 0;
		}
	}
}

//コンフィグ(スキップ速度調整)
void SKIP_SPEED_CHANGE() {

	//スキップ速度調整
	if (GAME_y == GAMEMENU_y * 4 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 4 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);

		ConfigData.SKIP_SPEED += 10;
		ConfigData.SKIP_SPEED_COUNT += 1;

		if (ConfigData.SKIP_SPEED_COUNT >= 10) {
			ConfigData.SKIP_SPEED = 100;
			ConfigData.SKIP_SPEED_COUNT = 10;
		}
	}

	if (GAME_y == GAMEMENU_y * 4 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 4 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);

		ConfigData.SKIP_SPEED -= 10;
		ConfigData.SKIP_SPEED_COUNT -= 1;

		if (ConfigData.SKIP_SPEED_COUNT <= 0) {
			ConfigData.SKIP_SPEED = 0;
			ConfigData.SKIP_SPEED_COUNT = 0;
		}

	}
}

//コンフィグ(文字描画)
void STRING_SPEED_CHANGE() {

	//文字描画速度調整
	if (GAME_y == GAMEMENU_y * 5 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 5 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);

		ConfigData.STRING_SPEED += 10;
		ConfigData.STRING_SPEED_COUNT += 1;

		if (ConfigData.STRING_SPEED_COUNT >= 10) {
			ConfigData.STRING_SPEED = 100;
			ConfigData.STRING_SPEED_COUNT = 10;
		}
	}

	if (GAME_y == GAMEMENU_y * 5 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 5 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);

		ConfigData.STRING_SPEED -= 10;
		ConfigData.STRING_SPEED_COUNT -= 1;

		if (ConfigData.STRING_SPEED_COUNT <= 0) {
			ConfigData.STRING_SPEED = 0;
			ConfigData.STRING_SPEED_COUNT = 0;
		}
	}
}

//コンフィグ(サウンドノベル風とウインドウ風)
void SOUNDNOVEL_WINDOWNOVEL_CHANGE() {

	//サウンドノベル風とウインドウ風の切り替え
	if (GAME_y == GAMEMENU_y * 6 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 6 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

		WaitTimer(300);
		ConfigData.soundnovel_winownovel = 0;
	}

	if (GAME_y == GAMEMENU_y * 6 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 6 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);
		ConfigData.soundnovel_winownovel = 1;
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

		ConfigData.mouse_key_move = 1;
	}

	//キー操作を有効に
	if (GAME_y == GAMEMENU_y * 8 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 8 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

		WaitTimer(300);

		ConfigData.mouse_key_move = 0;
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
	DrawFormatString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, Cr, "%d", ConfigData.BGM_VOL);

	//SE音量目盛り描画
	DrawFormatString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, Cr, "%d", ConfigData.SE_VOL);

	//オート速度目盛り描画
	DrawFormatString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, Cr, "%d", ConfigData.AUTO_SPEED);

	//スキップ速度目盛り描画
	DrawFormatString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, Cr, "%d", ConfigData.SKIP_SPEED);

	//文字描画速度目盛り描画
	DrawFormatString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, Cr, "%d", ConfigData.STRING_SPEED);

	//サウンドノベル風
	if (ConfigData.soundnovel_winownovel == 0)
		DrawString(SAVE_NAME_X + CURSOR * 6, GAMEMENU_y * 6, "サウンドノベル風", Cr);

	//ウインドウ風
	if (ConfigData.soundnovel_winownovel == 1)
		DrawString(SAVE_NAME_X + CURSOR * 6, GAMEMENU_y * 6, "ウインドウ風", Cr);

	//非アクティブ時の処理
	if (WindowActive == TRUE)
		DrawString(SAVE_NAME_X + CURSOR * 7, GAMEMENU_y * 7, "処理", Cr);

	if (WindowActive == FALSE)
		DrawString(SAVE_NAME_X + CURSOR * 7, GAMEMENU_y * 7, "未処理", Cr);

	//マウス操作
	if (ConfigData.mouse_key_move == 1)
		DrawString(SAVE_NAME_X + CURSOR * 8, GAMEMENU_y * 8, "マウス操作", Cr);

	//キー操作
	if (ConfigData.mouse_key_move == 0)
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

static int LoadSaveData(const char* Message, const char* ErrorMessage, const char* SaveDataPath) {
	SAVE = LINKS_MessageBox_YESNO(Message);
	if (SAVE == IDYES) {
		SaveData_t Data;
		FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
		const errno_t er = fopen_s(&fp, SaveDataPath, "rb");
		if (0 != er) {
			LINKS_MessageBox_OK(ErrorMessage);
			return 0;
		}
#else
		fp = fopen(SaveDataPath, "rb");
		if (fp == NULL) {
			LINKS_MessageBox_OK(ErrorMessage);
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
//セーブデータ1のロード
int SAVEDATA_1_LOAD() {
	return LoadSaveData("セーブデータ1をロードしますか？", "セーブデータ1がありません！", "DATA/SAVE/SAVEDATA1.dat");
}

//セーブデータ2のロード
int SAVEDATA_2_LOAD() {
	return LoadSaveData("セーブデータ2をロードしますか？", "セーブデータ2がありません！", "DATA/SAVE/SAVEDATA2.dat");
}

//セーブデータ3をロード
int SAVEDATA_3_LOAD() {
	return LoadSaveData("セーブデータ3をロードしますか？", "セーブデータ3がありません！", "DATA/SAVE/SAVEDATA3.dat");
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

static void DeleteSaveData(const char* Message, const char* ImagePath, const char* SaveDataPath) {
	SAVE = LINKS_MessageBox_YESNO(Message);

	if (SAVE == IDYES) {
		remove(SaveDataPath);
		remove(ImagePath);
		//削除後のメッセージ
		DELETE_MESSAGE();
		//削除後の処理(サウンドノベル風)
		DELETE_SOUNDNOVEL();
		//削除後の処理(ウインドウ風)
		DELETE_WINDOWNOVEL();
	}
}
//セーブデータ1削除
void SAVEDATA_1_DELETE(){
	DeleteSaveData("セーブデータ1を削除しますか？", "DATA/SAVE/SAVESNAP1.png", "DATA/SAVE/SAVEDATA1.dat");
}

//セーブデータ2削除
void SAVEDATA_2_DELETE() {
	DeleteSaveData("セーブデータ2を削除しますか？", "DATA/SAVE/SAVESNAP2.png", "DATA/SAVE/SAVEDATA2.dat");
}

//セーブデータ3削除
void SAVEDATA_3_DELETE() {
	DeleteSaveData("セーブデータ3を削除しますか？", "DATA/SAVE/SAVESNAP3.png", "DATA/SAVE/SAVEDATA3.dat");
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

	const SkipDataConv* conv = reinterpret_cast<const SkipDataConv*>(&TextIgnoredFlag);
	//既読データ読み込み時の判定
	if (IDYES == SAVE && 0 < EndFlag && EndFlag <= countof(conv->arr) && 1 == conv->arr[EndFlag - 1]) {
		skip_auto = 2;
	}
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
	if (0 < LOG && LOG <= 10) {
		DrawGraph(0, 0, BACKLOG[LOG - 1], TRUE);
		char Message[15] = {};
#ifdef LINKS_C11_CRT_BOTH_SECURE_FUNCTIONS
		sprintf_s(Message, countof(Message), "バックログ%d", LOG);
#else
		snprintf(FilePathString, countof(Message), format, i);
#endif
		DrawString(0, 450, Message, Cr);
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
	for (int i : {0, 1}) {
		DrawString(SENTAKUSIX + CURSOR, SENTAKUSI1, ChoiceStrings[i], Cr);
	}
}

// 改行関数
int Kaigyou(void)
{
	if (ConfigData.soundnovel_winownovel == 0) {

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

	if (ConfigData.soundnovel_winownovel == 1) {

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
	if (ConfigData.soundnovel_winownovel == 0) {
		//背景画像を切り抜き、立ち絵の上にペースト
		CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
		DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);

	}

	//ウインドウ風時の処理
	if (ConfigData.soundnovel_winownovel == 1) {
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
	if (ConfigData.soundnovel_winownovel == 1) {

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
	ChangeVolumeSoundMem(255 * ConfigData.BGM_VOL / 100, BACKGROUNDMUSIC);

	//BGM再生
	PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);

	//文字を進める
	CP++;

}

//スクリプトタグ処理(SE再生)
void SCRIPT_OUTPUT_SOUNDEFFECT() {

	StopSoundMem(SOUNDEFFECT);

	// 音量の設定
	ChangeVolumeSoundMem(255 * ConfigData.SE_VOL / 100, SOUNDEFFECT);

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
		WaitTimer(1800 * ConfigData.AUTO_SPEED / 100);
		CP++;
	}

	//スキップ・オート変数がＯＮの場合(スキップ)
	if (skip_auto == 2) {

		//セーブデータ用スクリーンショット保存
		SAVESNAP();

		CP++;
	}

}

//バックログ取得関数
void BACKLOG_GET() {
	if (0 < BACKLOG_COUNT) {
		const int BacklogCount = (10 < BACKLOG_COUNT) ? 10 : BACKLOG_COUNT;
		if (1 < BacklogCount) {
			BACKLOG_BACKGROUND = BACKLOG[1];
			for (int i = BacklogCount - 1; 1 < i; --i) {
				BACKLOG[i] = DerivationGraph(0, 0, 640, 480, BACKLOG[i - 1]);
			}
			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");
			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");
		}
		else {
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");
		}
		BACKLOG_HANDLE = BACKLOG[0] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");
	}
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

	if (ConfigData.soundnovel_winownovel == 1) {

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

	if (ConfigData.soundnovel_winownovel == 0 && SAVE_CHOICE == 1) {

		DrawGraph(0, 0, BACKGROUND, TRUE);

		DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
	}
}

//選択肢ループ用描画処理(ウインドウ風)
void SCRIPT_OUTPUT_CHOICE_LOOP_WINDOWNOVEL() {

	if (ConfigData.soundnovel_winownovel == 1 && SAVE_CHOICE == 1) {

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
	if (1 <= EndFlag && EndFlag <= 7) {
		for (int i : {0, 1}) {
			Choices[i] = FileRead_open(ChoiceFiles[EndFlag - 1][i]);
			FileRead_gets(ChoiceStrings[i], RETU, Choices[i]);
		}
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
	if (1 <= EndFlag && EndFlag <= 7) {
		SAVE_CHOICE = 0;
		SAVESNAP_CHOICE = 0;
		EndFlag *= 2;
	}
}

//選択後の分岐処理(選択肢↓)
void SCRIPT_OUTPUT_CHOICE_BRANCH_DOWN() {
	if (1 <= EndFlag && EndFlag <= 7) {
		SAVE_CHOICE = 0;
		SAVESNAP_CHOICE = 0;
		EndFlag = EndFlag * 2 + 1;
	}
}

//選択肢時のバックログ取得(選択肢の読み込み)
void SCRIPT_OUTPUT_CHOICE_BACKLOG_CHOICE_READ() {
	if (2 <= EndFlag && EndFlag <= 15) {
		const int index = EndFlag / 2;
		for (int i : {0, 1}) {
			Choices[i] = FileRead_open(ChoiceFiles[index][i]);
			FileRead_gets(ChoiceStrings[i], RETU, Choices[i]);
		}
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
	SkipDataConv* conv = reinterpret_cast<SkipDataConv*>(&TextIgnoredFlag);
	if (1 <= EndFlag && EndFlag <= countof(conv->arr)) {
		conv->arr[EndFlag] = 1;
	}
	SKIP_READ_SAVE();
	// 終了フラグを立てるおよび参照文字位置を一つ進める
	EndFlag = 99999;
	CP++;
}

//立ち絵クリア処理
void SCRIPT_OUTPUT_CHARACTER_REMOVE() {

	//サウンドノベル風時の処理
	if (ConfigData.soundnovel_winownovel == 0) {
		CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
		DrawGraph(CHARACTERX, CHARACTERY, CHARACTER_DUMMY, TRUE);
		CP++;
	}

	//ウインドウ風時の処理
	if (ConfigData.soundnovel_winownovel == 1) {
		CHARACTER_DUMMY = DerivationGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_GRAPH_X, CHARACTER_GRAPH_Y, BACKGROUND);
		DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER_DUMMY, TRUE);
		CP++;
	}
}

//キャラクター名描画処理
void SCRIPT_OUTPUT_CHARACTER_NAME() {

	//サウンドノベル風時の処理
	if (ConfigData.soundnovel_winownovel == 0) {
		SP++;
		CP++;
	}

	//ウインドウ風時の処理
	if (ConfigData.soundnovel_winownovel == 1) {

		//キャラクター名を読み込む
		static_assert(10 <= countof(CHARACTER_NAME) && 9 <= countof(String[0]), "array length must be over 10");
		assert(countof(String[SP]) < CP + 10);
		memcpy(CHARACTER_NAME, &String[SP][CP + 1], 9);
		CHARACTER_NAME[9] = '\0';

		//キャラクター名の背景
		const int Window_Color = GetColor(0, 0, 0);
		DrawBox(30, 360, 150, 385, Window_Color, TRUE);

		// １文字描画
		DrawString(30, 360, CHARACTER_NAME, GetColor(255, 255, 255));

		SP++;
		CP++;
	}
}

//文字列の描画
void SCRIPT_OUTPUT_STRING_DRAW() {
	//TODO: https://github.com/S-H-GAMELINKS/Novel.Game.Engine.LINKS/issues/3
	// １文字分抜き出す
	OneMojiBuf[0] = String[SP][CP];
	OneMojiBuf[1] = String[SP][CP + 1];
	OneMojiBuf[2] = '\0';

	if (ConfigData.soundnovel_winownovel == 1 && DrawPointY <= 399)
		DrawPointY = 400;

	if (ConfigData.soundnovel_winownovel == 0) {
		// １文字描画
		DrawString(DrawPointX * MOJI_SIZE, DrawPointY * MOJI_SIZE, OneMojiBuf, GetColor(255, 255, 255));
	}

	if (ConfigData.soundnovel_winownovel == 1) {
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
		WaitTimer(30 * ConfigData.STRING_SPEED / 100);
	}

	//スキップ・オート変数がＯＮの場合(オートモード)
	if (skip_auto == 1) {
		// 少し待つ
		WaitTimer(30 * ConfigData.AUTO_SPEED / 100);
	}

	//スキップ・オート変数がＯＮの場合（スキップ）
	if (skip_auto == 2) {
		//速く処理
		WaitTimer(10 * ConfigData.SKIP_SPEED / 100);
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
	if (ConfigData.soundnovel_winownovel == 0) {

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
	if (ConfigData.soundnovel_winownovel == 1) {

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

			if (ConfigData.soundnovel_winownovel == 1) {

				int	Window_Color = GetColor(0, 0, 0);

				DrawBox(0, 400, 640, 480, Window_Color, TRUE);
			}

			if (CHARACTER != 0)
				DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
		}
	}
}
static bool isdigit(char c) { return '0' <= c && c <= '9'; }
static unsigned int ctoui(char c) { return c - '0'; }
static bool SelectLoadedResource(int& out, const int* LoadedArray, size_t LoadedArrayNum, char c0, char c1) {
	if (NULL == LoadedArray) return false;
	if (isdigit(c0) && isdigit(c1)) {
		const size_t CharactorNumber = (ctoui(c0) * 10) + ctoui(c1) - 1;
		if (LoadedArrayNum <= CharactorNumber) return false;
		out = LoadedArray[CharactorNumber];
		return true;
	}
	return false;
}
//キャラクター描画処理
void CHARACTER_DRAW() {
	if (SelectLoadedResource(CHARACTER, CHARACTER_LOAD, countof(CHARACTER_LOAD), String[SP][CP], String[SP][CP + 1])) {
		CP += 2;
	}
}

//背景描画処理
void BACKGROUND_DRAW() {
	if (SelectLoadedResource(BACKGROUND, BACKGROUND_LOAD, countof(BACKGROUND_LOAD), String[SP][CP], String[SP][CP + 1])) {
		CP += 2;
	}
}

//BGM再生処理
void BACKGROUNDMUSIC_START() {
	if (SelectLoadedResource(BACKGROUNDMUSIC, BACKGROUNDMUSIC_LOAD, countof(BACKGROUNDMUSIC_LOAD), String[SP][CP], String[SP][CP + 1])) {
		CP += 2;
	}
}

//SE再生処理
void SOUNDEFFECT_START() {
	if (SelectLoadedResource(SOUNDEFFECT, SOUNDEFFECT_LOAD, countof(SOUNDEFFECT_LOAD), String[SP][CP], String[SP][CP + 1])) {
		CP += 2;
	}
}

//動画再生処理
void MOVIE_START() {
	if (isdigit(String[SP][CP]) && isdigit(String[SP][CP + 1])) {
		const size_t CharactorNumber = (ctoui(String[SP][CP]) * 10) + ctoui(String[SP][CP + 1]) - 1;
		char MovieFilePath[25] = {};
#ifdef LINKS_C11_CRT_BOTH_SECURE_FUNCTIONS
		if (-1 == sprintf_s(MovieFilePath, countof(MovieFilePath), "DATA/MOVIE/MOVIE%c%c.wmv", String[SP][CP], String[SP][CP + 1])) return;
#else
		if (0 > snprintf(MovieFilePath, countof(MovieFilePath), format, i) return;
#endif
		PlayMovie(MovieFilePath, 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP += 2;
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
	for (int i : {0, 1}) {
		FileRead_close(Choices[i]);
	}
	return 0;
}

//スクリーンショット機能
int SCREENSHOT() {
	if (1 != CheckHitKey(KEY_INPUT_F12)) return 0;

	if (SCREENSHOT_COUNT < 1 || 9 < SCREENSHOT_COUNT) {
		LINKS_MessageBox_OK("これ以上スクリーンショットを取得できません");
	}
	else {
		static const char* const ScreenShotFileNames[] = {
			"DATA/SCREENSHOT/SCREENSHOT01.png",
			"DATA/SCREENSHOT/SCREENSHOT02.png",
			"DATA/SCREENSHOT/SCREENSHOT03.png",
			"DATA/SCREENSHOT/SCREENSHOT04.png",
			"DATA/SCREENSHOT/SCREENSHOT05.png",
			"DATA/SCREENSHOT/SCREENSHOT06.png",
			"DATA/SCREENSHOT/SCREENSHOT07.png",
			"DATA/SCREENSHOT/SCREENSHOT08.png",
			"DATA/SCREENSHOT/SCREENSHOT09.png",
			"DATA/SCREENSHOT/SCREENSHOT10.png",
		};
		static const char* const ScreenShotMessages[] = {
			"スクリーンショット０１を取得しました！",
			"スクリーンショット０２を取得しました！",
			"スクリーンショット０３を取得しました！",
			"スクリーンショット０４を取得しました！",
			"スクリーンショット０５を取得しました！",
			"スクリーンショット０６を取得しました！",
			"スクリーンショット０７を取得しました！",
			"スクリーンショット０８を取得しました！",
			"スクリーンショット０９を取得しました！",
			"スクリーンショット１０を取得しました！",
		};
		static_assert(countof(ScreenShotFileNames) == countof(ScreenShotMessages), "invalid array size.");
		SaveDrawScreenToPNG(0, 0, 640, 480, ScreenShotFileNames[SCREENSHOT_COUNT], 0);
		LINKS_MessageBox_OK(ScreenShotMessages[SCREENSHOT_COUNT]);
		++SCREENSHOT_COUNT;
	}
	WaitTimer(300);
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
