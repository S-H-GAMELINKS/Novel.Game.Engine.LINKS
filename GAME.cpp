//ライブラリとヘッダの読み込み
#include "DxLib.h"
#include "DEF.h"

// 文字列描画の位置
int DrawPointX = 0, DrawPointY = 0;

// 参照する文字列番号と文字列中の文字ポインタ
int SP = 0, CP = 0;

//キャラクター画像読込変数
int CHARACTER_LOAD[100], CHARACTER, CHARACTER_DUMMY;

//背景画像読込変数
int BACKGROUND_LOAD[100], BACKGROUND;

//背景音楽読込変数
int BACKGROUNDMUSIC_LOAD[100], BACKGROUNDMUSIC;

//効果音変数
int SOUNDEFFECT_LOAD[100], SOUNDEFFECT;

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

//立ち絵素材読込
void MATERIAL_LOAD_CHARACTER() {

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
	CHARACTER_LOAD[12] = LoadGraph("DATA/CHARACTER/CHAR12.png");
	CHARACTER_LOAD[13] = LoadGraph("DATA/CHARACTER/CHAR13.png");
	CHARACTER_LOAD[14] = LoadGraph("DATA/CHARACTER/CHAR14.png");
	CHARACTER_LOAD[15] = LoadGraph("DATA/CHARACTER/CHAR15.png");
	CHARACTER_LOAD[16] = LoadGraph("DATA/CHARACTER/CHAR16.png");
	CHARACTER_LOAD[17] = LoadGraph("DATA/CHARACTER/CHAR17.png");
	CHARACTER_LOAD[18] = LoadGraph("DATA/CHARACTER/CHAR18.png");
	CHARACTER_LOAD[19] = LoadGraph("DATA/CHARACTER/CHAR19.png");
	CHARACTER_LOAD[20] = LoadGraph("DATA/CHARACTER/CHAR20.png");
	CHARACTER_LOAD[21] = LoadGraph("DATA/CHARACTER/CHAR21.png");
	CHARACTER_LOAD[22] = LoadGraph("DATA/CHARACTER/CHAR22.png");
	CHARACTER_LOAD[23] = LoadGraph("DATA/CHARACTER/CHAR23.png");
	CHARACTER_LOAD[24] = LoadGraph("DATA/CHARACTER/CHAR24.png");
	CHARACTER_LOAD[25] = LoadGraph("DATA/CHARACTER/CHAR25.png");
	CHARACTER_LOAD[26] = LoadGraph("DATA/CHARACTER/CHAR26.png");
	CHARACTER_LOAD[27] = LoadGraph("DATA/CHARACTER/CHAR27.png");
	CHARACTER_LOAD[28] = LoadGraph("DATA/CHARACTER/CHAR28.png");
	CHARACTER_LOAD[29] = LoadGraph("DATA/CHARACTER/CHAR29.png");
	CHARACTER_LOAD[20] = LoadGraph("DATA/CHARACTER/CHAR30.png");
	CHARACTER_LOAD[31] = LoadGraph("DATA/CHARACTER/CHAR31.png");
	CHARACTER_LOAD[32] = LoadGraph("DATA/CHARACTER/CHAR32.png");
	CHARACTER_LOAD[33] = LoadGraph("DATA/CHARACTER/CHAR33.png");
	CHARACTER_LOAD[34] = LoadGraph("DATA/CHARACTER/CHAR34.png");
	CHARACTER_LOAD[35] = LoadGraph("DATA/CHARACTER/CHAR35.png");
	CHARACTER_LOAD[36] = LoadGraph("DATA/CHARACTER/CHAR36.png");
	CHARACTER_LOAD[37] = LoadGraph("DATA/CHARACTER/CHAR37.png");
	CHARACTER_LOAD[38] = LoadGraph("DATA/CHARACTER/CHAR38.png");
	CHARACTER_LOAD[39] = LoadGraph("DATA/CHARACTER/CHAR39.png");
	CHARACTER_LOAD[40] = LoadGraph("DATA/CHARACTER/CHAR40.png");
	CHARACTER_LOAD[41] = LoadGraph("DATA/CHARACTER/CHAR41.png");
	CHARACTER_LOAD[42] = LoadGraph("DATA/CHARACTER/CHAR42.png");
	CHARACTER_LOAD[43] = LoadGraph("DATA/CHARACTER/CHAR43.png");
	CHARACTER_LOAD[44] = LoadGraph("DATA/CHARACTER/CHAR44.png");
	CHARACTER_LOAD[45] = LoadGraph("DATA/CHARACTER/CHAR45.png");
	CHARACTER_LOAD[46] = LoadGraph("DATA/CHARACTER/CHAR46.png");
	CHARACTER_LOAD[47] = LoadGraph("DATA/CHARACTER/CHAR47.png");
	CHARACTER_LOAD[48] = LoadGraph("DATA/CHARACTER/CHAR48.png");
	CHARACTER_LOAD[49] = LoadGraph("DATA/CHARACTER/CHAR49.png");
	CHARACTER_LOAD[50] = LoadGraph("DATA/CHARACTER/CHAR50.png");
	CHARACTER_LOAD[51] = LoadGraph("DATA/CHARACTER/CHAR51.png");
	CHARACTER_LOAD[52] = LoadGraph("DATA/CHARACTER/CHAR52.png");
	CHARACTER_LOAD[53] = LoadGraph("DATA/CHARACTER/CHAR53.png");
	CHARACTER_LOAD[54] = LoadGraph("DATA/CHARACTER/CHAR54.png");
	CHARACTER_LOAD[55] = LoadGraph("DATA/CHARACTER/CHAR55.png");
	CHARACTER_LOAD[56] = LoadGraph("DATA/CHARACTER/CHAR56.png");
	CHARACTER_LOAD[57] = LoadGraph("DATA/CHARACTER/CHAR57.png");
	CHARACTER_LOAD[58] = LoadGraph("DATA/CHARACTER/CHAR58.png");
	CHARACTER_LOAD[59] = LoadGraph("DATA/CHARACTER/CHAR59.png");
	CHARACTER_LOAD[60] = LoadGraph("DATA/CHARACTER/CHAR60.png");
	CHARACTER_LOAD[61] = LoadGraph("DATA/CHARACTER/CHAR61.png");
	CHARACTER_LOAD[62] = LoadGraph("DATA/CHARACTER/CHAR62.png");
	CHARACTER_LOAD[63] = LoadGraph("DATA/CHARACTER/CHAR63.png");
	CHARACTER_LOAD[64] = LoadGraph("DATA/CHARACTER/CHAR64.png");
	CHARACTER_LOAD[65] = LoadGraph("DATA/CHARACTER/CHAR65.png");
	CHARACTER_LOAD[66] = LoadGraph("DATA/CHARACTER/CHAR66.png");
	CHARACTER_LOAD[67] = LoadGraph("DATA/CHARACTER/CHAR67.png");
	CHARACTER_LOAD[68] = LoadGraph("DATA/CHARACTER/CHAR68.png");
	CHARACTER_LOAD[69] = LoadGraph("DATA/CHARACTER/CHAR69.png");
	CHARACTER_LOAD[70] = LoadGraph("DATA/CHARACTER/CHAR70.png");
	CHARACTER_LOAD[71] = LoadGraph("DATA/CHARACTER/CHAR71.png");
	CHARACTER_LOAD[72] = LoadGraph("DATA/CHARACTER/CHAR72.png");
	CHARACTER_LOAD[73] = LoadGraph("DATA/CHARACTER/CHAR73.png");
	CHARACTER_LOAD[74] = LoadGraph("DATA/CHARACTER/CHAR74.png");
	CHARACTER_LOAD[75] = LoadGraph("DATA/CHARACTER/CHAR75.png");
	CHARACTER_LOAD[76] = LoadGraph("DATA/CHARACTER/CHAR76.png");
	CHARACTER_LOAD[77] = LoadGraph("DATA/CHARACTER/CHAR77.png");
	CHARACTER_LOAD[78] = LoadGraph("DATA/CHARACTER/CHAR78.png");
	CHARACTER_LOAD[79] = LoadGraph("DATA/CHARACTER/CHAR79.png");
	CHARACTER_LOAD[80] = LoadGraph("DATA/CHARACTER/CHAR80.png");
	CHARACTER_LOAD[81] = LoadGraph("DATA/CHARACTER/CHAR81.png");
	CHARACTER_LOAD[82] = LoadGraph("DATA/CHARACTER/CHAR82.png");
	CHARACTER_LOAD[83] = LoadGraph("DATA/CHARACTER/CHAR83.png");
	CHARACTER_LOAD[84] = LoadGraph("DATA/CHARACTER/CHAR84.png");
	CHARACTER_LOAD[85] = LoadGraph("DATA/CHARACTER/CHAR85.png");
	CHARACTER_LOAD[86] = LoadGraph("DATA/CHARACTER/CHAR86.png");
	CHARACTER_LOAD[87] = LoadGraph("DATA/CHARACTER/CHAR87.png");
	CHARACTER_LOAD[88] = LoadGraph("DATA/CHARACTER/CHAR88.png");
	CHARACTER_LOAD[89] = LoadGraph("DATA/CHARACTER/CHAR89.png");
	CHARACTER_LOAD[90] = LoadGraph("DATA/CHARACTER/CHAR90.png");
	CHARACTER_LOAD[91] = LoadGraph("DATA/CHARACTER/CHAR91.png");
	CHARACTER_LOAD[92] = LoadGraph("DATA/CHARACTER/CHAR92.png");
	CHARACTER_LOAD[93] = LoadGraph("DATA/CHARACTER/CHAR93.png");
	CHARACTER_LOAD[94] = LoadGraph("DATA/CHARACTER/CHAR94.png");
	CHARACTER_LOAD[95] = LoadGraph("DATA/CHARACTER/CHAR95.png");
	CHARACTER_LOAD[96] = LoadGraph("DATA/CHARACTER/CHAR96.png");
	CHARACTER_LOAD[97] = LoadGraph("DATA/CHARACTER/CHAR97.png");
	CHARACTER_LOAD[98] = LoadGraph("DATA/CHARACTER/CHAR98.png");
	CHARACTER_LOAD[99] = LoadGraph("DATA/CHARACTER/CHAR99.png");
}

