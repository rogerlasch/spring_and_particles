@echo off
IF EXIST *.exe( del *.exe)
IF EXIST *.obj (del *.obj)
cl /nologo /EHsc /std:c++latest /c /I "dependencies" *.cpp
link /nologo /INCREMENTAL:NO /out:main.exe /MACHINE:X86 /MANIFEST:NO /LIBPATH:"dependencies\lib\x86" *.obj fmod_vc.lib
