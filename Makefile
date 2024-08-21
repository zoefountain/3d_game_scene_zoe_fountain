CXX				:= g++

DOXYGEN 		:= doxygen

BUILD_DIR		:= ./bin
SRC_DIR			:= ./src
DOCS_DIR		:= ./docs

MSG_START		:= "Build Started"
MSG_END			:= "Build Complete"
MSG_CLEAN		:= "Cleaning up"
MSG_DOC_START	:= "Documents Generation Starts"
MSG_DOC_END		:= "Documents Generation Starts"


ifeq ($(OS),Windows_NT)
    os  := Windows
	# Make sure your Env Variable is set to SFML
	# Tested with SFML 2.5.1 GCC 7.3.0 MinGW (SEH) - 64-bit
	# Convert Windows directory path to UNIX Path
	SDK         := ${MYSYS2}
    SDK_PATH    := $(subst \,/,$(subst C:\,/c/,$(SDK)))
    INCLUDES    := -I/mingw64/include -I. -I${SDK_PATH}/include -I. -I/mingw64/include/GLFW  
	LIBS        := -L${SDK_PATH}/lib -L/mingw64/lib
    CXXFLAGS	:= -std=c++11 -Wall -Wextra -g ${INCLUDES}
    LIBRARIES   := -lsfml-graphics -lsfml-window -lsfml-system -lglew32 -lopengl32 -lglu32 -lglfw3
    TARGET      := ${BUILD_DIR}/sampleapp.exe
else
    os          := $(shell uname -s)
    INCLUDES    := -I.
    LIBS        := -L.
    CXXFLAGS    := -std=c++11 -Wall -Wextra -g ${INCLUDES}
    LIBRARIES   := -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLEW -lglfw
    TARGET      := ${BUILD_DIR}/sampleapp.bin
endif

SRC				:=	$(wildcard ${SRC_DIR}/*.cpp) # List the CPP src files

all				:= build

build:
	@echo 	${MSG_START} ${os}

	@echo 		"***	C++ Compiler	***"
	@echo 		${CXX}
	@echo 		"*** C++ Flags		***"
	@echo 		${CXXFLAGS}
	@echo 		"*** LIBRARIES		***"
	@echo 		${LIBRARIES}
	@echo 		"*** SRC		***"
	@echo 		${SRC}
	@echo 		"*** TARGET		***"
	@echo 		${TARGET}

	@#remove directory if it exits and then create directory
	@rm -rf 		${BUILD_DIR} 	|| 	true

	@#create bin directory
	@mkdir 		${BUILD_DIR}

	@#remove directory if it exits and then create directory
	@rm -rf 		${DOCS_DIR} 	|| 	true

	@#create docs directory
	@mkdir 		${DOCS_DIR}

	${CXX} ${CXXFLAGS} -o ${TARGET} ${SRC} ${LIBS} ${LIBRARIES}
	
	@echo ${MSG_END}
	
	@# Run TARGET
	./${TARGET}

docs:
	@echo 	${MSG_DOC_START}
	$(DOXYGEN) ./Doxyfile
	@echo 	${MSG_DOC_END}

.PHONY: clean

clean:
	@echo 		${MSG_CLEAN}
	rm -rf 		${BUILD_DIR} ${DOCS_DIR} || true