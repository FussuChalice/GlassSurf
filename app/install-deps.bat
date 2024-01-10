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

mkdir dll lib include
cd ..

:: Copy files
copy ".\tools\vcpkg\installed\x64-windows\bin\*.dll" ".\deps\dll\"
copy ".\tools\vcpkg\installed\x64-windows\lib\*.lib" ".\deps\lib\"
xcopy ".\tools\vcpkg\installed\x64-windows\include\*" ".\deps\include\" /E /I /Y

python ./tools/rmv.py -b .\deps\include\


::Generate copyright
python ./tools/cprgen.py -s .\tools\vcpkg\installed\x64-windows\share\ -o .\deps\COPYRIGHT.txt