//背景画像読込
void 	MATERIAL_LOAD_BACKGROUND() {

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
	BACKGROUND_LOAD[12] = LoadGraph("DATA/BACKGROUND/BG12.png");
	BACKGROUND_LOAD[13] = LoadGraph("DATA/BACKGROUND/BG13.png");
	BACKGROUND_LOAD[14] = LoadGraph("DATA/BACKGROUND/BG14.png");
	BACKGROUND_LOAD[15] = LoadGraph("DATA/BACKGROUND/BG15.png");
	BACKGROUND_LOAD[16] = LoadGraph("DATA/BACKGROUND/BG16.png");
	BACKGROUND_LOAD[17] = LoadGraph("DATA/BACKGROUND/BG17.png");
	BACKGROUND_LOAD[18] = LoadGraph("DATA/BACKGROUND/BG18.png");
	BACKGROUND_LOAD[19] = LoadGraph("DATA/BACKGROUND/BG19.png");
	BACKGROUND_LOAD[20] = LoadGraph("DATA/BACKGROUND/BG20.png");
	BACKGROUND_LOAD[21] = LoadGraph("DATA/BACKGROUND/BG21.png");
	BACKGROUND_LOAD[22] = LoadGraph("DATA/BACKGROUND/BG22.png");
	BACKGROUND_LOAD[23] = LoadGraph("DATA/BACKGROUND/BG23.png");
	BACKGROUND_LOAD[24] = LoadGraph("DATA/BACKGROUND/BG24.png");
	BACKGROUND_LOAD[25] = LoadGraph("DATA/BACKGROUND/BG25.png");
	BACKGROUND_LOAD[26] = LoadGraph("DATA/BACKGROUND/BG26.png");
	BACKGROUND_LOAD[27] = LoadGraph("DATA/BACKGROUND/BG27.png");
	BACKGROUND_LOAD[28] = LoadGraph("DATA/BACKGROUND/BG28.png");
	BACKGROUND_LOAD[29] = LoadGraph("DATA/BACKGROUND/BG29.png");
	BACKGROUND_LOAD[20] = LoadGraph("DATA/BACKGROUND/BG30.png");
	BACKGROUND_LOAD[31] = LoadGraph("DATA/BACKGROUND/BG31.png");
	BACKGROUND_LOAD[32] = LoadGraph("DATA/BACKGROUND/BG32.png");
	BACKGROUND_LOAD[33] = LoadGraph("DATA/BACKGROUND/BG33.png");
	BACKGROUND_LOAD[34] = LoadGraph("DATA/BACKGROUND/BG34.png");
	BACKGROUND_LOAD[35] = LoadGraph("DATA/BACKGROUND/BG35.png");
	BACKGROUND_LOAD[36] = LoadGraph("DATA/BACKGROUND/BG36.png");
	BACKGROUND_LOAD[37] = LoadGraph("DATA/BACKGROUND/BG37.png");
	BACKGROUND_LOAD[38] = LoadGraph("DATA/BACKGROUND/BG38.png");
	BACKGROUND_LOAD[39] = LoadGraph("DATA/BACKGROUND/BG39.png");
	BACKGROUND_LOAD[40] = LoadGraph("DATA/BACKGROUND/BG40.png");
	BACKGROUND_LOAD[41] = LoadGraph("DATA/BACKGROUND/BG41.png");
	BACKGROUND_LOAD[42] = LoadGraph("DATA/BACKGROUND/BG42.png");
	BACKGROUND_LOAD[43] = LoadGraph("DATA/BACKGROUND/BG43.png");
	BACKGROUND_LOAD[44] = LoadGraph("DATA/BACKGROUND/BG44.png");
	BACKGROUND_LOAD[45] = LoadGraph("DATA/BACKGROUND/BG45.png");
	BACKGROUND_LOAD[46] = LoadGraph("DATA/BACKGROUND/BG46.png");
	BACKGROUND_LOAD[47] = LoadGraph("DATA/BACKGROUND/BG47.png");
	BACKGROUND_LOAD[48] = LoadGraph("DATA/BACKGROUND/BG48.png");
	BACKGROUND_LOAD[49] = LoadGraph("DATA/BACKGROUND/BG49.png");
	BACKGROUND_LOAD[50] = LoadGraph("DATA/BACKGROUND/BG50.png");
	BACKGROUND_LOAD[51] = LoadGraph("DATA/BACKGROUND/BG51.png");
	BACKGROUND_LOAD[52] = LoadGraph("DATA/BACKGROUND/BG52.png");
	BACKGROUND_LOAD[53] = LoadGraph("DATA/BACKGROUND/BG53.png");
	BACKGROUND_LOAD[54] = LoadGraph("DATA/BACKGROUND/BG54.png");
	BACKGROUND_LOAD[55] = LoadGraph("DATA/BACKGROUND/BG55.png");
	BACKGROUND_LOAD[56] = LoadGraph("DATA/BACKGROUND/BG56.png");
	BACKGROUND_LOAD[57] = LoadGraph("DATA/BACKGROUND/BG57.png");
	BACKGROUND_LOAD[58] = LoadGraph("DATA/BACKGROUND/BG58.png");
	BACKGROUND_LOAD[59] = LoadGraph("DATA/BACKGROUND/BG59.png");
	BACKGROUND_LOAD[60] = LoadGraph("DATA/BACKGROUND/BG60.png");
	BACKGROUND_LOAD[61] = LoadGraph("DATA/BACKGROUND/BG61.png");
	BACKGROUND_LOAD[62] = LoadGraph("DATA/BACKGROUND/BG62.png");
	BACKGROUND_LOAD[63] = LoadGraph("DATA/BACKGROUND/BG63.png");
	BACKGROUND_LOAD[64] = LoadGraph("DATA/BACKGROUND/BG64.png");
	BACKGROUND_LOAD[65] = LoadGraph("DATA/BACKGROUND/BG65.png");
	BACKGROUND_LOAD[66] = LoadGraph("DATA/BACKGROUND/BG66.png");
	BACKGROUND_LOAD[67] = LoadGraph("DATA/BACKGROUND/BG67.png");
	BACKGROUND_LOAD[68] = LoadGraph("DATA/BACKGROUND/BG68.png");
	BACKGROUND_LOAD[69] = LoadGraph("DATA/BACKGROUND/BG69.png");
	BACKGROUND_LOAD[70] = LoadGraph("DATA/BACKGROUND/BG70.png");
	BACKGROUND_LOAD[71] = LoadGraph("DATA/BACKGROUND/BG71.png");
	BACKGROUND_LOAD[72] = LoadGraph("DATA/BACKGROUND/BG72.png");
	BACKGROUND_LOAD[73] = LoadGraph("DATA/BACKGROUND/BG73.png");
	BACKGROUND_LOAD[74] = LoadGraph("DATA/BACKGROUND/BG74.png");
	BACKGROUND_LOAD[75] = LoadGraph("DATA/BACKGROUND/BG75.png");
	BACKGROUND_LOAD[76] = LoadGraph("DATA/BACKGROUND/BG76.png");
	BACKGROUND_LOAD[77] = LoadGraph("DATA/BACKGROUND/BG77.png");
	BACKGROUND_LOAD[78] = LoadGraph("DATA/BACKGROUND/BG78.png");
	BACKGROUND_LOAD[79] = LoadGraph("DATA/BACKGROUND/BG79.png");
	BACKGROUND_LOAD[80] = LoadGraph("DATA/BACKGROUND/BG80.png");
	BACKGROUND_LOAD[81] = LoadGraph("DATA/BACKGROUND/BG81.png");
	BACKGROUND_LOAD[82] = LoadGraph("DATA/BACKGROUND/BG82.png");
	BACKGROUND_LOAD[83] = LoadGraph("DATA/BACKGROUND/BG83.png");
	BACKGROUND_LOAD[84] = LoadGraph("DATA/BACKGROUND/BG84.png");
	BACKGROUND_LOAD[85] = LoadGraph("DATA/BACKGROUND/BG85.png");
	BACKGROUND_LOAD[86] = LoadGraph("DATA/BACKGROUND/BG86.png");
	BACKGROUND_LOAD[87] = LoadGraph("DATA/BACKGROUND/BG87.png");
	BACKGROUND_LOAD[88] = LoadGraph("DATA/BACKGROUND/BG88.png");
	BACKGROUND_LOAD[89] = LoadGraph("DATA/BACKGROUND/BG89.png");
	BACKGROUND_LOAD[90] = LoadGraph("DATA/BACKGROUND/BG90.png");
	BACKGROUND_LOAD[91] = LoadGraph("DATA/BACKGROUND/BG91.png");
	BACKGROUND_LOAD[92] = LoadGraph("DATA/BACKGROUND/BG92.png");
	BACKGROUND_LOAD[93] = LoadGraph("DATA/BACKGROUND/BG93.png");
	BACKGROUND_LOAD[94] = LoadGraph("DATA/BACKGROUND/BG94.png");
	BACKGROUND_LOAD[95] = LoadGraph("DATA/BACKGROUND/BG95.png");
	BACKGROUND_LOAD[96] = LoadGraph("DATA/BACKGROUND/BG96.png");
	BACKGROUND_LOAD[97] = LoadGraph("DATA/BACKGROUND/BG97.png");
	BACKGROUND_LOAD[98] = LoadGraph("DATA/BACKGROUND/BG98.png");
	BACKGROUND_LOAD[99] = LoadGraph("DATA/BACKGROUND/BG99.png");
}

//ＢＧＭ読込
void MATERIAL_LOAD_BACKGROUNDMUSIC() {

	BACKGROUNDMUSIC_LOAD[0] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM01.ogg");
	BACKGROUNDMUSIC_LOAD[1] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM02.ogg");
	BACKGROUNDMUSIC_LOAD[2] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM03.ogg");
	BACKGROUNDMUSIC_LOAD[3] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM04.ogg");
	BACKGROUNDMUSIC_LOAD[4] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM05.ogg");
	BACKGROUNDMUSIC_LOAD[5] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM06.ogg");
	BACKGROUNDMUSIC_LOAD[6] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM07.ogg");
	BACKGROUNDMUSIC_LOAD[7] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM08.ogg");
	BACKGROUNDMUSIC_LOAD[8] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM09.ogg");
	BACKGROUNDMUSIC_LOAD[9] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM10.ogg");
	BACKGROUNDMUSIC_LOAD[10] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM11.ogg");
	BACKGROUNDMUSIC_LOAD[12] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM12.ogg");
	BACKGROUNDMUSIC_LOAD[13] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM13.ogg");
	BACKGROUNDMUSIC_LOAD[14] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM14.ogg");
	BACKGROUNDMUSIC_LOAD[15] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM15.ogg");
	BACKGROUNDMUSIC_LOAD[16] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM16.ogg");
	BACKGROUNDMUSIC_LOAD[17] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM17.ogg");
	BACKGROUNDMUSIC_LOAD[18] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM18.ogg");
	BACKGROUNDMUSIC_LOAD[19] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM19.ogg");
	BACKGROUNDMUSIC_LOAD[20] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM20.ogg");
	BACKGROUNDMUSIC_LOAD[21] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM21.ogg");
	BACKGROUNDMUSIC_LOAD[22] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM22.ogg");
	BACKGROUNDMUSIC_LOAD[23] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM23.ogg");
	BACKGROUNDMUSIC_LOAD[24] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM24.ogg");
	BACKGROUNDMUSIC_LOAD[25] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM25.ogg");
	BACKGROUNDMUSIC_LOAD[26] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM26.ogg");
	BACKGROUNDMUSIC_LOAD[27] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM27.ogg");
	BACKGROUNDMUSIC_LOAD[28] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM28.ogg");
	BACKGROUNDMUSIC_LOAD[29] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM29.ogg");
	BACKGROUNDMUSIC_LOAD[20] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM30.ogg");
	BACKGROUNDMUSIC_LOAD[31] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM31.ogg");
	BACKGROUNDMUSIC_LOAD[32] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM32.ogg");
	BACKGROUNDMUSIC_LOAD[33] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM33.ogg");
	BACKGROUNDMUSIC_LOAD[34] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM34.ogg");
	BACKGROUNDMUSIC_LOAD[35] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM35.ogg");
	BACKGROUNDMUSIC_LOAD[36] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM36.ogg");
	BACKGROUNDMUSIC_LOAD[37] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM37.ogg");
	BACKGROUNDMUSIC_LOAD[38] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM38.ogg");
	BACKGROUNDMUSIC_LOAD[39] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM39.ogg");
	BACKGROUNDMUSIC_LOAD[40] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM40.ogg");
	BACKGROUNDMUSIC_LOAD[41] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM41.ogg");
	BACKGROUNDMUSIC_LOAD[42] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM42.ogg");
	BACKGROUNDMUSIC_LOAD[43] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM43.ogg");
	BACKGROUNDMUSIC_LOAD[44] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM44.ogg");
	BACKGROUNDMUSIC_LOAD[45] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM45.ogg");
	BACKGROUNDMUSIC_LOAD[46] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM46.ogg");
	BACKGROUNDMUSIC_LOAD[47] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM47.ogg");
	BACKGROUNDMUSIC_LOAD[48] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM48.ogg");
	BACKGROUNDMUSIC_LOAD[49] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM49.ogg");
	BACKGROUNDMUSIC_LOAD[50] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM50.ogg");
	BACKGROUNDMUSIC_LOAD[51] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM51.ogg");
	BACKGROUNDMUSIC_LOAD[52] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM52.ogg");
	BACKGROUNDMUSIC_LOAD[53] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM53.ogg");
	BACKGROUNDMUSIC_LOAD[54] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM54.ogg");
	BACKGROUNDMUSIC_LOAD[55] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM55.ogg");
	BACKGROUNDMUSIC_LOAD[56] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM56.ogg");
	BACKGROUNDMUSIC_LOAD[57] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM57.ogg");
	BACKGROUNDMUSIC_LOAD[58] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM58.ogg");
	BACKGROUNDMUSIC_LOAD[59] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM59.ogg");
	BACKGROUNDMUSIC_LOAD[60] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM60.ogg");
	BACKGROUNDMUSIC_LOAD[61] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM61.ogg");
	BACKGROUNDMUSIC_LOAD[62] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM62.ogg");
	BACKGROUNDMUSIC_LOAD[63] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM63.ogg");
	BACKGROUNDMUSIC_LOAD[64] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM64.ogg");
	BACKGROUNDMUSIC_LOAD[65] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM65.ogg");
	BACKGROUNDMUSIC_LOAD[66] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM66.ogg");
	BACKGROUNDMUSIC_LOAD[67] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM67.ogg");
	BACKGROUNDMUSIC_LOAD[68] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM68.ogg");
	BACKGROUNDMUSIC_LOAD[69] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM69.ogg");
	BACKGROUNDMUSIC_LOAD[70] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM70.ogg");
	BACKGROUNDMUSIC_LOAD[71] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM71.ogg");
	BACKGROUNDMUSIC_LOAD[72] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM72.ogg");
	BACKGROUNDMUSIC_LOAD[73] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM73.ogg");
	BACKGROUNDMUSIC_LOAD[74] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM74.ogg");
	BACKGROUNDMUSIC_LOAD[75] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM75.ogg");
	BACKGROUNDMUSIC_LOAD[76] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM76.ogg");
	BACKGROUNDMUSIC_LOAD[77] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM77.ogg");
	BACKGROUNDMUSIC_LOAD[78] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM78.ogg");
	BACKGROUNDMUSIC_LOAD[79] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM79.ogg");
	BACKGROUNDMUSIC_LOAD[80] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM80.ogg");
	BACKGROUNDMUSIC_LOAD[81] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM81.ogg");
	BACKGROUNDMUSIC_LOAD[82] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM82.ogg");
	BACKGROUNDMUSIC_LOAD[83] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM83.ogg");
	BACKGROUNDMUSIC_LOAD[84] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM84.ogg");
	BACKGROUNDMUSIC_LOAD[85] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM85.ogg");
	BACKGROUNDMUSIC_LOAD[86] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM86.ogg");
	BACKGROUNDMUSIC_LOAD[87] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM87.ogg");
	BACKGROUNDMUSIC_LOAD[88] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM88.ogg");
	BACKGROUNDMUSIC_LOAD[89] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM89.ogg");
	BACKGROUNDMUSIC_LOAD[90] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM90.ogg");
	BACKGROUNDMUSIC_LOAD[91] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM91.ogg");
	BACKGROUNDMUSIC_LOAD[92] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM92.ogg");
	BACKGROUNDMUSIC_LOAD[93] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM93.ogg");
	BACKGROUNDMUSIC_LOAD[94] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM94.ogg");
	BACKGROUNDMUSIC_LOAD[95] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM95.ogg");
	BACKGROUNDMUSIC_LOAD[96] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM96.ogg");
	BACKGROUNDMUSIC_LOAD[97] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM97.ogg");
	BACKGROUNDMUSIC_LOAD[98] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM98.ogg");
	BACKGROUNDMUSIC_LOAD[99] = LoadGraph("DATA/BACKGROUNDMUSIC/BGM99.ogg");
}

