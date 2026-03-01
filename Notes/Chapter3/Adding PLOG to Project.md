# ✅ Integrating `plog` (Release Archive Version) into VS Code + g++-13

Since you downloaded the release ZIP, your folder is likely named:

```
external/plog-1.1.11/
```

Inside it, the headers live in:

```
external/plog-1.1.11/include/plog/
```

Because `plog` is **header-only**, you do not need to link anything — only include paths matter.

---

# 1️⃣ Add the Plog Source Code

If using the ZIP release (like you did):

1. Create an `external` folder in your workspace root.
    
2. Extract the archive there.
    

Your structure should look like:

```
workspace/
├── .vscode/
├── learncpp/
└── external/
    └── plog-1.1.11/
        └── include/
            └── plog/
                ├── Log.h
                ├── Init.h
                ├── Formatters/
                └── Initializers/
```

⚠️ Important: The include flag must point to the **`include`** folder — not the root of `plog-1.1.11`.

---

# 2️⃣ Update IntelliSense (`c_cpp_properties.json`)

Because you are using `plog-1.1.11`, update the include path accordingly.

```json
{
  "configurations": [
    {
      "name": "Linux",
      "includePath": [
        "${workspaceFolder}/**",
        "${workspaceFolder}/external/plog-1.1.11/include"
      ],
      "defines": [],
      "compilerPath": "/usr/bin/g++-13",
      "cStandard": "c11",
      "cppStandard": "c++23",
      "intelliSenseMode": "linux-gcc-x64"
    }
  ],
  "version": 4
}
```

This ensures VS Code can resolve:

```cpp
#include <plog/Log.h>
```

---

# 3️⃣ Update Build Tasks (`tasks.json`)

Your compiler needs the same include path.

Update your task arguments to:

```json
{
    "type": "cppbuild",
    "label": "C/C++: g++-13 build active file",
    "command": "/usr/bin/g++-13",
    "args": [
        "-fdiagnostics-color=always",
        "-g",
        "-std=c++23",
        "-pedantic-errors",
        "-Wall",
        "-Wextra",
        "-Wconversion",
        "-Wsign-conversion",
        "-I${workspaceFolder}/external/plog-1.1.11/include",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}"
    ]
}
```

That `-I` flag must exactly match your folder name.

---

# 4️⃣ Correct Test File (Updated)

Previously you hit this error:

```
‘TxtFormatter’ is not a member of ‘plog’
```

That happened because formatters must be explicitly included.

Here is a **working test file**:

```cpp
#include <iostream>

#include <plog/Log.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Formatters/TxtFormatter.h>

int main()
{
    plog::init<plog::TxtFormatter>(plog::debug, plog::streamStdOut);

    std::cout << "Standard std::cout message.\n";

    PLOG_DEBUG << "Debug message";
    PLOG_INFO  << "Info message";
    PLOG_ERROR << "Error message";

    return 0;
}
```

---

# ✅ Alternative (Simpler) Initialization

If you prefer not specifying a formatter manually, you can use:

```cpp
#include <plog/Log.h>
#include <plog/Initializers/ColorConsoleInitializer.h>

int main()
{
    plog::init(plog::debug, plog::streamStdOut);

    PLOGI << "Info log";
}
```

That initializer already selects a default formatter internally.

---

# 🎯 Summary of What Changed

Because you downloaded:

```
plog-1.1.11
```

You must use:

```
external/plog-1.1.11/include
```

instead of:

```
external/plog/include
```

And when using custom formatters like `TxtFormatter`, you must include:

```cpp
#include <plog/Formatters/TxtFormatter.h>
```
