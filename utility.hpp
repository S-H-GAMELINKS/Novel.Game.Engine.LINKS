#ifndef LINKS_UTILITY_HPP_
#define LINKS_UTILITY_HPP_
#include <Windows.h>

int LINKS_MessageBox_YESNO(LPCTSTR lpText) noexcept;
int LINKS_MessageBox_OK(LPCTSTR lpText) noexcept;
//画面クリア処理関数
void SCREEN_CLEAR() noexcept;

constexpr bool isdigit(char c) noexcept { return '0' <= c && c <= '9'; }
constexpr unsigned int ctoui(char c) noexcept { return c - '0'; }
#endif