//ＳＥ読込
void MATERIAL_LOAD_SOUNDEFFECT(){

	SOUNDEFFECT_LOAD[0] = LoadGraph("DATA/SOUNDEFFECT/SE01.ogg");
	SOUNDEFFECT_LOAD[1] = LoadGraph("DATA/SOUNDEFFECT/SE02.ogg");
	SOUNDEFFECT_LOAD[2] = LoadGraph("DATA/SOUNDEFFECT/SE03.ogg");
	SOUNDEFFECT_LOAD[3] = LoadGraph("DATA/SOUNDEFFECT/SE04.ogg");
	SOUNDEFFECT_LOAD[4] = LoadGraph("DATA/SOUNDEFFECT/SE05.ogg");
	SOUNDEFFECT_LOAD[5] = LoadGraph("DATA/SOUNDEFFECT/SE06.ogg");
	SOUNDEFFECT_LOAD[6] = LoadGraph("DATA/SOUNDEFFECT/SE07.ogg");
	SOUNDEFFECT_LOAD[7] = LoadGraph("DATA/SOUNDEFFECT/SE08.ogg");
	SOUNDEFFECT_LOAD[8] = LoadGraph("DATA/SOUNDEFFECT/SE09.ogg");
	SOUNDEFFECT_LOAD[9] = LoadGraph("DATA/SOUNDEFFECT/SE10.ogg");
	SOUNDEFFECT_LOAD[10] = LoadGraph("DATA/SOUNDEFFECT/SE11.ogg");
	SOUNDEFFECT_LOAD[12] = LoadGraph("DATA/SOUNDEFFECT/SE12.ogg");
	SOUNDEFFECT_LOAD[13] = LoadGraph("DATA/SOUNDEFFECT/SE13.ogg");
	SOUNDEFFECT_LOAD[14] = LoadGraph("DATA/SOUNDEFFECT/SE14.ogg");
	SOUNDEFFECT_LOAD[15] = LoadGraph("DATA/SOUNDEFFECT/SE15.ogg");
	SOUNDEFFECT_LOAD[16] = LoadGraph("DATA/SOUNDEFFECT/SE16.ogg");
	SOUNDEFFECT_LOAD[17] = LoadGraph("DATA/SOUNDEFFECT/SE17.ogg");
	SOUNDEFFECT_LOAD[18] = LoadGraph("DATA/SOUNDEFFECT/SE18.ogg");
	SOUNDEFFECT_LOAD[19] = LoadGraph("DATA/SOUNDEFFECT/SE19.ogg");
	SOUNDEFFECT_LOAD[20] = LoadGraph("DATA/SOUNDEFFECT/SE20.ogg");
	SOUNDEFFECT_LOAD[21] = LoadGraph("DATA/SOUNDEFFECT/SE21.ogg");
	SOUNDEFFECT_LOAD[22] = LoadGraph("DATA/SOUNDEFFECT/SE22.ogg");
	SOUNDEFFECT_LOAD[23] = LoadGraph("DATA/SOUNDEFFECT/SE23.ogg");
	SOUNDEFFECT_LOAD[24] = LoadGraph("DATA/SOUNDEFFECT/SE24.ogg");
	SOUNDEFFECT_LOAD[25] = LoadGraph("DATA/SOUNDEFFECT/SE25.ogg");
	SOUNDEFFECT_LOAD[26] = LoadGraph("DATA/SOUNDEFFECT/SE26.ogg");
	SOUNDEFFECT_LOAD[27] = LoadGraph("DATA/SOUNDEFFECT/SE27.ogg");
	SOUNDEFFECT_LOAD[28] = LoadGraph("DATA/SOUNDEFFECT/SE28.ogg");
	SOUNDEFFECT_LOAD[29] = LoadGraph("DATA/SOUNDEFFECT/SE29.ogg");
	SOUNDEFFECT_LOAD[20] = LoadGraph("DATA/SOUNDEFFECT/SE30.ogg");
	SOUNDEFFECT_LOAD[31] = LoadGraph("DATA/SOUNDEFFECT/SE31.ogg");
	SOUNDEFFECT_LOAD[32] = LoadGraph("DATA/SOUNDEFFECT/SE32.ogg");
	SOUNDEFFECT_LOAD[33] = LoadGraph("DATA/SOUNDEFFECT/SE33.ogg");
	SOUNDEFFECT_LOAD[34] = LoadGraph("DATA/SOUNDEFFECT/SE34.ogg");
	SOUNDEFFECT_LOAD[35] = LoadGraph("DATA/SOUNDEFFECT/SE35.ogg");
	SOUNDEFFECT_LOAD[36] = LoadGraph("DATA/SOUNDEFFECT/SE36.ogg");
	SOUNDEFFECT_LOAD[37] = LoadGraph("DATA/SOUNDEFFECT/SE37.ogg");
	SOUNDEFFECT_LOAD[38] = LoadGraph("DATA/SOUNDEFFECT/SE38.ogg");
	SOUNDEFFECT_LOAD[39] = LoadGraph("DATA/SOUNDEFFECT/SE39.ogg");
	SOUNDEFFECT_LOAD[40] = LoadGraph("DATA/SOUNDEFFECT/SE40.ogg");
	SOUNDEFFECT_LOAD[41] = LoadGraph("DATA/SOUNDEFFECT/SE41.ogg");
	SOUNDEFFECT_LOAD[42] = LoadGraph("DATA/SOUNDEFFECT/SE42.ogg");
	SOUNDEFFECT_LOAD[43] = LoadGraph("DATA/SOUNDEFFECT/SE43.ogg");
	SOUNDEFFECT_LOAD[44] = LoadGraph("DATA/SOUNDEFFECT/SE44.ogg");
	SOUNDEFFECT_LOAD[45] = LoadGraph("DATA/SOUNDEFFECT/SE45.ogg");
	SOUNDEFFECT_LOAD[46] = LoadGraph("DATA/SOUNDEFFECT/SE46.ogg");
	SOUNDEFFECT_LOAD[47] = LoadGraph("DATA/SOUNDEFFECT/SE47.ogg");
	SOUNDEFFECT_LOAD[48] = LoadGraph("DATA/SOUNDEFFECT/SE48.ogg");
	SOUNDEFFECT_LOAD[49] = LoadGraph("DATA/SOUNDEFFECT/SE49.ogg");
	SOUNDEFFECT_LOAD[50] = LoadGraph("DATA/SOUNDEFFECT/SE50.ogg");
	SOUNDEFFECT_LOAD[51] = LoadGraph("DATA/SOUNDEFFECT/SE51.ogg");
	SOUNDEFFECT_LOAD[52] = LoadGraph("DATA/SOUNDEFFECT/SE52.ogg");
	SOUNDEFFECT_LOAD[53] = LoadGraph("DATA/SOUNDEFFECT/SE53.ogg");
	SOUNDEFFECT_LOAD[54] = LoadGraph("DATA/SOUNDEFFECT/SE54.ogg");
	SOUNDEFFECT_LOAD[55] = LoadGraph("DATA/SOUNDEFFECT/SE55.ogg");
	SOUNDEFFECT_LOAD[56] = LoadGraph("DATA/SOUNDEFFECT/SE56.ogg");
	SOUNDEFFECT_LOAD[57] = LoadGraph("DATA/SOUNDEFFECT/SE57.ogg");
	SOUNDEFFECT_LOAD[58] = LoadGraph("DATA/SOUNDEFFECT/SE58.ogg");
	SOUNDEFFECT_LOAD[59] = LoadGraph("DATA/SOUNDEFFECT/SE59.ogg");
	SOUNDEFFECT_LOAD[60] = LoadGraph("DATA/SOUNDEFFECT/SE60.ogg");
	SOUNDEFFECT_LOAD[61] = LoadGraph("DATA/SOUNDEFFECT/SE61.ogg");
	SOUNDEFFECT_LOAD[62] = LoadGraph("DATA/SOUNDEFFECT/SE62.ogg");
	SOUNDEFFECT_LOAD[63] = LoadGraph("DATA/SOUNDEFFECT/SE63.ogg");
	SOUNDEFFECT_LOAD[64] = LoadGraph("DATA/SOUNDEFFECT/SE64.ogg");
	SOUNDEFFECT_LOAD[65] = LoadGraph("DATA/SOUNDEFFECT/SE65.ogg");
	SOUNDEFFECT_LOAD[66] = LoadGraph("DATA/SOUNDEFFECT/SE66.ogg");
	SOUNDEFFECT_LOAD[67] = LoadGraph("DATA/SOUNDEFFECT/SE67.ogg");
	SOUNDEFFECT_LOAD[68] = LoadGraph("DATA/SOUNDEFFECT/SE68.ogg");
	SOUNDEFFECT_LOAD[69] = LoadGraph("DATA/SOUNDEFFECT/SE69.ogg");
	SOUNDEFFECT_LOAD[70] = LoadGraph("DATA/SOUNDEFFECT/SE70.ogg");
	SOUNDEFFECT_LOAD[71] = LoadGraph("DATA/SOUNDEFFECT/SE71.ogg");
	SOUNDEFFECT_LOAD[72] = LoadGraph("DATA/SOUNDEFFECT/SE72.ogg");
	SOUNDEFFECT_LOAD[73] = LoadGraph("DATA/SOUNDEFFECT/SE73.ogg");
	SOUNDEFFECT_LOAD[74] = LoadGraph("DATA/SOUNDEFFECT/SE74.ogg");
	SOUNDEFFECT_LOAD[75] = LoadGraph("DATA/SOUNDEFFECT/SE75.ogg");
	SOUNDEFFECT_LOAD[76] = LoadGraph("DATA/SOUNDEFFECT/SE76.ogg");
	SOUNDEFFECT_LOAD[77] = LoadGraph("DATA/SOUNDEFFECT/SE77.ogg");
	SOUNDEFFECT_LOAD[78] = LoadGraph("DATA/SOUNDEFFECT/SE78.ogg");
	SOUNDEFFECT_LOAD[79] = LoadGraph("DATA/SOUNDEFFECT/SE79.ogg");
	SOUNDEFFECT_LOAD[80] = LoadGraph("DATA/SOUNDEFFECT/SE80.ogg");
	SOUNDEFFECT_LOAD[81] = LoadGraph("DATA/SOUNDEFFECT/SE81.ogg");
	SOUNDEFFECT_LOAD[82] = LoadGraph("DATA/SOUNDEFFECT/SE82.ogg");
	SOUNDEFFECT_LOAD[83] = LoadGraph("DATA/SOUNDEFFECT/SE83.ogg");
	SOUNDEFFECT_LOAD[84] = LoadGraph("DATA/SOUNDEFFECT/SE84.ogg");
	SOUNDEFFECT_LOAD[85] = LoadGraph("DATA/SOUNDEFFECT/SE85.ogg");
	SOUNDEFFECT_LOAD[86] = LoadGraph("DATA/SOUNDEFFECT/SE86.ogg");
	SOUNDEFFECT_LOAD[87] = LoadGraph("DATA/SOUNDEFFECT/SE87.ogg");
	SOUNDEFFECT_LOAD[88] = LoadGraph("DATA/SOUNDEFFECT/SE88.ogg");
	SOUNDEFFECT_LOAD[89] = LoadGraph("DATA/SOUNDEFFECT/SE89.ogg");
	SOUNDEFFECT_LOAD[90] = LoadGraph("DATA/SOUNDEFFECT/SE90.ogg");
	SOUNDEFFECT_LOAD[91] = LoadGraph("DATA/SOUNDEFFECT/SE91.ogg");
	SOUNDEFFECT_LOAD[92] = LoadGraph("DATA/SOUNDEFFECT/SE92.ogg");
	SOUNDEFFECT_LOAD[93] = LoadGraph("DATA/SOUNDEFFECT/SE93.ogg");
	SOUNDEFFECT_LOAD[94] = LoadGraph("DATA/SOUNDEFFECT/SE94.ogg");
	SOUNDEFFECT_LOAD[95] = LoadGraph("DATA/SOUNDEFFECT/SE95.ogg");
	SOUNDEFFECT_LOAD[96] = LoadGraph("DATA/SOUNDEFFECT/SE96.ogg");
	SOUNDEFFECT_LOAD[97] = LoadGraph("DATA/SOUNDEFFECT/SE97.ogg");
	SOUNDEFFECT_LOAD[98] = LoadGraph("DATA/SOUNDEFFECT/SE98.ogg");
	SOUNDEFFECT_LOAD[99] = LoadGraph("DATA/SOUNDEFFECT/SE99.ogg");
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
		SAVE = MessageBox(
			NULL,
			"戻りますか？",
			"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
			MB_YESNO
			);

		if (SAVE == IDYES) {

			ClearDrawScreen();
			GAME_y = GAMEMENU_y;
			Config = 0;
		}
	}
}

