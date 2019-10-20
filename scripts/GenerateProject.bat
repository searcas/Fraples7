@echo off
pushd %~dp0\..\
call vendor\ven\premake\premake5.exe vs2019
popd
PAUSE