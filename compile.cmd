cl /EHsc /D "_UNICODE" /D "UNICODE" /MT /Zc:wchar_t *.cpp kernel32.lib user32.lib gdi32.lib Shell32.lib /link /DYNAMICBASE /DLL /out:TeXCompiler.dll