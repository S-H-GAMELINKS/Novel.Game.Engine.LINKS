/*=============================================================================
  Copyright (c) 2017 S.H.(GAMELINKS)
  https://github.com/S-H-GAMELINKS/Novel.Game.Engine.LINKS
  This software is released under the MIT License, see LICENSE.
=============================================================================*/
#include "save.hpp"
#include "DEF.h"
#include "utility.hpp"
#include "resource_manager.hpp"
#include "GAME.h"
#include <DxLib.h>

int SAVE_CHOICE = 0;
static int SAVESNAP1, SAVESNAP2, SAVESNAP3, SAVETITLE;
static int SAVESNAP_HANDLE1 = 0, SAVESNAP_HANDLE2 = 0, SAVESNAP_HANDLE3 = 0, SAVESNAP_CHOICE = 0;

static int SAVE_y = save_base_pos_y;

void setSaveSnapChoice(bool b) {
	SAVESNAP_CHOICE = b;
}

namespace {
	//セーブデータ一覧描画
	void SAVEDATA_DRAW() {

		//スクリーンショット描画
		DrawRotaGraph(saved_snap_draw_pos_x, save_base_pos_y, 0.2f, 0, SAVESNAP1, TRUE);
		DrawRotaGraph(saved_snap_draw_pos_x, save_base_pos_y * 2, 0.2f, 0, SAVESNAP2, TRUE);
		DrawRotaGraph(saved_snap_draw_pos_x, save_base_pos_y * 3, 0.2f, 0, SAVESNAP3, TRUE);

		//セーブデータ名描画
		DrawString(save_name_pos_x, save_base_pos_y, "セーブデータ1", Cr);
		DrawString(save_name_pos_x, save_base_pos_y * 2, "セーブデータ2", Cr);
		DrawString(save_name_pos_x, save_base_pos_y * 3, "セーブデータ3", Cr);

		DrawString(save_name_pos_x - cursor_move_unit, save_base_pos_y * 4, "戻る", Cr);
		static_assert(0 < (save_name_pos_x - cursor_move_unit), "error");
	}

	//セーブデータスクリーンショット読込
	void SAVEDATA_SCREENSHOT_READ() {

		//セーブ時のスクリーンショット読込
		SAVESNAP1 = LoadGraph("DATA/SAVE/SAVESNAP1.png");
		SAVESNAP2 = LoadGraph("DATA/SAVE/SAVESNAP2.png");
		SAVESNAP3 = LoadGraph("DATA/SAVE/SAVESNAP3.png");
		SAVETITLE = LoadGraph("DATA/BACKGROUND/SAVE.png");

		WaitTimer(600);//キー判定消去待ち目的ではない(セーブデータ画面の描画遅延処理)
	}

	//セーブ後のメッセージ
	void SAVE_MESSAGE() {

		MessageBoxOk("セーブしました！");
	}

	//セーブ後の処理(サウンドノベル風)
	void SAVE_SOUNDNOVEL() {

		//サウンドノベル風描画時の処理
		SOUNDNOVEL();

		SAVE_CHOICE = 0;

		GAMEMENU_COUNT = true;
	}

	//セーブ後の処理(ウインドウ風)
	void SAVE_WINDOWNOVEL() {

		//ウインドウ風描画時の処理
		WINDOWNOVEL();

		SAVE_CHOICE = 0;

		GAMEMENU_COUNT = true;
	}

