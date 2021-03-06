﻿/*=============================================================================
  Copyright (c) 2017 S.H.(GAMELINKS)
  https://github.com/S-H-GAMELINKS/Novel.Game.Engine.LINKS
  This software is released under the MIT License, see LICENSE.
=============================================================================*/
#ifndef LINKS_UTILITY_HPP_
#define LINKS_UTILITY_HPP_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cassert>

#ifdef NDEBUG
#	define LINKS_EXPECT_TRUE(expression) expression
#else
#	define LINKS_EXPECT_TRUE(expression) assert(expression)
#endif

int MessageBoxYesNo(LPCTSTR lpText) noexcept;
int MessageBoxOk(LPCTSTR lpText) noexcept;
//画面クリア処理関数
void SCREEN_CLEAR() noexcept;

constexpr bool isdigit(char c) noexcept { return '0' <= c && c <= '9'; }
constexpr unsigned int ctoui(char c) noexcept { return c - '0'; }
#endif
