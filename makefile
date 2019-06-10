#project name = DemoAppGetPutFileOneDrive = DAGPOD

compile = i686-w64-mingw32
CC 		= $(compile)-gcc
strip 	= $(compile)-strip.exe
exe 	= DAGPOD.exe 
opt 	= -mwindows -mconsole -municode
#  -municode
L 		= -L./lib -lstdc++ -lwinpthread -lwininet -lws2_32
I 		= -I./include
D		= -DMINGW32
#-DUNICODE -D_UNICODE 

all: rm
	$(CC) ./w32/main.cpp -o ./build/debug/$(exe) $(I) $(L) $(opt) $(D)
	cp ./build/debug/$(exe) ./build/release/$(exe)
	$(strip) ./build/release/$(exe)

rm:
	@rm -f ./build/debug/*.*
	@rm -f ./build/release/*.*