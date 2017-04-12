//ライブラリとヘッダの読み込み
#include "DxLib.h"
#include "DEF.h"

// 文字列描画の位置
int DrawPointX = 0, DrawPointY = 0;

// 参照する文字列番号と文字列中の文字ポインタ
int SP = 0, CP = 0;

//キャラクター画像読込変数
int CHARACTER_LOAD[12], CHARACTER, CHARACTER_DUMMY;

//背景画像読込変数
int BACKGROUND_LOAD[12], BACKGROUND;

//背景音楽読込変数
int BACKGROUNDMUSIC_LOAD[12], BACKGROUNDMUSIC;

//効果音変数
int SOUNDEFFECT_LOAD[12], SOUNDEFFECT;

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

//各素材データ読込関数
void MATERIAL_LOAD() {

	//サウンドデータの読み込み形式
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);

	//キャラクター画像読込
	CHARACTER_LOAD[0] = LoadGraph("DATA/CHARACTER/CHAR01.png");
	CHARACTER_LOAD[1] = LoadGraph("DATA/CHARACTER/CHAR02.png");
	CHARACTER_LOAD[2] = LoadGraph("DATA/CHARACTER/CHAR03.png");
	CHARACTER_LOAD[3] = LoadGraph("DATA/CHARACTER/CHAR04.png");
	CHARACTER_LOAD[4] = LoadGraph("DATA/CHARACTER/CHAR05.png");
	CHARACTER_LOAD[5] = LoadGraph("DATA/CHARACTER/CHAR06.png");
	CHARACTER_LOAD[6] = LoadGraph("DATA/CHARACTER/CHAR07.png");
	CHARACTER_LOAD[7] = LoadGraph("DATA/CHARACTER/CHAR08.png");
	CHARACTER_LOAD[8] = LoadGraph("DATA/CHARACTER/CHAR09.png");
	CHARACTER_LOAD[9] = LoadGraph("DATA/CHARACTER/CHAR10.png");
	CHARACTER_LOAD[10] = LoadGraph("DATA/CHARACTER/CHAR11.png");
	CHARACTER_LOAD[11] = LoadGraph("DATA/CHARACTER/CHAR12.png");

	//背景画像読込
	BACKGROUND_LOAD[0] = LoadGraph("DATA/BACKGROUND/BG01.png");
	BACKGROUND_LOAD[1] = LoadGraph("DATA/BACKGROUND/BG02.png");
	BACKGROUND_LOAD[2] = LoadGraph("DATA/BACKGROUND/BG03.png");
	BACKGROUND_LOAD[3] = LoadGraph("DATA/BACKGROUND/BG04.png");
	BACKGROUND_LOAD[4] = LoadGraph("DATA/BACKGROUND/BG05.png");
	BACKGROUND_LOAD[5] = LoadGraph("DATA/BACKGROUND/BG06.png");
	BACKGROUND_LOAD[6] = LoadGraph("DATA/BACKGROUND/BG07.png");
	BACKGROUND_LOAD[7] = LoadGraph("DATA/BACKGROUND/BG08.png");
	BACKGROUND_LOAD[8] = LoadGraph("DATA/BACKGROUND/BG09.png");
	BACKGROUND_LOAD[9] = LoadGraph("DATA/BACKGROUND/BG10.png");
	BACKGROUND_LOAD[10] = LoadGraph("DATA/BACKGROUND/BG11.png");
	BACKGROUND_LOAD[11] = LoadGraph("DATA/BACKGROUND/BG12.png");

	//ＢＧＭ読込
	BACKGROUNDMUSIC_LOAD[0] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM01.ogg");
	BACKGROUNDMUSIC_LOAD[1] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM02.ogg");
	BACKGROUNDMUSIC_LOAD[2] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM03.ogg");
	BACKGROUNDMUSIC_LOAD[3] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM04.ogg");
	BACKGROUNDMUSIC_LOAD[4] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM05.ogg");
	BACKGROUNDMUSIC_LOAD[5] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM06.ogg");
	BACKGROUNDMUSIC_LOAD[6] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM07.ogg");
	BACKGROUNDMUSIC_LOAD[7] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM08.ogg");
	BACKGROUNDMUSIC_LOAD[8] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM09.ogg");
	BACKGROUNDMUSIC_LOAD[9] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM10.ogg");
	BACKGROUNDMUSIC_LOAD[10] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM11.ogg");
	BACKGROUNDMUSIC_LOAD[11] = LoadSoundMem("DATA/BACKGROUNDMUSIC/BGM12.ogg");

	//ＳＥ読込
	SOUNDEFFECT_LOAD[0] = LoadSoundMem("DATA/SOUNDEFFECT/SE01.ogg");
	SOUNDEFFECT_LOAD[1] = LoadSoundMem("DATA/SOUNDEFFECT/SE02.ogg");
	SOUNDEFFECT_LOAD[2] = LoadSoundMem("DATA/SOUNDEFFECT/SE03.ogg");
	SOUNDEFFECT_LOAD[3] = LoadSoundMem("DATA/SOUNDEFFECT/SE04.ogg");
	SOUNDEFFECT_LOAD[4] = LoadSoundMem("DATA/SOUNDEFFECT/SE05.ogg");
	SOUNDEFFECT_LOAD[5] = LoadSoundMem("DATA/SOUNDEFFECT/SE06.ogg");
	SOUNDEFFECT_LOAD[6] = LoadSoundMem("DATA/SOUNDEFFECT/SE07.ogg");
	SOUNDEFFECT_LOAD[7] = LoadSoundMem("DATA/SOUNDEFFECT/SE08.ogg");
	SOUNDEFFECT_LOAD[8] = LoadSoundMem("DATA/SOUNDEFFECT/SE09.ogg");
	SOUNDEFFECT_LOAD[9] = LoadSoundMem("DATA/SOUNDEFFECT/SE10.ogg");
	SOUNDEFFECT_LOAD[10] = LoadSoundMem("DATA/SOUNDEFFECT/SE11.ogg");
	SOUNDEFFECT_LOAD[11] = LoadSoundMem("DATA/SOUNDEFFECT/SE12.ogg");

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

	switch (EndFlag) {

		//メインルート
	case 1:

		// メインスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/LINKS.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//	//Aルート
	case 2:

		//Aルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/A.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Bルート
	case 3:

		//Ｂルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/B.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Cルート
	case 4:

		//Cルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/C.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Dルート
	case 5:

		//Dルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/D.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Eルート
	case 6:

		//Eルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/E.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Fルート
	case 7:

		//Fルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/F.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Gルート
	case 8:

		//Gルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/G.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Hルート
	case 9:

		//Hルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/H.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Iルート
	case 10:

		//Iルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/I.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Jルート
	case 11:

		//Jルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/J.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Kルート
	case 12:

		//Kルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/K.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Lルート
	case 13:

		//Lルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/L.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Mルート
	case 14:

		//Mルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/M.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;

		//Nルート
	case 15:

		//Nルートのスクリプトファイルを開く
		ScriptFile = FileRead_open("DATA/STR/N.txt");

		//スクリプトファイルを配列に流しこみ
		SCRIPT_TO_ARRAY();
		break;
	}

	return 0;
}

