#include <iostream>
#include <string>
#include <unordered_map>

int main(int argc, char**argv ){

    std::string input = "This is a piece of text used to demonstrate Huffman encoding";
    std::unordered_map<std::string, int> alphabet;
    for(int i = 0; i < input.size(); i++){
        alphabet[input.substr(i,1)]++;
    }

    std::cout << "total chars: " << input.size() << std::endl;
    for(auto out : alphabet){
        std::cout << out.first << " | " << out.second << std::endl;
    }
}

// Huffman encoding