#ifndef LINKS_RESOURCE_MANAGER_HPP_
#define LINKS_RESOURCE_MANAGER_HPP_
#include <cstddef>
#ifdef __c2__
#include <Windows.h>
#endif
#include <tchar.h>

//
// forward decreation
//
class ImageResourceManager;
class SoundResourceManager;

//
// Global variables
//
extern ImageResourceManager charactor;
extern ImageResourceManager background;
extern SoundResourceManager backgroundMusic;
extern SoundResourceManager soundEffect;

//
// Definition
//
class ResourceManagerBase {
public:
	static constexpr std::size_t resource_limit_num = 99;
protected:
	int resources_[resource_limit_num];
private:
	int activeResource_;
public:
	ResourceManagerBase() noexcept;
	ResourceManagerBase(const ResourceManagerBase&) = delete;
	ResourceManagerBase(ResourceManagerBase&&) = delete;
	ResourceManagerBase& operator=(const ResourceManagerBase&) = delete;
	ResourceManagerBase& operator=(ResourceManagerBase&&) = delete;
	int activeResource() const noexcept;
	void activeResource(int handle) noexcept;
	void reset() noexcept;
	bool select(char c0, char c1) noexcept;
};
class ImageResourceManager : public ResourceManagerBase {
public:
	ImageResourceManager() noexcept;
	ImageResourceManager(const ImageResourceManager&) = delete;
	ImageResourceManager(ImageResourceManager&&) = delete;
	ImageResourceManager& operator=(const ImageResourceManager&) = delete;
	ImageResourceManager& operator=(ImageResourceManager&&) = delete;
	bool load(const TCHAR* format) noexcept;
	int DrawGraph(int x, int y, bool transFlag) noexcept;
	int DrawRectGraph(int destX, int destY, int srcX, int srcY, int width, int height, bool transFlag, bool turnFlag = false) noexcept;
	int DerivationGraph(int srcX, int srcY, int width, int height) noexcept;
};
class SoundResourceManager : public ResourceManagerBase {
public:
	SoundResourceManager() noexcept;
	SoundResourceManager(const SoundResourceManager&) = delete;
	SoundResourceManager(SoundResourceManager&&) = delete;
	SoundResourceManager& operator=(const SoundResourceManager&) = delete;
	SoundResourceManager& operator=(SoundResourceManager&&) = delete;
	bool load(const TCHAR* format) noexcept;
	int changeVolume(int volumePal) noexcept;
	int play(int playType, bool topPositionFlag = true) noexcept;
	int stop() noexcept;
};
#endif
