#include <Windows.h>
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
