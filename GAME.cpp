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
int SaveFlag = 0;
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
}ConfigData_t;

//各素材データ読込関数
int MATERIAL_LOAD() {

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

	return 0;
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

//矢印キー操作関数
int MoveKey(int KeyStateBuf[]) {

	//キー入力用変数
	char GetHitKeyStateAll_Key[256];
	
	//キーの情報を変数へ
	GetHitKeyStateAll(GetHitKeyStateAll_Key);
	
	//キー入力の状況
	for (int i = 0; i<256; i++) {
	
		if (GetHitKeyStateAll_Key[i] == 1) KeyStateBuf[i]++;
		else                            KeyStateBuf[i] = 0;
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
	DrawString(SAVE_X, SAVE_y, "■", Cr);
}

//ゲームメニューカーソル関数
void GAME_MENU_CURSOR(int Cr, int GAME_y) {
	DrawString(SAVE_X - (CURSOR * 6), GAME_y, "■", Cr);
}

//マウス操作
int Mouse_Move() {

	//マウスの位置情報変数
	int MouseX, MouseY;

	//マウスの位置を取得
	GetMousePoint(&MouseX, &MouseY);

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

	//ゲームメニュー
	if (EndFlag != 99 && GAMEMENU_COUNT == 0 && Config == 0) {

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
	
	//セーブ画面
	if (EndFlag != 99 && GAMEMENU_COUNT == 0 && SaveFlag != 0) {

		if (MouseY <= 199)
			SAVE_y = 100;

		if (MouseY >= 200 && MouseY <= 299)
			SAVE_y = 200;

		if (MouseY >= 300 && MouseY <= 399)
			SAVE_y = 300;

		if (MouseY >= 400)
			SAVE_y = 400;

	}

	//セーブ画面(タイトルメニュー)
	if (EndFlag == 99 && SaveFlag != 0) {

		if (MouseY <= 199)
			SAVE_y = 100;

		if (MouseY >= 200 && MouseY <= 299)
			SAVE_y = 200;

		if (MouseY >= 300 && MouseY <= 399)
			SAVE_y = 300;

		if (MouseY >= 400)
			SAVE_y = 400;

	}

	//選択肢画面
	if (EndFlag == 1 || EndFlag == 2 || EndFlag == 3 || EndFlag == 4 || EndFlag == 5 || EndFlag == 6 || EndFlag == 7) {

			if (MouseY <= 229)
				y = 200;

			if (MouseY >= 230)
				y = 230;
	}

	//コンフィグ画面(ゲームメニュー)
	if (EndFlag != 99 && GAMEMENU_COUNT == 0 && Config == 1) {

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

		if (MouseY >= 240)
			GAME_y = 240;
	}

	//コンフィグ画面(タイトルメニュー)
	if (EndFlag == 99 && Config == 1) {

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

		if (MouseY >= 240)
			GAME_y = 240;
	}

	return 0;

}

//セーブデータロード関数(タイトルメニュー)
int SAVEDATA_LOAD() {

	//セーブデータ・ロード画面
	if (SaveFlag == 2) {

		WaitTimer(600);

		//セーブ時のスクリーンショット読込
		SAVESNAP1 = LoadGraph("DATA/SAVE/SAVESNAP1.png");
		SAVESNAP2 = LoadGraph("DATA/SAVE/SAVESNAP2.png");
		SAVESNAP3 = LoadGraph("DATA/SAVE/SAVESNAP3.png");
		SAVETITLE = LoadGraph("DATA/BACKGROUND/SAVE.png");

		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && SaveFlag == 2) {

			//背景描画
			DrawGraph(0, 0, SAVETITLE, TRUE);

			//カーソル
			SAVE_LOAD_MENU(Cr, SAVE_y);

			//スクリーンショット描画
			DrawRotaGraph(SAVE_SNAP_X, SAVE_Y, 0.2f, 0, SAVESNAP1, TRUE);
			DrawRotaGraph(SAVE_SNAP_X, SAVE_Y + SAVE_Y, 0.2f, 0, SAVESNAP2, TRUE);
			DrawRotaGraph(SAVE_SNAP_X, SAVE_Y + SAVE_Y + SAVE_Y, 0.2f, 0, SAVESNAP3, TRUE);

			//セーブデータ名描画
			DrawString(SAVE_NAME_X, SAVE_Y, "セーブデータ1", Cr);
			DrawString(SAVE_NAME_X, SAVE_Y + SAVE_Y, "セーブデータ2", Cr);
			DrawString(SAVE_NAME_X, SAVE_Y + SAVE_Y + SAVE_Y, "セーブデータ3", Cr);
			DrawString(SAVE_NAME_X - CURSOR, SAVE_Y + SAVE_Y + SAVE_Y + SAVE_Y, "タイトルへ戻る", Cr);

			//マウス操作
			Mouse_Move();

			//キー操作関連
			SetDrawScreen(DX_SCREEN_BACK);

			ClearDrawScreen();

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

			SetDrawScreen(DX_SCREEN_FRONT);

			//セーブデータ１のロード
			if (SAVE_y == SAVE_Y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == SAVE_Y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

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

					//サウンドノベル風描画の処理
					if (soundnovel_winownovel == 0) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						MessageBox(
							NULL,
							"ロードしました！",
							"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
							MB_OK
						);

						WaitTimer(300);

					}

					//ウインドウ風描画時の処理
					if (soundnovel_winownovel == 1) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						MessageBox(
							NULL,
							"ロードしました！",
							"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
							MB_OK
						);

						WaitTimer(300);

					}

					fclose(fp);
					break;
				}
			}

			//セーブデータ２のロード
			if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

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

					//サウンドノベル風描画の処理
					if (soundnovel_winownovel == 0) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						MessageBox(
							NULL,
							"ロードしました！",
							"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
							MB_OK
						);

						WaitTimer(300);

					}

					//ウインドウ風描画時の処理
					if (soundnovel_winownovel == 1) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						MessageBox(
							NULL,
							"ロードしました！",
							"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
							MB_OK
						);

						WaitTimer(300);

					}

					fclose(fp);
					break;
				}
			}

			//セーブデータ３のロード
			if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

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

					//サウンドノベル風描画の処理
					if (soundnovel_winownovel == 0) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						MessageBox(
							NULL,
							"ロードしました！",
							"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
							MB_OK
						);

						WaitTimer(300);

					}

					//ウインドウ風描画時の処理
					if (soundnovel_winownovel == 1) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						MessageBox(
							NULL,
							"ロードしました！",
							"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
							MB_OK
						);

						WaitTimer(300);

					}

					fclose(fp);
					break;
				}
			}

			//タイトルに戻る
			if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
				
				SAVE = MessageBox(
					NULL,
					"タイトルに戻りますか？",
					"ノベルゲームエンジン「LINKS」",
					MB_YESNO
					);

				if (SAVE == IDYES) {
					EndFlag = 99;
					SaveFlag = 0;
					WaitTimer(600);
					break;
				}
			}

		}
	}

	return 0;
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
	ConfigData_t Data = { BGM_VOL, BGM_VOL_COUNT, SE_VOL, SE_VOL_COUNT, SKIP_SPEED, SKIP_SPEED_COUNT, AUTO_SPEED, AUTO_SPEED_COUNT, STRING_SPEED, STRING_SPEED_COUNT, soundnovel_winownovel };
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

//クイックロード
int QUICKSAVE_LOAD() {

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

	//サウンドノベル風描画の処理
	if (soundnovel_winownovel == 0) {

		ClearDrawScreen();
		GAMEMENU_COUNT = 1;

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

			// 音量の設定
			ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

		MessageBox(
			NULL,
			"ロードしました！",
			"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
			MB_OK
		);

		WaitTimer(300);
	}

	//ウインドウ風描画時の処理
	if (soundnovel_winownovel == 1) {

		ClearDrawScreen();
		GAMEMENU_COUNT = 1;

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

			// 音量の設定
			ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

		MessageBox(
			NULL,
			"ロードしました！",
			"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
			MB_OK
		);

		WaitTimer(300);
	}

	fclose(fp);

	return 0;

}

