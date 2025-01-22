# Define variables
CXX := g++
CXXFLAGS := -std=c++11 #Tells the compiler to C++11 standard when compiling

# List of common files
common := common/common.h common/common.cpp

# List of GGML Source Files
ggml := src/gguf.cpp src/ggml.c src/ggml-threading.h src/ggml-threading.cpp src/ggml-quants.c  			\
		src/ggml-quants.h src/ggml-opt.cpp src/ggml-impl.h src/ggml-common.h src/ggml-common.h 			\
		src/ggml-backend.cpp src/ggml-backend-reg.cpp src/ggml-backend-impl.h src/ggml-alloc.c 			\
		src/ggml-cpu/ggml-cpu.c src/ggml-cpu/ggml-cpu.cpp src/ggml-cpu/ggml-cpu-traits.h 	  		 	\
		src/ggml-cpu/ggml-cpu-traits.cpp src/ggml-cpu/ggml-cpu-quants.c src/ggml-cpu/ggml-cpu-impl.h    \
		src/ggml-cpu/ggml-cpu-hbm.h src/ggml-cpu/ggml-cpu-hbm.cpp src/ggml-cpu/ggml-cpu-aarch64.h 		\
		src/ggml-cpu/ggml-cpu-aarch64.cpp src/ggml-cpu/cpu-feats-x86.cpp src/ggml.h src/gguf.h			\
		src/ggml-cpp.h src/ggml-cpu.h src/ggml-alloc.h src/ggml-backend.h
ggml_files := $(shell ls -p src | grep -v /)

# build gpt2 project
gpt2: build
	mkdir -p ./build/src/gpt2
	cp -rf gpt2/gpt2-main.cpp ./build/src/gpt2
	cp -rf $(common) ./build/src/gpt2
	cp -rf $(ggml) ./build/src/gpt2
	# ggml_build_files:=$(patsubst %, build/src/gpt2/%, $(ggml_files))

	chmod 444 build/src/gpt2/common.cpp build/src/gpt2/gpt2-main.cpp

	# $(patsubst %, build/src/gpt2/%, $(ggml_files)) 
	$(CXX) $(CXXFLAGS)  build/src/gpt2/common.cpp  build/src/gpt2/gpt2-main.cpp -o build/bin/gpt2
	

# build setup
build: clean
	mkdir -p ./build/bin
	mkdir -p ./build/src
	mkdir -p ./build/src/ggml


clean: 
	rm -rf ./build
