biên dịch : 
g++ -std=c++23 (Get-ChildItem -Recurse -Filter *.cpp | % FullName) -o app.exe

chạy : ./app