//セーブ・ロード・スキップ・オート他 ゲームメニュー
int GAMEMENU() {

	//ゲームメニューを開く
	if (CheckHitKey(KEY_INPUT_BACK) == 1 || (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {

		GAMEMENU_COUNT = 0;
		ClearDrawScreen();
		StopSoundMem(BACKGROUNDMUSIC);
		GAME_y = GAMEMENU_y;

		WaitTimer(300);

		//ゲームメニューループ
		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && GAMEMENU_COUNT == 0) {

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

			//キー操作関連
			SetDrawScreen(DX_SCREEN_BACK);

			ClearDrawScreen();

			//カーソル描画
			GAME_MENU_CURSOR(Cr, GAME_y);

			//マウス操作
			Mouse_Move();

			if (Key[KEY_INPUT_DOWN] == 1) {
				ClearDrawScreen();
				GAME_y += GAMEMENU_y;
				if (GAME_y == (GAMEMENU_y * 13))
					GAME_y = GAMEMENU_y;
			}

			if (Key[KEY_INPUT_UP] == 1) {
				ClearDrawScreen();
				GAME_y -= GAMEMENU_y;
				if (GAME_y == (GAMEMENU_y - GAMEMENU_y))
					GAME_y = (GAMEMENU_y * 12);
			}

			SetDrawScreen(DX_SCREEN_FRONT);

			//セーブ
			if (GAME_y == GAMEMENU_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == GAMEMENU_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"セーブ画面に移行しますか？",
					"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
					MB_YESNO
					);

				if (SAVE == IDYES) {
					ClearDrawScreen();
					SaveFlag = 1;
					SAVE_y = SAVE_Y;
				}

				WaitTimer(300);

				//セーブデータ・セーブ画面
				if (SaveFlag == 1) {

					//セーブ時のスクリーンショット読込
					SAVESNAP1 = LoadGraph("DATA/SAVE/SAVESNAP1.png");
					SAVESNAP2 = LoadGraph("DATA/SAVE/SAVESNAP2.png");
					SAVESNAP3 = LoadGraph("DATA/SAVE/SAVESNAP3.png");
					SAVETITLE = LoadGraph("DATA/BACKGROUND/SAVE.png");

					WaitTimer(600);

					//セーブ画面ループ
					while (ProcessMessage() == 0 && MoveKey(Key) == 0) {

						//背景描画
						DrawGraph(0, 0, SAVETITLE, TRUE);

						//カーソル描画
						SAVE_LOAD_MENU(Cr, SAVE_y);

						//スクリーンショット描画
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y, 0.2f, 0, SAVESNAP1, TRUE);
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 2, 0.2f, 0, SAVESNAP2, TRUE);
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 3, 0.2f, 0, SAVESNAP3, TRUE);

						//セーブデータ名描画
						DrawString(SAVE_NAME_X, SAVE_Y, "セーブデータ1", Cr);
						DrawString(SAVE_NAME_X, SAVE_Y * 2, "セーブデータ2", Cr);
						DrawString(SAVE_NAME_X, SAVE_Y * 3, "セーブデータ3", Cr);
						DrawString(SAVE_NAME_X - CURSOR, SAVE_Y * 4, "メニューに戻る", Cr);

						//キー操作関連
						SetDrawScreen(DX_SCREEN_BACK);

						ClearDrawScreen();

						//マウス操作
						Mouse_Move();

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

						SetDrawScreen(DX_SCREEN_FRONT);

						//セーブデータ１にセーブ
						if (SAVE_y == SAVE_Y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == SAVE_Y && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

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

								MessageBox(
									NULL,
									"セーブしました！",
									"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
									MB_OK
									);

								//サウンドノベル風描画時の処理
								if (soundnovel_winownovel == 0) {

									SaveFlag = 0;
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

									SAVE_CHOICE = 0;

									GAMEMENU_COUNT = 1;

									break;
								}

								//ウインドウ風描画時の処理
								if (soundnovel_winownovel == 1) {

									SaveFlag = 0;
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

									SAVE_CHOICE = 0;

									GAMEMENU_COUNT = 1;

									break;
								}

							}

							WaitTimer(300);
						}

						//セーブデータ２にセーブ
						if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

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

								MessageBox(
									NULL,
									"セーブしました！",
									"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
									MB_OK
									);

								//サウンドノベル風描画時の処理
								if (soundnovel_winownovel == 0) {

									SaveFlag = 0;
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

									SAVE_CHOICE = 0;

									GAMEMENU_COUNT = 1;

									break;
								}

								//ウインドウ風描画時の処理
								if (soundnovel_winownovel == 1) {

									SaveFlag = 0;
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

									SAVE_CHOICE = 0;

									GAMEMENU_COUNT = 1;

									break;
								}
							}

							WaitTimer(300);
						}

						//セーブデータ３にセーブ
						if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

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

								MessageBox(
									NULL,
									"セーブしました！",
									"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
									MB_OK
									);

								//サウンドノベル風描画時の処理
								if (soundnovel_winownovel == 0) {

									SaveFlag = 0;
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

									SAVE_CHOICE = 0;

									GAMEMENU_COUNT = 1;

									break;
								}

								//ウインドウ風描画時の処理
								if (soundnovel_winownovel == 1) {

									SaveFlag = 0;
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

									SAVE_CHOICE = 0;

									GAMEMENU_COUNT = 1;

									break;
								}


							}

							WaitTimer(300);
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
								WaitTimer(300);

								break;
							}

							WaitTimer(300);
						}
					}

					WaitTimer(1800);
				}
			}

			//ロード
			if (GAME_y == (GAMEMENU_y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 2) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {


				SAVE = MessageBox(
					NULL,
					"ロード画面に移行しますか？",
					"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					ClearDrawScreen();
					SaveFlag = 4;
					WaitTimer(600);

					SAVE_y = SAVE_Y;

					//セーブ時のスクリーンショット読込
					SAVESNAP1 = LoadGraph("DATA/SAVE/SAVESNAP1.png");
					SAVESNAP2 = LoadGraph("DATA/SAVE/SAVESNAP2.png");
					SAVESNAP3 = LoadGraph("DATA/SAVE/SAVESNAP3.png");
					SAVETITLE = LoadGraph("DATA/BACKGROUND/SAVE.png");

					//ロード画面のループ
					while (ProcessMessage() == 0 && MoveKey(Key) == 0) {

						//背景描画
						DrawGraph(0, 0, SAVETITLE, TRUE);

						//カーソル描画
						SAVE_LOAD_MENU(Cr, SAVE_y);

						//スクリーンショット描画
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y, 0.2f, 0, SAVESNAP1, TRUE);
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 2, 0.2f, 0, SAVESNAP2, TRUE);
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 3, 0.2f, 0, SAVESNAP3, TRUE);

						//セーブデータ名描画
						DrawString(SAVE_NAME_X, SAVE_Y, "セーブデータ1", Cr);
						DrawString(SAVE_NAME_X, SAVE_Y * 2, "セーブデータ2", Cr);
						DrawString(SAVE_NAME_X, SAVE_Y * 3, "セーブデータ3", Cr);
						DrawString(SAVE_NAME_X - CURSOR, SAVE_Y * 4, "メニューに戻る", Cr);

						//キー操作関連
						SetDrawScreen(DX_SCREEN_BACK);

						ClearDrawScreen();

						//マウス操作
						Mouse_Move();

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
								SAVE_y = SAVE_Y_MAX + SAVE_Y;
						}

						SetDrawScreen(DX_SCREEN_FRONT);

						//セーブデータ１のロード
						if (SAVE_y == SAVE_Y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == SAVE_Y && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"セーブデータ1をロードしますか？",
								"ノベルゲームエンジン「LINKS」",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								ClearDrawScreen();

								GAMEMENU_COUNT = 1;

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
								}
								fread(&Data, sizeof(Data), 1, fp);
								EndFlag = Data.ENDFLAG;
								SP = Data.SP;
								CP = Data.CP;
								CHARACTER = Data.CHAR;
								BACKGROUND = Data.BG;
								BACKGROUNDMUSIC = Data.BGM;
								SAVE_CHOICE = Data.SAVE_CHOICE;

								//サウンドノベル風描画の処理
								if (soundnovel_winownovel == 0) {

									ClearDrawScreen();
									GAMEMENU_COUNT = 1;

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

										// 音量の設定
										ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

									MessageBox(
										NULL,
										"ロードしました！",
										"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
										MB_OK
									);

									WaitTimer(300);
								}

								//ウインドウ風描画時の処理
								if (soundnovel_winownovel == 1) {

									ClearDrawScreen();
									GAMEMENU_COUNT = 1;

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

										// 音量の設定
										ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

									MessageBox(
										NULL,
										"ロードしました！",
										"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
										MB_OK
									);


									WaitTimer(300);
								}

								break;
							}

							WaitTimer(300);
						}

						if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"セーブデータ2をロードしますか？",
								"ノベルゲームエンジン「LINKS」",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								ClearDrawScreen();

								GAMEMENU_COUNT = 1;

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
								}
								fread(&Data, sizeof(Data), 1, fp);
								EndFlag = Data.ENDFLAG;
								SP = Data.SP;
								CP = Data.CP;
								CHARACTER = Data.CHAR;
								BACKGROUND = Data.BG;
								BACKGROUNDMUSIC = Data.BGM;
								SAVE_CHOICE = Data.SAVE_CHOICE;

								//サウンドノベル風描画の処理
								if (soundnovel_winownovel == 0) {

									ClearDrawScreen();
									GAMEMENU_COUNT = 1;

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

										// 音量の設定
										ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

									MessageBox(
										NULL,
										"ロードしました！",
										"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
										MB_OK
									);

									WaitTimer(300);
								}

								//ウインドウ風描画時の処理
								if (soundnovel_winownovel == 1) {

									ClearDrawScreen();
									GAMEMENU_COUNT = 1;

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

										// 音量の設定
										ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

									MessageBox(
										NULL,
										"ロードしました！",
										"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
										MB_OK
									);

									WaitTimer(300);
								}

								break;

							}

							WaitTimer(300);
						}

						//セーブデータ３のロード
						if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"セーブデータ3をロードしますか？",
								"ノベルゲームエンジン「LINKS」",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								ClearDrawScreen();

								GAMEMENU_COUNT = 1;

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
								}
								fread(&Data, sizeof(Data), 1, fp);
								EndFlag = Data.ENDFLAG;
								SP = Data.SP;
								CP = Data.CP;
								CHARACTER = Data.CHAR;
								BACKGROUND = Data.BG;
								BACKGROUNDMUSIC = Data.BGM;
								SAVE_CHOICE = Data.SAVE_CHOICE;

								//サウンドノベル風描画の処理
								if (soundnovel_winownovel == 0) {

									ClearDrawScreen();
									GAMEMENU_COUNT = 1;

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

										// 音量の設定
										ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

									MessageBox(
										NULL,
										"ロードしました！",
										"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
										MB_OK
									);

									WaitTimer(300);
								}

								//ウインドウ風描画時の処理
								if (soundnovel_winownovel == 1) {

									ClearDrawScreen();
									GAMEMENU_COUNT = 1;

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

										// 音量の設定
										ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

									MessageBox(
										NULL,
										"ロードしました！",
										"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
										MB_OK
									);

									WaitTimer(300);
								}

								MessageBox(
									NULL,
									"ロードしました！",
									"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
									MB_OK
								);

								break;
							}

							WaitTimer(300);
						}

						//メニューに戻る
						if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
							SAVE = MessageBox(
								NULL,
								"メニューに戻りますか？",
								"ノベルゲームエンジン「LINKS」",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								ClearDrawScreen();
								SaveFlag = 0;
								WaitTimer(300);

								break;
							}

							WaitTimer(300);
						}
					}
				}

				WaitTimer(300);

			}

			//セーブデータ削除
			if (GAME_y == (GAMEMENU_y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 3) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"セーブデータ削除画面に移行しますか？",
					"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					ClearDrawScreen();
					SaveFlag = 3;
					SAVE_y = SAVE_Y;
				}

				WaitTimer(300);

				//セーブデータ・削除画面
				if (SaveFlag == 3) {

					//セーブ時のスクリーンショット読込
					SAVESNAP1 = LoadGraph("DATA/SAVE/SAVESNAP1.png");
					SAVESNAP2 = LoadGraph("DATA/SAVE/SAVESNAP2.png");
					SAVESNAP3 = LoadGraph("DATA/SAVE/SAVESNAP3.png");
					SAVETITLE = LoadGraph("DATA/BACKGROUND/SAVE.png");

					WaitTimer(600);

					while (ProcessMessage() == 0 && MoveKey(Key) == 0) {

						//背景描画
						DrawGraph(0, 0, SAVETITLE, TRUE);

						SAVE_LOAD_MENU(Cr, SAVE_y);

						//スクリーンショット描画
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y, 0.2f, 0, SAVESNAP1, TRUE);
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 2, 0.2f, 0, SAVESNAP2, TRUE);
						DrawRotaGraph(SAVE_SNAP_X, SAVE_Y * 3, 0.2f, 0, SAVESNAP3, TRUE);

						//セーブデータ名描画
						DrawString(SAVE_NAME_X, SAVE_Y, "セーブデータ1", Cr);
						DrawString(SAVE_NAME_X, SAVE_Y * 2, "セーブデータ2", Cr);
						DrawString(SAVE_NAME_X, SAVE_Y * 3, "セーブデータ3", Cr);
						DrawString(SAVE_NAME_X - CURSOR, SAVE_Y * 4, "メニューに戻る", Cr);

						//キー操作関連
						SetDrawScreen(DX_SCREEN_BACK);

						ClearDrawScreen();

						//マウス操作
						Mouse_Move();

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

						SetDrawScreen(DX_SCREEN_FRONT);

						if (SAVE_y == SAVE_Y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == SAVE_Y && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

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

								MessageBox(
									NULL,
									"削除しました！",
									"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
									MB_OK
									);

								if (soundnovel_winownovel == 0) {

									GAMEMENU_COUNT = 1;
									SaveFlag = 0;
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
									SP = SP - 1;
									CP = EOF;

									WaitTimer(300);

									break;
								}


								if (soundnovel_winownovel == 1) {

									GAMEMENU_COUNT = 1;
									SaveFlag = 0;
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
									SP = SP - 1;
									CP = EOF;

									WaitTimer(300);

									break;
								}


							}

							WaitTimer(300);
						}

						if (SAVE_y == (SAVE_Y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 2) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

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

								MessageBox(
									NULL,
									"削除しました！",
									"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
									MB_OK
									);

								if (soundnovel_winownovel == 0) {

									GAMEMENU_COUNT = 1;
									SaveFlag = 0;
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
									SP = SP - 1;
									CP = EOF;

									WaitTimer(300);

									break;
								}

								if (soundnovel_winownovel == 1) {

									GAMEMENU_COUNT = 1;
									SaveFlag = 0;
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
									SP = SP - 1;
									CP = EOF;

									WaitTimer(300);

									break;
								}

							}

							WaitTimer(300);
						}

						if (SAVE_y == (SAVE_Y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 3) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

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

								MessageBox(
									NULL,
									"削除しました！",
									"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
									MB_OK
									);

								if (soundnovel_winownovel == 0) {

									GAMEMENU_COUNT = 1;
									SaveFlag = 0;
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
									SP = SP - 1;
									CP = EOF;

									WaitTimer(300);

									break;
								}

								if (soundnovel_winownovel == 1) {

									GAMEMENU_COUNT = 1;
									SaveFlag = 0;
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
									SP = SP - 1;
									CP = EOF;

									WaitTimer(300);

									break;
								}
							}

							WaitTimer(300);
						}

						if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							SAVE = MessageBox(
								NULL,
								"メニューに戻りますか？",
								"ノベルゲームエンジン「LINKS」",
								MB_YESNO
								);

							if (SAVE == IDYES) {

								SaveFlag = 0;
								ClearDrawScreen();

								WaitTimer(300);

								break;
							}

							WaitTimer(300);
						}
					}
				}

			}

			//既読スキップ
			if (GAME_y == (GAMEMENU_y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 4) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SKIP_READ_LOAD();

				SAVE = MessageBox(
					NULL,
					"既読スキップを実行しますか？",
					"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
					MB_YESNO
					);

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

					if (soundnovel_winownovel == 0) {
						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						WaitTimer(300);

						break;
					}

					if (soundnovel_winownovel == 1) {
						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						WaitTimer(300);

						break;
					}
				}

				WaitTimer(300);
			}

			//スキップ
			if (GAME_y == (GAMEMENU_y * 5) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 5) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"スキップを実行しますか？",
					"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
					MB_YESNO
					);
				if (SAVE == IDYES) {

					if (soundnovel_winownovel == 0) {
						ClearDrawScreen();
						skip_auto = 2;
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						WaitTimer(300);

						break;
					}

					if (soundnovel_winownovel == 1) {
						ClearDrawScreen();
						skip_auto = 2;
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						WaitTimer(300);

						break;
					}
				}

				WaitTimer(300);
			}

			//オート
			if (GAME_y == (GAMEMENU_y * 6) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 6) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"オートモードを実行しますか？",
					"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
					MB_YESNO
					);
				if (SAVE == IDYES) {

					if (soundnovel_winownovel == 0) {
						ClearDrawScreen();
						skip_auto = 1;
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						WaitTimer(300);

						break;
					}

					if (soundnovel_winownovel == 1) {
						ClearDrawScreen();
						skip_auto = 1;
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						WaitTimer(300);

						break;
					}


				}

				WaitTimer(300);
			}

			//オート/スキップ停止
			if (GAME_y == (GAMEMENU_y * 7) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 7) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"スキップ又はオートモードを終了しますか？",
					"ノベルゲームエンジン「LINKS」",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					if (soundnovel_winownovel == 0) {
						ClearDrawScreen();
						skip_auto = 0;
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						WaitTimer(300);

						break;
					}

					if (soundnovel_winownovel == 1) {
						ClearDrawScreen();
						skip_auto = 0;
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						WaitTimer(300);

						break;
					}
				}

				WaitTimer(300);
			}

			//バックログ参照
			if (GAME_y == (GAMEMENU_y * 8) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 8) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"バックログ画面に移行しますか？",
					"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					WaitTimer(600);

					LOG = 1;

					while (ProcessMessage() == 0) {

						if (LOG != 10 && CheckHitKey(KEY_INPUT_UP) == 1 || LOG != 10 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
							LOG++;
							WaitTimer(300);
						}

						if (LOG != 1 && CheckHitKey(KEY_INPUT_DOWN) == 1 || LOG != 1 && (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
							LOG--;
							WaitTimer(300);
						}

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

						SetDrawScreen(DX_SCREEN_BACK);

						ClearDrawScreen();

						SetDrawScreen(DX_SCREEN_FRONT);

						if (CheckHitKey(KEY_INPUT_RETURN) == 1 || (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0 && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

							ClearDrawScreen();

							DeleteGraph(BACKLOG[0]);

							WaitTimer(300);

							break;
						}
					}
				}

				WaitTimer(300);
			}

			//設定
			if (GAME_y == (GAMEMENU_y * 9) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 9) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

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

						//セーブデータ名描画
						DrawString(SAVE_NAME_X, GAMEMENU_y, "ＢＧＭ音量", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 2, "ＳＥ音量", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 3, "オート速度", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 4, "スキップ速度", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 5, "文字描画速度", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 6, "描画方法", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 7, "非アクティブ時", Cr);
						DrawString(SAVE_NAME_X, GAMEMENU_y * 8, "メニューに戻る", Cr);

						//目盛り描画

						if (BGM_VOL_COUNT == 10)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■■■■■■■", Cr);

						if (BGM_VOL_COUNT == 9)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■■■■■■", Cr);

						if (BGM_VOL_COUNT == 8)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■■■■■", Cr);

						if (BGM_VOL_COUNT == 7)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■■■■", Cr);

						if (BGM_VOL_COUNT == 6)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■■■", Cr);

						if (BGM_VOL_COUNT == 5)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■■", Cr);

						if (BGM_VOL_COUNT == 4)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■", Cr);

						if (BGM_VOL_COUNT == 3)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■", Cr);

						if (BGM_VOL_COUNT == 2)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■", Cr);

						if (BGM_VOL_COUNT == 1)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■", Cr);

						if (BGM_VOL_COUNT == 0)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "", Cr);

						if (SE_VOL_COUNT == 10)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■■■■■■■", Cr);

						if (SE_VOL_COUNT == 9)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■■■■■■", Cr);

						if (SE_VOL_COUNT == 8)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■■■■■", Cr);

						if (SE_VOL_COUNT == 7)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■■■■", Cr);

						if (SE_VOL_COUNT == 6)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■■■", Cr);

						if (SE_VOL_COUNT == 5)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■■", Cr);

						if (SE_VOL_COUNT == 4)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■", Cr);

						if (SE_VOL_COUNT == 3)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■", Cr);

						if (SE_VOL_COUNT == 2)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■", Cr);

						if (SE_VOL_COUNT == 1)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■", Cr);

						if (SE_VOL_COUNT == 0)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "", Cr);

						if (AUTO_SPEED_COUNT == 10)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■■■■■■■", Cr);

						if (AUTO_SPEED_COUNT == 9)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■■■■■■", Cr);

						if (AUTO_SPEED_COUNT == 8)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■■■■■", Cr);

						if (AUTO_SPEED_COUNT == 7)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■■■■", Cr);

						if (AUTO_SPEED_COUNT == 6)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■■■", Cr);

						if (AUTO_SPEED_COUNT == 5)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■■", Cr);

						if (AUTO_SPEED_COUNT == 4)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■", Cr);

						if (AUTO_SPEED_COUNT == 3)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■", Cr);

						if (AUTO_SPEED_COUNT == 2)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■", Cr);

						if (AUTO_SPEED_COUNT == 1)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■", Cr);

						if (AUTO_SPEED_COUNT == 0)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "", Cr);

						if (SKIP_SPEED_COUNT == 10)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■■■■■■■", Cr);

						if (SKIP_SPEED_COUNT == 9)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■■■■■■", Cr);

						if (SKIP_SPEED_COUNT == 8)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■■■■■", Cr);

						if (SKIP_SPEED_COUNT == 7)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■■■■", Cr);

						if (SKIP_SPEED_COUNT == 6)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■■■", Cr);

						if (SKIP_SPEED_COUNT == 5)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■■", Cr);

						if (SKIP_SPEED_COUNT == 4)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■", Cr);

						if (SKIP_SPEED_COUNT == 3)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■", Cr);

						if (SKIP_SPEED_COUNT == 2)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■", Cr);

						if (SKIP_SPEED_COUNT == 1)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■", Cr);

						if (SKIP_SPEED_COUNT == 0)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "", Cr);


						if (STRING_SPEED_COUNT == 10)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■■■■■■■", Cr);

						if (STRING_SPEED_COUNT == 9)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■■■■■■", Cr);

						if (STRING_SPEED_COUNT == 8)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■■■■■", Cr);

						if (STRING_SPEED_COUNT == 7)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■■■■", Cr);

						if (STRING_SPEED_COUNT == 6)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■■■", Cr);

						if (STRING_SPEED_COUNT == 5)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■■", Cr);

						if (STRING_SPEED_COUNT == 4)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■", Cr);

						if (STRING_SPEED_COUNT == 3)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■", Cr);

						if (STRING_SPEED_COUNT == 2)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■", Cr);

						if (STRING_SPEED_COUNT == 1)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■", Cr);

						if (STRING_SPEED_COUNT == 0)
							DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "", Cr);

						if (soundnovel_winownovel == 0)
							DrawString(SAVE_NAME_X + CURSOR * 6, GAMEMENU_y * 6, "サウンドノベル風", Cr);

						if (soundnovel_winownovel == 1)
							DrawString(SAVE_NAME_X + CURSOR * 6, GAMEMENU_y * 6, "ウインドウ風", Cr);

						if (WindowActive == TRUE)
							DrawString(SAVE_NAME_X + CURSOR * 7, GAMEMENU_y * 7, "処理", Cr);

						if (WindowActive == FALSE)
							DrawString(SAVE_NAME_X + CURSOR * 7, GAMEMENU_y * 7, "未処理", Cr);

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

						//サウンドノベル風とウインドウ風の切り替え
						if (GAME_y == GAMEMENU_y * 6 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 6 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

							WaitTimer(300);
							soundnovel_winownovel = 0;
						}

						if (GAME_y == GAMEMENU_y * 6 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 6 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

							WaitTimer(300);
							soundnovel_winownovel = 1;
						}

						//非アクティブ時の処理の切り替え
						if (GAME_y == GAMEMENU_y * 7 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 7 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

							WaitTimer(300);
							WindowActive = FALSE;

							//非アクティブ状態では処理を実行しない
							SetAlwaysRunFlag(WindowActive);
						}

						if (GAME_y == GAMEMENU_y * 7 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 7 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

							WaitTimer(300);
							WindowActive = TRUE;

							//非アクティブ状態でもゲームを実行
							SetAlwaysRunFlag(WindowActive);
						}

						//メニューに戻る
						if (GAME_y == GAMEMENU_y * 8 && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == GAMEMENU_y * 8 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

							SAVE = MessageBox(
								NULL,
								"メニューに戻りますか？",
								"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
								MB_YESNO
								);

							if (SAVE == IDYES) {
								WaitTimer(300);
								ClearDrawScreen();
								GAME_y = GAMEMENU_y;
								Config = 0;
								break;
							}

							WaitTimer(300);
						}

						//キー操作関連
						SetDrawScreen(DX_SCREEN_BACK);

						ClearDrawScreen();

						Mouse_Move();

						if (Key[KEY_INPUT_DOWN] == 1) {
							ClearDrawScreen();
							GAME_y += GAMEMENU_y;
							if (GAME_y == (GAMEMENU_y * 9))
								GAME_y = GAMEMENU_y;
						}

						if (Key[KEY_INPUT_UP] == 1) {
							ClearDrawScreen();
							GAME_y -= GAMEMENU_y;
							if (GAME_y == (GAMEMENU_y - GAMEMENU_y))
								GAME_y = (GAMEMENU_y * 8);
						}

						SetDrawScreen(DX_SCREEN_FRONT);


					}
				}

				WaitTimer(300);

			}

			//タイトルに戻る
			if (GAME_y == (GAMEMENU_y * 10) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 10) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

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
					SaveFlag = 0;
					CHARACTER = 0;
					BACKGROUND = 0;
					BACKGROUNDMUSIC = 0;

					WaitTimer(300);

					break;
				}

				WaitTimer(300);

			}

			//ゲームに戻る
			if (GAME_y == (GAMEMENU_y * 11) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 11) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"ゲームに戻りますか？",
					"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					if (soundnovel_winownovel == 0) {
						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						WaitTimer(300);

						break;
					}

					if (soundnovel_winownovel == 1) {

						ClearDrawScreen();
						GAMEMENU_COUNT = 1;

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

							// 音量の設定
							ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

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

						WaitTimer(300);

						break;
					}

				}

				WaitTimer(300);
			}

			//ゲーム終了
			if (GAME_y == (GAMEMENU_y * 12) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (GAMEMENU_y * 12) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

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
					break;
				}

				WaitTimer(300);
			}

			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {

				SAVE = MessageBox(
					NULL,
					"終了しますか？",
					"ノベルゲームエンジン「LINKS」",
					MB_YESNO
					);

				if (SAVE == IDYES) {

					EndFlag = 99999;
					break;
				}

				WaitTimer(300);
			}
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
		}
	}

	return 0;
}

