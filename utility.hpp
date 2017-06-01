#ifndef LINKS_UTILITY_HPP_
#define LINKS_UTILITY_HPP_
#include <Windows.h>
//Yes/Noのメッセージボックス
int LINKS_MessageBox_YESNO(LPCTSTR lpText);
int LINKS_MessageBox_OK(LPCTSTR lpText);
constexpr bool isdigit(char c) { return '0' <= c && c <= '9'; }
constexpr unsigned int ctoui(char c) { return c - '0'; }
#endif
