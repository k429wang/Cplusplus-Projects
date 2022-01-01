#include <iostream>
#include "geesespotter_lib.h"

char * createBoard(std::size_t xdim, std::size_t ydim){
    char* p_c = new char[xdim*ydim]{
                                    // 0x29, 0x29, 0x29, 0x29, 0x29,
                                    // 0x29, 0x39, 0x39, 0x39, 0x39,
                                    // 0x29, 0x29, 0x39, 0x29, 0x29,
                                    // 0x29, 0x29, 0x29, 0x39, 0x39,
                                    // 0x29, 0x39, 0x39, 0x39, 0x29,
                                    // 0x29, 0x39, 0x39, 0x29, 0x39 

                                    };

    for (std::size_t i{};i<(xdim*ydim);++i){
        p_c[i]=0;
    }

    return p_c;
}

void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
    for (std::size_t i{}; i<(xdim*ydim);++i){
        board[i]|=0x20;
    }
}

void cleanBoard(char * board){
    delete[] board;
    board=nullptr;
}

void printBoard(char * board, std::size_t xdim, std::size_t ydim){
    char c{};
    for(std::size_t i{};i<ydim;++i){
        for(std::size_t j{};j<xdim;++j){
            c = (board[i*(xdim)+j]);
            if ((c&0b00110000)==0b00110000){
                std::cout << "M";
            } else if ((c&0b00110000)==0b00100000){
                std::cout << "*";
            } else {
                std::cout << (c&0x0F);
            }
        }
        std::cout << std::endl;
    }
}

int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    std::size_t loc = (xloc*(xdim)+yloc);

    if ((board[loc]&0x20)==0x0){
        return 2;
    }

    if ((board[loc]&0x10)==0x10){
        board[loc]&=0b11101111;
    } else if ((board[loc]&0x10)==0x0){
        board[loc]|=0b00010000;
    }

    return 0;
}

void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
    for (std::size_t i{};i<ydim;++i){
        for (std::size_t j{};j<xdim;++j){
            if ((board[i*(xdim)+j]&0x09)==0x09){
                for (int k{-1};k<=1;++k){
                    for (int l{-1};l<=1;++l){
                        int a = i+k;
                        int b = j+l;
                        char c = board[(a)*(xdim)+(b)];
                        if ((c!=0x09)&&(a>=0)&&(b>=0)&&(a<ydim)&&(b<xdim)){
                            board[(a)*(xdim)+(b)]+=1;
                        }
                    }
                }
            }
        }
    }
}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    int loc = yloc*(xdim)+xloc;
    if ((board[loc]&0x30)==0x30){
        return 1;     
    } else if ((board[loc]&0x20)==0x00){
        return 2;
    } else if ((board[loc]&0x09)==0x09){
        board[loc]&=0x09;
        return 9;
    } else if ((board[loc]&0x09)!=0x00){
        board[loc]&=0x09;
        return 0;
    } else {
        for (int k{-1};k<=1;++k){
            for (int l{-1};l<=1;++l){
                int a = yloc+k;
                int b = xloc+l;
                if ((a>=0)&&(b>=0)&&(a<ydim)&&(b<xdim)){
                    board[(a)*(xdim)+(b)]&=0x09;
                }
            }
        }
        return 0;
    }
}

bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    std::size_t counter{};
    for(std::size_t i{};i<ydim;++i){
        for(std::size_t j{};j<xdim;++j){
            if (((board[i*(xdim)+j]&0x30)!=0x00)){
                if (((board[i*(xdim)+j]&0x0F)!=0x09)){
                    // std::cout << (i) << std::endl;
                    // std::cout << (j) << std::endl;
                    // std::cout << (int)(board[i*(xdim)+j]) << std::endl;
                    // std::cout << (board[i*(xdim)+j]&0x0F) << std::endl;
                    return false;
                }
                 if (((board[i*(xdim)+j]&0x20)!=0x09)){
                    counter++;
                }
            }
        }
    }
    if (counter==(xdim*ydim)){
        return false;
    }
    return true;
}

// int main();
// int main(){
//     char* p_b = createBoard(8,5);
//     computeNeighbors(p_b,8,5);
//     hideBoard(p_b,8,5);
//     printBoard(p_b,8,5);
//     std::cout << std::endl;
//     reveal(p_b,8,5,7,4);
//     printBoard(p_b,8,5);
//     //std::cout << isGameWon(p_b, 5,6) << std::endl;
// }