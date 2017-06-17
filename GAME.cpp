/*=============================================================================
  Copyright (c) 2017 S.H.(GAMELINKS)
  https://github.com/S-H-GAMELINKS/Novel.Game.Engine.LINKS
  This software is released under the MIT License, see LICENSE.
=============================================================================*/
//ライブラリとヘッダの読み込み
#include "GAME.h"
#include "DxLib.h"
#include "DEF.h"
#include <initializer_list>
#include <cassert>
#include <type_traits>
#include "resource_manager.hpp"
#include "back_log.hpp"
#include "save.hpp"
#include "auto_skip.hpp"
#include "fmt/fmt/format.h"

// 文字列描画の位置
int DrawPointX = 0, DrawPointY = 0;

// 参照する文字列番号と文字列中の文字ポインタ
int SP = 0, CP = 0;

//スクリプト用読込配列
char String[script_line_num_lim][script_line_string_len_lim];

//タイトル関連
int TITLE;
unsigned int Cr;
static_assert(
	std::is_same<decltype(Cr), decltype(DxLib::GetColor(std::declval<int>(), std::declval<int>(), std::declval<int>()))>::value,
	"Your DxLib version is too old."
);

//ゲームオーバー
static int GAMEOVER;

//選択肢読込変数
static char ChoiceStrings[2][script_line_string_len_lim];
static int Choices[2];
static constexpr const char* const ChoiceFiles[][2] = {
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
bool GAMEMENU_COUNT;

//既読スキップ変数
SkipData_t TextIgnoredFlags = {};

//非アクティブ用変数
static bool WindowActive = true;

// １文字分一時記憶配列
static char OneMojiBuf[3];

//キー操作
int Key[256];
int TitleMenuPosY = menu_init_pos_y;
int GAME_y = game_menu_base_pos_y;

//設定用変数
ConfigData_t ConfigData = {
	/*bgm_vol               :*/100,
	/*bgm_vol_count         :*/10,
	/*se_vol                :*/100,
	/*se_vol_count          :*/10,
	/*skip_speed            :*/100,
	/*skip_speed_count      :*/10,
	/*auto_speed            :*/100,
	/*auto_speed_count      :*/10,
	/*string_speed          :*/100,
	/*string_speed_count    :*/10,
	/*soundnovel_winownovel :*/0,
	/*mouse_key_move        :*/1
};
static int Config = 0;

//スクリーンショット用変数
static int SCREENSHOT_COUNT = 0;

//ショートカットキー用変数
static short SHORTCUT_KEY_FLAG = 0;

//セーブ・ロード関連
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

//
// function Definition
//
//各素材データ読込関数
void MATERIAL_LOAD() {

	//サウンドデータの読み込み形式
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMPRESS);

	//キャラクター画像読込
	LINKS_EXPECT_TRUE(charactor.load("DATA/CHARACTER/CHAR{0:02d}.png"));

	//背景画像読込
	LINKS_EXPECT_TRUE(background.load("DATA/BACKGROUND/BG{0:02d}.png"));

	//ＢＧＭ読込
	LINKS_EXPECT_TRUE(backgroundMusic.load("DATA/BACKGROUNDMUSIC/BGM{0:02d}.ogg"));

	//ＳＥ読込
	LINKS_EXPECT_TRUE(soundEffect.load("DATA/SOUNDEFFECT/SE{0:02d}.ogg"));

	//ゲームオーバー画面
	GAMEOVER = LoadGraph("DATA/BACKGROUND/GAMEOVER.png");

	// 白色の値を取得
	Cr = GetColor(255, 255, 255);

	//タイトルメニュー背景画像読込
	TITLE = LoadGraph("DATA/BACKGROUND/TITLE.png");
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
		for (auto&& s : String) FileRead_gets(s, countof(s), ScriptFile);
		FileRead_close(ScriptFile);
	}
	return 0;
}

