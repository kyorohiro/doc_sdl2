dir /b/s *.bc > a.txt
dir /b/s *.o >> a.txt
dir /b/s *.js >> a.txt
dir /b/s *.html >> a.txt
dir /b/s *.exe >> a.txt

FOR /F %k in (a.txt) DO del %k

del a.txt
