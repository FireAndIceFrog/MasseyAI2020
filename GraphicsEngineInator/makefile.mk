main.exe		: 	main.o algorithm.o graphics2.o 
	g++ -std=c++11  -Wl,-s -o main.exe main.o algorithm.o graphics2.o -l gdi32 -static-libgcc -static-libstdc++
			
main.o		:	main.cpp algorithm.h graphics2.h
	g++ -std=c++11  -c -fpermissive -fconserve-space main.cpp
	
algorithm.o		:	 algorithm.cpp algorithm.h
	g++ -std=c++11  -c -fpermissive -fconserve-space algorithm.cpp		

graphics2.o		:	 graphics2.cpp graphics2.h
	g++ -std=c++11  -c -fpermissive -fconserve-space -Wno-write-strings  graphics2.cpp

clean:
	del *.o
	del *.exe
