CFLAGS = -std=c90 -pedantic -Wall -Wextra -Werror -O3
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -Werror -O3
CPPFLAGS = -Iinclude
LDFLAGS = -lgmp -pthread
SRC = src/
INC = include/
TEST = test/
EXE = cs_add_test

$(TEST)$(EXE): $(TEST)cs_add_test.o $(SRC)cs_add.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST)cs_add_test.o: $(TEST)cs_add_test.cc $(INC)cs_add.h

$(SRC)cs_add.o: $(SRC)cs_add.c $(INC)cs_add.h

.PHONY:
clean:
	$(RM) $(SRC)*.o $(TEST)*.o $(TEST)$(EXE)
