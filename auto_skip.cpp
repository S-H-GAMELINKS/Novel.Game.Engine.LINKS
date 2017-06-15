/*=============================================================================
  Copyright (c) 2017 S.H.(GAMELINKS)
  https://github.com/S-H-GAMELINKS/Novel.Game.Engine.LINKS
  This software is released under the MIT License, see LICENSE.
=============================================================================*/
#include "auto_skip.hpp"
#include "GAME.h"
#include "save.hpp"

#include <DxLib.h>

enum class Skiptype : int {
	off = 0,
	automatic = 1,
	skip = 2
};

//スキップ・オートモード用変数
static Skiptype skip_auto = Skiptype::off;

void disableSkip() noexcept {
	skip_auto = Skiptype::off;
}

namespace {
	//既読スキップメッセージ
	int SKIP_READ_MESSAGE() noexcept {
		return MessageBoxYesNo("既読スキップを実行しますか？");
	}

	//オート処理メッセージ
	int AUTO_MESSAGE() noexcept {
		return MessageBoxYesNo("オートモードを実行しますか？");
	}

	//オート/スキップ停止処理メッセージ
	int AUTO_SKIP_MESSAGE() noexcept {
		return MessageBoxYesNo("スキップ又はオートモードを終了しますか？");
	}

	//既読スキップ後の処理(サウンドノベル風)
	void SKIP_READ_SOUNDNOVEL() noexcept {
		GAMEMENU_COUNT = true;
		//サウンドノベル風描画時の処理
		SOUNDNOVEL();
	}

	//既読スキップ後の処理(ウインドウ風)
	void SKIP_READ_WINDOWNOVEL() noexcept {
		GAMEMENU_COUNT = true;
		//既読スキップ後の処理(ウインドウ風)
		WINDOWNOVEL();
	}

}
//既読スキップ判定
void SKIP_READ_CHECK() noexcept {
	const SkipDataConv* conv = reinterpret_cast<const SkipDataConv*>(&TextIgnoredFlags);
	//既読データ読み込み時の判定
	if (IDYES == SKIP_READ_MESSAGE() && 0 < EndFlag && EndFlag <= countof(conv->arr) && 1 == conv->arr[EndFlag - 1]) {
		skip_auto = Skiptype::skip;
	}
	//ショートカットキー時の事後処理
	SHORTCUT_KEY_DRAW();
}

//スキップ処理
void SKIP_START() noexcept {
	if (IDYES == MessageBoxYesNo("スキップを実行しますか？")) {
		skip_auto = Skiptype::skip;
		GAMEMENU_COUNT = true;
		//サウンドノベル風描画時の処理
		SOUNDNOVEL();
		//ウインドウ風描画時の処理
		WINDOWNOVEL();
	}
}

//オート処理
void AUTO_START() noexcept {
	if (IDYES == AUTO_MESSAGE()) {
		skip_auto = Skiptype::automatic;
		GAMEMENU_COUNT = true;
		//サウンドノベル風描画時の処理
		SOUNDNOVEL();
		//既読スキップ後の処理(ウインドウ風)
		WINDOWNOVEL();
	}
}

//オート/スキップ停止処理
void AUTO_SKIP_STOP() noexcept {
	if (IDYES == AUTO_SKIP_MESSAGE()) {
		skip_auto = Skiptype::off;
		GAMEMENU_COUNT = true;
		//サウンドノベル風描画時の処理
		SOUNDNOVEL();
		//ウインドウ風描画時の処理
		WINDOWNOVEL();
	}
}

//スクリプトタグ処理(クリック待ち)
void SCRIPT_UTPUT_KEYWAIT() noexcept {
	//セーブデータ用スクリーンショット保存
	SAVESNAP();
	//スキップ・オート変数がＯＦＦの場合
	if (skip_auto == Skiptype::off) {
		// ボタン押し待ちおよび参照文字位置を一つ進める
		DxLib::WaitKey();
		//エンターキーで次へ
		if (DxLib::CheckHitKey(KEY_INPUT_RETURN) == 1 || (DxLib::GetMouseInput() & MOUSE_INPUT_LEFT) == 1) {
			CP++;
		}
	}
	else {
		if (skip_auto == Skiptype::automatic) {
			//少し待って、次の文字列を描画
			DxLib::WaitTimer(1800 * ConfigData.auto_speed / 100);
		}
		CP++;
	}
}

//スクリプトタグ処理(少し待つ)
void SCRIPT_OUTPUT_WAIT() noexcept {
	//オート又は通常時、3秒待つ
	if (skip_auto != Skiptype::skip) {
		DxLib::WaitTimer(1800);
	}
	CP++;
}

//文字列の描画速度
void SCRIPT_OUTPUT_STRING_DRAW_SPEED() noexcept {
	switch (skip_auto) {
	case Skiptype::off:
		// 少し待つ
		DxLib::WaitTimer(30 * ConfigData.string_speed / 100); break;
	case Skiptype::automatic:
		// 少し待つ
		DxLib::WaitTimer(30 * ConfigData.auto_speed / 100); break;
	case Skiptype::skip:
		//速く処理
		DxLib::WaitTimer(10 * ConfigData.skip_speed / 100); break;
	default:
		break;
	}
}
