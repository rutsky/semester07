@echo off

goto :main

:gcd
  set a=%1
  set b=%2

  :loop_start
    if not %a% gtr 0 exit /B %b%
      set /a c=%a%
      set /a a=%b% %% %a%
      set /a b=%c% 
  goto loop_start

:main
call :gcd 42 56
echo %errorlevel%
