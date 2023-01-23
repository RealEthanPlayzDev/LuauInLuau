# LuauInLuau
Inspired by @Rerumu's [LuauInLuau](https://gist.github.com/Rerumu/ecaf1de2f2b31d0fa91b9bac8e1e15d8), I've created this repository to translate Luau to Luau.

## Features
- Running Luau code (with or without safe env)
- Compiling Luau code into bytecode

## Getting LuauInLuau
You can get it from releases or compile using the following instruction: (they were tested in Linux, WSL2 to be specific, using bash)
1. Clone this repository
2. Initialize all submodules
3. Install emsdk (``cd emsdk && ./emsdk install latest && ./emsdk activate latest && cd ..``)
4. Compile this project into WebAssembly (``sh build.sh``, make sure cmake, clang/gcc, and llvm is installed)
5. Use Wasynth to translate the WebAssembly to Luau (``wasm2luau LuauInLuau.wasm > LuauInLuau.luau``)
6. Copy over the contents of ``ExtraCodeSnippet.txt`` (at the ``snippets`` folder) and comment out the old returned function generated by Wasynth, _you might need to change some things if theres a breaking change update_.
7. (ONLY NEEDED IF RUNNING VANILLA LUAU) Copy the contents of ``Vector3Table.txt`` (at the ``snippets`` folder) to the top of the script, no changes should be required, you need this to have the script work at vanilla Luau (like the luau repl for example) as Wasynth uses Roblox's Vector3 datatype (the snippet checks for the existence of the V3 global and if it doesn't exist then it recreates it + overriding type and typeof for getting the V3 datatype). Alternatively compile Wasynth with ``default-features = false``, since it will include the Vector3 table implementation directly without any need of user interference. (Thanks @Rerumu for the Wasynth compile tip)

## How it works and a bit of a motivation background
I've started working on this around December 2022, where I found @Rerumu's LuauInLuau gist which caught my interest since I've been looking for a Luau compiler and interpreter written in Luau, the way it works was pretty simple, you compile C++ code into WebAssembly and use @Rerumu's [Wasynth](https://github.com/Rerumu/Wasynth) to translate WebAssembly to Luau, @Rerumu and a few others in their server had helped me with this process. I was then able to produce a working LuauInLuau for version 0.556.

Now skipping to January 14 2023, I've come back to this little project under one goal, to be able to compile Luau code and have the bytecode string in Luau, I could have just directly used ``luau_compile`` but when I first started trying things, I was too stupid to understand how Wasynth even handles loading and storing string and integers.

My solution? Make a C++ program to wrap around those functions! Yes, that is why there is C++ code in this repository, albeit the functions weren't exported independently and I still had to learn how to load and store things myself, thanks to the cleaner generated code however, I was able to understand the basic principle of how it works. In the end I was able to export functions to run and compile Luau code respectively.

## Credits
- [Luau](https://github.com/Roblox/luau) - The Roblox Luau repository
- [emsdk](https://github.com/emscripten-core/emsdk) - Emscripten SDK for compiling C++ -> WebAssembly
- [Wasynth](https://github.com/Rerumu/Wasynth) - WebAssembly -> Luau translation tool
- [The original LuauInLuau](https://gist.github.com/Rerumu/ecaf1de2f2b31d0fa91b9bac8e1e15d8) - What started this project, and used some code from it.
- [Fiu](https://github.com/TheGreatSageEqualToHeaven/Fiu) - Used their Luau bytecode version verification code

## Acknowledgements
- @Roblox and Luau contributors
- Emscripten contributors and creators
- @Rerumu
- @TheGreatSageEqualToHeaven