	static int CreateSaveData(int* SaveSnapHandle, const char* Message, const char* ImagePath, const char* SaveDataPath) {
		if (IDYES == MessageBoxYesNo(Message)) {
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
			SaveData_t Data = { EndFlag, SP, 0, charactor.activeResource(), background.activeResource(), backgroundMusic.activeResource(), SAVE_CHOICE };
			FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
			const errno_t er = fopen_s(&fp, SaveDataPath, "wb");
			if (0 != er) {
				return 0;
			}
#else
			fp = fopen(SaveDataPath, "wb");//バイナリファイルを開く
			if (fp == nullptr) {//エラーが起きたらnullptrを返す
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

	//セーブ画面(キー操作)
	void SAVEDATA_KEY_MOVE() {

		if (Key[KEY_INPUT_DOWN] == 1) {
			SAVE_y = (SAVE_y == (save_buttom_y)) ? save_base_pos_y : SAVE_y + save_move_unit;
		}

		if (Key[KEY_INPUT_UP] == 1) {
			SAVE_y = (save_base_pos_y == SAVE_y) ? save_buttom_y : SAVE_y - save_move_unit;
		}
	}

	//セーブロードメニューカーソル関数
	void SAVE_LOAD_MENU(unsigned int color, int y) {
		//カーソルの描画
		DrawString(save_base_pos_x, y, "■", color);
	}

	//セーブデータ・セーブ画面ループ
	void SAVEDATA_SAVE_LOOP() {

		//セーブデータ・セーブ画面ループ
		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && false == GAMEMENU_COUNT) {

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
			if (SAVE_y == save_base_pos_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == save_base_pos_y && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				//セーブデータ１にセーブ
				SAVEDATA_1_SAVE();
				WaitTimer(300);
			}

			//セーブデータ２にセーブ
			if (SAVE_y == (save_base_pos_y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (save_base_pos_y * 2) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				//セーブデータ２にセーブ
				SAVEDATA_2_SAVE();
				WaitTimer(300);
			}

			//セーブデータ３にセーブ
			if (SAVE_y == (save_base_pos_y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (save_base_pos_y * 3) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				//セーブデータ３にセーブ
				SAVEDATA_3_SAVE();
				WaitTimer(300);
			}

			//画面に戻る
			if (SAVE_y == (save_base_pos_y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (save_base_pos_y * 4) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				if (IDYES == MessageBoxYesNo("戻りますか？")) {

					ClearDrawScreen();

					//ショートカットキー時の事後処理
					SHORTCUT_KEY_DRAW();
					break;
				}
				WaitTimer(300);
			}
		}
	}
}
//セーブデータセーブ関数
void SAVEDATA_SAVE() {
	if (IDYES == MessageBoxYesNo("セーブ画面に移行しますか？")) {
		ClearDrawScreen();
		SAVE_y = save_base_pos_y;

		//セーブデータのスクリーンショットの読み込み
		SAVEDATA_SCREENSHOT_READ();

		//セーブデータ・セーブ画面ループ
		SAVEDATA_SAVE_LOOP();
	}
}

namespace {
	//ロード後のメッセージ
	void LOAD_MESSAGE() {

		MessageBoxOk("ロードしました！");
	}

	//ロード後の処理(サウンドノベル風)
	void LOAD_SOUNDNOVEL() {

		//サウンドノベル風描画時の処理
		SOUNDNOVEL();

		GAMEMENU_COUNT = true;
	}

	//ロード後の処理(ウインドウ風)
	void LOAD_WINDOWNOVEL() {

		//ウインドウ風描画時の処理
		WINDOWNOVEL();

		GAMEMENU_COUNT = true;
	}

	static int LoadSaveData(const char* Message, const char* ErrorMessage, const char* SaveDataPath) {
		if (IDYES == MessageBoxYesNo(Message)) {
			SaveData_t Data;
			FILE *fp;
#ifdef LINKS_HAS_FOPEN_S
			const errno_t er = fopen_s(&fp, SaveDataPath, "rb");
			if (0 != er) {
				MessageBoxOk(ErrorMessage);
				return 0;
			}
#else
			fp = fopen(SaveDataPath, "rb");
			if (fp == nullptr) {
				MessageBoxOk(ErrorMessage);
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

		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && false == GAMEMENU_COUNT) {

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
			if (SAVE_y == save_base_pos_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == save_base_pos_y && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				//セーブデータ１をロード
				SAVEDATA_1_LOAD();
				WaitTimer(300);
			}

			//セーブデータ２のロード
			if (SAVE_y == (save_base_pos_y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (save_base_pos_y * 2) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				//セーブデータ2をロード
				SAVEDATA_2_LOAD();
				WaitTimer(300);
			}

			//セーブデータ３のロード
			if (SAVE_y == (save_base_pos_y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (save_base_pos_y * 3) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {

				//セーブデータ2をロード
				SAVEDATA_3_LOAD();
				WaitTimer(300);
			}

			//戻る
			if (SAVE_y == (save_base_pos_y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (save_base_pos_y * 4) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
				if (IDYES == MessageBoxYesNo("戻りますか？")) {

					ClearDrawScreen();

					//ショートカットキー時の事後処理
					SHORTCUT_KEY_DRAW();
					break;
				}
				WaitTimer(300);
			}
		}
	}
}

//セーブデータロード関数
int SAVEDATA_LOAD() {
	if (IDYES == MessageBoxYesNo("ロード画面に移行しますか？")) {

		ClearDrawScreen();
		SAVE_y = save_base_pos_y;

		//セーブデータのスクリーンショット読込
		SAVEDATA_SCREENSHOT_READ();

		//セーブデータ・ロード画面ループ
		SAVEDATA_LOAD_LOOP();
	}
	return 0;
}

namespace {
	//削除後のメッセージ
	static void DELETE_MESSAGE() {

		MessageBoxOk("削除しました！");
	}

	//削除後の処理(サウンドノベル風)
	static void DELETE_SOUNDNOVEL() {

		//サウンドノベル風描画時の処理
		SOUNDNOVEL();

		GAMEMENU_COUNT = true;
	}

	//削除後の処理(ウインドウ風)
	static void DELETE_WINDOWNOVEL() {

		//削除後の処理(ウインドウ風)
		WINDOWNOVEL();

		GAMEMENU_COUNT = true;
	}

	static void DeleteSaveData(const char* Message, const char* ImagePath, const char* SaveDataPath) {
		if (IDYES == MessageBoxYesNo(Message)) {
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
	void SAVEDATA_1_DELETE() {
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

		while (ProcessMessage() == 0 && MoveKey(Key) == 0 && false == GAMEMENU_COUNT) {

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

			if (SAVE_y == save_base_pos_y && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == save_base_pos_y && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				//セーブデータ1削除処理
				SAVEDATA_1_DELETE();
				WaitTimer(300);
			}

			if (SAVE_y == (save_base_pos_y * 2) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (save_base_pos_y * 2) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				//セーブデータ2削除処理
				SAVEDATA_2_DELETE();
				WaitTimer(300);
			}

			if (SAVE_y == (save_base_pos_y * 3) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (save_base_pos_y * 3) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

				//セーブデータ3削除処理
				SAVEDATA_3_DELETE();
				WaitTimer(300);
			}

			if (SAVE_y == (save_base_pos_y * 4) && CheckHitKey(KEY_INPUT_RETURN) == 1 || SAVE_y == (save_base_pos_y * 4) && (GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				if (IDYES == MessageBoxYesNo("戻りますか？")) {

					ClearDrawScreen();

					//ショートカットキー時の事後処理
					SHORTCUT_KEY_DRAW();
					WaitTimer(300);//キー判定消去待ち目的ではない
					break;
				}
				WaitTimer(300);
			}
		}
	}
}

//セーブデータ削除処理
void SAVEDATA_DELETE() {
	if (IDYES == MessageBoxYesNo("セーブデータ削除画面に移行しますか？")) {

		ClearDrawScreen();
		SAVE_y = save_base_pos_y;

		//セーブ時のスクリーンショット読込
		SAVEDATA_SCREENSHOT_READ();

		//セーブデータ削除画面ループ
		SAVEDATA_DELETE_LOOP();
	}
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

//セーブデータ用スクリーンショット取得(選択肢画面)
void SCRIPT_OUTPUT_CHOICE_LOOP_SAVESNAP() {

	if (SAVESNAP_CHOICE == 1) {

		SaveDrawScreenToPNG(0, 0, 640, 480, "DATA/SAVE/SAVESNAP_CHOICE.png", 0);

		SAVESNAP_CHOICE = LoadGraph("DATA/SAVE/SAVESNAP_CHOICE.png", 0);
	}
}

//マウス操作(セーブ画面関連)
void Mouse_Move_SAVE(int MouseY) {

	if (false == GAMEMENU_COUNT && EndFlag != 99 || EndFlag == 99) {
		SAVE_y = (MouseY <= 199) ? 100
			: (MouseY <= 299) ? 200
			: (MouseY <= 399) ? 300
			: 400;
	}
}
