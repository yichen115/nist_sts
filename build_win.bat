set curr_path=%~dp0
set build_dir=%curr_path%build

if exist %build_dir% (
	rd /s /q %build_dir%
)
md %build_dir%

cd %build_dir%

rem ���Գ������õ���OPENSSL�������Լ�ʵ���������
cmake -G"Visual Studio 15" -DOPENSSL_HOME_PATH="c:/openssl" ..

pause
