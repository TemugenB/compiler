# 🏗️ Compiler: The While Language

🧼✨ A comprehensive collection of compiler components developed for the **While** programming language. This repository documents the transition from high-level source code to x86 Assembly, covering lexical analysis, syntax parsing, semantic validation, and final code generation.

---

## 📂 Repository Structure

The project is divided into four main stages, mirroring the architecture of a real-world compiler:

* **`lexical/`**: Tokenizes raw source code using **Flex**.
* **`syntax/`**: Defines the grammar and structure using **Bisonc++**.
* **`semantic/`**: Performs type checking and symbol table management.
* **`code_gen/`**: Translates the validated program into NASM x86 Assembly.

---

## 📚 Core Compiler Concepts

### 🔹 Lexical Analysis (`while.l`)
The part of the compiler that converts raw source code into tokens (e.g., `10` -> `digit`).
* **Longest Match:** The lexer always attempts to match the longest possible string.
* **Rule Priority:** The order of rules in the `.l` file matters; specific keywords must come before general identifiers.
* **Regex Examples:** * Identifiers: `[a-z]|[a-z][a-zA-Z0-9_]*[a-zA-Z0-9]` (Handles underscores and start/end rules).
    * Strings: `\"[^"]+\"` (Matches one or more characters inside double quotes).

### 🔹 Syntax & Semantic Analysis
* **Syntax:** Managed via Bisonc++ to handle operator precedence (e.g., `%left T_MUL T_DIV`).
* **Semantics:** Performs type checking using a **Symbol Table** (mapping names to types like `a -> int`).

### 🔹 Code Generation Schemes
We use **S-Attributed grammars** to synthesize assembly code fragments.
* **Stack Strategy:** To prevent sub-expressions from overwriting the `EAX` register, we use `push` and `pop`.
    * *Example (Addition):* Evaluate `e2` to `EAX` -> `push eax` -> Evaluate `e1` to `EAX` -> `pop ebx` -> `add eax, ebx`.
* **Boolean Logic:** Uses `sete`, `setb`, and `seta` to mirror CPU flags into the `AL` register.


### 🛠️ Workflow on Pandora Server
```bash
# 1. Upload and navigate
scp project.zip user@pandora.inf.elte.hu:~
ssh user@pandora.inf.elte.hu
cd project/

# 2. Build and Run
make
./while tests/01.ok > 01.asm
nasm -felf 01.asm
gcc io.c 01.o -m32 -o compiler_out
./compiler_out