//各処理後のゲーム画面の描画(サウンドノベル風)
void SOUNDNOVEL() {

	if (soundnovel_winownovel == 0) {

		ClearDrawScreen();

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
	}
}

//各処理後のゲーム画面の描画(ウインドウ風)
void WINDOWNOVEL() {

	//ウインドウ風描画時の処理
	if (soundnovel_winownovel == 1) {

		ClearDrawScreen();

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

			if (GetHitKeyStateAll_Key[i] == 1) KeyStateBuf[i]++;
			else                            KeyStateBuf[i] = 0;
		}
	}
	return 0;
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

			if (MouseY <= 359)
				y = 330;

			if (MouseY >= 360 && MouseY <= 389)
				y = 360;

			if (MouseY >= 390 && MouseY <= 419)
				y = 390;

			if (MouseY >= 420 && MouseY <= 449)
				y = 420;

			if (MouseY >= 450)
				y = 450;
		}
}

//マウス操作(ゲームメニュー)
void Mouse_Move_GAME(int MouseY) {
	
	//ゲームメニュー
	if (EndFlag == 99 || EndFlag != 99 && GAMEMENU_COUNT == 0 && Config == 0) {

		if (MouseY <= 59)
			GAME_y = 30;

		if (MouseY >= 60 && MouseY <= 89)
			GAME_y = 60;

		if (MouseY >= 90 && MouseY <= 119)
			GAME_y = 90;

		if (MouseY >= 120 && MouseY <= 149)
			GAME_y = 120;

		if (MouseY >= 150 && MouseY <= 179)
			GAME_y = 150;

		if (MouseY >= 180 && MouseY <= 209)
			GAME_y = 180;

		if (MouseY >= 210 && MouseY <= 239)
			GAME_y = 210;

		if (MouseY >= 240 && MouseY <= 269)
			GAME_y = 240;

		if (MouseY >= 270 && MouseY <= 299)
			GAME_y = 270;

		if (MouseY >= 300 && MouseY <= 329)
			GAME_y = 300;

		if (MouseY >= 330 && MouseY <= 359)
			GAME_y = 330;

		if (MouseY >= 360)
			GAME_y = 360;
	}
}

//マウス操作(セーブ画面関連)
void Mouse_Move_SAVE(int MouseY) {

	if (GAMEMENU_COUNT == 0 && EndFlag != 99 || EndFlag == 99) {

		if (MouseY <= 199)
			SAVE_y = 100;

		if (MouseY >= 200 && MouseY <= 299)
			SAVE_y = 200;

		if (MouseY >= 300 && MouseY <= 399)
			SAVE_y = 300;

		if (MouseY >= 400)
			SAVE_y = 400;
	}
}

//マウス操作(選択肢画面)
void Mouse_Move_CHOICE(int MouseY) {

	//選択肢画面
	if (EndFlag == 1 || EndFlag == 2 || EndFlag == 3 || EndFlag == 4 || EndFlag == 5 || EndFlag == 6 || EndFlag == 7) {

		if (MouseY <= 229)
			y = 200;

		if (MouseY >= 230)
			y = 230;
	}

}

