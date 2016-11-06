# TeXCompiler #
This is a [Notepad++ plugin](https://notepad-plus-plus.org/contribute/plugin-howto.html) which compiles `.tex` files in the editor.
## Compile ##
Use [VS Command Prompt](https://msdn.microsoft.com/en-us/library/f2ccy3wt.aspx) (mind your Notepad++ executable: x86 or 64)
For example.

    "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86
    compile.cmd

## Configure ##
Use the sample configuration file `config.txt`. Copy that file under

    %localappdata%\TeXCompiler\config.txt

You can give any three commands which will be executed one after the other.
You can use macros like
* `$(FULLCURRENTPATH)`
* `$(CURRENTDIRECTORY)`
* `$(FileName)`