//コンフィグ(メッセージ)
void CONFIG_MESSAGE() {

	SAVE = MessageBox(
		NULL,
		"設定を変更しますか？",
		"ノベルゲームエンジン「LINKS」",
		MB_YESNO
	);
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

			//画面に戻る
			if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				SAVE = MessageBox(
					NULL,
					"戻りますか？",
					"ノベルゲームエンジン「LINKS」",
					MB_YESNO
				);

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

			//戻る
			if (SAVE_y == (SAVE_Y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (SAVE_Y * 4) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

					SAVE = MessageBox(
						NULL,
						"戻りますか？",
						"ノベルゲームエンジン「LINKS」",
						MB_YESNO
					);

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
				"戻りますか？",
				"ノベルゲームエンジン「LINKS」",
				MB_YESNO
			);

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

	//ショートカットキー時の事後処理
	SHORTCUT_KEY_DRAW();
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

				//ショートカットキー時の事後処理
				SHORTCUT_KEY_DRAW();
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

		//キャラクター描画処理
	case 'C':

		CP++;

		switch (String[SP][CP]) {

		case '0':

			CP++;

			switch (String[SP][CP])
			{
			case '1':
				
				//キャラ01読込
				CHARACTER = CHARACTER_LOAD[0];
				CP++;
				break;

			case '2':

				//キャラ02読込
				CHARACTER = CHARACTER_LOAD[1];
				CP++;
				break;

			case '3':

				//キャラ03読込
				CHARACTER = CHARACTER_LOAD[2];
				CP++;
				break;

			case '4':

				//キャラ04読込
				CHARACTER = CHARACTER_LOAD[3];
				CP++;
				break;

			case '5':

				//キャラ05読込
				CHARACTER = CHARACTER_LOAD[4];
				CP++;
				break;

			case '6':

				//キャラ06読込
				CHARACTER = CHARACTER_LOAD[5];
				CP++;
				break;

			case '7':

				//キャラ07読込
				CHARACTER = CHARACTER_LOAD[6];
				CP++;
				break;

			case '8':

				//キャラ08読込
				CHARACTER = CHARACTER_LOAD[7];
				CP++;
				break;

			case '9':

				//キャラ09読込
				CHARACTER = CHARACTER_LOAD[8];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		case '1':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ10読込
				CHARACTER = CHARACTER_LOAD[9];
				CP++;
				break;

			case '1':

				//キャラ11読込
				CHARACTER = CHARACTER_LOAD[10];
				CP++;
				break;

			case '2':

				//キャラ12読込
				CHARACTER = CHARACTER_LOAD[11];
				CP++;
				break;

			case '3':

				//キャラ13読込
				CHARACTER = CHARACTER_LOAD[12];
				CP++;
				break;

			case '4':

				//キャラ14読込
				CHARACTER = CHARACTER_LOAD[13];
				CP++;
				break;

			case '5':

				//キャラ15読込
				CHARACTER = CHARACTER_LOAD[14];
				CP++;
				break;

			case '6':

				//キャラ16読込
				CHARACTER = CHARACTER_LOAD[15];
				CP++;
				break;

			case '7':

				//キャラ17読込
				CHARACTER = CHARACTER_LOAD[16];
				CP++;
				break;

			case '8':

				//キャラ18読込
				CHARACTER = CHARACTER_LOAD[17];
				CP++;
				break;

			case '9':

				//キャラ19読込
				CHARACTER = CHARACTER_LOAD[18];
				CP++;
				break;
			}
			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '2':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ20読込
				CHARACTER = CHARACTER_LOAD[19];
				CP++;
				break;

			case '1':

				//キャラ21読込
				CHARACTER = CHARACTER_LOAD[20];
				CP++;
				break;

			case '2':

				//キャラ22読込
				CHARACTER = CHARACTER_LOAD[21];
				CP++;
				break;

			case '3':

				//キャラ23読込
				CHARACTER = CHARACTER_LOAD[22];
				CP++;
				break;

			case '4':

				//キャラ24読込
				CHARACTER = CHARACTER_LOAD[23];
				CP++;
				break;

			case '5':

				//キャラ25読込
				CHARACTER = CHARACTER_LOAD[24];
				CP++;
				break;

			case '6':

				//キャラ26読込
				CHARACTER = CHARACTER_LOAD[25];
				CP++;
				break;

			case '7':

				//キャラ27読込
				CHARACTER = CHARACTER_LOAD[26];
				CP++;
				break;

			case '8':

				//キャラ28読込
				CHARACTER = CHARACTER_LOAD[27];
				CP++;
				break;

			case '9':

				//キャラ29読込
				CHARACTER = CHARACTER_LOAD[28];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '3':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ30読込
				CHARACTER = CHARACTER_LOAD[29];
				CP++;
				break;

			case '1':

				//キャラ31読込
				CHARACTER = CHARACTER_LOAD[30];
				CP++;
				break;

			case '2':

				//キャラ32読込
				CHARACTER = CHARACTER_LOAD[31];
				CP++;
				break;

			case '3':

				//キャラ33読込
				CHARACTER = CHARACTER_LOAD[32];
				CP++;
				break;

			case '4':

				//キャラ34読込
				CHARACTER = CHARACTER_LOAD[33];
				CP++;
				break;

			case '5':

				//キャラ35読込
				CHARACTER = CHARACTER_LOAD[34];
				CP++;
				break;

			case '6':

				//キャラ36読込
				CHARACTER = CHARACTER_LOAD[35];
				CP++;
				break;

			case '7':

				//キャラ37読込
				CHARACTER = CHARACTER_LOAD[36];
				CP++;
				break;

			case '8':

				//キャラ38読込
				CHARACTER = CHARACTER_LOAD[37];
				CP++;
				break;

			case '9':

				//キャラ39読込
				CHARACTER = CHARACTER_LOAD[38];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '4':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ40読込
				CHARACTER = CHARACTER_LOAD[39];
				CP++;
				break;

			case '1':

				//キャラ41読込
				CHARACTER = CHARACTER_LOAD[40];
				CP++;
				break;

			case '2':

				//キャラ42読込
				CHARACTER = CHARACTER_LOAD[41];
				CP++;
				break;

			case '3':

				//キャラ43読込
				CHARACTER = CHARACTER_LOAD[42];
				CP++;
				break;

			case '4':

				//キャラ44読込
				CHARACTER = CHARACTER_LOAD[43];
				CP++;
				break;

			case '5':

				//キャラ45読込
				CHARACTER = CHARACTER_LOAD[44];
				CP++;
				break;

			case '6':

				//キャラ46読込
				CHARACTER = CHARACTER_LOAD[45];
				CP++;
				break;

			case '7':

				//キャラ47読込
				CHARACTER = CHARACTER_LOAD[46];
				CP++;
				break;

			case '8':

				//キャラ48読込
				CHARACTER = CHARACTER_LOAD[47];
				CP++;
				break;

			case '9':

				//キャラ49読込
				CHARACTER = CHARACTER_LOAD[48];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '5':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ50読込
				CHARACTER = CHARACTER_LOAD[49];
				CP++;
				break;

			case '1':

				//キャラ51読込
				CHARACTER = CHARACTER_LOAD[50];
				CP++;
				break;

			case '2':

				//キャラ52読込
				CHARACTER = CHARACTER_LOAD[51];
				CP++;
				break;

			case '3':

				//キャラ53読込
				CHARACTER = CHARACTER_LOAD[52];
				CP++;
				break;

			case '4':

				//キャラ54読込
				CHARACTER = CHARACTER_LOAD[53];
				CP++;
				break;

			case '5':

				//キャラ55読込
				CHARACTER = CHARACTER_LOAD[54];
				CP++;
				break;

			case '6':

				//キャラ56読込
				CHARACTER = CHARACTER_LOAD[55];
				CP++;
				break;

			case '7':

				//キャラ57読込
				CHARACTER = CHARACTER_LOAD[56];
				CP++;
				break;

			case '8':

				//キャラ58読込
				CHARACTER = CHARACTER_LOAD[57];
				CP++;
				break;

			case '9':

				//キャラ59読込
				CHARACTER = CHARACTER_LOAD[58];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '6':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ60読込
				CHARACTER = CHARACTER_LOAD[59];
				CP++;
				break;

			case '1':

				//キャラ61読込
				CHARACTER = CHARACTER_LOAD[60];
				CP++;
				break;

			case '2':

				//キャラ62読込
				CHARACTER = CHARACTER_LOAD[61];
				CP++;
				break;

			case '3':

				//キャラ63読込
				CHARACTER = CHARACTER_LOAD[62];
				CP++;
				break;

			case '4':

				//キャラ64読込
				CHARACTER = CHARACTER_LOAD[63];
				CP++;
				break;

			case '5':

				//キャラ65読込
				CHARACTER = CHARACTER_LOAD[64];
				CP++;
				break;

			case '6':

				//キャラ66読込
				CHARACTER = CHARACTER_LOAD[65];
				CP++;
				break;

			case '7':

				//キャラ67読込
				CHARACTER = CHARACTER_LOAD[66];
				CP++;
				break;

			case '8':

				//キャラ68読込
				CHARACTER = CHARACTER_LOAD[67];
				CP++;
				break;

			case '9':

				//キャラ69読込
				CHARACTER = CHARACTER_LOAD[68];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '7':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ70読込
				CHARACTER = CHARACTER_LOAD[70];
				CP++;
				break;

			case '1':

				//キャラ71読込
				CHARACTER = CHARACTER_LOAD[70];
				CP++;
				break;

			case '2':

				//キャラ72読込
				CHARACTER = CHARACTER_LOAD[71];
				CP++;
				break;

			case '3':

				//キャラ73読込
				CHARACTER = CHARACTER_LOAD[72];
				CP++;
				break;

			case '4':

				//キャラ74読込
				CHARACTER = CHARACTER_LOAD[73];
				CP++;
				break;

			case '5':

				//キャラ75読込
				CHARACTER = CHARACTER_LOAD[74];
				CP++;
				break;

			case '6':

				//キャラ76読込
				CHARACTER = CHARACTER_LOAD[75];
				CP++;
				break;

			case '7':

				//キャラ77読込
				CHARACTER = CHARACTER_LOAD[76];
				CP++;
				break;

			case '8':

				//キャラ78読込
				CHARACTER = CHARACTER_LOAD[77];
				CP++;
				break;

			case '9':

				//キャラ79読込
				CHARACTER = CHARACTER_LOAD[78];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '8':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ80読込
				CHARACTER = CHARACTER_LOAD[79];
				CP++;
				break;

			case '1':

				//キャラ81読込
				CHARACTER = CHARACTER_LOAD[80];
				CP++;
				break;

			case '2':

				//キャラ82読込
				CHARACTER = CHARACTER_LOAD[81];
				CP++;
				break;

			case '3':

				//キャラ83読込
				CHARACTER = CHARACTER_LOAD[82];
				CP++;
				break;

			case '4':

				//キャラ84読込
				CHARACTER = CHARACTER_LOAD[83];
				CP++;
				break;

			case '5':

				//キャラ85読込
				CHARACTER = CHARACTER_LOAD[84];
				CP++;
				break;

			case '6':

				//キャラ86読込
				CHARACTER = CHARACTER_LOAD[85];
				CP++;
				break;

			case '7':

				//キャラ87読込
				CHARACTER = CHARACTER_LOAD[86];
				CP++;
				break;

			case '8':

				//キャラ88読込
				CHARACTER = CHARACTER_LOAD[87];
				CP++;
				break;

			case '9':

				//キャラ89読込
				CHARACTER = CHARACTER_LOAD[88];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '9':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ90読込
				CHARACTER = CHARACTER_LOAD[89];
				CP++;
				break;

			case '1':

				//キャラ91読込
				CHARACTER = CHARACTER_LOAD[90];
				CP++;
				break;

			case '2':

				//キャラ92読込
				CHARACTER = CHARACTER_LOAD[91];
				CP++;
				break;

			case '3':

				//キャラ93読込
				CHARACTER = CHARACTER_LOAD[92];
				CP++;
				break;

			case '4':

				//キャラ94読込
				CHARACTER = CHARACTER_LOAD[93];
				CP++;
				break;

			case '5':

				//キャラ95読込
				CHARACTER = CHARACTER_LOAD[94];
				CP++;
				break;

			case '6':

				//キャラ96読込
				CHARACTER = CHARACTER_LOAD[95];
				CP++;
				break;

			case '7':

				//キャラ97読込
				CHARACTER = CHARACTER_LOAD[96];
				CP++;
				break;

			case '8':

				//キャラ98読込
				CHARACTER = CHARACTER_LOAD[97];
				CP++;
				break;

			case '9':

				//キャラ99読込
				CHARACTER = CHARACTER_LOAD[98];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		}
		break;

		//背景描画処理
	case 'B':

		CP++;

		switch (String[SP][CP]) {

		case '0':

			CP++;

			switch (String[SP][CP])
			{
			case '1':

				//キャラ01読込
				CHARACTER = CHARACTER_LOAD[0];
				CP++;
				break;

			case '2':

				//キャラ02読込
				CHARACTER = CHARACTER_LOAD[1];
				CP++;
				break;

			case '3':

				//キャラ03読込
				CHARACTER = CHARACTER_LOAD[2];
				CP++;
				break;

			case '4':

				//キャラ04読込
				CHARACTER = CHARACTER_LOAD[3];
				CP++;
				break;

			case '5':

				//キャラ05読込
				CHARACTER = CHARACTER_LOAD[4];
				CP++;
				break;

			case '6':

				//キャラ06読込
				CHARACTER = CHARACTER_LOAD[5];
				CP++;
				break;

			case '7':

				//キャラ07読込
				CHARACTER = CHARACTER_LOAD[6];
				CP++;
				break;

			case '8':

				//キャラ08読込
				CHARACTER = CHARACTER_LOAD[7];
				CP++;
				break;

			case '9':

				//キャラ09読込
				CHARACTER = CHARACTER_LOAD[8];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '1':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ10読込
				CHARACTER = CHARACTER_LOAD[9];
				CP++;
				break;

			case '1':

				//キャラ11読込
				CHARACTER = CHARACTER_LOAD[10];
				CP++;
				break;

			case '2':

				//キャラ12読込
				CHARACTER = CHARACTER_LOAD[11];
				CP++;
				break;

			case '3':

				//キャラ13読込
				CHARACTER = CHARACTER_LOAD[12];
				CP++;
				break;

			case '4':

				//キャラ14読込
				CHARACTER = CHARACTER_LOAD[13];
				CP++;
				break;

			case '5':

				//キャラ15読込
				CHARACTER = CHARACTER_LOAD[14];
				CP++;
				break;

			case '6':

				//キャラ16読込
				CHARACTER = CHARACTER_LOAD[15];
				CP++;
				break;

			case '7':

				//キャラ17読込
				CHARACTER = CHARACTER_LOAD[16];
				CP++;
				break;

			case '8':

				//キャラ18読込
				CHARACTER = CHARACTER_LOAD[17];
				CP++;
				break;

			case '9':

				//キャラ19読込
				CHARACTER = CHARACTER_LOAD[18];
				CP++;
				break;
			}
			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '2':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ20読込
				CHARACTER = CHARACTER_LOAD[19];
				CP++;
				break;

			case '1':

				//キャラ21読込
				CHARACTER = CHARACTER_LOAD[20];
				CP++;
				break;

			case '2':

				//キャラ22読込
				CHARACTER = CHARACTER_LOAD[21];
				CP++;
				break;

			case '3':

				//キャラ23読込
				CHARACTER = CHARACTER_LOAD[22];
				CP++;
				break;

			case '4':

				//キャラ24読込
				CHARACTER = CHARACTER_LOAD[23];
				CP++;
				break;

			case '5':

				//キャラ25読込
				CHARACTER = CHARACTER_LOAD[24];
				CP++;
				break;

			case '6':

				//キャラ26読込
				CHARACTER = CHARACTER_LOAD[25];
				CP++;
				break;

			case '7':

				//キャラ27読込
				CHARACTER = CHARACTER_LOAD[26];
				CP++;
				break;

			case '8':

				//キャラ28読込
				CHARACTER = CHARACTER_LOAD[27];
				CP++;
				break;

			case '9':

				//キャラ29読込
				CHARACTER = CHARACTER_LOAD[28];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '3':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ30読込
				CHARACTER = CHARACTER_LOAD[29];
				CP++;
				break;

			case '1':

				//キャラ31読込
				CHARACTER = CHARACTER_LOAD[30];
				CP++;
				break;

			case '2':

				//キャラ32読込
				CHARACTER = CHARACTER_LOAD[31];
				CP++;
				break;

			case '3':

				//キャラ33読込
				CHARACTER = CHARACTER_LOAD[32];
				CP++;
				break;

			case '4':

				//キャラ34読込
				CHARACTER = CHARACTER_LOAD[33];
				CP++;
				break;

			case '5':

				//キャラ35読込
				CHARACTER = CHARACTER_LOAD[34];
				CP++;
				break;

			case '6':

				//キャラ36読込
				CHARACTER = CHARACTER_LOAD[35];
				CP++;
				break;

			case '7':

				//キャラ37読込
				CHARACTER = CHARACTER_LOAD[36];
				CP++;
				break;

			case '8':

				//キャラ38読込
				CHARACTER = CHARACTER_LOAD[37];
				CP++;
				break;

			case '9':

				//キャラ39読込
				CHARACTER = CHARACTER_LOAD[38];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '4':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ40読込
				CHARACTER = CHARACTER_LOAD[39];
				CP++;
				break;

			case '1':

				//キャラ41読込
				CHARACTER = CHARACTER_LOAD[40];
				CP++;
				break;

			case '2':

				//キャラ42読込
				CHARACTER = CHARACTER_LOAD[41];
				CP++;
				break;

			case '3':

				//キャラ43読込
				CHARACTER = CHARACTER_LOAD[42];
				CP++;
				break;

			case '4':

				//キャラ44読込
				CHARACTER = CHARACTER_LOAD[43];
				CP++;
				break;

			case '5':

				//キャラ45読込
				CHARACTER = CHARACTER_LOAD[44];
				CP++;
				break;

			case '6':

				//キャラ46読込
				CHARACTER = CHARACTER_LOAD[45];
				CP++;
				break;

			case '7':

				//キャラ47読込
				CHARACTER = CHARACTER_LOAD[46];
				CP++;
				break;

			case '8':

				//キャラ48読込
				CHARACTER = CHARACTER_LOAD[47];
				CP++;
				break;

			case '9':

				//キャラ49読込
				CHARACTER = CHARACTER_LOAD[48];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '5':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ50読込
				CHARACTER = CHARACTER_LOAD[49];
				CP++;
				break;

			case '1':

				//キャラ51読込
				CHARACTER = CHARACTER_LOAD[50];
				CP++;
				break;

			case '2':

				//キャラ52読込
				CHARACTER = CHARACTER_LOAD[51];
				CP++;
				break;

			case '3':

				//キャラ53読込
				CHARACTER = CHARACTER_LOAD[52];
				CP++;
				break;

			case '4':

				//キャラ54読込
				CHARACTER = CHARACTER_LOAD[53];
				CP++;
				break;

			case '5':

				//キャラ55読込
				CHARACTER = CHARACTER_LOAD[54];
				CP++;
				break;

			case '6':

				//キャラ56読込
				CHARACTER = CHARACTER_LOAD[55];
				CP++;
				break;

			case '7':

				//キャラ57読込
				CHARACTER = CHARACTER_LOAD[56];
				CP++;
				break;

			case '8':

				//キャラ58読込
				CHARACTER = CHARACTER_LOAD[57];
				CP++;
				break;

			case '9':

				//キャラ59読込
				CHARACTER = CHARACTER_LOAD[58];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '6':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ60読込
				CHARACTER = CHARACTER_LOAD[59];
				CP++;
				break;

			case '1':

				//キャラ61読込
				CHARACTER = CHARACTER_LOAD[60];
				CP++;
				break;

			case '2':

				//キャラ62読込
				CHARACTER = CHARACTER_LOAD[61];
				CP++;
				break;

			case '3':

				//キャラ63読込
				CHARACTER = CHARACTER_LOAD[62];
				CP++;
				break;

			case '4':

				//キャラ64読込
				CHARACTER = CHARACTER_LOAD[63];
				CP++;
				break;

			case '5':

				//キャラ65読込
				CHARACTER = CHARACTER_LOAD[64];
				CP++;
				break;

			case '6':

				//キャラ66読込
				CHARACTER = CHARACTER_LOAD[65];
				CP++;
				break;

			case '7':

				//キャラ67読込
				CHARACTER = CHARACTER_LOAD[66];
				CP++;
				break;

			case '8':

				//キャラ68読込
				CHARACTER = CHARACTER_LOAD[67];
				CP++;
				break;

			case '9':

				//キャラ69読込
				CHARACTER = CHARACTER_LOAD[68];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '7':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ70読込
				CHARACTER = CHARACTER_LOAD[70];
				CP++;
				break;

			case '1':

				//キャラ71読込
				CHARACTER = CHARACTER_LOAD[70];
				CP++;
				break;

			case '2':

				//キャラ72読込
				CHARACTER = CHARACTER_LOAD[71];
				CP++;
				break;

			case '3':

				//キャラ73読込
				CHARACTER = CHARACTER_LOAD[72];
				CP++;
				break;

			case '4':

				//キャラ74読込
				CHARACTER = CHARACTER_LOAD[73];
				CP++;
				break;

			case '5':

				//キャラ75読込
				CHARACTER = CHARACTER_LOAD[74];
				CP++;
				break;

			case '6':

				//キャラ76読込
				CHARACTER = CHARACTER_LOAD[75];
				CP++;
				break;

			case '7':

				//キャラ77読込
				CHARACTER = CHARACTER_LOAD[76];
				CP++;
				break;

			case '8':

				//キャラ78読込
				CHARACTER = CHARACTER_LOAD[77];
				CP++;
				break;

			case '9':

				//キャラ79読込
				CHARACTER = CHARACTER_LOAD[78];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '8':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ80読込
				CHARACTER = CHARACTER_LOAD[79];
				CP++;
				break;

			case '1':

				//キャラ81読込
				CHARACTER = CHARACTER_LOAD[80];
				CP++;
				break;

			case '2':

				//キャラ82読込
				CHARACTER = CHARACTER_LOAD[81];
				CP++;
				break;

			case '3':

				//キャラ83読込
				CHARACTER = CHARACTER_LOAD[82];
				CP++;
				break;

			case '4':

				//キャラ84読込
				CHARACTER = CHARACTER_LOAD[83];
				CP++;
				break;

			case '5':

				//キャラ85読込
				CHARACTER = CHARACTER_LOAD[84];
				CP++;
				break;

			case '6':

				//キャラ86読込
				CHARACTER = CHARACTER_LOAD[85];
				CP++;
				break;

			case '7':

				//キャラ87読込
				CHARACTER = CHARACTER_LOAD[86];
				CP++;
				break;

			case '8':

				//キャラ88読込
				CHARACTER = CHARACTER_LOAD[87];
				CP++;
				break;

			case '9':

				//キャラ89読込
				CHARACTER = CHARACTER_LOAD[88];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '9':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ90読込
				CHARACTER = CHARACTER_LOAD[89];
				CP++;
				break;

			case '1':

				//キャラ91読込
				CHARACTER = CHARACTER_LOAD[90];
				CP++;
				break;

			case '2':

				//キャラ92読込
				CHARACTER = CHARACTER_LOAD[91];
				CP++;
				break;

			case '3':

				//キャラ93読込
				CHARACTER = CHARACTER_LOAD[92];
				CP++;
				break;

			case '4':

				//キャラ94読込
				CHARACTER = CHARACTER_LOAD[93];
				CP++;
				break;

			case '5':

				//キャラ95読込
				CHARACTER = CHARACTER_LOAD[94];
				CP++;
				break;

			case '6':

				//キャラ96読込
				CHARACTER = CHARACTER_LOAD[95];
				CP++;
				break;

			case '7':

				//キャラ97読込
				CHARACTER = CHARACTER_LOAD[96];
				CP++;
				break;

			case '8':

				//キャラ98読込
				CHARACTER = CHARACTER_LOAD[97];
				CP++;
				break;

			case '9':

				//キャラ99読込
				CHARACTER = CHARACTER_LOAD[98];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		}
		break;

		//BGM再生処理
	case 'M':

		CP++;

		switch (String[SP][CP]) {

		case '0':

			CP++;

			switch (String[SP][CP])
			{
			case '1':

				//キャラ01読込
				CHARACTER = CHARACTER_LOAD[0];
				CP++;
				break;

			case '2':

				//キャラ02読込
				CHARACTER = CHARACTER_LOAD[1];
				CP++;
				break;

			case '3':

				//キャラ03読込
				CHARACTER = CHARACTER_LOAD[2];
				CP++;
				break;

			case '4':

				//キャラ04読込
				CHARACTER = CHARACTER_LOAD[3];
				CP++;
				break;

			case '5':

				//キャラ05読込
				CHARACTER = CHARACTER_LOAD[4];
				CP++;
				break;

			case '6':

				//キャラ06読込
				CHARACTER = CHARACTER_LOAD[5];
				CP++;
				break;

			case '7':

				//キャラ07読込
				CHARACTER = CHARACTER_LOAD[6];
				CP++;
				break;

			case '8':

				//キャラ08読込
				CHARACTER = CHARACTER_LOAD[7];
				CP++;
				break;

			case '9':

				//キャラ09読込
				CHARACTER = CHARACTER_LOAD[8];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '1':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ10読込
				CHARACTER = CHARACTER_LOAD[9];
				CP++;
				break;

			case '1':

				//キャラ11読込
				CHARACTER = CHARACTER_LOAD[10];
				CP++;
				break;

			case '2':

				//キャラ12読込
				CHARACTER = CHARACTER_LOAD[11];
				CP++;
				break;

			case '3':

				//キャラ13読込
				CHARACTER = CHARACTER_LOAD[12];
				CP++;
				break;

			case '4':

				//キャラ14読込
				CHARACTER = CHARACTER_LOAD[13];
				CP++;
				break;

			case '5':

				//キャラ15読込
				CHARACTER = CHARACTER_LOAD[14];
				CP++;
				break;

			case '6':

				//キャラ16読込
				CHARACTER = CHARACTER_LOAD[15];
				CP++;
				break;

			case '7':

				//キャラ17読込
				CHARACTER = CHARACTER_LOAD[16];
				CP++;
				break;

			case '8':

				//キャラ18読込
				CHARACTER = CHARACTER_LOAD[17];
				CP++;
				break;

			case '9':

				//キャラ19読込
				CHARACTER = CHARACTER_LOAD[18];
				CP++;
				break;
			}
			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '2':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ20読込
				CHARACTER = CHARACTER_LOAD[19];
				CP++;
				break;

			case '1':

				//キャラ21読込
				CHARACTER = CHARACTER_LOAD[20];
				CP++;
				break;

			case '2':

				//キャラ22読込
				CHARACTER = CHARACTER_LOAD[21];
				CP++;
				break;

			case '3':

				//キャラ23読込
				CHARACTER = CHARACTER_LOAD[22];
				CP++;
				break;

			case '4':

				//キャラ24読込
				CHARACTER = CHARACTER_LOAD[23];
				CP++;
				break;

			case '5':

				//キャラ25読込
				CHARACTER = CHARACTER_LOAD[24];
				CP++;
				break;

			case '6':

				//キャラ26読込
				CHARACTER = CHARACTER_LOAD[25];
				CP++;
				break;

			case '7':

				//キャラ27読込
				CHARACTER = CHARACTER_LOAD[26];
				CP++;
				break;

			case '8':

				//キャラ28読込
				CHARACTER = CHARACTER_LOAD[27];
				CP++;
				break;

			case '9':

				//キャラ29読込
				CHARACTER = CHARACTER_LOAD[28];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '3':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ30読込
				CHARACTER = CHARACTER_LOAD[29];
				CP++;
				break;

			case '1':

				//キャラ31読込
				CHARACTER = CHARACTER_LOAD[30];
				CP++;
				break;

			case '2':

				//キャラ32読込
				CHARACTER = CHARACTER_LOAD[31];
				CP++;
				break;

			case '3':

				//キャラ33読込
				CHARACTER = CHARACTER_LOAD[32];
				CP++;
				break;

			case '4':

				//キャラ34読込
				CHARACTER = CHARACTER_LOAD[33];
				CP++;
				break;

			case '5':

				//キャラ35読込
				CHARACTER = CHARACTER_LOAD[34];
				CP++;
				break;

			case '6':

				//キャラ36読込
				CHARACTER = CHARACTER_LOAD[35];
				CP++;
				break;

			case '7':

				//キャラ37読込
				CHARACTER = CHARACTER_LOAD[36];
				CP++;
				break;

			case '8':

				//キャラ38読込
				CHARACTER = CHARACTER_LOAD[37];
				CP++;
				break;

			case '9':

				//キャラ39読込
				CHARACTER = CHARACTER_LOAD[38];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '4':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ40読込
				CHARACTER = CHARACTER_LOAD[39];
				CP++;
				break;

			case '1':

				//キャラ41読込
				CHARACTER = CHARACTER_LOAD[40];
				CP++;
				break;

			case '2':

				//キャラ42読込
				CHARACTER = CHARACTER_LOAD[41];
				CP++;
				break;

			case '3':

				//キャラ43読込
				CHARACTER = CHARACTER_LOAD[42];
				CP++;
				break;

			case '4':

				//キャラ44読込
				CHARACTER = CHARACTER_LOAD[43];
				CP++;
				break;

			case '5':

				//キャラ45読込
				CHARACTER = CHARACTER_LOAD[44];
				CP++;
				break;

			case '6':

				//キャラ46読込
				CHARACTER = CHARACTER_LOAD[45];
				CP++;
				break;

			case '7':

				//キャラ47読込
				CHARACTER = CHARACTER_LOAD[46];
				CP++;
				break;

			case '8':

				//キャラ48読込
				CHARACTER = CHARACTER_LOAD[47];
				CP++;
				break;

			case '9':

				//キャラ49読込
				CHARACTER = CHARACTER_LOAD[48];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '5':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ50読込
				CHARACTER = CHARACTER_LOAD[49];
				CP++;
				break;

			case '1':

				//キャラ51読込
				CHARACTER = CHARACTER_LOAD[50];
				CP++;
				break;

			case '2':

				//キャラ52読込
				CHARACTER = CHARACTER_LOAD[51];
				CP++;
				break;

			case '3':

				//キャラ53読込
				CHARACTER = CHARACTER_LOAD[52];
				CP++;
				break;

			case '4':

				//キャラ54読込
				CHARACTER = CHARACTER_LOAD[53];
				CP++;
				break;

			case '5':

				//キャラ55読込
				CHARACTER = CHARACTER_LOAD[54];
				CP++;
				break;

			case '6':

				//キャラ56読込
				CHARACTER = CHARACTER_LOAD[55];
				CP++;
				break;

			case '7':

				//キャラ57読込
				CHARACTER = CHARACTER_LOAD[56];
				CP++;
				break;

			case '8':

				//キャラ58読込
				CHARACTER = CHARACTER_LOAD[57];
				CP++;
				break;

			case '9':

				//キャラ59読込
				CHARACTER = CHARACTER_LOAD[58];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '6':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ60読込
				CHARACTER = CHARACTER_LOAD[59];
				CP++;
				break;

			case '1':

				//キャラ61読込
				CHARACTER = CHARACTER_LOAD[60];
				CP++;
				break;

			case '2':

				//キャラ62読込
				CHARACTER = CHARACTER_LOAD[61];
				CP++;
				break;

			case '3':

				//キャラ63読込
				CHARACTER = CHARACTER_LOAD[62];
				CP++;
				break;

			case '4':

				//キャラ64読込
				CHARACTER = CHARACTER_LOAD[63];
				CP++;
				break;

			case '5':

				//キャラ65読込
				CHARACTER = CHARACTER_LOAD[64];
				CP++;
				break;

			case '6':

				//キャラ66読込
				CHARACTER = CHARACTER_LOAD[65];
				CP++;
				break;

			case '7':

				//キャラ67読込
				CHARACTER = CHARACTER_LOAD[66];
				CP++;
				break;

			case '8':

				//キャラ68読込
				CHARACTER = CHARACTER_LOAD[67];
				CP++;
				break;

			case '9':

				//キャラ69読込
				CHARACTER = CHARACTER_LOAD[68];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '7':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ70読込
				CHARACTER = CHARACTER_LOAD[70];
				CP++;
				break;

			case '1':

				//キャラ71読込
				CHARACTER = CHARACTER_LOAD[70];
				CP++;
				break;

			case '2':

				//キャラ72読込
				CHARACTER = CHARACTER_LOAD[71];
				CP++;
				break;

			case '3':

				//キャラ73読込
				CHARACTER = CHARACTER_LOAD[72];
				CP++;
				break;

			case '4':

				//キャラ74読込
				CHARACTER = CHARACTER_LOAD[73];
				CP++;
				break;

			case '5':

				//キャラ75読込
				CHARACTER = CHARACTER_LOAD[74];
				CP++;
				break;

			case '6':

				//キャラ76読込
				CHARACTER = CHARACTER_LOAD[75];
				CP++;
				break;

			case '7':

				//キャラ77読込
				CHARACTER = CHARACTER_LOAD[76];
				CP++;
				break;

			case '8':

				//キャラ78読込
				CHARACTER = CHARACTER_LOAD[77];
				CP++;
				break;

			case '9':

				//キャラ79読込
				CHARACTER = CHARACTER_LOAD[78];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '8':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ80読込
				CHARACTER = CHARACTER_LOAD[79];
				CP++;
				break;

			case '1':

				//キャラ81読込
				CHARACTER = CHARACTER_LOAD[80];
				CP++;
				break;

			case '2':

				//キャラ82読込
				CHARACTER = CHARACTER_LOAD[81];
				CP++;
				break;

			case '3':

				//キャラ83読込
				CHARACTER = CHARACTER_LOAD[82];
				CP++;
				break;

			case '4':

				//キャラ84読込
				CHARACTER = CHARACTER_LOAD[83];
				CP++;
				break;

			case '5':

				//キャラ85読込
				CHARACTER = CHARACTER_LOAD[84];
				CP++;
				break;

			case '6':

				//キャラ86読込
				CHARACTER = CHARACTER_LOAD[85];
				CP++;
				break;

			case '7':

				//キャラ87読込
				CHARACTER = CHARACTER_LOAD[86];
				CP++;
				break;

			case '8':

				//キャラ88読込
				CHARACTER = CHARACTER_LOAD[87];
				CP++;
				break;

			case '9':

				//キャラ89読込
				CHARACTER = CHARACTER_LOAD[88];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '9':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ90読込
				CHARACTER = CHARACTER_LOAD[89];
				CP++;
				break;

			case '1':

				//キャラ91読込
				CHARACTER = CHARACTER_LOAD[90];
				CP++;
				break;

			case '2':

				//キャラ92読込
				CHARACTER = CHARACTER_LOAD[91];
				CP++;
				break;

			case '3':

				//キャラ93読込
				CHARACTER = CHARACTER_LOAD[92];
				CP++;
				break;

			case '4':

				//キャラ94読込
				CHARACTER = CHARACTER_LOAD[93];
				CP++;
				break;

			case '5':

				//キャラ95読込
				CHARACTER = CHARACTER_LOAD[94];
				CP++;
				break;

			case '6':

				//キャラ96読込
				CHARACTER = CHARACTER_LOAD[95];
				CP++;
				break;

			case '7':

				//キャラ97読込
				CHARACTER = CHARACTER_LOAD[96];
				CP++;
				break;

			case '8':

				//キャラ98読込
				CHARACTER = CHARACTER_LOAD[97];
				CP++;
				break;

			case '9':

				//キャラ99読込
				CHARACTER = CHARACTER_LOAD[98];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		}
		break;

		//SE再生処理
	case 'S':

		CP++;

		switch (String[SP][CP]) {

		case '0':

			CP++;

			switch (String[SP][CP])
			{
			case '1':

				//キャラ01読込
				CHARACTER = CHARACTER_LOAD[0];
				CP++;
				break;

			case '2':

				//キャラ02読込
				CHARACTER = CHARACTER_LOAD[1];
				CP++;
				break;

			case '3':

				//キャラ03読込
				CHARACTER = CHARACTER_LOAD[2];
				CP++;
				break;

			case '4':

				//キャラ04読込
				CHARACTER = CHARACTER_LOAD[3];
				CP++;
				break;

			case '5':

				//キャラ05読込
				CHARACTER = CHARACTER_LOAD[4];
				CP++;
				break;

			case '6':

				//キャラ06読込
				CHARACTER = CHARACTER_LOAD[5];
				CP++;
				break;

			case '7':

				//キャラ07読込
				CHARACTER = CHARACTER_LOAD[6];
				CP++;
				break;

			case '8':

				//キャラ08読込
				CHARACTER = CHARACTER_LOAD[7];
				CP++;
				break;

			case '9':

				//キャラ09読込
				CHARACTER = CHARACTER_LOAD[8];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '1':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ10読込
				CHARACTER = CHARACTER_LOAD[9];
				CP++;
				break;

			case '1':

				//キャラ11読込
				CHARACTER = CHARACTER_LOAD[10];
				CP++;
				break;

			case '2':

				//キャラ12読込
				CHARACTER = CHARACTER_LOAD[11];
				CP++;
				break;

			case '3':

				//キャラ13読込
				CHARACTER = CHARACTER_LOAD[12];
				CP++;
				break;

			case '4':

				//キャラ14読込
				CHARACTER = CHARACTER_LOAD[13];
				CP++;
				break;

			case '5':

				//キャラ15読込
				CHARACTER = CHARACTER_LOAD[14];
				CP++;
				break;

			case '6':

				//キャラ16読込
				CHARACTER = CHARACTER_LOAD[15];
				CP++;
				break;

			case '7':

				//キャラ17読込
				CHARACTER = CHARACTER_LOAD[16];
				CP++;
				break;

			case '8':

				//キャラ18読込
				CHARACTER = CHARACTER_LOAD[17];
				CP++;
				break;

			case '9':

				//キャラ19読込
				CHARACTER = CHARACTER_LOAD[18];
				CP++;
				break;
			}
			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '2':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ20読込
				CHARACTER = CHARACTER_LOAD[19];
				CP++;
				break;

			case '1':

				//キャラ21読込
				CHARACTER = CHARACTER_LOAD[20];
				CP++;
				break;

			case '2':

				//キャラ22読込
				CHARACTER = CHARACTER_LOAD[21];
				CP++;
				break;

			case '3':

				//キャラ23読込
				CHARACTER = CHARACTER_LOAD[22];
				CP++;
				break;

			case '4':

				//キャラ24読込
				CHARACTER = CHARACTER_LOAD[23];
				CP++;
				break;

			case '5':

				//キャラ25読込
				CHARACTER = CHARACTER_LOAD[24];
				CP++;
				break;

			case '6':

				//キャラ26読込
				CHARACTER = CHARACTER_LOAD[25];
				CP++;
				break;

			case '7':

				//キャラ27読込
				CHARACTER = CHARACTER_LOAD[26];
				CP++;
				break;

			case '8':

				//キャラ28読込
				CHARACTER = CHARACTER_LOAD[27];
				CP++;
				break;

			case '9':

				//キャラ29読込
				CHARACTER = CHARACTER_LOAD[28];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '3':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ30読込
				CHARACTER = CHARACTER_LOAD[29];
				CP++;
				break;

			case '1':

				//キャラ31読込
				CHARACTER = CHARACTER_LOAD[30];
				CP++;
				break;

			case '2':

				//キャラ32読込
				CHARACTER = CHARACTER_LOAD[31];
				CP++;
				break;

			case '3':

				//キャラ33読込
				CHARACTER = CHARACTER_LOAD[32];
				CP++;
				break;

			case '4':

				//キャラ34読込
				CHARACTER = CHARACTER_LOAD[33];
				CP++;
				break;

			case '5':

				//キャラ35読込
				CHARACTER = CHARACTER_LOAD[34];
				CP++;
				break;

			case '6':

				//キャラ36読込
				CHARACTER = CHARACTER_LOAD[35];
				CP++;
				break;

			case '7':

				//キャラ37読込
				CHARACTER = CHARACTER_LOAD[36];
				CP++;
				break;

			case '8':

				//キャラ38読込
				CHARACTER = CHARACTER_LOAD[37];
				CP++;
				break;

			case '9':

				//キャラ39読込
				CHARACTER = CHARACTER_LOAD[38];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '4':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ40読込
				CHARACTER = CHARACTER_LOAD[39];
				CP++;
				break;

			case '1':

				//キャラ41読込
				CHARACTER = CHARACTER_LOAD[40];
				CP++;
				break;

			case '2':

				//キャラ42読込
				CHARACTER = CHARACTER_LOAD[41];
				CP++;
				break;

			case '3':

				//キャラ43読込
				CHARACTER = CHARACTER_LOAD[42];
				CP++;
				break;

			case '4':

				//キャラ44読込
				CHARACTER = CHARACTER_LOAD[43];
				CP++;
				break;

			case '5':

				//キャラ45読込
				CHARACTER = CHARACTER_LOAD[44];
				CP++;
				break;

			case '6':

				//キャラ46読込
				CHARACTER = CHARACTER_LOAD[45];
				CP++;
				break;

			case '7':

				//キャラ47読込
				CHARACTER = CHARACTER_LOAD[46];
				CP++;
				break;

			case '8':

				//キャラ48読込
				CHARACTER = CHARACTER_LOAD[47];
				CP++;
				break;

			case '9':

				//キャラ49読込
				CHARACTER = CHARACTER_LOAD[48];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '5':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ50読込
				CHARACTER = CHARACTER_LOAD[49];
				CP++;
				break;

			case '1':

				//キャラ51読込
				CHARACTER = CHARACTER_LOAD[50];
				CP++;
				break;

			case '2':

				//キャラ52読込
				CHARACTER = CHARACTER_LOAD[51];
				CP++;
				break;

			case '3':

				//キャラ53読込
				CHARACTER = CHARACTER_LOAD[52];
				CP++;
				break;

			case '4':

				//キャラ54読込
				CHARACTER = CHARACTER_LOAD[53];
				CP++;
				break;

			case '5':

				//キャラ55読込
				CHARACTER = CHARACTER_LOAD[54];
				CP++;
				break;

			case '6':

				//キャラ56読込
				CHARACTER = CHARACTER_LOAD[55];
				CP++;
				break;

			case '7':

				//キャラ57読込
				CHARACTER = CHARACTER_LOAD[56];
				CP++;
				break;

			case '8':

				//キャラ58読込
				CHARACTER = CHARACTER_LOAD[57];
				CP++;
				break;

			case '9':

				//キャラ59読込
				CHARACTER = CHARACTER_LOAD[58];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '6':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ60読込
				CHARACTER = CHARACTER_LOAD[59];
				CP++;
				break;

			case '1':

				//キャラ61読込
				CHARACTER = CHARACTER_LOAD[60];
				CP++;
				break;

			case '2':

				//キャラ62読込
				CHARACTER = CHARACTER_LOAD[61];
				CP++;
				break;

			case '3':

				//キャラ63読込
				CHARACTER = CHARACTER_LOAD[62];
				CP++;
				break;

			case '4':

				//キャラ64読込
				CHARACTER = CHARACTER_LOAD[63];
				CP++;
				break;

			case '5':

				//キャラ65読込
				CHARACTER = CHARACTER_LOAD[64];
				CP++;
				break;

			case '6':

				//キャラ66読込
				CHARACTER = CHARACTER_LOAD[65];
				CP++;
				break;

			case '7':

				//キャラ67読込
				CHARACTER = CHARACTER_LOAD[66];
				CP++;
				break;

			case '8':

				//キャラ68読込
				CHARACTER = CHARACTER_LOAD[67];
				CP++;
				break;

			case '9':

				//キャラ69読込
				CHARACTER = CHARACTER_LOAD[68];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '7':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ70読込
				CHARACTER = CHARACTER_LOAD[70];
				CP++;
				break;

			case '1':

				//キャラ71読込
				CHARACTER = CHARACTER_LOAD[70];
				CP++;
				break;

			case '2':

				//キャラ72読込
				CHARACTER = CHARACTER_LOAD[71];
				CP++;
				break;

			case '3':

				//キャラ73読込
				CHARACTER = CHARACTER_LOAD[72];
				CP++;
				break;

			case '4':

				//キャラ74読込
				CHARACTER = CHARACTER_LOAD[73];
				CP++;
				break;

			case '5':

				//キャラ75読込
				CHARACTER = CHARACTER_LOAD[74];
				CP++;
				break;

			case '6':

				//キャラ76読込
				CHARACTER = CHARACTER_LOAD[75];
				CP++;
				break;

			case '7':

				//キャラ77読込
				CHARACTER = CHARACTER_LOAD[76];
				CP++;
				break;

			case '8':

				//キャラ78読込
				CHARACTER = CHARACTER_LOAD[77];
				CP++;
				break;

			case '9':

				//キャラ79読込
				CHARACTER = CHARACTER_LOAD[78];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '8':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ80読込
				CHARACTER = CHARACTER_LOAD[79];
				CP++;
				break;

			case '1':

				//キャラ81読込
				CHARACTER = CHARACTER_LOAD[80];
				CP++;
				break;

			case '2':

				//キャラ82読込
				CHARACTER = CHARACTER_LOAD[81];
				CP++;
				break;

			case '3':

				//キャラ83読込
				CHARACTER = CHARACTER_LOAD[82];
				CP++;
				break;

			case '4':

				//キャラ84読込
				CHARACTER = CHARACTER_LOAD[83];
				CP++;
				break;

			case '5':

				//キャラ85読込
				CHARACTER = CHARACTER_LOAD[84];
				CP++;
				break;

			case '6':

				//キャラ86読込
				CHARACTER = CHARACTER_LOAD[85];
				CP++;
				break;

			case '7':

				//キャラ87読込
				CHARACTER = CHARACTER_LOAD[86];
				CP++;
				break;

			case '8':

				//キャラ88読込
				CHARACTER = CHARACTER_LOAD[87];
				CP++;
				break;

			case '9':

				//キャラ89読込
				CHARACTER = CHARACTER_LOAD[88];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '9':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ90読込
				CHARACTER = CHARACTER_LOAD[89];
				CP++;
				break;

			case '1':

				//キャラ91読込
				CHARACTER = CHARACTER_LOAD[90];
				CP++;
				break;

			case '2':

				//キャラ92読込
				CHARACTER = CHARACTER_LOAD[91];
				CP++;
				break;

			case '3':

				//キャラ93読込
				CHARACTER = CHARACTER_LOAD[92];
				CP++;
				break;

			case '4':

				//キャラ94読込
				CHARACTER = CHARACTER_LOAD[93];
				CP++;
				break;

			case '5':

				//キャラ95読込
				CHARACTER = CHARACTER_LOAD[94];
				CP++;
				break;

			case '6':

				//キャラ96読込
				CHARACTER = CHARACTER_LOAD[95];
				CP++;
				break;

			case '7':

				//キャラ97読込
				CHARACTER = CHARACTER_LOAD[96];
				CP++;
				break;

			case '8':

				//キャラ98読込
				CHARACTER = CHARACTER_LOAD[97];
				CP++;
				break;

			case '9':

				//キャラ99読込
				CHARACTER = CHARACTER_LOAD[98];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		}
		break;

		//ムービー再生処理
	case 'V':

		CP++;

		switch (String[SP][CP]) {

		case '0':

			CP++;

			switch (String[SP][CP])
			{
			case '1':

				//キャラ01読込
				CHARACTER = CHARACTER_LOAD[0];
				CP++;
				break;

			case '2':

				//キャラ02読込
				CHARACTER = CHARACTER_LOAD[1];
				CP++;
				break;

			case '3':

				//キャラ03読込
				CHARACTER = CHARACTER_LOAD[2];
				CP++;
				break;

			case '4':

				//キャラ04読込
				CHARACTER = CHARACTER_LOAD[3];
				CP++;
				break;

			case '5':

				//キャラ05読込
				CHARACTER = CHARACTER_LOAD[4];
				CP++;
				break;

			case '6':

				//キャラ06読込
				CHARACTER = CHARACTER_LOAD[5];
				CP++;
				break;

			case '7':

				//キャラ07読込
				CHARACTER = CHARACTER_LOAD[6];
				CP++;
				break;

			case '8':

				//キャラ08読込
				CHARACTER = CHARACTER_LOAD[7];
				CP++;
				break;

			case '9':

				//キャラ09読込
				CHARACTER = CHARACTER_LOAD[8];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '1':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ10読込
				CHARACTER = CHARACTER_LOAD[9];
				CP++;
				break;

			case '1':

				//キャラ11読込
				CHARACTER = CHARACTER_LOAD[10];
				CP++;
				break;

			case '2':

				//キャラ12読込
				CHARACTER = CHARACTER_LOAD[11];
				CP++;
				break;

			case '3':

				//キャラ13読込
				CHARACTER = CHARACTER_LOAD[12];
				CP++;
				break;

			case '4':

				//キャラ14読込
				CHARACTER = CHARACTER_LOAD[13];
				CP++;
				break;

			case '5':

				//キャラ15読込
				CHARACTER = CHARACTER_LOAD[14];
				CP++;
				break;

			case '6':

				//キャラ16読込
				CHARACTER = CHARACTER_LOAD[15];
				CP++;
				break;

			case '7':

				//キャラ17読込
				CHARACTER = CHARACTER_LOAD[16];
				CP++;
				break;

			case '8':

				//キャラ18読込
				CHARACTER = CHARACTER_LOAD[17];
				CP++;
				break;

			case '9':

				//キャラ19読込
				CHARACTER = CHARACTER_LOAD[18];
				CP++;
				break;
			}
			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '2':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ20読込
				CHARACTER = CHARACTER_LOAD[19];
				CP++;
				break;

			case '1':

				//キャラ21読込
				CHARACTER = CHARACTER_LOAD[20];
				CP++;
				break;

			case '2':

				//キャラ22読込
				CHARACTER = CHARACTER_LOAD[21];
				CP++;
				break;

			case '3':

				//キャラ23読込
				CHARACTER = CHARACTER_LOAD[22];
				CP++;
				break;

			case '4':

				//キャラ24読込
				CHARACTER = CHARACTER_LOAD[23];
				CP++;
				break;

			case '5':

				//キャラ25読込
				CHARACTER = CHARACTER_LOAD[24];
				CP++;
				break;

			case '6':

				//キャラ26読込
				CHARACTER = CHARACTER_LOAD[25];
				CP++;
				break;

			case '7':

				//キャラ27読込
				CHARACTER = CHARACTER_LOAD[26];
				CP++;
				break;

			case '8':

				//キャラ28読込
				CHARACTER = CHARACTER_LOAD[27];
				CP++;
				break;

			case '9':

				//キャラ29読込
				CHARACTER = CHARACTER_LOAD[28];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '3':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ30読込
				CHARACTER = CHARACTER_LOAD[29];
				CP++;
				break;

			case '1':

				//キャラ31読込
				CHARACTER = CHARACTER_LOAD[30];
				CP++;
				break;

			case '2':

				//キャラ32読込
				CHARACTER = CHARACTER_LOAD[31];
				CP++;
				break;

			case '3':

				//キャラ33読込
				CHARACTER = CHARACTER_LOAD[32];
				CP++;
				break;

			case '4':

				//キャラ34読込
				CHARACTER = CHARACTER_LOAD[33];
				CP++;
				break;

			case '5':

				//キャラ35読込
				CHARACTER = CHARACTER_LOAD[34];
				CP++;
				break;

			case '6':

				//キャラ36読込
				CHARACTER = CHARACTER_LOAD[35];
				CP++;
				break;

			case '7':

				//キャラ37読込
				CHARACTER = CHARACTER_LOAD[36];
				CP++;
				break;

			case '8':

				//キャラ38読込
				CHARACTER = CHARACTER_LOAD[37];
				CP++;
				break;

			case '9':

				//キャラ39読込
				CHARACTER = CHARACTER_LOAD[38];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '4':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ40読込
				CHARACTER = CHARACTER_LOAD[39];
				CP++;
				break;

			case '1':

				//キャラ41読込
				CHARACTER = CHARACTER_LOAD[40];
				CP++;
				break;

			case '2':

				//キャラ42読込
				CHARACTER = CHARACTER_LOAD[41];
				CP++;
				break;

			case '3':

				//キャラ43読込
				CHARACTER = CHARACTER_LOAD[42];
				CP++;
				break;

			case '4':

				//キャラ44読込
				CHARACTER = CHARACTER_LOAD[43];
				CP++;
				break;

			case '5':

				//キャラ45読込
				CHARACTER = CHARACTER_LOAD[44];
				CP++;
				break;

			case '6':

				//キャラ46読込
				CHARACTER = CHARACTER_LOAD[45];
				CP++;
				break;

			case '7':

				//キャラ47読込
				CHARACTER = CHARACTER_LOAD[46];
				CP++;
				break;

			case '8':

				//キャラ48読込
				CHARACTER = CHARACTER_LOAD[47];
				CP++;
				break;

			case '9':

				//キャラ49読込
				CHARACTER = CHARACTER_LOAD[48];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '5':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ50読込
				CHARACTER = CHARACTER_LOAD[49];
				CP++;
				break;

			case '1':

				//キャラ51読込
				CHARACTER = CHARACTER_LOAD[50];
				CP++;
				break;

			case '2':

				//キャラ52読込
				CHARACTER = CHARACTER_LOAD[51];
				CP++;
				break;

			case '3':

				//キャラ53読込
				CHARACTER = CHARACTER_LOAD[52];
				CP++;
				break;

			case '4':

				//キャラ54読込
				CHARACTER = CHARACTER_LOAD[53];
				CP++;
				break;

			case '5':

				//キャラ55読込
				CHARACTER = CHARACTER_LOAD[54];
				CP++;
				break;

			case '6':

				//キャラ56読込
				CHARACTER = CHARACTER_LOAD[55];
				CP++;
				break;

			case '7':

				//キャラ57読込
				CHARACTER = CHARACTER_LOAD[56];
				CP++;
				break;

			case '8':

				//キャラ58読込
				CHARACTER = CHARACTER_LOAD[57];
				CP++;
				break;

			case '9':

				//キャラ59読込
				CHARACTER = CHARACTER_LOAD[58];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '6':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ60読込
				CHARACTER = CHARACTER_LOAD[59];
				CP++;
				break;

			case '1':

				//キャラ61読込
				CHARACTER = CHARACTER_LOAD[60];
				CP++;
				break;

			case '2':

				//キャラ62読込
				CHARACTER = CHARACTER_LOAD[61];
				CP++;
				break;

			case '3':

				//キャラ63読込
				CHARACTER = CHARACTER_LOAD[62];
				CP++;
				break;

			case '4':

				//キャラ64読込
				CHARACTER = CHARACTER_LOAD[63];
				CP++;
				break;

			case '5':

				//キャラ65読込
				CHARACTER = CHARACTER_LOAD[64];
				CP++;
				break;

			case '6':

				//キャラ66読込
				CHARACTER = CHARACTER_LOAD[65];
				CP++;
				break;

			case '7':

				//キャラ67読込
				CHARACTER = CHARACTER_LOAD[66];
				CP++;
				break;

			case '8':

				//キャラ68読込
				CHARACTER = CHARACTER_LOAD[67];
				CP++;
				break;

			case '9':

				//キャラ69読込
				CHARACTER = CHARACTER_LOAD[68];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '7':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ70読込
				CHARACTER = CHARACTER_LOAD[70];
				CP++;
				break;

			case '1':

				//キャラ71読込
				CHARACTER = CHARACTER_LOAD[70];
				CP++;
				break;

			case '2':

				//キャラ72読込
				CHARACTER = CHARACTER_LOAD[71];
				CP++;
				break;

			case '3':

				//キャラ73読込
				CHARACTER = CHARACTER_LOAD[72];
				CP++;
				break;

			case '4':

				//キャラ74読込
				CHARACTER = CHARACTER_LOAD[73];
				CP++;
				break;

			case '5':

				//キャラ75読込
				CHARACTER = CHARACTER_LOAD[74];
				CP++;
				break;

			case '6':

				//キャラ76読込
				CHARACTER = CHARACTER_LOAD[75];
				CP++;
				break;

			case '7':

				//キャラ77読込
				CHARACTER = CHARACTER_LOAD[76];
				CP++;
				break;

			case '8':

				//キャラ78読込
				CHARACTER = CHARACTER_LOAD[77];
				CP++;
				break;

			case '9':

				//キャラ79読込
				CHARACTER = CHARACTER_LOAD[78];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '8':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ80読込
				CHARACTER = CHARACTER_LOAD[79];
				CP++;
				break;

			case '1':

				//キャラ81読込
				CHARACTER = CHARACTER_LOAD[80];
				CP++;
				break;

			case '2':

				//キャラ82読込
				CHARACTER = CHARACTER_LOAD[81];
				CP++;
				break;

			case '3':

				//キャラ83読込
				CHARACTER = CHARACTER_LOAD[82];
				CP++;
				break;

			case '4':

				//キャラ84読込
				CHARACTER = CHARACTER_LOAD[83];
				CP++;
				break;

			case '5':

				//キャラ85読込
				CHARACTER = CHARACTER_LOAD[84];
				CP++;
				break;

			case '6':

				//キャラ86読込
				CHARACTER = CHARACTER_LOAD[85];
				CP++;
				break;

			case '7':

				//キャラ87読込
				CHARACTER = CHARACTER_LOAD[86];
				CP++;
				break;

			case '8':

				//キャラ88読込
				CHARACTER = CHARACTER_LOAD[87];
				CP++;
				break;

			case '9':

				//キャラ89読込
				CHARACTER = CHARACTER_LOAD[88];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		case '9':

			CP++;

			switch (String[SP][CP])
			{
			case '0':

				//キャラ90読込
				CHARACTER = CHARACTER_LOAD[89];
				CP++;
				break;

			case '1':

				//キャラ91読込
				CHARACTER = CHARACTER_LOAD[90];
				CP++;
				break;

			case '2':

				//キャラ92読込
				CHARACTER = CHARACTER_LOAD[91];
				CP++;
				break;

			case '3':

				//キャラ93読込
				CHARACTER = CHARACTER_LOAD[92];
				CP++;
				break;

			case '4':

				//キャラ94読込
				CHARACTER = CHARACTER_LOAD[93];
				CP++;
				break;

			case '5':

				//キャラ95読込
				CHARACTER = CHARACTER_LOAD[94];
				CP++;
				break;

			case '6':

				//キャラ96読込
				CHARACTER = CHARACTER_LOAD[95];
				CP++;
				break;

			case '7':

				//キャラ97読込
				CHARACTER = CHARACTER_LOAD[96];
				CP++;
				break;

			case '8':

				//キャラ98読込
				CHARACTER = CHARACTER_LOAD[97];
				CP++;
				break;

			case '9':

				//キャラ99読込
				CHARACTER = CHARACTER_LOAD[98];
				CP++;
				break;
			}

			//キャラクター描画
			SCRIPT_OUTPUT_CHARACTER_DRAW();
			break;

		}
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

	//タイトルへ戻る
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F10) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = 0;
		GAMEMENU_TITLE_BACK();
	}
}