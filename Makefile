#получение исполняемого файла путем компоновки объектных (пока только 1 объектный). 
compile: objectfiles
	g++ -o ./build/study ./build/study.o -static

	
# получение объектного модуля из исходного кода. Получается ELF-файл типа "перемещаемый". Выполнить его пока нельзя, далее нужно его передать компоновщику 

objectfiles: study.cpp
	g++ -g -c study.cpp
	
	mv study.o build/study.o

	
clean: 
	rm -f build/*.o
	rm -f build/study


