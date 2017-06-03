#include "utility.hpp"
#include <DxLib.h>
int MessageBoxYesNo(LPCTSTR lpText) noexcept
{
	return MessageBox(
		DxLib::GetMainWindowHandle(),
		lpText,
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);
}
int LINKS_MessageBox_OK(LPCTSTR lpText) noexcept
{
	return MessageBox(
		DxLib::GetMainWindowHandle(),
		lpText,
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_OK
	);
}

//画面クリア処理関数
void SCREEN_CLEAR() noexcept {
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	SetDrawScreen(DX_SCREEN_FRONT);
}