//マウス操作(コンフィグ)
void Mouse_Move_CONFIG(int MouseY) {

	//コンフィグ画面
	if (Config == 1) {

		if (MouseY <= 59)
			GAME_y = 30;

		if (MouseY >= 60 && MouseY <= 89)
			GAME_y = 60;

		if (MouseY >= 90 && MouseY <= 119)
			GAME_y = 90;

		if (MouseY >= 120 && MouseY <= 149)
			GAME_y = 120;

		if (MouseY >= 150 && MouseY <= 179)
			GAME_y = 150;

		if (MouseY >= 180 && MouseY <= 209)
			GAME_y = 180;

		if (MouseY >= 210 && MouseY <= 239)
			GAME_y = 210;

		if (MouseY >= 240 && MouseY <= 269)
			GAME_y = 240;

		if (MouseY >= 270)
			GAME_y = 270;
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

//画面クリア処理関数
void SCREEN_CLEAR() {

	//画面処理
	SetDrawScreen(DX_SCREEN_BACK);

	ClearDrawScreen();

	SetDrawScreen(DX_SCREEN_FRONT);
}

//SKIP_READ LOAD関数
int SKIP_READ_LOAD()
{
	//既読データを読み込んで、各変数に代入
	SkipData_t Data;
#pragma warning(disable:4996);
	FILE *fp = fopen("DATA/SAVE/SKIP_READ.dat", "rb");
	if (fp == NULL) {
		return 0;
	}
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
}

//SKIP_READ SAVE関数
int SKIP_READ_SAVE()
{
		//既読スキップデータ保存
#pragma warning(disable:4996);
		SkipData_t Data = { LINKS, A, B, C, D, E, F, G, H, I, J, K, L, M, N };
		FILE *fp = fopen("DATA/SAVE/SKIP_READ.dat", "wb");//バイナリファイルを開く
		if (fp == NULL) {//エラーが起きたらNULLを返す
			return 0;
		}
		fwrite(&Data, sizeof(Data), 1, fp); // SkipData_t構造体の中身を出力
		fclose(fp);//ファイルを閉じる

	return 0;

}

//CONFIG_SAVE関数
int CONFIG_SAVE()
{
	//設定データ保存
	#pragma warning(disable:4996);
	ConfigData_t Data = { BGM_VOL, BGM_VOL_COUNT, SE_VOL, SE_VOL_COUNT, SKIP_SPEED, SKIP_SPEED_COUNT, AUTO_SPEED, AUTO_SPEED_COUNT, STRING_SPEED, STRING_SPEED_COUNT, soundnovel_winownovel, mouse_key_move };
	FILE *fp = fopen("DATA/SAVE/Config.dat", "wb");//バイナリファイルを開く
	if (fp == NULL) {//エラーが起きたらNULLを返す
		return 0;
	}
	fwrite(&Data, sizeof(Data), 1, fp); // ConfigData_t構造体の中身を出力
	fclose(fp);//ファイルを閉じる

	return 0;
}

//CONFIG_LOAD関数
int CONFIG_LOAD()
{
	//設定データの読み込み
	ConfigData_t Data;
	#pragma warning(disable:4996);
	FILE *fp = fopen("DATA/SAVE/Config.dat", "rb");
	if (fp == NULL) {
		return 0;
	}
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

//クイックセーブ
int QUICKSAVE_SAVE(){

	//クイックセーブデータの作成 
#pragma warning(disable:4996);
	QuickSaveData_t Data = { EndFlag, SP, 0, CHARACTER, BACKGROUND, BACKGROUNDMUSIC, SAVE_CHOICE };
	FILE *fp = fopen("DATA/SAVE/QUICKSAVEDATA.dat", "wb");//バイナリファイルを開く
	if (fp == NULL) {//エラーが起きたらNULLを返す
		return 0;
	}
	fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t構造体の中身を出力
	fclose(fp);//ファイルを閉じる

	return 0;
}

//クイックセーブデータ又はセーブデータ読み込み時の文字位置処理
void SAVEDATA_LOAD_STRING_POINT() {

	SP = SP + 1;
	CP = 0;
}

//クイックロード時のメッセージ
void QUICKSAVE_LOAD_MESSAGE() {
	SAVE = MessageBox(
		NULL,
		"クイックロードを実行しますか？",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);
}

//クイックロード
int QUICKSAVE_LOAD() {

	//クイックロード時のメッセージ
	QUICKSAVE_LOAD_MESSAGE();

	if (SAVE == IDYES) {

		//クイックセーブデータの読み込み
		QuickSaveData_t Data;
#pragma warning(disable:4996);
		FILE *fp = fopen("DATA/SAVE/QUICKSAVEDATA.dat", "rb");
		if (fp == NULL) {
			return 0;
		}
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

		//クイックセーブデータ又はセーブデータ読み込み時の文字位置処理
		SAVEDATA_LOAD_STRING_POINT();

		MessageBox(
			NULL,
			"ロードしました！",
			"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
			MB_OK
		);

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

	if (EndFlag != 99)
		DrawString(SAVE_NAME_X, GAMEMENU_y * 9, "メニューに戻る", Cr);

	if (EndFlag == 99)
		DrawString(SAVE_NAME_X, GAMEMENU_y * 9, "タイトルに戻る", Cr);

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

		//タイトルに戻る
		if (EndFlag == 99) {
			SAVE = MessageBox(
				NULL,
				"タイトルに戻りますか？",
				"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
				MB_YESNO
			);
		}

		//ゲームメニューに戻る
		if (EndFlag != 99) {
			SAVE = MessageBox(
				NULL,
				"メニューに戻りますか？",
				"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
				MB_YESNO
			);
		}

		if (SAVE == IDYES) {
			WaitTimer(300);
			ClearDrawScreen();
			GAME_y = GAMEMENU_y;
			Config = 0;
		}
	}
}

//コンフィグ
void CONFIG() {

	SAVE = MessageBox(
		NULL,
		"設定を変更しますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

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

	if (EndFlag == 99)
		DrawString(SAVE_NAME_X - CURSOR, SAVE_Y * 4, "タイトルに戻る", Cr);

	if (EndFlag != 99)
		DrawString(SAVE_NAME_X - CURSOR, SAVE_Y * 4, "メニューに戻る", Cr);
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

	SAVE = MessageBox(
		NULL,
		"セーブ画面に移行しますか？",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);
}

//セーブ後のメッセージ
void SAVE_MESSAGE() {

	MessageBox(
		NULL,
		"セーブしました！",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_OK
	);
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

//セーブデータ１にセーブ
int SAVEDATA_1_SAVE() {

	SAVE = MessageBox(
		NULL,
		"セーブデータ1にセーブしますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

	if (SAVE == IDYES) {

		//セーブデータ１用のスクリーンショット取得変数
		SAVESNAP_HANDLE1 = 1;

		//選択肢画面でのセーブ処理
		if (SAVESNAP_CHOICE != 0) {

			SetDrawScreen(DX_SCREEN_BACK);

			DrawGraph(0, 0, SAVESNAP_CHOICE, TRUE);

			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP1.png", 0);

			SAVESNAP_CHOICE = 0;

			SAVESNAP_HANDLE1 = 0;

			SetDrawScreen(DX_SCREEN_FRONT);

		}

		//セーブデータの作成 
#pragma warning(disable:4996);
		SaveData_t Data = { EndFlag, SP, 0, CHARACTER, BACKGROUND, BACKGROUNDMUSIC, SAVE_CHOICE };
		FILE *fp = fopen("DATA/SAVE/SAVEDATA1.dat", "wb");//バイナリファイルを開く
		if (fp == NULL) {//エラーが起きたらNULLを返す
			return 0;
		}
		fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t構造体の中身を出力
		fclose(fp);//ファイルを閉じる

		//セーブ後のメッセージ
		SAVE_MESSAGE();

		//サウンドノベル風描画時の処理
		SAVE_SOUNDNOVEL();

		//ウインドウ風描画時の処理
		SAVE_WINDOWNOVEL();
	}

	return 0;
}

//セーブデータ2にセーブ
int SAVEDATA_2_SAVE() {

	SAVE = MessageBox(
		NULL,
		"セーブデータ2にセーブしますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

	if (SAVE == IDYES) {

		SAVESNAP_HANDLE2 = 1;

		//選択肢画面でのセーブ処理
		if (SAVESNAP_CHOICE != 0) {

			SetDrawScreen(DX_SCREEN_BACK);

			DrawGraph(0, 0, SAVESNAP_CHOICE, TRUE);

			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP2.png", 0);

			SAVESNAP_CHOICE = 0;

			SAVESNAP_HANDLE3 = 0;

			SetDrawScreen(DX_SCREEN_FRONT);

		}

		//セーブデータの作成 
#pragma warning(disable:4996);
		SaveData_t Data = { EndFlag, SP, 0, CHARACTER, BACKGROUND, BACKGROUNDMUSIC, SAVE_CHOICE };
		FILE *fp = fopen("DATA/SAVE/SAVEDATA2.dat", "wb");//バイナリファイルを開く
		if (fp == NULL) {//エラーが起きたらNULLを返す
			return 0;
		}
		fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t構造体の中身を出力
		fclose(fp);//ファイルを閉じる

	   //セーブ後のメッセージ
		SAVE_MESSAGE();

		//サウンドノベル風描画時の処理
		SAVE_SOUNDNOVEL();

		//ウインドウ風描画時の処理
		SAVE_WINDOWNOVEL();
	}

	return 0;
}

//セーブデータ3にセーブ
int SAVEDATA_3_SAVE() {

	SAVE = MessageBox(
		NULL,
		"セーブデータ3にセーブしますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

	if (SAVE == IDYES) {

		SAVESNAP_HANDLE3 = 1;

		//選択肢画面でのセーブ処理
		if (SAVESNAP_CHOICE != 0) {

			SetDrawScreen(DX_SCREEN_BACK);

			DrawGraph(0, 0, SAVESNAP_CHOICE, TRUE);

			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP3.png", 0);

			SAVESNAP_CHOICE = 0;

			SAVESNAP_HANDLE3 = 0;

			SetDrawScreen(DX_SCREEN_FRONT);

		}

		//セーブデータの作成 
#pragma warning(disable:4996);
		SaveData_t Data = { EndFlag, SP, 0, CHARACTER, BACKGROUND, BACKGROUNDMUSIC, SAVE_CHOICE };
		FILE *fp = fopen("DATA/SAVE/SAVEDATA3.dat", "wb");//バイナリファイルを開く
		if (fp == NULL) {//エラーが起きたらNULLを返す
			return 0;
		}
		fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t構造体の中身を出力
		fclose(fp);//ファイルを閉じる

	   //セーブ後のメッセージ
		SAVE_MESSAGE();

		//サウンドノベル風描画時の処理
		SAVE_SOUNDNOVEL();

		//ウインドウ風描画時の処理
		SAVE_WINDOWNOVEL();
	}

	return 0;
}

//セーブデータ・セーブ画面ループ
void SAVEDATA_SAVE_LOOP() {

	//セーブデータ・セーブ画面ループ
	while (ProcessMessage() == 0 && MoveKey(Key) == 0) {

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
				break;
			}

			//セーブデータ２にセーブ
			if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				//セーブデータ２にセーブ
				SAVEDATA_2_SAVE();
				break;
			}

			//セーブデータ３にセーブ
			if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				//セーブデータ３にセーブ
				SAVEDATA_3_SAVE();
				break;
			}

			//メニュー画面に戻る
			if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				SAVE = MessageBox(
					NULL,
					"メニューに戻りますか？",
					"ノベルゲームエンジン「LINKS」",
					MB_YESNO
				);

				if (SAVE == IDYES) {

					ClearDrawScreen();
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

	SAVE = MessageBox(
		NULL,
		"ロード画面に移行しますか？",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);
}

//ロード後のメッセージ
void LOAD_MESSAGE() {

	MessageBox(
		NULL,
		"ロードしました！",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_OK
	);
}

//ロード後の処理(サウンドノベル風)
void LOAD_SOUNDNOVEL() {

	//サウンドノベル風描画時の処理
	SOUNDNOVEL();

	GAMEMENU_COUNT = 1;

	//クイックセーブデータ又はセーブデータ読み込み時の文字位置処理
	SAVEDATA_LOAD_STRING_POINT();
}

//ロード後の処理(ウインドウ風)
void LOAD_WINDOWNOVEL() {

	//ウインドウ風描画時の処理
	WINDOWNOVEL();

	GAMEMENU_COUNT = 1;

	//クイックセーブデータ又はセーブデータ読み込み時の文字位置処理
	SAVEDATA_LOAD_STRING_POINT();
}

//セーブデータ1のロード
int SAVEDATA_1_LOAD() {

	SAVE = MessageBox(
		NULL,
		"セーブデータ1をロードしますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

	if (SAVE == IDYES) {
		SaveData_t Data;
#pragma warning(disable:4996);
		FILE *fp = fopen("DATA/SAVE/SAVEDATA1.dat", "rb");
		if (fp == NULL) {

			MessageBox(
				NULL,
				"セーブデータ1がありません！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			return 0;
		}
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

	SAVE = MessageBox(
		NULL,
		"セーブデータ2をロードしますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

	if (SAVE == IDYES) {
		SaveData_t Data;
#pragma warning(disable:4996);
		FILE *fp = fopen("DATA/SAVE/SAVEDATA2.dat", "rb");
		if (fp == NULL) {

			MessageBox(
				NULL,
				"セーブデータ2がありません！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			return 0;
		}
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

	SAVE = MessageBox(
		NULL,
		"セーブデータ3をロードしますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

	if (SAVE == IDYES) {
		SaveData_t Data;
#pragma warning(disable:4996);
		FILE *fp = fopen("DATA/SAVE/SAVEDATA3.dat", "rb");
		if (fp == NULL) {

			MessageBox(
				NULL,
				"セーブデータ3がありません！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			return 0;
		}
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
}

//セーブデータ・ロード画面ループ
void SAVEDATA_LOAD_LOOP() {

	while (ProcessMessage() == 0 && MoveKey(Key) == 0) {

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
				break;
			}

			//セーブデータ２のロード
			if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				//セーブデータ2をロード
				SAVEDATA_2_LOAD();
				break;
			}

			//セーブデータ３のロード
			if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				//セーブデータ2をロード
				SAVEDATA_3_LOAD();
				break;
			}

			//タイトルに戻る
			if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				if (EndFlag == 99) {
					SAVE = MessageBox(
						NULL,
						"タイトルに戻りますか？",
						"ノベルゲームエンジン「LINKS」",
						MB_YESNO
					);

					if (SAVE == IDYES)
						break;
				}

				if (EndFlag != 99) {
					SAVE = MessageBox(
						NULL,
						"メニューに戻りますか？",
						"ノベルゲームエンジン「LINKS」",
						MB_YESNO
					);

					if (SAVE == IDYES)
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

	SAVE = MessageBox(
		NULL,
		"セーブデータ削除画面に移行しますか？",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);
}

//削除後のメッセージ
void DELETE_MESSAGE() {

	MessageBox(
		NULL,
		"削除しました！",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_OK
	);
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

	SAVE = MessageBox(
		NULL,
		"セーブデータ1を削除しますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

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

	SAVE = MessageBox(
		NULL,
		"セーブデータ2を削除しますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

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

	SAVE = MessageBox(
		NULL,
		"セーブデータ3を削除しますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

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

	while (ProcessMessage() == 0 && MoveKey(Key) == 0) {

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
			break;
		}

		if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

			//セーブデータ2削除処理
			SAVEDATA_2_DELETE();
			break;
		}

		if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

			//セーブデータ3削除処理
			SAVEDATA_3_DELETE();
			break;
		}

		if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

			SAVE = MessageBox(
				NULL,
				"メニューに戻りますか？",
				"ノベルゲームエンジン「LINKS」",
				MB_YESNO
			);

			if (SAVE == IDYES) {
				ClearDrawScreen();
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

	SAVE = MessageBox(
		NULL,
		"既読スキップを実行しますか？",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);
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

	if (SAVE == IDYES) {

		//既読スキップ後の処理(サウンドノベル風)
		SKIP_READ_SOUNDNOVEL();

		//既読スキップ後の処理(ウインドウ風)
		SKIP_READ_WINDOWNOVEL();
	}
}

//スキップ処理
void SKIP_START() {

	SAVE = MessageBox(
		NULL,
		"スキップを実行しますか？",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

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

	SAVE = MessageBox(
		NULL,
		"オートモードを実行しますか？",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);
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

	SAVE = MessageBox(
		NULL,
		"スキップ又はオートモードを終了しますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);
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

	SAVE = MessageBox(
		NULL,
		"バックログ画面に移行しますか？",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);
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

				break;
			}
		}
	}
}

//タイトルに戻る
void GAMEMENU_TITLE_BACK() {

	SAVE = MessageBox(
		NULL,
		"タイトル画面に戻りますか？",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

	if (SAVE == IDYES) {

		ClearDrawScreen();

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

	SAVE = MessageBox(
		NULL,
		"ゲームに戻りますか？",
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

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

	SAVE = MessageBox(
		NULL,
		"終了しますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);

	if (SAVE == IDYES) {

		//クイックセーブ
		QUICKSAVE_SAVE();

		EndFlag = 99999;

		GAMEMENU_COUNT = 1;
	}
}

//終了ウインドウ
int GAME_FINISH() {

	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {

		SAVE = MessageBox(
			NULL,
			"終了しますか？",
			"ノベルゲームエンジン「LINKS」",
			MB_YESNO
		);

		if (SAVE == IDYES) {
			QUICKSAVE_SAVE();
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

	if (soundnovel_winownovel == 0) {

		DrawGraph(0, 0, BACKGROUND, TRUE);

		DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
	}
}

//選択肢ループ湯描画処理(ウインドウ風)
void SCRIPT_OUTPUT_CHOICE_LOOP_WINDOWNOVEL() {

	if (soundnovel_winownovel == 1) {

		int	Window_Color = GetColor(0, 0, 0);

		DrawGraph(0, 0, BACKGROUND, TRUE);

		DrawBox(0, 400, 640, 480, Window_Color, TRUE);

		DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
	}
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

//選択肢ループ
void SCRIPT_OUTPUT_CHOICE_LOOP() {

	while (ProcessMessage() == 0 && MoveKey(Key) == 0 && EndFlag != 99 && EndFlag != 99999 && SAVE_CHOICE != 0) {

		//選択肢ループ用描画処理(サウンドノベル風)
		SCRIPT_OUTPUT_CHOICE_LOOP_SOUNDNOVEL();

		//選択肢ループ用描画処理(ウインドウノベル風)
		SCRIPT_OUTPUT_CHOICE_LOOP_WINDOWNOVEL();
		
		//選択肢ファイルの読み込み(描画用
		SCRIPT_OUTPUT_CHOICE_READ();

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

	// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
	ClearDrawScreen();
	DrawPointY = 0;
	DrawPointX = 0;
	CHARACTER = 0;
	BACKGROUND = 0;
	CP++;

	SetDrawScreen(DX_SCREEN_FRONT);
}

//スクリプトタグ処理(選択肢処理)
void SCRIPT_OUTPUT_CHOICE() {

	y = SENTAKUSIY;

	if (EndFlag == 1 || EndFlag == 2 || EndFlag == 3 || EndFlag == 4 || EndFlag == 5 || EndFlag == 6 || EndFlag == 7) {

		SAVE_CHOICE = 1;
		SAVESNAP_CHOICE = 1;

		BACKLOG_COUNT++;

		//選択肢ループ
		SCRIPT_OUTPUT_CHOICE_LOOP();

		//選択肢時のバックログ取得
		SCRIPT_OUTPUT_CHOICE_BACKLOG();
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
	if (soundnovel_winownovel == 0 && DrawPointY * MOJI_SIZE + MOJI_SIZE > CHARACTERY + MOJI_SIZE) {

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

//ウインドウ風時の改ページ処理
void SCRIPT_OUTPUT_STRING_PAGE_CLEAR_WINODWNOVEL() {

	//ウインドウ風時の改ページ処理
	if (soundnovel_winownovel == 1 && DrawPointY > 480) {

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

//スクリプトタグ処理(メイン)関数
int SCRIPT_OUTPUT() {

	char  Moji;

	// 文字の描画
	Moji = String[SP][CP];

	switch (Moji)
	{
		// 改行文字
	case '0':

		// 改行処理および参照文字位置を一つ進める
		Kaigyou();
		CP++;
		break;

		// ボタン押し待ち文字
	case '1':

		//クリック待ち処理
		SCRIPT_UTPUT_KEYWAIT();
		break;

		// クリア文字
	case '2':

		//ゲーム画面のクリア処理
		SCRIPT_OUTPUT_SCREENCLEAR();
		break;

		//少し待つ
	case '3':

		//スクリプトタグ処理(少し待つ)
		SCRIPT_OUTPUT_WAIT();
		break;

		//ゲームオーバー
	case '4':

		//ゲームオーバー画面処理
		SCRIPT_OUTPUT_GAMEOVER();
		break;

		//エンディング
	case '5':

		//エンディング再生
		SCRIPT_OUTPUT_ENDING();
		break;

		//BGMの再生を止める
	case '6':

		//BGMの再生を止める
		SCRIPT_OUTPUT_BGMSTOP();
		break;

		//SEの再生を止める
	case '7':

		//SEの再生を止める
		SCRIPT_OUTPUT_SESTOP();
		break;

		//選択肢の表示
	case '8':

		//選択肢描画処理
		SCRIPT_OUTPUT_CHOICE();
		break;

		// 終了文字
	case '9':

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

		//キャラ01読込（画面に出力）
	case 'A':

		//キャラ01読込
		CHARACTER = CHARACTER_LOAD[0];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//キャラ02読込（画面に出力）
	case 'B':

		//キャラ02読込
		CHARACTER = CHARACTER_LOAD[1];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//キャラ03読込（画面に出力）
	case 'C':

		//キャラ03読込
		CHARACTER = CHARACTER_LOAD[2];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//キャラ04読込（画面に出力）
	case 'D':

		//キャラ04読込
		CHARACTER = CHARACTER_LOAD[3];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//キャラ05読込（画面に出力）
	case 'E':

		//キャラ05読込
		CHARACTER = CHARACTER_LOAD[4];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//キャラ06読込（画面に出力）
	case 'F':

		//キャラ06読込
		CHARACTER = CHARACTER_LOAD[5];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//キャラ07読込（画面に出力）
	case 'G':

		//キャラ07読込
		CHARACTER = CHARACTER_LOAD[6];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//キャラ08読込（画面に出力）
	case 'H':

		//キャラ08読込
		CHARACTER = CHARACTER_LOAD[7];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//キャラ09読込（画面に出力）
	case 'I':

		//キャラ09読込
		CHARACTER = CHARACTER_LOAD[8];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//キャラ10読込（画面に出力）
	case 'J':

		//キャラ10読込
		CHARACTER = CHARACTER_LOAD[9];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//キャラ11読込（画面に出力）
	case 'K':

		//キャラ11読込
		CHARACTER = CHARACTER_LOAD[10];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//キャラ12読込（画面に出力）
	case 'L':

		//キャラ02読込
		CHARACTER = CHARACTER_LOAD[11];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//背景01読込（画面に出力）
	case 'M':

		//背景01読込
		BACKGROUND = BACKGROUND_LOAD[0];

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//背景02読込（画面に出力）
	case 'N':

		//背景02読込
		BACKGROUND = BACKGROUND_LOAD[1];

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//背景03読込（画面に出力）
	case 'O':

		//背景03読込
		BACKGROUND = BACKGROUND_LOAD[2];

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//背景04読込（画面に出力）
	case 'P':

		//背景04読込
		BACKGROUND = BACKGROUND_LOAD[3];

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//背景05読込（画面に出力）
	case 'Q':

		//背景05読込
		BACKGROUND = BACKGROUND_LOAD[4];

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//背景06読込（画面に出力）
	case 'R':

		//背景06読込
		BACKGROUND = BACKGROUND_LOAD[5];

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//背景07読込（画面に出力）
	case 'S':

		//背景07読込
		BACKGROUND = BACKGROUND_LOAD[6];

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//背景08読込（画面に出力）
	case 'T':

		//背景08読込
		BACKGROUND = BACKGROUND_LOAD[7];

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//背景09読込（画面に出力）
	case 'U':

		//背景09読込
		BACKGROUND = BACKGROUND_LOAD[8];

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//背景10読込（画面に出力）
	case 'V':

		//背景10読込
		BACKGROUND = BACKGROUND_LOAD[9];

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//背景11読込（画面に出力）
	case 'W':

		//背景11読込
		BACKGROUND = BACKGROUND_LOAD[10];

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//背景12読込（画面に出力）
	case 'X':

		//背景12読込
		BACKGROUND = BACKGROUND_LOAD[11];

		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//BGM01再生文字
	case 'Y':

		//以前のBGMの再生停止
		StopSoundMem(BACKGROUNDMUSIC);

		//BGM01読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[0];

		//BGM再生
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//BGM02再生文字
	case 'Z':

		//以前のBGMの再生停止
		StopSoundMem(BACKGROUNDMUSIC);

		//BGM02読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[1];

		//BGM再生
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//BGM03再生文字
	case 'a':

		//以前のBGMの再生停止
		StopSoundMem(BACKGROUNDMUSIC);

		//BGM03読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[2];

		//BGM再生
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//BGM04再生文字
	case 'b':

		//以前のBGMの再生停止
		StopSoundMem(BACKGROUNDMUSIC);

		//BGM04読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[3];

		//BGM再生
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//BGM05再生文字
	case 'c':

		//以前のBGMの再生停止
		StopSoundMem(BACKGROUNDMUSIC);

		//BGM05読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[4];

		//BGM再生
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//BGM06再生文字
	case 'd':

		//以前のBGMの再生停止
		StopSoundMem(BACKGROUNDMUSIC);

		//BGM06読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[5];

		//BGM再生
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//BGM07再生文字
	case 'e':

		//以前のBGMの再生停止
		StopSoundMem(BACKGROUNDMUSIC);

		//BGM07読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[6];

		//BGM再生
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//BGM08再生文字
	case 'f':

		//以前のBGMの再生停止
		StopSoundMem(BACKGROUNDMUSIC);

		//BGM09読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[7];

		//BGM再生
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//BGM09再生文字
	case 'g':

		//以前のBGMの再生停止
		StopSoundMem(BACKGROUNDMUSIC);

		//BGM09読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[8];

		//BGM再生
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//BGM10再生文字
	case 'h':

		//以前のBGMの再生停止
		StopSoundMem(BACKGROUNDMUSIC);

		//BGM10読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[9];

		//BGM再生
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//BGM11再生文字
	case 'i':

		//以前のBGMの再生停止
		StopSoundMem(BACKGROUNDMUSIC);

		//BGM11読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[10];

		//BGM再生
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//BGM12再生文字
	case 'j':

		//以前のBGMの再生停止
		StopSoundMem(BACKGROUNDMUSIC);

		//BGM12読込
		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[11];

		//BGM再生
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//SE01再生文字
	case 'k':

		//以前のSEが再生されていれば停止
		StopSoundMem(SOUNDEFFECT);

		//SE01読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[0];

		//SE再生
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//SE02再生文字
	case 'l':

		//以前のSEが再生されていれば停止
		StopSoundMem(SOUNDEFFECT);

		//SE02読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[1];

		//SE再生
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//SE03再生文字
	case 'm':

		//以前のSEが再生されていれば停止
		StopSoundMem(SOUNDEFFECT);

		//SE03読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[2];

		//SE再生
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//SE04再生文字
	case 'n':

		//以前のSEが再生されていれば停止
		StopSoundMem(SOUNDEFFECT);

		//SE04読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[3];

		//SE再生
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//SE05再生文字
	case 'o':

		//以前のSEが再生されていれば停止
		StopSoundMem(SOUNDEFFECT);

		//SE05読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[4];

		//SE再生
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//SE06再生文字
	case 'p':

		//以前のSEが再生されていれば停止
		StopSoundMem(SOUNDEFFECT);

		//SE06読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[5];

		//SE再生
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//SE07再生文字
	case 'q':

		//以前のSEが再生されていれば停止
		StopSoundMem(SOUNDEFFECT);

		//SE07読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[6];

		//SE再生
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//SE08再生文字
	case 'r':

		//以前のSEが再生されていれば停止
		StopSoundMem(SOUNDEFFECT);

		//SE08読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[7];

		//SE再生
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//SE09再生文字
	case 's':

		//以前のSEが再生されていれば停止
		StopSoundMem(SOUNDEFFECT);

		//SE09読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[8];

		//SE再生
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//SE10再生文字
	case 't':

		//以前のSEが再生されていれば停止
		StopSoundMem(SOUNDEFFECT);

		//SE10読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[9];

		//SE再生
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//SE11再生文字
	case 'u':

		//以前のSEが再生されていれば停止
		StopSoundMem(SOUNDEFFECT);

		//SE11読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[10];

		//SE再生
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//SE12再生文字
	case 'v':

		//以前のSEが再生されていれば停止
		StopSoundMem(SOUNDEFFECT);

		//SE12読込
		SOUNDEFFECT = SOUNDEFFECT_LOAD[11];

		//SE再生
		SCRIPT_OUTPUT_SOUNDEFFECT();
		break;

		//動画01再生（画面に動画を再生）
	case 'w':

		//動画01再生
		PlayMovie("DATA/MOVIE/MOVIE01.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

		//動画02再生（画面に動画を再生）
	case 'x':

		//動画02再生
		PlayMovie("DATA/MOVIE/MOVIE02.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

		//動画01再生（画面に動画を再生）
	case 'y':

		//動画01再生
		PlayMovie("DATA/MOVIE/MOVIE03.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
		CP++;
		break;

		//動画02再生（画面に動画を再生）
	case 'z':

		//動画02再生
		PlayMovie("DATA/MOVIE/MOVIE04.wmv", 1, DX_MOVIEPLAYTYPE_BCANCEL);
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

		MessageBox(
			NULL,
			"スクリーンショット０１を取得しました！",
			"ノベルゲームエンジン「LINKS」",
			MB_OK
		);

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット02取得機能
void SCREENSHOT_02() {

	//スクリーンショット０２取得
	if (SCREENSHOT_COUNT == 1 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT02.png", 0);

		MessageBox(
			NULL,
			"スクリーンショット０２を取得しました！",
			"ノベルゲームエンジン「LINKS」",
			MB_OK
		);

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット03取得機能
void SCREENSHOT_03() {

	//スクリーンショット０３取得
	if (SCREENSHOT_COUNT == 2 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT03.png", 0);

		MessageBox(
			NULL,
			"スクリーンショット０３を取得しました！",
			"ノベルゲームエンジン「LINKS」",
			MB_OK
		);

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット04取得機能
void SCREENSHOT_04() {

	//スクリーンショット０４取得
	if (SCREENSHOT_COUNT == 3 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT04.png", 0);

		MessageBox(
			NULL,
			"スクリーンショット０４を取得しました！",
			"ノベルゲームエンジン「LINKS」",
			MB_OK
		);

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット05取得機能
void SCREENSHOT_05() {

	//スクリーンショット０５取得
	if (SCREENSHOT_COUNT == 4 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT05.png", 0);

		MessageBox(
			NULL,
			"スクリーンショット０５を取得しました！",
			"ノベルゲームエンジン「LINKS」",
			MB_OK
		);

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット06取得機能
void SCREENSHOT_06() {

	//スクリーンショット０６取得
	if (SCREENSHOT_COUNT == 5 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT06.png", 0);

		MessageBox(
			NULL,
			"スクリーンショット０６を取得しました！",
			"ノベルゲームエンジン「LINKS」",
			MB_OK
		);

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット07取得機能
void SCREENSHOT_07() {

	//スクリーンショット０７取得
	if (SCREENSHOT_COUNT == 6 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT07.png", 0);

		MessageBox(
			NULL,
			"スクリーンショット０７を取得しました！",
			"ノベルゲームエンジン「LINKS」",
			MB_OK
		);

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット08取得機能
void SCREENSHOT_08() {

	//スクリーンショット０８取得
	if (SCREENSHOT_COUNT == 7 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT08.png", 0);

		MessageBox(
			NULL,
			"スクリーンショット０８を取得しました！",
			"ノベルゲームエンジン「LINKS」",
			MB_OK
		);

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット09取得機能
void SCREENSHOT_09() {

	//スクリーンショット０９取得
	if (SCREENSHOT_COUNT == 8 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT09.png", 0);

		MessageBox(
			NULL,
			"スクリーンショット０９を取得しました！",
			"ノベルゲームエンジン「LINKS」",
			MB_OK
		);

		//スクリーンショット取得後の処理
		SCREEN_SHOT_COUNT();
	}
}

//スクリーンショット10取得機能
void SCREENSHOT_10() {

	//スクリーンショット１０取得
	if (SCREENSHOT_COUNT == 9 && CheckHitKey(KEY_INPUT_F12) == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT10.png", 0);

		MessageBox(
			NULL,
			"スクリーンショット１０を取得しました！",
			"ノベルゲームエンジン「LINKS」",
			MB_OK
		);

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
			
		MessageBox(
			NULL,
			"これ以上スクリーンショットを取得できません",
			"ノベルゲームエンジン「LINKS」",
			MB_OK
		);

		WaitTimer(300);
	}

	return 0;		
}

//各種F1～F11キー選択時の処理
void SHORTCUT_KEY_DRAW() {

	//サウンドノベル風時の処理
	SOUNDNOVEL();

	//ウインドウ風時の処理
	WINDOWNOVEL();
}

//各種F1～F11キー
void SHORTCUT_KEY() {

	//セーブ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F1) == 1)
		SAVEDATA_SAVE();

	//ロード
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F2) == 1)
		SAVEDATA_LOAD();

	//セーブデータ削除
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F3) == 1)
		SAVEDATA_DELETE();

	//既読スキップ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F4) == 1)
		SKIP_READ_LOAD();

	//スキップ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F5) == 1)
		SKIP_START();
	
	//オート
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F6) == 1)
		AUTO_START();

	//スキップ&オート停止
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F7) == 1)
		AUTO_SKIP_STOP();

	//バックログ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F8) == 1)
		BACKLOG_DRAW();

	//設定
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F9) == 1)
		CONFIG();

	//タイトルへ戻る
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F10) == 1)
		GAMEMENU_TITLE_BACK();
}