//スクリプトタグ処理(立ち絵)
void SCRIPT_OUTPUT_CHARACTER() {

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

}

//スクリプトタグ処理(メイン)関数
int SCRIPT_OUTPUT() {

	char  Moji;

	// 文字の描画
	Moji = String[SP][CP];

	switch (Moji)
	{

		//********************演出文字(ここから)****************************************//

		// 改行文字
	case '0':

		// 改行処理および参照文字位置を一つ進める
		Kaigyou();
		CP++;

		break;

		// ボタン押し待ち文字
	case '1':

		//スキップ・オート変数がＯＦＦの場合
		if (skip_auto == 0) {

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

			// ボタン押し待ちおよび参照文字位置を一つ進める
			WaitKey();

			//エンターキーで次へ
			if (CheckHitKey(KEY_INPUT_RETURN) == 1 || (GetMouseInput() & MOUSE_INPUT_LEFT) == 1)
				CP++;
		}

		//スキップ・オート変数がＯＮの場合（オートモード）
		if (skip_auto == 1) {

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

			//少し待って、次の文字列を描画
			WaitTimer(1800 * AUTO_SPEED / 100);
			CP++;
		}

		//スキップ・オート変数がＯＮの場合(スキップ)
		if (skip_auto == 2) {

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

			CP++;
		}

		break;

		// クリア文字
	case '2':


		SetDrawScreen(DX_SCREEN_BACK);

		BACKLOG_COUNT++;

		if (BACKLOG_COUNT == 1) {

			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;
		}

		if (BACKLOG_COUNT == 2) {

			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

		if (BACKLOG_COUNT == 3) {
		
			BACKLOG_BACKGROUND = BACKLOG[1];

			BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

		if (BACKLOG_COUNT == 4) {

			BACKLOG_BACKGROUND = BACKLOG[2];

			BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG_BACKGROUND = BACKLOG[1];

			BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

			BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

			BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

			BACKLOG[0] = BACKLOG_HANDLE;

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

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

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

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

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

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

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

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

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

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

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

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

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

		}

		SetDrawScreen(DX_SCREEN_FRONT);
			
		break;

		//少し待つ
	case '3':

		//オート又は通常時、3秒待つ
		if (skip_auto != 2) {
			WaitTimer(1800);
			CP++;
		}

		//スキップ時、3秒待たずに次へ
		if (skip_auto == 2)
			CP++;
		
		break;

		//ゲームオーバー
	case '4':

		BACKGROUND = GAMEOVER;
		DrawGraph(0, 0, BACKGROUND, TRUE);

		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}

		CP++;
		break;

		//エンディング
	case '5':

		PlayMovie("DATA/MOVIE/ENDING.wmv", 1, DX_MOVIEPLAYTYPE_NORMAL);
		CP++;

		break;

		//BGMの再生を止める
	case '6':

		StopSoundMem(BACKGROUNDMUSIC);
		BACKGROUNDMUSIC = 0;
		CP++;

		break;

		//SEの再生を止める
	case '7':

		StopSoundMem(SOUNDEFFECT);
		CP++;

		break;

		//
	case '8':
		y = SENTAKUSIY;

		if (EndFlag == 1 || EndFlag == 2 || EndFlag == 3 || EndFlag == 4 || EndFlag == 5 || EndFlag == 6 || EndFlag == 7) {

			WaitTimer(1200);

			SAVE_CHOICE = 1;
			SAVESNAP_CHOICE = 1;

			BACKLOG_COUNT++;

			//選択肢

			while (ProcessMessage() == 0 && MoveKey(Key) == 0 && EndFlag != 99 && EndFlag != 99999) {

				if (soundnovel_winownovel == 0) {

					DrawGraph(0, 0, BACKGROUND, TRUE);

					DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
				}

				if (soundnovel_winownovel == 1) {

					int	Window_Color = GetColor(0, 0, 0);

					DrawGraph(0, 0, BACKGROUND, TRUE);
					
					DrawBox(0, 400, 640, 480, Window_Color, TRUE);

					DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
				}

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

				sentakusi(Cr, y);

				//ゲームメニュー
				GAMEMENU();

				//ゲーム終了
				GAME_FINISH();

				if (SAVESNAP_CHOICE == 1) {

					SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP_CHOICE.png", 0);

					SAVESNAP_CHOICE = LoadGraph("DATA/SAVE/SAVESNAP_CHOICE.png", 0);

				}

				//キー操作関連
				SetDrawScreen(DX_SCREEN_BACK);

				ClearDrawScreen();

				Mouse_Move();

				if (Key[KEY_INPUT_DOWN] == 1) {
					ClearDrawScreen();
					y += CURSOR;
					if (y == (SENTAKUSI2 + CURSOR))                         // y座標が260なら(選択が一番下なら)
						y = SENTAKUSI1;                        // 選択座標を一番上に
				}
				if (Key[KEY_INPUT_UP] == 1) {
					ClearDrawScreen();
					y -= CURSOR;
					if (y == (SENTAKUSI1 - CURSOR))
						y = SENTAKUSI2;
				}

				SetDrawScreen(DX_SCREEN_FRONT);

				if (y == SENTAKUSI1 && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == SENTAKUSI1 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

					if (EndFlag == 1) {
						EndFlag = 2;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 2) {
						EndFlag = 4;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 3) {
						EndFlag = 6;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 4) {
						EndFlag = 8;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 5) {
						EndFlag = 10;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 6) {
						EndFlag = 12;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 7) {
						EndFlag = 14;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

				}

				if (y == SENTAKUSI2 && CheckHitKey(KEY_INPUT_RETURN) == 1 || y == SENTAKUSI2 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

					if (EndFlag == 1) {
						EndFlag = 3;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 2) {
						EndFlag = 5;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 3) {
						EndFlag = 7;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 4) {
						EndFlag = 9;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 5) {
						EndFlag = 11;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 6) {
						EndFlag = 13;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					if (EndFlag == 7) {
						EndFlag = 15;
						SAVE_CHOICE = 0;
						SAVESNAP_CHOICE = 0;
						break;
					}

					CP++;
					break;
				}

			}


			SetDrawScreen(DX_SCREEN_BACK);

			if (soundnovel_winownovel == 0) {

				DrawGraph(0, 0, BACKGROUND, TRUE);

				DrawGraph(CHARACTERX, CHARACTERY, CHARACTER, TRUE);
			}

			if (soundnovel_winownovel == 1) {

				int	Window_Color = GetColor(0, 0, 0);

				DrawGraph(0, 0, BACKGROUND, TRUE);

				DrawBox(0, 400, 640, 480, Window_Color, TRUE);

				DrawGraph(CHARACTERX, CHARACTERY - CHARACTERY, CHARACTER, TRUE);
			}

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

			sentakusi(Cr, y);

			if (BACKLOG_COUNT == 1) {

				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

			}

			if (BACKLOG_COUNT == 2) {

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

			}

			if (BACKLOG_COUNT == 3) {

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 4) {

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			SetDrawScreen(DX_SCREEN_FRONT);

			// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
			SetDrawScreen(DX_SCREEN_BACK);

			ClearDrawScreen();
			DrawPointY = 0;
			DrawPointX = 0;
			CHARACTER = 0;
			BACKGROUND = 0;
			CP++;

			SetDrawScreen(DX_SCREEN_FRONT);

			break;
		}

		if (EndFlag == 8 || EndFlag == 9 || EndFlag == 10 || EndFlag == 11 || EndFlag == 12 || EndFlag == 13 || EndFlag == 14 || EndFlag == 15) {
			CP++;
			break;
		}

		// 終了文字
	case '9':

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

		break;

		//立ち絵消しタグ
	case '@':

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

		break;

		//ウインドウ風キャラクター名描画タグ
	case '#':

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

		break;

		//********************演出文字(ここまで)****************************************//

		//********************キャラクター画像読込文字(ここから)****************************************//

		//キャラ01読込（画面に出力）
	case 'A':

		//キャラ01読込
		CHARACTER = CHARACTER_LOAD[0];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER();

		//文字を進める
		CP++;

		break;

		//キャラ02読込（画面に出力）
	case 'B':

		//キャラ02読込
		CHARACTER = CHARACTER_LOAD[1];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER();

		//文字を進める
		CP++;

		break;

		//キャラ03読込（画面に出力）
	case 'C':

		//キャラ03読込
		CHARACTER = CHARACTER_LOAD[2];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER();

		//文字を進める
		CP++;

		break;

		//キャラ04読込（画面に出力）
	case 'D':

		//キャラ04読込
		CHARACTER = CHARACTER_LOAD[3];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER();

		//文字を進める
		CP++;

		break;

		//キャラ05読込（画面に出力）
	case 'E':

		//キャラ05読込
		CHARACTER = CHARACTER_LOAD[4];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER();

		//文字を進める
		CP++;

		break;

		//キャラ06読込（画面に出力）
	case 'F':

		//キャラ06読込
		CHARACTER = CHARACTER_LOAD[5];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER();

		//文字を進める
		CP++;

		break;

		//キャラ07読込（画面に出力）
	case 'G':

		//キャラ07読込
		CHARACTER = CHARACTER_LOAD[6];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER();

		//文字を進める
		CP++;

		break;

		//キャラ08読込（画面に出力）
	case 'H':

		//キャラ08読込
		CHARACTER = CHARACTER_LOAD[7];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER();

		//文字を進める
		CP++;

		break;

		//キャラ09読込（画面に出力）
	case 'I':

		//キャラ09読込
		CHARACTER = CHARACTER_LOAD[8];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER();

		//文字を進める
		CP++;

		break;

		//キャラ10読込（画面に出力）
	case 'J':

		//キャラ10読込
		CHARACTER = CHARACTER_LOAD[9];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER();

		//文字を進める
		CP++;

		break;

		//キャラ11読込（画面に出力）
	case 'K':

		//キャラ11読込
		CHARACTER = CHARACTER_LOAD[10];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER();

		//文字を進める
		CP++;

		break;

		//キャラ12読込（画面に出力）
	case 'L':

		//キャラ02読込
		CHARACTER = CHARACTER_LOAD[11];

		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER();

		//文字を進める
		CP++;

		break;

		//********************キャラクター画像読込文字(ここまで)****************************************//

		//********************背景画像読込文字(ここから)****************************************//

		//背景01読込（画面に出力）
	case 'M':

		BACKGROUND = BACKGROUND_LOAD[0];

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(0, 0, BACKGROUND, TRUE);

		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);
 			
			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}

		CP++;

		break;

		//背景02読込（画面に出力）
	case 'N':

		BACKGROUND = BACKGROUND_LOAD[1];

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(0, 0, BACKGROUND, TRUE);

		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}

		CP++;

		break;

		//背景03読込（画面に出力）
	case 'O':

		BACKGROUND = BACKGROUND_LOAD[2];

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//背景04読込（画面に出力）
	case 'P':

		BACKGROUND = BACKGROUND_LOAD[3];

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//背景05読込（画面に出力）
	case 'Q':

		BACKGROUND = BACKGROUND_LOAD[4];

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//背景06読込（画面に出力）
	case 'R':

		BACKGROUND = BACKGROUND_LOAD[5];

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//背景07読込（画面に出力）
	case 'S':

		BACKGROUND = BACKGROUND_LOAD[6];

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//背景08読込（画面に出力）
	case 'T':

		BACKGROUND = BACKGROUND_LOAD[7];

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//背景09読込（画面に出力）
	case 'U':

		BACKGROUND = BACKGROUND_LOAD[8];

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//背景10読込（画面に出力）
	case 'V':

		BACKGROUND = BACKGROUND_LOAD[9];

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//背景11読込（画面に出力）
	case 'W':

		BACKGROUND = BACKGROUND_LOAD[10];

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//背景12読込（画面に出力）
	case 'X':

		BACKGROUND = BACKGROUND_LOAD[11];

		// 読みこんだグラフィックを画面左上に描画
		DrawGraph(0, 0, BACKGROUND, TRUE);
		
		if (soundnovel_winownovel == 1) {

			int	Window_Color = GetColor(0, 0, 0);

			DrawBox(0, 400, 640, 480, Window_Color, TRUE);
		}
		
		CP++;

		break;

		//********************背景画像読込文字(ここまで)****************************************//


		//********************BGM再生文字(ここから)****************************************//

		//BGM01再生文字
	case 'Y':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[0];

		// 音量の設定
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM02再生文字
	case 'Z':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[1];

		// 音量の設定
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM03再生文字
	case 'a':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[2];

		// 音量の設定
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM04再生文字
	case 'b':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[3];

		// 音量の設定
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM05再生文字
	case 'c':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[4];

		// 音量の設定
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM06再生文字
	case 'd':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[5];

		// 音量の設定
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM07再生文字
	case 'e':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[6];

		// 音量の設定
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM08再生文字
	case 'f':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[7];

		// 音量の設定
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM09再生文字
	case 'g':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[8];

		// 音量の設定
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM10再生文字
	case 'h':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[9];

		// 音量の設定
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM11再生文字
	case 'i':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[10];

		// 音量の設定
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//BGM12再生文字
	case 'j':

		StopSoundMem(BACKGROUNDMUSIC);

		BACKGROUNDMUSIC = BACKGROUNDMUSIC_LOAD[11];

		// 音量の設定
		ChangeVolumeSoundMem(255 * BGM_VOL / 100, BACKGROUNDMUSIC);

		PlaySoundMem(BACKGROUNDMUSIC, DX_PLAYTYPE_LOOP);
		CP++;

		break;

		//********************BGM再生文字(ここまで)****************************************//

		//********************SE再生文字(ここから)****************************************//

		//SE01再生文字
	case 'k':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[0];

		// 音量の設定
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE02再生文字
	case 'l':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[1];

		// 音量の設定
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE03再生文字
	case 'm':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[2];

		// 音量の設定
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE04再生文字
	case 'n':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[3];

		// 音量の設定
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE05再生文字
	case 'o':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[4];

		// 音量の設定
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE06再生文字
	case 'p':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[5];

		// 音量の設定
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE07再生文字
	case 'q':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[6];

		// 音量の設定
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE08再生文字
	case 'r':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[7];

		// 音量の設定
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE09再生文字
	case 's':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[8];

		// 音量の設定
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE10再生文字
	case 't':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[9];

		// 音量の設定
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE11再生文字
	case 'u':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[10];

		// 音量の設定
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//SE12再生文字
	case 'v':

		StopSoundMem(SOUNDEFFECT);

		SOUNDEFFECT = SOUNDEFFECT_LOAD[11];

		// 音量の設定
		ChangeVolumeSoundMem(255 * SE_VOL / 100, SOUNDEFFECT);

		PlaySoundMem(SOUNDEFFECT, DX_PLAYTYPE_BACK);
		CP++;

		break;

		//********************se再生文字(ここまで)****************************************//

		//********************動画読込文字(ここから)****************************************//

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

		//********************動画読込文字(ここまで)****************************************//

	default:	// その他の文字

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

		// 画面からはみ出たら改行する
		if (DrawPointX * MOJI_SIZE + MOJI_SIZE > 640)
			Kaigyou();

		//サウンドノベル風時の改ページ処理
		if (soundnovel_winownovel == 0 && DrawPointY * MOJI_SIZE + MOJI_SIZE > CHARACTERY + MOJI_SIZE) {

			SetDrawScreen(DX_SCREEN_BACK);

			BACKLOG_COUNT++;

			if (BACKLOG_COUNT == 1) {

				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

			}

			if (BACKLOG_COUNT == 2) {

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

			}

			if (BACKLOG_COUNT == 3) {

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 4) {

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}
			
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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

		//ウインドウ風時の改ページ処理
		if (soundnovel_winownovel == 1 && DrawPointY > 479 ) {


			SetDrawScreen(DX_SCREEN_BACK);

			BACKLOG_COUNT++;

			if (BACKLOG_COUNT == 1) {

				SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

			}

			if (BACKLOG_COUNT == 2) {

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

			}

			if (BACKLOG_COUNT == 3) {

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

			if (BACKLOG_COUNT == 4) {

				BACKLOG_BACKGROUND = BACKLOG[2];

				BACKLOG[3] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG_BACKGROUND = BACKLOG[1];

				BACKLOG[2] = DerivationGraph(0, 0, 640, 480, BACKLOG_BACKGROUND);

				BACKLOG[1] = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				SaveDrawScreen(0, 0, 640, 480, "DATA/BACKLOG/BACKLOG1.png");

				BACKLOG_HANDLE = LoadGraph("DATA/BACKLOG/BACKLOG1.png");

				BACKLOG[0] = BACKLOG_HANDLE;

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				CHARACTER = 0;
				BACKGROUND = 0;
				CP++;

			}

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

//スクリーンショット機能
int SCREENSHOT() {
	
		//スクリーンショット０１取得
		if (SCREENSHOT_COUNT == 0 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT01.png", 0);

			MessageBox(
				NULL,
				"スクリーンショット０１を取得しました！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//スクリーンショット０２取得
		if (SCREENSHOT_COUNT == 1 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT02.png", 0);

			MessageBox(
				NULL,
				"スクリーンショット０２を取得しました！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//スクリーンショット０３取得
		if (SCREENSHOT_COUNT == 2 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT03.png", 0);

			MessageBox(
				NULL,
				"スクリーンショット０３を取得しました！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//スクリーンショット０４取得
		if (SCREENSHOT_COUNT == 3 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT04.png", 0);

			MessageBox(
				NULL,
				"スクリーンショット０４を取得しました！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//スクリーンショット０５取得
		if (SCREENSHOT_COUNT == 4 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT05.png", 0);

			MessageBox(
				NULL,
				"スクリーンショット０５を取得しました！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//スクリーンショット０６取得
		if (SCREENSHOT_COUNT == 5 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT06.png", 0);

			MessageBox(
				NULL,
				"スクリーンショット０６を取得しました！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//スクリーンショット０７取得
		if (SCREENSHOT_COUNT == 6 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT07.png", 0);

			MessageBox(
				NULL,
				"スクリーンショット０７を取得しました！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//スクリーンショット０８取得
		if (SCREENSHOT_COUNT == 7 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT08.png", 0);

			MessageBox(
				NULL,
				"スクリーンショット０８を取得しました！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//スクリーンショット０９取得
		if (SCREENSHOT_COUNT == 8 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT09.png", 0);

			MessageBox(
				NULL,
				"スクリーンショット０９を取得しました！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

		//スクリーンショット１０取得
		if (SCREENSHOT_COUNT == 9 && CheckHitKey(KEY_INPUT_F12) == 1) {
			
			SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SCREENSHOT/SCREENSHOT10.png", 0);

			MessageBox(
				NULL,
				"スクリーンショット１０を取得しました！",
				"ノベルゲームエンジン「LINKS」",
				MB_OK
			);

			WaitTimer(300);
			SCREENSHOT_COUNT++;

		}

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

//コンフィグ(タイトル画面)
int CONFIG(){


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

			//セーブデータ名描画
			DrawString(SAVE_NAME_X, GAMEMENU_y, "ＢＧＭ音量", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 2, "ＳＥ音量", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 3, "オート速度", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 4, "スキップ速度", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 5, "文字描画速度", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 6, "描画方法", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 7, "非アクティブ時", Cr);
			DrawString(SAVE_NAME_X, GAMEMENU_y * 8, "メニューに戻る", Cr);

			//目盛り描画

			if (BGM_VOL_COUNT == 10)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■■■■■■■", Cr);

			if (BGM_VOL_COUNT == 9)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■■■■■■", Cr);

			if (BGM_VOL_COUNT == 8)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■■■■■", Cr);

			if (BGM_VOL_COUNT == 7)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■■■■", Cr);

			if (BGM_VOL_COUNT == 6)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■■■", Cr);

			if (BGM_VOL_COUNT == 5)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■■", Cr);

			if (BGM_VOL_COUNT == 4)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■■", Cr);

			if (BGM_VOL_COUNT == 3)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■■", Cr);

			if (BGM_VOL_COUNT == 2)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■■", Cr);

			if (BGM_VOL_COUNT == 1)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "■", Cr);

			if (BGM_VOL_COUNT == 0)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y, "", Cr);

			if (SE_VOL_COUNT == 10)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■■■■■■■", Cr);

			if (SE_VOL_COUNT == 9)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■■■■■■", Cr);

			if (SE_VOL_COUNT == 8)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■■■■■", Cr);

			if (SE_VOL_COUNT == 7)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■■■■", Cr);

			if (SE_VOL_COUNT == 6)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■■■", Cr);

			if (SE_VOL_COUNT == 5)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■■", Cr);

			if (SE_VOL_COUNT == 4)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■■", Cr);

			if (SE_VOL_COUNT == 3)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■■", Cr);

			if (SE_VOL_COUNT == 2)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■■", Cr);

			if (SE_VOL_COUNT == 1)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "■", Cr);

			if (SE_VOL_COUNT == 0)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 2, "", Cr);

			if (AUTO_SPEED_COUNT == 10)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■■■■■■■", Cr);

			if (AUTO_SPEED_COUNT == 9)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■■■■■■", Cr);

			if (AUTO_SPEED_COUNT == 8)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■■■■■", Cr);

			if (AUTO_SPEED_COUNT == 7)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■■■■", Cr);

			if (AUTO_SPEED_COUNT == 6)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■■■", Cr);

			if (AUTO_SPEED_COUNT == 5)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■■", Cr);

			if (AUTO_SPEED_COUNT == 4)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■■", Cr);

			if (AUTO_SPEED_COUNT == 3)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■■", Cr);

			if (AUTO_SPEED_COUNT == 2)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■■", Cr);

			if (AUTO_SPEED_COUNT == 1)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "■", Cr);

			if (AUTO_SPEED_COUNT == 0)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 3, "", Cr);

			if (SKIP_SPEED_COUNT == 10)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■■■■■■■", Cr);

			if (SKIP_SPEED_COUNT == 9)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■■■■■■", Cr);

			if (SKIP_SPEED_COUNT == 8)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■■■■■", Cr);

			if (SKIP_SPEED_COUNT == 7)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■■■■", Cr);

			if (SKIP_SPEED_COUNT == 6)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■■■", Cr);

			if (SKIP_SPEED_COUNT == 5)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■■", Cr);

			if (SKIP_SPEED_COUNT == 4)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■■", Cr);

			if (SKIP_SPEED_COUNT == 3)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■■", Cr);

			if (SKIP_SPEED_COUNT == 2)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■■", Cr);

			if (SKIP_SPEED_COUNT == 1)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "■", Cr);

			if (SKIP_SPEED_COUNT == 0)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 4, "", Cr);

			if (STRING_SPEED_COUNT == 10)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■■■■■■■", Cr);

			if (STRING_SPEED_COUNT == 9)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■■■■■■", Cr);

			if (STRING_SPEED_COUNT == 8)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■■■■■", Cr);

			if (STRING_SPEED_COUNT == 7)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■■■■", Cr);

			if (STRING_SPEED_COUNT == 6)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■■■", Cr);

			if (STRING_SPEED_COUNT == 5)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■■", Cr);

			if (STRING_SPEED_COUNT == 4)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■■", Cr);

			if (STRING_SPEED_COUNT == 3)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■■", Cr);

			if (STRING_SPEED_COUNT == 2)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■■", Cr);

			if (STRING_SPEED_COUNT == 1)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "■", Cr);

			if (STRING_SPEED_COUNT == 0)
				DrawString(SAVE_NAME_X + CURSOR * 5, GAMEMENU_y * 5, "", Cr);

			if (soundnovel_winownovel == 0)
				DrawString(SAVE_NAME_X + CURSOR * 6, GAMEMENU_y * 6, "サウンドノベル風", Cr);

			if (soundnovel_winownovel == 1)
				DrawString(SAVE_NAME_X + CURSOR * 6, GAMEMENU_y * 6, "ウインドウ風", Cr);

			if (WindowActive == TRUE)
				DrawString(SAVE_NAME_X + CURSOR * 7, GAMEMENU_y * 7, "処理", Cr);

			if (WindowActive == FALSE)
				DrawString(SAVE_NAME_X + CURSOR * 7, GAMEMENU_y * 7, "未処理", Cr);

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

			//サウンドノベル風とウインドウ風の切り替え
			if (GAME_y == GAMEMENU_y * 6 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == GAMEMENU_y * 6 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				WaitTimer(300);
				soundnovel_winownovel = 0;
			}

			if (GAME_y == GAMEMENU_y * 6 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == GAMEMENU_y * 6 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

				WaitTimer(300);
				soundnovel_winownovel = 1;
			}

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

			//タイトルに戻る
			if (GAME_y == GAMEMENU_y * 8 && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == GAMEMENU_y * 8 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				SAVE = MessageBox(
					NULL,
					"タイトルに戻りますか？",
					"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
					MB_YESNO
				);

				if (SAVE == IDYES) {
					WaitTimer(300);
					ClearDrawScreen();
					GAME_y = GAMEMENU_y;
					Config = 0;
					break;
				}

				WaitTimer(300);
			}

			//キー操作関連
			SetDrawScreen(DX_SCREEN_BACK);

			ClearDrawScreen();

			//マウス操作関連
			Mouse_Move();

			//キー操作関連
			if (Key[KEY_INPUT_DOWN] == 1) {
				ClearDrawScreen();
				GAME_y += GAMEMENU_y;
				if (GAME_y == (GAMEMENU_y * 9))
					GAME_y = GAMEMENU_y;
			}

			if (Key[KEY_INPUT_UP] == 1) {
				ClearDrawScreen();
				GAME_y -= GAMEMENU_y;
				if (GAME_y == (GAMEMENU_y - GAMEMENU_y))
					GAME_y = (GAMEMENU_y * 8);
			}

			SetDrawScreen(DX_SCREEN_FRONT);


		}
	}

	WaitTimer(300);



	return 0;
}