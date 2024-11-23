# [Baka MPlayer](http://bakamplayer.u8sand.net)

[![Build Status](https://travis-ci.org/u8sand/Baka-MPlayer.svg?branch=master)](https://travis-ci.org/u8sand/Baka-MPlayer)

--------------


## Overview

Baka MPlayer is a free and open source, cross-platform, **libmpv** based multimedia player.
Its simple design reflects the idea for an uncluttered, simple, and enjoyable environment for watching tv shows.


## Requirements

* gcc
* pkg-config
* libmpv-dev
* qtbase5-dev (>= 5.2.0)
  * qt5-qmake
  * qttools5-dev-tools
  * qtdeclarative5-dev
  * libqt5svg5-dev
  * libqt5x11extras5-dev
  * libqt5network5
* youtube-dl (optional, for streaming youtube videos)

Note: Packages may be named slightly different for each distro

### Get the font

Baka MPlayer was designed around the font called Noto Sans. Noto Sans was used because of its open source nature and its broad support for Unicode characters. Having the correct font installed insures that what you see is what was intended.

[Get it here.](https://www.google.com/get/noto/#sans-lgc)


## Compilation

### Windows

These instructions are for cross-compiling for Windows on a Linux system (Note: the architecture can be either `x86_64` or `i686` depending on which platform you're compiling for).
```
git clone -b release https://github.com/u8sand/Baka-MPlayer.git
cd "Baka-MPlayer"
mkdir build
cp -r windows/cross-compilation/* build/
cd build
arch=x86_64
./baka-build.sh $arch
```
This is a very long process because you'll need to build the mingw32 toolchain `mxe` and all dependent libraries, `libmpv.a`, and finally `baka-mplayer.exe`. If everything succeeded without error, you'll get `Baka-MPlayer.$arch.zip` which should contain everything you need.

To rebuild simply delete the directory (in build) or the .zip file of what you need to rebuild and re-run `./baka-build.sh $arch`.

To add custom patches, put them in `src/patches/` prefixed with the name of what you're patching.

### Linux

If your distribution does not provide a package, you can compile it from source.
However we've made scripts for some distributions. See `etc/sbin/linux/`.
```
git clone -b release https://github.com/u8sand/Baka-MPlayer.git
cd "Baka-MPlayer"
mkdir build
cp -r linux/* build/
cd build
distro=debian_based
./$distro.sh
```
If this doesn't work or the distro you use is not listed here, you'll need to build mpv and then Baka MPlayer (the dependencies above are for Baka MPlayer). For help building mpv see `https://github.com/mpv-player/mpv-build`. Compiling Baka MPlayer from source can be done like so:
```
git clone -b release https://github.com/u8sand/Baka-MPlayer.git
cd "Baka-MPlayer"
./configure
make -j `grep -c ^processor /proc/cpuinfo`
sudo make install
```
The configuration file will be created on first run and will be written to `~/.config/bakamplayer.ini`.

### macOS

As of right now you have to compile from source.
You require some more dependencies which you can get from homebrew:
```
brew install youtube-dl
brew install mpv --with-libmpv
git clone -b release https://github.com/u8sand/Baka-MPlayer.git
cd Baka-MPlayer
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
brew install qt5
export QMAKE=/usr/local/Cellar/qt5/5*/bin/qmake
./configure CONFIG+=install_translations
make
open build
```
Then drag the app to your Applications folder.
In the future there will be a brew formula to simplify this.

Similarly to Linux, the configuration file will be created on first run and will be written to `~/.config/bakamplayer.ini`.

### Other languages

By default, Baka MPlayer will compile in English if no language is specified during compilation. To compile a multi-lingual version of baka-mplayer, configure it like so:

    ./configure CONFIG+=install_translations

For more configuration options see the `configure` source file or read the manual.

You can check out which languages we currently support by checking out `Baka-MPlayer/src/translations/`.


## Bug reports

Please use the [issues tracker](https://github.com/u8sand/Baka-MPlayer/issues) provided by GitHub to send us bug reports or feature requests.


## Contact

**IRC Channel**: `#baka-mplayer` on `irc.freenode.net`

You can ask us questions about using Baka MPlayer, give feedback, or discuss its development.
However, if possible, please avoid posting bugs there and use the [issue tracker](https://github.com/u8sand/Baka-MPlayer/issues) instead.

## 安装MSYS2，并更新为最新
1. 到这里下载最新的安装包 https://www.msys2.org
2. 修改镜像源，否则更新太慢
3. pacman -Syu 更新到最新的组件 
4. 安装编译的依赖
5. 将 xx\mingw64\bin 路径加入Path环境变量中。这个只是方便后续使用 mingw64 下面的一些命令，非必须
```
pacman -S --needed base-devel mingw-w64-x86_64-toolchain

pacman -S git mingw-w64-x86_64-gcc mingw-w64-x86_64-binutils mingw-w64-x86_64-make base-devel mingw-w64-x86_64-qt5 mingw-w64-x86_64-pkg-config mingw-w64-x86_64-mpv mingw-w64-x86_64-libzip mingw-w64-x86_64-jbigkit mingw-w64-x86_64-mpg123
```

## 安装Qt开发环境
1. 下载Qt5.15.2-Windows-x86_64-MinGW8.1.0-20201214.7z，解压出来作为Qt的基础依赖
2. 下载qt-creator-opensource-windows-x86_64-5.0.3.exe，安装qt开发工具，kits配置好mingw的编译器，qt版本

## 导入项目
将项目Baka-MPlayer\src\Baka-MPlayer.pro导入到 Qt Creator

## Windows 下编译出中文版本
需要在qmake处增加额外的参数："CONFIG+=embed_translations"

## 下载 libmpv 放到 Baka-MPlayer\src\mpv 目录
https://github.com/zhongfly/mpv-winbuild/releases
https://sourceforge.net/projects/mpv-player-windows/files/libmpv/
这里可以下载最新版的libmpv

## 下载 youtube-dl 放到 Baka-MPlayer\src\youtube-dl 目录
https://github.com/ytdl-org/youtube-dl/releases
这里可以下载最新版的youtube-dl

## 动态编译，查找依赖的dll，生成绿色软件包
1. ### 将release生成exe放到一个单独的文件夹 
	C:\Users\admin\Desktop\baka-mplayer\

2. ### qt相关的依赖可以通过这个命令得到
	通过 MSYS2 MinGW 64-bit 命令界面  windeployqt.exe /c/Users/admin/Desktop/baka-mplayer/baka-mplayer.exe

3. ### mingw相关的依赖，可以通过以下两种方式得到
	3.1 Dependencies.exe  -modules C:\Users\admin\Desktop\baka-mplayer\baka-mplayer.exe | findstr "mingw"  
	Dependencies.exe 这个可以到这里下载 https://github.com/lucasg/Dependencies/releases

	3.2 通过 MSYS2 MinGW 64-bit 命令界面  ldd.exe /c/Users/admin/Desktop/baka-mplayer/baka-mplayer.exe | grep "mingw"
	
	通过上面两种方法之一，拿到依赖的dll后，再通过文本处理，变为一个批量复制dll到C:\Users\admin\Desktop\baka-mplayer的cmd命令，运行这个cmd命令，就可以把所有依赖的dll都复制过来了

## 静态编译
安装静态版本的qt5 
```
pacman -S mingw-w64-x86_64-qt5-static
```
将mpv-1.dll复制到生成的baka-mplayer.exe的文件夹，然后就能运行了，还可以将流媒体支持的youtube-dl.exe一并复制过来。

