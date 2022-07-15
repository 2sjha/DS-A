# C++ Project Setup in VS Code on Linux.

I'm using the following:

-   OS : Manjaro
-   Editor : Code - OSS
-   C++ Extensions in VSCode : C/C++ Runner by frannck94, which inturn has dependencies on C/C++ by ms-vscode and CodeLLDB by vadimcn
-   Formatting : clang-format
-   Debugger: gdb

## Setup Steps

-   Install Code - OSS and gdb using pacman/yay
-   Install CodeLLDB extension from marketplace.
-   Manually Download and Install 'C'/C++ Runner' & 'C/C++' extension vsix from https://marketplace.visualstudio.com/items?itemName=franneck94.c-cpp-runner and https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools respectively. Please refer https://stackoverflow.com/a/38866913 for more details.

PS: Extension Marketplace tab in Code-OSS did not have Microsoft CppTools extension and it has an older version for C/C++ Runner. I had an issue with the older runner version (3.0.0), where I could not configure the compiler path. No matter however many times I updated the cppCompilerpath config, it kept refreshing to an invalid path. Upon searching, I found out that [it had been fixed in later versions](https://github.com/franneck94/Vscode-C-Cpp-Runner/issues/21#issuecomment-907586590), but since later versions were not available in marketpalce tab directly, I had to manually install those.
