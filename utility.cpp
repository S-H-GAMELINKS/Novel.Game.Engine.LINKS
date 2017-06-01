#include "utility.hpp"
#include <DxLib.h>
int LINKS_MessageBox_YESNO(LPCTSTR lpText)
{
	return MessageBox(
		DxLib::GetMainWindowHandle(),
		lpText,
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_YESNO
	);
}
int LINKS_MessageBox_OK(LPCTSTR lpText)
{
	return MessageBox(
		DxLib::GetMainWindowHandle(),
		lpText,
		"ゲームリンクス制作のノベルゲームエンジン「LINKS」",
		MB_OK
	);
}
