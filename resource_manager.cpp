#include "resource_manager.hpp"
#include "utility.hpp"
#include "fmt/fmt/format.h"
#include <DxLib.h>

//
// Global variables
//
ImageResourceManager charactor = {};
ImageResourceManager background = {};
SoundResourceManager backgroundMusic = {};
SoundResourceManager soundEffect = {};

//
// Test
//
static_assert(ResourceManagerBase::resource_limit_num < MAX_IMAGE_NUM, "err");
static_assert(ResourceManagerBase::resource_limit_num < MAX_SOUND_NUM, "err");

//
// Definition
//
ResourceManagerBase::ResourceManagerBase() noexcept : resources_(), activeResource_(-1) {}

int ResourceManagerBase::activeResource() const noexcept
{
	return this->activeResource_;
}

void ResourceManagerBase::activeResource(int handle) noexcept
{
	this->activeResource_ = handle;
}

void ResourceManagerBase::reset() noexcept
{
	this->activeResource(-1);
}

bool ResourceManagerBase::select(char c0, char c1) noexcept
{
	if (isdigit(c0) && isdigit(c1)) {
		const size_t charactorNumber = (ctoui(c0) * 10) + ctoui(c1) - 1;
		if (resource_limit_num <= charactorNumber) return false;
		this->activeResource_ = this->resources_[charactorNumber];
		return true;
	}
	return false;
}

ImageResourceManager::ImageResourceManager() noexcept : ResourceManagerBase() {}

bool ImageResourceManager::load(const TCHAR * format) noexcept
{
	try {
		for (std::size_t i = 0; i < resource_limit_num; ++i) {
			this->resources_[i] = DxLib::LoadGraph(fmt::format(format, i + 1).c_str());
		}
		return true;
	} catch (...) {
		return false;
	}
}

int ImageResourceManager::DrawGraph(int x, int y, bool transFlag) noexcept
{
	if (0 < this->activeResource()) return DxLib::DrawGraph(x, y, this->activeResource(), transFlag);
	return -1;
}

int ImageResourceManager::DrawRectGraph(int destX, int destY, int srcX, int srcY, int width, int height, bool transFlag, bool turnFlag) noexcept
{
	if (0 < this->activeResource()) return DxLib::DrawRectGraph(destX, destY, srcX, srcY, width, height, this->activeResource(), transFlag,turnFlag);
	return -1;
}

int ImageResourceManager::DerivationGraph(int srcX, int srcY, int width, int height) noexcept
{
	if (0 < this->activeResource()) return DxLib::DerivationGraph(srcX, srcY, width, height, this->activeResource());
	return -1;
}

SoundResourceManager::SoundResourceManager() noexcept : ResourceManagerBase() {}

bool SoundResourceManager::load(const TCHAR * format) noexcept
{
	try {
		for (std::size_t i = 0; i < resource_limit_num; ++i) {
			this->resources_[i] = DxLib::LoadSoundMem(fmt::format(format, i + 1).c_str());
		}
		return true;
	}
	catch (...) {
		return false;
	}
}

int SoundResourceManager::changeVolume(int volumePal) noexcept
{
	return DxLib::ChangeVolumeSoundMem(volumePal, this->activeResource());
}

int SoundResourceManager::play(int playType, bool topPositionFlag) noexcept
{
	return DxLib::PlaySoundMem(this->activeResource(), playType, topPositionFlag);
}

int SoundResourceManager::stop() noexcept
{
	return DxLib::StopSoundMem(this->activeResource());
}
