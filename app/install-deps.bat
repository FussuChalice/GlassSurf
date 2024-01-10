:: Cloning VCPKG
cd ./tools

git clone https://github.com/Microsoft/vcpkg.git
cd ./vcpkg

call "bootstrap-vcpkg.bat"

:: Installing packages
.\vcpkg.exe install opencv4 --triplet x64-windows
.\vcpkg.exe install winreg --triplet x64-windows
.\vcpkg.exe install argparse --triplet x64-windows
.\vcpkg.exe install gtk --triplet x64-windows

:: Making directories for deps
cd ..
cd ..

mkdir deps
cd ./deps

mkdir debug release

cd ./debug
mkdir dll lib include
cd ..

cd ./release
mkdir dll lib include
cd ..
cd ..

:: Copy files

:: Release
copy ".\tools\vcpkg\installed\x64-windows\bin\*.dll" ".\deps\release\dll\"
copy ".\tools\vcpkg\installed\x64-windows\lib\*.lib" ".\deps\release\lib\"
xcopy ".\tools\vcpkg\installed\x64-windows\include\*" ".\deps\release\include\" /E /I /Y

python ./tools/rmv.py -b .\deps\release\include\

:: Debug
copy ".\tools\vcpkg\installed\x64-windows\debug\bin\*.dll" ".\deps\debug\dll\"
copy ".\tools\vcpkg\installed\x64-windows\debug\lib\*.lib" ".\deps\debug\lib\"
xcopy ".\tools\vcpkg\installed\x64-windows\include\*" ".\deps\debug\include\" /E /I /Y

python ./tools/rmv.py -b .\deps\debug\include\

::Generate copyright
python ./tools/cprgen.py -s .\tools\vcpkg\installed\x64-windows\share\ -o .\deps\COPYRIGHT.txt