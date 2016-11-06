# TeXCompiler #
This is a [Notepad++ plugin](https://notepad-plus-plus.org/contribute/plugin-howto.html) which compiles `.tex` files in the editor.
## Compile ##
Use VS Command Prompt (mind your Notepad++ executable: x86 or 64)
For me it is the folllowing.

    "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86
    compile.cmd

## Configure ##
Use the sample configuration file `config.txt`. Copy that file under

    %localappdata%\TeXCompiler\config.txt

You can give any three commands which will be executed one after the other.
You can use macros like
* $(FULLCURRENTPATH)
* $(CURRENTDIRECTORY)
* $(FileName)
