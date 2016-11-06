RC /I"inc/" res\TeXCompiler.rc
CL /EHsc /GL /Ox /W3 /GS /Os /D_UNICODE /DUNICODE /MT /I"inc/" /Zc:wchar_t res/TeXCompiler.res src/*.cpp kernel32.lib user32.lib gdi32.lib Shell32.lib /link /DLL /out:TeXCompiler.dll
