#ifndef LINKS_GAME_H_
#define LINKS_GAME_H_

#include <Windows.h>
#include "DEF.h"
#include "utility.hpp"
#include <cstdint>

//既読スキップ
struct alignas(4) SkipData_t {
	std::int32_t LINKS;		//メインルートの既読情報
	std::int32_t A;			//Aルートの既読情報
	std::int32_t B;			//Bルートの既読情報
	std::int32_t C;			//Cルートの既読情報
	std::int32_t D;			//Dルートの既読情報
	std::int32_t E;			//Eルートの既読情報
	std::int32_t F;			//Fルートの既読情報
	std::int32_t G;			//Gルートの既読情報
	std::int32_t H;			//Hルートの既読情報
	std::int32_t I;			//Iルートの既読情報
	std::int32_t J;			//Jルートの既読情報
	std::int32_t K;			//Kルートの既読情報
	std::int32_t L;			//Lルートの既読情報
	std::int32_t M;			//Mルートの既読情報
	std::int32_t N;			//Nルートの既読情報
};

union SkipDataConv {
	alignas(4) SkipData_t flag;
	alignas(4) std::int32_t arr[15];
};
static_assert(alignof(std::int32_t) == 4, "err");
static_assert(alignof(SkipData_t) == alignof(std::int32_t[15]), "err");
static_assert(sizeof(SkipData_t) == sizeof(std::int32_t[15]), "err");

//設定データ
struct alignas(4) ConfigData_t {
	std::int32_t bgm_vol;				//BGM音量情報
	std::int32_t bgm_vol_count;			//BGM音量メーター情報
	std::int32_t se_vol;					//SE音量情報
	std::int32_t se_vol_count;			//SE音量メーター情報
	std::int32_t skip_speed;				//スキップ速度情報
	std::int32_t skip_speed_count;		//スキップ速度メーター情報
	std::int32_t auto_speed;				//オート速度情報
	std::int32_t auto_speed_count;		//オート速度メーター情報
	std::int32_t string_speed;			//文字列描画速度
	std::int32_t string_speed_count;		//文字列描画速度メーター情報
	std::int32_t soundnovel_winownovel;	//サウンドノベル風とウインドウ風描画の情報
	std::int32_t mouse_key_move;			//マウス操作とキー操作の情報
};


// 文字列描画の位置
extern int DrawPointX, DrawPointY;

// 参照する文字列番号と文字列中の文字ポインタ
extern int SP, CP;

//スクリプト用読込配列
extern char String[script_line_num_lim][script_line_string_len_lim];

//タイトル関連
extern int TITLE;
extern unsigned int Cr;

//エンドフラグ
extern int EndFlag;

//既読スキップ変数
extern SkipData_t TextIgnoredFlag;

//設定用変数
extern ConfigData_t ConfigData;

//バックログ変数
extern char *BACKLOG_DELETE;

//セーブ用変数
extern int SAVE, SAVE_CHOICE;
extern char *SAVESNAP_CHOICE_DELETE;

//スキップ・オートモード用変数
extern int skip_auto;

//キー操作
extern int Key[256];
extern int y;
extern int SAVE_y;
extern int GAME_y;

//各素材データ読込関数
void MATERIAL_LOAD();

//スクリプト読込関数
int SCRIPT_READ();

//矢印キー操作関数
int MoveKey(int KeyStateBuf[]);

//タイトルメニューカーソル関数
void title(int Cr, int y);

//セーブロードメニューカーソル関数
void SAVE_LOAD_MENU(int Cr, int SAVE_y);

//ゲームメニューカーソル関数
void GAME_MENU_CURSOR(int Cr, int GAME_y);

//セーブデータロード関数
int SAVEDATA_LOAD();

//SKIP_READ LOAD関数
int SKIP_READ_LOAD();

//SKIP_READ SAVE関数
int SKIP_READ_SAVE();

//CONFIG_SAVE関数
int CONFIG_SAVE();

//CONFIG_LOAD関数
int CONFIG_LOAD();

//クイックロード
int QUICKSAVE_LOAD();

//コンティニュー用ロード
int CONTINUE_LOAD();

//セーブ・ロード・スキップ・オート他 ゲームメニュー
int GAMEMENU();

//選択肢機能
void sentakusi(int Cr, int y);

// 改行関数
int Kaigyou(void);

//スクリプトタグ処理関数
int SCRIPT_OUTPUT();

//終了ウインドウ
int GAME_FINISH();

//初期化
int FORMAT();

//スクリーンショット機能
int SCREENSHOT();

//マウス操作
int Mouse_Move();

//コンフィグ(タイトル画面)
void CONFIG();

//終了ウインドウ
int GAME_FINISH();

//画面クリア処理
void SCREEN_CLEAR();

//各種F1～F11キー
void SHORTCUT_KEY();

#endif //LINKS_GAME_H_
