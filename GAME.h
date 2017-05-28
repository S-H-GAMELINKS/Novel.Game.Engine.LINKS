#ifndef LINKS_GAME_H_
#define LINKS_GAME_H_

#include <Windows.h>
#include "DEF.h"

// 文字列描画の位置
extern int DrawPointX, DrawPointY;

// 参照する文字列番号と文字列中の文字ポインタ
extern int SP, CP;

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

//Yes/Noのメッセージボックス
int LINKS_MessageBox_YESNO(LPCTSTR lpText);

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
