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

## 首先安装Qt开发环境
1 下载qt-opensource-windows-x86-x.x.x.exe安装包
2 选择组件的时候，勾选 Tools（Qt Creator）

## 安装MSYS2，并更新为最新
1 到这里下载最新的安装包 https://www.msys2.org
2 修改镜像源，否则更新太慢
3 pacman -Syu 更新到最新的组件 
4 安装编译的依赖
pacman -S  git mingw-w64-x86_64-gcc mingw-w64-x86_64-binutils mingw-w64-x86_64-make base-devel mingw-w64-x86_64-qt5 mingw-w64-x86_64-pkg-config mingw-w64-x86_64-mpv mingw-w64-x86_64-libzip mingw-w64-x86_64-jbigkit mingw-w64-x86_64-mpg123

## 导入项目
将项目Baka-MPlayer\src\Baka-MPlayer.pro导入到 Qt Creator

## Windows 下编译出中文版本
需要在qmake处增加额外的参数："CONFIG+=embed_translations"