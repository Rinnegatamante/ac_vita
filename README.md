# Assassin's Creed: Altair Chronicles Vita

<p align="center"><img src="./screenshots/game.png"></p>

This is a wrapper/port of <b>Assassin's Creed: Altair Chronicles</b> for the *PS Vita*.

The port works by loading the official Android/Xperia ARMv6/Armv7 executable in memory, resolving its imports with native functions and patching it in order to properly run.
By doing so, it's basically as if we emulate a minimalist Android environment in which we run natively the executable as is.

## Changelog

### v.0.9

- Initial release.

## Note

- This port works with both the Android and Xperia build of the game. In order to achieve the best result, it's highly recommended to use the Xperia build (v.1.0.2) of the game since it has native physical buttons support.
- There are some issues with audio voiced sequences playing sometimes in incorrect oders.
- There are some border glitches on some 2D sprites.
- There are some issues in which pause menu and analogs movement can stop working in certain levels (Dpad movement will still work fine).

## Setup Instructions (For End Users)

In order to properly install the game, you'll have to follow these steps precisely:

- Install [kubridge](https://github.com/TheOfficialFloW/kubridge/releases/) and [FdFix](https://github.com/TheOfficialFloW/FdFix/releases/) by copying `kubridge.skprx` and `fd_fix.skprx` to your taiHEN plugins folder (usually `ux0:tai`) and adding two entries to your `config.txt` under `*KERNEL`:
  
```
  *KERNEL
  ux0:tai/kubridge.skprx
  ux0:tai/fd_fix.skprx
```

**Note** Don't install fd_fix.skprx if you're using rePatch plugin

- **Optional**: Install [PSVshell](https://github.com/Electry/PSVshell/releases) to overclock your device to 500Mhz.
- Install `libshacccg.suprx`, if you don't have it already, by following [this guide](https://samilops2.gitbook.io/vita-troubleshooting-guide/shader-compiler/extract-libshacccg.suprx).
- Obtain your copy of *Assassin's Creed: Altair Chronicles* legally for Android or Sony Xperia Play in form of an `.apk` file and an `.obb` file. [You can get all the required files directly from your phone](https://stackoverflow.com/questions/11012976/how-do-i-get-the-apk-of-an-installed-app-without-root-access) or by using an apk extractor you can find in the play store.
- Open the apk with your zip explorer and extract the file `libassissinscreed.so` from the `lib/armeabi-v7a` or `lib/armeabi` folder to `ux0:data/assassins`. 
- Open the obb with your zip explorer and extract the `gameloft` folder inside it in `ux0:data/assassins`.

## Build Instructions (For Developers)

In order to build the loader, you'll need a [vitasdk](https://github.com/vitasdk) build fully compiled with softfp usage.  
You can find a precompiled version here: https://github.com/vitasdk/buildscripts/actions/runs/1102643776.  
Additionally, you'll need these libraries to be compiled as well with `-mfloat-abi=softfp` added to their CFLAGS:

- [SoLoud](https://github.com/vitasdk/packages/blob/master/soloud/VITABUILD)

- [libmathneon](https://github.com/Rinnegatamante/math-neon)

  - ```bash
    make install
    ```

- [vitaShaRK](https://github.com/Rinnegatamante/vitaShaRK)

  - ```bash
    make install
    ```

- [kubridge](https://github.com/TheOfficialFloW/kubridge)

  - ```bash
    mkdir build && cd build
    cmake .. && make install
    ```

- [vitaGL](https://github.com/Rinnegatamante/vitaGL)

  - ````bash
    make SOFTFP_ABI=1 NO_DEBUG=1 HAVE_CIRCULAR_VERTEX_POOL=2 USE_SCRATCH_MEM=1 DRAW_SPEEDHACK=2 PHYCONT_ON_DEMAND=1 install
    ````

After all these requirements are met, you can compile the loader with the following commands:

```bash
mkdir build && cd build
cmake .. && make
```

## Credits

- TheFloW for the original .so loader and initial port of the game.