//各処理後のゲーム画面の描画(サウンドノベル風)
void SOUNDNOVEL() noexcept {

	if (ConfigData.soundnovel_winownovel == 0) {

		SCREEN_CLEAR();

		//背景の表示
		background.DrawGraph(0, 0, true);
		//立ち絵の表示
		charactor.DrawGraph(charactor_pos_x, charactor_pos_y, true);
		//ＢＧＭの再生
		backgroundMusic.play(DX_PLAYTYPE_LOOP);

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
void WINDOWNOVEL() noexcept {

	//ウインドウ風描画時の処理
	if (ConfigData.soundnovel_winownovel == 1) {

		SCREEN_CLEAR();

		//背景の表示
		background.DrawGraph(0, 0, true);
		static const auto windowColor = GetColor(0, 0, 0);
		DrawBox(0, 400, 640, 480, windowColor, TRUE);
		//立ち絵の表示
		charactor.DrawGraph(charactor_pos_x, charactor_pos_y - charactor_pos_y, true);
		//ＢＧＭの再生
		backgroundMusic.play(DX_PLAYTYPE_LOOP);

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
int MoveKey(int (&KeyStateBuf)[256]) {

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
void SHORTCUT_KEY_DRAW() noexcept {

	if (SHORTCUT_KEY_FLAG == 1) {

		//サウンドノベル風時の処理
		SOUNDNOVEL();

		//ウインドウ風時の処理
		WINDOWNOVEL();

		SHORTCUT_KEY_FLAG = 0;
	}
}

//タイトルメニューカーソル関数
void title(unsigned int color, int y) {

	//カーソル
	DrawString(menu_pos_x, y, "■", color);

	//各メニュー項目
	DrawString(menu_pos_x + cursor_move_unit, title_menu_game_start_pos_y, "START", color);
	DrawString(menu_pos_x + cursor_move_unit, title_menu_game_load_pos_y, "LOAD", color);
	DrawString(menu_pos_x + cursor_move_unit, title_menu_game_config_pos_y, "CONFIG", color);
	DrawString(menu_pos_x + cursor_move_unit, title_menu_quick_load_pos_y, "QUICKLOAD", color);
	DrawString(menu_pos_x + cursor_move_unit, title_menu_continue_pos_y, "CONTINUE", color);
	DrawString(menu_pos_x + cursor_move_unit, title_menu_game_quit_pos_y, "QUIT", color);
}

//ゲームメニューカーソル関数
void GAME_MENU_CURSOR(unsigned int color, int y) {
	DrawString(save_base_pos_x - (cursor_move_unit * 6), y, "■", color);
}

namespace {
	//マウス操作(タイトルメニュー)
	void Mouse_Move_TITLE(int MouseY) {
		//タイトルメニュー
		if (EndFlag == 99) {
			TitleMenuPosY = (MouseY <= 329) ? 300
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
		if (EndFlag == 99 || EndFlag != 99 && false == GAMEMENU_COUNT && Config == 0) {
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

	//マウス操作(選択肢画面)
	void Mouse_Move_CHOICE(int MouseY) {
		//選択肢画面
		if (EndFlag == 1 || EndFlag == 2 || EndFlag == 3 || EndFlag == 4 || EndFlag == 5 || EndFlag == 6 || EndFlag == 7) {
			TitleMenuPosY = (MouseY <= 229) ? 200 : 230;
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
	if (fp == nullptr) {
		return 0;
	}
#endif
	fread(&TextIgnoredFlags, sizeof(SkipData_t), 1, fp);
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
		if (fp == nullptr) {//エラーが起きたらnullptrを返す
			return 0;
		}
#endif
		fwrite(&TextIgnoredFlags, sizeof(SkipData_t), 1, fp); // SkipData_t構造体の中身を出力
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
	if (fp == nullptr) {//エラーが起きたらnullptrを返す
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
	if (fp == nullptr) {
		return 0;
	}
#endif
	fread(&ConfigData, sizeof(ConfigData_t), 1, fp);
	fclose(fp);//ファイルを閉じる

	return 0;
}

namespace {
	//クイックセーブ
	int QUICKSAVE_SAVE() {
		if (IDYES == MessageBoxYesNo("クイックセーブを実行しますか？")) {

			//クイックセーブデータの作成
			QuickSaveData_t Data = { EndFlag, SP, 0, charactor.activeResource(), background.activeResource(), backgroundMusic.activeResource(), SAVE_CHOICE };
			FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
			const errno_t er = fopen_s(&fp, "DATA/SAVE/QUICKSAVEDATA.dat", "wb");
			if (0 != er) {
				return 0;
			}
#else
			fp = fopen("DATA/SAVE/QUICKSAVEDATA.dat", "wb");//バイナリファイルを開く
			if (fp == nullptr) {//エラーが起きたらnullptrを返す
				return 0;
			}
#endif
			fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t構造体の中身を出力
			fclose(fp);//ファイルを閉じる
		}

		MessageBoxOk("セーブしました！");

		return 0;

	}
}

//クイックロード
int QUICKSAVE_LOAD() {
	if (IDYES == MessageBoxYesNo("クイックロードを実行しますか？")) {

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
		if (fp == nullptr) {
			return 0;
		}
#endif
		fread(&Data, sizeof(Data), 1, fp);
		EndFlag = Data.ENDFLAG;
		SP = Data.SP;
		CP = Data.CP;
		charactor.activeResource(Data.CHAR);
		background.activeResource(Data.BG);
		backgroundMusic.activeResource(Data.BGM);
		SAVE_CHOICE = Data.SAVE_CHOICE;

		GAMEMENU_COUNT = true;

		//サウンドノベル風描画時の処理
		SOUNDNOVEL();

		//ウインドウ風描画時の処理
		WINDOWNOVEL();

		MessageBoxOk("ロードしました！");

		fclose(fp);
	}
	return 0;
}

namespace {
	//コンティニュー用セーブ
	int CONTINUE_SAVE() {

		//クイックセーブデータの作成
		ContinueSaveData_t Data = { EndFlag, SP, 0, charactor.activeResource(), background.activeResource(), backgroundMusic.activeResource(), SAVE_CHOICE };
		FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
		const errno_t er = fopen_s(&fp, "DATA/SAVE/CONTINUESAVEDATA.dat", "wb");
		if (0 != er) {
			return 0;
		}
#else
		fp = fopen("DATA/SAVE/CONTINUESAVEDATA.dat", "wb");//バイナリファイルを開く
		if (fp == nullptr) {//エラーが起きたらnullptrを返す
			return 0;
		}
#endif
		fwrite(&Data, sizeof(Data), 1, fp); // SaveData_t構造体の中身を出力
		fclose(fp);//ファイルを閉じる

		return 0;
	}
}

//コンティニュー用ロード
int CONTINUE_LOAD() {
	if (IDYES == MessageBoxYesNo("前回遊んだところから再開しますか？")) {

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
		if (fp == nullptr) {
			return 0;
		}
#endif
		fread(&Data, sizeof(Data), 1, fp);
		EndFlag = Data.ENDFLAG;
		SP = Data.SP;
		CP = Data.CP;
		charactor.activeResource(Data.CHAR);
		background.activeResource(Data.BG);
		backgroundMusic.activeResource(Data.BGM);
		SAVE_CHOICE = Data.SAVE_CHOICE;

		GAMEMENU_COUNT = true;

		//サウンドノベル風描画時の処理
		SOUNDNOVEL();

		//ウインドウ風描画時の処理
		WINDOWNOVEL();

		MessageBoxOk("ロードしました！");

		fclose(fp);
	}
	return 0;
}

namespace {
	//ゲームメニュー項目描画関数
	void GAMEMENU_DRAW() {
		static constexpr const char* menuStrings[] = {
			"セーブ", "ロード", "セーブデータ削除", "既読スキップ", "スキップ", "オート",
			"オート/スキップ停止", "バックログ参照", "設定", "タイトルに戻る", "ゲームに戻る", "ゲーム終了"
		};
		//各メニュー描画
		for (std::size_t i = 0; i < countof(menuStrings); ++i) {
			DrawString(save_name_pos_x, game_menu_base_pos_y * (i + 1), menuStrings[i], Cr);
		}
	}

	//ゲームメニュー(キー操作)
	void GAMEMENU_KEY_MOVE() {

		if (Key[KEY_INPUT_DOWN] == 1) {
			GAME_y += game_menu_base_pos_y;
			if (GAME_y == (game_menu_base_pos_y * 13))
				GAME_y = game_menu_base_pos_y;
		}

		if (Key[KEY_INPUT_UP] == 1) {
			GAME_y -= game_menu_base_pos_y;
			if (GAME_y == (game_menu_base_pos_y - game_menu_base_pos_y))
				GAME_y = (game_menu_base_pos_y * 12);
		}
	}

	//コンフィグ(キー操作)
	void CONFIG_KEY_MOVE() {

		//キー操作関連
		if (Key[KEY_INPUT_DOWN] == 1) {
			GAME_y += game_menu_base_pos_y;
			if (GAME_y == (game_menu_base_pos_y * 10))
				GAME_y = game_menu_base_pos_y;
		}

		if (Key[KEY_INPUT_UP] == 1) {
			GAME_y -= game_menu_base_pos_y;
			if (GAME_y == (game_menu_base_pos_y - game_menu_base_pos_y))
				GAME_y = (game_menu_base_pos_y * 9);
		}
	}

	//コンフィグ(BGM音量調節)
	void BGM_VOL_CHANGE() {

		//ＢＧＭ音量調整
		if (GAME_y == game_menu_base_pos_y && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == game_menu_base_pos_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			WaitTimer(300);

			ConfigData.bgm_vol += 10;
			ConfigData.bgm_vol_count += 1;

			if (ConfigData.bgm_vol_count >= 10) {
				ConfigData.bgm_vol = 100;
				ConfigData.bgm_vol_count = 10;
			}
		}

		if (GAME_y == game_menu_base_pos_y && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == game_menu_base_pos_y && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

			WaitTimer(300);

			ConfigData.bgm_vol -= 10;
			ConfigData.bgm_vol_count -= 1;

			if (ConfigData.bgm_vol_count <= 0) {
				ConfigData.bgm_vol = 0;
				ConfigData.bgm_vol_count = 0;
			}
		}

	}

	//コンフィグ(SE音量調整)
	void SE_VOL_CHANGE() {

		//ＳＥ音量調整
		if (GAME_y == game_menu_base_pos_y * 2 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == game_menu_base_pos_y * 2 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			WaitTimer(300);

			ConfigData.se_vol += 10;
			ConfigData.se_vol_count += 1;

			if (ConfigData.se_vol_count >= 10) {
				ConfigData.se_vol = 100;
				ConfigData.se_vol_count = 10;
			}
		}

		if (GAME_y == game_menu_base_pos_y * 2 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == game_menu_base_pos_y * 2 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

			WaitTimer(300);

			ConfigData.se_vol -= 10;
			ConfigData.se_vol_count -= 1;

			if (ConfigData.se_vol_count <= 0) {
				ConfigData.se_vol = 0;
				ConfigData.se_vol_count = 0;
			}
		}
	}

	//コンフィグ(オート速度調整)
	void AUTO_SPEED_CHANGE() {

		//オート速度調整
		if (GAME_y == game_menu_base_pos_y * 3 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == game_menu_base_pos_y * 3 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			WaitTimer(300);

			ConfigData.auto_speed += 10;
			ConfigData.auto_speed_count += 1;

			if (ConfigData.auto_speed_count >= 10) {
				ConfigData.auto_speed = 100;
				ConfigData.auto_speed_count = 10;
			}
		}

		if (GAME_y == game_menu_base_pos_y * 3 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == game_menu_base_pos_y * 3 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

			WaitTimer(300);

			ConfigData.auto_speed -= 10;
			ConfigData.auto_speed_count -= 1;

			if (ConfigData.auto_speed_count <= 0) {
				ConfigData.auto_speed = 0;
				ConfigData.auto_speed_count = 0;
			}
		}
	}

	//コンフィグ(スキップ速度調整)
	void SKIP_SPEED_CHANGE() {

		//スキップ速度調整
		if (GAME_y == game_menu_base_pos_y * 4 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == game_menu_base_pos_y * 4 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			WaitTimer(300);

			ConfigData.skip_speed += 10;
			ConfigData.skip_speed_count += 1;

			if (ConfigData.skip_speed_count >= 10) {
				ConfigData.skip_speed = 100;
				ConfigData.skip_speed_count = 10;
			}
		}

		if (GAME_y == game_menu_base_pos_y * 4 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == game_menu_base_pos_y * 4 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

			WaitTimer(300);

			ConfigData.skip_speed -= 10;
			ConfigData.skip_speed_count -= 1;

			if (ConfigData.skip_speed_count <= 0) {
				ConfigData.skip_speed = 0;
				ConfigData.skip_speed_count = 0;
			}

		}
	}

	//コンフィグ(文字描画)
	void STRING_SPEED_CHANGE() {

		//文字描画速度調整
		if (GAME_y == game_menu_base_pos_y * 5 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == game_menu_base_pos_y * 5 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			WaitTimer(300);

			ConfigData.string_speed += 10;
			ConfigData.string_speed_count += 1;

			if (ConfigData.string_speed_count >= 10) {
				ConfigData.string_speed = 100;
				ConfigData.string_speed_count = 10;
			}
		}

		if (GAME_y == game_menu_base_pos_y * 5 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == game_menu_base_pos_y * 5 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

			WaitTimer(300);

			ConfigData.string_speed -= 10;
			ConfigData.string_speed_count -= 1;

			if (ConfigData.string_speed_count <= 0) {
				ConfigData.string_speed = 0;
				ConfigData.string_speed_count = 0;
			}
		}
	}

	//コンフィグ(サウンドノベル風とウインドウ風)
	void SOUNDNOVEL_WINDOWNOVEL_CHANGE() {

		//サウンドノベル風とウインドウ風の切り替え
		if (GAME_y == game_menu_base_pos_y * 6 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == game_menu_base_pos_y * 6 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			WaitTimer(300);
			ConfigData.soundnovel_winownovel = 0;
		}

		if (GAME_y == game_menu_base_pos_y * 6 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == game_menu_base_pos_y * 6 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

			WaitTimer(300);
			ConfigData.soundnovel_winownovel = 1;
		}
	}

	//非アクティブ時の処理設定
	void WINDOWACTIVE() {

		//非アクティブ時の処理の切り替え
		if (GAME_y == game_menu_base_pos_y * 7 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == game_menu_base_pos_y * 7 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			WaitTimer(300);
			WindowActive = false;

			//非アクティブ状態ではゲームを実行しない
			SetAlwaysRunFlag(WindowActive);
		}

		if (GAME_y == game_menu_base_pos_y * 7 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == game_menu_base_pos_y * 7 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

			WaitTimer(300);
			WindowActive = true;

			//非アクティブ状態でもゲームを実行
			SetAlwaysRunFlag(WindowActive);
		}
	}

	//コンフィグ(マウス/キー操作)
	void MOUSE_KEY_MOVE() {

		//マウス操作を有効に
		if (GAME_y == game_menu_base_pos_y * 8 && CheckHitKey(KEY_INPUT_RIGHT) == 1 || GAME_y == game_menu_base_pos_y * 8 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			WaitTimer(300);

			ConfigData.mouse_key_move = 1;
		}

		//キー操作を有効に
		if (GAME_y == game_menu_base_pos_y * 8 && CheckHitKey(KEY_INPUT_LEFT) == 1 || GAME_y == game_menu_base_pos_y * 8 && ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)) {

			WaitTimer(300);

			ConfigData.mouse_key_move = 0;
		}
	}

	//タイトルに戻る
	void GAMEMENU_TITLE_BACK() {
		if (IDYES == MessageBoxYesNo("タイトル画面に戻りますか？")) {

			ClearDrawScreen();

			if (SHORTCUT_KEY_FLAG == 1) backgroundMusic.stop();

			GAMEMENU_COUNT = true;
			EndFlag = 99;
			TitleMenuPosY = menu_init_pos_y;
			disableSkip();
			charactor.reset();
			background.reset();
			backgroundMusic.reset();
		}
	}

	//ゲームに戻る
	void GAMEMENU_GAME_BACK() {
		if (IDYES == MessageBoxYesNo("ゲームに戻りますか？")) {

			GAMEMENU_COUNT = true;

			//サウンドノベル風描画時の処理
			SOUNDNOVEL();

			//ウインドウ風描画時の処理
			WINDOWNOVEL();
		}
	}

	//ゲーム終了
	void GAMEMENU_GAME_FINISH() {
		if (IDYES == MessageBoxYesNo("終了しますか？")) {

			//コンティニュー用セーブ
			CONTINUE_SAVE();

			EndFlag = 99999;

			GAMEMENU_COUNT = true;
		}
	}
}

//終了ウインドウ
int GAME_FINISH() {

	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
		if (IDYES == MessageBoxYesNo("終了しますか？")) {

			//コンティニュー用セーブ
			CONTINUE_SAVE();

			EndFlag = 99999;

			if (false == GAMEMENU_COUNT)
				GAMEMENU_COUNT = true;
		}
		WaitTimer(300);
	}

	return 0;
}

namespace {
	//各種設定情報描画
	void CONFIG_MENU() {
		static constexpr const char* saveDataName[] = {
			"ＢＧＭ音量", "ＳＥ音量", "オート速度", "スキップ速度", "文字描画速度", "描画方法", "非アクティブ時", "マウス/キー操作",
			"戻る"
		};
		for (std::size_t i = 0; i < countof(saveDataName); ++i) {
			DrawString(save_name_pos_x, game_menu_base_pos_y * (i + 1), saveDataName[i], Cr);
		}
		DrawFormatString(save_name_pos_x + cursor_move_unit * 5, game_menu_base_pos_y, Cr, "%d", ConfigData.bgm_vol);
		DrawFormatString(save_name_pos_x + cursor_move_unit * 5, game_menu_base_pos_y * 2, Cr, "%d", ConfigData.se_vol);
		DrawFormatString(save_name_pos_x + cursor_move_unit * 5, game_menu_base_pos_y * 3, Cr, "%d", ConfigData.auto_speed);
		DrawFormatString(save_name_pos_x + cursor_move_unit * 5, game_menu_base_pos_y * 4, Cr, "%d", ConfigData.skip_speed);
		DrawFormatString(save_name_pos_x + cursor_move_unit * 5, game_menu_base_pos_y * 5, Cr, "%d", ConfigData.string_speed);
		DrawString(save_name_pos_x + cursor_move_unit * 6, game_menu_base_pos_y * 6, ((1 == ConfigData.soundnovel_winownovel) ? "ウインドウ風" : "サウンドノベル風"), Cr);
		DrawString(save_name_pos_x + cursor_move_unit * 7, game_menu_base_pos_y * 7, ((WindowActive) ? "処理" : "未処理"), Cr);
		DrawString(save_name_pos_x + cursor_move_unit * 8, game_menu_base_pos_y * 8, ((1 == ConfigData.mouse_key_move) ? "マウス操作" : "キー操作"), Cr);
	}

	//コンフィグ(タイトル/ゲームメニューへ戻る)
	void CONFIG_TITLE_BACK() {

		//タイトルに戻る/ゲームメニューに戻る
		if (GAME_y == game_menu_base_pos_y * 9 && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == game_menu_base_pos_y * 9 && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
			if (IDYES == MessageBoxYesNo("戻りますか？")) {

				ClearDrawScreen();
				GAME_y = game_menu_base_pos_y;
				Config = 0;
			}
			WaitTimer(300);
		}
	}
}

//コンフィグ
void CONFIG() {
	if (IDYES == MessageBoxYesNo("設定を変更しますか？")) {

		Config = 1;

		GAME_y = game_menu_base_pos_y;

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

namespace {
	//各ゲームメニュー選択時処理
	static void GAMEMENU_CHOICE() {

		//セーブ
		if (GAME_y == game_menu_base_pos_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == game_menu_base_pos_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//セーブデータセーブ処理
			SAVEDATA_SAVE();
			WaitTimer(300);
		}

		//ロード
		if (GAME_y == (game_menu_base_pos_y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (game_menu_base_pos_y * 2) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//セーブデータロード処理
			SAVEDATA_LOAD();
			WaitTimer(300);
		}

		//セーブデータ削除
		if (GAME_y == (game_menu_base_pos_y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (game_menu_base_pos_y * 3) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//セーブデータ削除処理
			SAVEDATA_DELETE();
			WaitTimer(300);
		}

		//既読スキップ
		if (GAME_y == (game_menu_base_pos_y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (game_menu_base_pos_y * 4) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//既読データの読み込み
			SKIP_READ_LOAD();

			//既読済みの部分を判定して、スキップ
			SKIP_READ_CHECK();
			WaitTimer(300);
		}

		//スキップ
		if (GAME_y == (game_menu_base_pos_y * 5) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (game_menu_base_pos_y * 5) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//スキップ処理
			SKIP_START();
			WaitTimer(300);
		}

		//オート
		if (GAME_y == (game_menu_base_pos_y * 6) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (game_menu_base_pos_y * 6) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//オート処理
			AUTO_START();
			WaitTimer(300);
		}

		//オート/スキップ停止
		if (GAME_y == (game_menu_base_pos_y * 7) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (game_menu_base_pos_y * 7) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//オート/スキップ停止処理
			AUTO_SKIP_STOP();
			WaitTimer(300);
		}

		//バックログ参照
		if (GAME_y == (game_menu_base_pos_y * 8) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (game_menu_base_pos_y * 8) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//バックログ参照
			BACKLOG_DRAW();
			WaitTimer(300);
		}

		//設定
		if (GAME_y == (game_menu_base_pos_y * 9) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (game_menu_base_pos_y * 9) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//設定画面の呼び出し
			CONFIG();
			WaitTimer(300);
		}

		//タイトルに戻る
		if (GAME_y == (game_menu_base_pos_y * 10) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (game_menu_base_pos_y * 10) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//タイトルに戻る
			GAMEMENU_TITLE_BACK();
			WaitTimer(300);
		}

		//ゲームに戻る
		if (GAME_y == (game_menu_base_pos_y * 11) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (game_menu_base_pos_y * 11) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//ゲームに戻る
			GAMEMENU_GAME_BACK();
			WaitTimer(300);
		}

		//ゲーム終了
		if (GAME_y == (game_menu_base_pos_y * 12) && CheckHitKey(KEY_INPUT_RETURN) == 1 || GAME_y == (game_menu_base_pos_y * 12) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

			//ゲーム終了
			GAMEMENU_GAME_FINISH();
			WaitTimer(300);
		}

		//エスケープでゲーム終了
		GAME_FINISH();
	}
}

//ゲームメニュー
int GAMEMENU() {

	//ゲームメニューを開く
	if (CheckHitKey(KEY_INPUT_BACK) == 1 || (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {

		GAMEMENU_COUNT = false;
		ClearDrawScreen();
		backgroundMusic.stop();
		GAME_y = game_menu_base_pos_y;

		//ゲームメニューループ
		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && false == GAMEMENU_COUNT) {

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
void sentakusi(unsigned int color, int y) {

	//カーソルの描画
	DrawString(choise_pos_x, y, "■", color);

	//選択肢の描画
	for (std::size_t i : {0, 1}) {
		DrawString(choise_pos_x + cursor_move_unit, choise_pos_y[i], ChoiceStrings[i], color);
	}
}

// 改行関数
int Kaigyou()
{
	if (ConfigData.soundnovel_winownovel == 0) {

		int TempGraph;

		// 描画行位置を一つ下げる
		DrawPointY++;

		// 描画列を最初に戻す
		DrawPointX = 0;

		// もし画面からはみ出るなら画面をスクロールさせる
		if (DrawPointY * font_size + font_size > 480)
		{
			// テンポラリグラフィックの作成
			TempGraph = MakeGraph(640, 480);

			// 画面の内容を丸々コピーする
			GetDrawScreenGraph(0, 0, 640, 480, TempGraph);

			// 一行分上に貼り付ける
			DrawGraph(0, -font_size, TempGraph, FALSE);

			// 一番下の行の部分を黒で埋める
			DrawBox(0, 480 - font_size, 640, 480, 0, TRUE);

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

namespace {
	//スクリプトタグ処理(立ち絵描画)
	void SCRIPT_OUTPUT_CHARACTER_DRAW() {

		//サウンドノベル風時の処理
		if (ConfigData.soundnovel_winownovel == 0) {
			//背景画像を切り抜き、立ち絵の上にペースト
			const int charactorDummy = background.DerivationGraph(charactor_pos_x, charactor_pos_y, character_graph_size_x, character_graph_size_y);
			DxLib::DrawGraph(charactor_pos_x, charactor_pos_y, charactorDummy, true);
			DxLib::DeleteGraph(charactorDummy);
			// 読みこんだグラフィックを画面左上に描画
			charactor.DrawGraph(charactor_pos_x, charactor_pos_y, true);
		}
		//ウインドウ風時の処理
		if (ConfigData.soundnovel_winownovel == 1) {
			//背景画像を切り抜き、立ち絵の上にペースト
			const int charactorDummy = background.DerivationGraph(charactor_pos_x, 0, character_graph_size_x, character_graph_size_y);
			DxLib::DrawGraph(charactor_pos_x, 0, charactorDummy, true);
			DxLib::DeleteGraph(charactorDummy);
			// 読みこんだグラフィックを画面左上に描画
			charactor.DrawGraph(charactor_pos_x, 0, true);
		}
		//文字を進める
		CP++;
	}

	//スクリプトタグ処理(背景描画)
	void SCRIPT_OUTPUT_BACKGROUND() {

		// 読みこんだグラフィックを画面左上に描画
		background.DrawGraph(0, 0, true);
		//ウインドウ風時の処理
		if (ConfigData.soundnovel_winownovel == 1) {
			static const auto windowColor = GetColor(0, 0, 0);
			DrawBox(0, 400, 640, 480, windowColor, TRUE);
		}
		//文字を進める
		CP++;

	}

	//スクリプトタグ処理(BGM再生)
	void SCRIPT_OUTPUT_BACKGROUNDMUSIC() {
		backgroundMusic.changeVolume(255 * ConfigData.bgm_vol / 100);
		backgroundMusic.play(DX_PLAYTYPE_LOOP);
		//文字を進める
		CP++;
	}

	//スクリプトタグ処理(SE再生)
	void SCRIPT_OUTPUT_SOUNDEFFECT() {
		soundEffect.stop();
		soundEffect.changeVolume(255 * ConfigData.se_vol / 100);
		soundEffect.play(DX_PLAYTYPE_BACK);
		//文字を進める
		CP++;
	}

	//スクリプトタグ処理(ゲーム画面のクリア処理)
	void SCRIPT_OUTPUT_SCREENCLEAR() {

		SetDrawScreen(DX_SCREEN_BACK);

		incrementBackLogCount();

		//バックログ取得関数
		BACKLOG_GET();

		// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
		ClearDrawScreen();
		DrawPointY = 0;
		DrawPointX = 0;
		charactor.reset();
		background.reset();
		CP++;

		SetDrawScreen(DX_SCREEN_FRONT);

	}

	//スクリプトタグ処理(ゲームオーバー)
	void SCRIPT_OUTPUT_GAMEOVER() {
		background.activeResource(GAMEOVER);
		background.DrawGraph(0, 0, true);
		if (ConfigData.soundnovel_winownovel == 1) {
			static const auto windowColor = GetColor(0, 0, 0);
			DrawBox(0, 400, 640, 480, windowColor, TRUE);
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
		backgroundMusic.stop();
		backgroundMusic.reset();
		CP++;
	}

	//スクリプトタグ処理(SE再生終了)
	void SCRIPT_OUTPUT_SESTOP() {
		soundEffect.stop();
		CP++;
	}

	//選択肢ループ用描画処理(サウンドノベル風)
	void SCRIPT_OUTPUT_CHOICE_LOOP_SOUNDNOVEL() {
		if (ConfigData.soundnovel_winownovel == 0 && SAVE_CHOICE == 1) {
			background.DrawGraph(0, 0, true);
			charactor.DrawGraph(charactor_pos_x, charactor_pos_y, true);
		}
	}

	//選択肢ループ用描画処理(ウインドウ風)
	void SCRIPT_OUTPUT_CHOICE_LOOP_WINDOWNOVEL() {
		if (ConfigData.soundnovel_winownovel == 1 && SAVE_CHOICE == 1) {
			static const auto windowColor = GetColor(0, 0, 0);
			background.DrawGraph(0, 0, true);
			DxLib::DrawBox(0, 400, 640, 480, windowColor, TRUE);
			charactor.DrawGraph(charactor_pos_x, 0, true);
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
				FileRead_gets(ChoiceStrings[i], countof(ChoiceStrings[i]), Choices[i]);
			}
		}
	}

	//キー操作(選択肢画面用)
	void SCRIPT_OUTPUT_CHOICE_LOOP_KEY_MOVE() {

		if (Key[KEY_INPUT_DOWN] == 1) {
			TitleMenuPosY += cursor_move_unit;
			if (TitleMenuPosY == (choise_pos_y[1] + cursor_move_unit))                         // TitleMenuPosY座標が260なら(選択が一番下なら)
				TitleMenuPosY = choise_pos_y[0];                        // 選択座標を一番上に
		}
		if (Key[KEY_INPUT_UP] == 1) {
			TitleMenuPosY -= cursor_move_unit;
			if (TitleMenuPosY == (choise_pos_y[0] - cursor_move_unit))
				TitleMenuPosY = choise_pos_y[1];
		}
	}

	//選択後の分岐処理(選択肢↑)
	void SCRIPT_OUTPUT_CHOICE_BRANCH_UP() {
		if (1 <= EndFlag && EndFlag <= 7) {
			SAVE_CHOICE = 0;
			setSaveSnapChoice(false);
			EndFlag *= 2;
		}
	}

	//選択後の分岐処理(選択肢↓)
	void SCRIPT_OUTPUT_CHOICE_BRANCH_DOWN() {
		if (1 <= EndFlag && EndFlag <= 7) {
			SAVE_CHOICE = 0;
			setSaveSnapChoice(false);
			EndFlag = EndFlag * 2 + 1;
		}
	}

	//選択肢時のバックログ取得(選択肢の読み込み)
	void SCRIPT_OUTPUT_CHOICE_BACKLOG_CHOICE_READ() {
		if (2 <= EndFlag && EndFlag <= 15) {
			const int index = EndFlag / 2;
			for (int i : {0, 1}) {
				Choices[i] = FileRead_open(ChoiceFiles[index][i]);
				FileRead_gets(ChoiceStrings[i], countof(ChoiceStrings[i]), Choices[i]);
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
		sentakusi(Cr, TitleMenuPosY);

		//バックログ取得
		BACKLOG_GET();

		ClearDrawScreen();
		DrawPointY = 0;
		DrawPointX = 0;
		background.reset();
		charactor.reset();

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
			sentakusi(Cr, TitleMenuPosY);

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

			if (TitleMenuPosY == choise_pos_y[0] && CheckHitKey(KEY_INPUT_RETURN) == 1 || TitleMenuPosY == choise_pos_y[0] && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				incrementBackLogCount();

				//選択肢時のバックログ取得
				SCRIPT_OUTPUT_CHOICE_BACKLOG();

				//選択後の分岐処理(選択肢↑)
				SCRIPT_OUTPUT_CHOICE_BRANCH_UP();
				CP++;
				break;
			}

			if (TitleMenuPosY == choise_pos_y[1] && CheckHitKey(KEY_INPUT_RETURN) == 1 || TitleMenuPosY == choise_pos_y[1] && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				incrementBackLogCount();

				//選択肢時のバックログ取得
				SCRIPT_OUTPUT_CHOICE_BACKLOG();

				//選択後の分岐処理(選択肢↑)
				SCRIPT_OUTPUT_CHOICE_BRANCH_DOWN();
				CP++;
				break;
			}

		}
	}

	//スクリプトタグ処理(選択肢処理)
	void SCRIPT_OUTPUT_CHOICE() {

		TitleMenuPosY = choise_init_pos_y;

		if (EndFlag == 1 || EndFlag == 2 || EndFlag == 3 || EndFlag == 4 || EndFlag == 5 || EndFlag == 6 || EndFlag == 7) {

			SAVE_CHOICE = 1;
			setSaveSnapChoice(true);

			//選択肢ループ
			SCRIPT_OUTPUT_CHOICE_LOOP();
		}

		if (EndFlag == 8 || EndFlag == 9 || EndFlag == 10 || EndFlag == 11 || EndFlag == 12 || EndFlag == 13 || EndFlag == 14 || EndFlag == 15)
			CP++;
	}

	//スクリプトタグ処理(終了文字)
	void SCRIPT_OUTPUT_END() {
		SkipDataConv* conv = reinterpret_cast<SkipDataConv*>(&TextIgnoredFlags);
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
			background.DrawRectGraph(charactor_pos_x, charactor_pos_y, charactor_pos_x, charactor_pos_y, character_graph_size_x, character_graph_size_y, true);
		}
		//ウインドウ風時の処理
		else if (ConfigData.soundnovel_winownovel == 1) {
			background.DrawRectGraph(charactor_pos_x, 0, charactor_pos_x, 0, character_graph_size_x, character_graph_size_y, true);
		}
		CP++;
	}

	//キャラクター名描画処理
	void SCRIPT_OUTPUT_CHARACTER_NAME() {
		//ウインドウ風時の処理
		if (ConfigData.soundnovel_winownovel == 1) {
			char CHARACTER_NAME[10] = {};
			//キャラクター名を読み込む
			static_assert(10 <= countof(CHARACTER_NAME) && 10 <= countof(String[0]), "array length must be over 10");
			assert(0 < CP && std::size_t(CP + 10) <= countof(String[SP]));
			memcpy(CHARACTER_NAME, &String[SP][CP + 1], 9);
			CHARACTER_NAME[9] = '\0';

			//キャラクター名の背景
			static const auto windowColor = GetColor(0, 0, 0);
			DrawBox(30, 360, 150, 385, windowColor, TRUE);

			static const auto charColor = GetColor(255, 255, 255);
			// １文字描画
			DrawString(30, 360, CHARACTER_NAME, charColor);

			SP++;
			CP++;
		}
		SP++;
		CP++;
	}

	//文字列の描画
	void SCRIPT_OUTPUT_STRING_DRAW() {
		//TODO: https://github.com/S-H-GAMELINKS/Novel.Game.Engine.LINKS/issues/3
		// １文字分抜き出す
		OneMojiBuf[0] = String[SP][CP];
		OneMojiBuf[1] = String[SP][CP + 1];
		OneMojiBuf[2] = '\0';
		static const auto charColor = GetColor(255, 255, 255);
		if (ConfigData.soundnovel_winownovel == 0) {
			// １文字描画
			DrawString(DrawPointX * font_size, DrawPointY * font_size, OneMojiBuf, charColor);
		}

		if (ConfigData.soundnovel_winownovel == 1) {
			if (DrawPointY <= 399) DrawPointY = 400;
			// １文字描画
			DrawString(DrawPointX * font_size, DrawPointY, OneMojiBuf, charColor);
		}

		// 参照文字位置を２バイト勧める
		CP += 2;

		// カーソルを一文字文進める
		DrawPointX++;
	}

	//文字列の改行
	void SCRIPT_OUTPUT_STRING_KAIGYO() {
		// 画面からはみ出たら改行する
		if (DrawPointX * font_size + font_size > 640) Kaigyou();
	}

	//サウンドノベル風時の改ページ処理
	void SCRIPT_OUTPUT_STRING_PAGE_CLEAR_SOUNDNOVEL() {

		//サウンドノベル風時の改ページ処理
		if (ConfigData.soundnovel_winownovel == 0) {

			if (DrawPointY * font_size + font_size > charactor_pos_y + font_size) {

				SetDrawScreen(DX_SCREEN_BACK);

				incrementBackLogCount();

				//バックログ取得
				BACKLOG_GET();

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				charactor.reset();
				background.reset();
				CP++;

				SetDrawScreen(DX_SCREEN_FRONT);

				WaitTimer(300);
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;

				background.DrawGraph(0, 0, true);
				charactor.DrawGraph(charactor_pos_x, charactor_pos_y, true);
			}
		}
	}

	//ウインドウ風時の改ページ処理
	void SCRIPT_OUTPUT_STRING_PAGE_CLEAR_WINODWNOVEL() {

		//ウインドウ風時の改ページ処理
		if (ConfigData.soundnovel_winownovel == 1) {

			if (DrawPointY > 480) {

				SetDrawScreen(DX_SCREEN_BACK);

				incrementBackLogCount();

				//バックログ取得
				BACKLOG_GET();

				// 画面を初期化して描画文字位置を初期位置に戻すおよび参照文字位置を一つ進める
				ClearDrawScreen();
				DrawPointY = 0;
				DrawPointX = 0;
				charactor.reset();
				background.reset();
				CP++;

				SetDrawScreen(DX_SCREEN_FRONT);

				WaitTimer(300);
				ClearDrawScreen();
				DrawPointY = 400;
				DrawPointX = 0;

				background.DrawGraph(0, 0, true);
				if (ConfigData.soundnovel_winownovel == 1) {
					static const auto windowColor = GetColor(0, 0, 0);
					DrawBox(0, 400, 640, 480, windowColor, TRUE);
				}
				charactor.DrawGraph(charactor_pos_x, 0, true);
			}
		}
	}

	//動画再生処理
	void MOVIE_START() noexcept {
		if (isdigit(String[SP][CP]) && isdigit(String[SP][CP + 1])) {
			const size_t CharactorNumber = (ctoui(String[SP][CP]) * 10) + ctoui(String[SP][CP + 1]) - 1;
			if (99 <= CharactorNumber) return;
			try {
				DxLib::PlayMovie(
					fmt::format("DATA/MOVIE/MOVIE{0:c}{1:c}.wmv", String[SP][CP], String[SP][CP + 1]).c_str(),
					1,
					DX_MOVIEPLAYTYPE_BCANCEL
				);
			}
#if defined(_MSC_VER) && defined(_DEBUG)
			catch (const std::exception& er) {
				//例外が投げられた場合特にできることがないので握りつぶす
				OutputDebugStringA(er.what());
			}
#endif
			catch (...) {}
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
		if(charactor.select(String[SP][CP], String[SP][CP + 1])) CP++;
		//キャラクター描画
		SCRIPT_OUTPUT_CHARACTER_DRAW();
		break;

		//背景描画処理
	case 'B':
		CP++;
		if (background.select(String[SP][CP], String[SP][CP + 1])) CP++;
		//背景描画
		SCRIPT_OUTPUT_BACKGROUND();
		break;

		//BGM再生処理
	case 'M':
		CP++;
		backgroundMusic.stop();
		if (backgroundMusic.select(String[SP][CP], String[SP][CP + 1])) CP++;
		//BGM再生処理
		SCRIPT_OUTPUT_BACKGROUNDMUSIC();
		break;

		//SE再生処理
	case 'S':
		CP++;
		soundEffect.stop();
		if (soundEffect.select(String[SP][CP], String[SP][CP + 1])) CP++;
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
		MessageBoxOk("これ以上スクリーンショットを取得できません");
	}
	else {
		static constexpr const char* const ScreenShotFileNames[] = {
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
		static constexpr const char* const ScreenShotMessages[] = {
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
		MessageBoxOk(ScreenShotMessages[SCREENSHOT_COUNT]);
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
		GAMEMENU_COUNT = false;
		SAVEDATA_SAVE();
	}

	//ロード
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F2) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = false;
		SAVEDATA_LOAD();
	}

	//セーブデータ削除
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F3) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = false;
		SAVEDATA_DELETE();
	}

	//既読スキップ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F4) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = false;
		SKIP_READ_CHECK();
	}

	//スキップ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F5) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = false;
		SKIP_START();
	}

	//オート
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F6) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = false;
		AUTO_START();
	}

	//スキップ&オート停止
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F7) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = false;
		AUTO_SKIP_STOP();
	}

	//バックログ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F8) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = false;
		BACKLOG_DRAW();
	}

	//設定
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F9) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = false;
		CONFIG();
	}

	//クイックセーブ
	if (EndFlag != 99 && CheckHitKey(KEY_INPUT_F10) == 1) {
		SHORTCUT_KEY_FLAG = 1;
		GAMEMENU_COUNT = false;
		QUICKSAVE_SAVE();
	}
}
